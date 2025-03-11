#include <stdio.h>

#include "token.h"


void printToken(Token token) {
    char *tokenNames[] = {
        "T_INT", "T_FLOAT", "T_OPEN_PAR", "T_CLOSE_PAR",
        "T_SUM", "T_MULT", "T_EOF", "T_NON_TERMINAL"
    };
    printf("<%s, %s>\n", tokenNames[token.category], token.lexeme);
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

