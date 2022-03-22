;Assignment to find the largest number in an array of numbers
section .data
block: dq 0x0000000000000001, 0x00F000000000000, 0x00000000000F0000, 0x000000F000000000, 0x0000012300000000, 0xF010207040230F01
post: dq "The largest number in the array is: "	;statement that we will print before printing the result
len: equ $-post
cnt: db 0		;to store count of total digits to be converted to ascii

section .bss
result: resb 0		;to store the ascii result 

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
	
	mov rsi, block
	mov rdx, 0x0000000000000000
	mov cl,0x06
	
	loop1:
		mov rax,qword[rsi]
		cmp rax,rdx
		jbe lesser
		
		mov rdx,rax
		
		lesser:
		add rsi,8
		dec cl
		jnz loop1
		
	mov rsi,result
	mov byte[cnt],0x10
	mov rax,rdx
	
	loop2:
		rol rax,4
		mov bl, al
		and bl,0x0F
		cmp bl,0x09
		jbe less
		add bl,0x07
		less: add bl,0x30
		mov [rsi],bl
		inc rsi
		dec byte[cnt]
		jnz loop2
	
	read_write 1,post,len
	read_write 1,result,0x10
	
	mov rax,60
	mov rdi,00
	syscall
