 DATA SEGMENT
BUFFER DB 9,-8,7,-4,5,6,-3,2,-12,15,-16,-126,-19,5,25,80,-123,-50,29,20,21,-22,27,32,36 
COUNT DB '?'
NUM DB 25

DATA ENDS 
CODE SEGMENT
ASSUME CS:CODE, DS:DATA, ES: DATA    
START:MOV	AX,	DATA
	  MOV	DS,	AX
	  MOV   CL,  NUM 
	  MOV   CH,00H          ;存入循环次数  
	  MOV   BL,0 
	  LEA   SI, BUFFER 
X2:	  MOV   AL,[SI]
      CMP   AL,-100          ;比较
	  JGE    X1
	  INC   BL
X1:   INC   SI
      LOOP  X2  
      MOV COUNT,BL          ;保存数据 
      MOV AH,4CH
	  INT	21H 	  
CODE	ENDS
	END	START         