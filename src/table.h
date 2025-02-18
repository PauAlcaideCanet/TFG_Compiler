#ifndef LR0_TABLE_H
#define LR0_TABLE_H

#include "token.h"

// Possible actions
typedef enum { SHIFT, REDUCE, ACCEPT, ERROR } ActionType;

// Enum the non-terminals
typedef enum {
    S,
    E,
    T,
    F
}NON_TERMINALS;

// Estructura per una acció de la taula LR(0)
typedef struct {
    ActionType type;
    int state;  // Transition state for Shift or production rule for Reduce
} Action;

// Production rule definition
typedef struct {
    int lhs;      // Left hand side
    int rhs_size; // Right hand size size
} Production_rule;


#define NUM_STATES 12       // This is in our case must be changed if the rules are changed
#define NUM_TERMINALS 5     // This is in our case must be changed if the rules are changed
#define NUM_NONTERMINALS 3  // This is in our case must be changed if the rules are changed

Action action_table[NUM_STATES][NUM_TERMINALS];

int goto_table[NUM_STATES][NUM_NONTERMINALS];

// Reule definition
Production_rule rules[] = {
    {S, 1},  // S → E
    {E, 3},  // E → E + T
    {E, 1},  // E → T
    {T, 3},  // T → T * F
    {T, 1},  // T → F
    {F, 3},  // F → (E)
    {F, 1}   // F → NUM
};

// LR (0) table initialization
void init_tables() {}

#endif
