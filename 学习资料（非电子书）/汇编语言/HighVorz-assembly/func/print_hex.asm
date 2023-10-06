    ; 入参 ax
    ; 输出 16位 无符号十六进制数
print_hex proc near
                     push   ax
                     push   bx
                     push   cx
                     push   dx

                     push   bp
                     mov    bp, sp

                     sub    sp, 16                        ; 扩展函数栈空间

                     mov    byte ptr [bp-1], '0'          ; 存入栈中
                     mov    byte ptr [bp-2], '1'
                     mov    byte ptr [bp-3], '2'
                     mov    byte ptr [bp-4], '3'
                     mov    byte ptr [bp-5], '4'
                     mov    byte ptr [bp-6], '5'
                     mov    byte ptr [bp-7], '6'
                     mov    byte ptr [bp-8], '7'
                     mov    byte ptr [bp-9], '8'
                     mov    byte ptr [bp-10], '9'
                     mov    byte ptr [bp-11], 'A'
                     mov    byte ptr [bp-12], 'B'
                     mov    byte ptr [bp-13], 'C'
                     mov    byte ptr [bp-14], 'D'
                     mov    byte ptr [bp-15], 'E'
                     mov    byte ptr [bp-16], 'F'


                     mov    ch, 4
                     mov    cl, 4
                     mov    bx, ax
    print_hex_rotate:
                     rol    bx, cl                        ; 循环左移
                     mov    al, bl
                     and    al, 0fh                       ; 取低四位
                     mov    ah, 00h
                     mov    si, 0
                     sub    si, ax

                     mov    al, byte ptr [bp + si - 1]    ; 输出低四位
                     call   print_char
                    
                     dec    ch
                     jnz    print_hex_rotate

                     mov    al, 'H'
                     call   print_char

                     mov    sp, bp
                     pop    bp

                     pop    dx
                     pop    cx
                     pop    bx
                     pop    ax
                     ret
print_hex endp
