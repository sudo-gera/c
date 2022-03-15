%include "st_io.inc"
global _start
section .data
section .bss
section .text
_start:
GETUN eax
mov ecx,eax
mov bl,12
div bl
cmp ah,0
jne not_12
mov ah,12
not_12:
movsx ebx,ah
sub ecx,ebx
mov eax,ecx
mov cl,12
div cl
UNSINT eax
PRINT ":"
UNSINT ebx
PUTCHAR 10
FINISH
