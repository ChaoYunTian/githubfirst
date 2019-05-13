#include <opencv2/opencv.hpp>
#include <iostream>
#include <time.h>
#include "Image.h"
#include "Matrix.h"
using namespace std;
void Matrix::Alloc(int h,int w)
{
   height = h;
   width = w;
   data = new double *[height];
   for(int i = 0; i < height; i++)
   {
      data[i] = new double [width];
   }
}

void Matrix::Alloc(int h,int w,double **t)
{

   t = new double *[h];
   for(int i = 0; i < h; i++)
   {
      t[i] = new double [w];
   }
}

void Matrix::Release()
{
   for(int i = 0; i < height; i++)
   {
     delete []data[i];
   }
   delete []data;
}

Matrix::Matrix():height(0),width(0),data(NULL)
{

}

Matrix::Matrix(int h,int w)
{
   Alloc(h,w);
}

Matrix::Matrix(int h,int w,double val)
{
   Alloc(h,w);
   for(int i = 0; i < height; i++)
   {
      for(int j = 0; j < width; j++)
      {
         data[i][j] = val;
      }
   }
}

Matrix::Matrix(const Matrix &im)
{
   if(data != im.data)
   {
      height = im.height;
      width = im.width;
      Alloc(height,width);
      for(int i = 0; i < height; i++)
      {
         for(int j = 0; j < width; j++)
         {
            data[i][j] = im.data[i][j];
         }
      }
   }
}

Matrix::~Matrix()
{
   if(data != NULL)
   {
      Release();
   }
}

void Matrix::Zeros(int h, int w)
{
   Release();
   Alloc(h,w);
}


void Matrix::Ones(int h, int w)
{
   Alloc(h,w);
   for(int i = 0; i < height; i++)
   {
      for(int j = 0; j < width; j++)
      {
         data[i][j] = 1.0;
      }
   }
}

void Matrix::Random(int h, int w)
{
   Alloc(h,w);
   srand((unsigned int)time(NULL)); //设定随机种子
   for(int i = 0; i < height; i++)
   {
      for(int j = 0; j < width; j++)
      {
         data[i][j] = double(rand())/double(RAND_MAX);
      }
   }
}

void Matrix::Identity(int n)
{
   Alloc(n,n);
   for(int i = 0; i < height; i++)
   {
       for(int j = 0; j < width; j++)
       {
          if(i == j)
          {
             data[i][j] = 1;
          }
          else
            data[i][j] = 0;
       }
   }

}

int Matrix::Height()
{
   return height;
}


int Matrix::Width()
{
   return width;
}

Matrix Matrix::MajorDiagonal()
{
   if(height != width)
   {
      cout << "this is not a square Matrix" << endl;
      return Matrix(0,0);
   }
   else
   {
      Matrix temp(height,1);
      for(int i = 0; i < height; i++)
      {
         for(int j = 0; j < width; j++)
         {
            if(i == j)
               temp.data[i][0] = data[i][j];
            else
               continue;
         }
      }
      return temp;
   }



}

Matrix Matrix::MinorDiagonal()
{
   if(height != width)
   {
      cout << "this is not a square Matrix" <<endl;
      return Matrix();
   }
   else
   {
      Matrix temp(height,1);
      for(int i = 0; i < height; i++)
      {
         for(int j = 0; j < width; j++)
         {
            if(i + j == height)
               temp.data[i][j] = data[i][j];
            else
               continue;
         }
      }
      return temp;
   }

}

Matrix Matrix::Row(int n)
{
   if(n > height)
   {
      cout << "this is not a square Matrix" <<endl;
      return Matrix(1,width);
   }
   else
   {
      Matrix temp(1,width);
      for(int j = 0; j < width; j++)
      {
         temp.data[0][j] = data[n][j];
      }
      return temp;
   }

}

Matrix Matrix::Column(int n)
{
   if(n > width)
   {
      cout << "this is not a squart Matrix" <<endl;
      return Matrix(height,1);
   }
   else
      {
         Matrix temp(height,1);
         for(int i = 0; i < height; i++)
         {
               temp.data[i][0] = data[i][n];
         }
         return temp;
      }
}


void Matrix::Transpose()
{
   double **t = new double *[width];
   for(int i =0 ; i < width; i++)
   {
      t[i] = new double [height];
   }
   for(int i = 0; i < height; i++)
   {
      for(int j = 0; j < width; j++)
      {
         t[i][j] = data[j][i];
      }
   }
   Alloc(height,width);
   int temp = height;
   height = width;
   width = temp;
   data = t;
}

double& Matrix::At(int row, int col)
{
   return data[row][col];
}

void Matrix::Set(int row, int col, double value)
{
   data[row][col] = value;
}

void Matrix::Set(double value)
{
   for(int i = 0; i < height; i++)
   {
      for(int j = 0; j < width; j++)
      {
         data[i][j]= value;
      }
   }
}

