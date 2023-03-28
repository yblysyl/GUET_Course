/***************************
		 词法分析
***************************/
/*
 标识符 1
 整数   2
 关键字 3
 运算符 4
 分隔符 5
*/
#include<stdlib.h>
#include<stdio.h>
#include<windows.h>
#include<string.h>
#define MAX 10000								//二元式行数
#define MAXID 8
#define MAXNUM "65535"

//保存二元式的结构体
struct ds
{
	char* idstr;								//字符串 
	int style;									//类型
};
struct ds data[MAX];
long num = 0;
int wrong = 0;
int line = 1;
int errorno = 0;


/*******************************************
 初始化函数
********************************************/
void init()
{
	char* key[] = { " ","BEGIN","END","IF","THEN","ELSE","WHILE","DO","INTEGER","VAR" };	//关键字

	char* separator[] = { " ",";",".",":=",",","(",")",":" };								//分隔符

	char* operation[] = { " ","+","-","*","/","<","<=",">",">=","<>","=" };					//运算符
	FILE* fp;
	int i;
	fp = fopen("keyword.txt", "w");//创建各类此文的文本文件
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

	fp = fopen("id.txt", "w");		//符号表
	fclose(fp);
	fp = fopen("int.txt", "w");
	fclose(fp);
	fp = fopen("token.txt", "w");
	fclose(fp);
}


/*******************************************
 根据不同命令查表或造表函数
********************************************/
int find(char* buf, int type, int command)				//command=1 只要查表 command=2 找不到时 要加进去表中
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
			return(number);							//若找到，返回在相应表中的序号
		}
		else
			c = fgetc(fp);
	}
	if (command == 1)									//找不到，当command=1，返回0
	{
		fclose(fp);
		return(0);
	}
	switch (type)									//当command=2,向表中追加标识符 
	{
	case 1: fp = fopen("id.txt", "a"); break;
	case 2: fp = fopen("int.txt", "a"); break;
	case 3: fp = fopen("keyword.txt", "a"); break;
	case 4: fp = fopen("operation.txt", "a"); break;
	case 5: fp = fopen("separator.txt", "a");
	}
	fprintf(fp, "%s\n", buf);
	fclose(fp);
	return(0);										//造表时，将字符串添加到表尾并返回序号值
}


/*******************************************
 整数处理函数
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
	find(buffer, 2, 2);								//先查整数表，若找不到则插入整数表
	fp = fopen("token.txt", "a");
	fprintf(fp, "%s\t\t\t2\n", buffer);
	data[num].idstr = buffer;
	data[num].style = 2;
	num++;
	fclose(fp);
}


/*******************************************
 字符串处理函数
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
	result = find(buffer, 3, 1);						  //先查关键字表
	fp = fopen("token.txt", "a");
	if (result != 0)
	{
		result += 2;
		fprintf(fp, "%s\t\t\t%d\n", buffer, result);    //若找到，写入token文件
		data[num].idstr = buffer;
		data[num].style = result;
		num++;
	}
	else
	{
		result = find(buffer, 1, 2);					//若找不到，则非关键字，查标识符表，还找不到则插入标识符表
		fprintf(fp, "%s\t\t\t1\n", buffer, 1);
		data[num].idstr = buffer;
		data[num].style = 1;
		num++;
	}
	fclose(fp);
}


/*******************************************
 出错处理函数
********************************************/
void error_manage(char error, int lineno)
{
	printf("error: %c ,line %d", error, lineno);    //报告出错符号和所在行数
}


