/*
    (c) Claes Jakobsson 2012
    
    released under BSD license
*/

#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdio.h>
#include <stdlib.h>

#define REPORT_ERROR(...) \
    fprintf(stderr, __VA_ARGS__); \
    exit(1)

#define REPORT_INFO(...) fprintf(stderr, __VA_ARGS__)

#endif