#include<stdio.h>
#define N 100
void faust(int n,int m)
{
   int a[N],i,j=0,finally=0,*p;
   p=a;
   for(i=0;i<n;i++)
     *(p+i)=i+1;
   i=0;
      while(finally<n)
   {
      if(*(p+i)!=0)
         j++;
      if(j==m)
      {
         *(p+i)=0;
         j=0;
         finally++;
         printf("%-4d",i+1);    //finally为退出的人数
         if(finally%10==0)
            printf("\n");
      }
      i++;
      if(i==n)       //如果到最后，i又从0开始
         i=0;
   }
   if(finally%10!=0)
         printf("\n");
}
int main()
{
   int n,m;
   system("color 5C");
   printf("输入总人数和报数范围：");
   scanf("%d%d",&n,&m);
   faust(n,m);
   return 0;
}
