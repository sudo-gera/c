%include "st_io.inc"
global _start
section .bss
a resb 1
b resd 1
section .data
section .text
_start:
mov byte[a],-12
movsx eax,byte[a]
mov [b],eax
SIGNINT [b]
PUTCHAR 10
FINISH