void Matrix::Reshape(int h, int w)
{
   int row=0,col=0;
   double **p = new double *[h];
   for(int i = 0; i < h; i++)
   {
      p[i] = new double [w];
   }
   for(int i = 0; i < h; i++)
   {
      for(int j = 0; j < w; j++)
      {
         p[i][j] = data[row][col++];
         if(col == width)
         {
            row += 1;
            col = 0;
         }
      }
   }
   Release();
   Alloc(h,w);
   data = p;
}

bool Matrix::IsEmpty()
{
   if(data == NULL)
      return true;
   else
   {
      for(int i = 0; i < height; i++)
      {
         for(int j = 0; j < width; j++)
         {
            if(data[i][j] != 0)
               return false;
         }
      }
         return true;
   }
}


bool Matrix::IsSquare()
{
   if(height == width)
      return true;
   else
      return false;
}

void Matrix::CopyTo(Matrix &m)
{
   m.height = height;
   m.width = width;
   Alloc(m.height,m.width);
   for(int i = 0; i < height; i++)
   {
      for(int j = 0; j < width; j++)
      {
         m.data[i][j] = data[i][j];
      }
   }
}

void Matrix::Mul(double s)
{
   for(int i = 0; i < height; i++)
   {
      for(int j = 0; j < width; j++)
      {
         data[i][j] = data[i][j]*s;
      }
   }
}

void Matrix::Cat(Matrix &m, int code)
{
   int t_height = 0;
   int t_width = 0;
   double **t = NULL;
   if(code < 5 && code > 0)
   {

      if(code == 1)       //接在右端
      {
         t_height = (m.height > height)? m.height:height;
         t_width = m.width + width;
         Alloc(t_height,t_width,t);
         cout << "1" << endl;
         for(int i = 0; i < t_height; i++)
         {
            for(int j = 0; j < width; j++)
            {
               t[i][j] = data[i][j];
            }
         }
         for(int i =0; i < t_height; i++)
         {
            for(int j = width; j < t_width; j++)
            {
               t[i][j] = m.data[i][j - width];
            }
         }
      }
         /*else if(code == 2)      //接到上端
         {
            t_height = m.height + height;
            t_width = (m.width > width) ? m.width:width;
            Alloc(t_height,t_width,t);
            for(int i = 0; i < m.height; i++)
            {
               for(int j = 0; j < m.width; j++)
               {
                  t[i][j] = m.data[i][j];
               }
            }
            for(int i = height; i < t_height; i++)
            {
               for(int j = 0; j < width; j++)
               {
                  t[i][j] = data[i - height][j];
               }
            }
         }
         else if(code == 3)      //接到左端
         {
            t_height = (m.height > height)?m.height:height;
            t_width = m.width + width;
            Alloc(t_height,t_width,t);
            for(int i = 0; i < t_height; i++)
            {
               for(int j = 0; j < m.width; j++)
               {
                  t[i][j] = m.data[i][j];
               }
            }
            for(int i = 0; i < t_height; i++)
            {
               for(int j = m.width; j < t_width; j++)
               {
                  t[i][j] = data[i][j - m.width];
               }
            }*/

         if(code == 2)     //接到下端
         {
            t_height = m.height + height;
            t_width = (m.width > width)? m.width:width;
            Alloc(t_height,t_width,t);
            for(int i = 0; i < height; i++)
            {
               for(int j = 0; j < width; j++)
               {
                  t[i][j] = data[i][j];
               }
            }
            for(int i = height; i < t_height; i++)
            {
               for(int j = 0; j < m.width; j++)
               {
                  t[i][j] = m.data[i - height][j];
               }
            }
         }
         Release();
         height = t_height;
         width = t_width;
         data = t;

      }
}

Matrix Add(const Matrix &m1, const Matrix &m2)
{
   if(m1.height != m2.height || m1.width != m2.width)
   {
      cout <<" this Matrix is not sum " << endl;
      return Matrix();
   }
   else
   {
      Matrix temp(m1.height,m1.width);
      for(int i = 0; i < m1.height; i++)
      {
         for(int j = 0; j < m1.width; j++)
         {
            temp.data[i][j] = m1.data[i][j] + m2.data[i][j];
            if(temp.data[i][j] > 255)
               temp.data[i][j] = 255;
         }
      }
      return temp;
   }
}

Matrix Sub(const Matrix &m1, const Matrix &m2)
{
   if(m1.height != m2.height || m1.width != m2.width)
   {
      cout << " this Matrix is not reduce " << endl;
      return Matrix();
   }
   else
   {
      Matrix temp(m1.height,m1.width);
      for(int i = 0; i < m1.height; i++)
      {
         for(int j = 0; j < m1.width; j++)
         {
            temp.data[i][j] = m1.data[i][j] - m2.data[i][j];
            if(temp.data[i][j] < 0)
               temp.data[i][j] = 0;
         }
      }
      return temp;
   }
}

