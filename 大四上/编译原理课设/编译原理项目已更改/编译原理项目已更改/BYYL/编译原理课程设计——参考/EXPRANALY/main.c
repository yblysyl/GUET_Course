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
#include<string.h>
#define MAX 10000 //二元式行数
#define MAXID 8
#define MAXNUM "65535"
//保存二元式的结构体
struct ds
{
	char *idstr; //字符串 
	int style; //类型
};
struct ds data[MAX];
long num=0;
int rong=0;
int rongid=0;
int line=1;
int errorno=0;
/*******************************************
 初始化函数
********************************************/
void init()
{             
    char *key[]={" ","BEGIN","END","IF","THEN","ELSE","WHILE","DO","INTEGER","VAR"};     /*语言所有关键字*/

    char *limit[]={" ",";",":",",",".","(",")"};   //限界符
		 
    char *operation[]={" ","+","-","*","/","<","<=",">",">=","<>","=",":="};//运算符
    FILE *fp;
    int i;
    char c;
    fp=fopen("keyword.txt","w");
    for(i=1;i<=9;i++)
       fprintf(fp,"%s\n",key[i]);
    fclose(fp);               /*初始化关键字表*/
    fp=fopen("limit.txt","w");
    for(i=1;i<=6;i++)            /*初始化限界符表*/
       fprintf(fp,"%s\n",limit[i]);
	 c='"';
   fprintf(fp,"%c\n",c);
   fclose(fp);       
	fp=fopen("operation.txt","w");  /*初始化运算符表*/
	for(i=1;i<=11;i++)
		fprintf(fp,"%s\n",operation[i]);
	fclose(fp);
         
    fp=fopen("id.txt","w");
    fclose(fp);               /*初始化标识符表*/
    fp=fopen("int.txt","w");
    fclose(fp);               /*初始化常数表*/
    fp=fopen("token.txt","w");
    fclose(fp);               /*初始化输出文件*/
}


/*******************************************
 根据不同命令查表或造表函数
********************************************/
int find(char *buf,int type,int command) //command=1 只要查表 command=2 找不到时 要加进去表中
{             
    int number=0;
    FILE *fp;
    char c;
    char temp[30];
    int i=0;
    switch(type)
    {
        
        case 1: fp=fopen("id.txt","r");break;
        case 2: fp=fopen("int.txt","r");break;
		case 3: fp=fopen("keyword.txt","r");break;
        case 4: fp=fopen("operation.txt","r"); break;
		case 5: fp=fopen("limit.txt","r");
    }
    c=fgetc(fp);
    while(c!=EOF)
    {
        while(c!='\n')
        {
            temp[i++]=c;
            c=fgetc(fp);
        }
        temp[i]='\0';
        i=0;
        number++;
        if(strcmp(temp,buf)==0)
        {  
		    fclose(fp);
			return(number);        /*若找到，返回在相应表中的序号*/
        }
        else
           c=fgetc(fp);
     }
     if(command==1)
     {   
	     fclose(fp); 
		 return(0);                /*找不到，当只需查表，返回0，否则还需造表*/
     }
     switch(type)
     {
         case 1: fp=fopen("id.txt","a");break;  //当command=2,向表中追加标识符  
         case 2: fp=fopen("int.txt","a");break;
         case 3: fp=fopen("keyword.txt","a");break;
         case 4: fp=fopen("operation.txt","a");break;
		 case 5: fp=fopen("limit.txt","a");
     }
     fprintf(fp,"%s\n",buf);
     fclose(fp);
     return(0);             /*造表时，将字符串添加到表尾并返回序号值*/
}

/*******************************************
 数字串处理函数
********************************************/
void cs_manage(char *buffer)
{             
    FILE *fp;
	if(strlen(buffer)>5) 
	{
	rong=1;
	return ;
	}
    if(strlen(buffer)==5)
	{
   if(strcmp(buffer,MAXNUM)>0) rong=1;
	   return ;
	}
    find(buffer,2,2);       /*先查整数表，若找不到则造入常数表并返回序号值*/
    fp=fopen("token.txt","a");
	fprintf(fp,"%s\t\t\t2\n",buffer); //类型是2
	data[num].idstr =buffer;
	data[num].style =2;
	num++;
	fclose(fp);               /*写入输出文件*/
}

/*******************************************
 字符串处理函数 
********************************************/
void ch_manage(char *buffer)
{                     
    FILE *fp;
    int result;
	if(strlen(buffer)>8)
	{
	rong=1;
	return ;
	}
    result=find(buffer,3,1);           /*先查关键字表*/
    fp=fopen("token.txt","a");
    if(result!=0)
	{
		result+=2;
		fprintf(fp,"%s\t\t\t%d\n",buffer,result);    /*若找到，写入输出文件 类型是1*/
		data[num].idstr =buffer;
    	data[num].style =result;
		num++;
	}
    else
    {
        result=find(buffer,1,2);       /*若找不到，则非关键字，查标识符表，还找不到则造入标识符表*/
        fprintf(fp,"%s\t\t\t1\n",buffer,1);  //类型是2
		data[num].idstr =buffer;
	    data[num].style =1;
    	num++;
    }                                 /*写入输出文件*/
    fclose(fp);
}

/*******************************************
 出错处理函数
********************************************/
void er_manage(char error,int lineno)
{                 
    printf("error: %c ,line %d",error,lineno);    /*报告出错符号和所在行数*/
}

