;1. ��֪��NUM�����������BUFFERΪ�׵�ַ���ֽڴ洢���У���ͳ�����и�Ԫ�صĸ�����Ҫ��ŵ�COUNT��Ԫ����д��������
;����� 1800301338 �ڱ���
 DATA SEGMENT
BUFFER DB 9,-8,7,-4,5,6,-3,2,-12,15,-16,-20,-19,5,25,80,-100,-50,29,20,21,-22,27,32,36 
COUNT DB '?'
NUM DB 25

DATA ENDS 
CODE SEGMENT
ASSUME CS:CODE, DS:DATA, ES: DATA    
START:MOV	AX,	DATA
	  MOV	DS,	AX
	  MOV   CL,  NUM 
	  MOV   CH,00H          ;����ѭ������  
	  MOV   BL,0 
	  LEA   SI, BUFFER 
X2:	  MOV   AL,[SI]
      CMP   AL,0H          ;�Ƚ�
	  JGE    X1
	  INC   BL
X1:   INC   SI
      LOOP  X2  
      MOV COUNT,BL          ;�������� 
      MOV AH,4CH
	  INT	21H 	  
CODE	ENDS
	END	START                