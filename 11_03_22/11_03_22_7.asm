%include "st_io.inc"
global _start
section .data
section .bss
section .text
_start:
mov ax,30
mov bx,20
mul bx
jc _1
jmp _0
_0:
jo _01
jmp _00
_1:
jo _11
jmp _10
_00:
SIGNINT 400
jmp end
_01:
SIGNINT 401
jmp end
_10:
SIGNINT 410
jmp end
_11:
SIGNINT 411
jmp end
end:
PUTCHAR 10
FINISH
