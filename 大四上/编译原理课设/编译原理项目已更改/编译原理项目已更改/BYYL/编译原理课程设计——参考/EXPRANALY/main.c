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
#include<string.h>
#define MAX 10000 //��Ԫʽ����
#define MAXID 8
#define MAXNUM "65535"
//�����Ԫʽ�Ľṹ��
struct ds
{
	char *idstr; //�ַ��� 
	int style; //����
};
struct ds data[MAX];
long num=0;
int rong=0;
int rongid=0;
int line=1;
int errorno=0;
/*******************************************
 ��ʼ������
********************************************/
void init()
{             
    char *key[]={" ","BEGIN","END","IF","THEN","ELSE","WHILE","DO","INTEGER","VAR"};     /*�������йؼ���*/

    char *limit[]={" ",";",":",",",".","(",")"};   //�޽��
		 
    char *operation[]={" ","+","-","*","/","<","<=",">",">=","<>","=",":="};//�����
    FILE *fp;
    int i;
    char c;
    fp=fopen("keyword.txt","w");
    for(i=1;i<=9;i++)
       fprintf(fp,"%s\n",key[i]);
    fclose(fp);               /*��ʼ���ؼ��ֱ�*/
    fp=fopen("limit.txt","w");
    for(i=1;i<=6;i++)            /*��ʼ���޽����*/
       fprintf(fp,"%s\n",limit[i]);
	 c='"';
   fprintf(fp,"%c\n",c);
   fclose(fp);       
	fp=fopen("operation.txt","w");  /*��ʼ���������*/
	for(i=1;i<=11;i++)
		fprintf(fp,"%s\n",operation[i]);
	fclose(fp);
         
    fp=fopen("id.txt","w");
    fclose(fp);               /*��ʼ����ʶ����*/
    fp=fopen("int.txt","w");
    fclose(fp);               /*��ʼ��������*/
    fp=fopen("token.txt","w");
    fclose(fp);               /*��ʼ������ļ�*/
}


/*******************************************
 ���ݲ�ͬ������������
********************************************/
int find(char *buf,int type,int command) //command=1 ֻҪ��� command=2 �Ҳ���ʱ Ҫ�ӽ�ȥ����
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
			return(number);        /*���ҵ�����������Ӧ���е����*/
        }
        else
           c=fgetc(fp);
     }
     if(command==1)
     {   
	     fclose(fp); 
		 return(0);                /*�Ҳ�������ֻ��������0�����������*/
     }
     switch(type)
     {
         case 1: fp=fopen("id.txt","a");break;  //��command=2,�����׷�ӱ�ʶ��  
         case 2: fp=fopen("int.txt","a");break;
         case 3: fp=fopen("keyword.txt","a");break;
         case 4: fp=fopen("operation.txt","a");break;
		 case 5: fp=fopen("limit.txt","a");
     }
     fprintf(fp,"%s\n",buf);
     fclose(fp);
     return(0);             /*���ʱ�����ַ�����ӵ���β���������ֵ*/
}

/*******************************************
 ���ִ�������
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
    find(buffer,2,2);       /*�Ȳ����������Ҳ��������볣�����������ֵ*/
    fp=fopen("token.txt","a");
	fprintf(fp,"%s\t\t\t2\n",buffer); //������2
	data[num].idstr =buffer;
	data[num].style =2;
	num++;
	fclose(fp);               /*д������ļ�*/
}

/*******************************************
 �ַ��������� 
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
    result=find(buffer,3,1);           /*�Ȳ�ؼ��ֱ�*/
    fp=fopen("token.txt","a");
    if(result!=0)
	{
		result+=2;
		fprintf(fp,"%s\t\t\t%d\n",buffer,result);    /*���ҵ���д������ļ� ������1*/
		data[num].idstr =buffer;
    	data[num].style =result;
		num++;
	}
    else
    {
        result=find(buffer,1,2);       /*���Ҳ�������ǹؼ��֣����ʶ�������Ҳ����������ʶ����*/
        fprintf(fp,"%s\t\t\t1\n",buffer,1);  //������2
		data[num].idstr =buffer;
	    data[num].style =1;
    	num++;
    }                                 /*д������ļ�*/
    fclose(fp);
}

/*******************************************
 ��������
********************************************/
void er_manage(char error,int lineno)
{                 
    printf("error: %c ,line %d",error,lineno);    /*���������ź���������*/
}

