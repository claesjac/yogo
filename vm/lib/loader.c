/*  classloader.c
 *
 *  Copyright (C) 2012 by Claes Jakobsson
 *    
 *  You may distribute under the terms of MIT/X license, as specified in README and LICENSE
 */

#include "yogo.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>

#include <Judy.h>

#define LOAD_BUFFER_SIZE 4096

static const char *MAGIC_IDENTIFIER = "YOGO";

static void system_loader(YogoInterp *, YogoPackage *c, YogoFunction *f);
static void load_package(YogoInterp *, YogoPackage *c, YogoFunction *f);

void yogo_init_packageloader(YogoInterp *interp) {
    YogoPackage *c;
    YogoFunction *system_loader_func, *load_package_func;
    
    c = yogo_create_package(interp, "Yogo::Loader");
    system_loader_func = yogo_create_native_function(interp, system_loader, NULL);
    load_package_func = yogo_create_native_function(interp, load_package, NULL);
    
    yogo_define_function(interp, c, "system_loader", system_loader_func);
    yogo_define_function(interp, c, "load", load_package_func);
    
    yogo_define_package(interp, c->name, c);
}

void system_loader(YogoInterp *interp, YogoPackage *cls, YogoFunction *f) {
    yogo_push_stack(interp, yogo_create_string("Yogo::Loader"));
}

void load_package(YogoInterp *interp, YogoPackage *cls, YogoFunction *func) {
    FILE *in;
    char buffer[LOAD_BUFFER_SIZE];
    char *name;
    uint16_t major, minor, function_count;
    uint16_t length;
    uint16_t *op_base;
    uint32_t op_count;
    uint32_t i;
    YogoPackage *loaded_cls;
    YogoFunction *loaded_func;

    const char *path = yogo_get_string(yogo_pop_stack(interp));

    in = fopen(path, "r");
    if (in == NULL) {
        YOGO_REPORT_ERROR("Unable to load %s because of: %s\n", path, strerror(errno));
    }
    
    /* Header: magic value (4 bytes), major version (1 byte), minor version (1) byte */
    memset(buffer, 0, LOAD_BUFFER_SIZE);
    if (fread(buffer, sizeof(char), 8, in) != 8) { 
        YOGO_REPORT_ERROR("Failed to read header because of: %s\n", strerror(errno));
    }
    if (strncmp(buffer, MAGIC_IDENTIFIER, 4) != 0) {
        YOGO_REPORT_ERROR("Not a yogo object file\n");
    }
    
    major = (int) buffer[4];
    minor = (int) buffer[5];
        
    /* Name of class if any */
    memcpy(&length, buffer + 6, sizeof(uint16_t));
    length = htons(length);
    if (length) {
        if (fread(buffer, sizeof(char), length, in) != length) {
            YOGO_REPORT_ERROR("Failed to read name because of: %s\n", strerror(errno));
        }
        buffer[length] = '\0';
        name = strdup(buffer);
    }

    loaded_cls = yogo_create_package(interp, name);
    
    /* Constant pool */
    if (fread(buffer, sizeof(uint16_t), 1, in) != 1) {
        YOGO_REPORT_ERROR("Failed to read constant pool length because of: %s\n", strerror(errno));
    }
    
    /* Number of functions */
    if (fread(buffer, sizeof(uint16_t), 1, in) != 1) {
        YOGO_REPORT_ERROR("Failed to read function count\n");
    }
    memcpy(&function_count, buffer, sizeof(uint16_t));
    function_count = htons(function_count);
        
    for (i = 0; i < function_count; i++) {
        if (fread(&length, sizeof(uint16_t), 1, in) != 1) {
            YOGO_REPORT_ERROR("Failed to read function name length: %s", strerror(errno));
        }
        length = htons(length);
        if (!length) {
            YOGO_REPORT_ERROR("Invalid class file, missing function name length\n");
        }
        
        if (fread(buffer, sizeof(char), length, in) != length) {
            YOGO_REPORT_ERROR("Failed to read function name: %s", strerror(errno));
        }        
        buffer[length] = '\0';
        
        func = calloc(sizeof(YogoFunction), 1);
        name = strdup(buffer);
        
        if (fread(&op_count, sizeof(uint32_t), 1, in) != 1) {
            YOGO_REPORT_ERROR("Failed to read number of ops for %s\n", name);
        }
        op_count = htonl(op_count);
        op_base = calloc(sizeof(uint16_t), op_count);
        if (fread(op_base, sizeof(uint16_t), op_count, in) != op_count) {
            YOGO_REPORT_ERROR("Failed to read function ops for %s\n", name);
        }

        /* Byteswap as it's stored in network byte order */
        for (i = 0; i < op_count; i++) {
            op_base[i] = htons(op_base[i]);
        }
        
        loaded_func = yogo_create_native_function(interp, run_bytecode_interp, op_base);
        yogo_define_function(interp, loaded_cls, name, loaded_func);
        free(name);
    }
    
    yogo_define_package(interp, loaded_cls->name, loaded_cls);
    
    /* Initialize class */
    yogo_push_stack(interp, yogo_create_string(loaded_cls->name));
    yogo_call_str(interp, "<clinit>");
}