%include "st_io.inc"
global _start
section .bss
section .data
x db 2
a db 7
section .text
_start:
mov al,[x]
imul byte[x]
mov bx,ax
imul byte[x]
mov cx,ax
mov ax,bx
mov dl,10
imul dl
add ax,cx
add ax,5
mov cl,[a]
neg ax
idiv cl
mov ecx,0
movsx ecx,al
SIGNINT ecx
PUTCHAR 10
movsx ecx,ah
SIGNINT ecx
PUTCHAR 10
FINISH
