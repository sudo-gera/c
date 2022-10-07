.text

.global main
.global _main

.extern fgetc
.extern fputc
.extern getchar_unlocked
.extern putchar_unlocked
.extern realloc


_main:
main:
    sub sp,sp,256
    str x30,[sp,240]
    mov x4,0
    mov x5,0
    mov x6,0
    mov x7,0
    mov x8,0
    mov x9,0
    mov x10,0
    mov x11,0

    bl getchar_unlocked
    add x0,x0,1
    bl putchar_unlocked


    ldr x30,[sp,240]
    add sp,sp,256
    mov x0,0
ret

