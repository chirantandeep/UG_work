;hello2.asm
section .data
	msg	db	"Hello, World!",0
	NL	db	0xa ; ASCII code for new line
section .bss
section .text
	global main
main:
	mov	rax, 1		; instruct rax to write
	mov 	rdi, 1		; instruct rdi to output i.e. stdout
	mov 	rsi, msg	; String to display
	mov 	rdx, 13		; length of the msg
	syscall
	mov     rax, 1   	; instruct rax to write
        mov     rdi, 1   	; instruct rdi to output i.e. stdout
        mov     rsi, NL		; Display a new line
        mov     rdx, 1   	; length of the msg
	syscall
	mov 	rax, 60		; Quit instruction
	mov 	rdi, 0		; Success exit code
	syscall

