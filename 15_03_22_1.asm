%include "st_io.inc"
global _start
section .bss
c resb 4
section .text
_start:
GETUN eax
mov ecx,999
mov ebx,10
while:
mov edx,0
div ebx
inc dword[c]
add eax,0
loopne while
UNSINT [c]
PUTCHAR 10
FINISH
