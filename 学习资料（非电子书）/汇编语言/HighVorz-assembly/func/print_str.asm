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

