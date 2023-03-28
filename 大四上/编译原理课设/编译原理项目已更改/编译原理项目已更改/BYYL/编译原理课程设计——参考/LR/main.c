/***************************
 �﷨����
****************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#define MAXSIZE  1000//ջ��С
#define true 1
#define false 0

/*����ջ*/
typedef struct 
{
	char s[MAXSIZE];//��ŷ���
	int  sta[MAXSIZE];//���״̬
	int	 top;
}stack;

char input[100]={'\0'};
int intop; //ָ��ǰ���봮�ַ�

int error;//�����־

/* ����LR������*/

typedef struct    //����ACTION������
{
	char c;//����
	int  s;//״̬
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

int GOTO[7][2]={						//����GOTO������ṹ
	{1,2},{100,100},{100,100},{100,100},{100,100},{6,2},{100,100}
};

char proleft[4]={'L','L','E','E'};//��i������ʽ����

int is_empty(stack *st)
{
	if(st->top <0) return true;
	else return false;
}
//��ջ
void push(stack *st,char x,int y)
{
     if(st->top==MAXSIZE-1) printf("ջ���� ��\n");
	 else
	 {
		 st->top++;
		 st->s[st->top]=x;
		 st->sta[st->top]=y;
	 }
}

//ջָ�����ƣ�����ջ��Ԫ��
void pop(stack *st,int n)
{
//	stack *st;
	int i;
	for(i=0;i<n;i++)
	{
		if(st->top<0)
			printf("ջ�����!\n");
		else
			st->top--;
	}
};


int find_action(int top)//���ݵ�ǰ������ţ�ת��ACTION������ĵڶ������겢����
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
int find_goto(int s,char t)//���ݵ�ǰ״̬����GOTO������������״̬
{
	if(t=='E') 
		return(GOTO[s][1]);
	else
		return(GOTO[s][0]);
};
int find_proright(int num)//���ع�Լ����ʽ���Ҳ��ķ����ŵĸ���
{
	int count=0;	
	if(num==2) count=1;
	if(num==3) count=1;
	if(num==4) count=1;
	if(num==1) count=3;
	return count;
}
void LRdriver(stack *st)//LR����������
{
	int TS=st->sta[st->top];//ջ��״̬�ţ�TopStat��
	int IS=find_action(intop);//��ǰ������Ŷ�Ӧ�ĵڶ�λ����(InpSym)
	int NS;//��Լ���������״̬(NewStat)
	char PL;//��i������ʽ����(Production_left)
	int l;
	while((ACTION[TS][IS].c!='a')&&(!error))//aΪacc����ʾ��ǰ����������Ϊ����
	{
		printf("\n");/*�����������*/
		for(l=0;l<=st->top;l++)
			printf("%d",st->sta[l]);
		printf("\t");
		for(l=0;l<=st->top;l++)
			printf("%c",st->s[l]);
		printf("\t");
		for(l=intop;input[l]!='\0';l++)
			printf("%c",input[l]);	

		if(ACTION[TS][IS].c=='e')//��������ΪERROR
		{
			error=1;
		}
		else if(ACTION[TS][IS].c=='s')//��������Ϊ�ƽ���s��
		{
			push(st,input[intop],ACTION[TS][IS].s);
			intop++;
			printf("\ts%d",ACTION[TS][IS].s);
		}
		else if(ACTION[TS][IS].c=='r')//��������Ϊ��Լ��r��
		{
			pop(st,find_proright(ACTION[TS][IS].s));//find_proright(ACTION[TS][IS].s)Ϊ��i������ʽ�Ҳ��ķ����ŵĸ���
			PL=proleft[ACTION[TS][IS].s-1];//��i������ʽ����(Production_left)
			NS=find_goto(st->sta[st->top],PL);//��Լ���������״̬(NewStat)
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
	printf("\n������һ���Ŵ����ԣ���β ��\n");
    do
	{ 
		scanf("%c",&cc);
		input[i]=cc;
		i++;
	}while(cc!='#');
	input[i]='\0';
	intop=0;
	i=0;
	printf("״̬ջ\t����ջ\t������\t����");
	LRdriver(st);
}
