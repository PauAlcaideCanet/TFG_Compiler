/*====================================================================================================

This file contains the implementation of the functions to create, free, print and get information
from the tokens.

Also provides the implementation of the function to deserialize tokens from a file.

Made by Pau Alcaide Canet
====================================================================================================*/

#include <stdio.h>

#include "token.h"
#include "util.h"

// From the category in string format, get the actual category
TokenCat getTokenCategory(const char* cat_str) {
    if (strcmp(cat_str, "T_INT") == 0) return T_INT;
    if (strcmp(cat_str, "T_FLOAT") == 0) return T_FLOAT;

    if (strcmp(cat_str, "T_IDENTIFIER") == 0) return T_IDENTIFIER;
    if (strcmp(cat_str, "T_KEYWORD") == 0) return T_KEYWORD;
    if (strcmp(cat_str, "T_LITERAL") == 0) return T_LITERAL;
    
    // Operands
    if (strcmp(cat_str, "T_SUM") == 0) return T_SUM;
    if (strcmp(cat_str, "T_MULT") == 0) return T_MULT;
    if (strcmp(cat_str, "T_SUB") == 0) return T_SUB;
    if (strcmp(cat_str, "T_EQUAL") == 0) return T_EQUAL;
    if (strcmp(cat_str, "T_NOT_EQUAL") == 0) return T_NOT_EQUAL;
    if (strcmp(cat_str, "T_LESS_THAN") == 0) return T_LESS_THAN;
    if (strcmp(cat_str, "T_MORE_THAN") == 0) return T_MORE_THAN;
    if (strcmp(cat_str, "T_LESS_EQUAL") == 0) return T_LESS_EQUAL;
    if (strcmp(cat_str, "T_MORE_EQUAL") == 0) return T_MORE_EQUAL;

    // Special characters 
    if (strcmp(cat_str, "T_OPEN_PAR") == 0) return T_OPEN_PAR;
    if (strcmp(cat_str, "T_CLOSE_PAR") == 0) return T_CLOSE_PAR;

    if (strcmp(cat_str, "T_NONRECOGNIZED") == 0) return T_NONRECOGNIZED;
    if (strcmp(cat_str, "T_EOF") == 0) return T_EOF;
    if (strcmp(cat_str, "T_NON_TERMINAL") == 0) return T_NON_TERMINAL;
    
    printf("Unknown token type: %s\n", cat_str);
    exit(EXIT_FAILURE);
}

// Get the category of the token in a string format
char* getCategoryFromToken(Token token){
    if (token.category == T_INT) return "T_INT";
    if (token.category == T_FLOAT) return "T_FLOAT";
    if (token.category == T_IDENTIFIER) return "T_IDENTIFIER";
    if (token.category == T_KEYWORD) return "T_KEYWORD";
    if (token.category == T_LITERAL) return "T_LITERAL";  
    
    // Operands
    if (token.category == T_SUM) return "T_SUM";    
    if (token.category == T_MULT) return "T_MULT";
    if (token.category == T_SUB) return "T_SUB";
    if (token.category == T_EQUAL) return "T_EQUAL";
    if (token.category == T_NOT_EQUAL) return "T_NOT_EQUAL";
    if (token.category == T_LESS_THAN) return "T_LESS_THAN";
    if (token.category == T_MORE_THAN) return "T_MORE_THAN";
    if (token.category == T_LESS_EQUAL) return "T_LESS_EQUAL";
    if (token.category == T_MORE_EQUAL) return "T_MORE_EQUAL";
    
    // Special characters
    if (token.category == T_OPEN_PAR) return "T_OPEN_PAR";
    if (token.category == T_CLOSE_PAR) return "T_CLOSE_PAR";
    
    if (token.category == T_NONRECOGNIZED) return "T_NONRECOGNIZED";
    if (token.category == T_EOF) return "T_EOF";
    if (token.category == T_NON_TERMINAL) return "T_NON_TERMINAL";

    printf("Unknown token type %d\n", token.category);
    exit(EXIT_FAILURE);
}

// Function to print a token
void printToken(Token token) {
    printf("<%s, %s>", getCategoryFromToken(token), token.lexeme);
}

// Create the token
Token createToken(TokenCat cat, const char *lexeme) {
    Token token;
    token.category = cat;
    // Allocate memory for the token lexeme
    token.lexeme = malloc(strlen(lexeme) + 1);

    if (!token.lexeme) {
        printf("Memory allocation failed for lexeme.\n");
        exit(EXIT_FAILURE);
    }
    
    strcpy(token.lexeme, lexeme);
    return token;
}

// Function to read from the input file and initialize the list of tokens
Token* deserializeTokens(FILE* file){
    char line[MAX_LINE_LENGHT];
    int count = 0;
    rewind(file);   // Start reading from the start of the file

    // Initialize the list
    Token* tokens = NULL;

    // Go to #tokens
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "#tokens", 7) == 0) break;
    }

    // Read token lines until #parser
    while (fgets(line, sizeof(line), file)) {
        
        char *ptr = line;
        while (*ptr){
            // Strip spaces and newlines
            while (*ptr == ' ' || *ptr == '\t') ptr++;
            ptr++;  // skip '<'

            // Put the information into variables
            char cat_buf[64], lex_buf[64];
            if (sscanf(ptr, " %[^,], %[^>]", cat_buf, lex_buf) != 2) break;

            // Move to end of this token
            char *end = strchr(ptr, '>');
            if (!end) break;
            ptr = end + 1;

            count++;
            // Allocate memory for the new token
            Token* temp = realloc(tokens, count * sizeof(Token));
            tokens = temp;

            TokenCat cat = getTokenCategory(cat_buf);
            tokens[count-1] = createToken(cat, lex_buf);

        }
    }

    #if (DEBUG_RF == 1)
        printf("Reading from the file: TOKENS:\n");
        for(int i = 0; i< count; i++){
            printf(" %d: ", i);
            printToken(tokens[i]);
            printf(" ");
        }
        printf("\n");
    #endif

    return tokens;
}

// Function to free the token struct
void freeToken(Token *token) {
    if (token->lexeme) {
        free(token->lexeme);
        token->lexeme = NULL;
    }
}
