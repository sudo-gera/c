%include "st_io.inc"
global _start
section .data
a db 1,2,1,2,1
la dd 5
w dd 0
section .bss
section .text
_start:

mov [w],dword 0
_1:
mov ebx,[la]
cmp [w],ebx
jge _2
mov ebx,[w]
lea ebx,[a+ebx*1]
mov bl,[ebx]
movsx ebx,bl
cmp ebx,1
jne _3
UNSINT [w]
PUTCHAR 10
_3:
inc dword[w]
jmp _1
_2:


end:
FINISH
