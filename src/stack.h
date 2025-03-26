#ifndef STACK_H
#define STACK_H

#define MAX_STACK 100

// Stack structure
typedef struct {
    int states[MAX_STACK];
    int top;
} Stack;

void init_stack(Stack* stack);
void push(Stack* stack, int state);
int pop(Stack* stack);
int peek(Stack* stack);

#endif 
