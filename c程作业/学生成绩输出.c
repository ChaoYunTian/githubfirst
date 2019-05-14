#include<stdio.h>
#include<stdlib.h>
#define N 1
#define M 1

struct Date					//	定义日期结构体，以便储存学生出生日期；
{
	int year;
	int month;
	int day;
};
typedef struct				//定义学生信息结构体；
{
	long num;				//学号；
	char name[20];			//记录姓名；
	char sex[3];			//记录性别；
	struct Date birth;		//记录出生日期；
	float score[M];			//记录学生M门成绩信息；
	float aver;				//记录学生平均成绩;
}Stu;
void data_get(Stu *p)		//从文件中获取学生信息；
{
	char filename[20];
	FILE *fp;
	//fp=fopen("1.txt","rb");
	//fread(p,sizeof(Stu),N,fp);
	printf("请输入文件路径：");
	scanf("%s",filename);
	getchar();
	if((fp=fopen(filename,"rb")) == NULL)
	{
		printf("打开文件文件失败,请检查文件路径是否正确！\n");
		exit(0);
	}
	int i;
	for(i=0;i<N;i++)
	{
		if(fread(p+i,sizeof(Stu),1,fp) != 1)
		 	printf("文件读取失败!\n");
	}
	int n=fread(p,sizeof(Stu),N,fp);
	/*if(n!=N)
	{
		printf("文件读取部分失败！\n");
		exit(0);
	 }*/
	fclose(fp);
	printf("文件信息读取成功！\n");
}
void sort(Stu *s,Stu *p[N])					//对学生信息按照学生成绩的平均分数排序；
{
	int i,j,k;
	for(i=0;i<N-1;i++)
	{
		k=i;
		for(j=0;j<N-i;j++)
		{
			if(((s+k)->aver) <= ((s+j)->aver))
				k=j;
		}
		if(k!=i)
		{
			Stu *temp;
			temp=p[k];
			p[k]=p[i];
			p[i]=temp;
		}
	}
}
void print(Stu *p[])				//输出学生信息；
{
	int i;
	printf("%-4s%-10s%-10s%-5s%-14s","序号","学号","姓名","性别","出生日期");
	for(i=0;i<M;i++) printf("课程%-4d",i+1);
	printf("%-s","平均成绩\n");
	for(i=0;i<N;i++)
	{
		printf("%-4d",i+1);
		printf("%-10ld",(*(p+i))->num);
		printf("%-10s",(*(p+i))->name);
		printf("%-5s",(*(p+i))->sex);
		printf("%d-%.2d-%-10.2d",(*(p+i))->birth.year,(*(p+i))->birth.month,(*(p+i))->birth.day);
		int j;
		for(j=0;j<M;j++)
			printf("%-8.1f",(*(p+i))->score[j]);
		printf("%-.2f",(*(p+i))->aver);
		printf("\n");
	}
}
void main()
{
	int i=0;
	Stu s[N];
	Stu *p[N];					//定义指针数组，指向每一个学生，方便排序；
	for(i=0;i<N;i++)			//给指针数组赋初值；
		p[i]=&s[i];
	data_get(s);				//从文件中获取学生信息；
	sort(s,p);					//对学生信息按照学生成绩的平均分数排序；
	print(p);					//输出学生信息；
}
