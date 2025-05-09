/*====================================================================================================

This file contains the implementation of the functions to initialize the structures of Production rules, 
Context-free Grammar, Alphabet symbol, Action, Automata and Shift-Reduce Automata and to free
their memory.

Finally the implementation of the function to perform a step of a Shift-Reduce Automaton as well as 
the shift and the reduce functions.

Made by Pau Alcaide Canet
====================================================================================================*/

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
        // Fill the Left hand side with its token
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
void initAlphabet(const CFG *grammar, Alphabet_symbol* alphabet) { 
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
void initAutomata(const CFG *grammar, Automata* automata) {     
    //Init the Alphabet
    automata->num_symbols = grammar->num_terminals + grammar->num_non_terminals;
    automata->alphabet = malloc(automata->num_symbols * sizeof(Alphabet_symbol));
    initAlphabet(grammar, automata->alphabet);

    automata->start_state = START_STATE;
    automata->num_states = NUM_STATES;

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
    
    // Initialize the automaton using the grammar
    initAutomata(&sra->grammar, &sra->automata);

    // Initialize the stack
    init_stack(&sra->stack);
    Token empty_token = (Token){-1, ""};
    push(&sra->stack, sra->automata.start_state, empty_token); 
}

// When there is a Reduce step, build the AST 
void buildNodeFromRule(Production_rule rule, NodeStack *nodeStack, StackItem *rhsTokens){
    
    // Create the supernode for the LHS token
    Node *lhsNode = createTreeNode(rule.lhs);

    // Iterate over the RHS tokens
    for (int i = 0; i < rule.rhs_size; ++i) {
        Token token = rhsTokens[i].token;

        //Create the child node
        Node *child = NULL;

        printf("Hey!, The first element in the rhs is %s\n", rhsTokens[0].token.lexeme);
        if (token.category == T_NON_TERMINAL) {
            // Pop node from stack (previous subtree)
            child = pop_node(nodeStack);
            if (!child) {
                printf("Error: Stack underflow when handling non-terminal.\n");
                exit(EXIT_FAILURE);
            }
        } else {
            printf("I have reached here :)\n");
            // Create a new node for the terminal token
            child = createTreeNode(token);
        }

        addChild(lhsNode, child);
    }

    // Push the newly built subtree (lhsNode) onto the stack
    push_node(nodeStack, lhsNode);

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
int shift(SR_Automata *sra, Action action, Token input_token){
    push(&sra->stack, action.state, input_token);

    #if (DEBUGTOKEN == ON)
        printf("The state %d and token <%s, %s> have been shifted\n", action.state, getCategoryFromToken(input_token), input_token.lexeme);
    #endif

    return SHIFT;
}



int reduce(SR_Automata *sra, Action action, NodeStack* stackNode){
    // Fetch the rule to reduce 
    Production_rule rule = sra->grammar.rules[action.state];

    // Pop the RHS symbols from the stack
    StackItem items[MAX_RHSS];
    for (int i = 0; i < rule.rhs_size; i++) {
        items[i] = pop(&sra->stack);
        if (items[i].token.category != rule.rhs[rule.rhs_size-i-1].category){
            printf("There has been an error in the parsing process:\n");
            printf("The token popped (%s) does not match with the rule one (%s)\n",
                getCategoryFromToken(items[i].token),getCategoryFromToken(rule.rhs[rule.rhs_size-i-1]));
        }
    }

    // Generation of the AST
    buildNodeFromRule(rule, stackNode, items);

    // Get the current state after popping
    int new_state = peek(&sra->stack).state;
    
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
    push(&sra->stack, goto_action.state, rule.lhs);

    #if (DEBUGTOKEN == ON)
        printf("The reduce of the rule %s -> ", rule.lhs.lexeme);
        for (int i = 0; i < rule.rhs_size; i++){
            printf("%s ", rule.rhs[i].lexeme);
        }
        printf("has been aplied\n");
    #endif

    return REDUCE;
}



// Executes a step of the Shift-Reduce Automata
int SRAutomata_step(SR_Automata *sra, Token input_token, NodeStack* stackNode) {
    if (!sra) {
        printf("Error: SR_Automata pointer is NULL\n");
        exit(EXIT_FAILURE);
    }

    int state = peek(&sra->stack).state;
    int column = getColumn(input_token, sra->automata.alphabet, sra->automata.num_symbols);

    if (column == -1) {
        printf("Error: Invalid token '%s'.\n", input_token.lexeme);
        return -1;
    }

    Action action = sra->automata.transition_table[state][column];

    switch (action.type) {
        case SHIFT:
            return shift(sra, action, input_token);

        case REDUCE: 
            return reduce(sra, action, stackNode);
        
        case ACCEPT:
            int num_accept =  sizeof(sra->automata.accepting_states)/sizeof(int);
            for (int i = 0; i < num_accept; i++){
                if (sra->automata.accepting_states[i] == state){
                    printf("Input accepted!\n");
                    return ACCEPT;
                }
            }
            
            printf("You tried to end in a state which is not an accepting state!\n");
            return ERROR;
        
        case ERROR:
            printf("There has been an error in the parsing process a token '%s'!\n", input_token.lexeme);
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

