; original codes reference
; https://github.com/Apress/low-level-programming/blob/master/assignments/1_io_library/teacher/lib.inc
; https://github.com/jwasham/assembly-and-c

; references for system call number
; https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md
; https://web.archive.org/web/20120210203233/http://www.acsu.buffalo.edu/~charngda/linux_syscalls_64bit.html

      section .data
      section .text
exit:
      mov     rax, 60
      xor     rdi, rdi
      syscall

string_length:
      ; accepts a pointer to a string and returns its length
      xor     rax, rax
.loop:
      cmp     byte[rdi + rax], 0
      je      .end
      inc     rax
      jmp     .loop
.end:
      ret

print_string:
      ; accepts a pointer to a null-terminated string and print it to stdout
      push    rdi
      call    string_length
      pop     rsi

      mov     rdx, rax  ; rax contains length
      mov     rax, 1    ; system call number 1 : write
      mov     rdi, 1    ; file descriptor number 1 : stdout
      syscall
      ret

print_char:
      push    rdi
      mov     rdi, rsp  ;  rdi must contains memory address of beginning of the string
      call    print_string
      pop     rdi
      ret

print_newline:
      mov     rdi, 0xa
      call    print_char
      ret

print_uint:
      ; outputs an unsigned 8-bytes integer in decimal format
      mov     rax, rdi  ; rdi holds 8-bytes unsigned integer
      mov     rcx, 10   ; divisor
      mov     rsi, rsp 
      push    0         ; push 8-bytes with 0
      dec     rsi       ; rsi points highest address of the string buffer [rsp - 24 : rsp]
      sub     rsp, 16   ; we need at most 21 bytes of buffer to store 
                        ; 8-bytes unsigned integer including null (2^64 = 1.8466... * 10^19)
.loop:
      xor     rdx, rdx
      div     rcx       ; divides rax with rcx. remainder will be stored in rdx and quotient will be sotred in rax
      add     rdx, 48
      dec     rsi
      mov     [rsi], dl
      test    rax, rax
      jnz     .loop

      mov     rdi, rsi
      call    print_string
      add     rsp, 24
      ret

print_int:
      mov     rdx,rdi
      sar     rdx, 63
      cmp     rdx, 0
      je      .print_uint
      push    rdi       ; caller save reg
      mov     rdi, '-'
      call    print_char
      pop     rdi       ; caller restore
      neg     rdi
      call    print_uint
      ret

string_equals:
    xor rax, rax
    ret


read_char:
    xor rax, rax
    ret 

read_word:
    ret

; rdi points to a string
; returns rax: number, rdx : length
parse_uint:
    xor rax, rax
    ret

; rdi points to a string
; returns rax: number, rdx : length
parse_int:
    xor rax, rax
    ret 


string_copy:
    ret