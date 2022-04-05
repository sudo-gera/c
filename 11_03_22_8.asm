%include "st_io.inc"
global _start
section .data
section .bss
section .text
_start:
mov eax,1
mov ebx,1
for:
mul ebx
jc end
add ebx,1
jmp for
end:
add ebx,-1
UNSINT ebx
PUTCHAR 10
FINISH
