.p2align 16
.data
printfs: .ascii "%i\n\0"
.p2align 16
scanfs: .ascii "%i%i\0"
.p2align 16
a: .int 0
s: .int 0

.text

.global main
.extern scanf
.extern printf

main:
    mov x3,lr
    sub sp,sp,16
    str x3,[sp]
    str x3,[sp]
    ldr x0,=scanfs
    ldr x1,=a
    ldr x2,=s
    bl scanf
    ldr x1,a
    ldr x2,s
    add x1,x1,x2
    ldr x0,=printfs
    bl printf
    ldr x3,[sp]
    add sp,sp,16
    mov lr,x3
    mov x0,0
ret