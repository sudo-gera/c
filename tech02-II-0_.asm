.p2align 16

.data
A:  .int 0
    .int 0
B:  .int 0
    .int 0
C:  .int 0
    .int 0
D:  .int 0
    .int 0

.p2align 16

.text
.global A
.global B
.global C
.global D
.global _c

.extern R
.extern calculate

_d:
    mov x0,x1
ret

_c:
    ldr x4,=A
    str x0,[x4]
    ldr x4,=B
    str x1,[x4]
    ldr x4,=C
    str x2,[x4]
    ldr x4,=D
    str x3,[x4]

    sub sp,sp,16
    str lr,[sp]
    bl calculate
    ldr lr,[sp]
    add sp,sp,16

    ldr x0,R
ret