/*******************************************
 扫描程序
********************************************/
void scanner()
{            
    FILE *fpin,*fpout;
    char filename[20];
    char ch;
	int k=0;
    int i=0;
    int count,result;
	char array[30];
    char *word;
	int style=0;
	int result2=0;
	printf("\n please input the source file name:");
    scanf("%s",filename);
    if((fpin=fopen(filename,"r"))==NULL)
    {
        printf("cannot open file");
        return;
    }
    ch=fgetc(fpin); //读取字符
    while(ch!=EOF) //一直扫描到文件末尾
    {                 /*按字符依次扫描源程序，直至结束*/
        i=0;
        if(((ch>='A')&&(ch<='Z')))/*以字母开头*/
        {           
            while(((ch>='A')&&(ch<='Z'))||((ch>='0')&&(ch<='9')))
            {
                array[i++]=ch;
                ch=fgetc(fpin);
            }
            word=(char *)malloc((i+1)*sizeof(char));
			memcpy(word,array,i);
			word[i]='\0';
            ch_manage(word);//处理字符串
			if(rong) 
			{   errorno++;
				printf("\nerror:out of range :");
				for(k=0;k<i;k++) 
				 printf("%c",word[k]);   
				 printf(" ,line: %d", line);
			}
			rong=0;
            if(ch!=EOF)
			   fseek(fpin,-1L,SEEK_CUR); //文件指针后退一个字节
        }
        else if(ch>='0'&&ch<='9')   /*以数字开头*/
        {         
            while(ch>='0'&&ch<='9')
            {
                array[i++]=ch;
                ch=fgetc(fpin);
            }
            word=(char *)malloc((i+1)*sizeof(char));
			memcpy(word,array,i);
			word[i]='\0';
            cs_manage(word);
			if(rong) 
			{   errorno++;
				printf("\n error:out of range :");
				for(k=0;k<i;k++) 
				 printf("%c",word[k]);   
				 printf(" ,line: %d", line);
			}
			rong=0;
			
            if(ch!=EOF)
			   fseek(fpin,-1L,SEEK_CUR);
        }
        else if((ch==' ')||(ch=='\t'))
			;           /*消除空格符和水平制表符*/
		else if(ch=='\n')
			line++;           /*消除回车并记录行数*/
		else if(ch=='/')
        {                 /*消除注释*/
			ch=fgetc(fpin);
		    if((ch!='*')&&(ch!='/'))
            {              /*若为除号，写入输出文件*/
                fpout=fopen("token.txt","a");
				fprintf(fpout,"/\t\t\t15\n");
					data[num].idstr ="/";
	                data[num].style =15;
                	num++;
                fclose(fpout);
				fseek(fpin,-1L,SEEK_CUR);
			}
			else if(ch=='/')
			{
				ch=fgetc(fpin);
				while(ch!='\n')
					ch=fgetc(fpin);
				line++;
			}
			else if(ch=='*')
			{              /*若为注释的开始，消除包含在里面的所有字符*/
				count=0;
				ch=fgetc(fpin);
				while(count!=2)
                {          /*当扫描到‘*’且紧接着下一个字符为‘/’才是注释的结束*/
					count=0;
					while(ch!='*')
					{
						if(ch=='\n') 
							line++;
						ch=fgetc(fpin);
					}
					count++;
					ch=fgetc(fpin);
					if(ch=='/')
						count++;
					else
						ch=fgetc(fpin);
				}
			}
		}
		else
        {         /*首字符为其它字符,即运算限界符或非法字符*/
            array[0]=ch;
            ch=fgetc(fpin);       /*再读入下一个字符，判断是否为双字符运算、限界符*/
            if(ch!=EOF)
            {           /*若该字符非文件结束符*/
                array[1]=ch;
				word=(char *)malloc(3*sizeof(char));
				memcpy(word,array,2);
				word[2]='\0';
                result=find(word,4,1);      /*先检索是否为双字符运算符*/
				if(result==0)  //找不到
				{                           /*若不是*/
                    word=(char *)malloc(2*sizeof(char));
					memcpy(word,array,1);
					word[1]='\0';
					result=find(word,4,1);      /*检索是否为单字符运算、限界符*/
					result2=find(word,5,1);
					if(result!=0) style=4;
					if(result2!=0) style=5;
					if(result==0 && result2==0)
                    {                           /*若还不是，则为非法字符*/
						printf("\n");
						er_manage(array[0],line);
						errorno++;
						fseek(fpin,-1L,SEEK_CUR);
                    }
                    else
					{     /*若为单字符运算、限界符，写入输出文件并将扫描文件指针回退一个字符*/
						fpout=fopen("token.txt","a");
						result+=11;
						result2+=22;
						result=(style==4)? result:result2;
						fprintf(fpout,"%s\t\t\t%d\n",word,result);
							data[num].idstr =word;
	                        data[num].style =result;
                        	num++;
						fclose(fpout);
						fseek(fpin,-1L,SEEK_CUR);//文件指针后退一个字节
					}
				}
                else
				{             /*若为双字符运算、限界符，写输出文件*/
					fpout=fopen("token.txt","a");
					result+=11;
					fprintf(fpout,"%s\t\t\t%d\n",word,result);
					data[num].idstr =word;
	                data[num].style =result;
                	num++;
					fclose(fpout);
				}
            }
            else
				fseek(fpin,-1L,SEEK_CUR);//文件指针后退一个字节
        }
        ch=fgetc(fpin); 
    }
    fclose(fpin);
	printf("\nThere are %d error(s).\n",errorno);         /*报告错误字符个数*/
}

/*******************************************
 主函数
********************************************/
main()
{   
	int j=0;
    init();            /*初始化*/
    scanner();         /*扫描源程序*/
	               /*打印二元式流*/	
	printf("\n 二元式流 :\n");
	 while(data[j].idstr !=NULL)
	 {
		 printf("%s\t\t%d\t\t\n",data[j].idstr ,data[j].style );
		 j++;
	 }
}  
