;2. ��֪�ַ���STRING��'$'Ϊ������־��ͳ������Сд��ĸ�ĸ���������͵�COUNT��Ԫ�����Ѹ��ַ����е�Сд��ĸ��ɴ�д��ĸ�������ַ����ֲ��䡣Ҫ��ֱ�����Ļ�����ԭ�ַ����Լ��޸ĺ���ַ�����
;����� 1800301338 �ڱ��� 
;���ݶ�
DATA SEGMENT
STRING	DB "dadadDADASDadadDADAdsaDADWadsDWADasdADWADA$"
BU1 DB "yuan:",'$'
BU2 DB 0AH,0DH, "jieguo:",'$'
COUNT DB '?'
DATA ENDS   
;�����
CODE SEGMENT                            
ASSUME CS:CODE, DS:DATA, ES: DATA
START:  MOV	AX,	DATA
	    MOV	DS,	AX 
	    LEA DX,BU1
    	MOV AH,09H
	    INT	21H 
	    LEA DX,STRING       ;���ԭ�ַ���
    	MOV AH,09H
	    INT	21H 
	    LEA SI,STRING
X2:     MOV AL,[SI]
        CMP AL,'$'          ;ѭ�������ж�
        JE  NEXT
        CMP AL,61H           ;�ж��Ƿ�Сд��ĸ
	    JB	X1
	    CMP AL,7AH
	    JA X1
	    SUB AL,20H 
	    INC BL
X1:	    MOV [SI],AL
        INC SI
	    JMP X2 
NEXT:   MOV COUNT,BL        ;����Сд��ĸ����
        LEA DX,BU2
    	MOV AH,09H
	    INT	21H 
	    LEA DX,STRING       ;�������ַ���
    	MOV AH,09H
	    INT	21H	     
        MOV AH,4CH
	    INT	21H
CODE	ENDS
	END	START	    