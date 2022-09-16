%include "st_io.inc"
section .data
section .text
global _start
_start:
mov ecx,esp
GETUN ebp
PUTCHAR 10

mov edi,0
_1:
cmp edi,ebp
jae _2
	GETUN esi
	push word si
inc edi
jmp _1
_2:

PUTCHAR 10
mov edx,esp

mov esi,edx
_3:
cmp esi,ecx
jae _4
	mov edi,edx
	_5:
	cmp edi,esi
	jae _6
		mov bx,[esi]
		cmp bx,[edi]
		jne _7
			mov al,1
		_7:
	add edi,2
	jmp _5
	_6:
add esi,2
jmp _3
_4:

UNSINT eax
PUTCHAR 10

FINISH
