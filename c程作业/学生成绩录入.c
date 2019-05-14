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
	float score[M];			//记录学生M门成绩信息
	float aver;				//记录学生平均成绩;
}Stu;
void data_in(Stu *p)				//输入学生成绩并将其储存在文件中；
{
	printf("请依次录入%d名学生成绩：\n",N);
	int i=0;
	while(i < N)
	{
		printf("请输入第%d位学生信息\n",i+1);
		printf("\t学号:");
		scanf("%ld",&p->num);
		getchar();
		printf("\t姓名:");
		scanf("%s",p->name);
		getchar();
		printf("\t性别:");
		scanf("%s",p->sex);
		getchar();
		printf("\t出生日期:");
		scanf("%d-%d-%d",&p->birth.year,&p->birth.month,&p->birth.day);
		getchar();
		int j=0;
		float sum=0;
		for(;j<M;j++)
		{
			printf("\t课程%d:",j+1);
			scanf("%f",&p->score[j]);
			getchar();
			sum+=p->score[j];
		}
		p->aver=sum/M;
		i++;
		p++;
	}
	return ;
}
void file_in(Stu *p)
{
	char filename[20];
	FILE *fp;
	printf("请输入文件路径：");
	scanf("%s",filename);
	getchar();
	if((fp=fopen(filename,"wb")) == NULL)
	{
		printf("文件打开失败，请检查文件路径！\n");
		exit(0);
	}
	int n=fwrite(p,sizeof(Stu),N,fp);
	if(n != N)
	{
		printf("文件写入失败！");
		exit(0);
	}
	printf("文件写入成功！\n");
	fclose(fp);
}
int main()
{
	Stu s[N];
	data_in(s);
	file_in(s);
	return 0;
}
