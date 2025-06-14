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

#include <stdio.h>
#include "token.h"
#include "stack.h"
#include "node_stack.h"
#include "node.h"
#include "util.h"

#define MAX_RHSS 10

// Production rule definition
typedef struct {
    Token lhs;              // Left hand side
    Token* rhs;             // Right hand side
    int rhs_size;           // Right hand side size
} Production_rule;

//Grammar 
typedef struct{
    char** terminals;       // List of the terminal symbols
    int num_terminals;      // Used to allocate the memory and manipulate the terminal symbols
    char** non_terminals;   // List of the non-terminal symbols
    int num_non_terminals;  // Used to allocate the memory and manipulate the non-terminal symbols
    Production_rule* rules; // List of the production rules
    int num_rules;          // Used to allocate the memory and manipulate the production rules  
}CFG;

//Alphabet entries definition
typedef struct {
    char* symbol;           
    int column;             // Column that represents the symbol in the action table
    int is_terminal;        // 1 if true | 0 if false
} Alphabet_symbol;

// Possible actions
typedef enum { SHIFT, REDUCE, ACCEPT, ERROR } ActionType;

// Action structure
typedef struct {
    ActionType type;
    int state;              // Transition state for Shift or production rule for Reduce
} Action;

//Automata definition
typedef struct {
    Alphabet_symbol *alphabet;  // Alphabet of the automata
    int num_symbols;            // Number of symbols in the alphabet            
    int num_states;             // Number of states in the Automata [number of rows in the action table]
    int start_state;            
    int num_accept_states;      // Number of accepting states, needed to initialize and manipulate the accepting states
    int *accepting_states;      // List of the states in which the ACCEPT action can happen
    Action** transition_table;  // Matrix in where for a terminal or non-terminal and the current state it returns the action that has to be performed              
} Automata;

// Shift-reduce Automata definition
typedef struct {
    Automata automata;
    Stack stack;    
    CFG grammar;              
} SR_Automata;

//Printers
void printProductionRule(Production_rule rule);
void printCFG(const CFG* cfg);
void printSymbol(const Alphabet_symbol* symbol);
void printAction(const Action* action);
void printAutomata(const Automata* automata);

//Getters
int getNum(FILE* file, const char* title);
char** getCharList(FILE* file, const char* title, int num_items);
Production_rule* getProductionRules(FILE* file, int num_rules);
int* getIntList(FILE* file, const char* title, int num_items);
Action** getTransitions(FILE* file, int num_states, int num_terms);

// Initialization functions
void initCFG(CFG *grammar, FILE* file);
void initAlphabet(const CFG *grammar, Alphabet_symbol* alphabet);
void initAutomata(const CFG *grammar, Automata* automata, FILE* file);
void initSRAutomata(SR_Automata* automata, FILE* file);

//AST Node creator
void buildNodeFromRule(Production_rule rule, NodeStack *nodeStack, StackItem *rhsTokens, int rule_num);

// Execution
int getColumn(Token token, Alphabet_symbol *alphabet, int num_symbols);
int shift(SR_Automata *sra, Action action, Token input_token);
int reduce(SR_Automata *sra, Action action, NodeStack* stackNode);
int accept(SR_Automata *sra, int state);
int error();
int SRAutomata_step(SR_Automata *SRAutomata, Token input_token, NodeStack* stackNode);

// Free memory functions
void freeCFG(CFG *grammar);
void freeAutomata(Automata *automata);
void freeSR_Automata(SR_Automata *SRAutomata);

#endif
