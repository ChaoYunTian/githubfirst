/*#include<stdio.h>
int main()
{
    double funy(int n,double x);
    double x;
    int n;
    printf("ÊäÈë£º");
    scanf("%d%lf",&n,&x);
    funy(n,x);
    printf("ÖµÎª£º%.2lf",funy(n,x));
    return 0;
}
double funy(int n,double x)
{
   if(n==0)
        return 1;
   else if(n==1)
        return x;
   else
        return (2*n-1)*x-funy(n-1,x)-(n-1)*funy(n-2,x)/2;
}*/
#include<stdio.h>
int year,mouth,day,i,j,a;
int leap(int year);
int sum();
int main()
{
   int f;
   printf("输入年月日");
   scanf("%d%d%d",&year,&mouth,&day);
   leap(year);
   sum();
   printf("该日是%d年%d天",year,f);
}
int leap(int n)
{
   if(year%4==0&&year%100==0||year%400==0)
      a=0;
   else
      a=1;
   return (a);
}
int sum()
{
   int k,m=0;
   int g[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
   for(k=1;k<mouth;k++)
      m=m+g[k];
   if(i==0)
      m=m+1;
   return (m);
}
