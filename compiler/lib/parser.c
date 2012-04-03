#include "parser.h"
#include "tokenizer.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

void yogoc_parse_file(const char *path) {
    FILE *in;
    void *parser;
    YogocToken *t;
    YogocEmitter *emit;    
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
        
    parser = yogoc_ParseAlloc(malloc);
    emit = yogoc_create_emitter();
    
    while (src[i] != '\0') {
        t = malloc(sizeof(YogocToken));
                
        t->length = yogoc_next_token(&src[i], &token);
        t->type = token;
        t->value = strndup(&src[i], t->length);
        
        i += t->length;
        
        if (token == 0) {
            goto ABORT_PARSING;
        }
        
        if (token == TK_SPACE) {
            continue;
        }

        yogoc_Parse(parser, token, t, emit);
    }

    yogoc_Parse(parser, 0, t, emit);

ABORT_PARSING:
    yogoc_ParseFree(parser, free);
    
}