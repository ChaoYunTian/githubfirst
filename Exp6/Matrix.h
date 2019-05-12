#ifndef Matrix_H
#define Matrix_H

class Matrix
{
	public:
		void Alloc(int height, int width);
		void Alloc(int h,int w,double **&t);
		void Release();

		Matrix();
		Matrix(int h,int w);
		Matrix(int h, int w, double val);
		Matrix(const Matrix &m);
		~Matrix();

		void Zeros(int h, int w); // 根据参数产生h行w列的全零矩阵
		void Ones(int h, int w); // 根据参数产生h行w列的全1矩阵
		void Random(int h, int w); //产生h行w列的随机矩阵，矩阵的元素为[0,1]之间的随机实数（double类型）
		void Identity(int n); // 根据参数产生n行n列的单位矩阵

		int Height();  // 获得矩阵的行数
		int Width();   // 获得矩阵的列数
		Matrix MajorDiagonal();// 求矩阵主对角线上的元素，输出一个N行1列的矩阵，N为主对角线元素的个数
		Matrix MinorDiagonal();// 求矩阵的副对角线上的元素，输出一个N行1列的矩阵，N为副对角线上元素的个数
		Matrix Row(int n);// 返回矩阵的第n行上的元素，组出一个1行N列的矩阵输出，N为第n行上元素的个数
		Matrix Column(int n);// 返回矩阵的第n列上的元素，组出一个N行1列的矩阵输出，N为第n列上元素的个数

		void Transpose(); // 将矩阵转置

		double& At(int row, int col); //获取第row行第col列的矩阵元素的值
		void Set(int row, int col, double value); //设置第row行第col列矩阵元素的值为value
		void Set(double value); //设置矩阵所有元素为同一值value


		void Reshape(int h, int w); //在矩阵元素总数不变的情况下，将矩阵行列变为参数给定的大小
		bool IsEmpty();// 判断矩阵是否为空矩阵
		bool IsSquare();// 判断矩阵是否为方阵
		void CopyTo(Matrix &m); // 将矩阵复制给m
		void Mul(double s); // 矩阵的每个元素都乘以参数s
		void Cat(Matrix &m, int code); // 将矩阵m与当前矩阵进行拼接，code代表拼接的方式：将m拼接到当前矩阵的上、下、左、右，具体例子见本大纲后面的说明

		friend Matrix Add(const Matrix &m1, const Matrix &m2); // 友元函数，将矩阵m1和m2相加，结果矩阵作为函数的返回值
		friend Matrix Sub(const Matrix &m1, const Matrix &m2); // 友元函数，将矩阵m1和m2相减，结果矩阵作为函数的返回值
		friend void Swap(Matrix &a, Matrix &b); // 友元函数，交换两个矩阵

	protected:
		int height;
		int width;
		double **data;
};

#endif
