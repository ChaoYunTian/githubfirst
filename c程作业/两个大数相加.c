#include<stdio.h>
#include<string.h>
#define N 200
int main()
{
   char a[N]=" ",b[N]=" ";
   int str1[N]={0},str2[N]={0};
   int i,j,k,m,len1,len2,c;
   printf("输入两个大数：\n");
   gets(a);
   gets(b);
   len1=strlen(a);
   len2=strlen(b);
   if(len1>len2)
      m=len1;
   else
      m=len2;
   k=m;c=m;
   for(i=0;i<len1;i++,m--)
      str1[m]=a[len1-1-i]-'0';
   for(j=0;j<len2;j++,k--)
      str2[k]=b[len2-1-j]-'0';
   for(i=c;i>0;i--)
   {
      str1[i]+=str2[i];
      if(str1[i]>=10)
      {
         str1[i]-=10;
         str1[i-1]++;
      }
   }
   printf("两数和为：");
   for(i=0;i<=c;i++)
   {
      if(i==0 && str1[0]== 0) continue;
      printf("%d",str1[i]);

   }
   return 0;
}























