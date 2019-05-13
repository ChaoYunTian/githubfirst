#ifndef FILTER_H_INCLUDED
#define FILTER_H_INCLUDED

#include "Image.h"
#include "Matrix.h"

class Filter
{
public:
	Filter(int size);	//构造函数
	virtual ~Filter();	//析构函数

	virtual Matrix Filtering(const Matrix &input) = 0;	//滤波函数

protected:
	int filterSize;
};

#endif // FILTER_H_INCLUDED
