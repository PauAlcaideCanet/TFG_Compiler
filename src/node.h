/*
    Base és el que els uneix com a expressions, és el NodeType

*/

#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include "token.h"


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
};


Node* createTreeNode(Token token, int rule);
void addChild(Node *parent, Node *child);
void freeTree(Node *root);
void printTree(Node *node, const char *prefix, int isLast);


#endif // NODE_H