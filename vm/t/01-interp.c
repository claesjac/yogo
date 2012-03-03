#include <tap.h>
#include "yogo.h"

int main(void) {
    YogoInterp *interp;
    
    plan_tests(3);
    
    interp = yogo_create_interp();    
    ok(interp != NULL, "Created interpreter ok");
    
    ok(interp->curr_stack_top == NULL, "Stack is empty");
    ok(interp->stack_size == YOGO_DEFAULT_STACK_SIZE, "Stack size is 32");
    
    yogo_push_stack(interp, yogo_new_int(1));
    
    return exit_status();
}