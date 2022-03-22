;program to count the number of positive and negative numbers in an array of 64-bit signed integers

section .data
block: dq 0x8234567812345678, 0xFA134C3612345678, 0x312312345678FAC4, 0x23454674B1FABCD3
cnt_neg: db 0	;for storing the count of negative numbers
cnt_pos: db 0	;for storing the count of positive numbers

pos_st: dq "Positive: "	;statement for postiive numbers
len1: equ $-pos_st
neg_st: dq 0xA,"Negative: "	;statement for negative numbers
len2: equ $-neg_st

section .bss
result: resb 1			;reserving space for storing the count 

%macro read_write 3		;macro for read write instruction
mov rax,%1
mov rdi,%1
mov rsi,%2
mov rdx,%3
syscall
%endmacro

section .text
global _start
_start:

	mov rsi,block
	mov byte[cnt_pos],0x00
	mov byte[cnt_neg],0x00
	mov cl,0x04

	loop1:
	mov rax,qword[rsi]
	bt rax,63		
	jc negative		;if the number is negative then
	
	inc byte[cnt_pos]	;incremeting the positive count 
	jmp counter		;unconditional jump
	
	negative:		
	inc byte[cnt_neg]	;incrementing the negative count
	
	counter:
	add rsi,8		;taking pointer 8 bytes ahead
	dec cl			;decremeting the cl register count
	jnz loop1		;checking for 0 and looping
	
	mov rsi,result		;moving storage location into rsi

	mov bl, byte[cnt_pos]	;converting positive count to ascii
	cmp bl,0x09
	jbe less
	add bl,0x07
	less:
	add bl,0x30
	mov [rsi],bl
	inc rsi
	
	mov bl, byte[cnt_neg]	;converting negative count to ascii
	cmp bl,0x09
	jbe less1
	add bl,0x07
	less1:
	add bl,0x30
	mov [rsi],bl
	
	read_write 1,pos_st,len1	;all print statements
	read_write 1,result,1
	read_write 1,neg_st,len2
	read_write 1,result+1,8
	
	mov rax,60		;exit system call
	mov rdi,00
	syscall
