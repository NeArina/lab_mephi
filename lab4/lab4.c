#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <readline/readline.h>

void remove_duplicates(char *str) {
  if (str == NULL) {
    return;
  }

  int len = strlen(str); // len
  if (len == 0) {
    return;
  }

  int idx = 1;

  char last_char = str[0];
  printf("last char %c :", last_char);
  int j = 1;

  // str = "  abc   de   "

  while (idx < len) {
    if (str[idx] == last_char) {
      while (str[idx] == last_char && idx < len) {
        printf("str[idx]: %c\n", str[idx]);
        printf("last_char: %c\n", last_char);
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

void strip_string(char *str) {
  if (str == NULL) {
    return;
  }

  int len = strlen(str); // len
  int idx = 0;
  while (isspace(str[idx]) && idx < len) {
    idx++;
  }

  int last_char_was_space = 0;
  int j = 0;

  if (idx + 1 == len) {
    str[0] = 0;
  } else {
    // str = "  abc   de   "

    while (idx < len) {

      if (isspace(str[idx]) && last_char_was_space) {
        while (isspace(str[idx]) && idx < len) {
          idx++;
        }
      }

      if (idx < len) {
        last_char_was_space = isspace(str[idx]);
        str[j] = last_char_was_space ? ' ' : str[idx];
        j++;
        idx++;
      }
    }
  }
  str[j] = 0;

  if (j > 0 && isspace(str[j - 1])) {
    str[j - 1] = 0; // fixing last remaining space
  }
}


void my_task() {
  char *str;
  do {
    str = readline("input your string: ");
    if (str != NULL) {
      printf("before: \"%s\"\n", str);
      strip_string(str);
      printf("after:  \"%s\"\n", str);
      clock_t start = clock();
      remove_duplicates(str);
      clock_t end = clock();
      double elapsed_time = (end-start)/(double)CLOCKS_PER_SEC;
      printf("time: %.10lf\n", (elapsed_time));
      printf("my ta:  \"%s\"\n", str);
      free(str);
    }
  } while (str != NULL); // if (str) === if (str != NULL)
}

int main() {
  my_task();

  return 0;
}
