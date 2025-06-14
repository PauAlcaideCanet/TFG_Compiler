/*====================================================================================================

This file is separed into 5 sections: PRINTERS, GETTERS, INITIALIZATION, RUN, FREE.
In the printers section, utility functions to print some structs are implemented. 
In the getters section, the functions that extract the information from the input file are found.
In the initialization section, the functions that initialize the structs of CFG, Alphabet, Automata, and SRAutomata are found.
In the run section, the functions needed to run the parser and generate the AST are found.
In the free section, the functions that free the structs are found.


Made by Pau Alcaide Canet
====================================================================================================*/

#include "automata.h"

/*============== PRINTERS SECTION ======================*/
// In this section, utility functions to print some structs are implemented.

// Prints the production rules
void printProductionRule(Production_rule rule) {
    //Print left-hand side
    printToken(rule.lhs);
    printf(" ->");
    // Print Right hand side
    for (int i = 0; i < rule.rhs_size; i++) {
        printf(" ");
        printToken(rule.rhs[i]);
    }
    printf("\n");
}

// Prints de Context-Free Grammar struct
void printCFG(const CFG* cfg) {
    printf("-- CFG Details --\n");

    // Print the terminal symbols
    printf("Terminals:\n");
    for (int i = 0; i < cfg->num_terminals; ++i) {
        printf("%s, ", cfg->terminals[i]);
    }
    printf("\n");

    // Print the non-terminal symbols
    printf("Non-terminals:\n");
    for (int i = 0; i < cfg->num_non_terminals; ++i) {
        printf("%s, ", cfg->non_terminals[i]);
    }
    printf("\n");

    // Print the production rules
    printf("Production Rules:\n");
    for (int i = 0; i < cfg->num_rules; ++i) {
        printProductionRule(cfg->rules[i]); 
    }
}

// Prints a Symbol of the Alphabet
void printSymbol(const Alphabet_symbol* symbol){
    if (symbol == NULL) {
        printf("NULL symbol pointer\n");
        return;
    }

    printf("( Symbol: %s,\t", symbol->symbol);
    printf("Column: %d,\t", symbol->column);
    if (symbol->is_terminal == 1){
        printf("Type: Terminal)\n");
    }else{
        printf("Type: Non-Terminal)\n");
    }
}

// Prints an action
void printAction(const Action* action){
    char* type;
    if (action->type == 0) type = "SHIFT";
    else if (action->type == 1) type = "REDUCE";
    else if (action->type == 2) type = "ACCEPT";
    else type = "ERROR";

    printf("<%s, %d>",type, action->state);
}

// Prints a DFA
void printAutomata(const Automata* automata){
    if (automata == NULL) {
        printf("NULL Automata pointer.\n");
        return;
    }

    printf("-- Automaton Details --\n");
    // Print the number of states
    printf("Number of States: %d\n", automata->num_states);
    // Print the starting state
    printf("Starting State: %d\n", automata->start_state);

    // Print the accepting states
    printf("Accepting States:");
    for (int i = 0; i < automata->num_accept_states; ++i) {
        printf("%d, ", automata->accepting_states[i]);
    }
    printf("\n");

    // Print the alphabet
    printf("Alphabet Symbols:\n");
    for (int i = 0; i < automata->num_symbols; ++i) {
        printSymbol(&automata->alphabet[i]);
    }

    // Print the transition table
    printf("\nTransition Table:\n");
    for (int i = 0; i < automata->num_states; i++) {
        for (int j = 0; j < automata->num_symbols; j++) {
            printAction(&automata->transition_table[i][j]);
        }
        printf("\n");
    }
}

/*============== GETTERS SECTION ======================*/
// In this section the functions that extract the information from the input file are found.

//Get the title number from the input file      EX. title = NUM_TERMINALS
int getNum(FILE *file, const char* title){
    char line[MAX_LINE_LENGHT];
    int lenght = strlen(title);
    rewind(file);  // Make sure we start reading from the beginning of the file

    while (fgets(line, sizeof(line), file)) {
        // Read the first (length of the string passed as parameter)
        if (strncmp(line, title, lenght) == 0) {
            int num;
            // Read the number
            if (sscanf(line + lenght, " %d", &num) == 1) {
                #if (DEBUG_RF == 1)
                    printf("Reading from the file: %s = %d\n", title, num);
                #endif
                
                return num;
            }
        }
    }
    return -1;
}

