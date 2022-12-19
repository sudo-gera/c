.p2align 4
.data
R:  .int 0
    .int 0
.text
.global calculate
.global R

.extern A
.extern B
.extern C
.extern D

calculate:
    ldr x0,A
    ldr x1,B
    ldr x2,C
    ldr x3,D
    mul x0,x0,x1
    mul x2,x2,x3
    add x0,x0,x2
    ldr x4,=R
    str x0,[x4]
ret
