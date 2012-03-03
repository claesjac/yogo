/*  class.h
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

struct YogoClass {
    const char *name;    
    Pvoid_t functions;
};

typedef struct YogoClass YogoClass;

extern YogoClass *yogo_create_class(YogoInterp *, const char *);
extern void yogo_bind_function(YogoInterp *, YogoClass *, const char *name, YogoFunction *f);

#endif