// Gets a list of strings from the input file   EX. title = TERMINALS
char **getCharList(FILE* file, const char* title, int num_items){
    // I have considered the line as a maximum of 256 characters
    char line[MAX_LINE_LENGHT];
    char **items = malloc(num_items * sizeof(char*));
    int length = strlen(title);
    if (!items) {
        printf("Memory allocation failed when reading %s\n", title);
        return NULL;
    }

    int item_count = 0;
    rewind(file);  // Make sure we start reading from the beginning of the file

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, title, length) == 0) {
            // search for the {
            char *start = strchr(line, '{');
            // search for the }
            char *end = strrchr(line, '}');
            if (!start || !end) {
                printf("No %s have been found\n", title);
                return NULL;
            }

            *end = '\0';
            start++;

            char *item = strtok(start, ",");
            while (item && item_count < num_items) {
                // Eliminate whitespaces
                while (*item == ' ') item++;

                items[item_count] = strdup(item);
                item_count++;

                // Check for the next terminal
                item = strtok(NULL, ",");
            }


            break;
        }
    }

    #if (DEBUG_RF == 1)
        printf("Reading from the file: %s:", title);
        for (int i = 0; i < num_items; i++){
            printf(" %s,", items[i]);
        }
        printf("\n");
    #endif

    return items;
}

// Get the Rules from the input file
Production_rule* getProductionRules(FILE* file, int num_rules) {  

    // Allocate all memory for the production rules
    Production_rule* prod_list = malloc(num_rules * sizeof(Production_rule));
    if (!prod_list) {
        printf("Memory allocation failed in production rules");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGHT];
    rewind(file);

    
    // Find the "PROD_RULES" block
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "PROD_RULES", 10) == 0) break;
    }
    
    int rule_index = 0;
    while (rule_index < num_rules && fgets(line, sizeof(line), file)) {
        // The last line is a }, so if it is found get
        if (line[0] == '}') break; // End of rules
        
        // Strip spaces and newlines
        char *ptr = line;
        while (*ptr == ' ' || *ptr == '\t') ptr++;

        char lhs_cat[32], lhs_lex[32];
        int rhs_count;

        // Parse LHS token
        if (sscanf(ptr, "{{%[^,], %[^}]}", lhs_cat, lhs_lex) != 2) {
            printf("Failed to parse LHS of rule %d\n", rule_index);
            exit(EXIT_FAILURE);
        }

        prod_list[rule_index].lhs = createToken(getTokenCategory(lhs_cat), lhs_lex);
        
        // Find start of RHS tokens
        char *rhs_start = strchr(ptr, '{');
        rhs_start = strchr(rhs_start + 2, '{'); // Skip LHS { }
        rhs_start++;

        // Allocate memory for the right hand side tokens
        Token *rhs = malloc(MAX_RHSS * sizeof(Token));  // temporary size
        int rhs_index = 0;

        // Put the information of the file inside the list of tokens
        char rhs_cat[32], rhs_val[32];
        while ((rhs_start = strchr(rhs_start, '{')) && rhs_index < MAX_RHSS) {
            if (sscanf(rhs_start, "{%[^,], %[^}]}", rhs_cat, rhs_val) != 2) break;

            rhs[rhs_index++] = createToken(getTokenCategory(rhs_cat), rhs_val);

            // Move past the current '}' to search for the next '{'
            
            rhs_start = strchr(rhs_start, '}');
            rhs_start++;  // move past the closing brace
        }

        prod_list[rule_index].rhs_size = rhs_index;
        prod_list[rule_index].rhs = malloc(rhs_index * sizeof(Token));
        if (!prod_list[rule_index].rhs) {
            printf("Failed to allocate RHS for rule %d\n", rule_index);
            exit(EXIT_FAILURE);
        }

        // Put the information of the rhs inside the production rule struct
        memcpy(prod_list[rule_index].rhs, rhs, rhs_index * sizeof(Token));

        free(rhs);

        rule_index++;
    }

    #if (DEBUG_RF == 1)
        printf("Reading from the file: PROD_RULES:\n");
        for (int i = 0; i < num_rules; i++){
            printProductionRule(prod_list[i]);
        }
    #endif

    return prod_list;

}

