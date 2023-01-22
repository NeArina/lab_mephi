#include <math.h>
#include "implementation1.h"

long double f2(long double a, long double x, long double e, int *n) {
  long double q = x * log(a);
  long double p1 = 1, p0 = 0;
  long double sum = 1;
  long double e1 = e;
  int i = 1;
  int count = 1; // количество членов ряда, которое потребовалось вычислить для обеспечения заданной точности 

  while (e1 >= e) {
    p0 = p1;
    //printf("p0 = %Lf\n", p0);
    p1 *= q / i;
    //printf("p1 = %Lf\n", p1);
    sum += p1;
    //printf("sum = %Lf\n", sum);
    count += 1;
    e1 = fabsl(p1 - p0); // e1 = fabsl(p1);
    ++i;
  }
  *n = count;
  return sum;
}
