/*  interp.h
 *
 *  Copyright (C) 2012 by Claes Jakobsson
 *    
 *  You may distribute under the terms of MIT/X license, as specified in README and LICENSE
 */

#ifndef __INTERP_H__
#define __INTERP_H__

#define dINTERP YogoInterp*
#define pINTERP dINTERP my_yogo, 

struct YogoClass;
struct YogoFunction;

struct YogoInterp {    
    int x;
};

typedef struct YogoInterp YogoInterp;

void run_bytecode_interp(YogoInterp *, struct YogoClass *, struct YogoFunction *);

#endif