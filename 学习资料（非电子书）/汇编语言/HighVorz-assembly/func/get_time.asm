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
