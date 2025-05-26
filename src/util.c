/*====================================================================================================

This file contains the implementation of some utility functions.

Made by Pau Alcaide Canet

====================================================================================================*/

#include "util.h"

// For a character c it tells if it a whitespace
int is_whitespace(char c) {
    if (c == ' ' || c == '\t' || c == '\n' || c == '\r'){
        return 1;
    }
    return 0;
}