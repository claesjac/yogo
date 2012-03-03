/*  interp.c
 *
 *  Copyright (C) 2012 by Claes Jakobsson
 *    
 *  You may distribute under the terms of MIT/X license, as specified in README and LICENSE
 */

#include "yogo.h"
#include "error.h"
#include "interp.h"
#include "classloader.h"

#include <errno.h>
#include <string.h>

static void S_init_standard_classes(YogoInterp *interp) {
    yogo_init_classloader(interp);
}

YogoInterp *yogo_create_interp(void) {
    YogoInterp *interp = calloc(1, sizeof(YogoInterp));
    
    yogo_grow_stack(interp, YOGO_DEFAULT_STACK_SIZE);
    interp->curr_stack_top = *(interp->stack);

    interp->classes = (Pvoid_t) NULL;
    
    S_init_standard_classes(interp);
    
    return interp;
}

void yogo_grow_stack(YogoInterp *interp, uint32_t count) {
    uint32_t new_stack_size = interp->stack_size + count;
    interp->stack = realloc(interp->stack, new_stack_size);
    if (interp->stack == NULL) {
        YOGO_REPORT_ERROR("Failed to increase stack size because of: %s", strerror(errno));
    }
    interp->stack_size = new_stack_size;
}

void yogo_push_stack(YogoInterp *interp, YogoValue *v) {
    
}

YogoValue *yogo_pop_stack(YogoInterp *interp) {
}

YogoValue *yogo_peek_stack(YogoInterp *interp) {
    
}

YogoValue *