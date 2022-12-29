#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "myreadline.h"
#include "mystr.h"

// my func
void remove_duplicates(char *str) {
    // если строка null, то ничего не возвращаем
    if (str == NULL) {
        return;
    }
    // находим длину строки с помощью собственной функции mystrlen()
    int len = mystrlen(str);
    
    // если длина равна нулю, то ничего не возвращаем
    if (len == 0) {
        return;
    }

    int idx = 1; // присваиваем индексу начальное значение 1
    char last_char = str[0]; // 
    int j = 1; // пр

    // общий смысл действий: .....

    // пока индекс не равен длине строки, цикл будет работать
    while (idx < len) {
        ///
        if (str[idx] == last_char) {
            // 
            while (str[idx] == last_char && idx < len) {
                idx++; // увеличиваем индекс
            }
        }
        // если индекс меньше длины строки
        if (idx < len) {
            last_char = str[idx];
            str[j] = str[idx];
            j++;
            idx++;
        }
    }
    //
    str[j] = 0;

    // if (j > 0 && str[j - 1] ) {
    //   str[j - 1] = 0; // fixing last remaining space
    // }
}

void strip_string(char *str) {
    // если строка нулевая, то ничего не возвращаем
    if (str == NULL) {
        return;
    }

    // находим длину строки с помощью собственной функции mystrlen()
    int len = mystrlen(str);
    // присваиваем индексу нулевое значение
    int idx = 0;

    // общий смысл действий ......

    while (my_isspace(str[idx]) && idx < len) {
        idx++;
    }

    int last_char_was_space = 0; // создаем переменную под последний пробел (?)
    int j = 0;

    if (idx + 1 == len) {
        str[0] = 0;
    } 
    else {
        // str = "  abc   de   "

        while (idx < len) {
            if (my_isspace(str[idx]) && last_char_was_space) {
                while (my_isspace(str[idx]) && idx < len) {
                    idx++;
                }
            }

            if (idx < len) {
                last_char_was_space = my_isspace(str[idx]);
                str[j] = last_char_was_space ? ' ' : str[idx];
                j++;
                idx++;
            }
        }
    }
    str[j] = 0;

    if (j > 0 && my_isspace(str[j - 1])) {
        str[j - 1] = 0;
    }
}

void my_task() {
    char *str; // создаем переменную, в которой будет строка
    int t = 0; // (?)
    do {
        str = getstr("input string:");
        //printf("debug t=%d, str=\"%s\"\n", t, str);
        if (str != NULL) {
            printf("before: \"%s\"\n", str);
            // сделаем между строчками один пробел, убрав все tab'ы и лишние пробелы
            strip_string(str);
            printf("after:  \"%s\"\n", str);
            // начинаем замерять время
            clock_t start = clock();
            // выполняем индивидуальное задание
            remove_duplicates(str);
            // заканчиваем замер времени
            clock_t end = clock();
            // считаем время, за которое выполнилось индивидуальное задание
            double elapsed_time = (end - start) / (double)CLOCKS_PER_SEC;
            // печатаем время, за которое выполнилось индивидуальное задание
            printf("time: %.10lf\n", elapsed_time);
            // печатаем строчку, которая получилась после выполнения индивидуального задания
            printf("my task:  \"%s\"\n", str);
       } else {
        printf("readline() returned NULL\n"); // если строки нет или закончилось чтение
       }
	free(str); // освобождаем память, выделенную под строку
    } while (t != EOF && str != NULL); // if (str) === if (str != NULL)
}

int main() {
  my_task();
  return 0;
}

