/***************************
		 �ʷ�����
***************************/
/*
 ��ʶ�� 1
 ����   2
 �ؼ��� 3
 ����� 4
 �ָ��� 5
*/
#include<stdlib.h>
#include<stdio.h>
#include<windows.h>
#include<string.h>
#define MAX 10000								//��Ԫʽ����
#define MAXID 8
#define MAXNUM "65535"

//�����Ԫʽ�Ľṹ��
struct ds
{
	char* idstr;								//�ַ��� 
	int style;									//����
};
struct ds data[MAX];
long num = 0;
int wrong = 0;
int line = 1;
int errorno = 0;


/*******************************************
 ��ʼ������
********************************************/
void init()
{
	char* key[] = { " ","BEGIN","END","IF","THEN","ELSE","WHILE","DO","INTEGER","VAR" };	//�ؼ���

	char* separator[] = { " ",";",".",":=",",","(",")",":" };								//�ָ���

	char* operation[] = { " ","+","-","*","/","<","<=",">",">=","<>","=" };					//�����
	FILE* fp;
	int i;
	fp = fopen("keyword.txt", "w");//����������ĵ��ı��ļ�
	for (i = 1; i <= 9; i++)
		fprintf(fp, "%s\n", key[i]);
	fclose(fp);
	fp = fopen("separator.txt", "w");
	for (i = 1; i <= 7; i++)
		fprintf(fp, "%s\n", separator[i]);
	fclose(fp);
	fp = fopen("operation.txt", "w");
	for (i = 1; i <= 10; i++)
		fprintf(fp, "%s\n", operation[i]);
	fclose(fp);

	fp = fopen("id.txt", "w");		//���ű�
	fclose(fp);
	fp = fopen("int.txt", "w");
	fclose(fp);
	fp = fopen("token.txt", "w");
	fclose(fp);
}


/*******************************************
 ���ݲ�ͬ������������
********************************************/
int find(char* buf, int type, int command)				//command=1 ֻҪ��� command=2 �Ҳ���ʱ Ҫ�ӽ�ȥ����
{
	int number = 0;
	FILE* fp;
	char c;
	char temp[30];
	int i = 0;
	switch (type)
	{

	case 1: fp = fopen("id.txt", "r"); break;
	case 2: fp = fopen("int.txt", "r"); break;
	case 3: fp = fopen("keyword.txt", "r"); break;
	case 4: fp = fopen("operation.txt", "r"); break;
	case 5: fp = fopen("separator.txt", "r");
	}
	c = fgetc(fp);
	while (c != EOF)
	{
		while (c != '\n')
		{
			temp[i++] = c;
			c = fgetc(fp);
		}
		temp[i] = '\0';
		i = 0;
		number++;
		if (strcmp(temp, buf) == 0)
		{
			fclose(fp);
			return(number);							//���ҵ�����������Ӧ���е����
		}
		else
			c = fgetc(fp);
	}
	if (command == 1)									//�Ҳ�������command=1������0
	{
		fclose(fp);
		return(0);
	}
	switch (type)									//��command=2,�����׷�ӱ�ʶ�� 
	{
	case 1: fp = fopen("id.txt", "a"); break;
	case 2: fp = fopen("int.txt", "a"); break;
	case 3: fp = fopen("keyword.txt", "a"); break;
	case 4: fp = fopen("operation.txt", "a"); break;
	case 5: fp = fopen("separator.txt", "a");
	}
	fprintf(fp, "%s\n", buf);
	fclose(fp);
	return(0);										//���ʱ�����ַ�����ӵ���β���������ֵ
}


/*******************************************
 ����������
********************************************/
void int_manage(char* buffer)
{
	FILE* fp;
	if (strlen(buffer) > 5)
	{
		wrong = 1;
		return;
	}
	if (strlen(buffer) == 5)
	{
		if (strcmp(buffer, MAXNUM) > 0)
			wrong = 1;
		return;
	}
	find(buffer, 2, 2);								//�Ȳ����������Ҳ��������������
	fp = fopen("token.txt", "a");
	fprintf(fp, "%s\t\t\t2\n", buffer);
	data[num].idstr = buffer;
	data[num].style = 2;
	num++;
	fclose(fp);
}


