#include "op.h"
#include "op_io.h"

#include <stdio.h>

OP(print) {
    fprintf(stderr, "Hello %s\n", "world");
}