// Gets a list of integers from the input file with the title   EX. ACCEPT_STATES
int *getIntList(FILE *file, const char* title, int num_items){
    char line[MAX_LINE_LENGHT];
    int length = strlen(title);
    rewind(file);  // Start from the beginning

    char* start;
    int item_count = 0;
    // Allocate memory for the items in the list
    int* int_list = malloc (num_items * sizeof(int));

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, title, length) == 0) {
            // search for the {
            char *start = strchr(line, '{');
            // search for the }
            char *end = strrchr(line, '}');
            if (!start || !end) {
                printf("No %s have been found\n", title);
                return NULL;
            }

            *end = '\0';
            start++;

            char *num = strtok(start, ",");
            while (num && item_count < num_items) {
                // Eliminate whitespaces
                while (*num == ' ') num++;

                int_list[item_count] = atoi(num);
                item_count++;

                // Check for the next number
                num = strtok(NULL, ",");
            }


            break;
        }
    }

    #if (DEBUG_RF == 1)
        printf("Reading from the file: %s:", title);
        for (int i = 0; i < num_items; i++){
            printf(" %d,", int_list[i]);
        }
        printf("\n");
    #endif

    return int_list;
}

// Gets the action for the transition table of the DFA
Action **getTransitions(FILE *file, int num_states, int num_terms){
    char line[MAX_LINE_LENGHT];
    rewind(file);

    // Allocate memory for all the table
    Action **table = malloc(num_states * sizeof(Action *));
    if (!table) {
        fprintf(stderr, "Memory allocation failed for transitions table\n");
        return NULL;
    }

    for (int i = 0; i < num_states; i++) {
        table[i] = malloc(num_terms * sizeof(Action));
        if (!table[i]) {
            fprintf(stderr, "Memory allocation failed for row %d\n", i);
            return NULL;
        }
    }

    // To remember in which state are we
    int state_index = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "TRANSITIONS", 11) == 0) break; // Go to transitions
    }

    while (fgets(line, sizeof(line), file) && state_index < num_states) {
        //Remove whitespaces and tabulations at the beginning
        char *ptr = line;
        while (*ptr && (*ptr == ' ' || *ptr == '\t')) ptr++;

        char action_type[16];
        int number;

        for (int i = 0; i < num_terms; i++) {
            // Put the info in the txt to the variables
            if (sscanf(ptr, "{%[^,], %d}", action_type, &number) != 2) {
                fprintf(stderr, "Error parsing action at state %d, terminal %d\n", state_index, i);
                break;
            }
            
            // Match the string with the ActionType and put it in the table
            if (strcmp(action_type, "SHIFT") == 0) table[state_index][i].type = SHIFT;
            else if (strcmp(action_type, "REDUCE") == 0) table[state_index][i].type = REDUCE;
            else if (strcmp(action_type, "ACCEPT") == 0) table[state_index][i].type = ACCEPT;
            else table[state_index][i].type = ERROR;

            table[state_index][i].state = number;

            // Move ptr past this action
            ptr = strchr(ptr, '}');
            if (ptr) ptr+=2; // skip to next
        }

        state_index++;
    }

    #if (DEBUG_RF == 1)
        printf("Reading from the file: TRANSITIONS:\n");
        for (int i = 0; i < num_states; i++){
            for(int j = 0; j< num_terms; j++){
                printAction(&table[i][j]);
                printf(", ");
            }
            printf("\n");
        }
    #endif

    return table;
}

/*============== INITIALIZATION SECTION ======================*/
// In this section the functions that initialize the structs of CFG, Alphabet, Automata, and SRAutomata are found.

