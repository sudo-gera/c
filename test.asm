extern printf
extern scanf
global main

section .data
a dq 0
b dq 0
scanfstr db '%lli',0
printfstr db '%lli',10,0
section .text


main:

mov rsi,a
mov rdi,scanfstr
mov rax,0
call scanf

mov rsi,b
mov rdi,scanfstr
mov rax,0
call scanf

mov rax,[a]
mov rbx,[b]

cmp rax,rbx
jl _
    xchg rax,rbx
_:


mov rsi,rax
mov rdi,printfstr
mov rax,0
call printf


mov rax,0
ret



