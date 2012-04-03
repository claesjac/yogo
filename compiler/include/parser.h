#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdlib.h>
#include <stdint.h>

#include "grammar.h"
#include "emitter.h"

struct YogocToken {
    uint16_t    type;
    uint16_t    length;
    uint16_t    column;
    uint16_t    lineno;
    const char  *value;
};

typedef struct YogocToken YogocToken;

void *yogoc_ParseAlloc(void*(*)(size_t));
void yogoc_ParseFree(void *, void (*)(void *));
void yogoc_Parse(void *, int, YogocToken *, YogocEmitter *);

void yogoc_parse_file(const char *path);

#endif