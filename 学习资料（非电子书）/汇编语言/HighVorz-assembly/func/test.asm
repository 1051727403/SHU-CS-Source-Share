data segment
    string db 13 dup(?)
data ends

stack segment
          db 1024 dup(0)
stack ends

code segment
                     assume cs:code, ds: data
main proc far
    start:           
    ; 初始化段寄存器
                     mov    ax, data
                     mov    ds, ax
                     mov    ss, ax

    ; 建立函数栈
                     mov    ax, stack
                     mov    ss, ax

                     mov    bp, 1023
                     mov    sp, 1023


    ; 功能测试

                     call   get_num
                     call   print_ln

                     call   print_num
                     call   print_ln

                     mov    ax, 345
                     call   print_num
                     call   print_ln

                     mov    al, 'Y'
                     call   print_char
                     call   print_ln

                     mov    ax, 0h
                     call   print_hex
                     call   print_ln

                     mov    bx, ds
                     lea    dx, string
                     mov    ax, 10
                     call   get_str
                     call   print_ln

                     call   print_num                     ; 输出读取的字符串长度
                     call   print_ln

                     mov    ax, ds
                     lea    dx, string[2]
                     call   print_str
                     call   print_ln

    ;  退出
                     mov    ah, 4Ch
                     int    21h
                  
main endp

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


    ; 入参 ax字符串段地址 dx 字符串偏移地址
print_str proc near
                     push   ax
                     push   ds

                     mov    ds, ax
                     mov    ah, 09h
                     int    21h
    
                     pop    ds
                     pop    ax

                     ret
print_str endp

    ; 入参: al 存放字符
print_char proc near
                     mov    dl, al
                     mov    ah, 02h
                     int    21h
                     ret
print_char endp

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



    ; ! 必须预先分配空间 最大字符串长度 + 3  字符串长度(2) + 字符串 (n) + '$'
    ; 入参 bx:dx 指定存入字符串 段:偏移地址 al 为 n + 1
    ; bx:[dx] 起始两个字节 将存入 实际字符串长度
    ; 返回值 ax 实际字符串长度
get_str proc near
                     push   bx
                     push   ds
                     push   si

                     mov    ds, bx
                     mov    si, dx
                     mov    byte ptr ds:[si], al
                     mov    ah, 0ah
                     int    21h

                     mov    ah, 0
                     mov    al, ds:[si + 1]
                     mov    word ptr ds:[si], ax          ; 将覆盖 "缓冲区长度" 字段
                     
                     add    si, ax
                     add    si, 2

                     mov    byte ptr ds:[si], '$'         ; 添加终结符

                     pop    si
                     pop    ds
                     pop    bx
                     ret

get_str endp


                  
code ends
end start
