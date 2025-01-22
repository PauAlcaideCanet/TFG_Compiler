/*
* Here is where the Token structure is defined. 
* The token is defined as a structure of a type and a value. The types can be found in the TokenTypes enumeration.
*
* Made by Pau Alcaide Canet 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>


// Define the Operator type as a struct
typedef struct {
    char* str;   // Operator
    int value;   // Precedence in a complex operation (+,- --> 1 and *,/ --> 2)
} Operator;

// Define the enum for Token types
typedef enum {
    // Keywords
    T_Function,
    T_Let,
    T_Var,
    T_Integer,
    T_Float,
    T_Void,
    T_String,
    T_Bool,
    T_Return,
    T_Print,
    T_Enum,
    T_Case,
    T_If,

    // Expressions
    T_Identifier,
    T_IntegerConstant,
    T_FloatConstant,
    T_BoolConstant,
    T_StringConstant,

    // Operators
    T_Equal,
    T_Operator,

    // Symbols
    T_Arrow,
    T_Colon,
    T_Semicolon,
    T_ParensOpen,
    T_ParensClose,
    T_BraceOpen,
    T_BraceClose,
    T_Comma,
    T_Period
} TokenType;

// Define the Token struct
typedef struct {
    TokenType type;
    union {
        char* identifier;         // For T_Identifier and T_StringConstant
        int integerConstant;      // For T_IntegerConstant
        float floatConstant;      // For T_FloatConstant
        int boolConstant;         // For T_BoolConstant (using int as bool)
        Operator operatorValue;   // For T_Operator
    } value;
} Token;