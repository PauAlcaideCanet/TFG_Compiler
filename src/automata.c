#include <stdio.h>
#include "token.h"
#include "stack.h"
#include "automata.h"

// Get the Rules from its definition
Production_rule* getProductionRules() {   
    // Initialize a temporal variable with the saw info  
    static const char* raw_prod_rules[NUM_RULES][3][MAX_RHSS][2] = PROD_RULES;
    // Allocate all memory for the production rules
    Production_rule* prod_list = malloc(NUM_RULES * sizeof(Production_rule));
    if (!prod_list) {
        printf("Memory allocation failed in production rules");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_RULES; i++) {
        // Fill the Left thand side with its token
        prod_list[i].lhs = createToken(getTokenCategory(raw_prod_rules[i][0][0][0]), raw_prod_rules[i][0][0][1]);
        
        prod_list[i].rhs_size = atoi(raw_prod_rules[i][2][0][0]);  
        // Allocate memory for the Right Hand Side
        prod_list[i].rhs = malloc(prod_list[i].rhs_size * sizeof(Token));
        if (!prod_list[i].rhs) {
            fprintf(stderr, "Memory allocation failed for RHS of rule %d\n", i);
            exit(EXIT_FAILURE);
        }
        // Fill the information of the Right Hand Side
        for (int j = 0; j < prod_list[i].rhs_size; j++) { 
            prod_list[i].rhs[j] = createToken(getTokenCategory(raw_prod_rules[i][1][j][0]), raw_prod_rules[i][1][j][1]);
        }
    }

    return prod_list;
}



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


    //Initialize the rules
    Production_rule* rules = getProductionRules();
    grammar->rules = rules;   
}



// Alphabet initialization
void initAlphabet(const CFG *grammar, Alphabet_symbol* alphabet) { //Funciona
    int index = 0;
    // Fill the terminals into the alphabet
    for (int i = 0; i < grammar->num_terminals; i++) {
        alphabet[index].symbol = grammar->terminals[i];
        alphabet[index].column = index;
        alphabet[index].is_terminal = 1;
        index++;
    }
    // Fill the non-terminals into the alphabet
    for (int i = 0; i < grammar->num_non_terminals; i++) {
        alphabet[index].symbol = grammar->non_terminals[i];
        alphabet[index].column = index;
        alphabet[index].is_terminal = 0;
        index++;
    }
}



// Automata initialization
void initAutomata(const CFG *grammar, Automata* automata) {     //Aixo està bé
    //Init the Alphabet
    automata->num_symbols = grammar->num_terminals + grammar->num_non_terminals;
    automata->alphabet = malloc(automata->num_symbols * sizeof(Alphabet_symbol));
    initAlphabet(grammar, automata->alphabet);

    automata->num_states = NUM_STATES;
    automata->start_state = START_STATE;

    //Init the accepting states
    int accept_states[] = ACCEPT_STATES;  
    int num_accept_states = sizeof(accept_states) / sizeof(accept_states[0]); //Divide by the first element (int) (it can be changed to sizeof(int))
    automata->accepting_states = malloc(num_accept_states * sizeof(int));
    memcpy(automata->accepting_states, accept_states, num_accept_states * sizeof(int));

    
    //Init the Transitions
    static Action transition_data[NUM_STATES][NUM_TERMINALS + NUM_NON_TERMINALS] = TRANSITIONS;
    automata->transition_table = malloc(NUM_STATES * sizeof(Action*));
 
    for (int i = 0; i < NUM_STATES; i++) {
        automata->transition_table[i] = malloc(automata->num_symbols * sizeof(Action));
        for (int j = 0; j < automata->num_symbols; j++) {
            automata->transition_table[i][j] = transition_data[i][j];
        }
    }
}



