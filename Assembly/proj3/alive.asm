;alive.asm

section .data

msg1 	db 	"Hello, World",10,0 	;len(13)
msg1len equ 	$-msg1-1		; measure of length minus the 0 at last
msg2 	db 	"Alive and Kicking",10,0
msg2len equ 	$-msg2-1
radius 	dq 	357			; not a string 
pi 	dq 	3.14

section .bss
section .text
	global main
main:
	push 	rbp 			; Function prologue
	mov 	rbp,rsp			; function prologue

	mov 	rax, 1
	mov 	rdi, 1
	mov 	rsi, msg1
	mov 	rdx, msg1len
	syscall

	mov 	rax, 1
	mov 	rdi, 1
	mov 	rsi, msg2
	mov 	rdx, msg2len
	syscall
	mov 	rsp,rbp			;function epilogue
	pop 	rbp			;function epilogue
	mov 	rax, 60
	mov 	rdi, 0 
	syscall 
