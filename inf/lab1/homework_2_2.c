#include <stdio.h>
#include <math.h>

double my_sin(double x, double ac){
    double s = x, p = fabs(x), p1 = fabs(x);
    double  e = ac;
    int i = 2;
    while (fabs(e) >= ac) {
       p = -p*x*x/((2*i-1)*(2*i-2));
       s += p;
       e = fabs(p1) - fabs(p);
       e = fabs(e);
       p1 = p;
       i++;
    }
    return s;
}

int main(){
    double x, ac;
    printf("Enter numbers:\n");
    scanf("%lf\n%lf", &x, &ac);
    while (x > 2*M_PI){
        x = x - 2*M_PI;
    }
    while (x < 2*M_PI){
        x = x + 2*M_PI;
    }
    printf("%.14lf\n", my_sin(x, ac));
    printf("%.14lf\n", sin(x));
    return 0;
}
