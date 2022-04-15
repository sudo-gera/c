%include "st_io.inc"
global _start
extern _q
section .text
_start:

mov eax,_1
jmp _q
_1:

FINISH
