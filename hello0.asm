.data
msg:
    .ascii "Hell, Word!\n"
msg_end:

.text
.global _start
_start:
    mov r7, #4
    mov r0, #1
    ldr r1, =msg
    mov r2, #12
    svc #0

    mov r7, #1
    mov r0, #0
    svc #0