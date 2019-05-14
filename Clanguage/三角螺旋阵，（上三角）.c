#include<stdio.h>
#include<stdlib.h>
void fun(int n)
{
   int max,m=0,i=0,j=0,step=1,count=1;       //m控制方向，等于0是横向，等于1是对角线，等于2是纵向 ,step为每次加1
   int a[20][20]={0};
   if(n%2==0)
      max=n*n/2+n/2;
   else
      max=n*n/2+n/2+1;
      while(count<=max)
      {
         a[i][j]=count++;
         if(m==0)    //m=0时横向加
         {
            j+=step;
            if(j>=n||a[i][j]!=0)    //到边界了
               {
                  m=1;
                  j-=step;
                  j-=step;
                  i+=step;
               }
         }
         else if(m==1)     //走对角线加
         {
            j-=step;
            i+=step;
            if(j<0||a[i][j]!=0)
            {
               m=2;
               i-=step;
               j+=step;
               i-=step;
            }
         }
         else     //向上纵向加
         {
            i-=step;
            if(a[i][j]!=0)
            {
               m=0;
               i+=step;
               j+=step;
            }
         }
      }
         for(i=0;i<n;i++)
            {
               for(j=0;j<n;j++)
               {
                  if(a[i][j]!=0)
                     printf("%-4d",a[i][j]);
               }
               printf("\n");
            }
}
int main()
{
   int n;
   void fun(int n);
   printf("输入螺旋三角形的大小(1~20):");
   scanf("%d",&n);
   fun(n);
   return 0;
}
