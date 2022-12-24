#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "myreadline.h"
#include "mystr.h"

// my func
void remove_duplicates(char *str) {
    if (str == NULL) {
        return;
    }
    int len = mystrlen(str);
    if (len == 0) {
        return;
    }

    int idx = 1;

    char last_char = str[0];
    int j = 1;

    // str = "  abc   de   "

    while (idx < len) {
        if (str[idx] == last_char) {
            while (str[idx] == last_char && idx < len) {
                idx++;
            }
        }

        if (idx < len) {
            last_char = str[idx];
            str[j] = str[idx];
            j++;
            idx++;
        }
    }

    str[j] = 0;

    // if (j > 0 && str[j - 1] ) {
    //   str[j - 1] = 0; // fixing last remaining space
    // }
}

void strip_string(char *str) {
    if (str == NULL) {
        return;
    }
    int len = mystrlen(str);
    int idx = 0;
    while (my_isspace(str[idx]) && idx < len) {
        idx++;
    }

    int last_char_was_space = 0;
    int j = 0;

    if (idx + 1 == len) {
        str[0] = 0;
    } else {
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
    char *str;
    int t = 0;
    do {
        t = myreadline_char("input string:", &str);
        //printf("debug t=%d, str=\"%s\"\n", t, str);
        if (t >= 0 && str != NULL) {
            printf("before: \"%s\"\n", str);
            strip_string(str);
            printf("after:  \"%s\"\n", str);
	    clock_t start = clock();
            remove_duplicates(str);
	    clock_t end = clock();
            double elapsed_time = (end - start) / (double)CLOCKS_PER_SEC;
  	    printf("time: %.10lf\n", elapsed_time);
            printf("my task:  \"%s\"\n", str);
       }
	free(str);
    }
	 while (t != EOF && str != NULL); // if (str) === if (str != NULL)
}

int main() {
  my_task();
  return 0;
}

