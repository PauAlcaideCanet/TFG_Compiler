/*====================================================================================================

This file contains the implementation of the basic stack functions (init, push, pop and peek) 
with this stack version.

Made by Pau Alcaide Canet

====================================================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// Stack initializer function
void init_stack(Stack* stack) {
    stack->top = -1;
}

// Function to push an item into the stack
void push(Stack* stack, int state, Token token) {
    if (stack->top < MAX_STACK - 1) {
        stack->top++;
        stack->items[stack->top].state = state;
        stack->items[stack->top].token = token;
    } else {
        printf("Error: Stack overflow!\n");
    }
}

// Function to pop a stack item from the stack
StackItem pop(Stack* stack) {
    StackItem top;
    if (stack->top >= 0) {
        top = stack->items[stack->top];
        stack->top--;
        return top;
    }
    printf("Error: Stack underflow!\n");
    StackItem error_item = { -1, { -1, "ERROR" } };
    return error_item;
}

// Function to peek the first item in the stack
StackItem peek(Stack* stack) {
    if (stack->top >= 0) {
        return stack->items[stack->top];
    }
    printf("Error: Stack is empty!\n");
    StackItem error_item = { -1, { -1, "ERROR" } };
    return error_item;
}

// Function to print a stack item
void printStackItem(const StackItem *item){
    printf("{ Token: ");
    printToken(item->token);
    printf("; State: %d} ", item->state);
}
