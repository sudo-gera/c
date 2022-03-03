%include "st_io.inc"
global _start
section .bss
d resb 4
section .text
_start:
mov cx,[q]

mov [d],ch
mov [d+1],cl

UNSINT [d]

;mov eax,4
;mov ebx,1
;mov ecx,d
;mov edx,2
;int 0x80

mov eax,1
int 0x80

section .data
s db "1 2345678"
q dw 12592
