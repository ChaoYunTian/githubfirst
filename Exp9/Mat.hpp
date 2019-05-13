#ifndef MAT_HPP
#define MAT_HPP
#include<cmath>
#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

template< typename T>
class Mat;

template< typename T>
class Alloc
{
private:

   friend Mat<T>;
	Alloc(int h = 0, int w = 0, T val = 0):height(h), width(w)
	{
		if(h == 0 || w == 0)
		{
			data = NULL;
			refcount = new int(1);
		}
		else
		{
			data = new T* [height];
			for(int i = 0; i < height; ++i)
			{
				data[i] = new T [width];
			}
			if(val != 0)
			{
				for(int i = 0; i < height; ++i)
				{
					for(int j = 0; j < width; ++j)
					{
						data[i][j] = val;
					}
				}
			}
			refcount = new int(1);
		}
	}

	~Alloc()
	{
		if(data != NULL)
		{
			for(int i = 0; i < height; ++i)
			{
				delete []data[i];
			}
			delete []data;
		}
		delete refcount;   //���ü����ͷſռ�
	}

	int height;
	int width;
	T **data;
	int *refcount;   //���ü���
};

template< typename T>
class Mat
{
private:
	T Release()   //���ü����ж��Ƿ�Ҫ�ͷ�
	{
		(*agent->refcount)--;
		if (*agent->refcount == 0)
		{
			delete agent;
			agent = NULL;
			return true;
		}
		return false;
	}

public:
	Mat() //�޲����Ĺ��캯�����������ж�Ϊ���Mat����
	{
		agent = new Alloc<T>();
	}

	Mat(int h, int w) //���캯�����أ�����h�У�w�е�Mat����
	{
		agent = new Alloc<T>(h, w);
	}
	Mat(int h, int w, T val) //���캯�����أ�����Ԫ�ص�ֵ��Ϊval;
	{
		agent = new Alloc<T>(h, w, val);
	}
	Mat(const char* ImageName) //���캯�����أ������ļ�����Ӳ�̼���ͼ���ļ���ΪMat����;
	{
		agent = NULL;
		Read(ImageName);
	}

	Mat(T **m, int h, int w) //���캯�����أ��Ӷ�̬���鴴��Mat����;
	{
		agent = new Alloc<T>(h, w);
		for (int i = 0; i < h; ++i)
		{
			for (int j = 0; j < w; ++j)
			{
				agent->data[i][j] = m[i][j];
			}
		}
	}

	Mat(const Mat &m) //�������캯��;
	{
		if (this != &m)
		{
			agent = m.agent;
			(*agent->refcount)++;
		}
	}

	~Mat() //��������;
	{

	}

