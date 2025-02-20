#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "table.h"
#include "stack.h"


void parse(Token tokens[], int length) {
    
    //Initialize the stack
    Stack s;
    init_stack(&s);

    //Initialize the tables
    Action** action_table = init_actionTable();
    int** goto_table = init_gotoTable();
    Production_rule* rules = init_prodRules();

    
    push(&s, 0);  // Initial state
    int i = 0;    // Counter of the tokens
    
    while (1) {     //While true
        int state = peek(&s);
        int symbol = tokens[i].type; // Use TokenType directly as index


        Action action = action_table[state][symbol];

        printf("Current state: %d, Token: %d\n", state, symbol);
        printToken(tokens[i]);

        if (action.type == SHIFT) {
            push(&s, action.state);
            i++; //Go read the next token
        } else if (action.type == REDUCE) {
            Production_rule p = rules[action.state];
            for (int j = 0; j < p.rhs_size; j++){ 
                pop(&s); // Pop RHS symbols
            } 
            int new_state = goto_table[peek(&s)][p.lhs]; // Goto based on LHS
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
    
    Token tokens[] = {
        {T_INT, .value.integerConstant = 2},   
        {T_SUM, .value.operator = '+'},        
        {T_INT, .value.integerConstant = 3},   
        {T_EOF}                                
    };

    parse(tokens, 4);

    return 0;
}
