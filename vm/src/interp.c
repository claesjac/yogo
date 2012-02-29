#include "interp.h"
#include "error.h"
#include "bytecode.h"

#include "op.h"
#include "op_io.h"

#include <stdint.h>

void run_bytecode_interp(YogoClass *class, YogoFunction *func) {
    uint16_t    *base_ptr = (uint16_t *) func->data;
    uint16_t    pc = 0;
    int64_t     ia, ib, ic;
    double      da, db, dc;
    
    for(;;) {        
        uint16_t op = *(base_ptr + pc++);
        switch (op) {
            case OP_shift:
                break;
            
            case OP_print:
                op_print(NULL);
                break;
            
            case OP_iconst_n1 ... OP_iconst_5:
                ia = op - OP_iconst_n1 - 1;
                REPORT_INFO("Pushing %lld onto stack\n", ia);
                break;
            
            case OP_return:
                goto DONE;
                break;
            default:
                REPORT_ERROR("Invalid opcode: %d\n", op);
        }
    }
    
    DONE: REPORT_INFO("Exiting from %s:%s\n", class->name, func->name);
   
}