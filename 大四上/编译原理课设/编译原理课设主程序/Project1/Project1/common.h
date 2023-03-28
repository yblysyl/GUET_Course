#pragma once
#ifndef _COMMON_H
#define _COMMON_H 1

#define MAXSIZE  500				//栈大小

/*构造栈*/
typedef struct
{
	char* ch_word[MAXSIZE];			//存放单词
	int st_place[MAXSIZE];			//语义信息
	int ch[MAXSIZE];				//存放符号(编号),模拟符号栈 
	int  sta[MAXSIZE];				//存放状态，模拟状态栈--- 
	int  st_TC[MAXSIZE];
	int  st_FC[MAXSIZE];
	int	 top;
}stack;

struct inds
{
	char* instr;					//字符串 
	int sty;						//类型
};

struct tableaction					//构造action分析表
{
	char c;							//动作
	int  s;							//状态
};

struct tableproduction				//构造产生式属性表
{
	int word_number;				//产生式左部编号
	int word_count;					//产生式右部文法符号的个数

	int Pro_place;					//产生式左部符号的语义属性
	int Pro_TC;
	int Pro_FC;
};

#endif
