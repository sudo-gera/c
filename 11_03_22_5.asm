%include "st_io.inc"
global _start
section .data
section .bss
k resb 4
section .text
_start:
GETUN ebx
mov [k],ebx
add [k],dword 1
mov eax,[k]
mov edx,0
mov ebx,60
div ebx
mov ecx,edx
mov edx,0
div ebx
UNSINT eax
PRINT ":"
UNSINT edx
PRINT ":"
UNSINT ecx
PUTCHAR 10
FINISH
