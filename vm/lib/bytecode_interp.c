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
#include "op_math.h"

#include <stdint.h>

void run_bytecode_interp(YogoInterp *interp, YogoPackage *cls, YogoFunction *func) {
    uint16_t    *base_ptr = (uint16_t *) func->data;
    uint16_t    pc = 0;
    YogoValue   *lv, *rv;
    
    while(pc < func->op_count) {        
        uint16_t op = *(base_ptr + pc++);
        
        switch (op) {
            case OP_iconst_n1 ... OP_iconst_5:
                YOGO_REPORT_INFO("Push %d onto stack\n", op - OP_iconst_0);
            break;
            
            case OP_add:
                yogo_op_add(interp);
            break;
            
            case OP_print:
            break;
            
            default:
                YOGO_REPORT_ERROR("Invalid opcode: %d\n", op);
        }
    }

DONE: 
    return;
}

