%include "best_io.inc"
global _f_printreg
global _f_printstr

section .text

_f_printreg:
    printreg
ret

_f_printstr:
    push rax
    push rbx
    mov rax,[rsp+32]
    mov rbx,[rsp+24]
    printstr rax,rbx
    pop rbx
    pop rax
ret

; start
; jmp _2
; _1:
; db "--+++++++=="
; _2:
; push qword _1
; push qword _2
; call _f_printstr


; stop

