/*
    (c) Claes Jakobsson 2012
    
    released under BSD license
*/


#include "yogo.h"

static const char *clinit = "<clinit>";
    
int main(int argc, char *argv[]) {
    YogoInterp *interp = yogo_init();
    
/*    yogo_push_stack(interp, yogo_create_string("Yogo::ClassLoader"));
    yogo_call(interp, "system_loader");
    yogo_push_stack(interp, yogo_create_string(argv[1]));
    yogo_call(interp, "load");*/
    
/*    YogoClass *main;
    YogoFunction *func;
    PWord_t jv;
    
    main = load_class(argv[1]);
    YOGO_REPORT_INFO("Functions: %p\n", main->functions);
    
    JSLF(jv, main->functions, (uint8_t *) clinit);
    if (jv != NULL) {
        YOGO_REPORT_INFO("Found clinit\n");
    }
    
    func = (YogoFunction *) *jv;
    
    func->callptr(NULL, main, func);
    
    return 0;*/
}