/*  function.h
 *
 *  Copyright (C) 2012 by Claes Jakobsson
 *    
 *  You may distribute under the terms of MIT/X license, as specified in README and LICENSE
 */

#ifndef __FUNCTION_H__
#define __FUNCTION_H__

struct YogoPackage;
struct YogoInterp;
struct YogoFuction;

typedef void (*YogoNative)(struct YogoInterp *, struct YogoPackage *cls, struct YogoFunction *func);

struct YogoFunction {
    YogoNative callptr;
    uint32_t op_count;
    void *data;
};

typedef struct YogoFunction YogoFunction;

extern YogoFunction *yogo_create_native_function(struct YogoInterp *, YogoNative, void *data);

#endif