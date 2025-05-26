#include "cgen.h"

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
        Node *right = node->children->next->next->child;

        // Get the code for the left side in the accumulator
        cgen(left, out);

        fprintf(out, "sw $a0, 0($sp)\n");
        fprintf(out, "addiu $sp, $sp, -4\n");

        // Get the code for the right side in the accumulator
        cgen(right, out);                

        fprintf(out, "lw $t1, 4($sp)\n");         
        fprintf(out, "addiu $sp, $sp, 4\n");

        fprintf(out, "add $a0, $t1, $a0\n");      // Perfom the addition
}

