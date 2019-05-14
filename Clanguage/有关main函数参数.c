#include<stdio.h>
#define N 10000
int main()
{
   int i,j,m,n,count,num=0,k;
   for(i=1;i<=N;i++)
   {
      m=i*i;
      k=i;
      count=0;
      while(k!=0)
      {
         k=k/10;
         count++;
      }
      n=1;
      for(j=0;j<count;j++)
         n*=10;
      if(m%n==i)
        {
            printf("%-4d",i);
            num++;
            if(num%6==0)
         printf("\n");
        }
      else continue;
   }
   printf("\n一共有%d个",num);
}
