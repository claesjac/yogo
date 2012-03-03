/*  loader.h
 *
 *  Copyright (C) 2012 by Claes Jakobsson
 *    
 *  You may distribute under the terms of MIT/X license, as specified in README and LICENSE
 */

#ifndef __LOADER_H__
#define __LOADER_H__

#include "class.h"

YogoClass *load_class(const char *path);

void yogo_init_classloader(YogoInterp* interp);

#endif