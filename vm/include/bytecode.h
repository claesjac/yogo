/*
    (c) Claes Jakobsson 2012
    
    released under BSD license
*/

#define OPCODE(code, mnemonic, operands)

OPCODE(0, null, 0)
OPCODE(1, true, 0)
OPCODE(2, false, 0)
OPCODE(3, iload, 1)
OPCODE(4, istore, 1)
OPCODE(5, return, 0)
