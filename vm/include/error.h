/*  error.h
 *
 *  Copyright (C) 2012 by Claes Jakobsson
 *    
 *  You may distribute under the terms of MIT/X license, as specified in README and LICENSE
 */

#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdio.h>
#include <stdlib.h>

#define YOGO_REPORT_ERROR(...) \
    fprintf(stderr, __VA_ARGS__); \
    exit(1)

#define YOGO_REPORT_INFO(...) fprintf(stderr, __VA_ARGS__)

#endif