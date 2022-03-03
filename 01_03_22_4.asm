%include "st_io.inc"
global _start
section .bss
tmp resb 4
section .data
x db 100
a db 7
section .text
_start:
mov al,[x]
imul byte[x]
mov bx,ax
mov cx,0
mov cl,[x]
imul cx
mov [tmp],ax
mov [tmp+2],dx
mov eax,[tmp]
mov ecx,eax
mov eax,0
mov ax,bx
imul word 10
mov [tmp],ax
mov [tmp+2],dx
mov eax,[tmp]
add eax,ecx
add eax,5
neg eax

FINISH
