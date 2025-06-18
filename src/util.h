/*====================================================================================================

This file contains the declaration of some utility functions, and the definition of debuging tokens.
Also some general variable definitions are provided.

Made by Pau Alcaide Canet

====================================================================================================*/

#include <stdio.h>
#include <string.h>

/*========================================================================================*/
/*------------- When enabled (1) it shows information caught when reading from the input file -------------*/
#define DEBUG_RF 0
/*========================================================================================*/


/*========================================================================================*/
/*------------- When enabled (1) it shows the operations done by the parser -------------*/
#define DEBUGTOKEN 0
/*========================================================================================*/

// Putting GEN_TREE to ON(1) makes the program print the tree
#define PRINT_TREE 1

#define MAX_LINE_LENGHT 256

int is_whitespace(char c);