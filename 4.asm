%include "st_io.inc"
global _start
section .bss
a resd 1
section .text
_start:
mov ecx,(5684 / 4 + 357 / 3 + 245 / 5)*3
mov [a],ecx
UNSINT [a]
PUTCHAR 10
FINISH
section .data