/*******************************************
 ɨ�����
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
    ch=fgetc(fpin); //��ȡ�ַ�
    while(ch!=EOF) //һֱɨ�赽�ļ�ĩβ
    {                 /*���ַ�����ɨ��Դ����ֱ������*/
        i=0;
        if(((ch>='A')&&(ch<='Z')))/*����ĸ��ͷ*/
        {           
            while(((ch>='A')&&(ch<='Z'))||((ch>='0')&&(ch<='9')))
            {
                array[i++]=ch;
                ch=fgetc(fpin);
            }
            word=(char *)malloc((i+1)*sizeof(char));
			memcpy(word,array,i);
			word[i]='\0';
            ch_manage(word);//�����ַ���
			if(rong) 
			{   errorno++;
				printf("\nerror:out of range :");
				for(k=0;k<i;k++) 
				 printf("%c",word[k]);   
				 printf(" ,line: %d", line);
			}
			rong=0;
            if(ch!=EOF)
			   fseek(fpin,-1L,SEEK_CUR); //�ļ�ָ�����һ���ֽ�
        }
        else if(ch>='0'&&ch<='9')   /*�����ֿ�ͷ*/
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
			;           /*�����ո����ˮƽ�Ʊ��*/
		else if(ch=='\n')
			line++;           /*�����س�����¼����*/
		else if(ch=='/')
        {                 /*����ע��*/
			ch=fgetc(fpin);
		    if((ch!='*')&&(ch!='/'))
            {              /*��Ϊ���ţ�д������ļ�*/
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
			{              /*��Ϊע�͵Ŀ�ʼ����������������������ַ�*/
				count=0;
				ch=fgetc(fpin);
				while(count!=2)
                {          /*��ɨ�赽��*���ҽ�������һ���ַ�Ϊ��/������ע�͵Ľ���*/
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
        {         /*���ַ�Ϊ�����ַ�,�������޽����Ƿ��ַ�*/
            array[0]=ch;
            ch=fgetc(fpin);       /*�ٶ�����һ���ַ����ж��Ƿ�Ϊ˫�ַ����㡢�޽��*/
            if(ch!=EOF)
            {           /*�����ַ����ļ�������*/
                array[1]=ch;
				word=(char *)malloc(3*sizeof(char));
				memcpy(word,array,2);
				word[2]='\0';
                result=find(word,4,1);      /*�ȼ����Ƿ�Ϊ˫�ַ������*/
				if(result==0)  //�Ҳ���
				{                           /*������*/
                    word=(char *)malloc(2*sizeof(char));
					memcpy(word,array,1);
					word[1]='\0';
					result=find(word,4,1);      /*�����Ƿ�Ϊ���ַ����㡢�޽��*/
					result2=find(word,5,1);
					if(result!=0) style=4;
					if(result2!=0) style=5;
					if(result==0 && result2==0)
                    {                           /*�������ǣ���Ϊ�Ƿ��ַ�*/
						printf("\n");
						er_manage(array[0],line);
						errorno++;
						fseek(fpin,-1L,SEEK_CUR);
                    }
                    else
					{     /*��Ϊ���ַ����㡢�޽����д������ļ�����ɨ���ļ�ָ�����һ���ַ�*/
						fpout=fopen("token.txt","a");
						result+=11;
						result2+=22;
						result=(style==4)? result:result2;
						fprintf(fpout,"%s\t\t\t%d\n",word,result);
							data[num].idstr =word;
	                        data[num].style =result;
                        	num++;
						fclose(fpout);
						fseek(fpin,-1L,SEEK_CUR);//�ļ�ָ�����һ���ֽ�
					}
				}
                else
				{             /*��Ϊ˫�ַ����㡢�޽����д����ļ�*/
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
				fseek(fpin,-1L,SEEK_CUR);//�ļ�ָ�����һ���ֽ�
        }
        ch=fgetc(fpin); 
    }
    fclose(fpin);
	printf("\nThere are %d error(s).\n",errorno);         /*��������ַ�����*/
}

/*******************************************
 ������
********************************************/
main()
{   
	int j=0;
    init();            /*��ʼ��*/
    scanner();         /*ɨ��Դ����*/
	               /*��ӡ��Ԫʽ��*/	
	printf("\n ��Ԫʽ�� :\n");
	 while(data[j].idstr !=NULL)
	 {
		 printf("%s\t\t%d\t\t\n",data[j].idstr ,data[j].style );
		 j++;
	 }
}  
