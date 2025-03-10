#include <stdio.h>

#include "token.h"

// Function to print a token
void printToken(Token token) {
    printf("<%s, %s>\n", token.category, token.lexeme);
}