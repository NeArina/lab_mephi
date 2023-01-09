#include "input_help.h"

#include <stdio.h>
#include <stdlib.h>

int input_int(int *x, int min_x, int max_x, char *prompt) {
  char *end;
  int t;
  int tmp;
  do {
    char buffer[200];
    printf("%s", prompt);
    t = scanf("%s", buffer);

    if (t == EOF) {
      printf("EOF\n");
      return EOF;
    } else if (t == 0) {
      printf("input not a string O_o\n");
      scanf("%*[^\n]");
    } else {  // no error happened, can try strol
      tmp = strtol(buffer, &end, 10);
      if (*end != 0) {
        printf("not an int? try again\n");
      } else if (!(min_x <= tmp && tmp <= max_x)) {
        printf("the value must be between %d and %d\n", min_x, max_x);
      }
    }
  } while (!(min_x <= tmp && tmp <= max_x) || *end != 0);
  *x = tmp;
  scanf("%*c");
  return 0;
}