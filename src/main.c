#include <stdio.h>

#include "automata.h"
#include "token.h"
#include "stack.h"

int main(int argc, char *argv[]) {
    
    printf("Hello world");

    Token tokenList[] = {
        {T_INT, "2"},   
        {T_OPEN_PAR, "("},        
        {T_INT, "2"},
        {T_SUM, "+"},
        {T_INT, "2"},
        {T_CLOSE_PAR,")"}, 
        {T_EOF, ""}                                
    };

    // Here we are going to create the parser and run the code

    return 0;
}