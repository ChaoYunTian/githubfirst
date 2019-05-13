#include "cv.h"
#include "highgui.h"
#include "MedianFilter.h"
#include "MeanFilter.h"
#include "Image.h"
#include <iostream>

int mian
{
	Image img("Lena_gaussian.jpg");
	img.show("Origin");

	Filter *filter = NULL;
	
	while(true)
	{ 
		int number,n;
		cout << "1：均值滤波器 " << endl;
		cout << "2: 中值滤波器 " << endl;
		cout << "3: 退出程序 " << endl;
		cout << " 请选择所进行的操作 " << endl;
		cin >> number;
		
		if(number == 1)
		{
			cout << "输入滤波器n值" << endl;
			cin >> n;

			filter = new MeanFilter(n);
			Image result_mean;
			result_mean = filter->Filtering(img);
			result_mean.Show("Mean");
			delete filter;
		}
		else if(number == 2)
		{
			cout << "输入滤波器n值" << endl;
			cin >>n;

			filter = new MedianFilter(n);
			Image result_median;
			result_median = filter->Filtering(img);
			medianfilter.show("Median");
			delete filter;
		}

		else
			exit(0);
	}
	return 0;
}
