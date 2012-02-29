#ifndef __INTERP_H__
#define __INTERP_H__

#include "class.h"

struct YogoInterpreter {
    int x;
};

typedef struct YogoInterpreter YogoInterpreter;

void run_bytecode_interp(YogoClass *, YogoFunction *);

#endif