      section .data
test_string:
      db      "Hello Whatup", 0
      section .text
      global  _start
      
print: 
      mov     rax, 1
      mov     rdi, 1
      mov     rsi, output
      mov     rdx, 4
      syscall
      ret

strlen:
      xor     rax, rax
.loop:
      cmp     byte[rdi+rax], 0
      je      .end

      inc     rax
      jmp     .loop
.end:
      ret

_start:
      mov     rdi, test_string
      call    strlen

      mov     dword[output], eax
      push    rax
      call    print

      pop     rax
      mov     rdi, rax
      mov     rax, 60
      syscall

      section .bss
output:
      resb    4