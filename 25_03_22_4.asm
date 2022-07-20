%include "st_io.inc"
section .bss
aa resd 9999
n resd 1
section .text
global _start
_start:
GETUN [n]
PUTCHAR 27
PRINT "[32m"
PUTCHAR 9
mov dword edi,1
_5:
cmp edi,[n]
ja _6
	UNSINT edi
	PUTCHAR 9
inc dword edi
jmp _5
_6:
PUTCHAR 27
PRINT "[0m"
PUTCHAR 10
mov esi,1
_1:
cmp esi,[n]
ja _2
	PUTCHAR 27
	PRINT "[32m"
	UNSINT esi
	PUTCHAR 9
	PUTCHAR 27
	PRINT "[0m"
	mov edi,1
	_3:
	cmp edi,[n]
	ja _4
		mov ebp,esi
		mov ecx,edi
		_7:
		mov eax,edi
		mul esi
		cmp eax,0
		je _8
			mov eax,esi
			idiv edi
			mov esi,edi
			mov edi,edx
		jmp _7
		_8:
		add esi,edi
		UNSINT esi
		mov esi,ebp
		mov edi,ecx
		PUTCHAR 9
	inc edi
	jmp _3
	_4:
	PUTCHAR 10
inc esi
jmp _1
_2:
FINISH
