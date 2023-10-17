data segment
    count   dw 0
    prompt1 db 'Add or Search?: $'
    prompt2 db 'username: $'
    prompt3 db 'phone number: $'
    prompt4 db 'no result$'
    prompt5 db 'The phone number is: $'
    
    item    db 16 dup(?)

    string  db 1024 dup(?)
    ; 一条信息 32byte, 姓名16, 号码16

data ends

stack segment
          db 1024 dup(0)
stack ends

code segment
                   assume cs:code, ds:data, es:data

main proc far
    start:         
    ; 初始化段寄存器
                   mov    ax, data
                   mov    ds, ax
                   mov    es, ax
                   mov    ss, ax

    ; 建立函数栈
                   mov    ax, stack
                   mov    ss, ax

                   mov    bp, 1023
                   mov    sp, 1023

    ;
    choose_command:
                   mov    ax, ds
                   lea    dx, prompt1
                   call   print_str
                   
                   call   get_char
                   call   print_ln

                   cmp    al, 's'
                   je     _search
                   cmp    al, 'a'
                   je     _add
                   jmp    choose_command
    _search:       
                   mov    ax, ds
                   lea    dx, prompt2
                   call   print_str

                   mov    bx, ds
                   lea    dx, item
                   call   get_str

                   call   print_ln

    ; 遍历
                   mov    cx, count
                   mov    di, 0
    _loop:         
                   cmp    cx, 0
                   je     _noresult
                   
                   mov    ax, di                       ; 第n个数据数
                   lea    si, string                   ; string 起始地址
                   mov    bx, 32                       ; 计算信息头地址
                   mul    bx
                   add    si, ax                       ; si 为信息头
                   add    si, 2

                   push   di
                   lea    di, item[2]

                   push   cx

                   mov    ax, si                       ; 保存si
                   mov    cx, word ptr item            ; 比较两个字符串
                   cld
                   repe   cmpsb
                   jz     _matched

                   pop    cx
                   pop    di
                   inc    di
                   loop   _loop

             
                

    _noresult:     
                   mov    ax, ds
                   lea    dx, prompt4
                   call   print_str
                   call   print_ln
                   jmp    _end

    _matched:      
                   add    ax, 16
                   mov    si, ax

                   mov    ax, ds
                   lea    dx, prompt5   
                   call   print_str

                   mov    ax, ds
                   mov    dx, si
                   
                   
                   call   print_str
                   call   print_ln
                   jmp    _end

    _add:          
                   
                   mov    ax, count                    ; 数据数
                   lea    si, string                   ; string 起始地址
                   

                   mov    bx, 32                       ; 计算信息头地址
                   mul    bx

                   add    si, ax                       ; si 为信息头

                   mov    ax, ds
                   lea    dx, prompt2
                   call   print_str

                   mov    bx, ds
                   mov    dx, si
                   mov    ax, 12
                   call   get_str                      ; 读 username

                   call   print_ln
                   
                   add    si, 16
                   mov    ax, ds
                   lea    dx, prompt3
                   call   print_str

                   mov    bx, ds
                   mov    dx, si
                   mov    ax, 12
                   call   get_str                      ; 读 phone number

                   call   print_ln
                   add    word ptr count, 1
    _end:          
                   jmp    choose_command
         

    ;  退出
                   mov    ah, 4Ch
                   int    21h
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

    ; 换行
print_ln proc near
                   push   ax
                   push   dx
                   push   bp
                     
                   mov    bp, sp
                   sub    sp, 4

                   mov    word ptr [bp - 2], 0024h     ; '$'
                   mov    word ptr [bp - 4], 0d0ah     ; 0a, 0d
           
                   mov    ax, ss
                   lea    dx, [bp - 4]
                   call   print_str

                   mov    sp, bp
                   pop    bp
                   pop    dx
                   pop    ax
                   ret
print_ln endp

    ; 返回值 ax(al) 获取字符
get_char proc near
                   mov    ah, 01
                   int    21h
                   mov    ah, 0
                   ret
get_char endp

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
                   mov    word ptr ds:[si], ax         ; 将覆盖 "缓冲区长度" 字段
                     
                   add    si, ax
                   add    si, 2

                   mov    byte ptr ds:[si], '$'        ; 添加终结符

                   pop    si
                   pop    ds
                   pop    bx
                   ret

get_str endp


code ends

end start
