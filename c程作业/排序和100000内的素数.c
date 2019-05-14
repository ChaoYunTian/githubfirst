/*#include<stdio.h>
int main()
{
    int a[10000];
    int i,j,k,m,n;
    for(i=2;i<=10000;i++)
    {
        k=0;n=0;
        for(j=1;j<i;j++)
        {
            if(i%j==0)
            {
                a[n]=j;
                k=k+a[n];
                n++;
            }
        }
            if(k==i)
            {
                printf("%d\t",i);
                printf("its factors are");
                for(m=0;m<n;m++)
                    printf("%d ",a[m]);
                printf("\n");
            }
    }
    return 0;
}*/


/*#include<stdio.h>
#define N 10
int main()
{

    int a[N];
    int i,j,temp;
    printf("plase input a number:");
    for(i=0;i<N;i++)
    scanf("%d",&a[i]);
    for(i=0;i<N-1;i++)
    {
        for(j=0;j<N-1-i;j++)
        {
            if(a[j]>a[j+1])
            {
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
    printf("排序结果为：");
    for(i=0;i<N;i++)
    {
        printf("%d\t",a[i]);
    }
    return 0;
}*/


/*#include<stdio.h>
#define N 10
void sort(int a[])
{
    int i,j,temp;
    for(i=0;i<N-1;i++)
    for(j=i+1;j<N;j++)
    {
        if(a[i]<a[j])
        {
        temp=a[i];
        a[i]=a[j];
        a[j]=temp;
        }
    }
    for(i=0;i<N;i++)
    printf("%d ",a[i]);
}
int main()
{
    int a[N],i;
    printf("plase input ten numbers");
    for(i=0;i<N;i++)
    scanf("%d",&a[i]);
    sort(a);
    return 0;
}*/

//用了筛法的方法：
/*#include<stdio.h>
#include<math.h>
#define N 1000000
int main()
{
    char a[N+1]={0};
    int i,j,k,num=0;
    for(i=3;i<=N;i++)
    {
        if(a[i]==0)
            for(j=2;j<=(int)sqrt(i);j++)
                if(i%j==0)
                {
                    a[i]=1;
                    for(k=i;k<=N;k+=i)
                        a[k]=1;
                    break;
                }
    }
    for(i=2;i<=N;i++)
        if(a[i]==0)num++;
    printf("1000000以内的素数共有%d个",num);
    return 0;
}*/
#include<stdio.h>
#define N 10
int main()
{

    int m(int a[]);
    int i,a[N],j;
    printf("plase input a number:");
    for(i=0;i<N;i++)
    scanf("%d",&a[i]);
    m(a);
     return 0;
}
     int m(int a[])
     {
         int i,j,temp;
         for(i=0;i<N-1;i++)
        {
        for(j=0;j<N-1-i;j++)
            if(a[j]<a[j+1])
            {
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
        printf("排序结果为：");
         for(i=0;i<N;i++)
        printf("%d\t",a[i]);
        return 0;

     }

