#include <opencv2/opencv.hpp>
#include <iostream>
#include "Image.h"

using namespace std;


int main(int argc, char* argv[])
{
	Image img("Lena.jpg"); //创建对象

	img.Read("Fruits.jpg");
	//img.Write("FruitsCopy.jpg");
	cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);
   img.Show("Image");
	cvWaitKey(0); //等待按键

	img.Flip(false);
	img.Show("左右翻转");
	//实现图像的上下翻转,显示
	img.Flip(true);
	img.Show("上下翻转");
	//实现图像的缩放,显示
 	img.Resize(false);
  	img.Show("缩小一倍");

 	img.Read("Fruits.jpg");
 	img.Resize(true);
  	img.Show("放大一倍");


	//获取图像的某点的像素值,并修改
	for (int i = 200; i < 300; i++)
	{
		for (int j = 200; j<300; j++)
		{
			img.Set(i, j, 1);
		}
	}
	img.Show("改变像素值");

	//使用拷贝构造函数创建新的对象
	Image new_img(img);
	new_img.Show("新的对象");

	//截取指定区域内的图像,并显示
	img.Cut(100, 100, 200, 200);
	cout << "cut" << endl;
	//旋转图像并显示（简单起见，旋转角度为90度的整数倍）
	img.Rotate(-90);
	img.Show("逆时针旋转");

	//求图像的均值和方差，并在命令行输出
	float mean, variance;
	img.Mean_Variance(mean, variance);
	cout << "图像的均值和方差分别是" << mean << "  ," << variance << endl;


	//交换两个图像的数据
	Image img1("Baboon.jpg");
	Image img2("Lena.jpg");
	img1.Show("Image1");
	img2.Show("Image2");
	cvWaitKey(0); //等待按键

	Swap(img1, img2);
	img1.Show("Image1");
	img2.Show("Image2");
	cvWaitKey(0); //等待按键

	return 0;
}

