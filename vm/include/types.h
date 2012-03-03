/*  types.h
 *
 *  Copyright (C) 2012 by Claes Jakobsson
 *    
 *  You may distribute under the terms of MIT/X license, as specified in README and LICENSE
 */

#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdint.h>

typedef enum {
    YVt_NULL = 0,    /* Undefined */
    YVt_INTEGER,     /* Integer */
    YVt_DOUBLE,      /* Double */
    YVt_REFERENCE,   /* Reference */
    YVt_OBJECT,      /* Object */
    YVt_LIST,        /* List */
    YVt_MAP,         /* Map */
    YVt_STRING,      /* String */
} YogoType;

#define YVt_MASK 0x7

#define YV_IS_NULL(v) ((v->flags & YVt_MASK) == YVt_NULL)
#define YV_IS_INTEGER(v) ((v->flags & YVt_MASK) == YVt_INTEGER)
#define YV_IS_DOUBLE(v) ((v->flags & YVt_MASK) == YVt_DOUBLE)
#define YV_IS_REFERENCE(v) ((v->flags & YVt_MASK) == YVt_REFERENCE)
#define YV_IS_OBJECT(v) ((v->flags & YVt_MASK) == YVt_OBJECT)
#define YV_IS_LIST(v) ((v->flags & YVt_MASK) == YVt_LIST)
#define YV_IS_MAP(v) ((v->flags & YVt_MASK) == YVt_MAP)
#define YV_IS_STRING(v) ((v->flags & YVt_MASK) == YVt_STRING)

struct YogoValue {
    uint16_t flags;
    uint32_t refcnt;
    
    union {
        int64_t    ival;   /* Integer */
        double      dval;   /* Double */
        void       *pval;   /* String, Map, List, Object */
    } val;
};

typedef struct YogoValue YogoValue;

extern YogoValue *yogo_new_integer(const int64_t);
extern YogoValue *yogo_new_double(const double);
extern YogoValue *yogo_new_reference(YogoValue *);

#endif