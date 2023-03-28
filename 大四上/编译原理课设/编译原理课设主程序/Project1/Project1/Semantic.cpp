/***************************
 语义分析
****************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h> 
#include<windows.h>  
#define MAXSIZE  500				//栈大小
#include "common.h"

extern struct inds input[MAXSIZE];
extern struct tableaction ACTION[63][29];
extern int GOTO[48][15];
extern struct tableproduction production[33];
extern char* string[MAXSIZE];				//符号表
extern char* tempvar[MAXSIZE];				//临时标量表
extern int string_max;
extern int tempvar_max;
extern char* tempstr;
extern int error;//出错标志

extern void pop(stack* st, int n);
extern void push(stack* st, char* chword, int x, int y, int z, int t, int f);
extern int intop;							//指向当前输入串字符

extern int TS;								//栈顶状态号（TopStat）
extern int IS;								//当前输入符号(InpSym)
extern int NS;								//规约后GOTO产生的新状态(NewStat)
extern int PL;								//第i个产生式的左部(编号)(Production_left)

int T = 0;
int tempvar_cur = 0;
int NXQ = 100;

struct formula   //四元式结构体 
{
	char opr[20];  //操作码 
	char op1[20];	//操作数 
	char op2[20];	//操作数 
	char results[20];	//结果 
	int result;

};
struct formula gen[MAXSIZE];

int Entry(char* buf)								//以buf为名查，填符号表
{
	int i = 0;
	int temp;
	for (i = 0; i < string_max; i++)	//把buf的值和符号表里的值比较，相等则返回其编号 
	{
		if (strcmp(string[i], buf) == 0)
			return(i);
	}
	string[string_max] = buf;	//否则加入新的buf值到符号表中 
	temp = string_max;
	string_max++; //符号表编号+1 
	//printf("the %s is defined now",string[temp]); //并且打印新加入的值正在被定义 
	return(temp);
}
int NewTemp()    //申请临时工作单元  （一般存放运算结果） 
{
	int num;
	string[string_max] = tempvar[tempvar_cur];
	num = string_max;
	string_max++;
	tempvar_cur++;
	return num; // 产生临时变量的函数，每次调用都定义一个新的临时变量。返回值为该变量的编号
}

int Merge(int p1, int p2)  // 将链首“指针”分别为p1和p2的两条链合并为一条，并返回新链的链首”指针“  
{
	int p;				//将条件语句中false和next链合并一起，之后通过backpatch回填 
	if (!p2)
		return p1;
	else
	{
		p = p2;
		while (gen[p].result)
			p = gen[p].result;
		gen[p].result = p1;
		return p2;
	}
}

void BackPatch(int p, int t)  //用四元式序号t回填以p为首的链， 将链中每个四元式的Result域改写为t的值。 
{
	int q1;
	int q = p;
	while (q)
	{
		q1 = gen[q].result;
		gen[q].result = t;
		q = q1;
	}
	return;
}

void act(stack* st, int num)	//执行归约产生式对应的语义动作 
{

	if (num == 6 || num == 7 || num == 28)   //THEN ELSE ： 
	{
		production[ACTION[TS][IS].s].Pro_place = Entry(st->ch_word[st->top]);//归约产生式 部符号的语义属性= 查表找词文对应的编号的属性值 
	}
	else if (num == 5 || num == 8 || num == 9 || num == 23 || num == 24 || num == 25)//IF|WHILE|DO|.|：= |，|后必接跳转语句（j，x,x,x） //所以这就是为啥IF后只能接一个：=赋值语句 
	{
		production[ACTION[TS][IS].s].Pro_place = st->st_place[st->top]; //归约产生式左部符号的语义属性 = 右部语义信息的属性 
	}
	else if (num == 10)				//int 只要遇到整形，先赋值给T某 （赋值语句） 
	{
		tempstr = (char*)malloc(3 * sizeof(char));
		strcpy(tempstr , ":=");				//存放运算符的指针 
		strcpy(gen[NXQ].opr , tempstr);   //操作码 
		strcpy(gen[NXQ].op1 , st->ch_word[st->top - 2]);   //操作数 
		strcpy(gen[NXQ].op2 , string[st->st_place[st->top]]);	//操作数 
		gen[NXQ].result = 0;	//操作结果 
		NXQ++;
		//		printf("\nGEN(:= %s,0,%s)\n",st->ch_word[st->top-2],string[st->st_place[st->top]]);
	}
	else if (num == 11)//（var）之后之间看A+1 
	{
		production[ACTION[TS][IS].s].Pro_place = NewTemp();//对归约产生式 求值，并置于变量T中 
		tempstr = (char*)malloc(2 * sizeof(char));
		strcpy(tempstr , "+");
		strcpy(gen[NXQ].opr , tempstr);
		strcpy(gen[NXQ].op1 , string[st->st_place[st->top - 2]]);
		strcpy(gen[NXQ].op2 , string[st->st_place[st->top]]);
		strcpy(gen[NXQ].results , string[production[ACTION[TS][IS].s].Pro_place]);
		NXQ++;
		//		printf("\nGEN(+ %s,%s,%s)\n",string[st->st_place[st->top-2]],string[st->st_place[st->top]],string[production[ACTION[TS][IS].s].Pro_place]);
	}
	else if (num == 14)//（*）  x+x：=T   *的作用是使（x+x）的值能够作为T值被调用，否则调用栈中第一个值X 
	{
		production[ACTION[TS][IS].s].Pro_place = st->st_place[st->top - 1];// 归约产生式左部符号的语义属性 = 右部语义信息的属性栈中下一个值 
	}
	else if (num == 15)// （/ ）  while一遍后跳转回第100行
	{
		BackPatch(st->st_TC[st->top], st->st_FC[st->top - 1]);//假出口下一至回填真出口 
		strcpy(gen[NXQ].opr , "j");
		strcpy(gen[NXQ].op1 , "0");
		strcpy(gen[NXQ].op2 , "0");
		gen[NXQ].result = st->st_FC[st->top - 1];//结果取假出口下一值 
		NXQ++;
		production[ACTION[TS][IS].s].Pro_TC = st->st_TC[st->top - 1];//归约产生式左部符号的语义属性 = 真出口属性栈中下一个值 
	}

	else if (num == 17)//<=      不符合WHILE条件，直接（j,0,0,0） 
	{
		production[ACTION[TS][IS].s].Pro_TC = NXQ;
		production[ACTION[TS][IS].s].Pro_FC = NXQ + 1;
		strcpy(gen[NXQ].opr , string[st->st_place[st->top - 1]]);
		strcpy(gen[NXQ].op1 , string[st->st_place[st->top - 2]]);
		strcpy(gen[NXQ].op2 , string[st->st_place[st->top]]);
		gen[NXQ].result = 0;
		NXQ++;
		strcpy(gen[NXQ].opr , "j");
		strcpy(gen[NXQ].op1 , "0");
		strcpy(gen[NXQ].op2 ,"0");
		gen[NXQ].result = 0;
		NXQ++;
		//		printf("\nGEN(%s,%s,%s,0)\n",string[st->st_place[st->top-1]],string[st->st_place[st->top-2]],string[st->st_place[st->top]]);
	}


	else if (num == 18)//> 符合WHILE条件，跳转至执行语句所在的行（j,0,0,x）
	{
		production[ACTION[TS][IS].s].Pro_TC = Merge(T, st->st_FC[st->top]);
	}

	else if (num == 20) //<>   产生（j,0,0,0） 
	{
		BackPatch(st->st_TC[st->top - 2], NXQ);
		strcpy(gen[NXQ].opr , "return");
		strcpy(gen[NXQ].op1 , "0");
		strcpy(gen[NXQ].op2 , "0");
		gen[NXQ].result = 0;
		NXQ++;
		gen[NXQ].result = 99;
		printf("success");
	}

	else if (num == 22) //;    如果int后没分号 则全部是GEN（0，0，0，0） 
	{
		production[ACTION[TS][IS].s].Pro_TC = 0;

	}
}

void yuyi() {
	printf("\n\n\n\n====================================================语义分析结果====================================================\n\n");
	if (error) {
		printf("\n请先检查程序语法，修改语法错误后再重新运行！！\n");
		return;
	}
	int t;
	stack* st = (stack*)malloc(sizeof(stack));		//分析栈
	for (t = 0; t < MAXSIZE; t++)
	{
		st->ch[t] = 100;
	}
	st->top = 0;
	st->ch[0] = 0;									//初始把'#'入栈
	st->sta[0] = 0;
	intop = 0;

	TS = st->sta[st->top];				//栈顶状态号（TopStat）
	IS = input[intop].sty;				//当前输入符号(InpSym)

	while ((ACTION[TS][IS].c != 'A') && (!error))//A为acc
	{

		if (ACTION[TS][IS].c == 'S')		//分析动作为移进（s）
		{
			push(st, input[intop].instr, input[intop].sty, ACTION[TS][IS].s, 0, 0, 0);

			if (input[intop].sty == 6)
				BackPatch(st->st_TC[st->top - 1], NXQ);
			else if (input[intop].sty == 7)
			{
				T = NewTemp();
				T = Merge(NXQ, st->st_TC[st->top - 1]);
				strcpy(gen[NXQ].opr , "j");
				strcpy(gen[NXQ].op1 ,"0");
				strcpy(gen[NXQ].op2 , "0");
				gen[NXQ].result = 0;
				NXQ++;
				BackPatch(st->st_FC[st->top - 3], NXQ);
			}
			else if (input[intop].sty == 8)
			{
				st->st_FC[st->top] = NXQ;
			}
			else if (input[intop].sty == 9)
			{
				BackPatch(st->st_TC[st->top - 1], NXQ);
				st->st_TC[st->top] = st->st_FC[st->top - 1];
				st->st_FC[st->top] = st->st_FC[st->top - 2];
			}
			intop++;

		}
		else if (ACTION[TS][IS].c == 'r')		//分析动作为归约（r）
		{
			act(st, ACTION[TS][IS].s);
			pop(st, production[ACTION[TS][IS].s].word_count);
			PL = production[ACTION[TS][IS].s].word_number;//Production_left
			NS = GOTO[(st->sta[st->top])][production[ACTION[TS][IS].s].word_number - 29];//(NewStat)
			push(st, input[intop].instr, PL, NS, production[ACTION[TS][IS].s].Pro_place, production[ACTION[TS][IS].s].Pro_TC, production[ACTION[TS][IS].s].Pro_FC);

		}
		TS = st->sta[st->top];
		IS = input[intop].sty;
	}


	printf("\n\n产生的四元式为:\n\n");
	int i;
	for (i = 100; gen[i].result != 99; i++)
	{
		if (gen[i].results != NULL)
			printf("%d:GEN(%s,%s,%s,%s)\n", i, gen[i].opr, gen[i].op1, gen[i].op2, gen[i].results);
		else
			printf("%d:GEN(%s,%s,%s,%d)\n", i, gen[i].opr, gen[i].op1, gen[i].op2, gen[i].result);
	}
}


