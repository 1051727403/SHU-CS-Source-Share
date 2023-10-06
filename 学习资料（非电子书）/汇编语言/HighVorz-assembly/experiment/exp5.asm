data segment

    keyword  db 12 dup(?)
    sentence db 52 dup(?)

    prompt1  db 'Enter keyword: $'
    prompt2  db 'Entry sentence: $'

    noMatch  db 'no match$'
    matched1 db 'Match at location: $'
    matched2 db ' of the sentence$'
     
data ends

code segment
                     assume cs:code, ds:data
main proc far

    start:           
                     mov    ax, data
                     mov    ds, ax
                     mov    es, ax

    input_keyword:   
                     lea    dx, prompt1
                     mov    ax, ds
                     call   print_str

                     
                     mov    keyword[0], 10
                     mov    bx, ds
                     lea    dx, keyword
                     mov    ax, 10
                     call   get_str
                     call   print_ln

    intput_sentence: 
                     lea    dx, prompt2
                     mov    ax, ds
                     call   print_str

                  
                     mov    sentence[0], 50
                     mov    bx, ds
                     lea    dx, sentence
                     mov    ax, 50
                     call   get_str
                     call   print_ln

    find:            
    start1:          
                     lea    si, sentence[2]
                     lea    di, keyword[2]

    ; bx 边界
                     mov    bx, si
                     add    bx, sentence[0]
                        
    loop1:           
                     push   si
                     push   di
                     mov    ax, si
                     add    ax, keyword[0]
                     cmp    ax, bx
                     ja     no_match

    isMatch:         
                     mov    cx, keyword[0]
                     cld
                     repe   cmpsb
                     jz     matched
    un_match:        
                     pop    di
                     pop    si
                     inc    si
                     jmp    loop1
                    

    no_match:        
                     mov    ax, ds
                     lea    dx, noMatch
                     call   print_str
                     call   print_ln
                     jmp    intput_sentence
    
    matched:         
                     mov    ax, ds
                     lea    dx, matched1
                     call   print_str

                     mov    ax, si
                     lea    bx, sentence[2]
                     sub    ax, bx
                     sub    ax, keyword[0]
                     inc    ax
                     call   print_hex

                     mov    ax, ds
                     lea    dx, matched2
                     call   print_str
                     call   print_ln
                     jmp    intput_sentence


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



    ; 入参: ax (al) 存放字符
print_char proc near
                     mov    dl, al
                     mov    ah, 02h
                     int    21h
                     ret
print_char endp



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


    

main endp
code ends

end start
