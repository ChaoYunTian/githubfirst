#ifndef Image_H

#define Image_H

#include "Matrix.h"


class Image: public Matrix
{

public:

    Image(); //无参数的构造函数，创建行列都为零的Image对象

    Image(int h, int w); //构造函数重载，创建h行，w列的Image对象

    Image(int h, int w, unsigned char val); //构造函数重载，创建的图像像素值都为val;

    Image(const char* ImageName); //构造函数重载，利用文件名从硬盘加载图像文件成为Image对象;

    Image(unsigned char m[][100], int n); //构造函数重载，从静态数组创建Image对象;

    Image(unsigned char **m, int h, int w); //构造函数重载，从动态数组创建Image对象;

    Image(const Matrix &m); //构造函数重载，由Matrix类对象构造Image类对象

    Image(const Image &im);//拷贝构造函数;

    ~Image();//析构函数;

    void Read(const char* ImageName); //从硬盘文件中读入图像数据;

    void Write(char* filename); //将图像数据保存为图像文件;

    void Show(const char* winname); //显示图像;

    void Flip(int code); //图像的翻转; code为0左右，1 上下;

    void Resize(int h, int w); //图像的缩放为参数指定的大小

    void Cut(int x1,int y1,int x2,int y2);//裁剪点(x1,y1)到点(x2,y2)的图像

    void Rotate(int degree);//图像旋转的函数（旋转角度为任意角度）

    double Mean();//返回图像的均值

    double Variance();//求图像的方差

    Image operator-();
    Image gray2bw(unsigned char m);
    Image operator-(const Image &m)
    {
       return Matrix::operator-(m);
    }
};

#endif
