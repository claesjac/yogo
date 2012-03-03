#include "yogo.h"
#include "function.h"

YogoFunction *yogo_create_native_function(YogoInterp *interp, YogoNative callptr, void *data) {
    YogoFunction *func = calloc(1, sizeof(YogoFunction));
    
    func->callptr = callptr;
    func->data = data;
    
    return func;
}