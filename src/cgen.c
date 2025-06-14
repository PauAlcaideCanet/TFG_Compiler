/*=========================================================================================

This file contains the implementation of the code generation functions for Binary Operations
between integers, handling parenthesis and the If statement.

Made by Pau Alcaide Canet
===========================================================================================*/

#include "cgen.h"

// This function generates the code for a standard node
void cgen(Node *node, FILE *out) {

    switch(node->type){
        case BINARY_OP:
            genBinaryOp(node, out);
            break;

        case INT_OP:
            genInt(node, out);
            break;

        case PARENTHESIS_OP:
            // Generate code for the node in the center {   '('    'center_node'   ')'  }
            cgen(node->children->next->child, out);
            break;

        // This means that is a non-terminal followed by a non-terminal
        case NULL_OP:
            cgen(node->children->child, out);
            break;

        default:
            printf("There has been an error!");
            break;
    }

}

// This function generates code for an integer
void genInt(Node *node, FILE *out){
    Node* num = node->children->child;
    // Load the number into the accumulator
    fprintf(out, "li $a0, %s\n", num->token.lexeme);
}

// This function generates the code for a binary operation -------[ Assuming only integers ]-----------
void genBinaryOp(Node *node, FILE *out){
        
        //Get the right and left opperand nodes
        Node *left = node->children->child;
        Node *op = node->children->next->child;
        Node *right = node->children->next->next->child;

        // Get the code for the left side in the accumulator
        cgen(left, out);

        fprintf(out, "sw $a0, 0($sp)\n");
        fprintf(out, "addiu $sp, $sp, -4\n");

        // Get the code for the right side in the accumulator
        cgen(right, out);                

        fprintf(out, "lw $t1, 4($sp)\n");         
        fprintf(out, "addiu $sp, $sp, 4\n");

        if(strcmp(op->token.lexeme, "+") == 0){
            fprintf(out, "add $a0, $t1, $a0\n");      // Perfom the addition
        }else if(strcmp(op->token.lexeme, "-") == 0){
            fprintf(out, "sub $a0, $t1, $a0\n");      // Perfom the substraction
        }else if(strcmp(op->token.lexeme, "*") == 0){
            fprintf(out, "mul $a0, $t1, $a0\n");      // Perfom the multiplication
        }// At the moment the division is not supported.

}

// This function generates code for If statements
void genIf(Node *node, FILE *out) {
    static int labelCount = 0;
    int currentLabel = labelCount++;
    
    Node *cond = node->children->child;
    Node *thenBlock = node->children->next->child;
    Node *elseBlock = node->children->next->next->child;

    // Generate code for condition -> result in $a0
    cgen(cond, out);

    // Compare $a0 with 0, branch to ELSE if false
    fprintf(out, "beq $a0, $zero, else_%d\n", currentLabel);

    // THEN block
    cgen(thenBlock, out);
    
    // Jump over the else block after then
    fprintf(out, "j endif_%d\n", currentLabel);

    // ELSE block
    fprintf(out, "else_%d:\n", currentLabel);
    if (elseBlock) {
        cgen(elseBlock, out);
    }

    // End of if statement
    fprintf(out, "endif_%d:\n", currentLabel);
}

