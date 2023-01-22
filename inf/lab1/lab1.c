#include <stdio.h>

int len_(int x){
   int count = 0;
   while (x > 0){
      count += 1;
      x /= 10;
   }
   return count;
}

int new_num(int x){
   int q = 1, len = len_(x), reverse = 0, c = 0, y = 0, o=x, h = 0, r = 0;
   while (x > 10){
      c = x % 100;
      y = c / 10 + (c % 10)*10;
      reverse += y*q;
      q *= 100;
      x /= 100;
   }
   if (len % 2 == 0){
      return reverse;
   }
   else{
      r = o / q;
      h = r * q + reverse;
      return h;
   }
}

int main(){
   int a = 0;
   printf("Enter your number:\n");
   scanf("%d", &a);
   if (a > 0){
      printf("%d", new_num(a));
   }
   else{
      int c  = (-1)*a;
      printf("%d",new_num(c)*(-1));
   }
 return 0;
}
