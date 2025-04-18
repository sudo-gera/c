.text

.global main

.extern fgetc
.extern fputc
.extern getchar_unlocked
.extern putchar_unlocked
.extern realloc

.macro call fun
    str x4,[sp,0]
    str x5,[sp,16]
    str x6,[sp,32]
    str x7,[sp,48]
    str x8,[sp,64]
    str x9,[sp,80]
    str x10,[sp,96]
    str x11,[sp,112]
    bl \fun
    ldr x4,[sp,0]
    ldr x5,[sp,16]
    ldr x6,[sp,32]
    ldr x7,[sp,48]
    ldr x8,[sp,64]
    ldr x9,[sp,80]
    ldr x10,[sp,96]
    ldr x11,[sp,112]
.endm

.macro _ place, command, left, comp, right, br
    .ifc \command,if
        cmp \left,\right
        .ifc \comp,>=
            blt _\place
        .endif
        .ifc \comp,<=
            bgt _\place
        .endif
        .ifc \comp,!=
            beq _\place
        .endif
        .ifc \comp,==
            bne _\place
        .endif
        .ifc \comp,_=
            bne _\place
        .endif
        .ifc \comp,>
            ble _\place
        .endif
        .ifc \comp,<
            bge _\place
        .endif
    .endif
    .ifc \command,}
        _\place\():
    .endif
.endm

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

    loop_in:
        call getchar_unlocked
        mov x7,0
        mov w7,w0
_ 0     if x7 ">=" 256,{
            b loop_out
_ 0     ,}
_ 3     if x9 "_=" 8,{
_ 1         if x5 ">=" x6,{
                mov x0,x4
                add x6,x6,x6
                add x6,x6,8
                mov x1,x6
                call realloc
                mov x4,x0
_ 1         ,}
            str x8,[x4,x5]
            add x5,x5,8
            mov x9,0
            mov x8,0
_ 3     ,}
        mov x0,256
        mul x8,x8,x0
        add x8,x8,x7
        add x9,x9,1
    b loop_in
    loop_out:
_ 4     if  x9 "_=" 0,{
_ 5         if  x5 "_=" 0,{
                b end
_ 5         ,}
            sub x5,x5,8
            ldr x7,[x4,x5]
            mov x8,x7
            mov x9,8
_ 4     ,}
        mov x0,x8
        call putchar_unlocked
        mov x0,256
        udiv x8,x8,x0
        sub x9,x9,1
    b loop_out
    end:
    mov x0,x4
    call free
    ldr x30,[sp,240]
    add sp,sp,256
    mov x0,0
ret

