.data
space:
    .ascii "-------------------------------------------------------------------------------------\n"
lspace:
    .long -1

.global _start
.global _main
.global main


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


.data
_v:
    .int 0
    .int 0
    .int 0
    .int 0
_f16:
    .ascii "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f303132333435363738393a3b3c3d3e3f404142434445464748494a4b4c4d4e4f505152535455565758595a5b5c5d5e5f606162636465666768696a6b6c6d6e6f707172737475767778797a7b7c7d7e7f808182838485868788898a8b8c8d8e8f909192939495969798999a9b9c9d9e9fa0a1a2a3a4a5a6a7a8a9aaabacadaeafb0b1b2b3b4b5b6b7b8b9babbbcbdbebfc0c1c2c3c4c5c6c7c8c9cacbcccdcecfd0d1d2d3d4d5d6d7d8d9dadbdcdddedfe0e1e2e3e4e5e6e7e8e9eaebecedeeeff0f1f2f3f4f5f6f7f8f9fafbfcfdfeff"
_f16_0:
    .ascii "0000000000000000111111111111111122222222222222223333333333333333444444444444444455555555555555556666666666666666777777777777777788888888888888889999999999999999aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbccccccccccccccccddddddddddddddddeeeeeeeeeeeeeeeeffffffffffffffff"
_f16_1:
    .ascii "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
.text
_out:
    push %rax
    push %rbx
    push %rcx
    push %rdx
    push %rsi
    push %rdi
    push %r8
    push %r9
    push %r10
    push %r11
    push %r12
    push %r13
    push %r14
    push %r15

    push %rax
    push %rax
    mov $0,%rax
    mov 8(%rsp),%al
    mov $_f16,%rbx
    mov (%rbx,%rax,2),%ax
    mov %ax,0(%rsp)
    mov $0,%rax
    mov 9(%rsp),%al
    mov $_f16,%rbx
    mov (%rbx,%rax,2),%ax
    mov %ax,2(%rsp)
    mov $0,%rax
    mov 10(%rsp),%al
    mov $_f16,%rbx
    mov (%rbx,%rax,2),%ax
    mov %ax,4(%rsp)
    mov $0,%rax
    mov 11(%rsp),%al
    mov $_f16,%rbx
    mov (%rbx,%rax,2),%ax
    mov %ax,6(%rsp)
    mov $0,%rax
    mov 12(%rsp),%al
    mov $_f16,%rbx
    mov (%rbx,%rax,2),%ax
    mov %ax,8(%rsp)
    mov $0,%rax
    mov 13(%rsp),%al
    mov $_f16,%rbx
    mov (%rbx,%rax,2),%ax
    mov %ax,10(%rsp)
    mov $0,%rax
    mov 14(%rsp),%al
    mov $_f16,%rbx
    mov (%rbx,%rax,2),%ax
    mov %ax,12(%rsp)
    mov $0,%rax
    mov 15(%rsp),%al
    mov $_f16,%rbx
    mov (%rbx,%rax,2),%ax
    mov %ax,14(%rsp)
    mov $757935405,%eax
    shl $32,%rax
    mov $1031299442,%eax
    push %rax

    mov $24,%rdx
    mov $1, %rax
    mov $1, %rdi
    mov %rsp, %rsi
    syscall


    pop %rax
    pop %rax
    pop %rax
    pop %r15
    pop %r14
    pop %r13
    pop %r12
    pop %r11
    pop %r10
    pop %r9
    pop %r8
    pop %rdi
    pop %rsi
    pop %rdx
    pop %rcx
    pop %rbx
    pop %rax
ret


main:
_main:
_start:
    mov $258,%rax
    call _out

/*
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
_ 0     if %r12 "_=" 0,{
            jmp loop_out
_ 0     ,}
        add %r12,%r9
    jmp loop_in
    loop_out:


    mov %r9,%rdx
    mov $1, %rax
    mov $1, %rdi
    mov %r8, %rsi
    syscall


*/
    mov $60, %rax
    xor %rdi, %rdi
    syscall
