#include<stdio.h>
#include<string.h>
#define N 100
int longest(char a[]);
int max;
int longest(char a[])
{
   int i,count=0,length=0,k=0;
   for(i=0;a[i]!='\0';i++)
      k++;
   for(i=0;i<=k;i++)
   {
      if((a[i]>='a'&&a[i]<='z')||(a[i]>='A'&&a[i]<='Z'))
         length++;
      else if(length!=0)
      {
         if(length>max)
         {
            max=length;
            count=i-max;
         }
         length=0;
      }
      else continue;
   }
   return count;
}
int main()
{
   int i;
   char a[N];
   system("color 4E");
   printf("输入一行字符:");
   gets(a);
   int m=longest(a);
   printf("最长单词为：");
   for(i=m;i<m+max;i++)
   printf("%c",a[i]);
   return 0;
}


#include<stdio.h>
#define N 10
int main()
{
   int a[N]={1,2,3,4,5,6,7,8,9,10},i,n,m,*p;
   int move(int a[N],int m);
   p=&a[0];
   printf("原数组为：");
   for(i=0;i<10;i++)
      printf("%d\t",*(p+i));
   printf("\n输入要移动的位数：");
   scanf("%d",&m);
   move(a,m);
   printf("移动后的数组为：");
   for(i=0;i<N;i++)
      printf("%d\t",*(p+i));
   return 0;
}
void move(int a[N],int m)
{
   int *p,a_end,k;
   a_end=*(a+N-1);
   for(p=a+N-1;p>a;p--)
      *p=*(p-1);
   *a=a_end;
   m--;
   if (m>0)
      move(a,m);
}

