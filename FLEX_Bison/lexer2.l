%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Include for strcpy
#include "parser2.tab.h"  // Include the header with token definitions
%}

/* Flex rules */
%%

[0-9]+               { printf("NUMBER: %s\n", yytext); yylval.word = strdup(yytext); return NUMBER; }
"+"                  { printf("PLUS: %s\n", yytext); yylval.word = strdup(yytext); return PLUS; }


[ \t\n]+             { /* Ignore whitespace */ }

.                    { printf("UNRECOGNIZED: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}