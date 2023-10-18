data segment
    branch_table dw routine_0
                 dw routine_1
                 dw routine_2
                 dw routine_3
    string       db 'Hello, World!', 0ah, 0dh, '$'
    input_a      db 'a: ', '$'
    input_b      db 'b: ', '$'
    sum          db 'sum: ', '$'
    menu         db "1 print 'hello world'", 0ah, 0dh, "2 adder", 0ah, 0dh, "3 display current time", 0ah, 0dh, "4 quit", 0ah, 0dh, "Please input: ", '$'
data ends

stack segment
          db 1024 dup(0)
stack ends

code segment
                     assume cs:code, ds:data, es:data, ss:stack

main proc far
    start:           
    ; 初始化段寄存器 ds, es, ss
                     mov    ax, data
                     mov    ds, ax
                     mov    es, ax
                     mov    ax, stack
                     mov    ss, ax

    ; 建立函数栈
                     mov    ax, stack
                     mov    ss, ax

                     mov    bp, 1024
                     mov    sp, 1024

    display_menu:    
                     mov    ax, ds
                     mov    dx, offset menu
                     call   print_str

    input:           
                     call   get_num
                     call   print_ln

    choose_routine:  
    ; check legal parameter
                     cmp    ax, 1
                     jb     return_display
                     cmp    ax, 4
                     ja     return_display

                     dec    ax
                     mov    si, offset branch_table
                     mov    bl, type branch_table
                     mul    bl
                     add    si, ax
                     jmp    branch_table[si]
                     
    ;call ...
    return_display:  
                     call   print_ln
                     jmp    display_menu
    
    end_of_loop:     
                     jmp    quit
    
    quit:            
    ;  退出
                     mov    ah, 4Ch
                     int    21h

    routine_0:       
    ; print Hello, World
                     mov    ax, ds
                     mov    dx, offset string
                     call   print_str
                     jmp    return_display
                     
    routine_1:       
    ; add A+B

    ; get A
                     mov    ax, ds
                     mov    dx, offset input_a
                     call   print_str

                     call   get_num
                     call   print_ln
                     mov    bx, ax
    ; get B
                     mov    ax, ds
                     mov    dx, offset input_b
                     call   print_str

                     call   get_num
                     call   print_ln
                     add    bx, ax
    ; print A+B
                     mov    ax, ds
                     mov    dx, offset sum
                     call   print_str

                     mov    ax, bx
                     call   print_num
                     call   print_ln

                     jmp    return_display

    routine_2:       
                     call   get_time
                     
                     mov    al, ch
                     and    ax, 00ffh
                     call   print_num
                     
                     mov    al, ':'
                     call   print_char

                     mov    al, cl
                     and    ax, 00ffh
                     call   print_num
                     
                     mov    al, ':'
                     call   print_char

                     mov    al, dh
                     and    ax, 00ffh
                     call   print_num

                     call   print_ln

                     jmp    return_display
    routine_3:       
                     jmp    end_of_loop


    


main endp

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
                     mov    ax, 6                                  ; 字符最长 5 + '$'
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
                     ret
get_num endp

    ; 入参ax
    ; 输出16位无符号数
print_num proc near
                     push   ax                                     ; 被除数
                     push   bx                                     ; 除数=10
                     push   cx                                     ; 被除数位数
                     push   dx                                     ; 余数

                     mov    bx, 10
                     mov    cx, 0
                     mov    dx, 0


    print_num_while: 
                     div    bx                                     ; 占用阶段
                     add    dx, 30h
                     push   dx
                     mov    dx, 0

                     inc    cx
                     cmp    ax, 0
                     jne    print_num_while
                  
    print_num_output:
                     pop    ax                                     ; 解除占用
                     call   print_char
                     loop   print_num_output

                     pop    dx
                     pop    cx
                     pop    bx
                     pop    ax
                     ret
print_num endp

    ; 入参: ax (al) 存放字符
print_char proc near
                     mov    dl, al
                     mov    ah, 02h
                     int    21h
                     ret
print_char endp


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
                     mov    word ptr ds:[si], ax                   ; 将覆盖 "缓冲区长度" 字段
                     
                     add    si, ax
                     add    si, 2

                     mov    byte ptr ds:[si], '$'                  ; 添加终结符

                     pop    si
                     pop    ds
                     pop    bx
                     ret

get_str endp

    ; 换行
print_ln proc near
                     push   ax
                     push   dx
                     push   bp
                     
                     mov    bp, sp
                     sub    sp, 4

                     mov    word ptr [bp - 2], 0024h               ; '$'
                     mov    word ptr [bp - 4], 0d0ah               ; 0a, 0d
           
                     mov    ax, ss
                     lea    dx, [bp - 4]
                     call   print_str

                     mov    sp, bp
                     pop    bp
                     pop    dx
                     pop    ax
                     ret
print_ln endp

    ; 返回值
    ; ch: 时
    ; cl: 分
    ; dh: 秒
    ; dl: *0.01s
get_time proc near
                     push   ax

                     mov    ah, 2ch
                     int    21h

                     pop    ax
                     ret
get_time endp

code ends
end start
