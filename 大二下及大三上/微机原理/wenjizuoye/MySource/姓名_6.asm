 ;6. ��֪���ֱ���NUMBER�У������һ����������д��������Ļ�Ϸֱ��ö����ƣ��˽��ƣ�ʮ���ƣ�ʮ���������
 ;����� 1800301338 �ڱ��� 
 ;���ݶ�
DATA SEGMENT
NUMBER	DW 500   ;��������
BUFF DB 10,13, '$'      ;����
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
    CALL ZHUANHUAN       ;�����ӳ���
	






      MOV AH,4CH
	INT	21H  
	
	
ZHUANHUAN PROC NEAR
	MOV AX,[SI]      	
	MOV CX,0       
X1: MOV DX,0H
    DIV BX                      ;ת������
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
	    
	    RET
ZHUANHUAN ENDP
	    
CODE	ENDS
	END	START