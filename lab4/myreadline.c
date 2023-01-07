#include "myreadline.h"
// #define BUFFER_SIZE 20
// #define FORMAT_STR ("%19[^\n]s") // переделать scanf("%80["\n"], buf);
#include <stdio.h>
#include <stdlib.h>

#include "mystr.h"

// int myreadline_char(char *p_str, char **ppstr) {
//     printf("%s", p_str);

//     char str[80];
//     int j = 0;
//     char c = 0;

//     while (c != '\n' && j < 80 - 1) {
//         int t = scanf("%c", &c);
//         if (t == EOF) {
//             str[j] = 0;
//             *ppstr = (char*)malloc(sizeof(char) * mystrlen(str));
//             mystrcpy(*ppstr, str);
//             return EOF;
//         }

//         if (c != '\n') {
//             str[j++] = c;
//         }
//     }

//     str[j] = 0;
//     *ppstr = (char*)malloc(sizeof(char) * mystrlen(str));
//     mystrcpy(*ppstr, str);
//     return mystrlen(str);
// }
/*
int myreadline(char *p_str, char **ppstr) {
    printf("%s", p_str);

    char buffer[20];
    const int bufSize = 20;

    int size = 20; //////buffer
    int curSize = 0;
    char *str = malloc(20 * sizeof(char));

    if (str == NULL) {
        printf("Error of malloc in readline");
        return EOF;
    }

    str[0] = 0;
    int str_ended = 0;
    int t;
    do {
        // lfkjjhdjghjd25451248________________________
        t = scanf("%19[^\n]", buffer);
        if (t == EOF) {
            *ppstr = str;
            return EOF;
        }
        //printf("buffer = \"%s\"", buffer);
        str_ended = buffer[0] == 0;
        mystrcpy(str + curSize, buffer);
        buffer[0] = 0;
        curSize = mystrlen(str);

        if (curSize + 20 >= size) {
            size += 20;
            str = realloc(str, sizeof(char) * size);
        }

    } while (!str_ended);

    *ppstr = str;
    char c;
    scanf("%c", &c);
    //printf("%c = %d", c, (int)c);
    return curSize;
}
*/

char *getstr(char *p_str) {
  char *ptr = (char *)calloc(1, sizeof(char));  // выделяем память под указатель
  char buf[81] = {0};  // выделяем под 80 + 1 (\0) символов буфер
  int n, len = 0;
  *ptr = '\0';  // (/)
  do {
    n = scanf("%80[^\n]", buf);
    if (n < 0) {
      free(ptr);  // освобождаем память, выделенную под указатель
      ptr = NULL;  // присваиваем указателю ноль
      break;       // выходим из цикла
    }
    if (n == 0) {
      scanf("%*c");  // считать любое количество символов
    } else {
      len += mystrlen(buf);  // прибавить к длине длину буфера
      ptr = (char *)realloc(ptr, len + 1);  // перевыделить память
      ptr = mystrcat(
          ptr, buf);  // соединить с места, куда указывает указатель, буфер (?)
    }
  } while (n > 0);
  return ptr;
}
