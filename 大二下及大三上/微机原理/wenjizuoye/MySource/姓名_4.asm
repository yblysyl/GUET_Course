;4. ����һ����GRADE�����100��ѧ��ĳ�Ź��εĿ��Գɼ���Ҫ���һ���������������
;����� 1800301338�ڱ���    
;���ݶ�
 DATA SEGMENT
GRADE	DB 25,56,65,85,99,73,62,55,45,62,68,96,76,74,73,74,52,15,66,64,68,67,63,64,67,91,85,84,32,34,25,56,65,85,99,73,62,55,45,62,68,96,76,74,73,74,52,15,66,64,68,67,63,64,67,91,85,84,32,34,25,56,65,85,99,73,62,55,45,62,68,96,76,74,73,74,52,15,66,64,68,67,63,64,67,91,85,84,32,34,25,56,65,85,99,73,62,55,45,99
COUNT DB	100
BUA	DB  0        ; 90��100��
BUB	DB  0          ;80��89��
BUC	DB  0           ;70��79
BUD	DB  0           ;60��69��
BUE	DB  0          ;60������
DATA ENDS
  stack segment
    dw   128  dup(0)
  ends  
  ;�����
 CODE SEGMENT 

ASSUME CS:CODE, DS:DATA, ES: stack
START:  MOV	AX,	DATA
	    MOV	DS,	AX 
	    MOV	AX,stack
	    MOV	ES,	AX 
	    LEA SI,GRADE  
	    MOV CL,COUNT          ;��ʼ��������
	    MOV CH,00H    
X1:     MOV BL,[SI]
        CMP BL,60          ;��֧�ṹ
        JB X2
         CMP BL,70
        JB X3  
        CMP BL,80  
        JB X4
         CMP BL,90
        JB X5 
         INC BUA
        JAE NEXT
X2:      INC BUE 
         JMP NEXT
X3:       INC BUD 
         JMP NEXT
X4:       INC BUC
         JMP NEXT
X5:       INC BUB
         JMP NEXT


NEXT:    INC SI 
         LOOP X1
        
 
 
 
     LEA SI,GRADE 
     MOV CL,COUNT          ;��ʼ��������
	 MOV CH,00H   
L1:  MOV AL,[SI]
     MOV BL,[SI]     
     PUSH CX                      ;���������
     CALL  DAXIAO               ;�ҳ���ǰλ��֮������ֵ
     POP CX
     MOV [SI],BL                  ;��������
     MOV [DI],AL 
     INC SI
     LOOP L1
     MOV AH,4CH
	 INT	21H    


DAXIAO PROC NEAR 
    MOV DI,SI
L4: MOV AH,[DI]
	CMP AH,BL
	JBE	L2 
	MOV BL,AH
	MOV BP,DI
L2: INC DI
    LOOP L4 
    MOV DI,BP
	RET

DAXIAO ENDP  
CODE	ENDS
	END	START