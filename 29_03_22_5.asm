%include "st_io.inc"
section .data
aa times 9 dd 9
section .text
global _start
_start:
mov ecx,0
_1:
cmp ecx,9
jae _2
	lea eax,[aa+ecx*4]
	UNSINT [eax]
	PUTCHAR 32
inc ecx
jmp _1
_2:
PUTCHAR 10
push dword aa
mov eax,[esp]
mov dword [eax+ 0],0
mov dword [eax+ 4],0
mov dword [eax+ 8],0
mov dword [eax+12],0
mov dword [eax+16],0
mov dword [eax+20],0
mov dword [eax+24],0
mov dword [eax+28],0
mov dword [eax+32],0
add esp,4

mov ecx,0
_3:
cmp ecx,9
jae _4
	lea eax,[aa+ecx*4]
	UNSINT [eax]
	PUTCHAR 32
inc ecx
jmp _3
_4:
PUTCHAR 10

FINISH
