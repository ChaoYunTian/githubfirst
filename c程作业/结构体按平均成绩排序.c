#include<stdio.h>
#define N 3
#define M 3
struct date
{
    int year;
    int month;
    int day;
};
struct Student
{
    char name[10];
    char num[12];
    int sex;
    struct date birth;
    float score[M];
    float avescore;
};
void data_in(struct Student *p)
{
    for(int i=0;i<N;i++,p++)
    {
        printf("请输入第%d位学生信息\n",i+1);
        printf("请输入姓名：");
        scanf("%s",p->name);
        getchar();
        printf("请输入学号:");
        scanf("%s",p->num);
        getchar();
        printf("请选择性别:1,男\t2,女  ");
        scanf("%d",&p->sex);
        getchar();
        printf("请输入出生日期:（例如1999-01-01）");
        scanf("%d-%d-%d",&p->birth.year,&p->birth.month,&p->birth.day);
        getchar();
        printf("请分别输入%d门课的成绩中间以空格分割:(例如:90 90)",M);
        for(int i=0;i<M;i++)
        {
            scanf("%f",&p->score[i]);
            getchar();
        }
    }
}
void average(struct Student *p)
{
    float sum;
    for(int i=0;i<N;i++,p++)
    {
        sum=0;
        for(int j=0;j<M;j++)
            sum+=p->score[j];
        p->avescore=sum/M;
    }
}
void print( struct Student s)
{
    static int j=1;
    printf("%-8d%-10s%-12s",j++,s.name,s.num);
    if(s.sex==1) printf("%-8s","男");
    else printf("%-8s","女");
    printf("%d-%.2d-%-4.2d",s.birth.year,s.birth.month,s.birth.day);
    for(int i=0;i<M;i++)
        printf("%-8.1f",s.score[i]);
    printf("%-8.1f\n",s.avescore);
}
void sort(struct Student *s)
{
    struct Student *p[N];
    for(int i=0;i<N;i++)
        *(p+i)=s++;
    for(int i=0;i<N-1;i++)
    {
        for(int j=i+1;j<N;j++)
        {
            if(p[i]->avescore<p[j]->avescore)
            {
                struct Student *temp;
                temp=p[j];
                p[j]=p[i];
                p[i]=temp;
            }
        }
    }
    for(int i=0;i<N;i++) print(*p[i]);
}
int main()
{
    struct Student s[N];
    printf("本程序主要用于录入学生信息，并按照平均分从大到小输出。\n");
    data_in(s);
    average(s);
    printf("\n%-8s%-10s%-12s%-8s%-12s","序号","姓名","学号","性别","出生日期");
    for(int i=0;i<M;i++)
        printf("课程%d   ",i+1);
    printf("%-8s\n","平均成绩");
    sort(s);
    return 0;
}



