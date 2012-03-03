/*  str.h
 *
 *  Copyright (C) 2012 by Claes Jakobsson
 *    
 *  You may distribute under the terms of MIT/X license, as specified in README and LICENSE
 */
 
#ifndef __STR_H__
#define __STR_H__

extern YogoValue* yogo_create_string(const char *);
extern const char *yogo_get_string(YogoValue *);

#endif
