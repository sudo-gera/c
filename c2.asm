%include "st_io.inc"
global _start
section .bss
dat resb 2
d resb 1
m resb 1
y resb 1
section .text
_start:

GETUN eax
mov [dat],ax

mov eax,0
mov ax,[dat]
and eax,1111111b
mov [y],al

mov eax,0
mov ax,[dat]
shr eax,7
and eax,1111b
mov [m],al

mov eax,0
mov ax,[dat]
shr eax,11
and eax,11111b
mov [d],al

mov eax,0
mov al,[d]
UNSINT eax
PRINT "."

mov eax,0
mov al,[m]
UNSINT eax
PRINT "."

mov eax,0
mov al,[y]
UNSINT eax
PUTCHAR 10


FINISH
