        section .data
newline_char:
        db      10
codes:  db      'Hello eveybody!!'
        section .text
        global  _start
print_newline:
        mov     rax, 1
        mov     rdi, 1
        mov     rsi, newline_char
        mov     rdx, 1
        syscall
        ret
print_hello:
        mov     rax, rdi
        mov     rdi, 1
        mov     rdx, 1
        mov     rcx, 28 ; 7*4 (length of 'Hello!!' * 4 bits)
iterate:
        push    rax
        sub     rcx, 4
        sar     rax, cl
        and     rax, 0xf
        lea     rsi, [codes + rax]
        push    rcx
        mov     rax, 1
        syscall
        pop     rcx
        pop     rax
        test    rcx, rcx
        jnz     iterate
        ret
_start:
        mov     rdi, 0x01234ef
        call    print_hello ; Hello!!
        call    print_newline

        mov     rax, 60
        xor     rdi, rdi
        syscall
