; multi-segment executable file template.

data segment
    ; add your data here! 
    pr db 50 dup(0)
    ppp db 50 dup(0) 
    pp db 'adadad$'
    pkey db "press any key...$"
ends

stack segment
    dw   128  dup(0)
ends

code segment
start:
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax  
    mov di,107
    mov si,50 
    lea  bx , pp
 l1:  mov al,[di]
 cmp [di],'$'  
    jz next
    mov [si], al
    add si,1; 
    add di,1
    jmp l1
    ; add your code here
    next:        
    lea dx, pkey
    mov ah, 9
    int 21h        ; output string at ds:dx
    
    ; wait for any key....    
    mov ah, 1
    int 21h
    
    mov ax, 4c00h ; exit to operating system.
    int 21h    
ends

end start ; set entry point and stop the assembler.
