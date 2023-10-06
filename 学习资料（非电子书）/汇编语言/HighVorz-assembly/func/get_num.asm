    ; 返回值 ax
    ; 读入无符号十进制数 0~65535
    ; 非法格式: 65536, 0000, 01234, 空串
get_num proc near

                     push   bx
                     push   cx
                     push   dx
                     push   si

                     push   bp
                     mov    bp, sp
                     sub    sp, 8

                     mov    bx, ss
                     lea    dx, [bp - 8]
                     mov    ax, 6                         ; 字符最长 5 + '$'
                     call   get_str

                     lea    si, [bp - 6]
                     mov    bx, 10
                     mov    cx, ax
                     mov    ax, 0

    get_num_while:   
                     mov    dh, 0
                     mov    dl, ss:[si]
                     sub    dx, 30h
                     add    ax, dx
                     sub    cx, 1
                     jz     get_num_stop
                     mul    bx
                     inc    si
                     jmp    get_num_while
    get_num_stop:    

                     mov    sp, bp
                     pop    bp

                     pop    si
                     pop    dx
                     pop    cx
                     pop    bx
    
get_num endp
