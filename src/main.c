#include <stdio.h>

#include "automata.h"
#include "token.h"
#include "stack.h"
#include "node.h"
#include "node_stack.h"
#include "cgen.h"
#include "util.h"

#define MAX_NUM_TOKENS 128

int main(int argc, char *argv[]) {

    // Search for the flags in the parameters
    int helpFlag = 0;
    int readTreeFlag = 0;
    int serializeTreeFlag = 0;
    int generateCode = 0;
    for (int i = 0; i< argc; i++){
        if (strcmp(argv[i], "-help") == 0){
            helpFlag = 1;
        }else if (strcmp(argv[i], "-rt") == 0){
            readTreeFlag = 1;
        }else if (strcmp(argv[i], "-t") == 0){
            serializeTreeFlag = 1;
        }else if (strcmp(argv[i], "-g") == 0){
            generateCode = 1;
        }
    }

    // If there are to few arguments print the manpage
    // If the help flag is on print the manpage
    if(argc < 2 || helpFlag) { 
        // Open manpage
        FILE *manpage = fopen("manpage.txt", "r");  
        if (!manpage) {
            printf("Failed to open the Manpage\n");
        }
        int c;
        while ((c = fgetc(manpage)) != EOF) {
            putchar(c);
        }
        return 1;
    }

    //Open input file
    FILE *input = fopen(argv[1], "r");  
    if (!input) {
        printf("Failed to open file\n");
    }
    Node* root = NULL;
    
    //=========== DO THE PARSING PROCESS AND TREE GENERATION ================================

    // If the flag to read the tree from the file is active, read it from the file
    if (readTreeFlag){
        root = deserializeTree(input,0);

    // Do all the parsing process
    }else{
        
        // Create the automata and initializate it
        SR_Automata sra;
        initSRAutomata(&sra, input);

        //Create stack for the creation of the AST
        NodeStack CST;
        initNodeStack(&CST);


        // Get the list of tokens to parser from the token file
        //Open the token file
        FILE *tokenFile = fopen(argv[2], "r");  
        if (!tokenFile) {
            printf("Failed to open file\n");
        }
        Token* tokens = deserializeTokens(tokenFile);

        // Process each token using the Shift-Reduce Automaton
        int step = 0;
        int i = 0;
        while (i < MAX_NUM_TOKENS && step != ERROR && step != ACCEPT) {

            step = SRAutomata_step(&sra, tokens[i], &CST);

            if (step == SHIFT){
                freeToken(&tokens[i]);
                i++;
            }
        }

        root = peek_node(&CST);

        if(serializeTreeFlag){
            //Open output file
            FILE *out = fopen("outTree.txt", "w");  
            if (!out) {
                printf("Failed to open file\n");
            }

            // Put the AST into a file
            fprintf(out, "#tree\n\n");
            serializeTree(root, out, 0);
            fclose(out);
        }
        //Free the memory
        freeSR_Automata(&sra);
    }
    
    #if (PRINT_TREE == 1)
        //Print the Abstract Syntax Tree
        printf("\nThe tree is:\n");
        //printTree(root, 0);
        printTree(root, "", 1);
    #endif

    //========================== CODE GENERATION SECTION ================
    if (generateCode){
        printf("\nGenerating Code ...\n");
        //Open output file
        FILE *out = fopen("code.asm", "w");  
        if (!out) {
            printf("Failed to open file\n");
        }

        // Get the parents its type
        markParents(root);

        #if (PRINT_TREE == 1)
            //Print the Abstract Syntax Tree
            printf("\nThe tree is:\n");
            //printTree(root, 0);
            printTree(root, "", 1);
        #endif

        // Generate code for MIPS
        cgen(root, out);

        fclose(out);
    }
    

    // Free the tree struct
    freeTree(root);

    //Close files
    fclose(input);
    

    return 0; 
}