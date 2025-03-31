/*=========================================================================================

This file contains the structures of Production rules, Context-free Grammar, Alphabet symbol,
Action, Automata and Shift-Reduce Automata. Also contains the enumeration of the different 
actions that can happen in the transition table.

Also contains the declaration of the functions to initialize these structures and to free
their memory.abort

Finally the declaration of function to perform a step of a Shift-Reduce Automaton as well as the shift and 
the reduce functions.

Made by Pau Alcaide Canet
===========================================================================================*/

#ifndef AUTOMATA_H
#define AUTOMATA_H

#include "token.h"
#include "stack.h"
#include "definition.h"

/*========================================================================================*/
/*------------- When enabled (ON) it shows the operations done by the parser -------------*/
#define DEBUGTOKEN ON
/*========================================================================================*/

#define MAX_RHSS 10
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



// Initialization functions
void initCFG(CFG *grammar);
void initAlphabet(const CFG *grammar, Alphabet_symbol* alphabet);
void initAutomata(const CFG *grammar, Automata* automata);
void initSRAutomata(SR_Automata* automata);

// Execution
int SRAutomata_step(SR_Automata *SRAutomata, Token input_token);
int shift(SR_Automata *sra, Action action, Token input_token);
int reduce(SR_Automata *sra, Action action);

// Free memory functions
void freeCFG(CFG *grammar);
void freeAutomata(Automata *automata);
void freeSR_Automata(SR_Automata *SRAutomata);

//Getters
int getColumn(Token token, Alphabet_symbol *alphabet, int num_symbols);
Production_rule* getProductionRules();
#endif
