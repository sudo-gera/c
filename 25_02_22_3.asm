%include "st_io.inc"
section .data
a dd 1823798325
b dd 136305492
c dd 0
global _start
section .text
_start:

mov ax,[a]
mov bx,[b]
add ax,bx
mov cx,ax
mov ax,[a+2]
mov bx,[b+2]
adc ax,bx
mov [c],cx
mov [c+2],ax
UNSINT [c]


mov eax,1
mov ebx,0
int 0x80
