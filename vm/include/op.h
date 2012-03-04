/*  op.h
 *
 *  Copyright (C) 2012 by Claes Jakobsson
 *    
 *  You may distribute under the terms of MIT/X license, as specified in README and LICENSE
 */

#ifndef __OP_H__
#define __OP_H__

#include "package.h"

#define OP(op) void op_ ## op(void *stack)

#endif