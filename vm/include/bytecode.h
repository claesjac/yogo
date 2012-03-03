/*  bytecode.h
 *
 *  Copyright (C) 2012 by Claes Jakobsson
 *    
 *  You may distribute under the terms of MIT/X license, as specified in README and LICENSE
 */

#ifndef __BYTECODE_H__
#define __BYTECODE_H__

#define OPCODE(code, mnemonic, operands, kind) OP_ ## mnemonic = code,

enum Opcode {
OPCODE(  0, null,   0, )

/* These push a constant value onto the stack */
OPCODE(  1, iconst_n1, 0, )
OPCODE(  2, iconst_0, 0, )
OPCODE(  3, iconst_1, 0, )
OPCODE(  4, iconst_2, 0, )
OPCODE(  5, iconst_3, 0, )
OPCODE(  6, iconst_4, 0, )
OPCODE(  7, iconst_5, 0, )
OPCODE(  8, true,   0, )
OPCODE(  9, false,  0, )

/* Tests */
OPCODE( 20, istrue, 1, addr)
OPCODE( 21, isnull, 1, addr)
OPCODE( 22, iseq,   1, addr)
OPCODE( 23, islt,   1, addr)
OPCODE( 24, isgt,   1, addr)
OPCODE( 25, isle,   1, addr)
OPCODE( 26, isge,   1, addr)

/* Bitwise */
OPCODE( 40, band, 0, )
OPCODE( 41, bor, 0, )
OPCODE( 42, bnot, 0, )
OPCODE( 43, bxor, 0, )

/* Logical */
OPCODE( 50, and, 0, )
OPCODE( 51, or, 0, )
OPCODE( 52, not, 0, )
OPCODE( 53, xor, 0, )

/* Flow control */
OPCODE( 60, return, 0, )
OPCODE( 61, call, 0, )

/* List */
OPCODE( 70, shift,  0, )
OPCODE( 71, unshift,  0, )
OPCODE( 72, pop,  0, )
OPCODE( 73, push,  0, )
OPCODE( 74, peek,  0, )
OPCODE( 75, dup, 0, )
OPCODE( 76, splice, 0, )

/* Map/List */
OPCODE( 80, get, 0, )
OPCODE( 81, set, 0, )

/* Map */
OPCODE( 83, keys, 0, )
OPCODE( 84, values, 0, )

/* Stack */
OPCODE( 76, load,  1, num)
OPCODE( 76, store, 1, num)

/* Io */
OPCODE(  100, print,  0, )

};

#endif