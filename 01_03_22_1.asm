%include "st_io.inc"
global _start
section .bss
x resd 1
xp resd 1
section .data
y dd 25
t dd 19
section .text
_start:
mov dword [xp],t

mov ecx,[xp]
mov ebx,[ecx]
mov [x],ebx

mov ebx,[y]
mov [ecx],ebx

; mov bx,[x]
SIGNINT [x]
PUTCHAR 32
SIGNINT [ecx]
PUTCHAR 10
FINISH
