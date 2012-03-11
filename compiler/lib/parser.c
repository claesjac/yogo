#include "parser.h"
#include "tokenizer.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

void yogo_parse_file(const char *path) {
    FILE *in;
    void *parser;
    YogoToken last_token;
    YogoTokenizer *tokenizer;
    int token;
    uint32_t i = 0;
    char *src;
    struct stat finfo;
    
    if (stat(path, &finfo) != 0) {
        fprintf(stderr, "Stat on '%s' failed because of: %s\n", path, strerror(errno));
        exit(1);
    }
    
    if ((in = fopen(path, "r")) == NULL) {
        fprintf(stderr, "Failed to read '%s' becuase of: %s\n", path, strerror(errno));
        exit(1);
    }
    
    src = malloc(finfo.st_size);
    if (fread(src, sizeof(char), finfo.st_size, in) != finfo.st_size) {
        fprintf(stderr, "Failed to read all file at one go");
        exit(1);
    }
    
    tokenizer = yogo_tokenize(src);
    parser = yogo_ParseAlloc(malloc);
    
    while ((last_token.length = yogo_next_token(tokenizer, &token)) != 0) {
        fprintf(stderr, "Read token: %d %s\n", token, strndup(tokenizer->last_token, last_token.length));

        if (token == 0) {
            goto ABORT_PARSING;
        }
        
        yogo_Parse(parser, token, last_token);
    }

    yogo_Parse(parser, 0, last_token);

ABORT_PARSING:
    yogo_ParseFree(parser, free);
    yogo_free_tokenizer(tokenizer);
    
}