#ifndef AUTOMATA_H
#define AUTOMATA_H

#include "token.h"
#include "stack.h"


// Production rule definition
typedef struct {
    Token lhs;      // Left hand side
    Token* rhs;     // Right hand side
    int rhs_size;   // Right hand side size
} Production_rule;

//Grammar 
typedef struct{
    char** terminals;
    int num_terminals;
    char** non_terminals;
    int num_non_terminals;
    Production_rule* rules;
    int num_rules; 
}CFG;

//Alphabet entries definition
typedef struct {
    char* symbol;
    int column;
    int is_terminal; // 1 if true | 0 if false
} Alphabet_symbol;

// Possible actions
typedef enum { SHIFT, REDUCE, ACCEPT, ERROR } ActionType;

// Action structure
typedef struct {
    ActionType type;
    int state;  // Transition state for Shift or production rule for Reduce
} Action;


//Automata definition
typedef struct {
    Alphabet_symbol *alphabet;
    int num_symbols;                  
    int num_states;        
    int start_state;     
    int *accepting_states;     
    Action** transition_table;                
} Automata;

typedef struct {
    Automata automata;
    Stack stack;    
    CFG grammar;              
} SR_Automata;


//S'ha de fer una funció que ho processi

#define NUM_GRAMMAR 1

#if (NUM_GRAMMAR == 1)
    //Define Automata 1
    #define NUM_TERMINALS 7
    #define TERMINALS {"T_INT","T_FLOAT","T_OPEN_PAR","T_CLOSE_PAR","T_SUM","T_MULT", "T_EOF"}
    #define NUM_NON_TERMINALS 4
    #define NON_TERMINALS {"S", "E", "T", "F"} 
    #define NUM_RULES 7
    #define PROD_RULES {    {{T_NON_TERMINAL, "S"}, {{T_NON_TERMINAL,"E"}, {T_EOF, ""}}, 2}                             /*-Rule 0-*/, \
                            {{T_NON_TERMINAL, "E"}, {{T_NON_TERMINAL, "E"}, {T_SUM, "+"}, {T_NON_TERMINAL, "T"}}, 3}    /*-Rule 1-*/, \
                            {{T_NON_TERMINAL, "E"}, {{T_NON_TERMINAL, "T"}}, 1}                                         /*-Rule 2-*/, \
                            {{T_NON_TERMINAL, "T"}, {{T_NON_TERMINAL, "T"}, {T_MULT, "*"}, {T_NON_TERMINAL, "F"}}, 3}   /*-Rule 3-*/, \
                            {{T_NON_TERMINAL, "T"}, {{T_NON_TERMINAL, "F"}}, 1}                                         /*-Rule 4-*/, \
                            {{T_NON_TERMINAL, "F"}, {{T_OPEN_PAR, "("}, {T_NON_TERMINAL, "E"}, {T_CLOSE_PAR, ")"}}, 3}  /*-Rule 5-*/, \
                            {{T_NON_TERMINAL, "F"}, {{T_INT, "" }}, 1}                                                   /*-Rule 6-*/, \
    }
    #define NUM_STATES 12
    #define ACCEPT_STATES {1}
    #define START_STATE 0

    //The columns are placed TERMINALS-NON_TERMINALS in the same order than above
    // La part del float no està implementat encara
    #define TRANSITIONS {   {{SHIFT, 5},{SHIFT, 5},{SHIFT, 4},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{SHIFT, 1},{SHIFT, 2},{SHIFT, 3}},        /*-State 0-*/\
                            {{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{SHIFT, 6},{ERROR, -1},{ACCEPT, 0},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1}},   /*-State 1-*/\
                            {{REDUCE, 2},{REDUCE, 2},{REDUCE, 2},{REDUCE, 2},{REDUCE, 2},{SHIFT, 7},{REDUCE, 2},{REDUCE, 2},{REDUCE, 2},{REDUCE, 2},{REDUCE, 2}},   /*-State 2-*/\
                            {{REDUCE, 4},{REDUCE, 4},{REDUCE, 4},{REDUCE, 4},{REDUCE, 4},{REDUCE, 4},{REDUCE, 4},{REDUCE, 4},{REDUCE, 4},{REDUCE, 4},{REDUCE, 4}},  /*-State 3-*/\
                            {{SHIFT, 5},{SHIFT, 5},{SHIFT, 4},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{SHIFT, 8},{SHIFT, 2},{SHIFT, 3}},        /*-State 4-*/\
                            {{REDUCE, 6},{REDUCE, 6},{REDUCE, 6},{REDUCE, 6},{REDUCE, 6},{REDUCE, 6},{REDUCE, 6},{REDUCE, 6},{REDUCE, 6},{REDUCE, 6},{REDUCE, 6}},  /*-State 5-*/\
                            {{SHIFT, 5},{SHIFT, 5},{SHIFT, 4},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{SHIFT, 9},{SHIFT, 3}},       /*-State 6-*/\
                            {{SHIFT, 5},{SHIFT, 5},{SHIFT, 4},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{SHIFT, 11},{ERROR, -1}},     /*-State 7-*/\
                            {{ERROR, -1},{ERROR, -1},{ERROR, -1},{SHIFT, 10},{SHIFT, 6},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1}},   /*-State 8-*/\
                            {{REDUCE, 1},{REDUCE, 1},{REDUCE, 1},{REDUCE, 1},{REDUCE, 1},{SHIFT, 7},{REDUCE, 1},{REDUCE, 1},{REDUCE, 1},{REDUCE, 1},{REDUCE, 1}},   /*-State 9-*/\
                            {{REDUCE, 5},{REDUCE, 5},{REDUCE, 5},{REDUCE, 5},{REDUCE, 5},{REDUCE, 5},{REDUCE, 5},{REDUCE, 5},{REDUCE, 5},{REDUCE, 5},{REDUCE, 5}},  /*-State 10-*/\
                            {{REDUCE, 3},{REDUCE, 3},{REDUCE, 3},{REDUCE, 3},{REDUCE, 3},{REDUCE, 3},{REDUCE, 3},{REDUCE, 3},{REDUCE, 3},{REDUCE, 3},{REDUCE, 3}}   /*-State 11-*/\
}
    
#elif (NUM_GRAMMAR == 2)
    //Define Automata 2
    
#else
    #error "NUM_GRAMMAR is not any automata option!"
#endif

// Initialization functions
void initCFG(CFG *grammar);
void initAlphabet(const CFG *grammar, Alphabet_symbol* alphabet);
void initAutomata(const CFG *grammar, Automata* automata);
void initSRAutomata(SR_Automata* automata);

// Execution
void runSRAutomata(SR_Automata *SRAutomata, Token input_token);

// Free memory functions
void freeCFG(CFG *grammar);
void freeAlphabet(Alphabet_symbol *alphabet);
void freeAutomata(Automata *automata);
void freeSR_Automata(SR_Automata *SRAutomata);

//Getters
int getColumn();

#endif