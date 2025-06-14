/*=========================================================================================

This file contains the definition of the stack of nodes needed to build the 
Concrete Syntax Tree.

Made by Pau Alcaide Canet
===========================================================================================*/

#ifndef NODE_S
#define NODE_S

#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "node.h"

#define MAX_NODE_STACK_SIZE 20

typedef struct {
    int top;
    Node* nodes[MAX_NODE_STACK_SIZE];   // List of nodes pending to be part of the CST
} NodeStack;

void initNodeStack(NodeStack* stack);
int push_node(NodeStack* stack, Node* node);
Node* pop_node(NodeStack* stack);
Node* peek_node(NodeStack* stack);

#endif // NODE_S