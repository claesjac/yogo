/*  grammar.y
 *
 *  Copyright (C) 2012 by Claes Jakobsson
 *    
 *  You may distribute under the terms of MIT/X license, as specified in README and LICENSE
 */

%token_prefix TK_

%name yogoc_Parse

%token_type {YogocToken *}

%extra_argument {YogocEmitter *emit}

%syntax_error {
  fprintf(stderr, "Syntax error at column %d line %d: %s\n", TOKEN->column, TOKEN->lineno, "TOKEN.str""");
}

%include {
#include "parser.h"
#include "emitter.h"
}

input ::= stmtlist.

stmtlist ::= stmtlist stmt.
stmtlist ::= .

stmt ::= package.
stmt ::= named_sub.
stmt ::= anon_sub.
stmt ::= var_decl.
stmt ::= block.
stmt ::= SEMI.
stmt ::= 
/* package <SYMBOL>; */
package ::= PACKAGE PKGNAME(A) SEMI . { yogoc_set_package(emit, A->value); }
package ::= PACKAGE IDENTIFIER(A) SEMI . { yogoc_set_package(emit, A->value); }

/* Sub declarations */
named_sub ::= SUB IDENTIFIER(A) block . { yogoc_set_sub(emit, A->value); }
anon_sub ::= SUB block . { yogoc_set_sub(emit, NULL); }

block ::= OPEN_CURLY stmtlist CLOSE_CURLY . { fprintf(stderr, "Found block\n"); }

/* Do */
do ::= DO block. { fprintf(stderr, "Found do\n"); }

/* Variable declarations */
var_decl ::= MY type var SEMI . { fprintf(stderr, "Found my decl\n"); }

var ::= SCALAR_VAR .
var ::= HASH_VAR .
var ::= ARRAY_VAR .

/* These are the types that a value can be, we can't define our own types */
type ::= INTEGER.
type ::= DOUBLE.
type ::= STRING.
type ::= HASH.
type ::= ARRAY.
type ::= ANY.
type ::= OBJECT.
type ::= . /* empty */
