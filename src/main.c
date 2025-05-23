#include <stdio.h>

#include "automata.h"
#include "token.h"
#include "stack.h"
#include "node.h"
#include "node_stack.h"

// Putting GEN_TREE to ON makes the program print the tree
#define GEN_TREE ON

int main() {
    
    //Open input file
    FILE *input = fopen("input.txt", "r");  
    if (!input) {
        printf("Failed to open file\n");
    }

    // Create the automata and initializate it
    SR_Automata sra;
    initSRAutomata(&sra, input);

    //Create stack for the creation of the AST
    NodeStack AST;
    initNodeStack(&AST);


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

        step = SRAutomata_step(&sra, tokens[i], &AST);

        if (step == SHIFT){
            freeToken(&tokens[i]);
            i++;
        }
    }

    Node* root = peek_node(&AST);

    #if (GEN_TREE == ON)
        //Print the Abstract Syntax Tree
        printf("\nThe tree is:\n");
        //printTree(root, 0);
        printTree(root, "", 1);
    #endif

    //Open output file
    FILE *out = fopen("out.txt", "w");  
    if (!out) {
        printf("Failed to open file\n");
    }

    serializeTree(root, out, 0);
    fclose(out);
    
    //Free the memory
    freeSR_Automata(&sra);
    freeTree(root);
    
    //Close files
    fclose(input);
    

    return 0; 
}