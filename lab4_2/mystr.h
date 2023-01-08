#ifndef MYSTR_H
#define MYSTR_H

#include <stddef.h>

size_t mystrlen(const char *s);
int my_isspace(char c);
char *mystrcpy(char *dest, const char *src);
char *mystrcat(char *dest, const char *s);
char *mystrtok(char *str, const char *delim);

#endif
