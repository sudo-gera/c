.text
.global main

.extern putchar_unlocked
.extern getchar_unlocked


main:
    sub sp,sp,16
    str x30,[sp]

    loop:
        bl getchar_unlocked
        cmp x0,256
        bhs end
        sub x0,x0,48
        cmp x0,10
        bhs _1
            add x0,x0,48
            bl putchar_unlocked
        _1:
    b loop
    end:

    ldr x30,[sp]
    add sp,sp,16
    mov x0,0
ret