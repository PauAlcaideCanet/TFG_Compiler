/*====================================================================================================

This file contains the definition of the Nodes of the CST and the linked list used to store its children.

And the definition of the function to create nodes of the CST, as well as the function to add childs to a node
necessary to build the tree and a function that transverses the tree, and changes the type variable
of the parents depending on the children.

Also functions to serialize the tree into a file and deserialize it from a file are defined.

Finally, the functions to print and free the tree structure are defined.

Made by Pau Alcaide Canet
====================================================================================================*/

#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "util.h"


// Define the enum for the type of expression
typedef enum {
    NULL_OP,
    INT_OP,
    BINARY_OP,
    PARENTHESIS_OP,
    IF_OP,
    VARIABLE_DECL_OP,
    FUNCTION_DECL_OP
} ExprType;

typedef struct Node Node;

// Children of the node
typedef struct Node_children {
    Node *child;                    // The node for current child in the list
    struct Node_children *next;     // The pointer to the Node_children struct for the next child node
} Node_children;

// Tree node
struct Node {
    int id;                         // Identification number of the node
    int rule_num;                   // Production rule from where this node is derived
    Token token;
    Node_children *children;        // Linked list containing the children of the node
    ExprType type;                  // This sets the type of node
};


Node* createTreeNode(Token token, int rule);
void addChild(Node *parent, Node *child);

void serializeTree(Node *node, FILE *out, int white);
Node* deserializeTree(FILE* in, int recursion);

void freeTree(Node *root);
void markParents(Node *node);
void printTree(Node *node, const char *prefix, int isLast);


#endif // NODE_H