/*******************************************
 �ַ���������
********************************************/
void ch_manage(char* buffer)
{
	FILE* fp;
	int result;
	if (strlen(buffer) > 8)
	{
		wrong = 1;
		return;
	}
	result = find(buffer, 3, 1);						  //�Ȳ�ؼ��ֱ�
	fp = fopen("token.txt", "a");
	if (result != 0)
	{
		result += 2;
		fprintf(fp, "%s\t\t\t%d\n", buffer, result);    //���ҵ���д��token�ļ�
		data[num].idstr = buffer;
		data[num].style = result;
		num++;
	}
	else
	{
		result = find(buffer, 1, 2);					//���Ҳ�������ǹؼ��֣����ʶ�������Ҳ���������ʶ����
		fprintf(fp, "%s\t\t\t1\n", buffer, 1);
		data[num].idstr = buffer;
		data[num].style = 1;
		num++;
	}
	fclose(fp);
}


/*******************************************
 ��������
********************************************/
void error_manage(char error, int lineno)
{
	printf("error: %c ,line %d", error, lineno);    //���������ź���������
}


/*******************************************
 ɨ�����
********************************************/
void scanner()
{
	FILE* fpin, * fpout;
	char filename[20];
	char ch;
	int k = 0;
	int i = 0;
	int count, result;
	char array[30];
	char* word;
	int style = 0;
	int result2 = 0;
	printf("\n please input the source file name:");
	scanf("%s", filename);
	if ((fpin = fopen(filename, "r")) == NULL)
	{
		printf("\ncannot open file\n\n");
		return;
	}
	ch = fgetc(fpin);
	while (ch != EOF)													//һֱɨ�赽�ļ�ĩβ
	{
		i = 0;
		if (((ch >= 'A') && (ch <= 'Z')))									//����ĸ��ͷ
		{
			while (((ch >= 'A') && (ch <= 'Z')) || ((ch >= '0') && (ch <= '9')))
			{
				array[i++] = ch;
				ch = fgetc(fpin);
			}
			word = (char*)malloc((i + 1) * sizeof(char));
			memcpy(word, array, i);
			word[i] = '\0';
			ch_manage(word);										//�����ַ���
			if (wrong)
			{
				errorno++;
				printf("\nerror:out of range :");
				for (k = 0; k < i; k++)
					printf("%c", word[k]);
				printf(" ,line: %d", line);
			}
			wrong = 0;
			if (ch != EOF)
				fseek(fpin, -1L, SEEK_CUR);							//�ļ�ָ�����һ���ֽ�
		}
		else if (ch >= '0' && ch <= '9')									//�����ֿ�ͷ
		{
			while (ch >= '0' && ch <= '9')
			{
				array[i++] = ch;
				ch = fgetc(fpin);
			}
			word = (char*)malloc((i + 1) * sizeof(char));
			memcpy(word, array, i);
			word[i] = '\0';
			int_manage(word);										//��������
			if (wrong)
			{
				errorno++;
				printf("\nerror:out of range :");
				for (k = 0; k < i; k++)
					printf("%c", word[k]);
				printf(" ,line: %d", line);
			}
			wrong = 0;

			if (ch != EOF)
				fseek(fpin, -1L, SEEK_CUR);
		}
		else if ((ch == ' ') || (ch == '\t'))
			;														//�����ո����ˮƽ�Ʊ��
		else if (ch == '\n')
			line++;													//�����س�����¼����
		else if (ch == '/')
		{															//����ע��
			ch = fgetc(fpin);
			if ((ch != '*') && (ch != '/'))
			{														//��Ϊ���ţ�д������ļ�
				fpout = fopen("token.txt", "a");
				fprintf(fpout, "/\t\t\t15\n");
				data[num].idstr = "/";
				data[num].style = 15;
				num++;
				fclose(fpout);
				fseek(fpin, -1L, SEEK_CUR);
			}
			else if (ch == '/')										//����Ϊ//���������к�����ַ�
			{
				ch = fgetc(fpin);
				while (ch != '\n')
					ch = fgetc(fpin);
				line++;
			}
			else if (ch == '*')
			{														//����Ϊ/*������/*��*/֮����ַ�
				count = 0;
				ch = fgetc(fpin);
				while (count != 2)
				{													//��ɨ�赽*�ҽ�������һ���ַ�Ϊ/,����ע�͵Ľ���*/
					count = 0;
					while (ch != '*')
					{
						if (ch == '\n')
							line++;
						ch = fgetc(fpin);
					}
					count++;
					ch = fgetc(fpin);
					if (ch == '/')
						count++;
					else
						ch = fgetc(fpin);
				}
			}
		}
		else
		{														//���ַ�Ϊ�����ַ�,���������ָ�����Ƿ��ַ�*/
			array[0] = ch;
			ch = fgetc(fpin);										//�ٶ�����һ���ַ����ж��Ƿ�Ϊ˫�ַ����㡢�ָ���
			if (ch != EOF)
			{
				array[1] = ch;
				word = (char*)malloc(3 * sizeof(char));
				memcpy(word, array, 2);
				word[2] = '\0';
				result = find(word, 4, 1);							//�ȼ����Ƿ�Ϊ˫�ַ��������ָ���
				result2 = find(word, 5, 1);
				if ((result == 0) && (result2 == 0))					//������
				{
					word = (char*)malloc(2 * sizeof(char));
					memcpy(word, array, 1);
					word[1] = '\0';
					result = find(word, 4, 1);						//�����Ƿ�Ϊ���ַ����㡢�ָ���
					result2 = find(word, 5, 1);
					if (result != 0) style = 4;
					if (result2 != 0) style = 5;
					if (result == 0 && result2 == 0)
					{											//�������ǣ���Ϊ�Ƿ��ַ�
						printf("\n");
						error_manage(array[0], line);
						errorno++;
						fseek(fpin, -1L, SEEK_CUR);
					}
					else
					{											//��Ϊ���ַ����㡢�ָ����д��token�ļ�����ɨ���ļ�ָ�����һ���ַ�*/
						fpout = fopen("token.txt", "a");
						result += 11;
						result2 += 21;
						result = (style == 4) ? result : result2;
						fprintf(fpout, "%s\t\t\t%d\n", word, result);
						data[num].idstr = word;
						data[num].style = result;
						num++;
						fclose(fpout);
						fseek(fpin, -1L, SEEK_CUR);				//�ļ�ָ�����һ���ֽ�
					}
				}
				else
				{												//��Ϊ˫�ַ����㡢�ָ�����дtoken�ļ�
					fpout = fopen("token.txt", "a");
					result += 11;
					result2 += 21;
					result = (result == 11) ? result2 : result;
					fprintf(fpout, "%s\t\t\t%d\n", word, result);
					data[num].idstr = word;
					data[num].style = result;
					num++;
					fclose(fpout);
				}
			}
			else
				fseek(fpin, -1L, SEEK_CUR);						//�ļ�ָ�����һ���ֽ�
		}
		ch = fgetc(fpin);
	}
	fpout = fopen("token.txt", "a");
	fprintf(fpout, "#\t\t\t0\n");
	data[num].idstr = "#";
	data[num].style = 0;
	num++;
	fclose(fpout);
	printf("\nThere are %d error(s).\n\n", errorno);				//��������ַ�����
}

void cifa()
{
	int j = 0;

	init();														//��ʼ��
	scanner();												//ɨ��Դ����
	printf("====================================================�ʷ��������====================================================\n");
	printf("\n��Ԫʽ�� :\n\n");
	while (data[j].idstr != NULL)								//��ӡ��Ԫʽ��
	{
		printf("%s\t\t%d\t\t\n", data[j].idstr, data[j].style);
		j++;
	}
}

