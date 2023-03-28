; multi-segment executable file template.

data segment
    ; add your data here!  
    mess  db ' dada dawda dawd 123 da  ','$'  ; 
    med db 50 dup(0) ; 
    su db 0 
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
    lea bx,mess
    mov si,0 
l1: mov al,[bx]
    cmp al,'$'
    jz next 
    cmp al,' '
    jz  l2   
    mov mess+si,al
    add si,1 
l2: add bx,1 
    jmp l1
next: 
     mov mess+si,'$' 
    ; add your code here
            
    lea dx, mess
    mov ah, 9
    int 21h        ; output string at ds:dx
    
    ; wait for any key....    
    mov ah, 1
    int 21h
    
    mov ax, 4c00h ; exit to operating system.
    int 21h    
ends

end start ; set entry point and stop the assembler.
