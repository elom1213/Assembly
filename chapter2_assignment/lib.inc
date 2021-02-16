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
      je      string_length.end
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
      ; test performs bitwise AND and it's result is discarded, while modify current status reg
      ; if rdi holds negative value, test sets sign flag into 1
      test    rdi, rdi
      jns     print_uint
      push    rdi
      mov     rdi, '-'
      call    print_char
      pop     rdi
      neg     rdi
      call    print_uint
      ret

read_char:
      push  0           ; allocate 1 byte on stack
      xor   rax, rax    ; system call number 0 : read
      xor   rdi, rdi    ; file descriptor 0 : stdin
      mov   rsi, rsp    ; beginning of buffer
      mov   rdx, 1      ; read 1 byte
      syscall
      pop   rax
      ret 

read_word:
      ; rdi points a buffer
      ; rsi holds buffer size
      ; read_word sotres word in buffer
      ; return address of buffer storing it to rax
      ; return word's length in rdx
      ; if word's length exceedes buffer size, return 0
      mov   rbx, rsi    ; save buffer size
      dec   rbx         ; ignore null terminator
      xor   rcx, rcx    ; counter
.skip_whitespace:
      push  rdi
      push  rbx
      push  rcx
      call  read_char   ; rax is holding 1 byte char
      pop   rcx
      pop   rbx
      pop   rdi

      cmp   al, 0x09    ; tab
      je    .skip_whitespace
      cmp   al, 0x0a    ; line feed
      je    .skip_whitespace
      cmp   al, 0x0d    ; carriage return
      je    .skip_whitespace
      cmp   al, 0x20    ; space
      je    .skip_whitespace
      test  al, al
      jz    read_word.end

.store_word:
      mov   byte[rdi + rcx], al
      inc   rcx

      push  rdi
      push  rbx
      push  rcx
      call  read_char
      pop  rcx
      pop  rbx
      pop  rdi

      cmp   al, 0x09    ; tab
      je    read_word.end
      cmp   al, 0x0a    ; line feed
      je    read_word.end
      cmp   al, 0x0d    ; carriage return
      je    read_word.end
      cmp   al, 0x20    ; space
      je    read_word.end

      cmp   rcx, rbx    ; if word length >= buffer size, then exit
      jae   .out_of_bound

      test  al, al
      jz    read_word.end

      jmp   .store_word

.end:
      mov   byte[rdi + rcx], 0      ; insert null terminator at the end
      mov   rax, rdi
      mov   rbx, rcx

      push  rax
      push  rbx
      call  print_string
      call  print_newline
      pop   rbx
      pop   rax

      ret

.out_of_bound:
      xor   rax, rax
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

string_equals:
    xor rax, rax
    ret

string_copy:
    ret