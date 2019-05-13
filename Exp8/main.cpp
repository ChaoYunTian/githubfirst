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
		cout << "菜单：" << endl;
		cout << "1，均值滤波" << endl;
		cout << "2，中值滤波" << endl;
		cout << "0，退出" << endl;
		cout << "请输入你的选择：";

		cin >> choose;

		int n;
		if (choose == 1)
		{
			cout << "请输入滤波器大小（奇数）：";
			cin >> n;
			filter = new MeanFilter(n);

			Image result_mean;

			result_mean = filter->Filtering(img);
			result_mean.Show("Mean");
			delete filter;
		}
		else if (choose == 2)
		{
			cout << "请输入滤波器大小（奇数）：";
			cin >> n;
			filter = new MedianFilter(n);

			Image result_median;

			result_median = filter->Filtering(img);
			result_median.Show("Median");
			delete filter;
		}
		else if (choose == 0)
		{
			cout << "程序运行结束！" << endl;
			break;
		}
	}

	return 0;
}

