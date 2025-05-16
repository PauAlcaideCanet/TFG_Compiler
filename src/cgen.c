#include "cgen.h"

void cgen(Node *node, FILE *out) {
    switch (node->rule_num) {
        // E -> E + T
        case 1: {
            Node *left = node->children->child;
            Node *right = node->children->next->child;

            // Get the result of the left part of the addition into $a0
            cgen(left, out);

            fprintf(out, "sw $a0, 0($sp)\n");
            fprintf(out, "addiu $sp, $sp, -4\n");

            // Get the result of the right part of the addition into $a0
            cgen(right, out);

            fprintf(out, "lw $t1, 4($sp)\n");
            fprintf(out, "addiu $sp, $sp, 4\n");
            fprintf(out, "add $a0, $t1, $a0\n");
            break;
        
        // E -> T
        }case 2: 
        // T -> F
         case 4: {
            Node *next = node->children->child;
            cgen(next, out);
            break;

        // T -> T * F
        }case 3:{
            Node *left = node->children->child;
            Node *right = node->children->next->child;

            // Get the result of the left part of the multiplication into $a0
            cgen(left, out);

            fprintf(out, "sw $a0, 0($sp)\n");
            fprintf(out, "addiu $sp, $sp, -4\n");

            // Get the result of the right part of the multiplication into $a0
            cgen(right, out);

            fprintf(out, "lw $t1, 4($sp)\n");
            fprintf(out, "addiu $sp, $sp, 4\n");
            fprintf(out, "mul $a0, $t1, $a0\n");
            break;

        // F -> ( F )
        }case 5:{
            Node *next = node->children->next->child;
            cgen(next, out);
            break;

        // F -> INT
        }case 6:{
            //Put the integer inside the accumulator
            fprintf(out, "li $a0, %s\n", node->token.lexeme);
            break;

        }default:
            printf("Unknown rule number: %d\n", node->rule_num);
            exit(1);

    }
}
