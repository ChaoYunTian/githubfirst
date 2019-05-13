#include<stdio.h>
static int year;
static int weekday;

int isleapyear(int year)      //�жϸ����Ƿ�Ϊ���꣬�������򷵻�1
{
    return (year%4==0&&year%100!=0 || year%400==0);
}

long firstday(int year)    //�жϵ����һ�������ڼ�
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

void printmonthhead(int m) //ÿ���µı���
{
   printf("   %d��    ��   һ   ��   ��   ��   ��   ��\n",m);
   for(int i=0;i<weekday;i++)
      printf("   ");
}

int daymonth(int m)     //ÿ�����ж�����
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

void printmonth(int m)  //���ÿ������
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
   printf("�������(year�������1):");
   scanf("%d,&year");
   weekday=firstday(year);
   //printf("�����·�:\n");
   //scanf("%d,&month");
   printf("                %d��\n",year);
   printf("  ======================\n");
   for(int i=1;i<=12;i++)
   {
      printf("\n");
      printmonth(i);
      printf("\n");
   }
   return 0;
}
