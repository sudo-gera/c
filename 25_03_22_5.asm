%include "st_io.inc"
section .bss
aa resd 9999
h1 resd 1
h2 resd 1
min resd 1
min_1 resd 1
min_2 resd 1
max resd 1
max_1 resd 1
max_2 resd 1
q resd 1
w resd 1
e resd 1
h resd 1
c resd 1
z resd 1
x resd 1
section .text
global _start
_start:
GETUN [h1]
mov eax,[h1]
mov [h2],eax
PUTCHAR 10
mov ecx,0
_11:
cmp ecx,[h1]
jae _12
	mov esi,0
	_13:
	cmp esi,[h2]
	jae _14
		mov eax,ecx
		mov ebx,[h2]
		mul ebx
		add eax,esi
		mov [q],eax
		GETUN [c]
		mov eax,[q]
		lea eax,[aa+eax*4]
		mov ebx,[c]
		mov [eax],ebx
	inc dword esi
	jmp _13
	_14:
	PUTCHAR 10
inc dword ecx
jmp _11
_12:
mov dword ecx,0
_15:
cmp ecx,[h1]
jae _16
	mov dword esi,0
	_17:
	cmp esi,ecx
	jae _18
		mov eax,ecx
		mov ebx,[h2]
		mul ebx
		add eax,esi
		lea eax,[aa+eax*4]
		mov ebp,eax
		mov eax,esi
		mov ebx,[h1]
		mul ebx
		add eax,ecx
		lea eax,[aa+eax*4]
		mov ebx,[eax]
		xchg [ebp],ebx
		mov [eax],ebx
	inc dword esi
	jmp _17
	_18:
inc ecx
jmp _15
_16:
mov ecx,0
_19:
cmp ecx,[h1]
jae _20
	mov esi,0
	_21:
	cmp esi,[h2]
	jae _22
		mov eax,ecx
		mov ebx,[h2]
		mul ebx
		add eax,esi
		lea eax,[aa+eax*4]
		mov eax,[eax]
		mov [z],eax
		UNSINT [z]
		PRINT " "
	inc esi
	jmp _21
	_22:
	PUTCHAR 10
inc ecx
jmp _19
_20:
FINISH
