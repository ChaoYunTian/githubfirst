#include <opencv2/opencv.hpp>

#include <iostream>

#include <cmath>

#include "Image.h"

using namespace std;

Image::Image():Matrix()
{

}

Image::Image(int h,int w): Matrix(h, w)
{

}

Image::Image(int h,int w, unsigned char val)
{
   Alloc(h,w);
   for(int i = 0; i < h; i++)
   {
      for(int j = 0; j < w; j++)
      {
         data[i][j] = val;
      }
   }
}

Image::Image(const char* ImageName)    //构造函数重载，利用文件名从硬盘加载图像文件成为Image对象;
{
   Read(ImageName);
}

Image::Image(unsigned char m[][100], int n)     //构造函数重载，从静态数组创建Image对象;
{
   Alloc(n,100);
   for(int i = 0; i < height; i++)
   {
      for(int j = 0; j < width; j++)
      {
         data[i][j] = m[i][j];
      }
   }

}

Image::Image(unsigned char **m, int h, int w)      //构造函数重载，从动态数组创建Image对象;
 {
    Alloc(h,w);
    for(int i = 0; i < height; i++)
    {
       for(int j = 0; j < width; j++)
       {
          data[i][j] = m[i][j];
       }
    }
 }

Image::Image(const Matrix &m):Matrix(m)  //构造函数重载，由Matrix类对象构造Image类对象
{

}

Image::Image(const Image &im)    //拷贝构造函数;
{
   if (data != im.data)
	{
		height = im.height;
		width = im.width;
		Alloc(height,width);
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				data[i][j] = im.data[i][j];
			}
		}
	}
}

Image::~Image()
{

}

void Image::Read(const char* ImageName)
{
   IplImage* img = cvLoadImage(ImageName, CV_LOAD_IMAGE_GRAYSCALE);
	height = img->height;
	width = img->width;
	unsigned char *img_data = (unsigned char *)(img->imageData);
	int widthstep = img->widthStep;

	Alloc(height,width);

	for (int i = 0; i< height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			data[i][j] = img_data[i*widthstep + j];
		}
	}
	cvReleaseImage(&img);
}

void Image::Write(char* filename)
{
   IplImage* img = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	unsigned char *img_data = (unsigned char *)(img->imageData);
	int widthstep = img->widthStep;

	for (int i = 0; i< height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			img_data[i*widthstep + j] = data[i][j];
		}
	}

	cvSaveImage(filename, img);
	cvReleaseImage(&img);
}

void Image::Show(const char* winname)
{
   IplImage *img = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	unsigned char *img_data = (unsigned char *)(img->imageData);
	int widthstep = img->widthStep;

	for (int i = 0; i< height; i++)
	{
		for (int j = 0; j < width; j++)
		{
		   unsigned char temp;
		   if(data[i][j] > 255)
            temp = 255;
         else if(data[i][j] < 0)
            temp = 0;
         else
            temp = data[i][j];
			img_data[i*widthstep + j] = temp;
		}
	}

	cvNamedWindow(winname, CV_WINDOW_AUTOSIZE);
	cvShowImage(winname, img);
 	cvWaitKey(0);
	cvDestroyWindow(winname);
	cvReleaseImage(&img);
}

void Image::Flip(int code)
{
   if (code)
	{
		for (int i = 0; i < height / 2; i++)
		{
			for (int j = 0; j < width; j++)
			{
				unsigned char temp = data[i][j];
				data[i][j] = data[height - i - 1][j];
				data[height - i - 1][j] = temp;
			}
		}
	}
	else
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width / 2; j++)
			{
				unsigned char temp = data[i][j];
				data[i][j] = data[i][width - j - 1];
				data[i][width - j - 1] = temp;
			}
		}
	}
}

void Image::Resize(int h, int w)
{
   double **t_data;
   Alloc(h,w,t_data);
   for(int i = 0; i < h ; i++)
   {
      for(int j = 0; j < w ; j++)
      {
         t_data[i][j] = data[i * height / h][j * width / w];
      }
   }
   Release();
   height = h;
   width = w;
   data = t_data;
}

void Image::Cut(int x1,int y1,int x2,int y2)
{
   int t_height = y2 - y1 + 1;
   int t_width = x2 -x1 + 1;

	double **t_data = new double*[t_height];
	Alloc(t_height,t_width,t_data);
	for (int i = 0; i < t_height; i++)
	{
		for (int j = 0; j < t_width; j++)
		{
			t_data[i][j] = data[x1 + i][y1 + j];
		}
	}
	Release();
	height = t_height;
	width = t_width;
	data = t_data;
}

void Image::Rotate(int degree)
{
   const double Pi = 3.1415;
   int d = degree;
   if(degree > 90)
   {
      for(int i = degree; i > 90; i-=90)
      {
         Rotate(90);
      }
      d = degree % 90;
   }
   double q = d * Pi / 180.0;
   int t_height,t_width,x,y;
   t_height = int(height * cos(q) + width * sin(q));
   t_width = int(width * cos(q) + height * sin(q));
   double **t_data = new double*[t_height];
   Alloc(t_height,t_width,t_data);
   for(int i = 0; i < t_height; i++)
   {
      for(int j = 0; j < t_width; j++)
      {
         y = int (j * sin(q) + (i -width * sin(q)) * cos(q));
         x = int (j * cos(q) - (i - width * sin(q)) * sin(q));
         if((x >= 0 && x < height) && (y >= 0 && y < width) )
         {
            t_data[i][j] = data[y][x];
         }
         else
            t_data[i][j] = 0;
      }
   }
   Release();
   height = t_height;
   width = t_width;
   data = t_data;
}

double Image::Mean()
{
   double sum = 0,sum1 = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			sum += double(data[i][j]);
		}
	}
	sum1 = sum / (height * width);
	return sum1;
}

double Image::Variance()
{
   double sum = 0,sum2 = 0;
   double m = this->Mean();
   for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			sum += ((data[i][j] - m) * (data[i][j] - m));
		}
	}
	sum2 = (sum / (height * width));
	return sum2;
}

Image Image::operator-()      //对图像取反，像素值归为[0,1],每个像素值减1.0；
{
   Image temp(height, width);
   for(int i = 0; i < height; i++)
   {
      for(int j = 0; j < width; j++)
      {
         temp.data[i][j] = 255 - data[i][j];
      }
   }
   return temp;
}


Image Image::gray2bw(unsigned char m)     //以给的阀值t对图像进行二值化，返回结果图像对象
{
   Image temp = *this;
   for(int i = 0; i < height; i++)
   {
      for(int j = 0; j < width; j++)
      {
         temp.data[i][j] =(temp.data[i][j] > m)? 0:255;
      }
   }
   return temp;
}

