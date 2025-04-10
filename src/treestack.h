
#ifndef TREESTACK_H
#define TREESTACK_H

#include "node.h"

// AST Stack
typedef struct {
    int top;
    Expression** items;
} Tree_Stack;

void initTreeStack(Tree_Stack* stack);
void push(Tree_Stack* stack, Expression item);
Expression* pop(Tree_Stack* stack);
Expression* peek(Tree_Stack* stack);
void freeTreeStack(Tree_Stack* stack);

#endif // TREESTACK_H