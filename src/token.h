/*
* Here is where the Token structure is defined. 
* The token is defined as a structure of a type and a value. The types can be found in the TokenTypes enumeration.
*
* Made by Pau Alcaide Canet 
*/

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