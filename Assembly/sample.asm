section .data
str1: db "Hello World", 0xA      ;initializing label with String 
len1: equ $-str1                 ;storing the length of the string

section .bss

section .text  
global _start:
_start:

   mov rax,1                     ;moving write system call to accumulator
   mov rdi,1
   mov rsi,str1                  ;specifying base location 
   mov rdx,len1                  ;specifying length of output 
   syscall

   mov rax,60
   mov rdi,00                    ;exit systemcall
   syscall
