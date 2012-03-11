#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#include <unistd.h>
#include <stdint.h>

struct YogoTokenizer {
    const char *src, *last_token;
    off_t       offset;
    uint32_t    lineno;
    uint32_t    column;
};

typedef struct YogoTokenizer YogoTokenizer;

YogoTokenizer *yogo_tokenize(const char *);
int yogo_next_token(YogoTokenizer *, int *);
void yogo_free_tokenizer(YogoTokenizer *);

#endif
