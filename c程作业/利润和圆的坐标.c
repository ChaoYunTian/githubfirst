/*#include<stdio.h>
#include<math.h>
int main()
{
    double x,y,k;
    int h=10;
    printf("输入一个坐标：");
    scanf("%lf%lf",&x,&y);
    k=((fabs(x)-2)*(fabs(x)-2)+(fabs(y)-2)*(fabs(y)-2));
    if(k<=1)
        h=10;
    else h=0;
    printf("该点坐标的高度为%d",h);
    return 0;

}*/
/*#include<stdio.h>
int main()
{
    double i,j;
    printf("输入当月利润:");
    scanf("%lf",&i);
    if(i<=100000)
        printf("应发奖金：%.2lf",j=i*0.1);
    else if(100000<i&&i<=200000)
        printf("应发奖金:%.2lf",j=100000*0.1+(i-100000)*0.075);
    else if(200000<i&&i<=400000)
        printf("应发奖金：%.2lf",j=100000*0.1+100000*0.075+(i-200000)*0.05);
    else if(400000<i&&i<=600000)
        printf("应发奖金：%.2lf",j=100000*0.1+100000*0.075+200000*0.05+(i-400000)*0.03);
    else if(600000<i&&i<=1000000)
        printf("应发奖金：%.2lf",j=100000*0.1+100000*0.075+200000*0.05+200000*0.03+(i-600000)*0.015);
        else
        printf("应发奖金：%.2lf",j=100000*0.1+100000*0.075+200000*0.05+200000*0.03+400000*0.015+(i-1000000)*0.01);
    return 0;*/

/*#include<stdio.h>
#include<math.h>
int main()
{
    int i=0;
    double j;
    printf("输入当月利润:");
    scanf("%d",&i);
    switch(i/100000)
    {
    case 0:
         printf("应发奖金：%.2lf",j=i*0.1);
         break;
    case 1:
    case 2:
        printf("应发奖金:%.2lf",j=100000*0.1+(i-100000)*0.075);
        break;
    case 3:
    case 4:
        printf("应发奖金：%.2lf",j=100000*0.1+100000*0.075+(i-200000)*0.05);
        break;
    case 5:
    case 6:
        printf("应发奖金：%.2lf",j=100000*0.1+100000*0.075+200000*0.05+(i-400000)*0.03);
    break;
    case 7:
    case 8:
    case 9:
    case 10:
        printf("应发奖金：%.2lf",j=100000*0.1+100000*0.075+200000*0.05+200000*0.03+(i-600000)*0.015);
    break;
      default:
        printf("应发奖金：%.2lf",j=100000*0.1+100000*0.075+200000*0.05+200000*0.03+400000*0.015+(i-1000000)*0.01);
        break;
        return 0;
    }
}*/
#include<stdio.h>
#define N 8
int main()
{
    int a[N];
    int t,i;
    printf("输入一串数字：");
    for(i=0;i<8;i++)
    scanf("%d",&a[i]);
    a[i]=i;
    for(i=0;i<N/2;i++)
    {
        t=a[i];
        a[i]=a[N-i-1];
        a[N-i-1]=t;
    }
    for(i=0;i<N;i++)
    {
        printf("%d\t",a[i]);
    }
    return 0;
}
