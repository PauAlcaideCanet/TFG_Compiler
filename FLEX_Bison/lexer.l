%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Include for strdup
#include "parser.tab.h"  // Include the header with token definitions
%}

/* Flex rules */
%%

[0-9]+               { printf("NUMBER: %s\n", yytext); yylval.word = strdup(yytext); return NUMBER; }

"+"                  { printf("PLUS: %s\n", yytext); return PLUS; }
"*"                  { printf("MULT: %s\n", yytext); return MULT; }

"("                  { printf("OPEN_PAR: %s\n", yytext); return OPEN_PAR; }
")"                  { printf("CLOSE_PAR: %s\n", yytext); return CLOSE_PAR; }

[ \t\n]+             { /* Ignore whitespace */ }

.                    { /* Skip unrecognized strings */ }

%%

int yywrap() {
    return 1;
}
