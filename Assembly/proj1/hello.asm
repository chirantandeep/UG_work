;;;;;;;;hello.asm;;;;;;;
; There are three main parts of an assembly program.

;//\\//PART ONE\\//\\
section .data

; Here data is initialised/defined.
;   <var name> <type>      <value>
	msg	db	"hello, world",0
; Variable names referes to the start address of the
;variable in memory. 'db' is 8 bits in length, a BYTE.
;Some DATATYPES are given as
;-----------------------------
;| type | bits | name        |
;| db   | 8    | Byte        |
;| dw   | 16   | Word        |
;| dd   | 32   | Double word |
;| dq   | 64   | Quadword    |
;-----------------------------
;The name 'msg' points to 'h' of the 'hello, world' in
;memory. msg+1 will point to 'e' and similarly. A string
;is an array of characters.It is convenient ot have a 
;zero'0' indicating the end of a human readable string.
;It represents 8 zeros in the memory place('db' is 8 bit).
; ASCII code for NULL is '0'. A line feed or a new line 
;has code '10'.
; Constants can be decleared using the format :
;         <constant name> equ <value> 

;//\\//PART TWO\\//\\
section .bss

; bss stands for Block Started Symbol. Memory space for
;uninitialised variables is decleared in this section.
; <var name> <type> <number>
; Some bss datatypes are 
;-------------------------------
;| type   | bits | name        |
;| resb   | 8    | Byte        |
;| resw   | 16   | Word        |
;| resd   | 32   | Double word |
;| resq   | 64   | Quadword    |
;-------------------------------
; for example: dArray resd 20
; It decleares space for an array of 20 double words.
; If there is not enough memory for the bss section
; the program will crash.

;//\\//PART THREE\\//\\
section .text
	global main
main:
;This 'main:' part is called a label. A colon always
;accompanies a label without any other instructions.
; Registers such as rdi, rsi and rax are prepared for
; outputting a msg on the screen.
; The system call code '1' is put into register rax.
; mov makes a copy from source to destination. syntax : 
; mov destination, source
; mov register, immediate value
; mov register, memory
; mov memory, register
; BUT 'mov memory, memory' is wrong.
; 
	mov rax, 1 	; 1 means write
	mov rdi, 1	; 1 = to stdout
	mov rsi, msg	; string to display in rsi
; Now place the msg length in rdx register. Do not count
; quotes or the last 0.
	mov rdx, 12
; Then syscall is used to call to functionallity provided
; by the operating system.
	syscall
; To cleanly exit the program, put 60 to rax and 0 to rdi.
	mov rax, 60	; 60 = exit
	mov rdi, 0 	; 0 = success exit code
	syscall		; quit
; The system exits without complaining.

; System calls are used to ask the operating system to do
; some specific actions. Every OS has a different list of
; system calls. The .lst file will show the relative 
; address of the code in the leftmost column and will show
; show the code translated into machine lang in the next.
; which is HEXADECIMAL. For example 'mov rax' is converted
; to B8 and 'mov rdi' to BF. Also msg string is converted
; to ASCII hexadecimal characters. 
