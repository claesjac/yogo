/*  class.c
 *
 *  Copyright (C) 2012 by Claes Jakobsson
 *    
 *  You may distribute under the terms of MIT/X license, as specified in README and LICENSE
 */

#include "yogo.h"
#include "class.h"

#include <string.h>

YogoClass *yogo_create_class(pINTERP const char *name) {
    YogoClass *cls = calloc(1, sizeof(YogoClass));
    
    if (name != NULL) {
        cls->name = strdup(name);
    }
    
    cls->functions = (PWord_t) NULL;
    
    return cls;
}

void yogo_bind_function(YogoInterp *interp, YogoClass *cls, const char *name, YogoFunction *func) {
    
}