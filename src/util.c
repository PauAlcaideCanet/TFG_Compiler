#include "util.h"

int is_whitespace(char c) {
    if (c == ' ' || c == '\t' || c == '\n' || c == '\r'){
        return 1;
    }
    return 0;
}