#include<stdio.h>
#include<windows.h>
#include<time.h>
#define S 11
#define C 6
void produce_score(float score[S][C])                 //利用随机数生成分数列表；
{
    int i,j;
    printf("成绩表如下：\n");
    for(i=0;i<S;i++)
    {
        printf("第%d位学生:\t",i+1);
        for(j=0;j<C;j++)
        {
            Sleep(100);
            srand(time(NULL));
            score[i][j]=(float)(rand()%41+60);
            printf("%5.2f\t",score[i][j]);
        }
        printf("\n");
    }
}
float score_average(float score[S][C],int n)            //计算个人所有课程的平均成绩；
{
    int i=0;
    float sum=0;
    while(i<C)
     {
         sum+=score[n][i];
         i++;
     }
    return sum/C;
}
float class_average(float score[S][C],int n)         //计算每门课程的平均分数；
{
    int i=0;
    float sum=0;
    while(i<S)
    {
        sum+=score[n][i];
        i++;
    }
    return sum/S;
}
void find_highest(float score[S][C])               //寻找最高分数，并输出对应学生和课程；
{
    int i,j,s,c;
    float max=0;
    for(i=0;i<S;i++)
        for(j=0;j<C;j++)
            if(max<score[i][j])
            {
                max=score[i][j];
                s=i+1;
                c=j+1;
            }
    printf("\n\n最高的分数是%-4.2f,他对应第%d位学生，第%d门课程；",max,s,c);
}
float variance_student(float score[S][C])          //计算方差；
{
    int i=0;
    float sum1=0,sum2=0,variance,average;
    while(i<S)
    {
        average=score_average(score,i);
        sum1=sum1+(average*average);
        sum2+=average;
        i++;
    }
    variance=(sum1/S)-(sum2/S)*(sum2/S);
    return variance;
}
int main()
{
    float score[S][C];                              //总共有十名学生，五门课程；
    produce_score(score);                           //利用随机数生成成绩表；
    int i=0;
    float max1=0,max2=0,average;
    printf("\n这%d名学生他们的平均成绩分别是：\n",S);
    while(i<S)                                      //计算每个学生的平均成绩并输出，最后再输出成绩最高学生的成绩及位置；
    {
        average=score_average(score,i);
        printf("%-4.2f  ",average);
        if(average>max1)
        {
            max1=average;
            max2=i;
        }
        i++;
    }
    printf("\n其中成绩最高的是第%d名学生，他的分数是：%-4.2f",(int)max2+1,max1);
    printf("\n\n这%d门课程的平均成绩分别是：",C);
    i=0,max1=0,max2=0;
    while(i<C)                                      //计算每门课程的平均成绩并输出，最后再输出成绩最高课程的成绩及位置；
    {
        average=class_average(score,i);
        printf("%-4.2f  ",average);
        if(average>max1)
        {

            max1=average;
            max2=i;
        }
        i++;
    }
    printf("\n其中成绩最高的是第%d门课程，它的分数是：%-4.2f",(int)max2+1,max1);
    find_highest(score);                           //寻找最高分数，并输出对应学生和课程；
    printf("\n\n所有学生平均分的方差是：%-4.2f",variance_student(score));
    return 0;
}
