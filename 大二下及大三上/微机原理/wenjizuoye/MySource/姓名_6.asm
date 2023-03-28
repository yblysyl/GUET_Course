 ;6. 已知在字变量NUMBER中，存放着一个整数，编写程序，在屏幕上分别用二进制，八进制，十进制，十六进制输出
 ;设计者 1800301338 于彬磊 
 ;数据段
DATA SEGMENT
NUMBER	DW 500   ;保存数字
BUFF DB 10,13, '$'      ;换行
DATA ENDS
CODE SEGMENT
ASSUME CS:CODE, DS:DATA, ES: DATA
START:MOV	AX,	DATA
	MOV	DS,	AX		
	LEA SI,NUMBER
    MOV BX,10H 
    CALL ZHUANHUAN
    MOV BX,08H
    CALL ZHUANHUAN 
    MOV BX,02H 
    CALL ZHUANHUAN       ;调用子程序
	






      MOV AH,4CH
	INT	21H  
	
	
ZHUANHUAN PROC NEAR
	MOV AX,[SI]      	
	MOV CX,0       
X1: MOV DX,0H
    DIV BX                      ;转换进制
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
	    
	    RET
ZHUANHUAN ENDP
	    
CODE	ENDS
	END	START