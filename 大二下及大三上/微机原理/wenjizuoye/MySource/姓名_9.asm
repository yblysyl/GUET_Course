 ;9. ��֪�����ݶ�DATA�У���BUFΪ��ַ���ִ洢���д����NUM��Ҫ������20���������������Ա�д���򣬽������͵�ARRAYΪ��ַ�Ĵ洢���У��������͵�TABLEΪ��ַ�Ĵ洢���У����ֱ�ͳ�������͸����ĸ����������COUNT��������NUMBER��������Ԫ�С�����������ͳ�ƽ������Ļ����ʮ���Ʒ�ʽ�����
 ;����� 1800301338 �ڱ��� 
 ;���ݶ�

DATA SEGMENT
BUF	DB	30,-15,50,-50,60,12,13,16,19,-55,-98,-89,-22,-21,-23,-25,-98,-64,-54,45,47,49,20
NUM	EQU $-BUF           ;����
ARRAY DB 50 DUP('?')  
ZHENGSHU DB 0
TABLE DB 50 DUP('?') 
FUSHU DB 0 
BUFF DB 10,13, '$'      ;���� 
BU1  DB 'ZHENGSHU','$'
BU2  DB 'FUSHU' ,'$'
DATA ENDS 
 ;�����
CODE SEGMENT   
ASSUME CS:CODE, DS:DATA, ES: DATA  
START:  MOV	AX,	DATA
	    MOV	DS,	AX  
	    LEA SI,BUF 
	    LEA DI,ARRAY
	    LEA BX,TABLE
	    MOV CX,NUM 
	  
	    
L1:	    MOV AX,[SI]
	    CMP AX,0         ;�жϴ�Сд
	    JG  L2   
	    JL  L3 
	    JMP L4
L2:     MOV [DI],AX          ;��������
        INC ZHENGSHU
        INC DI
         JMP L4
L3:	    MOV [BX],AX          ;��������
        INC FUSHU 
        INC BX
        JMP L4
L4:     INC SI 

        LOOP L1  
        
        LEA DX,BU1
        CALL SHUCHU
        
        MOV BX,0AH  
        MOV AX,0H 
        MOV AL,ZHENGSHU 
       CALL ZHUANHUAN  
      
          LEA DX,BUFF
        CALL SHUCHU
      
        LEA DX,BU2
        CALL SHUCHU  
       MOV AX,0H 
        MOV AL,FUSHU
       CALL ZHUANHUAN 
      
	      
        MOV AH,4CH
	    INT	21H 
	    
	     
SHUCHU PROC NEAR         ;�������
      MOV AH,09H
        INT 21H
    RET 	     
SHUCHU	ENDP     
	     
	    
ZHUANHUAN PROC NEAR      	    ; ����ת���������
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