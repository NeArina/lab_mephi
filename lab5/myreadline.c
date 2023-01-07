#include "myreadline.h"

#include <stdlib.h>
#include <string.h>

char *getstr(FILE *fp) {
  char *ptr = (char *)calloc(1, sizeof(char));  // выделяем память под указатель
  char buf[81] = {0};  // выделяем под 80 + 1 (\0) символов буфер
  int n, len = 0;
  *ptr = '\0';  // (/)
  do {
    n = fscanf(fp, "%80[^\n]", buf);
    // printf("byf: %s, n = %d\n", buf, n);

    if (n <= 0) {
      fscanf(fp, "%*c");  // считать любое количество символов
    } else {
      len += strlen(buf);  // прибавить к длине длину буфера
      ptr = (char *)realloc(ptr, len + 1);  // перевыделить память
      ptr = strcat(
          ptr, buf);  // соединить с места, куда указывает указатель, буфер (?)
    }
  } while (n > 0);
  return ptr;
}
