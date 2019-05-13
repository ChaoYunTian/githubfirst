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
		cout << "1����ֵ�˲��� " << endl;
		cout << "2: ��ֵ�˲��� " << endl;
		cout << "3: �˳����� " << endl;
		cout << " ��ѡ�������еĲ��� " << endl;
		cin >> number;
		
		if(number == 1)
		{
			cout << "�����˲���nֵ" << endl;
			cin >> n;

			filter = new MeanFilter(n);
			Image result_mean;
			result_mean = filter->Filtering(img);
			result_mean.Show("Mean");
			delete filter;
		}
		else if(number == 2)
		{
			cout << "�����˲���nֵ" << endl;
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