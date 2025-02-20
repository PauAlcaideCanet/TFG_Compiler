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


// LR (0) table initialization
void init_tables();

Action** init_actionTable();
int** init_gotoTable();
Production_rule* init_prodRules();


#endif
