; ��Ƴ��򣬴Ӽ�������ʮ����������������BUFFER�У��޷�������16λ�����ٰѽ����ʮ�����Ʒ�ʽ����Ļ���
 ;����� 1800301338 �ڱ��� 
 ;���ݶ�
DATA SEGMENT
BUF	DB	30
	DB	'?'
	DB	30	DUP('?')    ;���������ַ�
BUFF DB 10,13, '$'      ;����
DATA ENDS
CODE SEGMENT
ASSUME CS:CODE, DS:DATA, ES: DATA
START:MOV	AX,	DATA
	MOV	DS,	AX		
	LEA DX,BUF
	MOV AH,0AH          
	INT	21H
	LEA SI,BUF+2 
	MOV CL,BUF+1             ;��ʼ��������
	MOV CH,00H 
	MOV AX,0H               ;��ʼ��ax,ax���16��������
L1:	MUL DX                  ;����������ת��
    MOV BL,[SI]
    SUB BL,30H
	ADD AL,BL  
	MOV DX,0AH 
	INC SI
	LOOP L1
	
	
	
	MOV BX,10H        
X1: MOV DX,0H
    DIV BX                      ;ת��Ϊ16����
    CMP DL,09H
    JBE X2
    ADD DL,7H 
X2: ADD DL,30H 
    PUSH DX
    INC CX
	CMP AX,0H 
    JNE  X1
     
     LEA DX,BUFF                ;���
     MOV AH,09H
     INT 21H
      MOV DX,0
X3: POP DX
    MOV AH,02H
    INT 21H
    LOOP X3  





      MOV AH,4CH
	INT	21H
CODE	ENDS
	END	START