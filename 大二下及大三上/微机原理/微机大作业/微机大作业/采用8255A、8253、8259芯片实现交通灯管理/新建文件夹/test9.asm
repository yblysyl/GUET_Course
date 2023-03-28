
CODE 		SEGMENT            
ASSUME 	CS:CODE
IOCONPT EQU 0FF2BH			;8255���ƿ�
IOAPT	 EQU 0FF28H			;PA��
IOBPT	 EQU 0FF29H			;PB��
IOCPT	 EQU 0FF2AH			;PC��

INTPORT1 EQU 0FF80H
INTPORT2 EQU 0FF81H
PA       EQU 0FF20H			;��λ��
PB       EQU 0FF21H 			;���ο�
PC       EQU 0FF22H			;�����

TCONTRO EQU 0043H
TCON0	 EQU 0040H
TCON1    EQU 0041H

START:	
        MOV AX,0H			;д�ж������ӳ���
	MOV ES,AX
	MOV DI,002CH			;IR3�ж�������ַ
	LEA AX,LIGHT			;IR3�жϷ����ַ
	STOSW				;д�жϷ����ַƫ����
	MOV AX,SEG LIGHT		;д�жϷ���ε�ַ
        STOSW
                                        ;8259��ʼ��
        MOV AL,13H			;дICW1,���ش���������ʹ�ã�����ICW4
	MOV DX,INTPORT1
	OUT DX,AL
	MOV AL,08H			;дICW2
	MOV DX,INTPORT2
	OUT DX,AL
	MOV AL,09H			;дICW4
	OUT DX,AL
	MOV AL,0F7H			;дOCW1
	OUT DX,AL
                                        ;8255��ʼ��
        MOV DX,IOCONPT			;8255���ƿ�
	MOV AL,10000000B
	OUT DX,AL			;д������, PA,PB���
	
	MOV DX,IOBPT					;
	MOV AL, 0F0H
	OR AL,0F0H
	OUT DX,AL
	MOV DX,IOCPT
	MOV AL,0F0H					
	OUT DX,AL			;��·�ں��ȫ��
        MOV BX,2                        ;BX���ڼ�ʱ����
        MOV DI,0                        ;DI��ʾҪ��������״̬
	STI				;���ж�

                                         ;8253��ʼ��
        MOV DX,TCONTRO	                 ;8253���ƿ�
	MOV AL,00110101B		;������,������0,�ȵͺ��,��ʽ2,HEX
	OUT DX,AL			;д������
	MOV DX,TCON0		;T0��
	MOV AL,00H			;��������λֵ
	OUT DX,AL
	MOV AL,80H			;��������λֵ
	OUT DX,AL
 
        MOV DX,TCONTRO	                 ;8253���ƿ�
	MOV AL,01110111B		;������,������1,�ȵͺ��,��ʽ3,HEX
	OUT DX,AL			;д������
	MOV DX,TCON1		;T1��
	MOV AL,00H			;��������λֵ
	OUT DX,AL
	MOV AL,10H			;��������λֵ
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

CA0:MOV AL,10100101B                    ;�ϱ��̵���,���������
    MOV DX,IOCPT
    OUT DX,AL
    MOV BX,8
    MOV DI,1
    JMP  EXIT1

CA1:MOV DX,IOCPT
    OR AL,0F0H
    OUT DX,AL				;�ϱ��̵���
   
        MOV CX,3
IOLED1: MOV DX,IOBPT
	MOV AL, 0F0H
	AND AL,10101111B				
	OUT DX,AL						;�ϱ��Ƶ���
	
        PUSH CX
	MOV CX,8000H
        DELA1: 	LOOP DELA1					;��ʱ

	OR AL,01010000B				
	OUT DX,AL						;�ϱ��Ƶ���

	MOV CX,8000H
        DELA2:  LOOP DELA2					;��ʱ
        POP CX

	LOOP IOLED1					;�ϱ��Ƶ���˸3��

    MOV DX,IOCPT
    MOV AL,0F0H
    OUT DX,AL				;��·�ں��ȫ��	
    MOV BX,2
    MOV DI,2
    JMP EXIT	

EXIT1: JMP EXIT

CA2:MOV DX,IOCPT
    MOV AL,01011010B                    ;�����̵���
    OUT DX,AL						
    MOV BX,4
    MOV DI,3
    JMP EXIT

CA3:MOV DX,IOCPT
    OR AL,0F0H
    OUT DX,AL				;�����̵���

    MOV CX,3
IOLED2: MOV DX,IOBPT
	MOV AL, 0F0H
	AND AL,01011111B
	OUT DX,AL						;�����Ƶ���

	PUSH CX
	MOV CX,8000H
        DELA3:  LOOP DELA3					;��ʱ				

	OR AL,10100000B
	OUT DX,AL						;�����Ƶ���

	MOV CX,8000H
        DELA4:   LOOP DELA4					;��ʱ
        POP CX

	LOOP IOLED2					;�����Ƶ���˸3��
  
    MOV DX,IOCPT
    MOV AL,0F0H
    OUT DX,AL				;��·�ں��ȫ��
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
