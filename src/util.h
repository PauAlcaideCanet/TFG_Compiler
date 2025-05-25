#include <stdio.h>
#include <string.h>

/*========================================================================================*/
/*------------- When enabled (1) it shows information caught when reading from the input file -------------*/
#define DEBUG_RF 1
/*========================================================================================*/


/*========================================================================================*/
/*------------- When enabled (1) it shows the operations done by the parser -------------*/
#define DEBUGTOKEN 1
/*========================================================================================*/

#define MAX_LINE_LENGHT 256

int is_whitespace(char c);