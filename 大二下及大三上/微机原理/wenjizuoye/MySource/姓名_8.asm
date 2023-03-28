;8. 已知字数组ARRAY中，存放着NUM个带符号数，要求找出偶数的最小值，结果放在MIN单元中。
;1800301338 于彬磊 
;数据段
DATA SEGMENT
ARRAY	DB -51,8,7,4,5,-6,3,2,12,15
NUM DB 10 
MIN DB  '?'
DATA ENDS  
 ;代码段
CODE SEGMENT
ASSUME CS:CODE, DS:DATA, ES: DATA
START:  MOV	AX,	DATA
	    MOV	DS,	AX 
	    MOV CL,NUM          ;存入计数器
	    MOV CH,00H  
	    LEA SI,ARRAY
	    MOV BL,'?'          
X1:	    MOV AL,[SI]
        TEST AL,01H
        JNZ    X3  
        CALL DAXIAO         ;判断是否更小
X3:     INC SI
        LOOP X1 
        
        MOV MIN,BL           ;取出数据
        MOV AH,4CH
       	INT	21H

DAXIAO PROC NEAR 
    CMP BL,'?'
    JNE X4 
    MOV BL,AL
    RET
X4:	CMP AL,BL
	JGE	 X2  
	MOV BL,AL                   ;保留最小值
X2:
	RET

DAXIAO ENDP

CODE	ENDS
	END	START	    