%include "st_io.inc"
global _start
section .bss
tmp resb 4
section .data
a dw 125
b db 125
section .text
_start:
mov [tmp],dword 0
mov eax,0
mov al,[a]
mov ebx,0
mov bl,[b]
mul bl
mov [tmp],al
mov [tmp+1],ah
mov eax,0
mov al,[a+1]
mul bl
add [tmp+1],al
adc [tmp+2],ah
adc [tmp+3],byte 0
SIGNINT [tmp]
PUTCHAR 10
FINISH
