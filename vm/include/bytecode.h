/*
    (c) Claes Jakobsson 2012
    
    released under BSD license
*/

#ifndef __BYTECODE_H__
#define __BYTECODE_H__

#define OPCODE(code, mnemonic, operands, kind)

OPCODE(  0, null,   0, )
OPCODE(  1, true,   0, )
OPCODE(  2, false,  0, )
OPCODE(  3, iload,  1, num)
OPCODE(  4, istore, 1, num)
OPCODE(  5, return, 0, )
OPCODE(  6, istrue, 1, addr)
OPCODE(  7, iseq,   1, addr)
OPCODE(  8, shift,  0, )
OPCODE(  9, print,  0, )
OPCODE( 10, iconst_n1, 0, )
OPCODE( 11, iconst_0, 0, )
OPCODE( 12, iconst_1, 0, )
OPCODE( 13, iconst_2, 0, )
OPCODE( 14, iconst_3, 0, )
OPCODE( 15, iconst_4, 0, )
OPCODE( 16, iconst_5, 0, )

#endif