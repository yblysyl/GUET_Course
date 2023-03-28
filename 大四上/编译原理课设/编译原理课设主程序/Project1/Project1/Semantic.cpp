/***************************
 �������
****************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h> 
#include<windows.h>  
#define MAXSIZE  500				//ջ��С
#include "common.h"

extern struct inds input[MAXSIZE];
extern struct tableaction ACTION[63][29];
extern int GOTO[48][15];
extern struct tableproduction production[33];
extern char* string[MAXSIZE];				//���ű�
extern char* tempvar[MAXSIZE];				//��ʱ������
extern int string_max;
extern int tempvar_max;
extern char* tempstr;
extern int error;//�����־

extern void pop(stack* st, int n);
extern void push(stack* st, char* chword, int x, int y, int z, int t, int f);
extern int intop;							//ָ��ǰ���봮�ַ�

extern int TS;								//ջ��״̬�ţ�TopStat��
extern int IS;								//��ǰ�������(InpSym)
extern int NS;								//��Լ��GOTO��������״̬(NewStat)
extern int PL;								//��i������ʽ����(���)(Production_left)

int T = 0;
int tempvar_cur = 0;
int NXQ = 100;

struct formula   //��Ԫʽ�ṹ�� 
{
	char opr[20];  //������ 
	char op1[20];	//������ 
	char op2[20];	//������ 
	char results[20];	//��� 
	int result;

};
struct formula gen[MAXSIZE];

int Entry(char* buf)								//��bufΪ���飬����ű�
{
	int i = 0;
	int temp;
	for (i = 0; i < string_max; i++)	//��buf��ֵ�ͷ��ű����ֵ�Ƚϣ�����򷵻����� 
	{
		if (strcmp(string[i], buf) == 0)
			return(i);
	}
	string[string_max] = buf;	//��������µ�bufֵ�����ű��� 
	temp = string_max;
	string_max++; //���ű���+1 
	//printf("the %s is defined now",string[temp]); //���Ҵ�ӡ�¼����ֵ���ڱ����� 
	return(temp);
}
int NewTemp()    //������ʱ������Ԫ  ��һ������������ 
{
	int num;
	string[string_max] = tempvar[tempvar_cur];
	num = string_max;
	string_max++;
	tempvar_cur++;
	return num; // ������ʱ�����ĺ�����ÿ�ε��ö�����һ���µ���ʱ����������ֵΪ�ñ����ı��
}

int Merge(int p1, int p2)  // �����ס�ָ�롱�ֱ�Ϊp1��p2���������ϲ�Ϊһ�������������������ס�ָ�롰  
{
	int p;				//�����������false��next���ϲ�һ��֮��ͨ��backpatch���� 
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

void BackPatch(int p, int t)  //����Ԫʽ���t������pΪ�׵����� ������ÿ����Ԫʽ��Result���дΪt��ֵ�� 
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

void act(stack* st, int num)	//ִ�й�Լ����ʽ��Ӧ�����嶯�� 
{

	if (num == 6 || num == 7 || num == 28)   //THEN ELSE �� 
	{
		production[ACTION[TS][IS].s].Pro_place = Entry(st->ch_word[st->top]);//��Լ����ʽ �����ŵ���������= ����Ҵ��Ķ�Ӧ�ı�ŵ�����ֵ 
	}
	else if (num == 5 || num == 8 || num == 9 || num == 23 || num == 24 || num == 25)//IF|WHILE|DO|.|��= |��|��ؽ���ת��䣨j��x,x,x�� //���������ΪɶIF��ֻ�ܽ�һ����=��ֵ��� 
	{
		production[ACTION[TS][IS].s].Pro_place = st->st_place[st->top]; //��Լ����ʽ�󲿷��ŵ��������� = �Ҳ�������Ϣ������ 
	}
	else if (num == 10)				//int ֻҪ�������Σ��ȸ�ֵ��Tĳ ����ֵ��䣩 
	{
		tempstr = (char*)malloc(3 * sizeof(char));
		strcpy(tempstr , ":=");				//����������ָ�� 
		strcpy(gen[NXQ].opr , tempstr);   //������ 
		strcpy(gen[NXQ].op1 , st->ch_word[st->top - 2]);   //������ 
		strcpy(gen[NXQ].op2 , string[st->st_place[st->top]]);	//������ 
		gen[NXQ].result = 0;	//������� 
		NXQ++;
		//		printf("\nGEN(:= %s,0,%s)\n",st->ch_word[st->top-2],string[st->st_place[st->top]]);
	}
	else if (num == 11)//��var��֮��֮�俴A+1 
	{
		production[ACTION[TS][IS].s].Pro_place = NewTemp();//�Թ�Լ����ʽ ��ֵ�������ڱ���T�� 
		tempstr = (char*)malloc(2 * sizeof(char));
		strcpy(tempstr , "+");
		strcpy(gen[NXQ].opr , tempstr);
		strcpy(gen[NXQ].op1 , string[st->st_place[st->top - 2]]);
		strcpy(gen[NXQ].op2 , string[st->st_place[st->top]]);
		strcpy(gen[NXQ].results , string[production[ACTION[TS][IS].s].Pro_place]);
		NXQ++;
		//		printf("\nGEN(+ %s,%s,%s)\n",string[st->st_place[st->top-2]],string[st->st_place[st->top]],string[production[ACTION[TS][IS].s].Pro_place]);
	}
	else if (num == 14)//��*��  x+x��=T   *��������ʹ��x+x����ֵ�ܹ���ΪTֵ�����ã��������ջ�е�һ��ֵX 
	{
		production[ACTION[TS][IS].s].Pro_place = st->st_place[st->top - 1];// ��Լ����ʽ�󲿷��ŵ��������� = �Ҳ�������Ϣ������ջ����һ��ֵ 
	}
	else if (num == 15)// ��/ ��  whileһ�����ת�ص�100��
	{
		BackPatch(st->st_TC[st->top], st->st_FC[st->top - 1]);//�ٳ�����һ����������� 
		strcpy(gen[NXQ].opr , "j");
		strcpy(gen[NXQ].op1 , "0");
		strcpy(gen[NXQ].op2 , "0");
		gen[NXQ].result = st->st_FC[st->top - 1];//���ȡ�ٳ�����һֵ 
		NXQ++;
		production[ACTION[TS][IS].s].Pro_TC = st->st_TC[st->top - 1];//��Լ����ʽ�󲿷��ŵ��������� = ���������ջ����һ��ֵ 
	}

	else if (num == 17)//<=      ������WHILE������ֱ�ӣ�j,0,0,0�� 
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


	else if (num == 18)//> ����WHILE��������ת��ִ��������ڵ��У�j,0,0,x��
	{
		production[ACTION[TS][IS].s].Pro_TC = Merge(T, st->st_FC[st->top]);
	}

	else if (num == 20) //<>   ������j,0,0,0�� 
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

	else if (num == 22) //;    ���int��û�ֺ� ��ȫ����GEN��0��0��0��0�� 
	{
		production[ACTION[TS][IS].s].Pro_TC = 0;

	}
}

void yuyi() {
	printf("\n\n\n\n====================================================����������====================================================\n\n");
	if (error) {
		printf("\n���ȼ������﷨���޸��﷨��������������У���\n");
		return;
	}
	int t;
	stack* st = (stack*)malloc(sizeof(stack));		//����ջ
	for (t = 0; t < MAXSIZE; t++)
	{
		st->ch[t] = 100;
	}
	st->top = 0;
	st->ch[0] = 0;									//��ʼ��'#'��ջ
	st->sta[0] = 0;
	intop = 0;

	TS = st->sta[st->top];				//ջ��״̬�ţ�TopStat��
	IS = input[intop].sty;				//��ǰ�������(InpSym)

	while ((ACTION[TS][IS].c != 'A') && (!error))//AΪacc
	{

		if (ACTION[TS][IS].c == 'S')		//��������Ϊ�ƽ���s��
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
		else if (ACTION[TS][IS].c == 'r')		//��������Ϊ��Լ��r��
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


	printf("\n\n��������ԪʽΪ:\n\n");
	int i;
	for (i = 100; gen[i].result != 99; i++)
	{
		if (gen[i].results != NULL)
			printf("%d:GEN(%s,%s,%s,%s)\n", i, gen[i].opr, gen[i].op1, gen[i].op2, gen[i].results);
		else
			printf("%d:GEN(%s,%s,%s,%d)\n", i, gen[i].opr, gen[i].op1, gen[i].op2, gen[i].result);
	}
}


