;1. 已知有NUM个数存放在以BUFFER为首地址的字节存储区中，试统计其中负元素的个数，要求放到COUNT单元，编写完整程序。
;设计者 1800301338 于彬磊
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
	  MOV   CH,00H          ;存入循环次数  
	  MOV   BL,0 
	  LEA   SI, BUFFER 
X2:	  MOV   AL,[SI]
      CMP   AL,0H          ;比较
	  JGE    X1
	  INC   BL
X1:   INC   SI
      LOOP  X2  
      MOV COUNT,BL          ;保存数据 
      MOV AH,4CH
	  INT	21H 	  
CODE	ENDS
	END	START                