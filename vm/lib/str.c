/*  str.c
 *
 *  Copyright (C) 2012 by Claes Jakobsson
 *    
 *  You may distribute under the terms of MIT/X license, as specified in README and LICENSE
 */

#include "types.h" 
#include "str.h"

#include <stdlib.h>
#include <string.h>

YogoValue *yogo_create_string(const char *str) {
    YogoValue *v = calloc(1, sizeof(YogoValue));
    v->flags |= YVt_STRING;
    v->val.pval = strdup(str);
    v->refcnt++;
    return v;
}

const char *yogo_get_string(YogoValue *v) {
    if (YV_IS_STRING(v)) {
        return (const char *) v->val.pval;
    }
    
    /* TODO, stringify value */
    return "";
}