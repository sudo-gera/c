#include <sys/syscall.h>
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
        mov $SYS_read,%rax
        mov $0,%rdi
        mov $space, %rsi
        mov $lspace, %rdx
        sub $space, %rdx
        syscall
        mov %rax,%rdx
        mov $SYS_write, %rax
        mov $1, %rdi
        mov $space, %rsi
        syscall
        xor %rbx,%rbx
        cmp %rbx,%rdx
        jne _main
        mov $SYS_exit, %rax
        xor %rdi, %rdi
        syscall
