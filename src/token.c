#include <stdio.h>

#include "token.h"

// Function to print a token
void printToken(Token token) {
    printf("Token: ");
    switch (token.type) {
        case T_SUM:
        case T_MULT:
        case T_OPEN_PAR:
        case T_CLOSE_PAR:
            printf("Operator '%c'\n", token.value.operator);
            break;
        case T_INT:
            printf("Integer Constant %d\n", token.value.integerConstant);
            break;
        case T_FLOAT:
            printf("Float Constant %.2f\n", token.value.floatConstant);
            break;
        case T_EOF:
            printf("EOF\n");
            break;
        default:
            printf("Unknown Token\n");
            break;
    }
}