;8. ��֪������ARRAY�У������NUM������������Ҫ���ҳ�ż������Сֵ���������MIN��Ԫ�С�
;1800301338 �ڱ��� 
;���ݶ�
DATA SEGMENT
ARRAY	DB -51,8,7,4,5,-6,3,2,12,15
NUM DB 10 
MIN DB  '?'
DATA ENDS  
 ;�����
CODE SEGMENT
ASSUME CS:CODE, DS:DATA, ES: DATA
START:  MOV	AX,	DATA
	    MOV	DS,	AX 
	    MOV CL,NUM          ;���������
	    MOV CH,00H  
	    LEA SI,ARRAY
	    MOV BL,'?'          
X1:	    MOV AL,[SI]
        TEST AL,01H
        JNZ    X3  
        CALL DAXIAO         ;�ж��Ƿ��С
X3:     INC SI
        LOOP X1 
        
        MOV MIN,BL           ;ȡ������
        MOV AH,4CH
       	INT	21H

DAXIAO PROC NEAR 
    CMP BL,'?'
    JNE X4 
    MOV BL,AL
    RET
X4:	CMP AL,BL
	JGE	 X2  
	MOV BL,AL                   ;������Сֵ
X2:
	RET

DAXIAO ENDP

CODE	ENDS
	END	START	    