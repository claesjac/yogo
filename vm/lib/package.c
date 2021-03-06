/*  class.c
 *
 *  Copyright (C) 2012 by Claes Jakobsson
 *    
 *  You may distribute under the terms of MIT/X license, as specified in README and LICENSE
 */

#include "yogo.h"

#include <Judy.h>
#include <string.h>

YogoPackage *yogo_create_package(YogoInterp *interp, const char *name) {
    YogoPackage *cls = calloc(1, sizeof(YogoPackage));
    
    if (name != NULL) {
        cls->name = strdup(name);
    }
    
    cls->functions = (PWord_t) NULL;
    
    return cls;
}

YogoFunction *yogo_get_function(YogoInterp *interp, YogoPackage *cls, const char *name) {
    PWord_t f;
    
    JSLF(f, cls->functions, (uint8_t *) name);
    if (f == NULL) {
        YOGO_REPORT_INFO("Didn't find method, must traverse parents\n");
        return NULL;
    }
    
    return (YogoFunction *) *f;
}

void yogo_define_function(YogoInterp *interp, YogoPackage *cls, const char *name, YogoFunction *func) {
    PPvoid_t v;
    JSLI(v, cls->functions, (const uint8_t *) name);    
    *v = func;
}