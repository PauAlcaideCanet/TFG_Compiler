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
    T_EOF

} TokenType;

// Define the Token struct
typedef struct {
    TokenType type;
    union {
        char operator;              // For T_SUM, T_MULT, T_OPEN_PAR and T_CLOSE_PAR
        int integerConstant;        // For T_INT
        float floatConstant;        // For T_FLOAT
    } value;
} Token;

void printToken(Token token);

#endif