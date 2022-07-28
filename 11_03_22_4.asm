%include "st_io.inc"
global _start
section .data
section .bss
section .text
_start:
mov bh,10
GETUN eax
while:
cmp al,0
jne not_0
PRINT "n"
PUTCHAR 10
FINISH
not_0:
idiv bh
cmp ah,5
jne not_5
PRINT "y"
PUTCHAR 10
FINISH
not_5:
mov ah,0
jmp while
