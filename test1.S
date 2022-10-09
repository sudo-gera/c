.global _start
.extern _f_printstr
.extern _f_printreg

.data
    _sb:
        .ascii "123123"
    _se:
        .int -1


.macro prstr str:vararg
    jmp _2\@
    _1\@\():
        .ascii "\str"
    _2\@\():
    push $_1\@
    push $_2\@
    call _f_printstr
.endm

.text
_start:
#    push $_sb
 #   push $_se
  #  call _f_printstr
prstr hello world ==


mov $60,%rax
mov $0,%rbx
syscall
