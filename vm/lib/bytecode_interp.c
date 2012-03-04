/*  interp.c
 *
 *  Copyright (C) 2012 by Claes Jakobsson
 *    
 *  You may distribute under the terms of MIT/X license, as specified in README and LICENSE
 */

#include "yogo.h"

#include "bytecode.h"
#include "error.h"
#include "op.h"
#include "op_io.h"

#include <stdint.h>

void run_bytecode_interp(pINTERP YogoPackage *cls, YogoFunction *func) {
    uint16_t    *base_ptr = (uint16_t *) func->data;
    uint16_t    pc = 0;

    for(;;) {        
        uint16_t op = *(base_ptr + pc++);

        switch (op) {
            default:
                YOGO_REPORT_ERROR("Invalid opcode: %d\n", op);
        }
    }

DONE: 
    return;
}

