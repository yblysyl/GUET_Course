;3. 已知A班有30名学生，汇编语言课程成绩以百分制存放在TABLE中，现要求编写程序，把百分制成绩转换为四级制，即：A: 90～100分，B: 70～89分，C:60～69分,D:小于60分。结果存放回原TABLE中。
;设计者 1800301338 于彬磊  
;数据段
DATA SEGMENT
TABLE DB 25,56,65,85,99,73,62,55,45,62,68,96,76,74,73,74,52,15,66,64,68,67,63,64,67,91,85,84,32,34 
NUM DB 30  
DATA ENDS 
;代码段
CODE SEGMENT
ASSUME CS:CODE, DS:DATA, ES: DATA
START:  MOV	AX,	DATA
	    MOV	DS,	AX
	    LEA SI,TABLE  
	    MOV CL,NUM          ;初始化计数器
	    MOV CH,00H
X1:     MOV AL,[SI]
        CMP AL,90          ;分支结构
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
        	
HUI:    MOV [SI],AL         ;读回数据
        INC SI
        LOOP X1   

        MOV AH,4CH
	    INT	21H
CODE	ENDS
	END	START