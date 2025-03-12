#include <stdio.h>

#include "automata.h"
#include "token.h"
#include "stack.h"

int main() {
    
    
    SR_Automata sra;
    initSRAutomata(&sra);

    // Example list of tokens (This should be dynamically generated in a real parser)
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
    while (i < num_tokens && step != -1) {
        step = SRAutomata_step(&sra, tokens[i]);
        freeToken(&tokens[i]);

        i++;
    }

    freeSR_Automata(&sra);
    return 0; 
}