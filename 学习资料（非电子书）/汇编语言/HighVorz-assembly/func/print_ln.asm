    ; 换行
print_ln proc near
                     push   ax
                     push   dx
                     push   bp
                     
                     mov    bp, sp
                     sub    sp, 4

                     mov    word ptr [bp - 2], 0024h      ; '$'
                     mov    word ptr [bp - 4], 0d0ah      ; 0a, 0d
           
                     mov    ax, ss
                     lea    dx, [bp - 4]
                     call   print_str

                     mov    sp, bp
                     pop    bp
                     pop    dx
                     pop    ax
                     ret
print_ln endp
