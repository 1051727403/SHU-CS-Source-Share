data segment
    CRLF    db 0ah, 0dh, '$'
    string  db 90 dup(?)
    letter  db 0
    digit   db 0
    other   db 0
    prompt1 db 'the number of letter: $'
    prompt2 db 'the number of digit: $'
    prompt3 db 'the number of other: $'

data ends

stack segment
          db 100 dup(0)
stack ends

code segment
                    assume cs:code, ds:data, es:data

main proc far
    start:          
    ; 初始化段寄存器
                    mov    ax, data
                    mov    ds, ax

                    mov    ax, stack
                    mov    ss,ax

    

    input:          
                    mov    si, 0
                    mov    string[si], 80

                    lea    dx, string
                    call   get_str

    ; 遍历字符串
                    mov    ch, 0
                    mov    cl, string[si+1]
                    add    si, 2                 

    loop1:          
                    mov    al, string[si]
    
    isDigit:        
                    cmp    al, 30H
                    jb     isLittleLetter
                    cmp    al, 39H
                    ja     isLittleLetter
                    add    digit[0], 1
                    jmp    endOfwhile
          
    isLittleLetter: 
                    cmp    al, 61H
                    jb     isCapitalLetter
                    cmp    al, 7AH
                    ja     isCapitalLetter
                    add    letter[0], 1
                    jmp    endOfwhile
    isCapitalLetter:
                    cmp    al, 41H
                    jb     isOther
                    cmp    al, 5AH
                    ja     isOther
                    add    letter[0], 1
                    jmp    endOfwhile
    isOther:        
                    add    other[0], 1
    endOfwhile:     
                    inc    si
                    loop   loop1

    
    output:         
    ; 换行
                    call   println
    ; 输出 字母个数
                    lea    dx, prompt1
                    call   print_str

                    mov    al, letter[0]
                    mov    ah, 0

                    call   print_num
   
    ; 输出数字个数
                    lea    dx, prompt2
                    call   print_str

                    mov    al, digit[0]
                    mov    ah, 0

                    call   print_num
   

    ; 输出其他字符个数
                    lea    dx, prompt3
                    call   print_str

                    mov    al, other[0]
                    mov    ah, 0

                    call   print_num

    ; 结束程序
                    mov    ah, 4Ch
                    int    21h
   
main endp

    ; 入参ax
    ; 输出16位无符号数
print_num proc near
                    push   ax
                    push   bx
                    push   cx
                    push   dx
                    mov    bx, 10
                    mov    cx, 00h
                    mov    dx, 00h
                  

    while:          
                    div    bx
                    add    dx, 30h
                    push   dx
                    mov    dx, 00h

                    inc    cx
                    cmp    ax, 0h
                    jne    while
                  
    output_number:  
                    pop    dx
                    mov    ah, 02h
                    int    21h
                    loop   output_number

                    lea    dx, CRLF
                    mov    ah, 09h
                    int    21h

                    pop    dx
                    pop    cx
                    pop    bx
                    pop    ax
                    ret
print_num endp

    ; 输出DS:DX字符串
print_str proc near
                    mov    ah, 09h
                    int    21h
                    ret
print_str endp

    ; 输出换行
println proc near
                    lea    dx, CRLF
                    mov    ah, 09h
                    int    21h
                    ret
println endp

    ; 读入字符串DS:DX
get_str proc near
                    mov    ah, 0ah
                    int    21h
                    ret
get_str endp


code ends

end start
