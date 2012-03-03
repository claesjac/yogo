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
    YVt_INT,         /* Integer */
    YVt_DOUBLE,      /* Double */
    YVt_REF,         /* Reference */
    YVt_OBJECT,      /* Object */
    YVt_LIST,        /* List */
    YVt_MAP,         /* Map */
    YVt_STRING,      /* String */
} YogoType;

#define YVt_MASK 0x03

struct YogoValue {
    uint16_t flags;
    uint32_t refcnt;
    
    union {
        uint64_t    ival;   /* Integer */
        double      dval;   /* Double */
        void       *pval;   /* String, Map, List, Object */
    } val;
};

typedef struct YogoValue YogoValue;

#endif