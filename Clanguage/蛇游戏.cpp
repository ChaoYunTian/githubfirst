#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#define U 1
#define D 2
#define L 3
#define R 4
#define headc "※"
#define bodyc "■"
typedef struct SNAKE 		//蛇身结构体
{
	int x;
    int y;
    struct SNAKE *next;
}snake;


snake *head,*q;
snake *food;
int sleeptime=200,direction=R;
int score,add=10;
int map[56][26]={0};



void printwall();
void initsnake();
void pos(int x,int y);
void color(int x);
void noteatfood();
void eatfood();
int  biteself();
int  bitewall();
void snakemove();
int  createfood();
void getdirection();
void gamestart();
void gamecircle();
void gameover();
void pause();
void welcometogame();//开始界面


void pos(int x,int y)//设置光标位置
{
    COORD pos;
	HANDLE hOutput;
    pos.X=x;
    pos.Y=y;
    hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput,pos);
}

void color(int x)      //设置颜色
{
	HANDLE houtput;
	houtput=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(houtput, (short)x);
}

void initsnake()      //初始化蛇身
{
	snake *p;
	int i;
	p=(snake *)malloc(sizeof(snake));
	p->x=20;
	p->y=10;
	p->next=NULL;
	for(i=1;i<=4;i++)
	{
		head=(snake *)malloc(sizeof(snake));
		head->next=p;
		head->x=20+2*i;
		head->y=10;
		p=head;
	}
	p=head->next;
	color(14);
	pos(head->x,head->y);
	map[head->x][head->y]=2;
	printf(headc);
	while(p!=NULL)         //输出蛇身
	{
		color(14);
		pos(p->x,p->y);
		map[p->x][p->y]=1;
		printf(bodyc);
		p=p->next;
	}

}


void printwall()          //打印墙
{
	int i;
	color(11);
	for(i=1;i<=25;i++)
	{
		pos(0,i);
		printf("■");
		pos(56,i);
		printf("■");
	}
	for(i=0;i<=56;i+=2)
	{
		pos(i,0);
		printf("■");
		pos(i,26);
		printf("■");
	}
}

void noteatfood()          //没有吃到食物
{
		snake *nexthead;
		nexthead=(snake *)malloc(sizeof(snake));
		switch(direction)
		{
		case R: nexthead->x=head->x+2;
				nexthead->y=head->y;break;
		case L: nexthead->x=head->x-2;
				nexthead->y=head->y;break;
		case U: nexthead->x=head->x;
				nexthead->y=head->y-1;break;
		case D: nexthead->x=head->x;
				nexthead->y=head->y+1;break;
		}

		nexthead->next=head;
		head=nexthead;
		q=head->next;
		color(14);
		pos(head->x,head->y);
		printf(headc);
		while(q->next->next!=NULL)
		{
			pos(q->x,q->y);
			printf(bodyc);
			map[q->x][q->y]=1;
			q=q->next;
		}
		pos(q->next->x,q->next->y);
		printf("  ");
		map[q->next->x][q->next->y]=0;
		free(q->next);
		q->next=NULL;

}

void eatfood()
{
		snake *nexthead;
		nexthead=(snake *)malloc(sizeof(snake));
		nexthead->x=food->x;
		nexthead->y=food->y;
		nexthead->next=head;
		head=nexthead;
		q=head->next;
		color(14);
		pos(head->x,head->y);
		map[head->x][head->y]=2;
		printf(headc);
		while(q!=NULL)
		{
			pos(q->x,q->y);
			printf(bodyc);
			map[q->x][q->y]=1;
			q=q->next;
		}
		score=score+add;
		free(food);
		createfood();


}

void snakemove()     //蛇移动（判断有没有吃食物）
{
	getdirection();
	if(direction==U)
		if(head->x==food->x && head->y-1==food->y)
			eatfood();
		else noteatfood();
	else if	(direction==D)
		if(head->x==food->x && head->y+1==food->y)
			eatfood();
		else noteatfood();
	else if	(direction==L)
		if(head->x-2==food->x && head->y==food->y)
			eatfood();
		else noteatfood();
	else if	(direction==R)
		if(head->x+2==food->x && head->y==food->y)
			eatfood();
		else noteatfood();
}
int biteself()        //咬到自己
{

	if(map[head->x][head->y]==1)
		return 1;
	else
	{
		map[head->x][head->y]=2;
		return 0;
	}

}

