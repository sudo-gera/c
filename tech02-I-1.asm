.text
.global sum

.p2align 4

sum:
    while_begin:
    cmp x1,0
    beq while_end
        sub x1,x1,1
        ldr x10,[x2]
        add x2,x2,4
        add x0,x0,x10
    b while_begin
    while_end:
ret
