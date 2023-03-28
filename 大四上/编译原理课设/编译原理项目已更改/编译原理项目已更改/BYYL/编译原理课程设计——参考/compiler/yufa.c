/***************************
 �﷨����
****************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#define MAXSIZE  500				//ջ��С
#define true 1
#define false 0

/*����ջ*/
typedef struct 
{
	char *ch_word[MAXSIZE];			//��Ŵ���
	int st_place[MAXSIZE];			//������Ϣ
	int ch[MAXSIZE];				//��ŷ���(���)
	int  sta[MAXSIZE];				//���״̬
	int  st_TC[MAXSIZE];
	int  st_FC[MAXSIZE];
	int	 top;
}stack;

struct formula
{
	char *opr;
	char *op1;
	char *op2;
	char *results;
	int result;

};
struct formula gen[MAXSIZE];

struct inds
{
	char *instr;					//�ַ��� 
	int sty;						//����
};
struct inds input[MAXSIZE];
int intop;							//ָ��ǰ���봮�ַ�


int error;							//�����־

/* ����LR������*/

struct tableaction					//����action������
{
	char c;							//����
	int  s;							//״̬
 }ACTION[63][29]={0};					

 int GOTO[48][15]={0};				//����goto��

struct tableproduction				//�������ʽ���Ա�
{
	int word_number;				//����ʽ�󲿱��
	int Pro_place;					//����ʽ�󲿷��ŵ���������
	int word_count;					//����ʽ�Ҳ��ķ����ŵĸ���
	int Pro_TC;
	int Pro_FC;
}production[33]={0};

char *string[MAXSIZE];				//���ű�
int string_max=0;
char *tempvar[MAXSIZE];				//��ʱ������
int tempvar_max;
int  tempvar_cur=0;

int T=0;
char *tempstr;
int NXQ=100;
int TS;								//ջ��״̬�ţ�TopStat��
int IS;								//��ǰ�������(InpSym)
int NS;								//��Լ��GOTO��������״̬(NewStat)
int PL;								//��i������ʽ����(���)(Production_left)

//��ջ
void push(stack *st,char *chword,int x,int y,int z,int t,int f)
{
     if(st->top==MAXSIZE-1) printf("ջ���� ��\n");
	 else
	 {
		 st->top++;
		 st->ch_word[st->top]=chword;
		 st->st_place[st->top]=z;
		 st->ch[st->top]=x;
		 st->sta[st->top]=y;
		 st->st_TC[st->top]=t;
		 st->st_FC[st->top]=f;
	 }
}

//��ջ
void pop(stack *st,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		if(st->top<0)
			printf("ջ�����!\n");
		else
			st->top--;
	}
};

int Entry(char *buf)								//��bufΪ������ű�
{            
    int i=0;
	int temp;
	for(i=0;i<string_max;i++)
	{
		if(strcmp(string[i],buf)==0)
			return(i);
	}
	string[string_max]=buf;
	temp=string_max;
	string_max++;
	printf("the %s is defined now",string[temp]);
	return(temp);
}
int NewTemp()
{
	int num;
	string[string_max]=tempvar[tempvar_cur];
	num=string_max;
	string_max++;
	tempvar_cur++;
	return num;
}
	
int Merge(int p1,int p2)
{
	int p;
	if(!p2)
		return p1;
	else
	{
		p=p2;
		while(gen[p].result)
			p=gen[p].result;
		gen[p].result=p1;
		return p2;
	}
}

void BackPatch(int p,int t)
{
	int q1;
	int q=p;
	while(q)
	{
		q1=gen[q].result;
		gen[q].result=t;
		q=q1;
	}
}

