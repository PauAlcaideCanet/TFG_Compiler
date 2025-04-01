#include <stdio.h>

#include "automata.h"
#include "token.h"
#include "stack.h"
#include "node.h"

int main() {
    
    // Create the automata and initializate it
    SR_Automata sra;
    initSRAutomata(&sra);

    //Create the Abstract Syntax Tree
    AST tree;
    initAST(&tree);

    // List of tokens to parse
    Token tokens[] = {
        createToken(T_INT, "5"),
        createToken(T_SUM, "+"),
        createToken(T_OPEN_PAR, "("),
        createToken(T_INT, "3"),
        createToken(T_CLOSE_PAR, ")"),
        createToken(T_EOF, "")
    };

    int num_tokens = sizeof(tokens) / sizeof(tokens[0]);

    // Process each token using the Shift-Reduce Automaton
    int step = 0;
    int i = 0;
    while (i < num_tokens && step != ERROR && step != ACCEPT) {

        step = SRAutomata_step(&sra, tokens[i]);

        if (step == SHIFT){
            freeToken(&tokens[i]);
            i++;
        }
    }

    //Print the Abstract Syntax Tree
    printf("\nThe tree is:\n");
    printAST(tree.root);

    //Free the memory
    freeSR_Automata(&sra);
    freeAST(tree.root);
    
    return 0; 
}