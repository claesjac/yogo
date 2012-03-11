#include "tokenizer.h"
#include "grammar.h"
#include <tap.h>

int main(int argc, char *argv[]) {
    YogoTokenizer *tokenizer;
    int t, l;
    
    plan_tests(9);
    
    tokenizer = yogo_tokenize("package Foo::Bar;");
    ok(tokenizer != NULL, "Created tokenizer");
    
    l = yogo_next_token(tokenizer, &t);
    ok(t == TK_PACKAGE, "Token is 'package'");
    ok(l == 7, "Token length is 7");
    
    l = yogo_next_token(tokenizer, &t);
    ok(t == TK_SPACE, "Token is whitespace");
    ok(l == 1, "Token length is 1");

    l = yogo_next_token(tokenizer, &t);
    ok(t == TK_PKGNAME, "Token is 'Foo::Bar'");
    ok(l == 8, "Token length is 8");

    l = yogo_next_token(tokenizer, &t);
    ok(t == TK_SEMI, "Token is ';'");
    ok(l == 1, "Token length is 1");
    
    return exit_status();
    
}