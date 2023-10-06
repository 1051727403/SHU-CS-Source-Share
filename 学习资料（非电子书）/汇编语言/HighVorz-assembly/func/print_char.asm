; 入参: ax (al) 存放字符
print_char proc near
                    mov    dl, al
                    mov    ah, 02h
                    int    21h
                    ret
print_char endp
