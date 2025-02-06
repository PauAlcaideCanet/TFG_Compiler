%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Include for strcpy
#include "parser.tab.h"  // Include the header with token definitions
%}

/* Flex rules */
%%

"int"                { printf("KEYWORD: %s\n", yytext); strcpy(yylval.word, yytext); return KEYWORD; }
"return"             { printf("KEYWORD: %s\n", yytext); strcpy(yylval.word, yytext); return RETURN; }

[a-zA-Z_][a-zA-Z0-9_]*  { printf("IDENTIFIER: %s\n", yytext); strcpy(yylval.word, yytext); return IDENTIFIER; }

[0-9]+               { printf("NUMBER: %s\n", yytext); yylval.num = atoi(yytext); return NUMBER; }

"="                  { printf("ASSIGN: %s\n", yytext); return ASSIGN; }
"+"                  { printf("PLUS: %s\n", yytext); return PLUS; }

"("                  { printf("OPEN_PAREN: %s\n", yytext); return OPEN_PAREN; }
")"                  { printf("CLOSE_PAREN: %s\n", yytext); return CLOSE_PAREN; }
"{"                  { printf("OPEN_BRACE: %s\n", yytext); return OPEN_BRACE; }
"}"                  { printf("CLOSE_BRACE: %s\n", yytext); return CLOSE_BRACE; }
";"                  { printf("SEMICOLON: %s\n", yytext); return SEMICOLON; }

[ \t\n]+             { /* Ignore whitespace */ }

.                    { printf("UNRECOGNIZED: %s\n", yytext); return UNRECOGNIZED; }

%%

int yywrap() {
    return 1;
}
