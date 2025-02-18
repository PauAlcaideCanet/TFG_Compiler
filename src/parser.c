#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "table.h"
#include "stack.h"


void parse(Token tokens[], int length) {
    
    Stack s;
    init_stack(&s);
    
    push(&s, 0);  // Initial state
    int i = 0;    // Counter of the tokens
    
    while (1) {     //While true
        int state = peek(&s);
        int symbol = tokens[i].type; // Use TokenType directly as index

        Action action = action_table[state][symbol];

        if (action.type == SHIFT) {
            push(&s, action.state);
            i++; //Go read the next token
        } else if (action.type == REDUCE) {
            Production_rule p = rules[action.state];
            for (int j = 0; j < p.rhs_size; j++){ 
                pop(&s); // Pop RHS symbols
            } 
            int new_state = goto_table[peek(&s)][p.lhs - 2]; // Goto based on LHS
            push(&s, new_state);
        } else if (action.type == ACCEPT) {
            printf("Parsing successful!\n");
            return;
        } else {
            printf("Syntax error!\n");
            return;
        }
    }
}


int main() {
    
    return 0;
}
