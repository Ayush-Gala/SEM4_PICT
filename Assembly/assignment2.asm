section .data
input_msg: dq "Enter string you want to check the length of: ", 0x9 ;input message for the user 
len1: equ $-input_msg
output_msg: dq "The length of the entered string is: ", 0x9         ;output message for the user
len2: equ $-output_msg  
cnt: db 0                       ;label to store the count of loop

section .bss
result: resb 1                  ;creating a pointer for storing the result
string: resb 200                ;allocating memory of 200 bytes to string label

%macro read_write 3             ;macro for read and write system call
    mov rax,%1
    mov rdi,%1
    mov rsi,%2
    mov rdx,%3
    syscall
%endmacro

%macro exit 0                   ;macro for exit system call
    mov rax,60
    mov rdi,00
    syscall
%endmacro

section .text
global _start
_start:

    read_write 1,input_msg,len1
    read_write 0,string,200
    dec rax                             ;decrementing rax to eliminate newline char count
    mov rsi,result
    mov byte[cnt],0x10                     ;setting count to 16

    loop1:
        rol rax,4                       ;performing 4 bit rotations
        mov bl,al
        and bl,0x0F                     ;isolating last bit 
        cmp bl,0x09
        jbe less                        ;call for conversion to ASCII
        add bl,0x07                     ;for A-F
        less: add bl,0x30               ;for 0-9
        mov [rsi],bl
        inc rsi
        dec byte[cnt]                   ;decrementing count
        jnz loop1                       ;looping on non-zero answer

    read_write 1,output_msg,len2
    read_write 1,result,16

    exit
