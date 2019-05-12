#include <opencv2/opencv.hpp>
#include <iostream>
#include "Image.h"

using namespace std;


int main(int argc, char* argv[])
{
	Image img("Lena.jpg"); //��������

	img.Read("Fruits.jpg");
	//img.Write("FruitsCopy.jpg");
	cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);
   img.Show("Image");
	cvWaitKey(0); //�ȴ�����

	img.Flip(false);
	img.Show("���ҷ�ת");
	//ʵ��ͼ������·�ת,��ʾ
	img.Flip(true);
	img.Show("���·�ת");
	//ʵ��ͼ�������,��ʾ
 	img.Resize(false);
  	img.Show("��Сһ��");

 	img.Read("Fruits.jpg");
 	img.Resize(true);
  	img.Show("�Ŵ�һ��");


	//��ȡͼ���ĳ�������ֵ,���޸�
	for (int i = 200; i < 300; i++)
	{
		for (int j = 200; j<300; j++)
		{
			img.Set(i, j, 1);
		}
	}
	img.Show("�ı�����ֵ");

	//ʹ�ÿ������캯�������µĶ���
	Image new_img(img);
	new_img.Show("�µĶ���");

	//��ȡָ�������ڵ�ͼ��,����ʾ
	img.Cut(100, 100, 200, 200);
	cout << "cut" << endl;
	//��תͼ����ʾ�����������ת�Ƕ�Ϊ90�ȵ���������
	img.Rotate(-90);
	img.Show("��ʱ����ת");

	//��ͼ��ľ�ֵ�ͷ���������������
	float mean, variance;
	img.Mean_Variance(mean, variance);
	cout << "ͼ��ľ�ֵ�ͷ���ֱ���" << mean << "  ," << variance << endl;


	//��������ͼ�������
	Image img1("Baboon.jpg");
	Image img2("Lena.jpg");
	img1.Show("Image1");
	img2.Show("Image2");
	cvWaitKey(0); //�ȴ�����

	Swap(img1, img2);
	img1.Show("Image1");
	img2.Show("Image2");
	cvWaitKey(0); //�ȴ�����

	return 0;
}
