data segment
    string db 'Hello, World!$'
data ends

code segment
assume cs: code, ds: data

start:
    ; 初始化data段, code段自动初始化 
    mov ax, data
    mov ds, ax

    ; 09h dos 系统调用 system call
    lea dx, string
    mov ah, 09h
    int 21h

    ; 结束程序
    exit:          
                  mov    ah, 4Ch
                  int    21h
                  ret
code ends

end start
