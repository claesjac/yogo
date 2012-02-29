/*
    (c) Claes Jakobsson 2012
    
    released under BSD license
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
OPCODE(  8, iconst_6, 0, )
OPCODE(  9, iconst_7, 0, )
OPCODE( 10, iconst_8, 0, )

/* Tests */
OPCODE( 11, true,   0, )
OPCODE( 12, false,  0, )
OPCODE( 20, istrue, 1, addr)
OPCODE( 21, isfalse, 1, addr)
OPCODE( 23, iseq,   1, addr)
OPCODE( 24, isne,   1, addr)
OPCODE( 25, islt,   1, addr)
OPCODE( 26, isgt,   1, addr)
OPCODE( 27, isle,   1, addr)
OPCODE( 28, isge,   1, addr)

/* Binary */
OPCODE( 40, iand, 0, )
OPCODE( 41, ior, 0, )
OPCODE( 42, inot, 0, )
OPCODE( 43, ixor, 0, )

/* Logical */
OPCODE( 50, and, 0, )
OPCODE( 51, or, 0, )
OPCODE( 52, not, 0, )
OPCODE( 53, xor, 0, )

/* Flow control */
OPCODE( 60, return, 0, )

/* Stack */
OPCODE( 70, shift,  0, )
OPCODE( 71, unshift,  0, )
OPCODE( 72, pop,  0, )
OPCODE( 73, push,  0, )
OPCODE( 74, peek,  0, )
OPCODE( 75, dup,  0, )
OPCODE( 76, iload,  1, num)
OPCODE( 76, istore, 1, num)
OPCODE( 77, dload,  1, num)
OPCODE( 78, dstore, 1, num)
OPCODE( 79, sload,  1, num)
OPCODE( 80, sstore, 1, num)
OPCODE( 81, oload,  1, num)
OPCODE( 82, ostore, 1, num)

/* Io */
OPCODE(  100, print,  0, )

};

#endif