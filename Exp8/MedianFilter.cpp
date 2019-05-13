#include "Filter.h"
#include "MedianFilter.h"

MedianFilter::MedianFilter(int size):Filter(size)
{

}

MedianFilter::~MedianFilter()
{

}

int  MedianFilter::Median(double *a, int m)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 1; j < m; j++)
		{
			if (a[i] > a[j])
			{
				int temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
	if (m % 2 != 0)
	{
		return a[m / 2];
	}
	else
	{
		return (a[m / 2] + a[m / 2 - 1]) / 2;
	}
}

Matrix MedianFilter::Filtering(const Matrix &input)
{
	int h = input.Height();
	int w = input.Width();
	Matrix median(h, w);
	int new_h, new_w, end_h, end_w;
	int num = filterSize / 2;
	double *b = new double [filterSize * filterSize]();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if(i - num <= 0)
         {
            new_h = 0;
         }
         else
            new_h = i - num;
         if(j - num <= 0)
         {
            new_w = 0;
         }
         else
            new_w = j - num;

			if(i + num <= h)
         {
            end_h = i + num;
         }
         else
            end_h = h - 1;

			if(j + num <= w)
         {
            end_w = j + num;
         }
         else
            end_w = w - 1;

			int count = 0;
			for (int p = new_h; p < end_h; p++)
			{
				for (int q = new_w; q < end_w; q++)
				{
					b[count++] = input.At(p,q);
				}
			}
			median.At(i,j) = Median(b, count);
		}
	}

	delete[]b;
	return median;
}