void Swap(Matrix &a, Matrix &b)
{
   if(a.height != b.height || a.width != b.width)
   {
      cout << " this Matrix is not swap " << endl;
   }
   else
   {
      int temp = a.height;
      a.height = b.height;
      b.height = temp;

      temp = a.width;
      a.width = b.width;
      b.width = temp;

      double **t = a.data;
      a.data = b.data;
      b.data = t;

   }
}

Matrix& Matrix::operator=(const Matrix &m)
{
   if(&m != this)
   {
      Release();
      height = m.height;
      width = m.width;
      Alloc(height,width);
      for(int i = 0; i < m.height; i++)
      {
         for(int j = 0; j < m.width; j++)
         {
            data[i][j] = m.data[i][j];
         }
      }
   }
   return *this;
}
bool Matrix::operator==(const Matrix &m)
{
   if(height != m.height || width != m.width)
      return false;
   else
      for(int i = 0; i < height; i++)
      {
         for(int j = 0; j < width; j++)
         {
            if(data[i][j] != m.data[i][j])
            {
               return false;
            }
            else
               return true;
         }
      }
}

Matrix Matrix::operator+(const Matrix &m)
{
   if(height != m.height || width != m.width)
   {
      return Matrix();
   }
   else
   {
      Matrix temp(height,width);
      for(int i = 0; i < height; i++)
      {
         for(int j = 0; j < width; j++)
         {
            temp.data[i][j] = data[i][j] + m.data[i][j];
          }
      }
      return temp;
   }
}
Matrix Matrix::operator-(const Matrix &m)
{
   if(height != m.height || width != m.width)
   {
      return Matrix();
   }
   else
   {

      Matrix temp(height,width);
      for(int i = 0; i < height; i++)
      {
         for(int j = 0; j < width; j++)
         {
            temp.data[i][j] = data[i][j] - m.data[i][j];
         }
      }
      return temp;
   }

}

Matrix Matrix::operator*(const Image &img)
{
   if(height != img.height || width != img.width)
   {
      cout <<"can't *"<< endl;
   }
   else
   {
      double **t;
      Alloc(height,width,t);
      for(int i = 0; i < height; i++)
      {
         for(int j = 0; j < width; j++)
         {
            t[i][j] = data[i][j] * img.data[i][j];
         }
      }
      Release();
      height = img.height;
      width = img.width;
      data = t;
   }
}

Matrix Matrix::operator/(const Image &img)
{
   if(height != img.height || width != img.width)
   {
      cout << "can't /" << endl;
   }
   else
   {
      double **t;
      Alloc(height,width);
      for(int i = 0; i < height; i++)
      {
         for(int j = 0; j < width; j++)
         {
            if(img.data[i][j] != 0)
               t[i][j] = data[i][j] / img.data[i][j];
            else
            {
               img.data[i][j] = img.data[i][j] + 1;
               t[i][j] = data[i][j] / img.data[i][j];
            }
         }
      }
      Release();
      height = img.height;
      width = img.width;
      data = t ;
   }
}


Matrix& Matrix::operator++()
{
   for(int i = 0; i < height; i++)
   {
      for(int j = 0; j < width; j++)
      {
         data[i][j] = data[i][j] + 1.0;
      }
   }
   return *this;
}

Matrix& Matrix::operator--()
{
   for(int i = 0; i < height; i++)
   {
      for(int j = 0; j < width; j++)
      {
         data[i][j] = data[i][j] - 1.0;
      }
   }
   return *this;
}

Matrix Matrix::operator++(int)
{
   Matrix temp(*this);
   ++(*this);
   return *this;
}

Matrix Matrix::operator--(int)
{
   Matrix temp(*this);
   --(*this);
   return *this;
}


Matrix operator+(Matrix &m, double num)
{
   Matrix temp(m);
   for(int i = 0; i < m.height; i++)
   {
      for(int j = 0; j < m.width; j++)
      {
         temp.data[i][j] = temp.data[i][j] + num;
      }
   }
   return temp;
}

Matrix operator-(Matrix &m,double num)
{
   Matrix temp(m);
   for(int i = 0; i < m.height; i++)
   {
      for(int j = 0; j < m.width; j++)
      {
         temp.data[i][j] = temp.data[i][j] - num;
      }
   }
   return temp;
}

Matrix operator*(Matrix &m,double num)
{
   Matrix temp(m);
   for(int i = 0; i < m.height; i++)
   {
      for(int j = 0; j < m.width; j++)
      {
         temp.data[i][j] = temp.data[i][j] * num;
      }
   }
   return temp;
}

Matrix operator/(Matrix &m,double num)
{
   Matrix temp(m);
   for(int i = 0; i < m.height; i++)
   {
      for(int j = 0; j < m.width; j++)
      {
         temp.data[i][j] = temp.data[i][j] / num;
      }
   }
   return temp;
}
