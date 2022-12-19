
./a.out:     file format elf64-littleaarch64


Disassembly of section .init:

_init:
    nop
    stp	x29, x30, [sp, #-16]!
    mov	x29, sp
    bl call_weak_fn
    ldp	x29, x30, [sp], 16
    ret

Disassembly of section .plt:

.plt:
    stp	x16, x30, [sp, #-16]!
    adrp	x16, 10000 __FRAME_END__+0xf588
    ldr	x17, [x16, 4088]
    add	x16, x16, 0xff8
    br
    nop
    nop
    nop

free@plt:
    adrp	x16, 11000 free@GLIBC_2.17
    ldr	x17, [x16]
    add	x16, x16, 0x0
    br

__cxa_finalize
    adrp	x16, 11000 free@GLIBC_2.17
    ldr	x17, [x16, 8]
    add	x16, x16, 0x8
    br

realloc
    adrp	x16, 11000 free@GLIBC_2.17
    ldr	x17, [x16, 16]
    add	x16, x16, 0x10
    br

__libc_start_main
    adrp	x16, 11000 free@GLIBC_2.17
    ldr	x17, [x16, 24]
    add	x16, x16, 0x18
    br

getchar_unlocked
    adrp	x16, 11000 free@GLIBC_2.17
    ldr	x17, [x16, 32]
    add	x16, x16, 0x20
    br

abort
    adrp	x16, 11000 free@GLIBC_2.17
    ldr	x17, [x16, 40]
    add	x16, x16, 0x28
    br

putchar_unlocked
    adrp	x16, 11000 free@GLIBC_2.17
    ldr	x17, [x16, 48]
    add	x16, x16, 0x30
    br

__gmon_start__
    adrp	x16, 11000 free@GLIBC_2.17
    ldr	x17, [x16, 56]
    add	x16, x16, 0x38
    br

Disassembly of section .text:

_start:
    nop
    mov	x29, 0x0
    mov	x30, 0x0
    mov	x5, x0
    ldr	x1, [sp]
    add	x2, sp, 0x8
    mov	x6, sp
    adrp	x0, 10000 __FRAME_END__+0xf588
    ldr	x0, [x0, 4032]
    mov	x3, 0x0
    mov	x4, 0x0
    bl __libc_start_main
    bl abort

call_weak_fn:
    adrp	x0, 10000 __FRAME_END__+0xf588
    ldr	x0, [x0, 4056]
    cbz	x0, 7c4 call_weak_fn+0x10
    b __gmon_start__
    ret
    nop
    nop

deregister_tm_clones:
    adrp	x0, 11000 free@GLIBC_2.17
    add	x0, x0, 0x50
    adrp	x1, 11000 free@GLIBC_2.17
    add	x1, x1, 0x50
    cmp	x1, x0
    beq deregister_tm_clones+0x2c
    adrp	x1, 10000 __FRAME_END__+0xf588
    ldr	x1, [x1, 4048]
    cbz	x1, 7fc deregister_tm_clones+0x2c
    mov	x16, x1
    br
    ret

register_tm_clones:
    adrp	x0, 11000 free@GLIBC_2.17
    add	x0, x0, 0x50
    adrp	x1, 11000 free@GLIBC_2.17
    add	x1, x1, 0x50
    sub	x1, x1, x0
    lsr	x2, x1, 63
    add	x1, x2, x1, asr 3
    asr	x1, x1, 1
    cbz	x1, 838 register_tm_clones+0x38
    adrp	x2, 10000 __FRAME_END__+0xf588
    ldr	x2, [x2, 4064]
    cbz	x2, 838 register_tm_clones+0x38
    mov	x16, x2
    br
    ret
    nop

__do_global_dtors_aux:
    stp	x29, x30, [sp, #-32]!
    mov	x29, sp
    str	x19, [sp, 16]
    adrp	x19, 11000 free@GLIBC_2.17
    ldrb	w0, [x19, 80]
    cbnz	w0, 87c __do_global_dtors_aux+0x3c
    adrp	x0, 10000 __FRAME_END__+0xf588
    ldr	x0, [x0, 4040]
    cbz	x0, 870 __do_global_dtors_aux+0x30
    adrp	x0, 11000 free@GLIBC_2.17
    ldr	x0, [x0, 72]
    bl __cxa_finalize
    bl deregister_tm_clones
    mov	w0, 0x1
    strb	w0, [x19, 80]
    ldr	x19, [sp, 16]
    ldp	x29, x30, [sp], 32
    ret
    nop
    nop

frame_dummy:
    b register_tm_clones

main:
    sub	sp, sp, 0x100
    str	x30, [sp, 240]
    mov	x4, 0x0
    mov	x5, 0x0
    mov	x6, 0x0

loop_in:
    str	x4, [sp]
    str	x5, [sp, 16]
    str	x6, [sp, 32]
    str	x7, [sp, 48]
    bl getchar_unlocked
    ldr	x4, [sp]
    ldr	x5, [sp, 16]
    ldr	x6, [sp, 32]
    ldr	x7, [sp, 48]
    cmp	x0, 0x100
    blt ____0
    b loop_out

____0:
    mov	x7, x0
    cmp	x5, x6
    blt ____1
    mov	x0, x4
    add	x6, x6, x6
    add	x6, x6, 0x10
    mov	x1, x6
    str	x4, [sp]
    str	x5, [sp, 16]
    str	x6, [sp, 32]
    str	x7, [sp, 48]
    bl realloc
    ldr	x4, [sp]
    ldr	x5, [sp, 16]
    ldr	x6, [sp, 32]
    ldr	x7, [sp, 48]
    mov	x4, x0

____1:
    str	x7, [x4, x5]
    add	x5, x5, 0x10
    b loop_in

loop_out:
    cmp	x5, 0x0
    bne ____2
    b end

____2:
    sub	x5, x5, 0x10
    ldr	x7, [x4, x5]
    mov	x0, x7
    str	x4, [sp]
    str	x5, [sp, 16]
    str	x6, [sp, 32]
    str	x7, [sp, 48]
    bl putchar_unlocked
    ldr	x4, [sp]
    ldr	x5, [sp, 16]
    ldr	x6, [sp, 32]
    ldr	x7, [sp, 48]
    b loop_out

end:
    mov	x0, x4
    str	x4, [sp]
    str	x5, [sp, 16]
    str	x6, [sp, 32]
    str	x7, [sp, 48]
    bl free
    ldr	x4, [sp]
    ldr	x5, [sp, 16]
    ldr	x6, [sp, 32]
    ldr	x7, [sp, 48]
    ldr	x30, [sp, 240]
    add	sp, sp, 0x100
    mov	x0, 0x0
    ret

Disassembly of section .fini:

_fini:
    nop
    stp	x29, x30, [sp, #-16]!
    mov	x29, sp
    ldp	x29, x30, [sp], 16
    ret
