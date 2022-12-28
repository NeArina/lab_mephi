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
// dest = "hello0........."
//              _ = ptr
// s = "abc0" 
//      _ = s
char* mystrcat(char* dest, const char* s) {
    char* ptr = dest + mystrlen(dest); // 
    while (*s != '\0') { // пока не признак конца строки
        *ptr++ = *s++; // 
    }
    *ptr = '\0';
    return dest;
}