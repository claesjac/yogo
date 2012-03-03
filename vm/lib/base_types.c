#include "types.h"

#include <stdlib.h>

#define newYogoValue(flags) malloc

static YogoValue *S_new_yogo_value(uint16_t flags) {
    YogoValue *v = malloc(sizeof(YogoValue));
    v->flags = YVt_INTEGER;
    v->refcnt = 1;
    return v;
}

YogoValue *yogo_new_integer(int64_t iv) {
    YogoValue *v = S_new_yogo_value(YVt_INTEGER);
    v->val.ival = iv;
    return v;
}

YogoValue *yogo_new_double(double dv) {
    YogoValue *v = S_new_yogo_value(YVt_DOUBLE);
    v->val.dval = dv;
    return v;
}

YogoValue *yogo_new_reference(YogoValue *dst) {
    YogoValue *v = S_new_yogo_value(YVt_REFERENCE);
    dst->refcnt++;
    v->val.pval = dst;
    return v;    
}