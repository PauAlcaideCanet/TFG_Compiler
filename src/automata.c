#include <stdio.h>
#include "token.h"
#include "stack.h"
#include "automata.h"

// Initialization of the Context-Free Grammar
void initCFG(CFG *grammar) {
    
    // Initialize terminals
    grammar->num_terminals = NUM_TERMINALS;

    char *terminals[] = TERMINALS;
    grammar->terminals = (char**)malloc(NUM_TERMINALS * sizeof(char*));
    for (int i = 0; i < NUM_TERMINALS; ++i) {
        grammar->terminals[i] = strdup(terminals[i]);  
    }
    
    // Initialize non-terminals
    grammar->num_non_terminals = NUM_NON_TERMINALS;

    char *non_terminals[] = NON_TERMINALS;
    grammar->non_terminals = (char**)malloc(NUM_NON_TERMINALS * sizeof(char*));
    for (int i = 0; i < NUM_NON_TERMINALS; ++i) {
        grammar->non_terminals[i] = strdup(non_terminals[i]);
    }

    
    //----REMOVE------
    for (int i = 0; i < NUM_TERMINALS; ++i) {
        printf("Terminal: %s\n",grammar->terminals[i]);   
    }

    for (int i = 0; i < NUM_TERMINALS; ++i) {
        printf("Non Terminal: %s\n",grammar->non_terminals[i]);   
    }
    //----REMOVE------

    //Initialize the rules
    grammar->num_rules = NUM_RULES;

    Production_rule prod_rules[] = PROD_RULES;
    grammar->rules = (Production_rule*)malloc(NUM_RULES * sizeof(Production_rule));
    
    for (int i = 0; i < NUM_RULES; ++i) {
        grammar->rules[i].lhs = prod_rules[i].lhs;  //Put the Left Hand Side

        grammar->rules[i].rhs_size = prod_rules[i].rhs_size;
        grammar->rules[i].rhs = (Token*)malloc(prod_rules[i].rhs_size * sizeof(Token));

        for (int j = 0; j < prod_rules[i].rhs_size; ++j) {
            grammar->rules[i].rhs[j] = prod_rules[i].rhs[j];  // Copy RHS tokens
        }
    }  
    
}

// Alphabet initialization
void initAlphabet(const CFG *grammar, Alphabet_symbol* alphabet) {
    int index = 0;
    for (int i = 0; i < grammar->num_terminals; i++) {
        alphabet[index].symbol = grammar->terminals[i];
        alphabet[index].column = index;
        alphabet[index].is_terminal = 1;
        index++;
    }
    for (int i = 0; i < grammar->num_non_terminals; i++) {
        alphabet[index].symbol = grammar->non_terminals[i];
        alphabet[index].column = index;
        alphabet[index].is_terminal = 0;
        index++;
    }
}

// Automata initialization
void initAutomata(const CFG *grammar, Automata* automata) {
    //Init the Alphabet
    automata->alphabet = malloc(automata->num_symbols * sizeof(Alphabet_symbol));
    initAlphabet(grammar, automata->alphabet);

    automata->num_symbols = grammar->num_terminals + grammar->num_non_terminals;

    automata->num_states = NUM_STATES;
    automata->start_state = START_STATE;

    //Init the accepting states
    int accept_states[] = ACCEPT_STATES;  
    int num_accept_states = sizeof(accept_states) / sizeof(accept_states[0]); //Divide by the first element (int)
    automata->accepting_states = malloc(num_accept_states * sizeof(int));
    memcpy(automata->accepting_states, accept_states, num_accept_states * sizeof(int));

    //Init the Transitions
    Action* transitions[] = TRANSITIONS;
    automata->transition_table = malloc(NUM_STATES * sizeof(Action*));

    for (int i = 0; i < NUM_STATES; i++) {
        automata->transition_table[i] = malloc(automata->num_symbols * sizeof(Action));
        memcpy(automata->transition_table[i], transitions[i], automata->num_symbols * sizeof(Action));
    }

}

// Inicialitza l'autòmat shift-reduce
void initSRAutomata(SR_Automata* sra) {
    
}

// Executa l'autòmat shift-reduce
void runSRAutomata(SR_Automata *sra, Token input_token) {
    
}

// Free the memory of the CFG ---------REVISAR-----------
void freeCFG(CFG *grammar) {
    for (int i = 0; i < grammar->num_terminals; i++) {
        free(grammar->terminals[i]);
    }
    free(grammar->terminals);

    for (int i = 0; i < grammar->num_non_terminals; i++) {
        free(grammar->non_terminals[i]);
    }
    free(grammar->non_terminals);

    for (int i = 0; i < grammar->num_rules; i++) {
        free(grammar->rules[i].rhs);
    }
    free(grammar->rules);
}

// Allibera memòria de l'alfabet 
void freeAlphabet(Alphabet_symbol *alphabet) {
    
}

// Free the memory of the Automata   ---------REVISAR-----------
void freeAutomata(Automata *automata) {
    free(automata->alphabet);
    free(automata->accepting_states);
    
    for (int i = 0; i < automata->num_states; i++) {
        free(automata->transition_table[i]);
    }
    free(automata->transition_table);
}

// Allibera memòria de l'autòmat shift-reduce
void freeSR_Automata(SR_Automata *sra) {
    
}

// Retorna la columna associada a un token en la taula de transicions
int getColumn(Token token, Alphabet_symbol *alphabet, int num_symbols) {
    for (int i = 0; i < num_symbols; i++) {
        if (strcmp(token.lexeme, alphabet[i].symbol) == 0) {
            return alphabet[i].column;
        }
    }
    return -1; // Error case
}