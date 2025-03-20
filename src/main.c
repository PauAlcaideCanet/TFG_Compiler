#include <stdio.h>

#include "automata.h"
#include "token.h"
#include "stack.h"

int main() {
    
    // Create the automata and initializate it
    SR_Automata sra;
    initSRAutomata(&sra);

    // List of tokens to parse
    Token tokens[] = {
        createToken(T_OPEN_PAR, "("),
        createToken(T_INT, "5"),
        createToken(T_SUM, "+"),
        createToken(T_INT, "3"),
        createToken(T_CLOSE_PAR, ")"),
        createToken(T_EOF, "")
    };

    int num_tokens = sizeof(tokens) / sizeof(tokens[0]);

    // Process each token using the Shift-Reduce Automaton
    int step = 0;
    int i = 0;
    while (i < num_tokens && step != ERROR) {
        step = SRAutomata_step(&sra, tokens[i]);
        freeToken(&tokens[i]);

        i++;
    }

    //Free the memory
    freeSR_Automata(&sra);
    
    return 0; 
}