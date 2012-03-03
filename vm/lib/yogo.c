/*  yogo.c
 *
 *  Copyright (C) 2012 by Claes Jakobsson
 *    
 *  You may distribute under the terms of MIT/X license, as specified in README and LICENSE
 */

#include "yogo.h"
#include "classloader.h"

static void S_init_standard_classes(YogoInterp *interp) {
    yogo_init_classloader(interp);
}

YogoInterp *yogo_init(void) {
    YogoInterp *interp = calloc(1, sizeof(YogoInterp));
    
    S_init_standard_classes(interp);
    
    return interp;
}