// Shift-Reduce Automata initialization
void initSRAutomata(SR_Automata* sra) {
    if (sra == NULL) {
        fprintf(stderr, "Error: SR_Automata pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    // Initialize the context-free grammar (CFG)
    initCFG(&sra->grammar);
    // Initialize the stack
    init_stack(&sra->stack);
    push(&sra->stack, START_STATE); 
    // Initialize the automaton using the grammar
    initAutomata(&sra->grammar, &sra->automata);
}



// Returns the associated column for the introduced token 
int getColumn(Token token, Alphabet_symbol *alphabet, int num_symbols) {
    for (int i = 0; i < num_symbols; i++) {
        if(alphabet[i].is_terminal){
            // If it is terminal, return the category
            if (strcmp(getCategoryFromToken(token), alphabet[i].symbol) == 0) {
                return alphabet[i].column;
            }
        }else{
            //If it is non-terminal, returns the lexeme which is the category of non terminal
            if (strcmp(token.lexeme, alphabet[i].symbol) == 0) {
                return alphabet[i].column;
            }
        }    
    }
    return -1; // Error case
}



// Implementation of the shift action
int shift(SR_Automata *sra, Action action){
    push(&sra->stack, action.state);
    return SHIFT;
}



int reduce(SR_Automata *sra, Action action, Token input_token){
    // Fetch the rule to reduce 
    Production_rule rule = sra->grammar.rules[action.state];

    // Pop the RHS symbols from the stack
    for (int i = 0; i < rule.rhs_size; i++) {
        pop(&sra->stack);
    }

    // Get the current state after popping
    int new_state = peek(&sra->stack);
    
    // Find the column index of the LHS in the automaton's alphabet
    int lhs_column = getColumn(rule.lhs, sra->automata.alphabet, sra->automata.num_symbols);
    if (lhs_column == -1) {
        printf("ERROR: Could not find LHS '%s' in the alphabet!\n", rule.lhs.lexeme);
        exit(EXIT_FAILURE);
    }

    // Get the transition state for the LHS
    Action goto_action = sra->automata.transition_table[new_state][lhs_column];
    if (goto_action.type == ERROR) {
        printf("ERROR: No transition found for LHS '%s' in state %d!\n", rule.lhs.lexeme, new_state);
        exit(EXIT_FAILURE);
    }

    // Push the new state after reduction
    push(&sra->stack, goto_action.state);

    // Call it recursively in case there are more reduces to do before the next shift
    int n = SRAutomata_step(sra, input_token); 
    return n;
}



// Executes a step of the Shift-Reduce Automata
int SRAutomata_step(SR_Automata *sra, Token input_token) {
    if (!sra) {
        fprintf(stderr, "Error: SR_Automata pointer is NULL.\n");
        exit(EXIT_FAILURE);
    }

    int state = peek(&sra->stack);
    int column = getColumn(input_token, sra->automata.alphabet, sra->automata.num_symbols);

    if (column == -1) {
        printf("Error: Invalid token '%s'.\n", input_token.lexeme);
        return -1;
    }

    Action action = sra->automata.transition_table[state][column];

    switch (action.type) {
        case SHIFT:
            return shift(sra, action);
            break;
        
        case REDUCE: {
            return reduce(sra, action, input_token);
            break;
        }
        
        case ACCEPT:
            printf("Input accepted.\n");
            return ACCEPT;
            break;
        
        case ERROR:
            printf("There has been an error in the parsing process!\nAt token '%s'", input_token.lexeme);
            return ERROR;
        default:
            printf("Syntax error at token '%s'.\n", input_token.lexeme);
    }
    return ERROR;
}



// Free the memory of the CFG 
void freeCFG(CFG *grammar) {
    if (!grammar) return;

    // Free terminals
    for (int i = 0; i < grammar->num_terminals; i++) {
        free(grammar->terminals[i]);
    }
    free(grammar->terminals);

    // Free non-terminals
    for (int i = 0; i < grammar->num_non_terminals; i++) {
        free(grammar->non_terminals[i]);
    }
    free(grammar->non_terminals);

    // Free grammar rules
    for (int i = 0; i < grammar->num_rules; i++) {
        free(grammar->rules[i].lhs.lexeme); // Free LHS lexeme

        // Free RHS lexemes
        for (int j = 0; j < grammar->rules[i].rhs_size; j++) {
            free(grammar->rules[i].rhs[j].lexeme);
        }

        free(grammar->rules[i].rhs); // Free RHS array
    }
    free(grammar->rules); // Free rules array
}



// Free the memory of the Automata   
void freeAutomata(Automata *automata) {
    if (!automata) return;

    // Free alphabet array
    if (automata->alphabet) {
        free(automata->alphabet);
        automata->alphabet = NULL;
    }

    // Free accepting states
    if (automata->accepting_states) {
        free(automata->accepting_states);
        automata->accepting_states = NULL;
    }

    // Free transition table
    if (automata->transition_table) {
        for (int i = 0; i < automata->num_states; i++) {
            if (automata->transition_table[i]) {
                free(automata->transition_table[i]);
            }
        }
        free(automata->transition_table);
        automata->transition_table = NULL;
    }
}



// Free the memory of the Shift-Reduce Automata 
void freeSR_Automata(SR_Automata *sra) {
    if (!sra) return;

    freeCFG(&sra->grammar);     // Free grammar rules & lexemes
    freeAutomata(&sra->automata); // Free automata structures
}

