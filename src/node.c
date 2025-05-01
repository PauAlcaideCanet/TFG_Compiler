#include "node.h"

// Create a new TreeNode from a Token
Node* createTreeNode(Token token) {
    Node* node = (Node*) malloc(sizeof(Node));
    if (node != NULL) {
        node->token = token;
        node->children = NULL;
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

void printTree(Node *root, int white) {
    if (root == NULL) return;

    // Print whitespace
    for (int i = 0; i < white; ++i) {
        printf("  ");
    }

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
}

