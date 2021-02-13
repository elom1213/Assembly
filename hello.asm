section	.text
	global _start       ;must be declared for using gcc
_start:             ;tell linker entry point
    mov edi, msg    ; add edi, 0x01
    add dword[edi], 0x0a636261    ; add edi, 0x01
    ; add byte[edi], 0x01    ; add edi, 0x01
	mov	eax, 4	    ;system call number (sys_write)
	mov	ebx, 1	    ;file descriptor (stdout)
	lea	ecx, [1 + edi]   ;message to write
; 	mov	ecx, edi   ;message to write
	mov	edx, 8  ;message length
	int 0x80        ;call kernel
	mov	eax, 1	    ;system call number (sys_exit)
	int	0x80        ;call kernel

section	.data
msg     dd	0x00, 0x64	;our dear string
msg2	dw	0x63	;our dear string
; msg3	dw	100	;our dear string
; msg4	dw	102	;our dear string
; msg	dw	97, 98, 101, 102	;our dear string
len	equ	$ - msg			;length of our dear string
