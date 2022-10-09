.global _start
.global _main
.global main

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

.text

main:
_main:
_start:
    mov $12,%rax
    mov $0,%rdi
    syscall
    mov %rax,%r8
    mov $0, %r9
    mov $0, %r10
    loop_in:
_ 1     if %r9 "_=" %r10,{
            mov %r10,%rax
            mov $2,%rdx
            mul %rdx
            mov %rax,%r10
            add $256,%r10
            mov $12,%rax
            lea (%r8,%r10),%rdi
            syscall
_ 1     ,}
        mov $0,%rax
        mov $0,%rdi
        mov %r8,%rsi
        add %r9,%rsi
        mov %r10, %rdx
        sub %r9, %rdx
        syscall
        mov %rax,%r12
_ 0     if %r12 "_=" $0,{
            jmp loop_in_end
_ 0     ,}
        add %r12,%r9
    jmp loop_in
    loop_in_end:
    mov %r8,%r12
    mov %r8,%r13
    add %r9,%r13
    sub $1,%r13
    loop_all_rev:
_ 2     if %r12 ">=" %r13 ,{
            jmp loop_all_rev_end
_ 2     ,}
        mov (%r12),%al
        mov (%r13),%bl
        mov %bl,(%r12)
        mov %al,(%r13)
        add $1,%r12
        sub $1,%r13
    jmp loop_all_rev
    loop_all_rev_end:
    mov %r8,%r13
    add %r9,%r13
    sub $1,%r13
    mov %r13,%r12
    loop_all_word_rev:
_ 5     if %r12 "_=" %r8,{
            mov %r12,%r14
            loop_last_word_rev:
_ 6             if %r12 ">=" %r13 ,{
                    jmp loop_last_word_rev_end
_ 6             ,}
                mov (%r12),%al
                mov (%r13),%bl
                mov %bl,(%r12)
                mov %al,(%r13)
                add $1,%r12
                sub $1,%r13
            jmp loop_last_word_rev
            loop_last_word_rev_end:
            mov %r14,%r12
            mov %r12,%r13
            jmp loop_all_word_rev_end
_ 5     ,}
        mov (%r12),%al
_ 3     if %al "_=" $10,{
            mov %r12,%r14
            loop_one_word_rev:
_ 4             if %r12 ">=" %r13 ,{
                    jmp loop_one_word_rev_end
_ 4             ,}
                mov (%r12),%al
                mov (%r13),%bl
                mov %bl,(%r12)
                mov %al,(%r13)
                add $1,%r12
                sub $1,%r13
            jmp loop_one_word_rev
            loop_one_word_rev_end:
            mov %r14,%r13
            mov %r13,%r12
            sub $1,%r13
_ 3     ,}
        sub $1,%r12
    jmp loop_all_word_rev
    loop_all_word_rev_end:
    mov %r9,%rdx
    mov $1, %rax
    mov $1, %rdi
    mov %r8, %rsi
    syscall
mov $60, %rax
xor %rdi, %rdi
syscall
