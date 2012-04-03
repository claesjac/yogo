/*  interp.c
 *
 *  Copyright (C) 2012 by Claes Jakobsson
 *    
 *  You may distribute under the terms of MIT/X license, as specified in README and LICENSE
 */

#include "yogo.h"
#include "error.h"
#include "interp.h"
#include "loader.h"

#include <errno.h>
#include <string.h>

static void S_init_standard_packagees(YogoInterp *interp) {
    yogo_init_packageloader(interp);
}

YogoInterp *yogo_create_interp(void) {
    YogoInterp *interp = calloc(1, sizeof(YogoInterp));
    
    yogo_grow_stack(interp, YOGO_DEFAULT_STACK_SIZE);
    interp->curr_stack_top = interp->stack;

    interp->classes = (Pvoid_t) NULL;
    interp->constant_pool_index = (Pvoid_t) NULL;
    interp->constant_pool_value = (Pvoid_t) NULL;
    interp->next_constant_pool_index = 1;
    
    S_init_standard_packagees(interp);
    
    return interp;
}

void yogo_grow_stack(YogoInterp *interp, uint32_t count) {
    uint32_t new_stack_size = interp->stack_size + count;
    interp->stack = realloc(interp->stack, new_stack_size);
    if (interp->stack == NULL) {
        YOGO_REPORT_ERROR("Failed to increase stack size because of: %s", strerror(errno));
    }
    interp->stack_max = interp->stack + new_stack_size;

    interp->stack_size = new_stack_size;
}

void yogo_push_stack(YogoInterp *interp, YogoValue *v) {
    if (interp->curr_stack_top == interp->stack_max) {
        yogo_grow_stack(interp, YOGO_DEFAULT_STACK_SIZE);
    }

    *interp->curr_stack_top = v;
    interp->curr_stack_top++;
}

YogoValue *yogo_pop_stack(YogoInterp *interp) {
    YogoValue *v = *(interp->curr_stack_top - 1);
    interp->curr_stack_top--;
    return v; 
}

YogoValue *yogo_peek_stack(YogoInterp *interp) {
    YogoValue *v = *(interp->curr_stack_top - 1);
    return v; 
}

YogoPackage *yogo_find_package(YogoInterp *interp, const char *name) {
    PWord_t c;
        
    JSLF(c, interp->classes, (uint8_t *) name);
    if (c == NULL) {
        YOGO_REPORT_INFO("Didn't find class: %s\n", name);
        return NULL;
    }
    
    return (YogoPackage *) *c;    
}

void yogo_define_package(YogoInterp *interp, const char *name, YogoPackage *cls) {
    PPvoid_t v;
    JSLI(v, interp->classes, (const uint8_t *) name);    
    *v = cls;
}

int yogo_add_constant(YogoInterp *interp, YogoConstantPoolType type, size_t length, void *value) {    
    Word_t *c;
    uint32_t i;
    int64_t iv;
    double dv;
    char *v;
    YogoValue *yv;
    
    v = malloc(length + 1);
    v[0] = type;
    memcpy(&v[1], value, length);
    
    JHSG(c, interp->constant_pool_index, v, length + 1);
    if (c == NULL) {
        i = interp->next_constant_pool_index++;
                
        JHSI(c, interp->constant_pool_index, v, length + 1);
        *c = i;
        
        JLI(c, interp->constant_pool_value, i);
        
        switch (type) {
            case YCP_Integer:
                memcpy(&iv, value, sizeof(int64_t));
                yv = yogo_new_integer(iv);
                *c = (Word_t) yv;
            break;
            
            case YCP_Double:
                memcpy(&dv, value, sizeof(double));
                yv = yogo_new_double(dv);
                *c = (Word_t) yv;
            break;
            
            case YCP_String:
                yv = yogo_new_string(length, (const char *) value);
                *c = (Word_t) yv;
            break;
            
            default:
                YOGO_REPORT_ERROR("Invalid constant pool type: %d\n", type);
        }
            
        return i;
    }
    else {
        YOGO_REPORT_INFO("Item already exists\n");
    }

    return i;
}

