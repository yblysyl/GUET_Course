 DATA SEGMENT
BUF	DB 9,8,7,4,5,6,3,2,12,15              ;存入数据
count equ $-BUF
BU1 DB "THE MIN IS:",'$'
BU2 DB 0AH,0DH,"THE MAX IS:",'$'
;程序段
DATA ENDS
CODE SEGMENT
ASSUME CS:CODE, DS:DATA, ES: DATA
START:MOV	AX,	DATA
	MOV	DS,	AX
	MOV CX,COUNT
	LEA SI,BUF			;数据引用
		MOV BH,[SI]
	MOV BL,[SI]
X1:   MOV AL,[SI]
	CALL DAXIAO   		;调用程序
	INC SI
	LOOP X1 
	 LEA	DX,BU1			;以下为输出
   MOV AH,09H
	INT	21H
	MOV AL, BL
	CALL SHUCHU
	LEA	DX,BU2
   MOV AH,09H
	INT	21H
	MOV AL,BH
	CALL SHUCHU
	   
	   
	
      MOV AH,4CH
	INT	21H
DAXIAO PROC NEAR
	CMP AL,BL
	JB	X2
	CMP AL,BH			
	JB X3
	MOV BH,AL 		;保存大值
	JMP X3
X2:   MOV BL,AL		;保存小值
X3:
	RET

DAXIAO ENDP 

SHUCHU PROC NEAR			;转换输出
     MOV DL,AL
     CMP DL,09H
     JB X4
     ADD DL,07H
X4:  ADD DL,30H
     MOV AH,02H
     INT 21H
    
    RET
SHUCHU ENDP

CODE	ENDS
	END	START