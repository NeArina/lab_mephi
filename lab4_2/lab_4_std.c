#include <ctype.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *remove_duplicates(char *str) {
  char *result = (char *)calloc(strlen(str) + 1, sizeof(char));
  if (str == NULL) {
    return NULL;
  }

  int len = strlen(str);  // len
  if (len == 0) {
    result[0] = 0;
    return result;
  }
  int idx = 1;
  char last_char = str[0];
  result[0] = str[0];
  int j = 1;
  while (idx < len) {
    if (str[idx] == last_char) {
      while (str[idx] == last_char && idx < len) {
        idx++;
      }
    }

    if (idx < len) {
      last_char = str[idx];
      result[j] = str[idx];
      j++;
      idx++;
    }
  }

  result[j] = 0;
  return result;
}

char *strip_string_tok(char *str) {
  char *str_copy = (char *)calloc(strlen(str) + 1, sizeof(char));
  strcpy(str_copy, str);

  char *result = (char *)calloc(strlen(str) + 1, sizeof(char));
  int j = 0;

  char *token;

  token = strtok(str_copy, " \t\n");

  if (token) {
    strcpy(result + j, token);
    j += strlen(token);
    result[j++] = ' ';
  }
  /* walk through other tokens */
  while (token) {
    // printf(" %s\n", token);
    token = strtok(NULL, " \t\n");

    if (token) {
      strcpy(result + j, token);
      j += strlen(token);
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
  char *s2;
  do {
    str = readline("input your string: ");
    if (str != NULL) {
      printf("before: \"%s\"\n", str);
      // s1 = strip_string(str);
      clock_t start = clock();
      s1 = strip_string_tok(str);
      printf("after:  \"%s\"\n", s1);
      s2 = remove_duplicates(s1);
      clock_t end = clock();
      double elapsed_time = (end - start) / (double)CLOCKS_PER_SEC;
      printf("time: %.10lf\n", (elapsed_time));
      printf("my task:  \"%s\"\n", s2);
      free(str);
      free(s1);
      free(s2);
    }
  } while (str != NULL);
}

int main() {
  my_task();
  return 0;
}