void act(stack *st,int num)
{
	
	if(num==6||num==7||num==28)//||num==2||num==3)
	{
		production[ACTION[TS][IS].s].Pro_place=Entry(st->ch_word[st->top]);
	}
	else if(num==5||num==8||num==9||num==23||num==24||num==25)
	{
		production[ACTION[TS][IS].s].Pro_place=st->st_place[st->top];
	}
	else if(num==10)
	{
		tempstr=(char *)malloc(3*sizeof(char));
		tempstr=":=";
		gen[NXQ].opr=tempstr;
		gen[NXQ].op1=st->ch_word[st->top-2];
		gen[NXQ].op2=string[st->st_place[st->top]];
		gen[NXQ].result=0;
		NXQ++;
//		printf("\nGEN(:= %s,0,%s)\n",st->ch_word[st->top-2],string[st->st_place[st->top]]);
	}
	else if(num==11)
	{
		production[ACTION[TS][IS].s].Pro_place=NewTemp();
		tempstr=(char *)malloc(2*sizeof(char));
		tempstr="+";
		gen[NXQ].opr=tempstr;
		gen[NXQ].op1=string[st->st_place[st->top-2]];
		gen[NXQ].op2=string[st->st_place[st->top]];
		gen[NXQ].results=string[production[ACTION[TS][IS].s].Pro_place];
		NXQ++;
//		printf("\nGEN(+ %s,%s,%s)\n",string[st->st_place[st->top-2]],string[st->st_place[st->top]],string[production[ACTION[TS][IS].s].Pro_place]);
	}
	else if(num==14)
	{
		production[ACTION[TS][IS].s].Pro_place=st->st_place[st->top-1];
	}
	else if(num==15)
	{
		BackPatch(st->st_TC[st->top],st->st_FC[st->top-1]);
		gen[NXQ].opr="j";
		gen[NXQ].op1="0";
		gen[NXQ].op2="0";
		gen[NXQ].result=st->st_FC[st->top-1];
		NXQ++;
		production[ACTION[TS][IS].s].Pro_TC=st->st_TC[st->top-1];
	}
	else if(num==17)
	{
		production[ACTION[TS][IS].s].Pro_TC=NXQ;
		production[ACTION[TS][IS].s].Pro_FC=NXQ+1;
		gen[NXQ].opr=string[st->st_place[st->top-1]];
		gen[NXQ].op1=string[st->st_place[st->top-2]];
		gen[NXQ].op2=string[st->st_place[st->top]];
		gen[NXQ].result=0;
		NXQ++;
		gen[NXQ].opr="j";
		gen[NXQ].op1="0";
		gen[NXQ].op2="0";
		gen[NXQ].result=0;
		NXQ++;
//		printf("\nGEN(%s,%s,%s,0)\n",string[st->st_place[st->top-1]],string[st->st_place[st->top-2]],string[st->st_place[st->top]]);
	}
	else if(num==18)
	{
		production[ACTION[TS][IS].s].Pro_TC=Merge(T,st->st_FC[st->top]);
	}
	else if(num==20)
	{
		BackPatch(st->st_TC[st->top-2],NXQ);
		gen[NXQ].opr="return";
		gen[NXQ].op1="0";
		gen[NXQ].op2="0";
		gen[NXQ].result=0;
		NXQ++;
		gen[NXQ].result=99;
		printf("success");
	}
	else if(num==22)
	{
		production[ACTION[TS][IS].s].Pro_TC=0;

	}
}
void LRdriver(stack *st)					//LR����������
{
	int l;
	TS=st->sta[st->top];				//ջ��״̬�ţ�TopStat��
	IS=input[intop].sty;				//��ǰ�������(InpSym)
//	int NS;									//��Լ��GOTO��������״̬(NewStat)
//	int PL;									//��i������ʽ����(���)(Production_left)	
	while((ACTION[TS][IS].c!='A')&&(!error))//AΪacc
	{										/*�����������*/
		printf("\n");						
		for(l=0;l<=st->top;l++)
			printf("%d",st->sta[l]);
		if(l>=6)
			printf("\t");
		else
			printf("\t\t");
		for(l=0;l<=st->top;l++)
			printf("%d",st->ch[l]);
		if(l>=6)
			printf("\t");
		else
			printf("\t\t");
		for(l=intop;input[l].sty!=100;l++)
			printf("%-s",input[l].instr);

		if(ACTION[TS][IS].c=='\0')			//��������ΪERROR
		{
			error=1;
		}
		else if(ACTION[TS][IS].c=='S')		//��������Ϊ�ƽ���s��
		{
			push(st,input[intop].instr,input[intop].sty,ACTION[TS][IS].s,0,0,0);
			if(input[intop].sty==6)
				BackPatch(st->st_TC[st->top-1],NXQ);
			else if(input[intop].sty==7)
			{
				T=NewTemp();
				T=Merge(NXQ,st->st_TC[st->top-1]);
				gen[NXQ].opr="j";
				gen[NXQ].op1="0";
				gen[NXQ].op2="0";
				gen[NXQ].result=0;
				NXQ++;
				BackPatch(st->st_FC[st->top-3],NXQ);
			}
			else if(input[intop].sty==8)
			{
				st->st_FC[st->top]=NXQ;
			}
			else if(input[intop].sty==9)
			{
				BackPatch(st->st_TC[st->top-1],NXQ);
				st->st_TC[st->top]=st->st_FC[st->top-1];
				st->st_FC[st->top]=st->st_FC[st->top-2];
			}
			intop++;
			printf("\ts%d",ACTION[TS][IS].s);
		}
		else if(ACTION[TS][IS].c=='r')		//��������Ϊ��Լ��r��
		{
			act(st,ACTION[TS][IS].s);
			pop(st,production[ACTION[TS][IS].s].word_count);
			PL=production[ACTION[TS][IS].s].word_number;//Production_left
			NS=GOTO[(st->sta[st->top])][production[ACTION[TS][IS].s].word_number-29];//(NewStat)
			push(st,input[intop].instr,PL,NS,production[ACTION[TS][IS].s].Pro_place,production[ACTION[TS][IS].s].Pro_TC,production[ACTION[TS][IS].s].Pro_FC);
			printf("\tr%d",ACTION[TS][IS].s);
		}
		TS=st->sta[st->top];
		IS=input[intop].sty;
	}
	if(!error)
	{
		printf("\n");
		for(l=0;l<=st->top;l++)
			printf("%d",st->sta[l]);
		printf("\t\t");
		for(l=0;l<=st->top;l++)
			printf("%d",st->ch[l]);
		printf("\t");
		for(l=intop;input[l].sty!=100;l++)
			printf("%s",input[l].instr);
		printf("\tAccepted!\n");
	}
	else
		printf("\nIt must be an error here,Please check it again!\n");
};


