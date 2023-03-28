/***************************
 语法分析
****************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#define MAXSIZE  1000//栈大小
#define true 1
#define false 0

/*构造栈*/
typedef struct 
{
	char s[MAXSIZE];//存放符号
	int  sta[MAXSIZE];//存放状态
	int	 top;
}stack;

char input[100]={'\0'};
int intop; //指向当前输入串字符

int error;//出错标志

/* 构造LR分析表*/

typedef struct    //构造ACTION分析表
{
	char c;//动作
	int  s;//状态
 }taction;
taction ACTION[7][4]={					
	{{'s',3},{'s',4},{'e',0},{'e',0}},
	{{'e',0},{'e',0},{'e',0},{'a',0}},
	{{'e',0},{'e',0},{'s',5},{'r',2}},
	{{'e',0},{'e',0},{'r',3},{'r',3}},
	{{'e',0},{'e',0},{'r',4},{'r',4}},
	{{'s',3},{'s',4},{'e',0},{'e',0}},
	{{'e',0},{'e',0},{'e',0},{'r',1}}
};

int GOTO[7][2]={						//构造GOTO分析表结构
	{1,2},{100,100},{100,100},{100,100},{100,100},{6,2},{100,100}
};

char proleft[4]={'L','L','E','E'};//第i个产生式的左部

int is_empty(stack *st)
{
	if(st->top <0) return true;
	else return false;
}
//入栈
void push(stack *st,char x,int y)
{
     if(st->top==MAXSIZE-1) printf("栈上溢 ！\n");
	 else
	 {
		 st->top++;
		 st->s[st->top]=x;
		 st->sta[st->top]=y;
	 }
}

//栈指针下移，弹出栈顶元素
void pop(stack *st,int n)
{
//	stack *st;
	int i;
	for(i=0;i<n;i++)
	{
		if(st->top<0)
			printf("栈下溢出!\n");
		else
			st->top--;
	}
};


int find_action(int top)//根据当前输入符号，转换ACTION分析表的第二个坐标并返回
{
	int jnum;
	char ch_input=input[top];
	if(ch_input=='a')	   
		jnum=0;
	else if(ch_input=='b') 
		jnum=1;
	else if(ch_input==',') 
		jnum=2;
	else if(ch_input=='#') 
		jnum=3;
	else
		jnum=100;

	return  jnum;
};
int find_goto(int s,char t)//根据当前状态，查GOTO分析表，返回新状态
{
	if(t=='E') 
		return(GOTO[s][1]);
	else
		return(GOTO[s][0]);
};
int find_proright(int num)//返回归约产生式的右部文法符号的个数
{
	int count=0;	
	if(num==2) count=1;
	if(num==3) count=1;
	if(num==4) count=1;
	if(num==1) count=3;
	return count;
}
void LRdriver(stack *st)//LR分析器驱动
{
	int TS=st->sta[st->top];//栈顶状态号（TopStat）
	int IS=find_action(intop);//当前输入符号对应的第二位坐标(InpSym)
	int NS;//规约后产生的新状态(NewStat)
	char PL;//第i个产生式的左部(Production_left)
	int l;
	while((ACTION[TS][IS].c!='a')&&(!error))//a为acc，表示当前分析动作不为接受
	{
		printf("\n");/*输出分析过程*/
		for(l=0;l<=st->top;l++)
			printf("%d",st->sta[l]);
		printf("\t");
		for(l=0;l<=st->top;l++)
			printf("%c",st->s[l]);
		printf("\t");
		for(l=intop;input[l]!='\0';l++)
			printf("%c",input[l]);	

		if(ACTION[TS][IS].c=='e')//分析动作为ERROR
		{
			error=1;
		}
		else if(ACTION[TS][IS].c=='s')//分析动作为移进（s）
		{
			push(st,input[intop],ACTION[TS][IS].s);
			intop++;
			printf("\ts%d",ACTION[TS][IS].s);
		}
		else if(ACTION[TS][IS].c=='r')//分析动作为归约（r）
		{
			pop(st,find_proright(ACTION[TS][IS].s));//find_proright(ACTION[TS][IS].s)为第i个产生式右部文法符号的个数
			PL=proleft[ACTION[TS][IS].s-1];//第i个产生式的左部(Production_left)
			NS=find_goto(st->sta[st->top],PL);//规约后产生的新状态(NewStat)
			push(st,PL,NS);
			printf("\tr%d",ACTION[TS][IS].s);
		}
		TS=st->sta[st->top];
		IS=find_action(intop);
	}
	if(!error)
	{
	printf("\n");
		for(l=0;l<=st->top;l++)
			printf("%d",st->sta[l]);
		printf("\t");
		for(l=0;l<=st->top;l++)
			printf("%c",st->s[l]);
		printf("\t");
		for(l=intop;input[l]!='\0';l++)
			printf("%c",input[l]);
	printf("\nAccepted!");
	}
	else
		printf("\nIt must be an error here,Please check it again!\n");
};

	
void main()
{
	stack *st=(stack*)malloc(sizeof(stack));
	char cc;
	int i=0;
	int t=0;
	for(t=0;t<MAXSIZE;t++)
		st->s[t]='\0';
	st->top =0;
	st->s[0]='#';
	st->sta[0]=0;
	printf("\n请输入一符号串，以＃结尾 ：\n");
    do
	{ 
		scanf("%c",&cc);
		input[i]=cc;
		i++;
	}while(cc!='#');
	input[i]='\0';
	intop=0;
	i=0;
	printf("状态栈\t符号栈\t余留串\t动作");
	LRdriver(st);
}
