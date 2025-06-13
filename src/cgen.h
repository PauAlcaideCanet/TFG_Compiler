#include "automata.h"
#include "node.h"

void cgen(Node *node, FILE *out);

void genInt(Node *node, FILE* out);
void genBinaryOp(Node *node, FILE* out);