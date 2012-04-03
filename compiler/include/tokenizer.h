#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#include "parser.h"

#include <unistd.h>
#include <stdint.h>

struct YogocTokenizer {
    const char *src, *last_token;
    off_t       offset;
    uint32_t    lineno;
    uint32_t    column;
};

typedef struct YogocTokenizer YogocTokenizer;

YogocTokenizer *yogoc_tokenize(const char *);
int yogoc_next_token(const char *, int *);
void yogoc_free_tokenizer(YogocTokenizer *);

#endif
