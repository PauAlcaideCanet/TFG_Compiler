
#include "table.h"

#define NUM_STATES 12       // This is in our case must be changed if the rules are changed
#define NUM_TERMINALS 7     // This is in our case must be changed if the rules are changed
#define NUM_NONTERMINALS 3  // This is in our case must be changed if the rules are changed

Action** init_actionTable(){

    //Allocate memory for the action table
    Action** action_table = malloc(NUM_STATES * sizeof(Action*));
    for (int i = 0; i < NUM_STATES; i++) {
        action_table[i] = malloc(NUM_TERMINALS * sizeof(Action));
    }

    // Initialize all with ERROR value or with the REDUCE if is a reduce state
    for (int i = 0; i < NUM_STATES; i++) {
        for (int j = 0; j < NUM_TERMINALS; j++) {
            switch (i){

                case 2:
                    action_table[i][j] = (Action){REDUCE, 2};
                    break;
                
                case 3:
                    action_table[i][j] = (Action){REDUCE, 4};
                    break;

                case 5:
                    action_table[i][j] = (Action){REDUCE, 6};
                    break;

                case 9:
                    action_table[i][j] = (Action){REDUCE, 1};
                    break;

                case 10:
                    action_table[i][j] = (Action){REDUCE, 5};
                    break;

                case 11:
                    action_table[i][j] = (Action){REDUCE, 3};
                    break;

                default:
                    action_table[i][j].type = ERROR;
                    break;
            }
           
        }
    }

    // Definition of the automaton
    action_table[0][T_OPEN_PAR] = (Action){SHIFT, 4}; // ( → I4
    action_table[0][T_INT] = (Action){SHIFT, 5}; // NUM → I5
    action_table[0][T_FLOAT] = (Action){SHIFT, 5}; // NUM → I5

    action_table[1][T_SUM] = (Action){SHIFT, 6}; // + → I6

    action_table[2][T_MULT] = (Action){SHIFT, 7}; // * → I7

    action_table[4][T_OPEN_PAR] = (Action){SHIFT, 4}; // ( → I4
    action_table[4][T_INT] = (Action){SHIFT, 5}; // NUM → I5
    action_table[4][T_FLOAT] = (Action){SHIFT, 5}; // NUM → I5

    action_table[6][T_OPEN_PAR] = (Action){SHIFT, 4}; // ( → I4
    action_table[6][T_INT] = (Action){SHIFT, 5}; // NUM → I5
    action_table[6][T_FLOAT] = (Action){SHIFT, 5}; // NUM → I5

    action_table[7][T_OPEN_PAR] = (Action){SHIFT, 4}; // ( → I4
    action_table[7][T_INT] = (Action){SHIFT, 5}; // NUM → I5
    action_table[7][T_FLOAT] = (Action){SHIFT, 5}; // NUM → I5

    action_table[8][T_SUM] = (Action){SHIFT, 6}; // + → I6
    action_table[8][T_CLOSE_PAR] = (Action){SHIFT, 10}; // ) → I11

    action_table[9][T_MULT] = (Action){SHIFT, 7}; // * → I7

    action_table[1][T_EOF] = (Action){ACCEPT,0}; // S → e ACCEPT

    return action_table;
}

int** init_gotoTable() {

    //Allocate memory for the goto table
    int** goto_table = malloc(NUM_STATES * sizeof(int*));
    for (int i = 0; i < NUM_STATES; i++) {
        goto_table[i] = malloc(NUM_TERMINALS * sizeof(int));
    }

    for (int i = 0; i < NUM_STATES; i++) {
        for (int j = 0; j < NUM_NONTERMINALS; j++) {
            goto_table[i][j] = -1;
        }
    }

    // GOTO table definition
    goto_table[0][E] = 1; // E → I1
    goto_table[0][T] = 2; // T → I2
    goto_table[0][F] = 3; // F → I3

    goto_table[4][E] = 8; // E → I8
    goto_table[4][T] = 2; // T → I2
    goto_table[4][F] = 3; // F → I3

    goto_table[6][T] = 9; // T → I9
    goto_table[6][F] = 3; // F → I3

    goto_table[7][F] = 11; // F -> I11

    return goto_table;
}

Production_rule* init_prodRules(){

    // Dynamically allocate memory for the production rules
    Production_rule* rules = malloc(7 * sizeof(Production_rule));

    // Reule definition
    rules[0] = (Production_rule){S, 1};  // S → E
    rules[1] = (Production_rule){E, 3};  // E → E + T
    rules[2] = (Production_rule){E, 1};  // E → T
    rules[3] = (Production_rule){T, 3};  // T → T * F
    rules[4] = (Production_rule){T, 1};  // T → F
    rules[5] = (Production_rule){F, 3};  // F → (E)
    rules[6] = (Production_rule){F, 1};  // F → NUM

    return rules;
}
