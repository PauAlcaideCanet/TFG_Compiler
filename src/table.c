
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

    action_table[1][T_SEMICOLON] = (Action){SHIFT, 6}; // + → I6
    action_table[1][T_CLOSE_PAR] = (Action){ACCEPT, 0}; // Accept

    action_table[2][T_SEMICOLON] = (Action){SHIFT, 7}; // * → I7

    action_table[4][T_OPEN_PAR] = (Action){SHIFT, 4}; // ( → I4
    action_table[4][T_INT] = (Action){SHIFT, 5}; // NUM → I5
    action_table[4][T_FLOAT] = (Action){SHIFT, 5}; // NUM → I5

    action_table[5][T_CLOSE_PAR] = (Action){REDUCE, 6}; // F → NUM

    action_table[7][T_OPEN_PAR] = (Action){SHIFT, 4}; // ( → I4
    action_table[7][T_INT] = (Action){SHIFT, 5}; // NUM → I5
    action_table[7][T_FLOAT] = (Action){SHIFT, 5}; // NUM → I5

    action_table[8][T_SEMICOLON] = (Action){SHIFT, 6}; // + → I6
    action_table[8][T_CLOSE_PAR] = (Action){SHIFT, 11}; // ) → I11

    action_table[9][T_SEMICOLON] = (Action){SHIFT, 7}; // * → I7

    action_table[10][T_CLOSE_PAR] = (Action){REDUCE, 4}; // T → T * F

    action_table[11][T_CLOSE_PAR] = (Action){REDUCE, 5}; // F → (E)

    

    // GOTO table definition
    goto_table[0][0] = 1; // E → I1
    goto_table[0][1] = 2; // T → I2
    goto_table[0][2] = 3; // F → I3

    goto_table[4][0] = 8; // E → I8
    goto_table[4][1] = 2; // T → I2
    goto_table[4][2] = 3; // F → I3

    goto_table[6][1] = 9; // T → I9
    goto_table[6][2] = 3; // F → I3

    goto_table[7][2] = 10; // F → I10
}
