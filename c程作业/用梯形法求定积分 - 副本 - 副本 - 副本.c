#include<stdio.h>
#include<math.h>
#define N 100000
double s(double x)
{
    return sin(x);
}
double c(double x)
{
    return cos(x);
}
double e(double x)
{
    return exp(x);
}
double D(int n,double a,double b)
{
    double s(double x);
    double c(double x);
    double e(double x);
    double sum=0,x=a;
    double i=(b-a)/N;
    double (*p)(double x);
    int j=0;
    if(n==1) p=s;
    else if(n==2) p=c;
    else p=e;
    //printf("%f\n",(*p)(1));
    for(j=0;j<N;j++)
    {
        sum+=(((*p)(x)+(*p)(x+i))/2*i);
        x+=i;
    }
    return sum;
}
int main()
{
    double a,b;
    int n;
    //scanf("%lf",&a);
    printf("%.10f\n",c(1)-c(2));
    scanf("%d",&n);
    scanf("%lf %lf",&a,&b);
    printf("%.10f",D(n,a,b));
    return 0;
}
