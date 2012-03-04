/*  package.h
 *
 *  Copyright (C) 2012 by Claes Jakobsson
 *    
 *  You may distribute under the terms of MIT/X license, as specified in README and LICENSE
 */

#ifndef __CLASS_H__
#define __CLASS_H__

#include "interp.h"
#include "function.h"

#include <Judy.h>

struct YogoPackage {
    const char *name;    
    Pvoid_t functions;
};

typedef struct YogoPackage YogoPackage;

extern YogoPackage *yogo_create_package(YogoInterp *, const char *);

extern YogoFunction *yogo_get_function(YogoInterp *, YogoPackage *, const char *);
extern void yogo_define_function(YogoInterp *, YogoPackage *, const char *, YogoFunction *f);

#endif