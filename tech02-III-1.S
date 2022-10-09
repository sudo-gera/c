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
        mov $0,%rax
        mov $0,%rdi
        mov $space, %rsi
        mov $lspace, %rdx
        sub $space, %rdx
        syscall
        mov %rax,%rdx
        mov $1, %rax
        mov $1, %rdi
        mov $space, %rsi
        syscall
        xor %rbx,%rbx
        cmp %rbx,%rdx
        jne _main
        mov $60, %rax
        xor %rdi, %rdi
        syscall
