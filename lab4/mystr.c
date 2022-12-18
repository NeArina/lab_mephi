#include "mystr.h"
#include <stdlib.h>

size_t mystrlen(const char *s) {
    size_t res = 0;
    while (*s) {
        ++s; // lllggghhh'\0'
        ++res;
    }
    return res;
}

int my_isspace(char c) {
    return c == ' ' || c == '\t';
}

char *mystrcpy(char *dest, const char *src) {
    // a = b = 2;
    // b = 2;
    while ((*dest++ = *src++));
    return dest;
}
