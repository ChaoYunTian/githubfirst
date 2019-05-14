#include<stdio.h>
#include<malloc.h>
#define LEN sizeof(struct student)
struct student
{
	long num;
	float score;
	struct student *next;
};
int n=0;
struct student *insert(struct student *head,struct student *p0)
{
	struct student *p1=head,*p2;
	if(head==NULL)
    {
        head=p0;
        p0->next=NULL;
    }
    else
    {
        while((p1->num < p0->num)&&(p1->next!=NULL))
        {
            p2=p1;
            p1=p1->next;
        }
        if(p0->num<=p1->num)
        {
            if(head==p1)
                head=p0;
            else
                p2->next=p0;
            p0->next=p1;
        }
        else
        {
            p1->next=p0;
            p0->next=NULL;
        }
    }
    n++;
    return (head);
}
struct student *create(void)
{
	struct student *head=NULL,*p0;
    printf("请输入学号及成绩(输入0，0结束)\n");
    while(1)
    {
    	p0=(struct student *)malloc(LEN);
        scanf("%ld,%f",&p0->num,&p0->score);
        fflush(stdin);
        if(p0->num==0)
        {
        	free(p0);
			printf("\n创建结束\n");
			break;
        }
        else
            head=insert(head,p0);
    }
    return(head);
}
void print(struct student *head)
{
    struct student *p0=head;
    p0=head;
    if(head==NULL)
       printf("现在无数据！\n");
    while(p0!=NULL)
    {
    	printf("%-12ld|%4.2f\n",p0->num,p0->score);
    	p0=p0->next;
    }
}
struct student *del(struct student *head,long num)
{
    struct student *p0=head,*p1;
    while(p0!=NULL)
    {
    	if(p0->num==num)
    	{
    		if(head==p0)
    		   head=p0->next;
    		else if(p0->next==NULL)
    		   p1->next=NULL;
    		else
    		   p1->next=p0->next;
    		free (p0);
    		break;
    	}
    	 p1=p0;
         p0=p0->next;
    }
    if(n!=0&&p0!=NULL)
       n--;
    return (head);
}
void Free(struct student *head)
{
	struct student *p0=head,*p1;
	if(head==NULL)
	   return;
	else
	do{
		p1=p0->next;
		free(p0);
		p0=p1;
	  }while(p1!=NULL);
}
int main()
{
    struct student *head=NULL,*p0;
    int choice=-1;
    printf("*********开始创建*********\n");
    head=create();
    print(head);
    while(1)
    {
        printf("\n1.插入\t2.删除\t0.退出\n");
        printf("请选择:");
        scanf("%d",&choice);
        fflush(stdin);
        if(choice==0)break;
        switch(choice)
        {
        case 1:
        	{
            printf("请输入学号和成绩:");
            p0=(struct student *)malloc(LEN);
            scanf("%ld,%f",&p0->num,&p0->score);
            fflush(stdin);
            head=insert(head,p0);
            printf("插入完成: %ld\n",p0->num);
            print(head);
			}
            break;
        case 2:
        	{
            printf("请输入学号:");
            long num;
            scanf("%ld",&num);
            fflush(stdin);
            head=del(head,num);
            print(head);
            }
            break;
        }
    }
    Free(head);
    return 0;
}
