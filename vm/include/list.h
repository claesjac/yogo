/*  list.h
 *
 *  Copyright (C) 2012 by Claes Jakobsson
 *    
 *  You may distribute under the terms of MIT/X license, as specified in README and LICENSE
 */

#ifndef __LIST_H__
#define __LIST_H__

#define YOGO_LIST_HEAD \
    void (*push)(void *); \
    void (*pop)(void *); \
    void (*shift)(void *); \
    void (*unshift)(void *); \
    void (*splice)(void *); \
    void (*get)(void *); \
    void (*set)(void *)
        
#endif

struct YogoList {
    YOGO_LIST_HEAD;
};

typedef struct YogoList;

