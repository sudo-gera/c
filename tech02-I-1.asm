.text
.global sum

<<<<<<< HEAD
sum:
    mov x9,0
    mov w9,w0
    mov x0,x9
    
=======
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
>>>>>>> 37dd3845e25d15f427ae2869a98a9eb82732cf13
