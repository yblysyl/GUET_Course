 ;9. 已知在数据段DATA中，以BUF为首址的字存储区中存放着NUM（要求不少于20）个带符号数，试编写程序，将正数送到ARRAY为首址的存储区中，将负数送到TABLE为首址的存储区中，并分别统计正数和负数的个数，存放在COUNT（正）和NUMBER（负）单元中。并把正负数统计结果在屏幕上以十进制方式输出。
 ;设计者 1800301338 于彬磊 
 ;数据段

DATA SEGMENT
BUF	DB	30,-15,50,-50,60,12,13,16,19,-55,-98,-89,-22,-21,-23,-25,-98,-64,-54,45,47,49,20
NUM	EQU $-BUF           ;计数
ARRAY DB 50 DUP('?')  
ZHENGSHU DB 0
TABLE DB 50 DUP('?') 
FUSHU DB 0 
BUFF DB 10,13, '$'      ;换行 
BU1  DB 'ZHENGSHU','$'
BU2  DB 'FUSHU' ,'$'
DATA ENDS 
 ;代码段
CODE SEGMENT   
ASSUME CS:CODE, DS:DATA, ES: DATA  
START:  MOV	AX,	DATA
	    MOV	DS,	AX  
	    LEA SI,BUF 
	    LEA DI,ARRAY
	    LEA BX,TABLE
	    MOV CX,NUM 
	  
	    
L1:	    MOV AX,[SI]
	    CMP AX,0         ;判断大小写
	    JG  L2   
	    JL  L3 
	    JMP L4
L2:     MOV [DI],AX          ;正数处理
        INC ZHENGSHU
        INC DI
         JMP L4
L3:	    MOV [BX],AX          ;负数处理
        INC FUSHU 
        INC BX
        JMP L4
L4:     INC SI 

        LOOP L1  
        
        LEA DX,BU1
        CALL SHUCHU
        
        MOV BX,0AH  
        MOV AX,0H 
        MOV AL,ZHENGSHU 
       CALL ZHUANHUAN  
      
          LEA DX,BUFF
        CALL SHUCHU
      
        LEA DX,BU2
        CALL SHUCHU  
       MOV AX,0H 
        MOV AL,FUSHU
       CALL ZHUANHUAN 
      
	      
        MOV AH,4CH
	    INT	21H 
	    
	     
SHUCHU PROC NEAR         ;输出程序
      MOV AH,09H
        INT 21H
    RET 	     
SHUCHU	ENDP     
	     
	    
ZHUANHUAN PROC NEAR      	    ; 进制转换输出程序
	MOV CX,0       
X1: MOV DX,0H
    DIV BX                      ;转换进制
    CMP DL,09H
    JBE X2
    ADD DL,7H 
X2: ADD DL,30H 
    PUSH DX
    INC CX
	CMP AX,0H 
    JNE  X1
     
     LEA DX,BUFF                ;输出
     MOV AH,09H
     INT 21H
      MOV DX,0
X3: POP DX
    MOV AH,02H
    INT 21H
    LOOP X3  
	    
	    RET
ZHUANHUAN ENDP
	    
	    
CODE	ENDS
	END	START   