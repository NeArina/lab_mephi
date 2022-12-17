#include "mystrlen.h"
#include <stdlib.h>

size_t mystrlen(const char *s) {
    size_t res = 0;
    while (*s) {
        ++s; // lllggghhh'\0'
        ++res;
    }
    return res;
}
