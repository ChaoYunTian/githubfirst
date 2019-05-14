#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

void welcome()
{
	int i;
	char *p1="***************************************************************\n";
	char *p2="**********";
	char *p3="                                           ";
	char *p4=" = . = 欢 迎 进 入 趣 味 猜 数 游 戏 = . = ";
	char *p5="     C     ";
	char *p6=" 语 *** 言 "; 
	char *p7=" 小 *** 组 ";
	char *p8=" 作 *** 业 ";
	char *p9="*********************";
	char *p10=" 小组成员  ";
	char *p11=" 林 媛 燕  ";
	char *p12=" 曾 银 平  ";
	char *p13=" 张 会 迈  "; 
	for(i=0;i<3;i++)
		printf(p1);
	printf(p2);printf(p3);printf(p2);putchar('\n');
	printf(p2);printf(p4);printf(p2);putchar('\n');
	printf(p2);printf(p3);printf(p2);putchar('\n');
	printf(p1);
	printf(p2);printf(p5);printf(p9);printf(p7);printf(p2);putchar('\n');
	printf(p1);
	printf(p2);printf(p6);printf(p9);printf(p8);printf(p2);putchar('\n');
	printf(p1);
	printf(p2);printf(p10);printf(p9);printf(p11);printf(p2);putchar('\n');
	printf(p1);
	printf(p2);printf(p12);printf(p9);printf(p13);printf(p2);putchar('\n');
	printf(p1);
	printf("\t拼 命 加 载 中");
	for(i=1;i<7;i++)
	{
			printf(".");
			Sleep(1000);
	}
	system("cls");
} 
void print(int grade,int chance)
{	int i;
	for(i=0;i<=60;i++)	printf("*");
	printf("\n");
	printf("****    选择提示输入“H”         选择猜数输入“G”     ****\n");
	printf("****    选择重新开始输入“Q”     结束程序输入“E”     ****\n");
	printf("****    您现在得分：%d，您还有 %d 次机会。              ****\n",grade,chance);
	for(i=0;i<=60;i++)	printf("*");
	printf("\n"); 	
}//输出格式函数
void printa()
{	
	printf("========使用帮助一次将扣除当前分数的10================\n");
	printf("######  **************************************************\n"); 
	printf("#  C #  ①判断输入的数字比产生的数字大还是小\n");
	printf("# 语 #  ②判断是奇数还是偶数\n");
	printf("# 言 #  ③判断是不是素数，输出一定范围内的素数\n");
	printf("# ^^ #  ④判断你所猜的数中各位数字对应位置正误情况\n");
	printf("#HELP#  ⑤判断你所猜的数中正确数字是什么\n");
	printf("# 帮 #  ⑥请求输出某位数字是什么\n");
	printf("# 助 #  ⑦四位数之和\n");
	printf("# 功 #  ⑧唉~~放弃，告诉我答案\n");
	printf("# 能 #  ⑨亲~~ 点下看看\n");
	printf("######  *************************************************\n");	
}//输出帮助选择栏 
void fen(int x,int n[])
{
	int i;
	for(i=3;i>=0;i--)
	{
		n[i]=x%10;
		x=x/10;
	}
}//将四位数分开存入数组 
int prime(int x)
{
	int k,i,p;
	k=sqrt(x);
	for(i=2;i<=k;i++)
		if(x%i==0) break;
	if(i>k) p=1;
	else p=0;
	return(p);
}//判断素数 
void draw_heart()
{
	float y, x, a;
	for (y = 1.5f;y > -1.5f;y -= 0.1f)
	{
		for (x = -1.5f;x < 1.5f;x += 0.05f)
		{
			a = x*x + y*y - 1;
			putchar(a*a*a - x*x*y*y*y <= 0.0f ? '*' : ' ');
		}
		putchar('\n');
	}
} 
int main()
{
	int i,j,k,n[4],m[4],a=0,x,grade=100,chance=7,reward,r=0,order,z,y,p,sum=0,l=0,a1,q;
	char t;
	//welcome();
	srand((unsigned) time(NULL));
	x=rand()%9000+1000;//产生随机数 
	print(grade,chance);
	for(;grade!=0&&chance!=0;)//开始 
 	{
		scanf(" %c",&t);
		fflush(stdin);
		if(t=='h'||t=='H')
		{
			printa();
			scanf("%d",&order);
			fflush(stdin);
			switch(order)
			{
				case 1:	if(a!=0)
				       	{
					   		printf("你选择了提示信息1，会扣当前分数的1/10!\n");
				       		if(a>x) printf("您上次输入的 %d 大于产生的数字\n",a);
				       		if(a<x) printf("您上次输入的 %d 小于产生的数字\n",a);
							grade=grade*0.9;
						}
				       	else	printf("你还没有输入猜测的数字\n");
						break;
				case 2:	printf("你选择了提示信息2，会扣当前分数的1/10\n");
				       	if(x%2==0)	printf("产生的数字是偶数.");
				       	else printf("产生的数字是奇数.");
				        grade=grade*0.9;
						printf("\n");
						break;
				case 3:	printf("你选择了提示信息3，会扣当前分数的1/10\n");
				       	q=prime(x);
				       	if(q==0)printf("产生的数字不是素数"); 
				      	else 
						{
							printf("请输入要获知素数的范围<例如:2000,5000>:");
				      		scanf("%d,%d",&z,&y);
				      		for(j=z;j<=y;j++)
				      		{	q=prime(j);
				      			if(q==1) printf("%d ",j);
							}
						}
				       	grade=grade*0.9;
						printf("\n");
						break;
				case 4:	if(a!=0){printf("你选择了提示信息4，会扣当前分数的1/10\n");
				       	printf("你猜的数是%d, 与产生的数各位数字正误对比为:\n",a);
				       	fen(a,n);fen(x,m);
				       	for(i=0;i<=3;i++)
				       	{
							if(m[i]==n[i]) printf("R ");
							else printf("E ");
						}
				       	grade=grade*0.9; 
					   	printf("\n");}
					   	else printf("你还没有输入猜测的数字\n");
						break;
				case 5:	if(a!=0)
						{
							printf("你选择了提示信息5，会扣当前分数的1/10\n");
							l=0;
					       	fen(a,n);fen(x,m);
					       	for(j=0;j<=3;j++)
					       	{
								for(i=0;i<=3;i++)
					       		if(n[j]==m[i]) 
								{
									l++;
									break;
								}
							}
					       	printf("你输入的数中有%d个数字正确,正确的数字分别是:\n",l);
					       	for(j=0;j<=3;j++)
					       	{
								for(i=0;i<=3;i++)
					       		if(n[j]==m[i]) 
								{
									printf("%d ",n[j]);
									break;
								}
					       		grade=grade*0.9;
							}
							printf("\n");
						}
					    else printf("你还没有输入猜测的数字\n");
						a=a1;
						break;
				case 6:	r++;
				       	if(r==1){printf("你选择了提示信息6，会扣当前分数的1/10\n");
				       	fen(a,n);fen(x,m);
				       	printf("请输入希望得到的某位数字位置（从左到右表示为1,2,3,4):");
				       	scanf("%d",&p);
				       	printf("产生数据的第%d位是 %d\n",p,m[p-1]);
					   	grade=grade*0.9;}
					   	else printf("本功能只限使用一次，你已使用本功能，不能重复使用\n");
						break;
				case 7:	printf("你选择了提示信息7，会扣当前分数的1/10\n");
				       	fen(a,n);fen(x,m);
				       	for(i=0;i<=3;i++)
						   sum+=m[i];
				       	printf("四位数字之和为: %d\n",sum); grade=grade*0.9;break;
				case 8:	printf("你选择了提示信息8，你已放弃猜这个数。\n");
				       	printf("这个随机数是：%d\n",x);
					   	printf("@帅哥，游戏已经重新开始，请重新选择.\n");
					   	grade=100;chance=7;x=rand()%9000+1000;r=0;a=0;
						break;
				case 9:	printf("你选择了提示信息9，会扣当前分数的1/10！\n");
				       	draw_heart();
				       	grade=grade*0.9;break;
				default:break;
			}//帮助
		    print(grade,chance);
		} 
		else if(t=='G'||t=='g') 
		{	
			printf("请输入猜测的数字："); 
            scanf("%d",&a);
            fflush(stdin);
            if(a==x) 
			{
				chance--;
				reward=pow(2,chance);
				grade+=reward;
				printf("恭喜你答对了\n");
				printf("你的得分为:%d\n产生的数字:%d\n",grade,x);
				break;
			}
        	else if(a>=1000&&a<=9999 && chance !=0)
			{	
				printf("没猜对噢\n");
				chance--;
				if(chance != 0) print(grade,chance);
			}
			else if(a<1000 || a>9999) 
			{
				printf("请输入1000到9999之间的数，您输入的%d不在此范围内\n",a);
				print(grade,chance);
				printf("\t输入有误，请按照要求输入\n");
			}
			if(chance == 0)
			{
				printf("猜数次数用尽了，你输了！\n");
				printf("你的得分为:0\n");
				printf("产生的数字为%d\n",x);
				system("pause");
				x=rand()%9000+1000;
				grade=100;chance=7;
				print(grade,chance);
			} 
		}//选择猜数输入
		else if(t=='q'||t=='Q') 
		{
			grade=100;a=0;
			chance=7;
			printf("已退出，重新开始.\n");
			x=rand()%9000+1000;
			r=0;
			print(grade,chance);
		}
 		else if(t=='E'||t=='e') 
		{
			printf("谢谢使用，欢迎再次使用此程序\n");
			break;
		}// 结束程序输入
 		else 
		{
			printf("\t输入有误，请按照要求输入\n");
			print(grade,chance);
		}//选择重新开始输入 
 	}
 	return 0;
}
