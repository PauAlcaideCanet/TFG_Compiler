/*====================================================================================================

This file contains the structure of the Token as well as the enumeration of the different categories 
that tokens can have.

Also the declaration of the functions to create, free a token and some utility functions for tokens.

Also provides the declaration of the function to deserialize tokens from a file.

Made by Pau Alcaide Canet
====================================================================================================*/

#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Define the enum for Token category
typedef enum {
    //NUMS (ints, floats)
    T_INT,
    T_FLOAT,

    //For variables
    T_IDENTIFIER,

    // For If, while, functions ...
    T_KEYWORD,

    // For strings
    T_LITERAL,
        
    //Operations like +, *, ==, <=, ...
    T_MULT,
    T_SUM,
    
    T_SUB,
    T_EQUAL,
    T_NOT_EQUAL,
    T_LESS_THAN,
    T_MORE_THAN,
    T_MORE_EQUAL,
    T_LESS_EQUAL,

    //Symbols like ( ) or { }
    T_OPEN_PAR,
    T_CLOSE_PAR,

    // For non recognized words
    T_NONRECOGNIZED,

    //End of file (Assume we only have one single mathematical operation)
    // If we wanted to have more than one we would need something to separate them (New-line or semicolon)
    T_EOF,

    //For non-terminal symbols
    T_NON_TERMINAL

} TokenCat;

// Define the Token struct
typedef struct {
    TokenCat category;
    char *lexeme;
} Token;

void printToken(Token token);
Token createToken(TokenCat cat, const char *lexeme);
TokenCat getTokenCategory(const char* cat_str);
char* getCategoryFromToken(Token token);

Token* deserializeTokens(FILE* file);
void freeToken(Token *token);

#endif