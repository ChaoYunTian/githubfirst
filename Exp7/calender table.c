#include<stdio.h>
static int year;
static int weekday;

int isleapyear(int year)      //判断改年是否为润年，是闰年则返回1
{
    return (year%4==0&&year%100!=0 || year%400==0);
}

long firstday(int year)    //判断当年第一天是星期几
{
   long n,num;
   int i=1;
   n=year*365;
   for(i=1;i<=year;i++)
   {
      if(isleapyear(i))
         n++;
   }
   num=n%7;
   return num;
}

void printmonthhead(int m) //每个月的标题
{
   printf("   %d月    日   一   二   三   四   五   六\n",m);
   for(int i=0;i<weekday;i++)
      printf("   ");
}

int daymonth(int m)     //每个月有多少天
{
   switch(m)
   {
      case 1:
      case 3:
      case 5:
      case 7:
      case 8:
      case 10:
      case 12: return 31;break;
      case 4:
      case 6:
      case 9:
      case 11: return 30;break;
      case 2:
         {
            if(isleapyear(year))
               return 29;
            else
               return 28;
         }
      default :
         break;
   }
   return 0;
}

void printmonth(int m)  //输出每月日历
{
   printmonthhead(m);
   int days=daymonth(m);
   for(int i=1;i<=days;i++)
   {
      printf("   %d",i);
      weekday=(weekday+1)%7;
      if(weekday==0)
      {
         printf("\n");
         printf("   ");
      }
   }
}

int main()
{
   int year,month,day;
   int flag,number;
   printf("输入年份(year必须大于1):");
   scanf("%d,&year");
   weekday=firstday(year);
   //printf("输入月份:\n");
   //scanf("%d,&month");
   printf("                %d年\n",year);
   printf("  ======================\n");
   for(int i=1;i<=12;i++)
   {
      printf("\n");
      printmonth(i);
      printf("\n");
   }
   return 0;
}

