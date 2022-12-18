#include "myreadline.h"
// #define BUFFER_SIZE 20
// #define FORMAT_STR ("%19[^\n]s") // переделать scanf("%80["\n"], buf);
#include <stdlib.h>
#include "mystrlen.h"
#include <stdio.h>

int myreadline(char *p_str, char **ppstr) {
    printf("%s", p_str);

    //char buffer[20];

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
        t = scanf("%19[^\n]", str + curSize);
        if (t == EOF) {
            *ppstr = str;
            return EOF;
        }
        str_ended = str[curSize] == 0;
        curSize += mystrlen(str + curSize);
        if (curSize + 20 >= size) {
            size += 20;
            str = realloc(str, sizeof(char) * size);
        }

    } while (!str_ended);

    *ppstr = str;
    char c; /// зацикливание 
    scanf("%c", &c);
    return curSize;
}
