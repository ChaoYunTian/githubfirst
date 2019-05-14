#include<stdio.h>
#define N 100
int strstr(char *str1,char *str2)
{
    int count1,count2,flag=-1;
    for(count1=0;*(str1+count1)!='\0';count1++);
    for(count2=0;*(str2+count2)!='\0';count2++);
    for(int i=0;i<=count1-count2;i++)
    {
        if(*(str1+i)==str2[0])
        {
            int j;
            for(j=1;j<count2;j++)
                if(*(str1+i+j)!=*(str2+j)) break;
            if(j==count2)
            {
                flag=i+1;
                break;
            }
            else continue;
        }
        else continue;
    }
    return flag;

}
int main()
{
    char a[N]=" ",b[N]=" ";
    gets(a);
    gets(b);
    int flag=strstr(a,b);
    if(flag!=-1)
        printf("Having Found %d",flag);
    else
        printf("Not find out %d",flag);
    return 0;
}
