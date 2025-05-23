/*
    Base és el que els uneix com a expressions, és el NodeType

*/

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
Node* deserializeTree(FILE* in);

void freeTree(Node *root);
void printTree(Node *node, const char *prefix, int isLast);


#endif // NODE_H