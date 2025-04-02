/*
    Base és el que els uneix com a expressions, és el NodeType

*/

#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>

// Enumeration of the Type of nodes in the Abstract syntax tree
typedef enum {
    NODE_INTEGER,
    NODE_BINARY_OPERATION,
    NODE_GROUPING
} NodeType;

// Base expression structure
typedef struct Expression {
    NodeType type;
} Expression;

// Integer Node
typedef struct {
    Expression base;
    int value;
} IntNode;

// Binary Operation Node (sum, mult, ...)
typedef struct {
    Expression base;
    char operation;     // '+' or '*'
    Expression *lhs;
    Expression *rhs;
} BinaryOperationNode;

// Grouping Node (for parenthesis)
typedef struct {
    Expression base;
    Expression *expression;
} GroupingNode;

// AST Root Structure
typedef struct {
    Expression *root;  // Root of the AST
} AST;


IntNode *createIntegerNode(char* value);
BinaryOperationNode *createBinaryOperationNode(char operation, Expression *lhs, Expression *rhs);
GroupingNode *createGroupingNode(Expression *expression);
void initAST(AST *ast);
void printAST(Expression *node);
void freeAST(Expression *node);

#endif // NODE_H