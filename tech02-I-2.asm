.text
.global solve

.p2align 4

solve:
    mov x10,-1
    wh:
        add x10,x10,1
        mov x11,0
        add x11,x11,x0
        mul x11,x11,x10
        add x11,x11,x1
        mul x11,x11,x10
        add x11,x11,x2
        mul x11,x11,x10
        add x11,x11,x3
        cmp w11,0
        bne wh
    mov x0,x10
ret