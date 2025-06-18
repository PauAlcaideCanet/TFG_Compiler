/*====================================================================================================

This file contains the function to create nodes of the CST, as well as the function to add childs to a node
necessary to build the tree and a function that transverses the tree, and changes the type variable
of the parents depending on the children.

Also functions to serialize the tree into a file and deserialize it from a file are implemented.

Finally, the functions to print and free the tree structure are implemented.

Made by Pau Alcaide Canet
====================================================================================================*/

#include "node.h"

// Create a new TreeNode from a Token
Node* createTreeNode(Token token, int rule) {
    static int current_id = 0;  // Keeps track of the next ID

    Node* node = (Node*) malloc(sizeof(Node));
    if (node != NULL) {
        node->id = current_id++;  // Assign and increment the ID
        node->rule_num = rule;     
        node->token = token;
        node->children = NULL;
        node->type = NULL_OP;
    }
    return node;
}

// Add a child to a node
void addChild(Node *parent, Node *child) {
    // Allocate memory for the child
    Node_children *newChild = (Node_children*) malloc(sizeof(Node_children));
    if (newChild != NULL) {
        newChild->child = child;
        newChild->next = parent->children;
        parent->children = newChild;
    }
}

// Function to print the tree into a file
void serializeTree(Node *node, FILE *out, int white) {
    if (!node) return;

    // Print indentation
    for (int i = 0; i < white; i++) {
        fprintf(out, "\t");
    }

    // Print node info
    fprintf(out, "(ID: %d; RULE: %d; CATEGORY: %s; LEXEME: \"%s\" [\n", 
        node->id, 
        node->rule_num, 
        getCategoryFromToken(node->token), 
        node->token.lexeme);

    // Collect the children to serialize into an array
    int child_count = 0;
    Node_children *current = node->children;
    while (current) {
        child_count++;
        current = current->next;
    }

    Node *children[child_count];
    current = node->children;
    for (int i = child_count - 1; i >= 0; i--) {
        children[i] = current->child;
        current = current->next;
    }

    // Serialize the children
    for (int i = 0; i < child_count; i++) {
        serializeTree(children[i], out, white + 1);
    }

    // Print closing
    for (int i = 0; i < white; i++) {
        fprintf(out, "\t");
    }
    fprintf(out, "])\n");
}


// Function to gather the information of the tree from the input file and initialize the tree structure
Node* deserializeTree(FILE* in, int recursion){

    char line[MAX_LINE_LENGHT];

    if(recursion == 0){
        rewind(in);
        // Look for the #tree section
        while (fgets(line, sizeof(line), in)) {
            if (strncmp(line, "#tree", 5) == 0) {
                break;
            }
        }
        #if (DEBUG_RF == 1)
            printf("\nReading the information of the tree from the file:\n");
        #endif
    }

    int c;
    // Skip whitespace
    while ((c = fgetc(in)) != EOF && is_whitespace(c));

    // This means that the tree in the file is not started by a parenthesis, which is the indication for a node start
    if (c != '(') {
        printf("There has been an error reading from the input file in the \"#tree\" section\n");
        return NULL; 
    }
    int id, rule;
    char cat_buf[64], lex_buf[256];

    // Parse ID
    fscanf(in, "ID: %d; RULE: %d; CATEGORY: %[^;]; LEXEME: \"%[^\"]\" [", &id, &rule, cat_buf, lex_buf);

    #if (DEBUG_RF == 1)
        printf("ID: %d; RULE: %d; CATEGORY: %s; LEXEME %s\n",id, rule, cat_buf, lex_buf);
    #endif
    
    // Convert category string to enum
    TokenCat cat = getTokenCategory(cat_buf);
    Token token = createToken(cat, lex_buf);

    Node *node = createTreeNode(token, rule);
    // Rectify the id assigned by createTreeNode
    node->id = id;

    // Read children
    while (1) {
        // Skip whitespace
        while ((c = fgetc(in)) != EOF && is_whitespace(c));
        if (c == ']') break;  // End of children
        if (c == ')') break;

        if (c == '(') {
            ungetc(c, in);  // Put back the '(' to be able to call the function recursively
            Node *child = deserializeTree(in, 1);
            if (child) addChild(node, child);
        }
    }

    // Consume the closing ')'
    while ((c = fgetc(in)) != EOF && c != ')');

    return node;
}

// Free the tree structure
void freeTree(Node *root) {
    if (root == NULL) return;

    // Free recursiverly all nodes
    Node_children *current = root->children;
    while (current != NULL) {
        Node_children *next = current->next;
        freeTree(current->child);   
        free(current);              
        current = next;
    }

    freeToken(&root->token);         
    free(root);                     
}

// Marks the parents in function of what does its children have
void markParents(Node *node) {
    /*  This function is used as an intermediate step between the tree creation and 
        the translation into MIPS code. It adds a type to the node in order to know which 
        translation does it have to do. 

        EX. If it finds the token T_SUM, we know that the previous child is the left operand
        and the next child is the right operand, so we mark the parent as a sum node.*/
        
    if (!node) {
        printf("You have tried to mark the parents in an empty tree!");
        exit(1);
    }

    Node_children *child = node->children;
    while (child != NULL) {
        // Recursive call first to mark children
        markParents(child->child);

        // Check child's token category to decide parent's type
        switch (child->child->token.category) {
            case T_SUM:
            case T_MULT:
                node->type = BINARY_OP;
                break;

            case T_INT:
                node->type = INT_OP;
                break;

            case T_OPEN_PAR:
                node->type = PARENTHESIS_OP;
                break;

            default:
                // Do nothing if no match
                break;
        }
            
        child = child->next;
    }
}

// Function to print the Abstract Syntax tree 
void printTree(Node *node, const char *prefix, int isLast) {
    // prefix takes care of the indentation and the starting string to print in each line
    // isLast is a boolean that is true (1) when the node is the last child of its parent

    if (!node) return;

    // newPrefix used to descrive if the next node printing will have "    " or "|   " depending on if it is the last child
    char newPrefix[256];

    // Line of node printing
    if (isLast){
        printf("%s%s Node %d: <Symbol: %s, Category: %s> [Rule: %d; Type: %d]\n", prefix, "+-- ", node->id, node->token.lexeme, getCategoryFromToken(node->token), node->rule_num, node->type);
        snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix,"    ");
    }else{
        printf("%s%s Node %d: <Symbol: %s, Category: %s> [Rule: %d; Type: %d]\n", prefix, "|-- ",  node->id, node->token.lexeme, getCategoryFromToken(node->token), node->rule_num, node->type);
        snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix, "|   ");
    }

    // Count the number of children
    int count = 0;
    Node_children *temp = node->children;
    while (temp) {
        count++;
        temp = temp->next;
    }

    // Call recursively the function to print all nodes
    int i = 0;
    Node_children *child = node->children;
    while (child) {
        printTree(child->child, newPrefix, i == count - 1);
        i++;
        child = child->next;
    }
}
