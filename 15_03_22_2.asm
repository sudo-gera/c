%include "st_io.inc"
global _start
section .data
section .bss
section .text
_start:
mov al,1
mov bl,0
mov cl,-1
for:
add bl,1
mul bl
jnc c
mov dl,0
add dl,0
c:
loopne for
end:
add bl,-1
UNSINT ebx
PUTCHAR 10
FINISH