/*******************************************
 扫描程序
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
	while (ch != EOF)													//一直扫描到文件末尾
	{
		i = 0;
		if (((ch >= 'A') && (ch <= 'Z')))									//以字母开头
		{
			while (((ch >= 'A') && (ch <= 'Z')) || ((ch >= '0') && (ch <= '9')))
			{
				array[i++] = ch;
				ch = fgetc(fpin);
			}
			word = (char*)malloc((i + 1) * sizeof(char));
			memcpy(word, array, i);
			word[i] = '\0';
			ch_manage(word);										//处理字符串
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
				fseek(fpin, -1L, SEEK_CUR);							//文件指针后退一个字节
		}
		else if (ch >= '0' && ch <= '9')									//以数字开头
		{
			while (ch >= '0' && ch <= '9')
			{
				array[i++] = ch;
				ch = fgetc(fpin);
			}
			word = (char*)malloc((i + 1) * sizeof(char));
			memcpy(word, array, i);
			word[i] = '\0';
			int_manage(word);										//处理整数
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
			;														//消除空格符和水平制表符
		else if (ch == '\n')
			line++;													//消除回车并记录行数
		else if (ch == '/')
		{															//消除注释
			ch = fgetc(fpin);
			if ((ch != '*') && (ch != '/'))
			{														//若为除号，写入输出文件
				fpout = fopen("token.txt", "a");
				fprintf(fpout, "/\t\t\t15\n");
				data[num].idstr = "/";
				data[num].style = 15;
				num++;
				fclose(fpout);
				fseek(fpin, -1L, SEEK_CUR);
			}
			else if (ch == '/')										//符号为//，消除此行后面的字符
			{
				ch = fgetc(fpin);
				while (ch != '\n')
					ch = fgetc(fpin);
				line++;
			}
			else if (ch == '*')
			{														//符号为/*，消除/*和*/之间的字符
				count = 0;
				ch = fgetc(fpin);
				while (count != 2)
				{													//当扫描到*且紧接着下一个字符为/,才是注释的结束*/
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
		{														//首字符为其它字符,即运算符或分隔符或非法字符*/
			array[0] = ch;
			ch = fgetc(fpin);										//再读入下一个字符，判断是否为双字符运算、分隔符
			if (ch != EOF)
			{
				array[1] = ch;
				word = (char*)malloc(3 * sizeof(char));
				memcpy(word, array, 2);
				word[2] = '\0';
				result = find(word, 4, 1);							//先检索是否为双字符运算符或分隔符
				result2 = find(word, 5, 1);
				if ((result == 0) && (result2 == 0))					//若不是
				{
					word = (char*)malloc(2 * sizeof(char));
					memcpy(word, array, 1);
					word[1] = '\0';
					result = find(word, 4, 1);						//检索是否为单字符运算、分隔符
					result2 = find(word, 5, 1);
					if (result != 0) style = 4;
					if (result2 != 0) style = 5;
					if (result == 0 && result2 == 0)
					{											//若还不是，则为非法字符
						printf("\n");
						error_manage(array[0], line);
						errorno++;
						fseek(fpin, -1L, SEEK_CUR);
					}
					else
					{											//若为单字符运算、分割符，写入token文件并将扫描文件指针回退一个字符*/
						fpout = fopen("token.txt", "a");
						result += 11;
						result2 += 21;
						result = (style == 4) ? result : result2;
						fprintf(fpout, "%s\t\t\t%d\n", word, result);
						data[num].idstr = word;
						data[num].style = result;
						num++;
						fclose(fpout);
						fseek(fpin, -1L, SEEK_CUR);				//文件指针后退一个字节
					}
				}
				else
				{												//若为双字符运算、分隔符，写token文件
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
				fseek(fpin, -1L, SEEK_CUR);						//文件指针后退一个字节
		}
		ch = fgetc(fpin);
	}
	fpout = fopen("token.txt", "a");
	fprintf(fpout, "#\t\t\t0\n");
	data[num].idstr = "#";
	data[num].style = 0;
	num++;
	fclose(fpout);
	printf("\nThere are %d error(s).\n\n", errorno);				//报告错误字符个数
}

void cifa()
{
	int j = 0;

	init();														//初始化
	scanner();												//扫描源程序
	printf("====================================================词法分析结果====================================================\n");
	printf("\n二元式流 :\n\n");
	while (data[j].idstr != NULL)								//打印二元式流
	{
		printf("%s\t\t%d\t\t\n", data[j].idstr, data[j].style);
		j++;
	}
}

