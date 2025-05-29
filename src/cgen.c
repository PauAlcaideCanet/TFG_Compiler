/*====================================================================================================

This file contains the implementation of the functions to emmit MIPS code given the root node of the tree and the output file.


Made by Pau Alcaide Canet
====================================================================================================*/

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
            
        case IF_OP:
            genTernaryOp(node, out);
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

// Function to perform the sum
void genSum(FILE* out){
     fprintf(out, "add $a0, $t1, $a0\n");      // Perfom the addition
}

// Function to perform the substraction
void genSub(FILE* out){
     fprintf(out, "sub $a0, $t1, $a0\n");       // Perfom the substraction
}

// Function to perform the multiplication
void genMul(FILE* out){
     fprintf(out, "mul $a0, $t1, $a0\n");       // Perfom the multiplication
}

// Function to handle the equal comparison
void genEqual(FILE *out) {
    fprintf(out, "seq $a0, $t1, $a0\n");
}

// Function to handle the equal comparison
void genNotEqual(FILE *out) {
    fprintf(out, "sne $a0, $t1, $a0\n");
}

// Function to handle the less than comparison
void genLessThan(FILE *out) {
    fprintf(out, "slt $a0, $t1, $a0\n");
}

// Function to handle the more than comparison
void genMoreThan(FILE *out) {
    fprintf(out, "slt $a0, $a0, $t1\n");  
}

// Function to handle the case where the first operand is less or equal than the second
void genLessEqual(FILE *out) {
    /* 
    a <= b --> $t1 <= $a0

    This is the same as doing:
    $a0 < $t1 and negate the value
    */
    fprintf(out, "slt $t2, $a0, $t1\n");  // Compute if $a0 < $t1
    fprintf(out, "xori $a0, $t2, 1\n");   // Negate the value to get if $a0 >= $t1
}

// Function to handle the case where the first operand is greater or equal than the second
void genMoreEqual(FILE *out) {
    fprintf(out, "slt $t2, $t1, $a0\n");  // Compute if $t1 < $a0
    fprintf(out, "xori $a0, $t2, 1\n");   // Negate the value to get if $t1 >= $a0
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

        const char *op_lex = op->token.lexeme;

        if(strcmp(op_lex, "+") == 0){
            genSum(out);
        }else if(strcmp(op_lex, "-") == 0){
            genSub(out);
        }else if(strcmp(op_lex, "*") == 0){
            genMul(out);
        }else if(strcmp(op_lex, "==") == 0){
            genEqual(out);                              // In $a0 the result of the comparation
        }else if (strcmp(op_lex, "!=") == 0){
            genNotEqual(out);
        } else if (strcmp(op_lex, "<") == 0){
            genLessThan(out);
        } else if (strcmp(op_lex, ">") == 0){
            genMoreThan(out);
        } else if (strcmp(op_lex, "<=") == 0){
            genLessEqual(out);
        } else if (strcmp(op_lex, ">=") == 0){
            genMoreEqual(out);
        } else {
            fprintf(stderr, "Unknown binary operator: %s\n", op_lex);
        }
}



// This function generates code for a ternary operations
void genTernaryOp(Node* node, FILE* out) {

    static int label_id = 0;
    
    Node* cond_node = node->children->next->next->next->child;              // Node 1: condition
    Node* if_expr = node->children->next->next->child;                      // Node 3: true branch
    Node* else_expr = node->children->child;                                // Node 5: false branch

    char true_label[32], end_label[32];
    sprintf(true_label, "L_true_%d", label_id);
    sprintf(end_label, "L_end_%d", label_id);
    label_id++;


    // Evaluate the condition
    cgen(cond_node, out);  // 1 if true, 0 if false


    // Branch if condition is true
    fprintf(out, "bne $a0, $zero, %s\n", true_label);  // if $a0 != 0 → true

    // False branch
    cgen(else_expr, out);             // Applies the else body
    fprintf(out, "j %s\n", end_label);

    //True branch
    fprintf(out, "%s:\n", true_label);
    cgen(if_expr, out);          // Applies the if body

    // End label 
    fprintf(out, "%s:\n", end_label);
}
    
// =========== SI hi ha temps fer la funció =================