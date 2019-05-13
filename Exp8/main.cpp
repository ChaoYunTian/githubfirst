#include "opencv2/opencv.hpp"
#include "Filter.h"
#include "MedianFilter.h"
#include "MeanFilter.h"
#include "Image.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	Image img("Lena_salt_and_pepper.jpg");
	img.Show("Origin");

	Filter *filter = NULL;
	int choose = 1;

	while (1)
	{
		cout << "�˵���" << endl;
		cout << "1����ֵ�˲�" << endl;
		cout << "2����ֵ�˲�" << endl;
		cout << "0���˳�" << endl;
		cout << "���������ѡ��";

		cin >> choose;

		int n;
		if (choose == 1)
		{
			cout << "�������˲�����С����������";
			cin >> n;
			filter = new MeanFilter(n);

			Image result_mean;

			result_mean = filter->Filtering(img);
			result_mean.Show("Mean");
			delete filter;
		}
		else if (choose == 2)
		{
			cout << "�������˲�����С����������";
			cin >> n;
			filter = new MedianFilter(n);

			Image result_median;

			result_median = filter->Filtering(img);
			result_median.Show("Median");
			delete filter;
		}
		else if (choose == 0)
		{
			cout << "�������н�����" << endl;
			break;
		}
	}

	return 0;
}
