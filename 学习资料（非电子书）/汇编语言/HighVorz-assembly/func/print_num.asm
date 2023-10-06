    ; 入参ax
    ; 输出16位无符号数
print_num proc near
                     push   ax                            ; 被除数
                     push   bx                            ; 除数=10
                     push   cx                            ; 被除数位数
                     push   dx                            ; 余数

                     mov    bx, 10
                     mov    cx, 0
                     mov    dx, 0


    print_num_while: 
                     div    bx                            ; 占用阶段
                     add    dx, 30h
                     push   dx
                     mov    dx, 0

                     inc    cx
                     cmp    ax, 0
                     jne    print_num_while
                  
    print_num_output:
                     pop    ax                            ; 解除占用
                     call   print_char
                     loop   print_num_output

                     pop    dx
                     pop    cx
                     pop    bx
                     pop    ax
                     ret
print_num endp
