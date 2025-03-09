#include "token.h"
#include "parser.h"
#include "table.h"
#include "stack.h"


typedef struct {
    TokenType *alphabet;    
    int num_symbols;                
    int num_states;         
    int start_state;     
    int *accepting_states; 
    int num_accepting;      
    Action** action_table;     
    Stack stack;            
} Automata;


void automata_init(Automata *automata, TokenType *alphabet, int num_symbols, int num_states, 
    int start, int *accepting_states, int num_accepting, Action** action_table, Stack stack);

void automata_run(Automata *automata);