	void Read(const char *ImageName) //��Ӳ���ļ��ж���ͼ������;
	{
		if (agent != NULL)
			Release();

		IplImage* img = cvLoadImage(ImageName, CV_LOAD_IMAGE_GRAYSCALE);

		int height = img->height;
		int width = img->width;
		unsigned char *img_data = (unsigned char *)(img->imageData);
		int widthstep = img->widthStep;

		agent = new Alloc<T>(height, width);

		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				agent->data[i][j] = T(img_data[i*widthstep + j]);
			}
		}

		cvReleaseImage(&img);
	}
	void Write(const char *filename) //�����ݱ���Ϊͼ���ļ�;
	{
		IplImage* img = cvCreateImage(cvSize(agent->width, agent->height), IPL_DEPTH_8U, 1);
		unsigned char *img_data = (unsigned char *)(img->imageData);
		int widthstep = img->widthStep;

		for (int i = 0; i < agent->height; ++i)
		{
			for (int j = 0; j < agent->width; ++j)
			{
				img_data[i*widthstep + j] = (unsigned char) (agent->data[i][j]);
			}
		}

		cvSaveImage(filename, img);
		cvReleaseImage(&img);
	}
	void Show(const char *winname)      //��ͼ������ʾ����;
	{
		IplImage* img = cvCreateImage(cvSize(agent->width, agent->height), IPL_DEPTH_8U, 1);

		unsigned char *img_data = (unsigned char *)(img->imageData);
		int widthstep = img->widthStep;

		for (int i = 0; i < agent->height; ++i)
		{
			for (int j = 0; j < agent->width; ++j)
			{
				T temp = agent->data[i][j];

				if (temp > 255)
				{
					temp = 255;
				}
				else if (temp < 0)
				{
					temp = 0;
				}
				img_data[i*widthstep + j] = (unsigned char) (temp);
			}
		}

		cvNamedWindow(winname, CV_WINDOW_AUTOSIZE);
		cvShowImage(winname, img);
		cvWaitKey(0);

		cvDestroyWindow(winname);
		cvReleaseImage(&img);
	}

	int Height()      //�õ�����߶�
	{
		return agent->height;
	}
	int Height() const      //�õ�����߶�
	{
		return agent->height;
	}

	int Width()       //�õ��������
	{
		return agent->width;
	}
	int Width() const       //�õ��������
	{
		return agent->width;
	}

	T& At(int row, int col)          //��ȡĳ���ֵ
	{
	   if(row >= 0 && row < agent->height && col >= 0 && col < agent->width);

         return agent->data[row][col];
	}
	T At(int row, int col) const     //��ȡĳ���ֵ��const����
	{
	   if(row >= 0 && row < agent->height && col >= 0 && col < agent->width);
         return agent->data[row][col];
	}

	void Set(int row, int col, T value)       //����Ԫ��(row,col)Ϊĳֵ;
	{
		agent->data[row][col] = value;
	}
	void Set(T value)       //��������Ԫ��Ϊͬһֵ;
	{
		for (int i = 0; i < agent->height; ++i)
		{
			for (int j = 0; j < agent->wodth; ++j)
			{
				agent->data[i][j] = value;
			}
		}
	}

	void Flip(int code)        //��ת; ����code��ֵ��0:���ҷ�ת��1:���·�ת;
	{
		if (code == 0)
		{
			for (int i = 0; i < agent->height; ++i)
			{
				for (int j = 0; j < agent->width / 2; ++j)
				{
					T temp = agent->data[i][j];
					agent->data[i][j] = agent->data[i][agent->width - 1 - j];
					agent->data[i][agent->width - 1 - j] = temp;
				}
			}
		}
		else if (code == 1)
		{
			for (int i = 0; i < agent->height / 2; ++i)
			{
				T* temp = agent->data[i];
				agent->data[i] = agent->data[agent->height - 1 - i];
				agent->data[agent->height - 1 - i] = temp;

			}
		}
	}
	void Resize(int h, int w)        //����
	{
		Alloc<T> *new_agent = new Alloc<T>(h, w);

		for (int i = 0; i < h; ++i)
		{
			for (int j = 0; j < w; ++j)
			{
				new_agent->data[i][j] = agent->data[i * agent->height / h][j * agent->width / w];
			}
		}

		Release();
		agent = new_agent;
	}

	Mat<T> Cut(int x1, int y1, int x2, int y2)         //�ü���(x1,y1)����(x2,y2)
	{
		int t_height = x2 - x1 + 1;
		int t_width = y2 - y1 + 1;
		Mat<T> temp(t_height, t_width);

		for (int i = 0; i < t_height; ++i)
		{
			for (int j = 0; j < t_width; ++j)
			{
				temp.At(i, j) = agent->data[x1 + i][y1 + j];
			}
		}

		return temp;
	}

	void Transpose() // ת��
	{
		Alloc<T> *new_agent = new Alloc<T>(agent->width, agent->height);

		for (int i = 0; i < agent->width; ++i)
		{
			for (int j = 0; j < agent->height; ++j)
			{
				new_agent->data[i][j] = agent->data[j][i];
			}
		}

		Release();
		agent = new_agent;
	}

	void Rotate(int degree)//��ת
	{
      const double Pi = 3.1415;
      int d = degree;
      if(degree > 90)
      {
         for(int p = degree; p > 90; p-=90)
         {
            Rotate(90);
         }
         d = degree % 90;
      }
      double q = d * Pi / 180.0;
      int t_height,t_width,x,y;
      t_height = int(agent->height * cos(q) + agent->width * sin(q));
      t_width = int(agent->width * cos(q) + agent->height * sin(q));
      Alloc<T> *temp = new Alloc<T>(t_height,t_width);
      for(int i = 0; i < t_height; i++)
      {
         for(int j = 0; j < t_width; j++)
         {
            y = int (j * sin(q) + (i - agent->width * sin(q)) * cos(q));
            x = int (j * cos(q) - (i - agent->width * sin(q)) * sin(q));
            if((x >= 0 && x < agent->width) && (y >= 0 && y < agent->height) )
            {
               temp->data[i][j] = agent->data[y][x];
            }
            else
               temp->data[i][j] = 0;
         }
      }
      Release();
      agent = temp;
	}

	void Reshape(int h, int w) //��Ԫ���������������£�����������б�Ϊ���������Ĵ�С
	{
		if(h * w == (agent->height * agent->width))
      {
         int rows = 0, cols = 0;
         Alloc<T> *new_agent = new Alloc<T>(h, w);

         for (int i = 0; i < h; ++i)
         {
            for (int j = 0; j < w; ++j)
            {
               new_agent->data[i][j] = agent->data[rows][cols++];
               if (cols == agent->width)
               {
                  rows++;
                  cols = 0;
               }
            }
         }

         Release();
         agent = new_agent;
      }
	}

	bool IsEmpty()// �ж��Ƿ�Ϊ�վ���
	{
		if (agent == NULL)
		{
			return false;
		}
		else if (agent->height == 0 || agent->width == 0)
		{
			return false;
		}
		else
		{
			for (int i = 0; i < agent->height; ++i)
			{
				for (int j = 0; j < agent->width; ++j)
				{
					if (agent->data[i][j] != 0)
						return false;
				}
			}
			return false;
		}
	}

	bool IsSquare()// �жϾ����Ƿ�Ϊ����
	{
		return (agent->height == agent->width);
	}

	Mat<T> MajorDiagonal()// �����Խ����ϵ�Ԫ�أ����һ��N��1�еľ���NΪ���Խ�����Ԫ�صĸ���
	{
		if(agent->height == agent->width)
      {
         Mat<T> temp(agent->height, 1);
         for (int i = 0; i < agent->height; ++i)
         {
            temp.At(i, 0) = agent->data[i][i];
         }

         return temp;
      }
	}

	Mat<T> MinorDiagonal()// �󸱶Խ����ϵ�Ԫ�أ����һ��N��1�еľ���NΪ���Խ�����Ԫ�صĸ���
	{
		if(agent->height == agent->width)
      {
         Mat<T> temp(agent->height, 1);
         for (int i = 0; i < agent->height; ++i)
         {
            temp.At(i, 0) = agent->data[i][agent->width - i - 1];
         }

         return temp;
      }
	}

	Mat<T> Row(int n)// ���ؾ���ĵ�n���ϵ�Ԫ�أ����һ��1��N�еľ��������NΪ��n����Ԫ�صĸ���
	{
         Mat<T> temp(1, agent->width);

         for (int i = 0; i < agent->width; ++i)
         {
            temp.At(0, i) = agent->data[n][i];
         }

         return temp;
	}

	Mat<T> Column(int n)// ���ؾ���ĵ�n���ϵ�Ԫ�أ����һ��N��1�еľ��������NΪ��n����Ԫ�صĸ���
	{
		Mat<T> temp(agent->height, 1);

		for (int i = 0; i < agent->height; ++i)
		{
			temp.At(i, 0) = agent->data[i][n];
		}

		return temp;
	}

	void Cat(Mat<T> &m, int code) // ��m�뵱ǰ�������ƴ�ӣ�code����ƴ�ӵķ�ʽ
	{
		Alloc<T> *new_agent = NULL;

		if (code == 0) //��������ƴ��
		{
			new_agent = new Alloc<T>(agent->height, agent->width + m.Width());

			for (int i = 0; i < new_agent->height; ++i)
			{
				for (int j = 0; j < new_agent->width; ++j)
				{
					if (j >= agent->width)
					{
						new_agent->data[i][j] = m.agent->data[i][j - agent->width];
					}
					else
					{
						new_agent->data[i][j] = agent->data[i][j];
					}
				}
			}
		}
		else if (code == 1) //��������ƴ��
		{
			new_agent = new Alloc<T>(agent->height + m.Height(), agent->width);

			for (int i = 0; i < new_agent->height; ++i)
			{
				for (int j = 0; j < new_agent->width; ++j)
				{
					if (i >= agent->height)
					{
						new_agent->data[i][j] = m.agent->data[i - agent->height][j];
					}
					else
					{
						new_agent->data[i][j] = agent->data[i][j];
					}
				}
			}
		}

		Release();
		agent = new_agent;
	}

	void CopyTo(Mat<T> &m) // �������Ƹ�m
	{
		if (this != &m && agent != m.agent)
		{
			m.Release();

			m.agent = new Alloc<T>(agent->height, agent->width);

			for (int i = 0; i < agent->height; ++i)
			{
				for (int j = 0; j < agent->width; ++j)
				{
					m.agent->data[i][j] = agent->data[i][j];
				}
			}
		}
	}

	Mat<T>& operator=(const Mat<T> &m)  //���ظ�ֵ���������ɶ����Ŀ�����
	{
		if (this != &m)
		{
			Release();
			agent = m.agent;
			(*agent->refcount)++;
		}
		return *this;
	}

	bool operator==(const Mat<T> &m)  //�ж�����Mat�����Ƿ����
	{
		if (agent == m.agent)
		{
			return true;
		}
		else
		{
			if (agent->height != m.agent->height || agent->width != m.agent->width)
			{
				return false;
			}
			else
			{
				for (int i = 0; i < agent->height; ++i)
				{
					for (int j = 0; j < agent->width; ++j)
					{
						if (agent->data[i][j] != m.agent->data[i][j])
							return false;
					}
				}
				return true;
			}
		}
	}

	Mat<T> operator+(const Mat<T> &m)  //��ӦԪ�ص���ֵ��ӣ�
	{
		if(agent->height == m.agent->height && agent->width == m.agent->width)
		{
         Mat<T> temp(agent->height, agent->width);

         for (int i = 0; i < agent->height; ++i)
         {
            for (int j = 0; j < agent->width; ++j)
            {
               temp.agent->data[i][j] = agent->data[i][j] + m.agent->data[i][j];
            }
         }
            return temp;
      }
	}

	Mat<T> operator-(const Mat<T> &m)  //��ӦԪ�ص���ֵ�����
	{
		if(agent->height == m.agent->height && agent->width == m.agent->width)
		{
         Mat<T> temp(agent->height, agent->width);
         for (int i = 0; i < agent->height; ++i)
         {
            for (int j = 0; j < agent->width; ++j)
            {
               temp.agent->data[i][j] = agent->data[i][j] - m.agent->data[i][j];
            }
         }
         return temp;
		}
	}

	Mat<T>& operator++()  //ǰ���Լӣ�
	{
		for (int i = 0; i < agent->height; ++i)
		{
			for (int j = 0; j < agent->width; ++j)
			{
				agent->data[i][j] += 1;
			}
		}
		return *this;
	}
	Mat<T>& operator--()  //ǰ���Լ���
	{
		for (int i = 0; i < agent->height; ++i)
		{
			for (int j = 0; j < agent->width; ++j)
			{
				agent->data[i][j] -= 1;
			}
		}
		return *this;
	}
	Mat<T> operator ++(int)  //�����Լӣ�
	{
		Mat<T> temp(*this);
		++(*this);
		return temp;
	}
	Mat<T> operator --(int)  //�����Լ���
	{
		Mat<T> temp(*this);
		--(*this);
		return temp;
	}

	Mat<T> operator-()  // ȡ����ע��Ҫ�Ѿ�������ݹ�����[0,1]���������1��
	{
		for (int i = 0; i < agent->height; ++i)
		{
			for (int j = 0; j < agent->width; ++j)
			{
				agent->data[i][j] = abs(agent->data[i][j] - 255);
			}
		}
		return *this;
	}

	friend Mat<T> operator+(Mat<T> &m, T num) //����Ԫ�ؼ���ͬһ��ֵ;
	{
		Mat<T> temp(m.Height(), m.Width());
		for (int i = 0; i < m.Height(); ++i)
		{
			for (int j = 0; j < m.Width(); ++j)
			{
				temp.At(i,j) = m.At(i,j) + num;
			}
		}
		return temp;
	}
	friend Mat<T> operator-(Mat<T> &m, T num) //����Ԫ�ؼ�ȥͬһ��ֵ;
	{
		Mat<T> temp(m.Height(), m.Width());
		for (int i = 0; i < m.Height(); ++i)
		{
			for (int j = 0; j < m.Width(); ++j)
			{
				temp.At(i, j) = m.At(i, j) - num;
			}
		}
		return temp;
	}
	friend Mat<T> operator*(Mat<T> &m, T num) //����Ԫ�س���ͬһ��ֵ;
	{
		Mat<T> temp(m.Height(), m.Width());
		for (int i = 0; i < m.Height(); ++i)
		{
			for (int j = 0; j < m.Width(); ++j)
			{
				temp.At(i, j) = m.At(i, j) * num;
			}
		}
		return temp;
	}
	friend Mat<T> operator/(Mat<T> &m, T num) //����Ԫ�س���ͬһ��ֵ;
	{
		if(num != 0)
		{
         Mat<T> temp(m.Height(), m.Width());

         for (int i = 0; i < m.Height(); ++i)
         {
            for (int j = 0; j < m.Width(); ++j)
            {
               temp.At(i, j) = m.At(i, j) / num;
            }
         }

         return temp;
		}
	}

	//���⣬����Ԫ������д��һ��T���͵�����һ��Mat����ļ�,��,��,��
	friend Mat<T> operator+(T num, Mat<T> &m)
	{
      Mat<T> temp(m.Height(), m.Width());

      for (int i = 0; i < m.Height(); ++i)
      {
         for (int j = 0; j < m.Width(); ++j)
         {
            temp.At(i, j) = num + m.At(i, j);
         }
      }
		return temp;
	}

	friend Mat<T> operator-(T num, Mat<T> &m)
	{
		Mat<T> sub(m.Height(), m.Width());
		for (int i = 0; i <m.Height(); ++i)
		{
			for (int j = 0; j < m.Width(); ++j)
			{
				sub.At(i,j) = num - m.At(i,j);
			}
		}
		return sub;
	}

	friend Mat<T> operator*(T num, Mat<T> &m)
	{
      Mat<T> temp(m.Height(), m.Width());

      for (int i = 0; i < m.Height(); ++i)
      {
         for (int j = 0; j < m.Width(); ++j)
         {
            temp.At(i, j) = num * m.At(i, j);
         }
      }

		return temp;
	}
	friend Mat<T> operator/(T num, Mat<T> &m)
	{
		Mat<T> temp(m.Height(), m.Width(), num);

		for (int i = 0; i <m.Height(); ++i)
		{
			for (int j = 0; j < m.Width(); ++j)
			{
				if (m.At(i, j) != 0)
				{
					temp.At(i, j) = num / m.At(i, j);
				}
				else
				{
					temp.At(i, j) = 255;
				}
			}
		}

		return temp;
	}

	Mat<T> gray2bw(T t) //�Ը�����ֵt���ж�ֵ�������ؽ������
	{
		Mat<T> temp(agent->height, agent->width);
		for (int i = 0; i < agent->height; ++i)
		{
			for (int j = 0; j < agent->width; ++j)
			{
				if (agent->data[i][j] > t)
				{
					agent->data[i][j] = 255;
				}
				else
				{
					agent->data[i][j] = 0;
				}
			}
		}
		return temp;
	}

	Mat<double> Normalize()//������Ԫ�ص�ֵ�任��0-1��Χ�ڣ���double���͵�Mat���������ע�⣺�����������޷�����Mat<double>���͵Ķ����˽�г�Աdata����Ҫ������At�������ĳ��Ԫ�ء�
	{
		Mat<double> temp(agent->height, agent->width);
		for (int i = 0; i < agent->height; ++i)
		{
			for (int j = 0; j < agent->width; ++j)
			{
				temp.At(i, j) = agent->data[i][j] / 255.0;
			}
		}
	}

	friend void Swap(Mat<T> &a, Mat<T> &b)//ʹ����Ԫ������������Mat����
	{
		Alloc<T> *temp;
		temp = a.agent;
		a.agent = b.agent;
		b.agent = temp;
	}

private:
	Alloc<T> *agent;	// �Լ�ʵ��һ�������࣬��������������������������ü���������ָ��
						// ������Ҫ����ָ�����������ָ����Ϊ���ݳ�Ա
};

#endif