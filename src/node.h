/*====================================================================================================

This file contains the definition of the functions needed to create the Abstract Syntax Tree
Also contains functions to serialize the information of the tree and deserialize it. 

Finally  the functions to print and free the tree are provided with a method that visits the 
tree recursively and marks the parents depending on the attributes of its children.

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
    Node *child;
    struct Node_children *next;
} Node_children;

// Tree node
struct Node {
    int id;
    int rule_num;
    Token token;
    Node_children *children;
    ExprType type; //This sets the type of node
};


Node* createTreeNode(Token token, int rule);
void addChild(Node *parent, Node *child);

void serializeTree(Node *node, FILE *out, int white);
Node* deserializeTree(FILE* in, int recursion);

void freeTree(Node *root);
void markParents(Node *node);
void printTree(Node *node, const char *prefix, int isLast);


#endif // NODE_H