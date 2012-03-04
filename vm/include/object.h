/*  object.h
 *
 *  Copyright (C) 2012 by Claes Jakobsson
 *    
 *  You may distribute under the terms of MIT/X license, as specified in README and LICENSE
 */

#ifndef __OBJECT_H__
#define __OBJECT_H__

struct YogoPackage;
struct YogoValue;
 
extern struct YogoPackage *yogo_get_package(YogoInterp *, YogoValue *);

#endif