/*  op_io.c
 *
 *  Copyright (C) 2012 by Claes Jakobsson
 *    
 *  You may distribute under the terms of MIT/X license, as specified in README and LICENSE
 */

#include "op.h"
#include "op_io.h"

#include <stdio.h>

OP(print) {
    fprintf(stderr, "Hello %s\n", "world");
}