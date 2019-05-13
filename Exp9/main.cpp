#include <opencv2/opencv.hpp>
#include "Mat.hpp"
#include "Filter.hpp"
#include <iostream>


int main(int argc, char *argv[])
{
    Mat<double> img1("lena.jpg");
    img1.Resize(140,240);
    img1.Show("缩放图像显示");

    (-img1).Show("取反图像");
    for(int i = 60; i < 100;i++)
    {
       for(int j = 60; j < 100; j++)
       {
          img1.At(i,j) = 0;
       }
    }
    img1.Show("获取元素的值并该变一部分");

    //旋转，裁剪，缩放，重组测试

    img1.Read("Lena.jpg");
	 img1.Resize(140, 240);
	 img1.Rotate(60);
	 img1.Show("旋转60°");

	 img1.Read("Lena.jpg");
	 img1.Resize(140,240);
	 img1.Show("缩放图像");
	 img1.Cut(50,100,100,150);

    img1.Read("Lena.jpg");
	 img1.Reshape(240,140);
	 img1.Show("2");

	 //进行加减操作
 	 Mat<double> img2;
	 img2 = img1 + 2.0;
  	 img2.Show("img1+2.0");

	 img2 = img1 - 1.5;
	 img2.Show("img1-1.5");

	 img2 = img1 * 2.6;
	 img2.Show("img1*2.6");

	 img2 = img1 / 3.0;
	 img2.Show("img1/3.0");

	 img2 = 1.8 + img1;
	 img2.Show("1.8+img1");

	 img2 = 2.3 * img1;
	 img2.Show("2.3*img1");

	 img1.CopyTo(img2);
	 for(int i = 0; i < 10; i++)
    {
       ++img2;
    }
	 img2.Show("自加10次");

	 img1.CopyTo(img2);
	 for(int i = 0; i < 10; i++)
    {
       img2--;
    }
    img2.Show("减10次");

    //对矩阵进行滤波，显示并保存成图像文件
    Mat<double> img3("Lena_salt_and_pepper.jpg");
    img3.Show("Origin");
    Filter<double> *filter = NULL;
    filter = new MeanFilter<double>(3);
    Mat<double> result_mean = filter->Filtering(img3);   //.Show("MeanFilter - 3")
    result_mean.Show("Mean");
    delete filter;

    filter = new MedianFilter<double>(3);
    Mat<double> result_median = filter->Filtering(img3);
    result_median.Show("Median");
    Mat<double> img5 = result_mean - result_median;
    img5.Show("滤波前后图像差");
    delete filter;
    return 0;
}



