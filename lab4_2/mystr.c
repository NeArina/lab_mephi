
#include "mystr.h"

#include <stdio.h>
#include <stdlib.h>

size_t mystrlen(const char *s) {
  size_t res = 0;
  while (*s) {
    ++s;  // lllggghhh  '\0'
    ++res;
  }
  return res;
}

int my_isspace(char c) { return c == ' ' || c == '\t'; }

char *mystrcpy(char *dest, const char *src) {
  while ((*dest++ = *src++))
    ;
  return dest;
}

char *mystrcat(char *dest, const char *s) {
  char *ptr = dest + mystrlen(dest);
  while (*s != '\0') {
    *ptr++ = *s++;
  }
  *ptr = '\0';
  return dest;
}

char *mystrchr(const char *string, const char ch) {
  while (*string && *string != ch) {
    ++string;
  }
  return (*string) ? (char *)string : NULL;
}

char *mystrtok(char *str, const char *delim) {
  static char *next;
  if (str) {
    next = str;
    while (*next && mystrchr(delim, *next)) {
      *next++ = 0;
    }  // now next points to the first non-delimiter char (or '\0')
  }
  if (*next == 0) {
    return NULL;
  }
  //    abc\0\0\0\01234\0
  str = next;
  while (*next && !mystrchr(delim, *next)) {
    next++;
  }
  while (*next && mystrchr(delim, *next)) {
    *next++ = 0;
  }
  return str;
}
