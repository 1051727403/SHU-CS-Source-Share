    ; ! 必须预先分配空间 n + 3  字符串长度(2byte) + 字符串 (最长为n byte) + '$' (1 byte)

    ; 入参 bx:dx 指定存入字符串的段:偏移地址 ; ax 为 n + 1

    ; 功能: bx:[dx] 起始两个字节将存入实际字符串长度, 之后存入字符串
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
