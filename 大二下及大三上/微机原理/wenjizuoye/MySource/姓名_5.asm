;         5. ��д����ͳ���ַ���STRING��ĳ�����ʵĸ������ַ�����'$'��Ϊ��������Ҫͳ�Ƶĵ��ʷ���C_WORD�У�ͳ�ƽ�������COUNT�С�
;                   ���磺�ַ���Ϊ'adding that this is because of the large infrastructure investment,
;                   high operational and maintenance costs, and the old regulations governing prices.'   
;             ͳ�Ƶ���'the'�ĸ�����
;         ����ߣ�1800301338 �ڱ���
DATA    SEGMENT
    STRING  DB 'adding that this is because of the large infrastructure investment, high operational and maintenance costs, and the old regulations governing prices.$'
    LEN     DW  $-STRING
    C_WORD  DB  'the$'
    COUNT   DW  0
    
DATA    ENDS

CODE    SEGMENT
    ASSUME  CS:CODE, DS:DATA
    
    START:
        MOV AX,DATA
        MOV DS,AX
        LEA SI,STRING        ;SI�洢STRING�ĵ�ַ��DI�洢C_WORD�ĵ�ַ
        LEA DI,C_WORD
        MOV CX,LEN
        
     MAIN:
        CALL    SELECT       ;����SELECT�ӳ��������ĿҪ��Ĺ���
        MOV     AH,4CH       ;ֹͣ����ִ��
        INT     21H
     
     
 SELECT PROC
    PUSH  AX
    PUSH  SI
    PUSH  DI
    PUSH  CX 
    PUSH  BX                 ;����ԭ������
    MOV   BX,DI              ;��BX��סԭ�е�C_WORD�ĵ�ַ���������֮��ѵ�ַ��ԭ
    MOV   AH,[DI]            ;AH�洢��Ҫ���ҵ��ַ������ַ��������ʼ��Ϊ��һ���ַ�
    COMPARE:
            MOV      AL,[SI]     ;STRING�е��ַ�
            INC      SI          ;��һ���ַ��ĵ�ַ
            CMP      AL,'$'      ;�Ƿ�����$���Ǿͽ�������
            JZ       OVER
            CMP      AL,AH       ;�Ƚ��Ƿ�����Ҫ���ҵĵ����ַ���ͬ
            JZ       CONTINUE    ;����ͬ������CONTINUE������Ҫ���ҵĵ����е��ַ�������һ��
            LOOP     COMPARE
            
    CONTINUE:
            INC      DI          ;��Ҫ���ҵĵ�������һ���ַ��ĵ�ַ
            MOV      DL,[DI]     ;���ַ�ȡ�������ж�
            CMP      DL,'$'      ;�����˵��ʵ�$,��ô��˵���ҵ���һ�������ĵ��ʣ�����COUNTER,���ʸ�����1
            JZ       COUNTER
            MOV      DH,[SI]     ;��STRING����һ���ַ�ȡ���������Ƿ��뵥���е���һ���ַ��Ƿ���ͬ������ͬ˵��ֻ��ǰ����ַ���ͬ���ѣ�
                                 ;����INIT��ʼDI�ĵ�ַ,����ͬ����ѵ����е��ַ�ȡ�������������бȽ�
            CMP      DH,DL       
            JNZ      INIT
            MOV      AH,[DI]     
            LOOP     COMPARE 
            
    INIT: 
            MOV     DI,BX
            MOV     AH,[DI]
            LOOP    COMPARE
         
    COUNTER: 
            INC      COUNT       ;�ҵ�һ�������ĵ��ʺ󣬸�����1���ѵ��ʵĵ�ַ��ԭ������������һ����ͬ�ĵ���     
        
            SUB      DI,3
            MOV      AH,[DI]
            LOOP     COMPARE
            
    
    
    OVER:
    POP   BX
    POP   CX
    POP   DI
    POP   SI
    POP   AX
    RET 
SELECT  ENDP
     
     
     
CODE    ENDS
        END     START

 


  

