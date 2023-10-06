; 设置存储字符串的缓冲区大小

data segment
    max        db 25
    str_buffer db 25 dup(0)
    len        db ?
    input_msg  db 'please enter string: $'
    error_msg  db 'overflow error$'
    echo_msg   db "string: $"
    
    str_count  db "the number of characters: $"
    debug      db "debug: $"
    number     db 0h, 0h
    CRLF       db 0ah, 0dh, '$'

    start_time db ?, ?, ?
    end_time   db ?, ?, ?
    start_s    dw ?, ?
    end_s      dw ?, ?
    result_s   dw ?, ?
    res_msg    db "seconds= $"
data ends


code segment

                  assume cs:code, ds:data, es:data
    start:        
                  mov    ax, data
                  mov    ds, ax
    ; 保存时间
                  mov    ax, data
                  mov    ds, ax


                  mov    ah, 2cH
                  int    21h
                  mov    start_time[0], ch
                  mov    start_time[1], cl
                  mov    start_time[2], dh

                  mov    bx, 00h
                  mov    ax, 0E10h
                  mov    bl, start_time[0]
                  mul    bx
                  mov    start_s[0], dx
                  mov    start_s[2], ax
        

                  mov    al, 3ch
                  mov    bl, start_time[1]
                  mul    bl
                  add    start_s[2], ax
                  adc    start_s[0], 00h

                  mov    ah, 00h
                  mov    al, start_time[2]
                  add    start_s[2], ax
                  adc    start_s[0], 00h


    
    ; 输出提示信息
                  mov    ax, data
                  mov    ds, ax
                  mov    ah, 9h
                  lea    dx, input_msg
                  int    21h

    ; 获取缓冲区大小
                  mov    bl, max
                  mov    bh, 00h
                  mov    cx, 0
                  lea    dx, str_buffer
                  mov    si, 0

    input:        
                  mov    ah, 01h
                  int    21h
                  inc    cx
    isEnter:      
                  cmp    al, 0dh
                  je     output
    isOverflow:   
                  cmp    cx, bx
                  jna    uppercase
                  lea    dx, CRLF
                  mov    ah, 09h
                  int    21h
                  lea    dx, error_msg
                  mov    ah, 09h
                  int    21h
                  lea    dx, CRLF
                  mov    ah, 09h
                  int    21h
                  jmp    end_input
    uppercase:    
                  cmp    al, 'a'
                  jb     store
                  cmp    al, 'z'
                  ja     store
                  sub    al, 20h
    store:        
                  mov    str_buffer[si], al
                  inc    si
                  jmp    input
    output:       
                  mov    str_buffer[si], '$'
                  mov    ah, 09h
                  int    21h
                  lea    dx, CRLF
                  mov    ah, 09h
                  int    21h
    count:        
                  lea    dx, str_count
                  mov    ah, 09h
                  int    21h
                  mov    ax, si
                  call   print_num
    end_input:    
                  mov    ah, 2cH
                  int    21h
                  mov    si, 00h
                  mov    end_time[si], ch
                  mov    end_time[si], cl
                  mov    end_time[si], dh
    output_time:  
                  
    
    ; 计算结束时间以及用时
                  mov    ah, 2cH
                  int    21h
                  mov    end_time[0], ch
                  mov    end_time[1], cl
                  mov    end_time[2], dh

                  mov    bx, 00h
                  mov    ax, 0E10h
                  mov    bl, end_time[0]
                  mul    bx
                  mov    end_s[0], dx
                  mov    end_s[2], ax
        

                  mov    al, 3ch
                  mov    bl, end_time[1]
                  mul    bl
                  add    end_s[2], ax
                  adc    end_s[0], 00h

                  mov    ah, 00h
                  mov    al, end_time[2]
                  add    end_s[2], ax
                  adc    end_s[0], 00h

                
    ; 计算结果
                  mov    ax, end_s[2]
                  mov    bx, start_s[2]
                  sub    ax, bx

                  
    
                  mov    result_s[2], ax
                  mov    ax, result_s[2]
              

                  mov    ax, end_s[0]
                  mov    bx, start_s[0]
                  sbb    ax, bx
                  mov    result_s[0], ax
                  
                  lea    dx, res_msg
                  mov    ah, 09h
                  int    21h

                  mov    ax, result_s[2]
                  call   print_num
    ; 结束程序
    end:          
                  mov    ah, 4Ch
                  int    21h
                  ret


     print_num:    
                  
                  mov    bx, 10
                  mov    cx, 00h
                  mov    dx, 00h
                  push   ax

    while:        
                  div    bx
                  add    dx, 30h
                  push   dx
                  mov    dx, 00h
                  
                  inc    cx
                  cmp    ax, 0h
                  jnz    while
                  
    output_number:
                  pop    dx
                  mov    ah, 02h
                  int    21h
                  loop   output_number
                  lea    dx, CRLF
                  mov    ah, 09h
                  int    21h
                  pop    ax
                  ret

    ; main endp
code ends
end start
