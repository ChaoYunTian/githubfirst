/*#include<stdio.h>
int main()
{
    int a[10];
    int b,i=0,k;
    printf("输入一个数：");
    scanf("%d",&b);
    while(b!=0)
    {
        a[i]=b%10;
        b=b/10;
       i++;
    }
 printf("各位为：");
    for(k=i-1;k>=0;k--)
        printf("%d ",a[k]);
    printf("\n它是一个%d位数",i);
    printf("\n倒序为：");
    for(k=0;k<=i-1;k++)
    printf("%d",a[k]);
    return 0;
}*/

/*#include<stdio.h>
#include<math.h>
int main()
{
    int i,j,k,m=0;
      printf("素数有：\n");
    for(i=101;i<=200;i+=2)
    {
        k=sqrt(i);
        for(j=2;j<=k;j++)
            if(i%j==0) break;
        if(i>=k+1)
        {
            printf("%d\t",i);
            m=m+1;
        }
        if(m%10==0)
            printf("\n");
    }
    return 0;
}*/
#include<stdio.h>
int main()
{
    int i=0,j,k,m,n,s=1,t;
    printf("plase input a number:");
    scanf("%d",&m);
    j=m; t=m;
    while(j>9)
    {
        j=j/10;
        s=s*10;
    }
    printf("各位为：");
    while(s>0)
    {
        n=m/s;
        printf("%d ",n);
        m=m%s;
        s=s/10;
        i++;
    }
    printf("\n它是一个%d位数",i);
    printf("\n逆序为：");
   do {
        printf("%d",t%10);
        t=t/10;
      }while(t>0);
    return 0;
}
