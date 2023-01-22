#include "implementation1.h"
#include <math.h>
#include <stdio.h>

int main(void) {
  long double a = 0, x = 0, g = 0, e = 0;
  int n = 0;
  while (a <= 0){
    printf("Enter your numbers (a, x, e):\n");
    scanf("%Lf %Lf %Lf", &a, &x, &e);
  }
  g = f2(a, x, e, &n);
  printf("my func a^x ~ %.15Lf, n = %d\n", g, n);
  long double c = pow(a, x);
  printf("math func ~ %.15Lf\n", c);
  return 0;
}

