#include "input_help.h"
#include <stdio.h>
#include <stdlib.h>

void input_int(int *x, int min_x, int max_x, char *prompt) {
    char *end;
    int t;
    int tmp;
    do {
        char buffer[200];
        printf("%s", prompt);
        t = scanf("%s", buffer);
        // Функция strtol преобразовывает строку в long int. 
        // Анализируя строку string, strtol интерпретирует её содержимое в целое число типа long int
        tmp = strtol(buffer, &end, 10);
        if (t == EOF) {
            printf("error read, EOF\n");
        } else if (t == 0) {
            printf("input not a string O_o\n");
            scanf("%*[^\n]");
        } else if (*end != 0) {
            printf("not an int? try again\n");
        } else if (!(min_x <= tmp && tmp <= max_x)) {
            printf("the value must be between %d and %d\n", min_x, max_x);
        }
    } while (!(min_x <= tmp && tmp <= max_x) || *end != 0);
    *x = tmp;
    scanf("%*c");
}