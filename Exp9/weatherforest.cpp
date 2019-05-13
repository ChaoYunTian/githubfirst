/***********************************************
 �ļ�����WeatherForecast.cpp
 ��Ҫ��  ģ������Ԥ����һ���µ��¶ȷ���
 ������
 1. displayTemp����ʾ�¼��¶ȵ���״ͼ
 2. displayPeaks����ʾ�¼��¶��еķ�ֵ
 3. displayFlat����ʾ�¼������õ��¶�
 4. forecasting�������û����룬
 ���������3������
 ************************************************/

#include <iostream>
#include <iomanip>
#include <cmath>
#define N 5

using namespace std;

void displayTemp(int temp[],int n)
{
   int min = temp[0];
   for(int i = 1; i < n; i++)
   {
      if( min > temp[i])
         min = temp[i];
      else
         continue;
   }
      for(int i = 0; i < n; i++)
      {
          if(min < 0)
         {
            cout << setw(4) << temp[i];
            if(temp[i] < 0)
            {
               for(int j = 0; j < (temp[i] - min);j++)
               {
                  cout << " " ;
               }
               for(int j = temp[i];j < 0;j++)
               {
                  cout << "*";
               }
               cout << "|" << endl;
            }
            else
            {
               for(int j = min;j < 0; j++)
               {
                  cout << " ";
               }
               cout << "|";
               for(int j = 0;j < temp[i];j++)
               {
                  cout << "*";
               }
               cout << endl;
            }
         }
      else
      {
         cout << setw(4) << temp[i];
         for(int i = 0; i < min;i++)
         {
            cout << " ";
         }
         cout << "|";
         for(int j = 0; j < temp[i]; j++)
         {
            cout << "*";
         }
         cout << endl;
      }
   }
}

int displayPeaks(int temp[],int n)
{
   int peak;
   for(int i = 0;i < n;i++)
   {
      if(temp[i] >= temp[i - 1] && temp[i] >= temp[i + 1])
         peak = temp[i];
      else
         continue;
   }
   return peak;
}

void displayFlat(int temp[], int n)
{
   int count = 1,maxnum = 0;
   for(int i = 0 ;i < n; i++)
   {
      if(temp[i] == temp[i++])
      {
         count++;
      }
      else
         {
            if(count > maxnum)
                  maxnum = count;
            count = 1;
         }
   }
   if(count > maxnum)
      maxnum = count;
   cout << "Maxnum is :" << maxnum << endl;
}

int main()
{
   int a[N],m,i,j;
   cout << " please input 15 weather :" << endl;
   for(int i = 0; i < N ;i++)
   {
      cin >> a[i];
   }
   displayTemp(a,N);

   m = displayPeaks(a,N);
   cout << "��ֵΪ��" << m << endl;
   displayFlat(a,N);

   return 0;

}
