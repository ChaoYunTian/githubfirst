#include<stdio.h>
int main()
{
    int i,j,k,n=8;
    for(i=1;i<=n;i++)
    {
        for(j=n-1;j>=i;j--)
            printf(" ");
        for(k=1;k<=2*i-1;k++)
            printf("*");
        if(n!=1)
        printf("\n");
    }
    for(i=n-1;i>=1;i--)
    {
        for(j=i;j<=n-1;j++)
            printf(" ");
        for(k=1;k<=2*i-1;k++)
            printf("*");
        if(i>1)
            printf("\n");
    }

}*/

#include<stdio.h>
int main()
{
    int i,j,k,bot=0,top=8,n=10,mid;
    int a[10]={1,2,3,4,5,6,7,9,11};
    printf("原数组为：");
    for(i=0;i<=8;i++)
        printf("%-4d",a[i]);
    printf("\n输入一个数：");
    scanf("%d",&k);
    if(k>a[8])
        a[9]=k;
    else
    {
        while(bot<=top)
        {
            mid=(bot+top)/2;
            if(k>=a[mid]) bot=mid+1;
            else top=mid-1;
        }
    printf("最终排序为：");
    for(i=9;i>mid;i--)
        a[i]=a[i-1];
        a[mid]=k;
    }
    for(i=0;i<=9;i++)
        printf("%-4d",a[i]);

}

#include<stdio.h>
int main()
{
    //int a[3][4]={1,2,3,4,5,6,7,8,9,10,11,12};
    int a[3][4]={1,2,3,13,5,6,14,8,9,10,11,12};
    int i,j,k,max,b,flog=0;
    printf("原二维数组为：\n");
    for(i=0;i<3;i++)
    {
        for(j=0;j<4;j++)
            printf("%-4d",a[i][j]);
        printf("\n");
    }
    for(i=0;i<3;i++)
    {
        max=a[i][0];
        for(j=0;j<4;j++)
        {
            if(max<a[i][j])
            {
                 max=a[i][j];
                 k=j;
            }
        }
            for(b=0;b<3;b++)
            {
                if(a[b][k]<max)
                    break;
            }
            if(b>=3)
            {
                printf("鞍点为：%d\t位于第%d行第%d列",a[i][k],i+1,k+1);
                flog=1;
            }
    }
    if(flog==0)
                printf("无鞍点");
}*/
