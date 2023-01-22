#include <stdio.h>
#include <math.h>

float my_exp(float x, int n){
    double s = 1, p = 1;
    for (int i = 1; i <= n; ++i){
        p = -p*x*x/i;
        s += p;
    }
    return s;
}

int main(){
    double x;
    int n;
    printf("Enter numbers:\n");
    scanf("%lf\n%d", &x, &n);
    float s = my_exp(x, n);
    printf("%lf\n", s);
    double r = exp(-x*x);
    printf("%lf\n", r);
    return 0;
}
 
