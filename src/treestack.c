#include <stdio.h>
#include <stdlib.h>
#include "treestack.h"

#define TREE_STACK_INITIAL_CAPACITY 16

void initTreeStack(Tree_Stack* stack) {
    stack->top = -1;
    stack->items = malloc(sizeof(Expression*) * TREE_STACK_INITIAL_CAPACITY);
    if (!stack->items) {
        printf("Failed to allocate memory for AST stack\n");
    }
}

// Push a pointer to an Expression node onto the stack
void push(Tree_Stack* stack, Expression* item) {
    stack->top++;
    stack->items[stack->top] = item;
}

// Pop the top Expression node from the stack
Expression* pop(Tree_Stack* stack) {
    if (stack->top == -1) {
        printf("AST stack underflow on pop\n");
        exit(EXIT_FAILURE);
    }
    Expression* item = stack->items[stack->top];
    stack->top--;
    return item;
}

// Peek at the top Expression node without removing it
Expression* peek(Tree_Stack* stack) {
    if (stack->top == -1) {
        printf("AST stack underflow on peek\n");
        exit(EXIT_FAILURE);
    }
    return stack->items[stack->top];
}

void freeTreeStack(Tree_Stack* stack) {

    if (!stack || !stack->items) return;

    free(stack->items);
    stack->items = NULL;
    stack->top = -1;
}
