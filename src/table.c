
#include <table.h>

void init_tables() {

    // Initialize all with ERROR value
    for (int i = 0; i < NUM_STATES; i++) {
        for (int j = 0; j < NUM_TERMINALS; j++) {
            action_table[i][j].type = ERROR;
        }
        for (int j = 0; j < NUM_NONTERMINALS; j++) {
            goto_table[i][j] = -1;
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

    action_table[8][T_SUM] = (Action){SHIFT, 6}; // + → I6
    action_table[8][T_CLOSE_PAR] = (Action){SHIFT, 11}; // ) → I11

    action_table[9][T_MULT] = (Action){SHIFT, 7}; // * → I7

    // TODO: Falten els REDUCE i ACCEPT

    

    // GOTO table definition
    goto_table[0][E] = 1; // E → I1
    goto_table[0][T] = 2; // T → I2
    goto_table[0][F] = 3; // F → I3

    goto_table[4][E] = 8; // E → I8
    goto_table[4][T] = 2; // T → I2
    goto_table[4][F] = 3; // F → I3

    goto_table[6][T] = 9; // T → I9
    goto_table[6][F] = 7; // F → I7

    goto_table[7][F] = 10; // F → I10
}
