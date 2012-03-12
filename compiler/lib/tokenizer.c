#include "tokenizer.h"
#include "grammar.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

YogoTokenizer *yogo_tokenize(const char *src) {
    size_t l = strlen(src);
    
    YogoTokenizer *tok = calloc(1, sizeof(YogoTokenizer));
    tok->src = calloc(1, l + 2);
    memcpy((void *) tok->src, src, l);

    return tok;
}

int yogo_keyword(const char *s, int l) {
    switch (*s) {
        case 'a': {
            if (l == 3 && s[1] == 'n' && s[2] == 'y') {
                return TK_ANY;
            }                        
        }
        break;
        
        case 'd': {
            if (l == 3 && s[1] == 'b' && s[2] == 'l') {
                return TK_DOUBLE;            
            }
        }
        break;
        
        case 'i': {
            if (l == 3 && s[1] == 'n' && s[2] == 't') {
                return TK_INTEGER;
            }
        }
        break;
        
        case 'm': {
            if (l == 2 && s[1] == 'y') {
                return TK_MY;
            }
        }
        break;
            
        case 'p': {
            if (l == 7 && strncmp(s, "package", 7) == 0) {
                return TK_PACKAGE;
            }
        }
        break;
        
        case 's': {
            if (l == 3) {
                switch (s[1]) {
                    case 't':
                        if (s[2] == 'r') {
                            return TK_STRING;
                        }
                    break;
                    
                    case 'u':
                        if (s[2] == 'b') {
                            return TK_SUB;                            
                        }
                    break;
                }
            }
            else if (l == 5) {
                if (strncmp(s, "shift", 5) == 0) {
//                    return TK_SHIFT;
                }
            }
        }
        break;
    }
    
    return 0;
}

int yogo_next_token(YogoTokenizer *tok, int *token) {
    int i, c, t;
    const char *s = tok->src + tok->offset;
    tok->last_token = s;
    /* Always start with 1 in length so we don't have to do this in each case */
    i = 1;

    switch (*s) {
        case ' ': case '\t': case '\n': case '\f': case '\r': {
            tok->column++;
            for (i = 1; isspace(s[i]); i++) {                
            }

            t = TK_SPACE;
            break;                                
        }
        
        /* TODO: Define what special vars we want */
        case '$':
            for (i = 1; s[i] == '_' || isalnum(s[i]); i++) {}    
            t = TK_SCALAR_VAR;
        break;
        
        case '@':
            for (i = 1; s[i] == '_' || isalnum(s[i]); i++) {}    
            t = TK_ARRAY_VAR;
        break;
        
        case '%':
            for (i = 1; s[i] == '_' || isalnum(s[i]); i++) {}    
            t = TK_HASH_VAR;
        break;
        
        case ';':
            t = TK_SEMI;
        break;
        
        case '{':
            t = TK_OPEN_CURLY;
        break;
        
        case '}':
            t = TK_CLOSE_CURLY;
        break;
        
        case 'A'...'Z':
        case 'a'...'z':
        case '_': {
            for (i = 1; isalnum(s[i]); i++) {}

            if ((t = yogo_keyword(s, i)) != 0) {
                goto FOUND_TOKEN;
            }

            t = TK_IDENTIFIER;
            
            REDO: if (s[i] == ':' && s[i + 1] == ':' && isalnum(s[i + 2])) {
                i += 3;
                for (; isalnum(s[i]); i++) {
                }

                t = TK_PKGNAME;
            
                goto REDO;
            }
                
        }
        break;
        
        default:
            i = 0;
            t = 0;
    }

FOUND_TOKEN:
    tok->offset += i;
    *token = t;
    
    return i;
}

void yogo_free_tokenizer(YogoTokenizer *tokenizer) {
    free(tokenizer);
}