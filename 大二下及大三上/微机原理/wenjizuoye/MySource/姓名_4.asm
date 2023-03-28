;4. 定义一数组GRADE存放有100个学生某门功课的考试成绩，要求编一程序，完成如下任务：
;设计者 1800301338于彬磊    
;数据段
 DATA SEGMENT
GRADE	DB 25,56,65,85,99,73,62,55,45,62,68,96,76,74,73,74,52,15,66,64,68,67,63,64,67,91,85,84,32,34,25,56,65,85,99,73,62,55,45,62,68,96,76,74,73,74,52,15,66,64,68,67,63,64,67,91,85,84,32,34,25,56,65,85,99,73,62,55,45,62,68,96,76,74,73,74,52,15,66,64,68,67,63,64,67,91,85,84,32,34,25,56,65,85,99,73,62,55,45,99
COUNT DB	100
BUA	DB  0        ; 90～100分
BUB	DB  0          ;80～89分
BUC	DB  0           ;70～79
BUD	DB  0           ;60～69分
BUE	DB  0          ;60分以下
DATA ENDS
  stack segment
    dw   128  dup(0)
  ends  
  ;代码段
 CODE SEGMENT 

ASSUME CS:CODE, DS:DATA, ES: stack
START:  MOV	AX,	DATA
	    MOV	DS,	AX 
	    MOV	AX,stack
	    MOV	ES,	AX 
	    LEA SI,GRADE  
	    MOV CL,COUNT          ;初始化计数器
	    MOV CH,00H    
X1:     MOV BL,[SI]
        CMP BL,60          ;分支结构
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
     MOV CL,COUNT          ;初始化计数器
	 MOV CH,00H   
L1:  MOV AL,[SI]
     MOV BL,[SI]     
     PUSH CX                      ;保存计数器
     CALL  DAXIAO               ;找出当前位置之后的最大值
     POP CX
     MOV [SI],BL                  ;交换数据
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