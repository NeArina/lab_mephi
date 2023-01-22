#include <math.h>
#include <stdio.h>

int num(int a, int *sum) {
  int max = -1, last = 0, sum_ = 0, number = 0, count = 0, a_ = a, a2 = a;
  int min = 10;

  int max_count = 0;
  int min_count = 0;
  while (a > 0) {
    last = a % 10;
    printf("last=%d\n", last);
    
    if (last > max) {
      max = last;
      max_count = 1;
    } else if (last == max) {
      max_count++;
    }
    
    if (last < min) {
      min = last;
      min_count = 1;
    } else if (last == min) {
      min_count++;
    }
    
    a /= 10;
  }

printf("min=%d, max=%d\n", min, max);

  *sum = min_count + max_count;
  a = a2;

  // могу предположить, что основная проблема в том, что условие должно быть (last != max && last != min) вместо (last != max || last != min)
  while (a > 0) {
    last = a % 10;
    if (last != max && last != min) {
      printf("num=%d, count=%d, last=%d\n", number, count, last);
      number += last * (int)pow(10, count);
      count += 1;
    }
    
    a /= 10;
  }
  return number;
}

int main(void) {
  int a = 0, sum = 0;
  scanf("%d", &a);
  int d = num(a, &sum);
  printf("%d\n", sum);
  printf("%d", d);
  return 0;
}
