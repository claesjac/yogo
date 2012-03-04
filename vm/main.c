/*
    (c) Claes Jakobsson 2012
    
    released under BSD license
*/


#include "yogo.h"
#include "str.h"
#include "call.h"

static const char *clinit = "<clinit>";
    
int main(int argc, char *argv[]) {
    YogoInterp *interp = yogo_create_interp();
    YogoValue *tmp;

    yogo_push_stack(interp, yogo_create_string("Yogo::Loader"));
    yogo_call_str(interp, "system_loader");
    
    tmp = yogo_pop_stack(interp);

    yogo_push_stack(interp, yogo_create_string(argv[1]));
    YOGO_REPORT_INFO("1: %s\n", yogo_get_string(yogo_peek_stack(interp)));
    yogo_push_stack(interp, tmp);
    YOGO_REPORT_INFO("1: %s\n", yogo_get_string(yogo_peek_stack(interp)));
    yogo_call_str(interp, "load");
    
/*    YogoPackage *main;
    YogoFunction *func;
    PWord_t jv;
    
    main = load_package(argv[1]);
    YOGO_REPORT_INFO("Functions: %p\n", main->functions);
    
    JSLF(jv, main->functions, (uint8_t *) clinit);
    if (jv != NULL) {
        YOGO_REPORT_INFO("Found clinit\n");
    }
    
    func = (YogoFunction *) *jv;
    
    func->callptr(NULL, main, func);
    
    return 0;*/
}