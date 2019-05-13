#ifndef FILTER_HPP_INCLUDED
#define FILTER_HPP_INCLUDED
#include "Mat.hpp"

template <class T>
class Filter
{
public:
   Filter(int size):filterSize(size)
   {

   }
   virtual ~Filter()
   {

   }
   virtual Mat<T> Filtering(const Mat<T> &input) = 0;

protected:
   int filterSize;

};


//meanFilter类
template<typename T1>
class MeanFilter : public Filter<T1>
{
public:
   MeanFilter(int size):Filter<T1>(size)
   {

   }
   virtual ~MeanFilter()
   {

   }
   virtual Mat<T1> Filtering(const Mat<T1> &input)      //均值滤波器
   {
      int h = input.Height();
      int w = input .Width();
      int new_h, new_w, end_h, end_w;
      int num = Filter<T1>::filterSize / 2;
      Mat<T1> temp(h,w);
      for(int i = 0; i < h; i++)
      {
         for(int j = 0;j < w; j++)
         {
            T1 sum = 0;
            if(i - num <= 0)
            {
               new_h = 0;
            }
            else
               new_h = i - num;
            if(j - num <= 0)
            {
               new_w = 0;
            }
            else
               new_w = j - num;

            if(i + num < h)
            {
               end_h = i + num;
            }
            else
               end_h = h - 1;

            if(j + num < w)
            {
               end_w = j + num;
            }
            else
               end_w = w - 1;
            for(int m = new_h; m <= end_h; m++)
            {
               for(int n = new_w; n <= end_w; n++)
               {
                  sum += input.At(m,n);
               }
            }
            temp.At(i,j) = sum /((end_h - new_h + 1) * (end_w - new_w + 1));
         }
      }
      return temp;
   }
};
//Median类
template <typename T2>
class MedianFilter : public Filter<T2>
{
   public:
      MedianFilter(int size):Filter<T2>(size)
      {

      }
      virtual ~MedianFilter()
      {

      }
      virtual Mat<T2> Filtering(const Mat<T2> &input)      //中值滤波器
      {
         int h = input.Height();
         int w = input .Width();
         int new_h,new_w,end_h,end_w;
         int num = Filter<T2>::filterSize / 2;
         T2 *b = new T2 [Filter<T2>::filterSize * Filter<T2>::filterSize]();
         Mat<T2> temp(h,w);
         for(int i = 0; i < h; i++)
         {
            for(int j = 0;j < w; j++)
            {
               T2 sum = 0;
               if(i - num <= 0)
               {
                  new_h = 0;
               }
               else
                  new_h = i - num;
               if(j - num <= 0)
               {
                  new_w = 0;
               }
               else
                  new_w = j - num;

               if(i + num < h)
               {
                  end_h = i + num;
               }
               else
                  end_h = h - 1;

               if(j + num < w)
               {
                  end_w = j + num;
               }
               else
                  end_w = w - 1;
               int count = 0;
               for(int p = new_h; p <= end_h; p++)
               {
                  for(int q = new_w; q <= end_w; q++)
                  {
                     b[count++] = input.At(p,q);
                  }
               }
               temp.At(i,j) = Median(b, count);
            }
         }
         return temp;
      }
   private:
      T2 Median(T2 *a,int m)
      {
         for (int i = 0; i < m; i++)
         {
            for (int j = 1; j < m; j++)
            {
               if(a[i] > a[j])
               {
                  int temp = a[i];
                  a[i] = a[j];
                  a[j] = temp;
               }
            }
         }
         if (m % 2 != 0)
         {
            return a[m / 2];
         }
         else
         {
            return (a[m / 2] + a[m / 2 - 1]) / 2;
         }
      }
};


#endif // FILTER_HPP_INCLUDED
