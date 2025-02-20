
#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <stdio.h>

#include "token.h"


// Parser structure
typedef struct {
    Token *tokens;   
    int index;       // Current index in the token array
    int token_count; // Total number of tokens
} Parser;


Parser *create_parser(Token *tokens) {

    Parser *parser = (Parser *)malloc(sizeof(Parser));
    parser->tokens = tokens;
    parser->index = 0;
    parser->token_count = sizeof(tokens)/sizeof(Token);
    
    return parser;
}


#endif