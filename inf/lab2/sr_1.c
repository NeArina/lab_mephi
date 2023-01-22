
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
void sq(int a){
  for (int i = 1; i <= a; ++i){
    for (int j = 1; j <= a; ++j){
      if (i == j || i+j == a+1 || i == 1 || i == a || j == 1 || j == a){
        printf("#");
      }
      else {
        printf(" ");
      }
    }
    printf("\n");
  }
}
int main(void) {
  int a;
  scanf("%d", &a);
  sq(a);
  return 0;
}
