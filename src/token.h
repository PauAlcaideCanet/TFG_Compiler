/*====================================================================================================

This file contains the structure of the Token as well as the enumeration of the different categories 
that tokens can have.

Also the declaration of the functions to create, free a token and some utility functions for tokens.

Made by Pau Alcaide Canet
====================================================================================================*/

#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Define the enum for Token types
typedef enum {
    //NUMS
    T_INT,
    T_FLOAT,

    //Symbols
    T_OPEN_PAR,
    T_CLOSE_PAR,

    //Operations
    T_SUM,
    T_MULT,

    //End of file (Assume we only have one single mathematical operation)
    // If we wanted to have more than one we would need something to separate them (New-line or semicolon)
    T_EOF,

    //This is temporary
    T_NON_TERMINAL

} TokenType;

// Define the Token struct
typedef struct {
    TokenType category;
    char *lexeme;
} Token;

void printToken(Token token);
Token createToken(TokenType type, const char *lexeme);
TokenType getTokenCategory(const char* type_str);
char* getCategoryFromToken(Token token);
void freeToken(Token *token);

#endif