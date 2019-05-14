#include<stdio.h>
#include<stdlib.h>
#include<math.h>
double one(double x)
{
   return sin(x);
}
double two(double x)
{
   return cos(x);
}
double three(double x)
{
   return exp(x);
}
double faust(double a,double b,double (*p)(double))
{
   double step=(b-a)/1000;
   double sum=0,x;
   for(x=a;x<b;x+=step)
      //sum+=step*(p(x));
      sum=sum+((p(x)+p(x+step))*step)/2;
   return sum;
}
int main()
{
   double a,b,sum,(*p)();
   int t,type;
   if(type==0)
      exit(0);
   while(type!=0)
   {
   printf("请从下面3个选择计算的函数：\n");
   printf("1:sin(x)\t2:cos(x)\t3:exp(x)\t0:结束\n");
   printf("你选择的是：");
   scanf("%d",&type);
   while(type<0||type>=4)
   {
      printf("输入错误，请重新输入：");
      scanf("%d",&type);
   }
   switch(type)
   {
      case 1:p=one;break;
      case 2:p=two;break;
      case 3:p=three;break;
      case 0:return 0;
   }
   printf("请输入下极限：");
   scanf("%lf",&a);
   printf("请输入上极限：");
   scanf("%lf",&b);
   if(a>b)
   {
      t=a;a=b;b=t;
   }
   sum=faust(a,b,p);
   printf("第%d种函数积分结果为%f\n",type,sum);
   }

}
/*#include<stdio.h>
#include<math.h>
 void hsin(double a,double b)
{
    double x,y=0,s=(b-a)/1000;
	for(x=a;x<b;x+=s)
	    y+=s*sin(x);
	printf("结果为：%0.6f\n",y);
}
void hcos(double a,double b)
{
    double x,y=0,s=(b-a)/1000;
	for(x=a;x<b;x+=s)
	    y+=s*cos(x);
	printf("结果为：%0.6f\n",y);

}
void hexp(double a,double b)
{
	double x,y=0,s=(b-a)/1000;
	for(x=a;x<b;x+=s)
	    y+=s*exp(x);
	printf("结果为：%0.6f\n",y);
}
int main()
{
	void (*p)(double a,double b);
	int t,m;
	m=1;
	double a,b;
	while(m!=0)
	{
	printf("1.sin(x)\t2.cos(x)\n");
	printf("3.exp(x)\t0.exit\n");
	printf("请选择序号：");
	scanf("%d",&m);
	while((m<0)||(m>3))
	{
	   printf("输入错误！请重新选择");
	   scanf("%d",&m);
    }
	 if(m!=0)
	{
		printf("请输入积分上限和积分下限：");
		scanf("%lf%lf",&a,&b);
		if(m==1)p=hsin;
		if(m==2)p=hcos;
		if(m==3)p=hexp;
		if(a>b)
		{
		   t=a;a=b;b=t;
		}
		(*p)(a,b);
	}
    }
	return 0;
}*/

