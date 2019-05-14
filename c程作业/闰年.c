#include<stdio.h>
int main()
{
    int i=0,year=2000;
    printf("ÈòÄêÓĞ£º\n");
    scanf("%d",year);
    while(year<=2200)
    {
        if(year%4==0&&year%100!=0||year%400==0)
        {
            i++;
            printf("%d\t",year);
        }
        if(i%10==0)
        {
            printf("\n");
             year++;
        }
    }
    return 0;
}

