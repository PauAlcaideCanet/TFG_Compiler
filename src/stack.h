#ifndef STACK_H
#define STACK_H

#include "token.h"

#define ERROR_ITEM (StackItem){-1, (Token){-1, ERROR}}
#define MAX_STACK 100

typedef struct{
    int state;
    Token token;
} StackItem;

// Stack structure
typedef struct {
    StackItem items[MAX_STACK];
    int top;
} Stack;

void init_stack(Stack* stack);
void push(Stack* stack, int state, Token token);
StackItem pop(Stack* stack);
StackItem peek(Stack* stack);

#endif 
