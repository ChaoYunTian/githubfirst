#include "MeanFilter.h"
#include "Filter.h"
#include "Matrix.h"

MeanFilter::MeanFilter(int size):Filter(size)
{

}

MeanFilter::~MeanFilter()
{

}

Matrix MeanFilter::Filtering(const Matrix &input)
{

	int h = input.Height();
	int w = input.Width();
	int num = filterSize / 2,new_h,new_w,end_h,end_w;
	Matrix meanfilter(h,w);
	for(int i = 0; i < h; i++)
	{
		for(int j = 0; j < w; j++)
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
			/*new_h = (i - num <= 0)? 0:(i - num);
			new_w = (j - num <= 0)? 0:(j - num);
			end_h = (i + num <= h)? (i + num):(h - 1);
			end_w = (j + num <= w)? (j + num):(w - 1);*/
			int distand = (end_h - new_h + 1) * (end_w - new_w + 1);
			double sum = 0;
			for(int p = new_h; p < end_h; p++)
			{
				for(int q = new_w; q < end_w; q++)
				{
					sum += input.At(p,q);
				}
			}
			meanfilter.At(i,j) = sum / distand;
		}
	}
	return meanfilter;
}




