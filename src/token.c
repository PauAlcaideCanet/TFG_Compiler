/*====================================================================================================

This file contains the implementation of the functions to create, free, print and get information
from the tokens.

Made by Pau Alcaide Canet
====================================================================================================*/

#include <stdio.h>

#include "token.h"


void printToken(Token token) {
    char *tokenNames[] = {
        "T_INT", "T_FLOAT", "T_OPEN_PAR", "T_CLOSE_PAR",
        "T_SUM", "T_MULT", "T_EOF", "T_NON_TERMINAL"
    };
    printf("<%s, %s>", tokenNames[token.category], token.lexeme);
}

Token createToken(TokenType type, const char *lexeme) {
    Token token;
    token.category = type;
    token.lexeme = malloc(strlen(lexeme) + 1);

    if (!token.lexeme) {
        fprintf(stderr, "Memory allocation failed for lexeme.\n");
        exit(EXIT_FAILURE);
    }
    
    strcpy(token.lexeme, lexeme);
    return token;
}

void freeToken(Token *token) {
    if (token->lexeme) {
        free(token->lexeme);
        token->lexeme = NULL;
    }
}

TokenType getTokenCategory(const char* type_str) {
    if (strcmp(type_str, "T_INT") == 0) return T_INT;
    if (strcmp(type_str, "T_FLOAT") == 0) return T_FLOAT;
    if (strcmp(type_str, "T_OPEN_PAR") == 0) return T_OPEN_PAR;
    if (strcmp(type_str, "T_CLOSE_PAR") == 0) return T_CLOSE_PAR;
    if (strcmp(type_str, "T_SUM") == 0) return T_SUM;
    if (strcmp(type_str, "T_MULT") == 0) return T_MULT;
    if (strcmp(type_str, "T_EOF") == 0) return T_EOF;
    if (strcmp(type_str, "T_NON_TERMINAL") == 0) return T_NON_TERMINAL;
    
    printf("Unknown token type: %s\n", type_str);
    exit(EXIT_FAILURE);
}

char* getCategoryFromToken(Token token){
    if (token.category == 0) return "T_INT";
    if (token.category == 1) return "T_FLOAT";
    if (token.category == 2) return "T_OPEN_PAR";
    if (token.category == 3) return "T_CLOSE_PAR";
    if (token.category == 4) return "T_SUM";
    if (token.category == 5) return "T_MULT";
    if (token.category == 6) return "T_EOF";
    if (token.category == 7) return "T_NON_TERMINAL";

    printf("Unknown token type %d\n", token.category);
    exit(EXIT_FAILURE);
}
