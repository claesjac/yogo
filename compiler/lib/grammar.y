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
input ::= stmtlist.

stmtlist ::= stmtlist stmt.
stmtlist ::= stmt.

/* package <SYMBOL>; */
stmt ::= package.
stmt ::= named_sub.

package ::= PACKAGE PKGNAME SEMI. { fprintf(stderr, "Found package decl\n"); }
package ::= PACKAGE IDENTIFIER SEMI. { fprintf(stderr, "Found package decl\n"); }

named_sub ::= SUB IDENTIFIER block. { fprintf(stderr, "Found sub: %s\n", "foo"); }

block ::= OPEN_CURLY CLOSE_CURLY. { fprintf(stderr, "Found block\n"); }



