#include "implementation.h"
#include <stdio.h>

int main(void) {
  long double a = 0, x = 0, g = 0, e = 0;
  int n;
  printf("Enter your numbers (a, x, e):\n");
  scanf("%Lf %Lf %Lf", &a, &x, &e);

  if (a > 0 && e > 0) {
    g = f2(a, x, e, &n);
    printf("a^x ~ %.15Lf, n = %d\n", g, n);
  } else {
    printf("'a' and 'e' have to be positive numbers\n");
  }
  return 0;
}
