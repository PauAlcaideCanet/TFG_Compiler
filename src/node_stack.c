/*====================================================================================================

This file contains the implementation of the functions manipulate the stack of nodes.

Made by Pau Alcaide Canet
====================================================================================================*/

#include "node_stack.h"

void initNodeStack(NodeStack* stack) {
    stack->top = -1;
}

int push_node(NodeStack* stack, Node* node) {
    if (stack->top >= MAX_NODE_STACK_SIZE - 1) {
        fprintf(stderr, "Node Stack overflow!\n");
        return 0;
    }
    stack->nodes[++(stack->top)] = node;
    return 1;
}

Node* pop_node(NodeStack* stack) {
    if (stack->top < 0) {
        fprintf(stderr, "Node Stack underflow!\n");
        return NULL;
    }
    return stack->nodes[(stack->top)--];
}

Node* peek_node(NodeStack* stack) {
    if (stack->top < 0) {
        return NULL;
    }
    return stack->nodes[stack->top];
}
