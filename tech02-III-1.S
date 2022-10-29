#include <sys/syscall.h>
.intel_syntax noprefix
.data
space:
    .ascii "-------------------------------------------------------------------------------------\n"
lspace:
    .long -1

.global _start
.global _main
.global main

.text
main:
_main:
_start:
        mov rax,SYS_read
        mov rdi,0
        mov rsi,space
        mov rdx,lspace
        sub rdx,space
        syscall
        mov rdx,rax
        mov rax,SYS_write
        mov rdi,1
        mov rsi,space
        syscall
        xor rbx,rbx
        cmp rdx,rbx
        jne _main
        mov rax,SYS_exit
        xor rdi,rdi
        syscall
