%include "st_io.inc"
global _start
section .bss
a resb 1
b resw 1
section .data
section .text
_start:
mov byte[a],-12
movsx ax,byte[a]
mov [b],ax

movsx eax,word[b]
SIGNINT eax
PUTCHAR 10
FINISH
