#include "node.h"
#include "automata.h"

// Create an Integer Node
IntNode *createIntegerNode(char* value) {
    IntNode *node = (IntNode *)malloc(sizeof(IntNode));
    node->base.type = NODE_INTEGER;
    node->value = value;
    return node;
}


// Create a Binary Operation Node
BinaryOperationNode *createBinaryOperationNode(char operation, Expression *lhs, Expression *rhs) {
    BinaryOperationNode *node = (BinaryOperationNode *)malloc(sizeof(BinaryOperationNode));
    node->base.type = NODE_BINARY_OPERATION;
    node->operation = operation;
    node->lhs = lhs;
    node->rhs = rhs;
    return node;
}


// Create a Grouping Node
GroupingNode *createGroupingNode(Expression *expression) {
    GroupingNode *node = (GroupingNode *)malloc(sizeof(GroupingNode));
    node->base.type = NODE_GROUPING;
    node->expression = expression;
    return node;
}



// Print AST (Recursive)
void printAST(Expression *node) {
    if (!node) return;

    switch (node->type) {
        case NODE_INTEGER:
            printf("%d", ((IntNode *)node)->value);
            break;

        case NODE_BINARY_OPERATION: {
            BinaryOperationNode *binOp = (BinaryOperationNode *)node;
            printf("(");
            printAST(binOp->lhs);
            printf(" %c ", binOp->operation);
            printAST(binOp->rhs);
            printf(")");
            break;

        }
        case NODE_GROUPING: {
            GroupingNode *group = (GroupingNode *)node;
            printf("(");
            printAST(group->expression);
            printf(")");
            break;

        }
    }
}



void freeAST(Expression *node) {
    if (!node) return;

    switch (node->type) {
        case NODE_BINARY_OPERATION:
            freeAST(((BinaryOperationNode *)node)->lhs);
            freeAST(((BinaryOperationNode *)node)->rhs);
            break;

        case NODE_GROUPING:
            freeAST(((GroupingNode *)node)->expression);
            break;

        case NODE_INTEGER:
            break;

    }

    free(node);
}