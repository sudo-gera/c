%include "st_io.inc"
section .text
global _start
_start:
mov ecx,0
_1:
cmp ecx,10
jae _2
	GETUN esi
	push esi
inc ecx
jmp _1
_2:
pushad
add esp,32
mov eax,[esp]
mov ebx,[esp+4]
mov [esp],ebx
mov [esp+4],eax
sub esp,32
popad
mov ecx,0
_3:
cmp ecx,10
jae _4
	pop esi
	UNSINT esi
	PUTCHAR 10
inc ecx
jmp _3
_4:
FINISH
