; 设计程序，从键盘输入十进制数，结果存放在BUFFER中（无符号数，16位），再把结果以十六进制方式在屏幕输出
 ;设计者 1800301338 于彬磊 
 ;数据段
DATA SEGMENT
BUF	DB	30
	DB	'?'
	DB	30	DUP('?')    ;保存输入字符
BUFF DB 10,13, '$'      ;换行
DATA ENDS
CODE SEGMENT
ASSUME CS:CODE, DS:DATA, ES: DATA
START:MOV	AX,	DATA
	MOV	DS,	AX		
	LEA DX,BUF
	MOV AH,0AH          
	INT	21H
	LEA SI,BUF+2 
	MOV CL,BUF+1             ;初始化计数器
	MOV CH,00H 
	MOV AX,0H               ;初始化ax,ax存放16进制数字
L1:	MUL DX                  ;将输入数据转换
    MOV BL,[SI]
    SUB BL,30H
	ADD AL,BL  
	MOV DX,0AH 
	INC SI
	LOOP L1
	
	
	
	MOV BX,10H        
X1: MOV DX,0H
    DIV BX                      ;转换为16进制
    CMP DL,09H
    JBE X2
    ADD DL,7H 
X2: ADD DL,30H 
    PUSH DX
    INC CX
	CMP AX,0H 
    JNE  X1
     
     LEA DX,BUFF                ;输出
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