#ifndef MEANFILTER_H
#define MEANFILTER_H
#include "Matrix.h"
#include "Filter.h"

class MeanFilter :public Filter
{
public:
	MeanFilter(int size);
	virtual ~MeanFilter();
	virtual Matrix Filtering(const Matrix &input);	//滤波函数
};

#endif      // MEDIANFILTER_H
