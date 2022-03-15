%include "st_io.inc"
global _start
section .data
section .bss
section .text
_start:
mov ecx,9
mov bl,0
mov bh,1
for:
jcxz end
add ecx,-1
mov al,bl
add al,bh
mov bl,bh
mov bh,al
jmp for
end:
movzx ecx,bl
UNSINT ecx
PUTCHAR 10
FINISH
