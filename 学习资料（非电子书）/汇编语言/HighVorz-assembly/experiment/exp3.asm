data segment
    CRLF db 0ah, 0dh, '$'

data ends

code segment
main proc far
          assume cs:code, ds:data, es:data
    start:
          mov    ax, data
          mov    ds, ax

          mov    cx, 7
          mov    bx, 10h
    s0:   
          push   cx
          mov    cx, 16
    s1:   
          mov    dx, bx
          mov    ah, 02h
          int    21h
          mov    dx, 0h
          mov    ah, 02h
          int    21h
          inc    bx
          loop   s1
          pop    cx
          lea    dx, CRLF
          mov    ah, 09h
          int    21h
          loop   s0

          ret
main endp
code ends
end start
