#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mystr.h"
#include "myreadline.h"
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
}

char *strip_string_tok(char *str) {
  char *str_copy = (char *)calloc(mystrlen(str) + 1, sizeof(char));
  mystrcpy(str_copy, str);
  char *result = (char *)calloc(mystrlen(str) + 1, sizeof(char));
  int j = 0;
  char *token;

  token = mystrtok(str_copy, " \t\n");
  if (token) {
    mystrcpy(result + j, token);
    j += mystrlen(token);
    result[j++] = ' ';
  }
  while (token) {
    token = mystrtok(NULL, " \t\n");

    if (token) {
      mystrcpy(result + j, token);
      j += mystrlen(token);
      result[j++] = ' ';
    }
  }
  if (j > 0 && result[j - 1] == ' ') {
    result[j - 1] = 0;
  }
  free(str_copy);
  return result;
}


void my_task() {
    char *str;
    char *s1;
    do {
	str = getstr("input string: ");
        if (str != NULL) {
            printf("before: \"%s\"\n", str);
            clock_t start = clock();
            s1 = strip_string_tok(str);
            printf("after: \"%s\"\n", s1);
            remove_duplicates(s1);
	    clock_t end = clock();
            double elapsed_time = (end - start) / (double)CLOCKS_PER_SEC;
  	    printf("time: %.10lf\n", elapsed_time);
            printf("my task:  \"%s\"\n", s1);
            free(str);
            free(s1);
       }
    } while (str != NULL); // if (str) === if (str != NULL)
}

int main() {
  my_task();
  return 0;
}
