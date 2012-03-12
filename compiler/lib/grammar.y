/*  grammar.y
 *
 *  Copyright (C) 2012 by Claes Jakobsson
 *    
 *  You may distribute under the terms of MIT/X license, as specified in README and LICENSE
 */

%token_prefix TK_

%name yogo_Parse

%token_type {YogoToken}

%include {
#include "parser.h"
}

input ::= stmtlist .

stmtlist ::= stmtlist stmt .
stmtlist ::= stmt .

stmt ::= package .
stmt ::= named_sub .
stmt ::= anon_sub .
stmt ::= var_decl .

/* package <SYMBOL>; */
package ::= PACKAGE PKGNAME SEMI . { fprintf(stderr, "Found package decl\n"); }
package ::= PACKAGE IDENTIFIER SEMI . { fprintf(stderr, "Found package decl\n"); }

/* Sub declarations */
named_sub ::= SUB IDENTIFIER block . { fprintf(stderr, "Found sub: %s\n", "foo"); }
anon_sub ::= SUB block . { fprintf(stderr, "Found anonymous sub\n"); }

block ::= OPEN_CURLY stmtlist CLOSE_CURLY . { fprintf(stderr, "Found block\n"); }

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
