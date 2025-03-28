#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


void init_stack(Stack* stack) {
    stack->top = -1;
}


void push(Stack* stack, int state, Token token) {
    if (stack->top < MAX_STACK - 1) {
        stack->top++;
        stack->items[stack->top].state = state;
        stack->items[stack->top].token = token;
    } else {
        printf("Error: Stack overflow!\n");
    }
}

StackItem pop(Stack* stack) {
    if (stack->top >= 0) {
        stack->top--;
        return stack->items[stack->top];
    }
    printf("Error: Stack underflow!\n");
    StackItem error_item = { -1, { -1, "ERROR" } };
    return error_item;
}

// Peek function
StackItem peek(Stack* stack) {
    if (stack->top >= 0) {
        return stack->items[stack->top];
    }
    printf("Error: Stack is empty!\n");
    StackItem error_item = { -1, { -1, "ERROR" } };
    return error_item;
}
