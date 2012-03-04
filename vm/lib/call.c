/*  call.c
 *
 *  Copyright (C) 2012 by Claes Jakobsson
 *    
 *  You may distribute under the terms of MIT/X license, as specified in README and LICENSE
 */

#include "yogo.h"

void yogo_call_str(YogoInterp *interp, const char *name) {
    YogoValue *t;
    YogoPackage *cls;
    YogoFunction *func;

    t = yogo_pop_stack(interp);
    /* Find target class */
    if (YV_IS_STRING(t)) {
        cls = yogo_find_package(interp, yogo_get_string(t));;
    }
    else if (YV_IS_OBJECT(t)) {
        cls = yogo_get_package(interp, t);
    }
    else {
        cls = NULL;
    }
    
    if (cls == NULL) {
        YOGO_REPORT_ERROR("Unable to find target class");
    }
    
    func = yogo_get_function(interp, cls, name);
    if (func == NULL) {
        YOGO_REPORT_ERROR("Unable to find function with name: %s", name);
    }
    
    yogo_call_method(interp, cls, func);
}

void yogo_call_method(YogoInterp *interp, YogoPackage *cls, YogoFunction *func) {
    func->callptr(interp, cls, func);
}