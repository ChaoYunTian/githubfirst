#include <opencv2/opencv.hpp>
#include "Image.h"
#include <iostream>
using namespace std;

void Image::Alloc(int h, int w)
{
   height = h;
   width = w;
   data = new unsigned char*[height];
   for(int i = 0; i < height; i++)
   {
      data[i] = new unsigned char [width];
   }
}

void Image::Release()
{
  for(int i = 0; i < height; i++)
  {
     delete []data[i];
  }
  delete []data;
}
//构造函数
Image::Image() :height(0), width(0), data(NULL)
{
}

//构造函数重载
Image::Image(int h, int w)
{
	Alloc(h,w);
}

//构造函数重载，创建的图像像素值都为val;
Image::Image(int h, int w, unsigned char val)
{
      Alloc(h,w);
      for(int i = 0; i < height; i++)
      {
         for (int j = 0; j < width; j++)
         {
            data[i][j] = val;
         }
      }
}

//构造函数重载，利用文件名从硬盘加载图像文件成为Image对象;
Image::Image(char* ImageName)
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

//构造函数重载，从一维静态数组创建Image对象，图像的行数和列数由后面两个参数给出;
Image::Image(unsigned char *m, int rows, int cols)
{
	Alloc(rows,cols);
	for (int i = 0; i< height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			data[i][j] = m[i*width + j];
		}
	}
}

//构造函数重载，从静态二维数组创建Image对象，图像的行数（二维数组的第一个维度）由第二个参数rows给出;
Image::Image(unsigned char m[][100], int rows)
{
	Alloc(rows,100);
	for (int i = 0; i< height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			data[i][j] = m[i][j];
		}
	}
}

//构造函数重载，从动态数组（二级指针）创建Image对象，图像的行数和列数由后面两个参数给出;
Image::Image(unsigned char **m, int h, int w)
{
	Alloc(h,w);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			data[i][j] = m[i][j];
		}
	}
}

//拷贝构造函数
Image::Image(const Image &im)
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

//析构函数
Image::~Image()
{
	if (data != NULL)
	{
		Release();
	}
}

//从硬盘读入图像文件;
void Image::Read(char*  ImageName)
{
	IplImage* img = cvLoadImage(ImageName, CV_LOAD_IMAGE_GRAYSCALE);
	unsigned char *img_data = (unsigned char *)(img->imageData);
	int widthstep = img->widthStep;
	height = img->height;
	width = img->width;
   if (data != NULL)
	{
	   if(height != img->height || width != img->width)
      {
         Release();
      }
      Alloc(img->height,img->width);
	}
	for (int i = 0; i< height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			data[i][j] = img_data[i*widthstep + j];
		}
	}

	cvReleaseImage(&img);
}

//保存图像;
void Image::Write(char *filename)
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

//显示图像;
void Image::Show(char* winname)
{
	IplImage *img = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	unsigned char *img_data = (unsigned char *)(img->imageData);
	int widthstep = img->widthStep;

	for (int i = 0; i< height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			img_data[i*widthstep + j] = data[i][j];
		}
	}

	cvNamedWindow(winname, CV_WINDOW_AUTOSIZE);//创建窗口
	cvShowImage(winname, img);
 	cvWaitKey(0);
	cvDestroyWindow(winname);
	cvReleaseImage(&img); //释放图像;
}

//获取图像中指定点的值
unsigned char& Image::At(int row, int col) const
{
	return data[row][col];
}

//设置图像某一点为一值
void Image::Set(int rows, int cols, unsigned char val)
{
	data[rows][cols] = val;
}
//设置图像为同一值
void Image::Set(unsigned char value)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			data[i][j] = value;
		}
	}
}

//false 左右，true 上下;
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
//图像缩小，放大
void Image::Resize(int code)
{
	unsigned char **temp = NULL;
	if (code)
	{
		temp = new unsigned char*[height * 2];
		for (int i = 0; i < height * 2; i++)
		{
			temp[i] = new unsigned char[width * 2];
		}
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				temp[i * 2][j * 2] = data[i][j];
				temp[i * 2 + 1][j * 2] = data[i][j];
				temp[i * 2][j * 2 + 1] = data[i][j];
				temp[i * 2 + 1][j * 2 + 1] = data[i][j];
			}
		}
		Release();
		height *= 2; width *= 2;
		data = temp;
	}
	else
	{
		temp = new unsigned char*[height / 2];
		for (int i = 0; i < height / 2; i++)
		{
			temp[i] = new unsigned char[width / 2];
		}
		for (int i = 0; i < height / 2; i++)
		{
			for (int j = 0; j < width / 2; j++)
			{
				temp[i][j] = data[i * 2][j * 2];
			}
		}
		Release();
		height /= 2, width /= 2;
		data = temp;
	}
}

//图像裁剪的函数
void Image::Cut(int x1, int y1, int x2, int y2)
{
	int t_height = y2 - y1 + 1;
	int t_width = x2 - x1 + 1;
	unsigned char** temp = new unsigned char*[t_height];
	for (int i = 0; i < t_height; i++)
	{
		temp[i] = new unsigned char[t_width];
	}
	for (int i = 0; i < t_height; i++)
	{
		for (int j = 0; j < t_width; j++)
		{
			temp[i][j] = data[x1 + i][y1 + j];
		}
	}
	IplImage *img = cvCreateImage(cvSize(t_width, t_height), IPL_DEPTH_8U, 1);
	unsigned char *img_data = (unsigned char *)(img->imageData);
	int widthstep = img->widthStep;

	for (int i = 0; i< t_height; i++)
	{
		for (int j = 0; j < t_width; j++)
		{
			img_data[i * widthstep + j] = data[i][j];
		}
	}
	cvNamedWindow("CutImage", CV_WINDOW_AUTOSIZE);//创建窗口
	cvShowImage("CutImage", img);
	cvWaitKey(0);
   cvDestroyWindow("CutImage");
	cvReleaseImage(&img);
	for(int i = 0; i< t_height;i++)
   {
      delete []temp[i];
   }
   delete []temp;
}

//图像旋转的函数
void Image::Rotate(int degree)
{
	int times = degree / 90;
	if(times < 0)
      times = (-times);
	for (int i = 0; i < times; i++)
	{
		int t_height = width;
		int t_width = height;
		unsigned char** temp = new unsigned char*[t_height];
		for (int j = 0; j < t_height; j++)
		{
			temp[j] = new unsigned char[t_width];
		}
		for (int m = 0; m < height; m++)		//逆时针旋转
		{
			for (int n = 0; n< width; n++)
			{
				temp[t_height - n - 1][m] = data[m][n];
			}
		}
		Release();
		data = temp;
		height = t_height;
		width = t_width;
	}
}

void Image::Mean_Variance(float &m, float &var)    //求图像的均值和方差，利用参数输出
{
	float sum = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			sum += float(data[i][j]);
		}
	}
	m = sum / (height * width);
	sum = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			sum += ((data[i][j] - m) * (data[i][j] - m));
		}
	}
	var = sum / (height * width);
}


//实现友元函数，交换两个Image对象的数据
void Swap(Image &a, Image &b)
{
	int temp;
	temp = a.height;
	a.height = b.height;
	b.height = temp;
	temp = a.width;
	a.width = b.width;
	b.width = temp;

	unsigned char **t = a.data;
	a.data = b.data;
	b.data = t;
}
