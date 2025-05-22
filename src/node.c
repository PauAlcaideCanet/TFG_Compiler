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
    Node_children *newChild = (Node_children*) malloc(sizeof(Node_children));
    if (newChild != NULL) {
        newChild->child = child;
        newChild->next = parent->children;
        parent->children = newChild;
    }
}

// Free the tree structure
void freeTree(Node *root) {
    if (root == NULL) return;

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

            /* Use it if needed in a future
            case T_IF:
                node->type = IF;
                found = 1;
                break;

            case T_VAR_DECL:
                node->type = VARIABLE_DECL;
                found = 1;
                break;

            case T_FUNC_DECL:
                node->type = FUNCTION_DECL;
                found = 1;
                break;

            // Add other token categories here...
            */

            default:
                // Do nothing if no match
                break;
        }
            
        child = child->next;
    }
}


/*void printTree(Node *root, int white) {
    if (root == NULL) return;

    // Print whitespace
    for (int i = 0; i < white; ++i) {
        printf("  ");
    }

    printf("%d: ", root->id);

    // Print token info
    if (root->token.lexeme != NULL) {
        printf("%s\n", root->token.lexeme);
    } else {
        printf("[category: %d]\n", root->token.category);  
    }

    // Recurse into children
    Node_children *current = root->children;
    while (current != NULL) {
        printTree(current->child, white + 1);
        current = current->next;
    }
} */

void printTree(Node *node, const char *prefix, int isLast) {
    if (!node) return;

    // Line of node printing
    printf("%s%s Node %d: <Symbol: %s, Rule: %d>\n", prefix, isLast ? "+-- " : "|-- ",node->id, node->token.lexeme, node->rule_num);

    // Compute if it is the last child and assign different chars whether is it or not
    char newPrefix[256];
    snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix, isLast ? "    " : "|   ");

    int count = 0;
    Node_children *temp = node->children;
    while (temp) {
        count++;
        temp = temp->next;
    }

    int i = 0;
    Node_children *child = node->children;
    while (child) {
        printTree(child->child, newPrefix, i == count - 1);
        i++;
        child = child->next;
    }
}
