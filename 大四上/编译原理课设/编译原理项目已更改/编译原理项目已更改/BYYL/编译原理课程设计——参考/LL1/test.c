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
	char s[MAXSIZE];
	int top;
}stack;

//stack *st;
char temp='\0'; //存放栈顶元素

char input[100]={'\0'};
int intop;  //指向当前输入串字符

/* 构造LL(1）预测分析表*/

typedef struct production   //存放产生式
{
	char c;
	char str[100];
 }production;
production table[5][9]={
	 {{'E',"TP"},{'E',"TP"},{'\0','\0'},{'\0','\0'},{'\0','\0'},{'\0','\0'},{'E',"TP"},{'\0','\0'},{'\0','\0'}} ,
	 { {'\0','\0'},{'\0','\0'},{'P',"+TP"},{'P',"-TP"},{'\0','\0'},{'\0','\0'},	{'\0','\0'},{'P',"NULL"},{'P',"NULL"} },
	 {{'T',"FQ"},{'T',"FQ"},{'\0','\0'},{'\0','\0'},{'\0','\0'},{'\0','\0'},{'T',"FQ"},{'\0','\0'},{'\0','\0'} },
	 { {'\0','\0'},{'\0','\0'},{'Q',"NULL"}, {'Q',"NULL"},{'Q',"*FQ"},{'Q',"/FQ"},{'\0','\0'},{'Q',"NULL"},{'Q',"NULL"} },
	 { {'F',"abcdefghijklmnopqistuvwxyz"}, {'F',"0123456789"},{'\0','\0'},{'\0','\0'},{'\0','\0'},{'\0','\0'},{'F',"(E)"},{'\0','\0'},{'\0','\0'} }
  
 };
 int i=0,j=0;


int is_nonterminal(char c)
{
	if((c>='A')&&(c<='Z')) 
		return true;
	else return false;
}

int is_terminal(char c)
{
	if(((c>='0')&&(c<='9'))||((c>='a')&&(c<='z'))||(c=='+')||(c=='-')||(c=='*')||(c=='/')||(c=='(')||(c==')'))
		return true;
	else return false;
}

int is_empty(stack *st)
{
	if(st->top <0) return true;
	else return false;
}
//入栈
void push(stack *st,char x)
{
 //	stack *st;
     if(st->top==MAXSIZE-1) printf("栈上溢出 ！\n");
	 else
	 {
		 st->top++;
		 st->s[st->top]=x;
	 }
}

//栈指针下移，弹出栈顶元素
void pop(stack *st)
{
//	stack *st; 
	if(st->top<0)
		printf("栈下溢出!\n");
	else
		st->top--;
}
//读栈顶元素 维持栈不变
void top(stack *st)
{
  	if(st->top<0)
		printf("栈下溢出，无栈顶元素!\n");
     else
		 temp=st->s[st->top];

}
//取顶元素
char gettop(stack *st)
{
top(st);
pop(st);
return temp;
}

production * find_production(int top, char ch)
{
   //struct production *p;
   char ch_input=input[top];
   char ch_nonter=ch;
   int k,m;
         if(((ch_input>='a')&&(ch_input<='z'))) m=0;
		 if(((ch_input>='0')&&(ch_input<='9'))) m=1;
		 if(ch_input=='+') m=2;
		 if(ch_input=='-') m=3;
		 if(ch_input=='*') m=4;
		 if(ch_input=='/') m=5;
		 if(ch_input=='(') m=6;
		 if(ch_input==')') m=7;
		 if(ch_input=='#') m=8;
   for(i=0;i<5;i++)
	   for(j=0;j<9;j++)
	   {
		   if( table[i][j].c ==ch_nonter)
		   { k=i;
		     break;
		   }
	   }
	  //p=table[k][m];
	   return &table[k][m];

}
void LL1driver(stack *st)
{
	int k=0,l=0;
	char t;
	production *p=(production *)malloc(sizeof(production)); //指向找到的产生式
	printf("\n");
//	while(is_empty(st)==0)
	while(st->top >=0)
	{
		//t=gettop(st);
		top(st);
		//pop(st);
		t=temp;
		if(is_nonterminal(t))
	{
		for(l=0;l<=st->top;l++)
			printf("%c",st->s[l]);
		printf("\t");
		for(l=intop;input[l]!='\0';l++)
			printf("%c",input[l]);
		printf("\t%c-->",t);
		p=find_production(intop,t);
	//	if(p->c!='\0')
	//	{ 
			if((p->str[0]=='a')||(p->str[0]=='0'))
			{
				 printf("%c",input[intop]); 
				 pop(st);
				 push(st,input[intop]);
			}
			else if((p->str[0]=='N')&&(p->str[1]=='U')&&(p->str[2]=='L')&&(p->str[3]=='L'))
			{  
				 k=0;
				 while(p->str[k]!='\0')
				 {
				 printf("%c",p->str [k]);
				 k++;
				 } 
				 printf("\n");
				  pop(st);
			}
			else
			{
			k=0;
			 while(p->str[k]!='\0')
			 {
				 printf("%c",p->str [k]);
				 k++;
			 }
			 pop(st);
			 k--;
             for(;k>=0;k--)
				 push(st,p->str [k]);
			 k=0;
              printf("\n");
			}
	//	}
	//	else printf("语法分析过程有误！\n");
	}
        else
		if((is_terminal(t))&&(t==input[intop]))
		{
			printf("\n");
			for(l=0;l<=st->top;l++)
				printf("%c",st->s[l]);
			printf("\t");
			for(l=intop;input[l]!='\0';l++)
				printf("%c",input[l]);
			pop(st);
			intop++;
			printf("\t终结符 %c 匹配 \n",t);
		}
		else
		if((t=='#')&&(input[intop]=='#'))
		{
		printf("success! \n");
		pop(st);
		}
        else  
			 printf("error! \n");


	}
}



	
void main()
{
//	inition();
	stack *st=(stack*)malloc(sizeof(stack));
	char cc; 
	int t=0;
	for(t=0;t<MAXSIZE;t++)
		st->s[t]='\0';
	st->top =0;
	st->s[0]='#';
	st->top=1;
	st->s[1]='E';
	printf("\n 请输入由终结符构成的算术表达式，以＃结尾 ：\n");
	i=0;
    do
	{ 
		scanf("%c",&cc);
		input[i]=cc;
		i++;
	}while(cc!='#');
	input[i]='\0';
	intop=0;
	 i=0;
	printf("分析栈\t余留串\t产生式");
	LL1driver(st);
}
