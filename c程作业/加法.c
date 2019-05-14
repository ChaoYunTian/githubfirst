#include<stdio.h>
int main()
{
    //打印加法表
    int num;
    int i;
    printf("输入一个数：");
    scanf("%d",&num);
    for(i=0;i<=num;i++)
    {
        printf("%d+%d=%d",i,(num-i),num);
    if(i%2==0)
    {
        printf("\t\t");
    }
    else
    {
        printf("\n");
    }
    }
    return 0;
}
