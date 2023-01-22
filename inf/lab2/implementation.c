#include <math.h>
#include "implementation.h"

long double f(long double a, long double x, int n){
  long double q = x * log(a);
  long double p = 1, sum = 1;
  
  for (int i = 1; i <= n; ++i){
    p *= q / i;
    sum += p;
  }
  return sum;
}