void yufa()
{	
	FILE *fpin;
	stack *st=(stack*)malloc(sizeof(stack));		//����ջ
	char file_token[]="token.txt";
	char file_goto[]="goto.txt";
	char file_action[]="action.txt";
	char file_proinfo[]="proinfo.txt";
	char file_infost[]="infost.txt";
	int x_location;									//x����
	int y_location;									//y����
	int goto_value;									//goto���Ա��е�״ֵ̬
	char action_act;								//action�������еĶ���
	int action_state;								//action�������е�״̬
	int pro_word_number;							//����ʽ���Ա��е�word_number
	int pro_word_count;								//����ʽ���Ա��е�word_count
	int i=0;
	int j=0;
	int t=0;
	tempstr=(char *)malloc(6*sizeof(char));	//�ݴ��token�ļ������Ĵ���
	for(t=0;t<MAXSIZE;t++)
	{
		st->ch[t]=100;
	}
	st->top =0;
	st->ch[0]=0;									//��ʼ��'#'��ջ
	st->sta[0]=0;
	if((fpin=fopen(file_token,"r"))==NULL)			/*��ȡtoken�ļ�*/
		printf("Error:The file token is NULL");
	else
		do
		{
			if(fgetc(fpin)==EOF)
				break;
			else
			{
				fseek(fpin,-1L,1);
				fscanf(fpin,"%s %d",tempstr,&input[i].sty);
				input[i].instr=tempstr;
				printf("%s ",input[i].instr);
				i++;
				tempstr=(char *)malloc(6*sizeof(char));
			}
		}while(fgetc(fpin)!=EOF);
	fclose(fpin);
	input[i].instr='\0';								//��β
	input[i].sty=100;
	intop=0;
	i=0;

	if((fpin=fopen(file_goto,"r"))==NULL)			/*��ȡgoto�ļ�������goto������*/
		printf("Error:The file goto is NULL");
	else
		do
		{
			if(fgetc(fpin)==EOF)
				break;
			else
			{
				fseek(fpin,-1L,1);
				fscanf(fpin,"%d %d %d",&x_location,&y_location,&goto_value);
				GOTO[x_location][y_location-29]=goto_value;			
			}
		}while(fgetc(fpin)!=EOF);
		fclose(fpin);

	if((fpin=fopen(file_action,"r"))==NULL)			/*��ȡaction�ļ�������action������*/
		printf("Error:The file action is NULL");
	else
		do
		{
			if(fgetc(fpin)==EOF)
				break;
			else
			{
				fseek(fpin,-1L,1);
				fscanf(fpin,"%d %d %c %d",&x_location,&y_location,&action_act,&action_state);
				ACTION[x_location][y_location].c=action_act;
				ACTION[x_location][y_location].s=action_state;
			}
		}while(fgetc(fpin)!=EOF);
	fclose(fpin);

	if((fpin=fopen(file_proinfo,"r"))==NULL)		/*��ȡproinfo�ļ����������ʽ���Ա�*/
		printf("Error:The file proinfo is NULL");
	else
		do
		{
			if(fgetc(fpin)==EOF)
				break;
			else
			{
				fseek(fpin,-1L,1);
				fscanf(fpin,"%d %d %d",&x_location,&pro_word_number,&pro_word_count);
				production[x_location].word_number=pro_word_number;
				production[x_location].word_count=pro_word_count;
			}
		}while(fgetc(fpin)!=EOF);
	fclose(fpin);

	i=0;
	if((fpin=fopen("id.txt","r"))==NULL)		/*��ȡ�ļ����������ʽ���Ա�*/
		printf("Error:The file proinfo is NULL");
	else
		do
		{
			if(fgetc(fpin)==EOF)
				break;
			else
			{
				fseek(fpin,-1L,1);
				tempstr=(char *)malloc(5*sizeof(char));
				fscanf(fpin,"%s",tempstr);
				string[i]=tempstr;
				i++;
			}
		}while(fgetc(fpin)!=EOF);
	string[i]='\0';
	string_max=i;

	i=0;
	if((fpin=fopen("temp_id.txt","r"))==NULL)		/*��ȡ�ļ����������ʽ���Ա�*/
		printf("Error:The file temp_id is NULL");
	else
		do
		{
			if(fgetc(fpin)==EOF)
				break;
			else
			{
				fseek(fpin,-1L,1);
				tempstr=(char *)malloc(3*sizeof(char));
				fscanf(fpin,"%s",tempstr);
				tempvar[i]=tempstr;
				i++;
			}
		}while(fgetc(fpin)!=EOF);
	tempvar[i]='\0';
	tempvar_max=i;
/*
	for(i=0;i<15;i++)
		nterm[i].nt_num=(i+29);
*/
	i=0;
	printf("\n״̬ջ\t\t����ջ\t\t������\t\t\t����");
//	printf("\n��������ԪʽΪ:\n");
	LRdriver(st);
	for(i=100;gen[i].result!=99;i++)
	{
		if(gen[i].results!=NULL)
			printf("%d:GEN(%s,%s,%s,%s)\n",i,gen[i].opr,gen[i].op1,gen[i].op2,gen[i].results);
		else
			printf("%d:GEN(%s,%s,%s,%d)\n",i,gen[i].opr,gen[i].op1,gen[i].op2,gen[i].result);
	}
}