// Initialization of the Context-Free Grammar
void initCFG(CFG *grammar, FILE* file) {         
    // Initialize terminals
    grammar->num_terminals = getNum(file, "NUM_TERMINALS");
    grammar->terminals = getCharList(file, "TERMINALS", grammar->num_terminals);
    
    // Initialize non-terminals
    grammar->num_non_terminals = getNum(file, "NUM_NON_TERMINALS");
    grammar->non_terminals = getCharList(file, "NON_TERMINALS", grammar->num_non_terminals);

    //Initialize the rules
    int num_rules = getNum(file, "NUM_RULES");
    grammar->num_rules = num_rules;

    Production_rule* rules = getProductionRules(file, grammar->num_rules);
    grammar->rules = rules;   

    #if (DEBUGTOKEN == 1)
        printCFG(grammar);
    #endif
    
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
void initAutomata(const CFG *grammar, Automata* automata, FILE* file) {     
    //Init the Alphabet
    automata->num_symbols = grammar->num_terminals + grammar->num_non_terminals;
    automata->alphabet = malloc(automata->num_symbols * sizeof(Alphabet_symbol));
    initAlphabet(grammar, automata->alphabet);

    automata->start_state = getNum(file, "START_STATE");
    automata->num_states = getNum(file, "NUM_STATES");

    //Init the accepting states
    automata->num_accept_states = getNum(file, "NUM_ACCEPT_STATES");
    automata->accepting_states = getIntList(file, "ACCEPT_STATES" ,automata->num_accept_states);  

    //Init the Transitions and put them into the automata struct
    Action** actionTable = getTransitions(file, automata->num_states, automata->num_symbols);
    automata->transition_table = actionTable;

    #if (DEBUGTOKEN == 1)
        printAutomata(automata);
        printf("\n");
    #endif

}

// Shift-Reduce Automata initialization
void initSRAutomata(SR_Automata* sra, FILE* file) {
    if (sra == NULL) {
        printf("Error: SR_Automata pointer is NULL\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the context-free grammar (CFG)
    initCFG(&sra->grammar, file);
    
    // Initialize the automaton using the grammar
    initAutomata(&sra->grammar, &sra->automata, file);

    // Initialize the stack
    init_stack(&sra->stack);
    Token empty_token = (Token){-1, ""};
    push(&sra->stack, sra->automata.start_state, empty_token); 
}

/*============== RUN SECTION ======================*/
// In this section the functions needed to run the parser and generate the AST are found.

// When there is a Reduce step, build the AST 
void buildNodeFromRule(Production_rule rule, NodeStack *nodeStack, StackItem *rhsTokens, int rule_num){
    // Create the supernode for the LHS token
    Node *lhsNode = createTreeNode(rule.lhs, rule_num);

    // Iterate over the RHS tokens
    for (int i = 0; i < rule.rhs_size; ++i) {
        Token token = rhsTokens[i].token;

        //Create the child node
        Node *child = NULL;

        if (token.category == T_NON_TERMINAL) {
            // Pop node from stack (previous subtree)
            child = pop_node(nodeStack);
            if (!child) {
                printf("Error: Stack underflow when handling non-terminal.\n");
                exit(EXIT_FAILURE);
            }
        } else {
            // Create a new node for the terminal token
            child = createTreeNode(token, -1);
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

    #if (DEBUGTOKEN == 1)
        printf("The state %d and token <%s, %s> have been shifted\n", action.state, getCategoryFromToken(input_token), input_token.lexeme);
    #endif

    return SHIFT;
}

// Implementation of the reduce action
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
    buildNodeFromRule(rule, stackNode, items, action.state);

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

    #if (DEBUGTOKEN == 1)
        printf("The reduce of the rule %s -> ", rule.lhs.lexeme);
        for (int i = 0; i < rule.rhs_size; i++){
            printf("%s ", rule.rhs[i].lexeme);
        }
        printf("has been aplied\n");

        printf("The items poped out of the stack are: ");
        for (int i = 0; i< rule.rhs_size; i++){
            printStackItem(&items[i]);
        }
        printf("\n");
    #endif

    return REDUCE;
}

// Implementation of the accept action
int accept(SR_Automata *sra, int state){
    
    // Check if the state is an accepting state
    for (int i = 0; i < sra->automata.num_accept_states; i++){
        if (sra->automata.accepting_states[i] == state){
            printf("Input accepted!\n");
            return ACCEPT;
        }
    }
    // Print error message in case you are trying to accept in a state that is not an accepting state
    printf("You tried to end in a state which is not an accepting state!\n");
    return ERROR;
}

// Implementation of the error action
int error(Token token){
    printf("There has been an error in the parsing process a token '%s'!\n", token.lexeme);
    return ERROR;
}

// Executes a step of the Shift-Reduce Automata
int SRAutomata_step(SR_Automata *sra, Token input_token, NodeStack* stackNode) {
    if (!sra) {
        printf("Error: SR_Automata pointer is NULL\n");
        exit(EXIT_FAILURE);
    }

    // Get the row and columns to search for the action table
    int state = peek(&sra->stack).state;
    int column = getColumn(input_token, sra->automata.alphabet, sra->automata.num_symbols);

    if (column == -1) {
        printf("Error: Invalid token '%s'.\n", input_token.lexeme);
        return -1;
    }

    // Search in the action table
    Action action = sra->automata.transition_table[state][column];

    switch (action.type) {
        case SHIFT:
            return shift(sra, action, input_token);

        case REDUCE: 
            // When using lookahead make sure the reduce is necessary
            return reduce(sra, action, stackNode);
        
        case ACCEPT:
            return accept(sra, state);
        
        case ERROR:
            return error(input_token);

        default:
            printf("Syntax error at token '%s'.\n", input_token.lexeme);
    }
    return ERROR;
}

/*============== FREE SECTION ======================*/
// In this section the functions that free the structs are found. 

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
