.data
space:
    .ascii "-------------------------------------------------------------------------------------\n"
lspace:
    .long -1

.global _start
.global _main
.global main

.extern print

.text

.macro putint arg
push %rdi
push \arg
pop %rdi
call print
pop %rdi
.endm

.macro _ place, command, left, comp, right, br
    .ifc \command,if
        cmp \right,\left
        .ifc \comp,>=
            jl _\place
        .endif
        .ifc \comp,<=
            jg _\place
        .endif
        .ifc \comp,!=
            je _\place
        .endif
        .ifc \comp,==
            jne _\place
        .endif
        .ifc \comp,_=
            jne _\place
        .endif
        .ifc \comp,>
            jle _\place
        .endif
        .ifc \comp,<
            jge _\place
        .endif
    .endif
    .ifc \command,}
        _\place\():
    .endif
.endm

/*
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
*/





.text
main:
_main:
#_start:
    mov $12,%rax
    mov $0,%rdi
    syscall
    mov %rax,%r8
    mov $0, %r9
    mov $0, %r10

    loop_in:
        mov $0,%rax
        mov $0,%rdi
        mov $space, %rsi
        mov $lspace, %rdx
        sub $space, %rdx
        syscall

        mov %rax,%r12

        if %rax "_=" 0,{
            jmp loop_end
        }

        lea [%r9+%rax],%rbx

        if %rbx > %%r10,{
            
        }


    jmp loop_in
    loop_end:





    mov $60, %rax
    xor %rdi, %rdi
    syscall
