/*  interp.h
 *
 *  Copyright (C) 2012 by Claes Jakobsson
 *    
 *  You may distribute under the terms of MIT/X license, as specified in README and LICENSE
 */

#ifndef __INTERP_H__
#define __INTERP_H__

#include "types.h"
#include <stdint.h>

#include <Judy.h>

#define dINTERP YogoInterp*
#define pINTERP dINTERP my_yogo, 

#define YOGO_DEFAULT_STACK_SIZE 32
#define YOGO_DEFAULT_STACK_GROW 32

struct YogoPackage;
struct YogoFunction;

typedef enum {
    YCP_Integer,
    YCP_Double,
    YCP_String
} YogoConstantPoolType;
    
struct YogoInterp {    
    YogoValue   **curr_stack_top;
    YogoValue   **stack_max;
    YogoValue   **stack;
    uint32_t    stack_size;
    
    /* JudyHS with the constant pool */
    Pvoid_t     constant_pool_index;
    Pvoid_t     constant_pool_value;
    uint32_t    next_constant_pool_index;
    
    /* JudySL with the package names */
    Pvoid_t     classes;
};

typedef struct YogoInterp YogoInterp;

extern YogoInterp *yogo_create_interp();

extern void run_bytecode_interp(YogoInterp *, struct YogoPackage *, struct YogoFunction *);

extern void yogo_grow_stack(YogoInterp *, uint32_t);
extern void yogo_push_stack(YogoInterp *, YogoValue *);
extern YogoValue *yogo_pop_stack(YogoInterp *);
extern YogoValue *yogo_peek_stack(YogoInterp *);

extern void yogo_define_package(YogoInterp *, const char *, struct YogoPackage *);
extern struct YogoPackage *yogo_find_package(YogoInterp *, const char *);
extern int yogo_add_constant(YogoInterp *, YogoConstantPoolType, size_t, void *);
#endif