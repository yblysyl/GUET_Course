;3. ��֪A����30��ѧ����������Կγ̳ɼ��԰ٷ��ƴ����TABLE�У���Ҫ���д���򣬰Ѱٷ��Ƴɼ�ת��Ϊ�ļ��ƣ�����A: 90��100�֣�B: 70��89�֣�C:60��69��,D:С��60�֡������Ż�ԭTABLE�С�
;����� 1800301338 �ڱ���  
;���ݶ�
DATA SEGMENT
TABLE DB 25,56,65,85,99,73,62,55,45,62,68,96,76,74,73,74,52,15,66,64,68,67,63,64,67,91,85,84,32,34 
NUM DB 30  
DATA ENDS 
;�����
CODE SEGMENT
ASSUME CS:CODE, DS:DATA, ES: DATA
START:  MOV	AX,	DATA
	    MOV	DS,	AX
	    LEA SI,TABLE  
	    MOV CL,NUM          ;��ʼ��������
	    MOV CH,00H
X1:     MOV AL,[SI]
        CMP AL,90          ;��֧�ṹ
        JAE X2
        CMP AL,70  
        JAE X3 
         CMP AL,60 
        JAE X4
        JMP X5
X2:	    MOV AL,'A' 
        JMP HUI 
X3:     MOV AL,'B' 
        JMP HUI 
X4:	    MOV AL,'C' 
        JMP HUI 
X5:     MOV AL,'D' 
        JMP HUI         
        	
HUI:    MOV [SI],AL         ;��������
        INC SI
        LOOP X1   

        MOV AH,4CH
	    INT	21H
CODE	ENDS
	END	START