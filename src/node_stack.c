/*=========================================================================================

This file contains the implementation of the stack of nodes needed to build the 
Concrete Syntax Tree.

Made by Pau Alcaide Canet
===========================================================================================*/

#include "node_stack.h"

// Initialization of the stack
void initNodeStack(NodeStack* stack) {
    stack->top = -1;
}

// Push a node onto the stack
int push_node(NodeStack* stack, Node* node) {
    if (stack->top >= MAX_NODE_STACK_SIZE - 1) {
        fprintf(stderr, "Node Stack overflow!\n");
        return 0;
    }
    stack->nodes[++(stack->top)] = node;
    return 1;
}

// Pop a node from the stack
Node* pop_node(NodeStack* stack) {
    if (stack->top < 0) {
        fprintf(stderr, "Node Stack underflow!\n");
        return NULL;
    }
    return stack->nodes[(stack->top)--];
}

// Peek the top node from the stack
Node* peek_node(NodeStack* stack) {
    if (stack->top < 0) {
        return NULL;
    }
    return stack->nodes[stack->top];
}
