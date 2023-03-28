/***************************
 语法分析
****************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#define MAXSIZE  500				//栈大小
#define true 1
#define false 0

/*构造栈*/
typedef struct 
{
	char *ch_word[MAXSIZE];			//存放词文
	int st_place[MAXSIZE];			//语义信息
	int ch[MAXSIZE];				//存放符号(编号)
	int  sta[MAXSIZE];				//存放状态
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
	char *instr;					//字符串 
	int sty;						//类型
};
struct inds input[MAXSIZE];
int intop;							//指向当前输入串字符


int error;							//出错标志

/* 构造LR分析表*/

struct tableaction					//构造action分析表
{
	char c;							//动作
	int  s;							//状态
 }ACTION[63][29]={0};					

 int GOTO[48][15]={0};				//构造goto表

struct tableproduction				//构造产生式属性表
{
	int word_number;				//产生式左部编号
	int Pro_place;					//产生式左部符号的语义属性
	int word_count;					//产生式右部文法符号的个数
	int Pro_TC;
	int Pro_FC;
}production[33]={0};

char *string[MAXSIZE];				//符号表
int string_max=0;
char *tempvar[MAXSIZE];				//临时标量表
int tempvar_max;
int  tempvar_cur=0;

int T=0;
char *tempstr;
int NXQ=100;
int TS;								//栈顶状态号（TopStat）
int IS;								//当前输入符号(InpSym)
int NS;								//规约后GOTO产生的新状态(NewStat)
int PL;								//第i个产生式的左部(编号)(Production_left)

//入栈
void push(stack *st,char *chword,int x,int y,int z,int t,int f)
{
     if(st->top==MAXSIZE-1) printf("栈上溢 ！\n");
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

//出栈
void pop(stack *st,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		if(st->top<0)
			printf("栈下溢出!\n");
		else
			st->top--;
	}
};

int Entry(char *buf)								//以buf为名查符号表
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
void LRdriver(stack *st)					//LR分析器驱动
{
	int l;
	TS=st->sta[st->top];				//栈顶状态号（TopStat）
	IS=input[intop].sty;				//当前输入符号(InpSym)
//	int NS;									//规约后GOTO产生的新状态(NewStat)
//	int PL;									//第i个产生式的左部(编号)(Production_left)	
	while((ACTION[TS][IS].c!='A')&&(!error))//A为acc
	{										/*输出分析过程*/
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

		if(ACTION[TS][IS].c=='\0')			//分析动作为ERROR
		{
			error=1;
		}
		else if(ACTION[TS][IS].c=='S')		//分析动作为移进（s）
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
		else if(ACTION[TS][IS].c=='r')		//分析动作为归约（r）
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
	stack *st=(stack*)malloc(sizeof(stack));		//分析栈
	char file_token[]="token.txt";
	char file_goto[]="goto.txt";
	char file_action[]="action.txt";
	char file_proinfo[]="proinfo.txt";
	char file_infost[]="infost.txt";
	int x_location;									//x坐标
	int y_location;									//y坐标
	int goto_value;									//goto属性表中的状态值
	char action_act;								//action分析表中的动作
	int action_state;								//action分析表中的状态
	int pro_word_number;							//产生式属性表中的word_number
	int pro_word_count;								//产生式属性表中的word_count
	int i=0;
	int j=0;
	int t=0;
	tempstr=(char *)malloc(6*sizeof(char));	//暂存从token文件读出的词文
	for(t=0;t<MAXSIZE;t++)
	{
		st->ch[t]=100;
	}
	st->top =0;
	st->ch[0]=0;									//初始把'#'入栈
	st->sta[0]=0;
	if((fpin=fopen(file_token,"r"))==NULL)			/*读取token文件*/
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
	input[i].instr='\0';								//结尾
	input[i].sty=100;
	intop=0;
	i=0;

	if((fpin=fopen(file_goto,"r"))==NULL)			/*读取goto文件，构造goto分析表*/
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

	if((fpin=fopen(file_action,"r"))==NULL)			/*读取action文件，构造action分析表*/
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

	if((fpin=fopen(file_proinfo,"r"))==NULL)		/*读取proinfo文件，构造产生式属性表*/
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
	if((fpin=fopen("id.txt","r"))==NULL)		/*读取文件，构造产生式属性表*/
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
	if((fpin=fopen("temp_id.txt","r"))==NULL)		/*读取文件，构造产生式属性表*/
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
	printf("\n状态栈\t\t符号栈\t\t余留串\t\t\t动作");
//	printf("\n产生的四元式为:\n");
	LRdriver(st);
	for(i=100;gen[i].result!=99;i++)
	{
		if(gen[i].results!=NULL)
			printf("%d:GEN(%s,%s,%s,%s)\n",i,gen[i].opr,gen[i].op1,gen[i].op2,gen[i].results);
		else
			printf("%d:GEN(%s,%s,%s,%d)\n",i,gen[i].opr,gen[i].op1,gen[i].op2,gen[i].result);
	}
}
