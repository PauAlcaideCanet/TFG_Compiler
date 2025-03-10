#include <stdio.h>
#include "token.h"
#include "stack.h"
#include "automata.h"

// Initialization functions
void initCFG(CFG *grammar);
Alphabet_symbol* createAlphabet(const CFG *grammar);
Automata* createAutomata(const CFG *grammar);
SR_Automata* createSRAutomata();

// Execution
void runSRAutomata(SR_Automata *SRAutomata, Token input_token);

// Free memory functions
void freeCFG(CFG *grammar);
void freeAlphabet(Alphabet_symbol *alphabet);
void freeAutomata(Automata *automata);
void freeSR_Automata(SR_Automata *SRAutomata);

//Getters
int getColumn();