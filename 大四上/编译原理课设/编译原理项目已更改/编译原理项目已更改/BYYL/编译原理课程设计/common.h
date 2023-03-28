#pragma once
#ifndef _COMMON_H
#define _COMMON_H 1

#define MAXSIZE  500				//ջ��С

/*����ջ*/
typedef struct
{
	char* ch_word[MAXSIZE];			//��ŵ���
	int st_place[MAXSIZE];			//������Ϣ
	int ch[MAXSIZE];				//��ŷ���(���),ģ�����ջ 
	int  sta[MAXSIZE];				//���״̬��ģ��״̬ջ--- 
	int  st_TC[MAXSIZE];
	int  st_FC[MAXSIZE];
	int	 top;
}stack;

struct inds
{
	char* instr;					//�ַ��� 
	int sty;						//����
};

struct tableaction					//����action������
{
	char c;							//����
	int  s;							//״̬
};

struct tableproduction				//�������ʽ���Ա�
{
	int word_number;				//����ʽ�󲿱��
	int word_count;					//����ʽ�Ҳ��ķ����ŵĸ���

	int Pro_place;					//����ʽ�󲿷��ŵ���������
	int Pro_TC;
	int Pro_FC;
};

#endif
