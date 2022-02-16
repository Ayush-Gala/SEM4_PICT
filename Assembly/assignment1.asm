section .data
input_msg: db "Enter 5 values: " , 0xA
len1: equ $-input_msg
output_msg: db "The 5 values you entered are: ", 0xA
len2: equ $-output_msg
cnt: db 0


section .bss
name: resb 20   ;reserving 20 bytes for name

%macro read_write 3 ;macro for reading and writing inputs
    mov rax, %1
    mov rdi, %1
    mov rsi, %2
    mov rdx, %3
    syscall
%endmacro

%macro exit 0       ;macro for exiting from the program
    mov rax,60
    mov rdi,60
    syscall
%endmacro

section .text
global _start
_start:

    read_write 1,input_msg,len1   
    mov rbx, name              ;loop for reading 5 names
    mov byte[cnt],0x5
    read_l:                      
        read_write 0,rbx,17     ;reading 16 byte input and 1 newline char
        syscall
        add rbx,17 
        dec byte[cnt]           ;decrementing count
        jnz read_l              ;jumping if the result is not 0

    read_write 1,output_msg,len2
    mov rbx, name              ;loop for printing 5 names
    mov byte[cnt],0x5
    print_l: 
        read_write 1,rbx,17
        syscall
        add rbx,17
        dec byte[cnt]  
        jnz print_l

    exit                        ;calling macro for exit system call
