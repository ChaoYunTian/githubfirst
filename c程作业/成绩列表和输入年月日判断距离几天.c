#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
#define N 3
#define M 5
float k[N];
int main()
{
   //int a[N][M]={70,70,70,70,100,70,70,70,70,70,70,70,70,70,70};
   int a[N][M];
   float produce_score(int a[N][M]);
   float average1(int a[N][M]);
   float average2(int a[N][M]);
   float max(int a[N][M]);
   float var(int a[N][M]);
   produce_score(a);
   average1(a);
   average2(a);
   max(a);
   var(a);
   return 0;
}
float produce_score(int a[N][M])
{
   int i,j;
   printf("成绩如下：\n");
   srand(time(NULL));
   for(i=0;i<N;i++)
   {
      printf("第%d位学生:",i+1);
      for(j=0;j<M;j++)
      {
         a[i][j]=(rand()%41+60);
         printf("%d\t",a[i][j]);
      }
      printf("\n");
   }
   return 0;
}
float average1(int a[N][M])
{
   int i,j;
   double sum;
   for(i=0;i<N;i++)
   {
      sum=0;
      for(j=0;j<M;j++)
          sum+=a[i][j];
         k[i]=sum/M;
         printf("第%d个学生的平均分为%.2lf\n",i+1,k[i]);
   }
   printf("\n");
}
float average2(int a[N][M])
{
   int i,j,sum;
   double k;
   for(j=0;j<M;j++)
   {
      sum=0;
      for(i=0;i<N;i++)
         sum+=a[i][j];
      k=sum/N;
      printf("第%d门课的平均分为：%.2lf\n",j+1,k);
   }
   printf("\n");
}
float max(int a[N][M])
{
   int i,j,k=0,m=0,max;
   max=a[0][0];
   for(i=0;i<N;i++)
   {
      for(j=0;j<M;j++)
      if(a[i][j]>max)
         {
            max=a[i][j];
            k=i;m=j;
         }
   }
   printf("最高分数为%d是第%d个学生的第%d门课程",max,k+1,m+1);
}
float var(int a[N][M])
{
   int i;
   double sum1=0,sum2=0,t;
   for(i=0;i<N;i++)
   {
      sum1+=k[i]*k[i];
      sum2+=k[i];
   }
   t=sum1/N-(sum2/N)*(sum2/N);
   printf("\n平均分方差为：%.2lf",t);
}
/*#include<stdio.h>
int year,mouth,day,i,a,t,x;
int leap(int year);
int date(int year);
int sum();
int main()
{
   printf("输入年月日:");
   scanf("%d%d%d",&year,&mouth,&day);
   leap(year);
   sum();
   date(year);
   printf("%d年%d月%d日是%d年第%d天距离1970年%d天",year,mouth,day,year,sum(),date(year));
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
   int k,m=0,x;
   int g[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
   for(k=1;k<mouth;k++)
         m=m+g[k];
   x=m+day;
   if(a==0)
   x=x+1;
   return (x);
}
int date(int year)
{
   int j,w=0,r=0,q;
   for(j=1970;j<year;j++)
   {
      if(j%4==0&&j%100==0||j%400==0)
      {
         t=0;
         w++;
      }
      else
      {
         t=1;
         r++;
      }
   }
   q=365*r+366*w+x;
   return (q);
}*/


