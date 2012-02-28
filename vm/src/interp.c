#include "interp.h"
#include "error.h"

#include <stdint.h>

void run_bytecode_interp(YogoClass *class, YogoFunction *func) {
    uint16_t *base_ptr = (uint16_t *) func->data;
    uint16_t pc = 0;
    
    for (;;) {        
        switch (*(base_ptr + pc++)) {
            default:
                REPORT_ERROR("Invalid opcode: %d\n", *(base_ptr + pc));
        }
    }    
}