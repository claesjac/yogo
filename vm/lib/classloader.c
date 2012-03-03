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

static void system_loader(YogoInterp *, YogoClass *c, YogoFunction *f);
static void load_class(YogoInterp *, YogoClass *c, YogoFunction *f);

void yogo_init_classloader(YogoInterp *interp) {
    YogoClass *c;
    YogoFunction *system_loader_func, *load_class_func;
    
    c = yogo_create_class(interp, "Yogo::ClassLoader");
    system_loader_func = yogo_create_native_function(interp, system_loader, NULL);
    load_class_func = yogo_create_native_function(interp, load_class, NULL);
    
    yogo_define_function(interp, c, "system_loader", system_loader_func);
    yogo_define_function(interp, c, "load", load_class_func);
    
    yogo_define_class(interp, c, c->name);
}

void system_loader(YogoInterp *interp, YogoClass *cls, YogoFunction *f) {
    
}

void load_class(YogoInterp *interp, YogoClass *cls, YogoFunction *f) {
    FILE *in;
    char buffer[LOAD_BUFFER_SIZE];
    char *name;
    uint16_t major, minor, function_count;
    uint16_t length;
    uint16_t *op_base;
    uint32_t op_count;
    uint32_t i;
    YogoClass *class;
    YogoFunction *func;
    Pvoid_t functions_array;
    PWord_t function_element;
    const char *path = "";
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
    
    class = calloc(1, sizeof(YogoClass));
    
    YOGO_REPORT_INFO("Version: %d.%d\n", major, minor);    

    /* Name of class if any */
    memcpy(&length, buffer + 6, sizeof(uint16_t));
    length = htons(length);
    if (length) {
        if (fread(buffer, sizeof(char), length, in) != length) {
            YOGO_REPORT_ERROR("Failed to read name because of: %s\n", strerror(errno));
        }
        buffer[length] = '\0';
        class->name = strdup(buffer);
    }

    YOGO_REPORT_INFO("Read classname: %s\n", class->name);

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
    
    functions_array = (PWord_t) NULL;
    
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
        func->data = calloc(sizeof(uint16_t), op_count);
        if (fread(func->data, sizeof(uint16_t), op_count, in) != op_count) {
            YOGO_REPORT_ERROR("Failed to read function ops for %s\n", name);
        }

        /* Byteswap as it's stored in network byte order */
        op_base = func->data;
        for (i = 0; i < op_count; i++) {
            op_base[i] = htons(op_base[i]);
        }
        
        YOGO_REPORT_INFO("Read function: %s\n", name);
        func->callptr = run_bytecode_interp;
        
        JSLI(function_element, functions_array, (const uint8_t *) name);
        if (function_element == PJERR) {
            YOGO_REPORT_ERROR("Failed to create entry for function\n");
        }
        
        *function_element = (unsigned long) func;
    }
    
    class->functions = functions_array;    
}