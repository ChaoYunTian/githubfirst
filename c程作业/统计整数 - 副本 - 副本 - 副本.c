#include<stdio.h>
#define N 100
static int count;
int transfer(char *p,int n)
{
	count++;
	int num=0,temp=1;
	for(;n>0;n--)
	{
		num+=(((int)*(p--)-48)*temp);
		temp*=10;
	}
	return num;
}
void F_num(char *p,int *b)
{
	int length=0,i=0;
	for(;*p!='\0'||*(p+1)!='\0';p++)
	{
		if(*p>='0'&&*p<='9')    length++;
		else if(length!=0)
		{
			b[i++]=transfer(p-1,length);
			length=0;
		}
		else continue;
	}
}
int main()
{
	char a[]="A123x456 17960? 302tab5876";
	int b[N];
	F_num(a,b);
	printf("总共有%d个整数\n分别是：",count);
	for(int i=0;i<count;i++)
		printf("%d ",b[i]);
	return 0;
}
