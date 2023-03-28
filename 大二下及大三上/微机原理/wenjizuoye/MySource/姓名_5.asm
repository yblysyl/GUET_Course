;         5. 编写程序，统计字符串STRING中某个单词的个数，字符串以'$'作为结束符，要统计的单词放在C_WORD中，统计结果存放在COUNT中。
;                   例如：字符串为'adding that this is because of the large infrastructure investment,
;                   high operational and maintenance costs, and the old regulations governing prices.'   
;             统计单词'the'的个数。
;         设计者：1800301338 于彬磊
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
        LEA SI,STRING        ;SI存储STRING的地址，DI存储C_WORD的地址
        LEA DI,C_WORD
        MOV CX,LEN
        
     MAIN:
        CALL    SELECT       ;调用SELECT子程序完成题目要求的功能
        MOV     AH,4CH       ;停止程序执行
        INT     21H
     
     
 SELECT PROC
    PUSH  AX
    PUSH  SI
    PUSH  DI
    PUSH  CX 
    PUSH  BX                 ;保护原有数据
    MOV   BX,DI              ;用BX记住原有的C_WORD的地址，方便查找之后把地址还原
    MOV   AH,[DI]            ;AH存储你要查找的字符串的字符，这里初始化为第一个字符
    COMPARE:
            MOV      AL,[SI]     ;STRING中的字符
            INC      SI          ;下一个字符的地址
            CMP      AL,'$'      ;是否遇到$，是就结束查找
            JZ       OVER
            CMP      AL,AH       ;比较是否与想要查找的单词字符相同
            JZ       CONTINUE    ;若相同就跳到CONTINUE，将想要查找的单词中的字符换到下一个
            LOOP     COMPARE
            
    CONTINUE:
            INC      DI          ;想要查找的单词中下一个字符的地址
            MOV      DL,[DI]     ;将字符取出来做判断
            CMP      DL,'$'      ;若到了单词的$,那么就说明找到了一个完整的单词，跳到COUNTER,单词个数加1
            JZ       COUNTER
            MOV      DH,[SI]     ;将STRING的下一个字符取出来，看是否与单词中的下一个字符是否相同，不相同说明只是前面的字符相同而已，
                                 ;跳到INIT初始DI的地址,若相同，则把单词中的字符取出来，到句子中比较
            CMP      DH,DL       
            JNZ      INIT
            MOV      AH,[DI]     
            LOOP     COMPARE 
            
    INIT: 
            MOV     DI,BX
            MOV     AH,[DI]
            LOOP    COMPARE
         
    COUNTER: 
            INC      COUNT       ;找到一个完整的单词后，个数加1，把单词的地址还原，继续查找下一个相同的单词     
        
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

 


  

