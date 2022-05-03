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
w resd 1
d resd 1
h resd 1
q resd 1
c resd 1
section .text
global _start
_start:
GETUN [h1]
GETUN [h2]
PUTCHAR 10
mov dword [w],0
_11:
mov eax,[w]
cmp eax,[h1]
jae _12
	mov dword [h],0
	_13:
	mov eax,[h]
	cmp eax,[h2]
	jae _14
		mov eax,[w]
		mov ebx,[h2]
		mul ebx
		add eax,[h]
		GETUN [c]
		lea eax,[aa+eax*4]
		mov ebx,[c]
		mov [eax],ebx
	inc dword [h]
	jmp _13
	_14:
	PUTCHAR 10
inc dword [w]
jmp _11
_12:
mov dword [min],-1
mov dword [max],0
mov dword [min_1],-1
mov dword [min_2],-1
mov dword [max_1],-1
mov dword [max_2],-1
mov dword [w],0
_15:
mov eax,[w]
cmp eax,[h1]
jae _16
	mov dword [h],0
	_17:
	mov eax,[h]
	cmp eax,[h2]
	jae _18
		mov eax,[w]
		mov ebx,[h2]
		mul ebx
		add eax,[h]
		lea eax,[aa+eax*4]
		mov eax,[eax]
		mov [q],eax
		cmp eax,[min]
		jae _19
			mov eax,[w]
			mov [min_1],eax
			mov eax,[h]
			mov [min_2],eax
			mov eax,[q]
			mov [min],eax
		_19:
		mov eax,[q]
		cmp eax,[max]
		jbe _20
			mov eax,[w]
			mov [max_1],eax
			mov eax,[h]
			mov [max_2],eax
			mov eax,[q]
			mov [max],eax
		_20:
	inc dword [h]
	jmp _17
	_18:
	PUTCHAR 10
inc dword [w]
jmp _15
_16:
UNSINT [min_1]
PRINT " "
UNSINT [min_2]
PRINT " "
UNSINT [min]
PUTCHAR 10
UNSINT [max_1]
PRINT " "
UNSINT [max_2]
PRINT " "
UNSINT [max]
PUTCHAR 10
FINISH
