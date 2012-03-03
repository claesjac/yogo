#include <tap.h>
#include "yogo.h"

int main(void) {
    YogoInterp *interp;
    YogoFunction *func;
    
    plan_tests(3);
    
    interp = yogo_create_interp();    
    
    return exit_status();
}