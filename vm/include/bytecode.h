/*
    (c) Claes Jakobsson 2012
    
    released under BSD license
*/

#define OPCODE(code, mnemonic, operands, kind)

OPCODE(  0, null,   0, )
OPCODE(  1, true,   0, )
OPCODE(  2, false,  0, )
OPCODE(  3, iload,  1, )
OPCODE(  4, istore, 1, )
OPCODE(  5, return, 0, )
OPCODE(  6, istrue, 1, addr)
OPCODE(  7, iseq,   1, addr)
OPCODE(  8, shift,  0, )
OPCODE(  9, print,  0, )