int bitewall()          //咬到墙
{
	if(head->x==0 || head->x==56 || head->y==0 || head->y==26)
		return 1;
	else return 0;
}

int createfood()		//创建食物
{
	bool isspectcoord(int x,int y);
	int x,y;
	food=(snake*)malloc(sizeof(snake));
	srand((unsigned)time(NULL));
	do
	{
		x=abs(rand())%54+2;
		y=abs(rand())%25+1;
		if(x%2!=0)
			x=x-1;
	}while(map[x][y]==1||map[x][y]==2);
	color(12);
	food->x=x;food->y=y;
	pos(food->x,food->y);
	printf("●");
	return 0;

}

/*bool isspectcoord(int x,int y)
{
	q=head;
	while(q!=NULL)
	{
		if(q->x==x && q->y==y )
			return true;
		q=q->next;
	}
	return false;
}*/					//判断食物是否与蛇身重合备用函数



void getdirection()				//获取方向
{
	if(GetAsyncKeyState(VK_UP) && direction!=D)
		direction=U;
	else if(GetAsyncKeyState(VK_DOWN) && direction!=U)
		direction=D;
	else if(GetAsyncKeyState(VK_LEFT) && direction!=R)
		direction=L;
	else if(GetAsyncKeyState(VK_RIGHT) && direction!=L)
		direction=R;
}


void gamestart()			//游戏开始
{

	printwall();
	initsnake();
	createfood();
	color(10);
	pos(64,10);
    printf("得分：%d  ",score);
    pos(64,11);
    printf("每个食物得分：%d分",add);
	pos(64,15);
    printf("不能穿墙，不能咬到自己\n");
    pos(64,16);
    printf("用↑.↓.←.→分别控制蛇的移动.");
    pos(64,17);
    printf("F1 为加速，F2 为减速\n");
    pos(64,18);
    printf("ESC :退出游戏. 空格键：暂停游戏.");
    pos(64,20);
	printf("～(￣▽￣～)(～￣▽￣)～");
}

void gameover()				//游戏结束
{
	color(15);
	system("cls");
	pos(32,14);
	printf("■■■■■■■■■■■■■■■");
	pos(32,15);
	printf("■                          ■");
	pos(32,16);
	printf("■        GAME OVER!        ■");
	pos(32,17);
	printf("■    您的最终得分为：%-4d  ■",score);
	pos(32,18);
	printf("■                          ■");
	pos(32,19);
	printf("■■■■■■■■■■■■■■■\n");
	pos(36,20);
	system("pause");
	exit(1);
}

void gamecircle()
{

	while(1)
	{
		color(10);
		pos(64,10);
        printf("得分：%d  ",score);
        pos(64,11);
        printf("每个食物得分：%d分",add);
		if(biteself()==1 || bitewall()==1)
			gameover();
		else if(GetAsyncKeyState(VK_SPACE))
			pause();
		else if(GetAsyncKeyState(VK_F1))
		{
			if(sleeptime>=50)
            {
                sleeptime=sleeptime-30;
                add=add+2;
                if(sleeptime==320)
                {
                    add=2;//防止减到1之后再加回来有错
                }
            }
		}
		else if(GetAsyncKeyState(VK_F2))
		{
			if(sleeptime<350)
            {
                sleeptime=sleeptime+30;
                add=add-2;
                if(sleeptime==350)
                {
                    add=1;  //保证最低分为1
                }
            }
		}
		else if(GetAsyncKeyState(VK_ESCAPE))
			gameover();
		else
			snakemove();
		Sleep(sleeptime);

	}
}

void pause()
{
	while(1)
	{
		if(GetAsyncKeyState(VK_SPACE))
			break;
		Sleep(300);
	}
}

void welcometogame()//开始界面
{
    system("title 贪吃蛇小游戏");
	pos(40,12);
    printf("欢迎来到贪食蛇游戏！\n");
	pos(40,13);
    system("pause");
    system("cls");
    pos(25,12);
    printf("用↑.↓.←.→分别控制蛇的移动， F1 为加速，F2 为减速\n");
    pos(25,13);
    printf("加速将能得到更高的分数。\n");
	pos(25,14);
    system("pause");
    system("cls");
}

int main()
{
	system("mode con cols=100 lines=33");
	welcometogame();
	gamestart();
	pause();
	gamecircle();
	return 0;
}


