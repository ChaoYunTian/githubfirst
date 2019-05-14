/*#include<stdio.h>
#define N 8
int main()
{
    int i,j,k;
    int a[N];
    printf("输入一串数:");
    for(i=0;i<8;i++)
    scanf("%d",&a[i]);
    for(i=0;i<7;i++)
        for(j=0;j<7;j++)
    {
        if(a[j]<a[j+1])
        {
            k=a[j+1];
            a[j+1]=a[j];
            a[j]=k;
        }
    }
        for(i=0;i<8;i++)
        {
            printf("%-6d",a[i]);

        }
        return 0;

}*/
/*
#include<stdio.h>
#include<stdlib.h>
int main()
{
    int i=0,j=0;
    char ch[10];
    printf("输入一串数：");
    scanf("%s",ch);
    for(i=0;ch[i]!=0;i++)
    {
        if(ch[i]%2==0)
        {
            j++;
            printf("%-c",ch[i]);
        }
    }
    printf("\n");
    printf("个数有：%d个",j);
    return 0;
}*/
/*#include<stdio.h>
#include <stdlib.h>
int main()
{
 char input[100] ;

int i=0;
scanf("%s" , input);
for( ; input[i]  != 0 ; i++) //如果不为空字符就循环
{
    if((input[i] - '0' ) %2 == 0) //判断是否为偶数
   printf("%c" , input[i]) ;
}
 return 0;
}*/
/*#include<stdio.h>
#include<math.h>
int main()
{
   char a[100]="A123x456 17960? 302tab5876";
   void find(char *p);
   printf("输入的字符串为：");
   printf("%s",a);
   find(a);
   return 0;
}
void find(char *p)
{
   int b[100],i,*q,num=0;
   q=b;
   for(;*p!='\0';p++)
      if(*p>='0'&&*p<='9')
      {
         *q=*p-'0';
         p++;
         while(*p>='0'&&*p<='9')
            *q=(*q)*10+(*(p++)-'0');
         num++;
         q++;
      }
   printf("\n输出：");
   for(i=0,q=b;i<num;i++,q++)
   printf("%d\t",*q);
   printf("\n一共有%d个",num);
}*/

#include<stdio.h>
#include<string.h>
int main()
{
    int tr(char *p1, char *p2);
    char str1[100]=" ",str2[100]=" ";
    printf("请输入两个字符串:\n");
    gets(str1);
    gets(str2);
    int flag=tr(str1,str2);
    if(flag!=-1)
    	printf("return %d\n",flag);
    else
		printf("return %d\n",flag);
    return 0;
}
int tr(char *p1,char *p2)
{
    int i,j,flag=-1;
    if(strlen(p2)>strlen(p1))
     return flag;
    else
   {
       for(i=0;i<strlen(p1);i++)
      {
        if(*(p1+i)==*p2)
        {
           for(j=0;j<strlen(p2);j++)
              if(*(p1+i+j)!=*(p2+j)||*(p1+i+j)=='\0')
               return -1;
            flag=i;
            if(*(p2+j)=='\0') break;
        }
      }
      return (flag);
   }
}








































/*#include<stdio.h>
#define N 8
int main()
{
    int *ptr_num;
    int i,j,k;
    int a[N];
    printf("输入一串数:");
    for(i=0;i<8;i++)
    scanf("%d",&a[i]);
    for(i=0;i<8;i++)
    {
        *ptr_num=a[0];
        printf("%d\t",&ptr_num);
        *ptr_num=a[2];
        printf("%d\t",&ptr_num);
        *ptr_num=a[4];
        printf("%d\t",&ptr_num);

    }
    return 0;
}
*/
