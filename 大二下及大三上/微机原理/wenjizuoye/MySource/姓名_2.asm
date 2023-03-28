;2. 已知字符串STRING以'$'为结束标志；统计其中小写字母的个数，结果送到COUNT单元，并把该字符串中的小写字母变成大写字母，其它字符保持不变。要求分别在屏幕上输出原字符串以及修改后的字符串。
;设计者 1800301338 于彬磊 
;数据段
DATA SEGMENT
STRING	DB "dadadDADASDadadDADAdsaDADWadsDWADasdADWADA$"
BU1 DB "yuan:",'$'
BU2 DB 0AH,0DH, "jieguo:",'$'
COUNT DB '?'
DATA ENDS   
;代码段
CODE SEGMENT                            
ASSUME CS:CODE, DS:DATA, ES: DATA
START:  MOV	AX,	DATA
	    MOV	DS,	AX 
	    LEA DX,BU1
    	MOV AH,09H
	    INT	21H 
	    LEA DX,STRING       ;输出原字符串
    	MOV AH,09H
	    INT	21H 
	    LEA SI,STRING
X2:     MOV AL,[SI]
        CMP AL,'$'          ;循环结束判定
        JE  NEXT
        CMP AL,61H           ;判定是否小写字母
	    JB	X1
	    CMP AL,7AH
	    JA X1
	    SUB AL,20H 
	    INC BL
X1:	    MOV [SI],AL
        INC SI
	    JMP X2 
NEXT:   MOV COUNT,BL        ;保存小写字母个数
        LEA DX,BU2
    	MOV AH,09H
	    INT	21H 
	    LEA DX,STRING       ;输出结果字符串
    	MOV AH,09H
	    INT	21H	     
        MOV AH,4CH
	    INT	21H
CODE	ENDS
	END	START	    