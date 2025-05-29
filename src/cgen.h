/*====================================================================================================

This file contains the definition of the functions to emmit MIPS code given the root node of the tree and the output file.


Made by Pau Alcaide Canet
====================================================================================================*/

#include "automata.h"
#include "node.h"

void cgen(Node *node, FILE *out);

void genInt(Node *node, FILE* out);
void genSum(FILE* out);
void genSub(FILE* out);
void genMul(FILE* out);

void genEqual(FILE* out);
void genNotEqual(FILE* out);
void genLessThan(FILE* out);
void genMoreThan(FILE* out);
void genLessEqual(FILE* out);
void genMoreEqual(FILE* out);


void genBinaryOp(Node *node, FILE* out);
void genTernaryOp(Node *node, FILE* out);