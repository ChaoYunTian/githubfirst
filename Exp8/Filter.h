#ifndef FILTER_H_INCLUDED
#define FILTER_H_INCLUDED

#include "Image.h"
#include "Matrix.h"

class Filter
{
public:
	Filter(int size);	//���캯��
	virtual ~Filter();	//��������

	virtual Matrix Filtering(const Matrix &input) = 0;	//�˲�����

protected:
	int filterSize;
};

#endif // FILTER_H_INCLUDED