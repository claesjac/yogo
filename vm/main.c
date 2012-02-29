/*
    (c) Claes Jakobsson 2012
    
    released under BSD license
*/

#include <stdio.h>

#include "class.h"
#include "error.h"
#include "loader.h"

static const char *clinit = "<clinit>";
    
int main(int argc, char *argv[]) {
    YogoClass *main;
    YogoFunction *func;
    PWord_t jv;
    
    main = load_class(argv[1]);
    REPORT_INFO("Functions: %p\n", main->functions);
    
    JSLF(jv, main->functions, (uint8_t *) clinit);
    if (jv != NULL) {
        REPORT_INFO("Found clinit\n");
    }
    
    func = (YogoFunction *) *jv;
    
    func->callptr(main, func);
    
    return 0;
}