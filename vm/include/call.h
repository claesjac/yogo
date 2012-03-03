/*  call.h
 *
 *  Copyright (C) 2012 by Claes Jakobsson
 *    
 *  You may distribute under the terms of MIT/X license, as specified in README and LICENSE
 */

#ifndef __CALL_H__
#define __CALL_H__

#include "class.h"
#include "interp.h"

extern void yogo_call_method(YogoInterp *, YogoClass *, YogoFunction *);
extern void yogo_call_str(YogoInterp *, const char *);

#endif