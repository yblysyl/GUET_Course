/***************************
 语法分析
****************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include "common.h"
#define MAXSIZE  500				             //栈大小

struct inds input[MAXSIZE];                     //存放takon表的内容（单词、对应编码） 
int intop = 0;                                 //当前进行词法分析的单词下标 

struct tableaction ACTION[63][29] = { 0 };         //用来模拟SLR分析表的ACTION表的内容 （动作、状态） 
int GOTO[48][15] = { 0 };                         //用来存储SLR分析表的GOTO表的内容  （状态） 
struct tableproduction production[33] = { 0 };    //用来存储产生式表 

char* string[MAXSIZE];	    	//存储符号表
int string_max;                 //符号表的长度 
char* tempvar[MAXSIZE];			//临时标量表
int tempvar_max;            	//临时标量表长度

int error;        //记录错误数 
char* tempstr;   //临时存储单词

int TS;							//栈顶状态号（TopStat）
int IS;							//当前输入符号(单词)
int NS;							//规约后GOTO产生的新状态(NewStat)
int PL;							//第i个产生式的左部(编号)(Production_left)

void color(int a)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}

//入栈
void push(stack* st, char* chword, int x, int y, int z, int t, int f)
{
	if (st->top == MAXSIZE - 1) printf("栈上溢 ！\n");
	else
	{
		st->top++;
		st->ch_word[st->top] = chword;
		st->st_place[st->top] = z;
		st->ch[st->top] = x;
		st->sta[st->top] = y;
		st->st_TC[st->top] = t;
		st->st_FC[st->top] = f;
	}
}

//出栈
void pop(stack* st, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (st->top < 0)
			printf("栈下溢出!\n");
		else
			st->top--;
	}
};

void LRdriver(stack* st)					//SLR分析器驱动
{
	int l;
	TS = st->sta[st->top];				//栈顶状态号（TopStat）
	IS = input[intop].sty;				//当前输入单词的编码(InpSym)	
	while ((ACTION[TS][IS].c != 'A') && (!error))//A为acc
	{										/*输出分析过程*/
		printf("\n");
		for (l = 0; l <= st->top; l++)
			printf("%d-", st->sta[l]);
		if (l >= 12)
			printf("\t");
		else if (l >= 9 && l <= 11)
			printf("\t\t");
		else if (l >= 7 && l <= 8)
			printf("\t\t\t");
		else if (l >= 4 && l <= 6)
			printf("\t\t\t\t");
		else
			printf("\t\t\t\t\t");
		for (l = 0; l <= st->top; l++)
			printf("%d-", st->ch[l]);
		if (l >= 10 && l <= 20)
			printf("\t\t");
		else if (l >= 7 && l <= 9)
			printf("\t\t\t");
		else if (l >= 4 && l <= 6)
			printf("\t\t\t\t");
		else
			printf("\t\t\t\t\t");
		for (l = intop; input[l].sty != 100; l++)
			printf("%-s", input[l].instr);


		if (ACTION[TS][IS].c == '\0')			//分析动作为ERROR
		{
			error++;
		}
		else if (ACTION[TS][IS].c == 'S')		//分析动作为移进（s）
		{
			//			            当前单词      单词对应编码   下一步状态 
			push(st, input[intop].instr, input[intop].sty, ACTION[TS][IS].s, 0, 0, 0);
			//栈指向下一个（即可读长度加1） 
			intop++;
			color(FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			printf("\ts%d", ACTION[TS][IS].s);	//输出 : s* 
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_INTENSITY);
		}
		else if (ACTION[TS][IS].c == 'r')		//分析动作为归约（r）
		{
			//弹栈（弹栈元素个数由产生式表的属性：word_count决定） 
			pop(st, production[ACTION[TS][IS].s].word_count);
			PL = production[ACTION[TS][IS].s].word_number;//以动作表当前状态值为下标去查产生式表，得到产生式左边的单词对应的值 
//			      当前状态栈值            产生式左边单词对应的值 
			NS = GOTO[(st->sta[st->top])][production[ACTION[TS][IS].s].word_number - 29];//查goto表 ， 
//			            单词        状态   
			push(st, input[intop].instr, PL, NS, production[ACTION[TS][IS].s].Pro_place, production[ACTION[TS][IS].s].Pro_TC, production[ACTION[TS][IS].s].Pro_FC);

			color(FOREGROUND_INTENSITY | FOREGROUND_RED);
			printf("\tr%d", ACTION[TS][IS].s);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_INTENSITY);
		}
		TS = st->sta[st->top];
		IS = input[intop].sty;
	}

	if (!error)
	{
		printf("\n");
		for (l = 0; l <= st->top; l++)
			printf("%d", st->sta[l]);
		printf("\t\t");
		for (l = 0; l <= st->top; l++)
			printf("%d", st->ch[l]);
		printf("\t");
		for (l = intop; input[l].sty != 100; l++)
			printf("%s", input[l].instr);
		color(FOREGROUND_INTENSITY | FOREGROUND_RED);
		printf("\tAccepted!\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_INTENSITY);
	}

	else {
		color(FOREGROUND_INTENSITY | FOREGROUND_RED);
		printf("\nIt must be an error here,Please check it again!\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_INTENSITY);
	}
};

void yufa()
{
	FILE* fpin;
	stack* st = (stack*)malloc(sizeof(stack));		//分析栈
	char file_token[] = "token.txt";
	char file_goto[] = "goto.txt";
	char file_action[] = "action.txt";
	char file_proinfo[] = "proinfo.txt";
	//char file_infost[]="infost.txt";
	int x_location;									//x坐标
	int y_location;									//y坐标
	int goto_value;									//goto属性表中的状态值
	char action_act;								//action分析表中的动作
	int action_state;								//action分析表中的状态
	int pro_word_number;							//产生式属性表中的word_number
	int pro_word_count;								//产生式属性表中的word_count
	int i = 0;
	int j = 0;
	int t = 0;
	tempstr = (char*)malloc(6 * sizeof(char));	//暂存从token文件读出的词文
	printf("\n\n\n\n====================================================语法分析结果====================================================\n");
	printf("\n程序内容：\n\n");
	for (t = 0; t < MAXSIZE; t++)//初始化栈 
	{
		st->ch[t] = 100;
	}
	st->top = 0;
	st->ch[0] = 0;									//初始把'#'入栈
	st->sta[0] = 0;
	if ((fpin = fopen(file_token, "r")) == NULL)			/*读取token文件*/
		printf("\n\nError:The file token is NULL\n");
	else
		do
		{
			if (fgetc(fpin) == EOF)
				break;
			else
			{
				fseek(fpin, -1L, 1);
				fscanf(fpin, "%s %d", tempstr, &input[i].sty);//每次读一行 
				input[i].instr = tempstr;
				printf("%s ", input[i].instr);//输出 
				i++;
				tempstr = (char*)malloc(6 * sizeof(char));
			}
		} while (fgetc(fpin) != EOF);
		fclose(fpin);
		input[i].instr = '\0';								//结尾
		input[i].sty = 100;
		intop = 0;
		i = 0;

		if ((fpin = fopen(file_goto, "r")) == NULL)			/*读取goto文件，构造goto分析表*/
			printf("\n\nError:The file goto is NULL\n");
		else
			do
			{
				if (fgetc(fpin) == EOF)
					break;
				else
				{
					fseek(fpin, -1L, 1);
					fscanf(fpin, "%d %d %d", &x_location, &y_location, &goto_value);
					GOTO[x_location][y_location - 29] = goto_value;
				}
			} while (fgetc(fpin) != EOF);
			fclose(fpin);

			if ((fpin = fopen(file_action, "r")) == NULL)			/*读取action文件，构造action分析表*/
				printf("\n\nError:The file action is NULL\n");
			else
				do
				{
					if (fgetc(fpin) == EOF)
						break;
					else
					{
						fseek(fpin, -1L, 1);
						fscanf(fpin, "%d %d %c %d", &x_location, &y_location, &action_act, &action_state);
						ACTION[x_location][y_location].c = action_act;
						ACTION[x_location][y_location].s = action_state;
					}
				} while (fgetc(fpin) != EOF);
				fclose(fpin);

				if ((fpin = fopen(file_proinfo, "r")) == NULL)		/*读取proinfo文件，构造产生式属性表*/
					printf("\n\nError:The file proinfo is NULL\n");
				else
					do
					{
						if (fgetc(fpin) == EOF)
							break;
						else
						{
							fseek(fpin, -1L, 1);
							fscanf(fpin, "%d %d %d", &x_location, &pro_word_number, &pro_word_count);
							production[x_location].word_number = pro_word_number;
							production[x_location].word_count = pro_word_count;
						}
					} while (fgetc(fpin) != EOF);
					fclose(fpin);

					i = 0;
					if ((fpin = fopen("id.txt", "r")) == NULL)		/*读取文件，构造变量表*/
						printf("\n\nError:The file proinfo is NULL\n");
					else
						do
						{
							if (fgetc(fpin) == EOF)
								break;
							else
							{
								fseek(fpin, -1L, 1);
								tempstr = (char*)malloc(5 * sizeof(char));
								fscanf(fpin, "%s", tempstr);
								string[i] = tempstr;
								i++;
							}
						} while (fgetc(fpin) != EOF);
						string[i] = '\0';
						string_max = i;

						i = 0;
						if ((fpin = fopen("temp_id.txt", "r")) == NULL)		/*读取文件，构造临时变量表*/
							printf("\n\nError:The file temp_id is NULL\n");
						else
							do
							{
								if (fgetc(fpin) == EOF)
									break;
								else
								{
									fseek(fpin, -1L, 1);
									tempstr = (char*)malloc(3 * sizeof(char));
									fscanf(fpin, "%s", tempstr);
									tempvar[i] = tempstr;
									i++;
								}
							} while (fgetc(fpin) != EOF);
							tempvar[i] = '\0';
							tempvar_max = i;

							i = 0;

							printf("\n\n\n状态栈\t\t\t\t\t符号栈\t\t\t\t\t余留串\t\t\t\t\t\t\t\t\t\t动作\n");
							printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------");
							
							LRdriver(st);
}


