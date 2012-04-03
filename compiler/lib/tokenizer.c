#include "tokenizer.h"
#include "grammar.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

YogocTokenizer *yogoc_tokenize(const char *src) {
    size_t l = strlen(src);
    
    YogocTokenizer *tok = calloc(1, sizeof(YogocTokenizer));
    tok->src = calloc(1, l + 2);
    memcpy((void *) tok->src, src, l);

    return tok;
}

int yogoc_keyword(const char *s, int l) {
    switch (*s) {
        case 'a': {
            if (l == 3 && s[1] == 'n' && s[2] == 'y') {
                return TK_ANY;
            }                        
        }
        break;
        
        case 'd': {
            switch (s[1]) {
                case 'o': {
                    if (l == 2) {
                        return TK_DO;                        
                    }
                }
                break;
                
                case 'b': {
                    if (l == 3 && s[2] == 'l') {
                        return TK_DOUBLE;
                    }
                }
                break;
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

int yogoc_next_token(const char *s, int *t) {
    int i, c;
    
    /* Always start with 1 in length so we don't have to do this in each case */
    i = 1;

    switch (*s) {
        case ' ': case '\t': case '\n': case '\f': case '\r': {
            if (*s == '\n') {
            }

            for (i = 1; isspace(s[i]); i++) {
                if (s[i] == '\n') {
                }
            }

            *t = TK_SPACE;
            return i;
        }
        break;                                
        
        /* TODO: Define what special vars we want */
        case '$':
            for (i = 1; s[i] == '_' || isalnum(s[i]); i++) {}    
            *t = TK_SCALAR_VAR;
            return i;
        break;
        
        case '@':
            for (i = 1; s[i] == '_' || isalnum(s[i]); i++) {}    
            *t = TK_ARRAY_VAR;
            return i;
        break;
        
        case '%':
            for (i = 1; s[i] == '_' || isalnum(s[i]); i++) {}    
            *t = TK_HASH_VAR;
            return i;
        break;
        
        case ';':
            *t = TK_SEMI;
            return 1;
        break;
        
        case '{':
            *t = TK_OPEN_CURLY;
            return 1;
        break;
        
        case '}':
            *t = TK_CLOSE_CURLY;
            return 1;
        break;
        
        case 'A'...'Z':
        case 'a'...'z':
        case '_': {
            for (i = 1; isalnum(s[i]); i++) {}

            if ((*t = yogoc_keyword(s, i)) != 0) {
                return i;
            }

            *t = TK_IDENTIFIER;
            
            REDO: if (s[i] == ':' && s[i + 1] == ':' && isalnum(s[i + 2])) {
                i += 3;
                for (; isalnum(s[i]); i++) {
                }

                *t = TK_PKGNAME;
            
                goto REDO;
            }
                
            return i;
        }
        break;
        
        default:
            fprintf(stderr, "Unknown token: %s\n", s);
            exit(1);
    }

    *t = 0;
    return 0;
}

void yogoc_free_tokenizer(YogocTokenizer *tokenizer) {
    free(tokenizer);
}