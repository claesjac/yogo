#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdlib.h>
#include <stdint.h>

#include "grammar.h"

struct YogoToken {
    const char *str;
    uint32_t    length;
    uint32_t    type;
};

typedef struct YogoToken YogoToken;

void *yogo_ParseAlloc(void*(*)(size_t));
void yogo_ParseFree(void *, void (*)(void *));
void yogo_Parse(void *, int, YogoToken);

void yogo_parse_file(const char *path);

#endif