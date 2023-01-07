#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
  srand(time(0));

  int count = 0;
  printf("Input number:");
  scanf("%d", &count);
  int *array = (int *)malloc(count * sizeof(int));
  char *name = "random.txt";
  FILE *file = fopen(name, "w+");
  // char alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int len = 8;
  // char *s[8];
  int n = 100;
  // генерация строк
  while (n) {
    for (int i = 0; i < len; ++i) {
      fprintf(file, "%c",
              'a' + rand() % 26);  // переход на новую строчку не получается
    }
    --n;
  }
  //   for (int i = 0; i < count; i++) {
  //     fprintf(file, "%d\n", rand() % 1000); // генерация чисел
  //   }
  fclose(file);
}