/*====================================================================================================

This file contains the structure of the Stack and the items it keeps.

Also the declaration of the basic stack functions (init, push, pop and peek) with this stack version.

Made by Pau Alcaide Canet
====================================================================================================*/

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
    StackItem items[MAX_STACK];     // List of tokens and the current state when they were added to the stack
    int top;
} Stack;

void init_stack(Stack* stack);
void push(Stack* stack, int state, Token token);
StackItem pop(Stack* stack);
StackItem peek(Stack* stack);
void printStackItem(const StackItem* item);

#endif 
