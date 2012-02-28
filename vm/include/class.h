/*
    (c) Claes Jakobsson 2012
    
    released under BSD license
*/

#ifndef __CLASS_H__
#define __CLASS_H__

#include <Judy.h>

struct YogoClass {
    const char *name;    
    struct YogoClass *parent;
    
    Pvoid_t functions;
};

typedef struct YogoClass YogoClass;

struct YogoFunction {
    const char *name;
    void (*callptr)(YogoClass *, struct YogoFunction *);
    void *data;
};

typedef struct YogoFunction YogoFunction;

#endif