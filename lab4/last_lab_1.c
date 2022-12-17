#include <ctype.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
  char *str_copy = (char *)calloc(strlen(str) + 1, sizeof(char));
  strcpy(str_copy, str);

  char *result = (char *)calloc(strlen(str) + 1, sizeof(char));
  int j = 0;

  char *token;

  /* get the first token */
  // 'e'
  // "e"
  token = strtok(str, " \t\n");

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
  if (j > 0 && result[j-1] == ' ') {
    result[j-1] = 0;
  }
  free(str_copy);
  return result;
}

char *strip_string(char *str) {
  if (str == NULL) {
    return NULL;
  }

  char *result = (char *)calloc(strlen(str) + 1, sizeof(char));
  // calloc(n, n_per_one) -> n * n_per_one
  // calloc(10, 1 + 1) -> 20
  // calloc(10 + 1, 1) -> 11

  int len = strlen(str); // len
  int idx = 0;
  while (isspace(str[idx]) && idx < len) {
    idx++;
  }

  int last_char_was_space = 0;
  int j = 0;

  if (idx + 1 == len) {
    result[0] = 0;
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
        result[j] = last_char_was_space ? ' ' : str[idx];
        j++;
        idx++;
      }
    }
  }
  result[j] = 0;

  if (j > 0 && isspace(result[j - 1])) {
    result[j - 1] = 0; // fixing last remaining space
  }
  return result;
}

void my_task() {
  char *str;
  char *s1;
  do {
    str = readline("input your string: ");
    if (str != NULL) {
      printf("before: \"%s\"\n", str);
      // s1 = strip_string(str);
      s1 = strip_string_tok(str);
      printf("after:  \"%s\"\n", s1);
      clock_t start = clock();
      remove_duplicates(str);
      clock_t end = clock();
      double elapsed_time = (end - start) / (double)CLOCKS_PER_SEC;
      printf("time: %.10lf\n", (elapsed_time));
      printf("my ta:  \"%s\"\n", str);
      free(str);
      free(s1);
    }
  } while (str != NULL); // if (str) === if (str != NULL)
}

int main() {
  my_task();

  return 0;
}


