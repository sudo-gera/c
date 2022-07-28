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
mov ecx,0
_3:
cmp ecx,10
jge _4
	mov ebx,esp
	add ebx,ecx
	add ebx,ecx
	add ebx,ecx
	add ebx,ecx
	mov edx,0
	cmp [ebx],edx
	jne _5
		inc al
	_5:
inc ecx
jmp _3
_4:
PUTCHAR 10
mov ecx,0
_6:
cmp ecx,10
jae _7
	pop esi
	UNSINT esi
	PUTCHAR 10
inc ecx
jmp _6
_7:
PUTCHAR 10
UNSINT eax
PUTCHAR 10
FINISH
