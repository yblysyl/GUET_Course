; multi-segment executable file template.

data segment
    ; add your data here! 
    ARRAY dw  100 dup(-10000,500,-1001,-20000,1);
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
    mov dx,0
    LEA  bx,ARRAY
    mov cx ,500
   L1: cmp [bx],-1000
    jge L 
    add dx, 1;
   L:add bx,2
   loop L1;
        
    mov bx,dx    
        
            
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
