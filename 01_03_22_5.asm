%include "st_io.inc"
global _start
section .bss
section .data
a dd 4
b dd -2
c dd 1
d dd 1
section .text
_start:
mov cl,[a]
add cl,[b]
mov eax,0
mov al,[a]
idiv cl
mov bl,al
movsx cx,byte[c]
add cx,[d]
mov eax,0
mov al,[b]
idiv cl
add al,bl
mov bl,10
imul bl
movsx ecx,al
SIGNINT ecx
PUTCHAR 10
FINISH
