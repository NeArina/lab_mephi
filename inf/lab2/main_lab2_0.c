#include <stdio.h>
#include <math.h>
#include "implementation.h"

int main(void) {
  long double a = 0, x = 0, g = 0;
  int n = 0;
  while (a <= 0 || n <= 0){
    printf("Enter your numbers:\n");
    scanf("%Lf %Lf %d", &a, &x, &n);
  }
  g = f(a, x, n);
  printf("My func ~ %.15Lf\n", g);
  long double c = pow(a, x);
  printf("Math func ~ %.15Lf\n", c);
  return 0;
}
