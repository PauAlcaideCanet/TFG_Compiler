/*=========================================================================================

This file contains the definition of the code generation functions for Binary Operations
between integers, handling parenthesis and the If statement.

Made by Pau Alcaide Canet
===========================================================================================*/

#include "automata.h"
#include "node.h"

void cgen(Node *node, FILE *out);

void genInt(Node *node, FILE* out);
void genBinaryOp(Node *node, FILE* out);
void genIf(Node *node, FILE *out);