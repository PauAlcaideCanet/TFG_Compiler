#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


void init_stack(Stack* stack) {
    stack->top = -1;
}


void push(Stack* stack, int state) {
    if (stack->top < MAX_STACK - 1) {
        stack->top++;
        stack->states[stack->top] = state;
    } else {
        printf("Error: Stack overflow!\n");
    }
}

int pop(Stack* stack) {
    if (stack->top >= 0) {
        stack->top--;
        return stack->states[stack->top];
    }
    printf("Error: Stack underflow!\n");
    return -1;
}

// Peek function
int peek(Stack* stack) {
    if (stack->top >= 0) {
        return stack->states[stack->top];
    }
    printf("Error: Stack is empty!\n");
    return -1;
}
