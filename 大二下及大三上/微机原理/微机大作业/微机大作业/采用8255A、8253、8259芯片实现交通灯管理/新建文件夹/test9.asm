
CODE 		SEGMENT            
ASSUME 	CS:CODE
IOCONPT EQU 0FF2BH			;8255控制口
IOAPT	 EQU 0FF28H			;PA口
IOBPT	 EQU 0FF29H			;PB口
IOCPT	 EQU 0FF2AH			;PC口

INTPORT1 EQU 0FF80H
INTPORT2 EQU 0FF81H
PA       EQU 0FF20H			;字位口
PB       EQU 0FF21H 			;字形口
PC       EQU 0FF22H			;键入口

TCONTRO EQU 0043H
TCON0	 EQU 0040H
TCON1    EQU 0041H

START:	
        MOV AX,0H			;写中断向量子程序
	MOV ES,AX
	MOV DI,002CH			;IR3中断向量地址
	LEA AX,LIGHT			;IR3中断服务地址
	STOSW				;写中断服务地址偏移量
	MOV AX,SEG LIGHT		;写中断服务段地址
        STOSW
                                        ;8259初始化
        MOV AL,13H			;写ICW1,边沿触发，单级使用，需设ICW4
	MOV DX,INTPORT1
	OUT DX,AL
	MOV AL,08H			;写ICW2
	MOV DX,INTPORT2
	OUT DX,AL
	MOV AL,09H			;写ICW4
	OUT DX,AL
	MOV AL,0F7H			;写OCW1
	OUT DX,AL
                                        ;8255初始化
        MOV DX,IOCONPT			;8255控制口
	MOV AL,10000000B
	OUT DX,AL			;写命令字, PA,PB输出
	
	MOV DX,IOBPT					;
	MOV AL, 0F0H
	OR AL,0F0H
	OUT DX,AL
	MOV DX,IOCPT
	MOV AL,0F0H					
	OUT DX,AL			;四路口红灯全亮
        MOV BX,2                        ;BX用于计时几秒
        MOV DI,0                        ;DI表示要进入那种状态
	STI				;开中断

                                         ;8253初始化
        MOV DX,TCONTRO	                 ;8253控制口
	MOV AL,00110101B		;命令字,计数器0,先低后高,方式2,HEX
	OUT DX,AL			;写命令字
	MOV DX,TCON0		;T0口
	MOV AL,00H			;计数器低位值
	OUT DX,AL
	MOV AL,80H			;计数器高位值
	OUT DX,AL
 
        MOV DX,TCONTRO	                 ;8253控制口
	MOV AL,01110111B		;命令字,计数器1,先低后高,方式3,HEX
	OUT DX,AL			;写命令字
	MOV DX,TCON1		;T1口
	MOV AL,00H			;计数器低位值
	OUT DX,AL
	MOV AL,10H			;计数器高位值
	OUT DX,AL				
	
         JMP $

LIGHT PROC FAR
      PUSH DX 
      PUSH CX
      DEC BX
      JNZ EXIT1
      CMP DI,0
      JZ CA0
      CMP DI,1
      JZ CA1
      CMP DI,2
      JZ CA2
      CMP DI,3
      JZ CA3
      JMP EXIT1

CA0:MOV AL,10100101B                    ;南北绿灯亮,东西红灯亮
    MOV DX,IOCPT
    OUT DX,AL
    MOV BX,8
    MOV DI,1
    JMP  EXIT1

CA1:MOV DX,IOCPT
    OR AL,0F0H
    OUT DX,AL				;南北绿灯灭
   
        MOV CX,3
IOLED1: MOV DX,IOBPT
	MOV AL, 0F0H
	AND AL,10101111B				
	OUT DX,AL						;南北黄灯亮
	
        PUSH CX
	MOV CX,8000H
        DELA1: 	LOOP DELA1					;延时

	OR AL,01010000B				
	OUT DX,AL						;南北黄灯灭

	MOV CX,8000H
        DELA2:  LOOP DELA2					;延时
        POP CX

	LOOP IOLED1					;南北黄灯闪烁3次

    MOV DX,IOCPT
    MOV AL,0F0H
    OUT DX,AL				;四路口红灯全亮	
    MOV BX,2
    MOV DI,2
    JMP EXIT	

EXIT1: JMP EXIT

CA2:MOV DX,IOCPT
    MOV AL,01011010B                    ;东西绿灯亮
    OUT DX,AL						
    MOV BX,4
    MOV DI,3
    JMP EXIT

CA3:MOV DX,IOCPT
    OR AL,0F0H
    OUT DX,AL				;东西绿灯灭

    MOV CX,3
IOLED2: MOV DX,IOBPT
	MOV AL, 0F0H
	AND AL,01011111B
	OUT DX,AL						;东西黄灯亮

	PUSH CX
	MOV CX,8000H
        DELA3:  LOOP DELA3					;延时				

	OR AL,10100000B
	OUT DX,AL						;东西黄灯灭

	MOV CX,8000H
        DELA4:   LOOP DELA4					;延时
        POP CX

	LOOP IOLED2					;东西黄灯闪烁3次
  
    MOV DX,IOCPT
    MOV AL,0F0H
    OUT DX,AL				;四路口红灯全亮
    MOV BX,1
    MOV DI,0
    JMP EXIT
      
EXIT: CLI
      PUSH AX
      MOV DX,0FF80H
      MOV AL,20H
      OUT DX,AL			;EOI      
      POP AX                             
      POP CX
      POP DX
      STI
      IRET
LIGHT ENDP
CODE ENDS
END START
