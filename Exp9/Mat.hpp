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
		delete refcount;   //引用计数释放空间
	}

	int height;
	int width;
	T **data;
	int *refcount;   //引用计数
};

template< typename T>
class Mat
{
private:
	T Release()   //引用计数判断是否要释放
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
	Mat() //无参数的构造函数，创建行列都为零的Mat对象
	{
		agent = new Alloc<T>();
	}

	Mat(int h, int w) //构造函数重载，创建h行，w列的Mat对象
	{
		agent = new Alloc<T>(h, w);
	}
	Mat(int h, int w, T val) //构造函数重载，矩阵元素的值都为val;
	{
		agent = new Alloc<T>(h, w, val);
	}
	Mat(const char* ImageName) //构造函数重载，利用文件名从硬盘加载图像文件成为Mat对象;
	{
		agent = NULL;
		Read(ImageName);
	}

	Mat(T **m, int h, int w) //构造函数重载，从动态数组创建Mat对象;
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

	Mat(const Mat &m) //拷贝构造函数;
	{
		if (this != &m)
		{
			agent = m.agent;
			(*agent->refcount)++;
		}
	}

	~Mat() //析构函数;
	{

	}

	void Read(const char *ImageName) //从硬盘文件中读入图像数据;
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
	void Write(const char *filename) //将数据保存为图像文件;
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
	void Show(const char *winname)      //用图像来显示矩阵;
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

	int Height()      //得到矩阵高度
	{
		return agent->height;
	}
	int Height() const      //得到矩阵高度
	{
		return agent->height;
	}

	int Width()       //得到矩阵宽度
	{
		return agent->width;
	}
	int Width() const       //得到矩阵宽度
	{
		return agent->width;
	}

	T& At(int row, int col)          //获取某点的值
	{
	   if(row >= 0 && row < agent->height && col >= 0 && col < agent->width);

         return agent->data[row][col];
	}
	T At(int row, int col) const     //获取某点的值，const重载
	{
	   if(row >= 0 && row < agent->height && col >= 0 && col < agent->width);
         return agent->data[row][col];
	}

	void Set(int row, int col, T value)       //设置元素(row,col)为某值;
	{
		agent->data[row][col] = value;
	}
	void Set(T value)       //设置所有元素为同一值;
	{
		for (int i = 0; i < agent->height; ++i)
		{
			for (int j = 0; j < agent->wodth; ++j)
			{
				agent->data[i][j] = value;
			}
		}
	}

	void Flip(int code)        //翻转; 根据code的值：0:左右翻转，1:上下翻转;
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
	void Resize(int h, int w)        //缩放
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

	Mat<T> Cut(int x1, int y1, int x2, int y2)         //裁剪点(x1,y1)到点(x2,y2)
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

	void Transpose() // 转置
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

	void Rotate(int degree)//旋转
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

	void Reshape(int h, int w) //在元素总数不变的情况下，将矩阵的行列变为参数给定的大小
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

	bool IsEmpty()// 判断是否为空矩阵
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

	bool IsSquare()// 判断矩阵是否为方阵
	{
		return (agent->height == agent->width);
	}

	Mat<T> MajorDiagonal()// 求主对角线上的元素，输出一个N行1列的矩阵，N为主对角线上元素的个数
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

	Mat<T> MinorDiagonal()// 求副对角线上的元素，输出一个N行1列的矩阵，N为副对角线上元素的个数
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

	Mat<T> Row(int n)// 返回矩阵的第n行上的元素，组出一个1行N列的矩阵输出，N为第n行上元素的个数
	{
         Mat<T> temp(1, agent->width);

         for (int i = 0; i < agent->width; ++i)
         {
            temp.At(0, i) = agent->data[n][i];
         }

         return temp;
	}

	Mat<T> Column(int n)// 返回矩阵的第n列上的元素，组出一个N行1列的矩阵输出，N为第n列上元素的个数
	{
		Mat<T> temp(agent->height, 1);

		for (int i = 0; i < agent->height; ++i)
		{
			temp.At(i, 0) = agent->data[i][n];
		}

		return temp;
	}

	void Cat(Mat<T> &m, int code) // 将m与当前对象进行拼接，code代表拼接的方式
	{
		Alloc<T> *new_agent = NULL;

		if (code == 0) //代表左右拼接
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
		else if (code == 1) //代表上下拼接
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

	void CopyTo(Mat<T> &m) // 将矩阵复制给m
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

	Mat<T>& operator=(const Mat<T> &m)  //重载赋值运算符，完成对象间的拷贝；
	{
		if (this != &m)
		{
			Release();
			agent = m.agent;
			(*agent->refcount)++;
		}
		return *this;
	}

	bool operator==(const Mat<T> &m)  //判断两个Mat对象是否相等
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

	Mat<T> operator+(const Mat<T> &m)  //对应元素的数值相加；
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

	Mat<T> operator-(const Mat<T> &m)  //对应元素的数值相减；
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

	Mat<T>& operator++()  //前置自加；
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
	Mat<T>& operator--()  //前置自减；
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
	Mat<T> operator ++(int)  //后置自加；
	{
		Mat<T> temp(*this);
		++(*this);
		return temp;
	}
	Mat<T> operator --(int)  //后置自减；
	{
		Mat<T> temp(*this);
		--(*this);
		return temp;
	}

	Mat<T> operator-()  // 取反；注意要把矩阵的数据规整到[0,1]区间后，再用1减
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

	friend Mat<T> operator+(Mat<T> &m, T num) //所有元素加上同一数值;
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
	friend Mat<T> operator-(Mat<T> &m, T num) //所有元素减去同一数值;
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
	friend Mat<T> operator*(Mat<T> &m, T num) //所有元素乘上同一数值;
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
	friend Mat<T> operator/(Mat<T> &m, T num) //所有元素除以同一数值;
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

	//另外，用友元函数再写出一个T类型的数和一个Mat对象的加,减,乘,除
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

	Mat<T> gray2bw(T t) //以给定阈值t进行二值化，返回结果对象
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

	Mat<double> Normalize()//将矩阵元素的值变换到0-1范围内，以double类型的Mat对象输出。注意：在这个函数里，无法访问Mat<double>类型的对象的私有成员data，需要调用其At函数获得某个元素。
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

	friend void Swap(Mat<T> &a, Mat<T> &b)//使用友元函数交换两个Mat对象
	{
		Alloc<T> *temp;
		temp = a.agent;
		a.agent = b.agent;
		b.agent = temp;
	}

private:
	Alloc<T> *agent;	// 自己实现一个代理类，来管理矩阵的行数、列数、引用计数和数据指针
						// 这里需要声明指向代理类对象的指针作为数据成员
};

#endif
