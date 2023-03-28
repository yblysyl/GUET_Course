/***************************
 �﷨����
****************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include "common.h"
#define MAXSIZE  500				             //ջ��С

struct inds input[MAXSIZE];                     //���takon������ݣ����ʡ���Ӧ���룩 
int intop = 0;                                 //��ǰ���дʷ������ĵ����±� 

struct tableaction ACTION[63][29] = { 0 };         //����ģ��SLR�������ACTION������� ��������״̬�� 
int GOTO[48][15] = { 0 };                         //�����洢SLR�������GOTO�������  ��״̬�� 
struct tableproduction production[33] = { 0 };    //�����洢����ʽ�� 

char* string[MAXSIZE];	    	//�洢���ű�
int string_max;                 //���ű�ĳ��� 
char* tempvar[MAXSIZE];			//��ʱ������
int tempvar_max;            	//��ʱ��������

int error;        //��¼������ 
char* tempstr;   //��ʱ�洢����

int TS;							//ջ��״̬�ţ�TopStat��
int IS;							//��ǰ�������(����)
int NS;							//��Լ��GOTO��������״̬(NewStat)
int PL;							//��i������ʽ����(���)(Production_left)

void color(int a)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}

//��ջ
void push(stack* st, char* chword, int x, int y, int z, int t, int f)
{
	if (st->top == MAXSIZE - 1) printf("ջ���� ��\n");
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

//��ջ
void pop(stack* st, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (st->top < 0)
			printf("ջ�����!\n");
		else
			st->top--;
	}
};

void LRdriver(stack* st)					//SLR����������
{
	int l;
	TS = st->sta[st->top];				//ջ��״̬�ţ�TopStat��
	IS = input[intop].sty;				//��ǰ���뵥�ʵı���(InpSym)	
	while ((ACTION[TS][IS].c != 'A') && (!error))//AΪacc
	{										/*�����������*/
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


		if (ACTION[TS][IS].c == '\0')			//��������ΪERROR
		{
			error++;
		}
		else if (ACTION[TS][IS].c == 'S')		//��������Ϊ�ƽ���s��
		{
			//			            ��ǰ����      ���ʶ�Ӧ����   ��һ��״̬ 
			push(st, input[intop].instr, input[intop].sty, ACTION[TS][IS].s, 0, 0, 0);
			//ջָ����һ�������ɶ����ȼ�1�� 
			intop++;
			color(FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			printf("\ts%d", ACTION[TS][IS].s);	//��� : s* 
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_INTENSITY);
		}
		else if (ACTION[TS][IS].c == 'r')		//��������Ϊ��Լ��r��
		{
			//��ջ����ջԪ�ظ����ɲ���ʽ������ԣ�word_count������ 
			pop(st, production[ACTION[TS][IS].s].word_count);
			PL = production[ACTION[TS][IS].s].word_number;//�Զ�����ǰ״ֵ̬Ϊ�±�ȥ�����ʽ���õ�����ʽ��ߵĵ��ʶ�Ӧ��ֵ 
//			      ��ǰ״̬ջֵ            ����ʽ��ߵ��ʶ�Ӧ��ֵ 
			NS = GOTO[(st->sta[st->top])][production[ACTION[TS][IS].s].word_number - 29];//��goto�� �� 
//			            ����        ״̬   
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
	stack* st = (stack*)malloc(sizeof(stack));		//����ջ
	char file_token[] = "token.txt";
	char file_goto[] = "goto.txt";
	char file_action[] = "action.txt";
	char file_proinfo[] = "proinfo.txt";
	//char file_infost[]="infost.txt";
	int x_location;									//x����
	int y_location;									//y����
	int goto_value;									//goto���Ա��е�״ֵ̬
	char action_act;								//action�������еĶ���
	int action_state;								//action�������е�״̬
	int pro_word_number;							//����ʽ���Ա��е�word_number
	int pro_word_count;								//����ʽ���Ա��е�word_count
	int i = 0;
	int j = 0;
	int t = 0;
	tempstr = (char*)malloc(6 * sizeof(char));	//�ݴ��token�ļ������Ĵ���
	printf("\n\n\n\n====================================================�﷨�������====================================================\n");
	printf("\n�������ݣ�\n\n");
	for (t = 0; t < MAXSIZE; t++)//��ʼ��ջ 
	{
		st->ch[t] = 100;
	}
	st->top = 0;
	st->ch[0] = 0;									//��ʼ��'#'��ջ
	st->sta[0] = 0;
	if ((fpin = fopen(file_token, "r")) == NULL)			/*��ȡtoken�ļ�*/
		printf("\n\nError:The file token is NULL\n");
	else
		do
		{
			if (fgetc(fpin) == EOF)
				break;
			else
			{
				fseek(fpin, -1L, 1);
				fscanf(fpin, "%s %d", tempstr, &input[i].sty);//ÿ�ζ�һ�� 
				input[i].instr = tempstr;
				printf("%s ", input[i].instr);//��� 
				i++;
				tempstr = (char*)malloc(6 * sizeof(char));
			}
		} while (fgetc(fpin) != EOF);
		fclose(fpin);
		input[i].instr = '\0';								//��β
		input[i].sty = 100;
		intop = 0;
		i = 0;

		if ((fpin = fopen(file_goto, "r")) == NULL)			/*��ȡgoto�ļ�������goto������*/
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

			if ((fpin = fopen(file_action, "r")) == NULL)			/*��ȡaction�ļ�������action������*/
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

				if ((fpin = fopen(file_proinfo, "r")) == NULL)		/*��ȡproinfo�ļ����������ʽ���Ա�*/
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
					if ((fpin = fopen("id.txt", "r")) == NULL)		/*��ȡ�ļ������������*/
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
						if ((fpin = fopen("temp_id.txt", "r")) == NULL)		/*��ȡ�ļ���������ʱ������*/
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

							printf("\n\n\n״̬ջ\t\t\t\t\t����ջ\t\t\t\t\t������\t\t\t\t\t\t\t\t\t\t����\n");
							printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------");
							
							LRdriver(st);
}


