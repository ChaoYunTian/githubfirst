#include<stdio.h>
#include<string.h>
#define N 100
int fun(char a[N],char b[N])
{
   char *p1,*p2;
   p1=a;p2=b;
   int i,j,k,len1,len2,count=0;
   len1=strlen(a);len2=strlen(b);
   for(i=0;i<len1;i++)
   {
      if(*(p1+i)==*p2)
         p2++;
      if(*p2=='\0')
      {
         count++;
         p2=b;
      }
      else continue;
   }
   return count;

}
int main()
{
   char a[N]=" ",b[N]=" ";
   int i,j;
   int fun(char a[N],char b[N]);
   gets(a);
   printf("输入查找的字符：");
   gets(b);
   fun(a,b);
   printf("same words is:%s,出现%d次",b,fun(a,b));
   return 0;
}

