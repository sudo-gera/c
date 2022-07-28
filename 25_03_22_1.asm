%include "st_io.inc"
section .bss
aa resd 9999
bb resd 9999
cc resd 9999
h1 resd 1
h2 resd 1
h3 resd 1
q resd 1
w resd 1
h resd 1
c resd 1
a resd 1
s resd 1
section .text
global _start
_start:
GETUN [h1]
GETUN [h2]
GETUN [h3]
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
		mov eax,[h2]
		mov ebx,[w]
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
mov dword [w],0
_22:
mov eax,[w]
cmp eax,[h2]
jae _23
	mov dword [h],0
	_24:
	mov eax,[h]
	cmp eax,[h3]
	jae _25
		mov eax,[h3]
		mov ebx,[w]
		mul ebx
		add eax,[h]
		GETUN [c]
		lea eax,[bb+eax*4]
		mov ebx,[c]
		mov [eax],ebx
	inc dword [h]
	jmp _24
	_25:
	PUTCHAR 10
inc dword [w]
jmp _22
_23:
mov dword [w],0
_1:
mov eax,[w]
cmp eax,[h1]
jae _2
	mov dword [h],0
	_3:
	mov eax,[h]
	cmp eax,[h3]
	jae _4
		mov dword [s],0
		mov dword [q],0
		_9:
		mov eax,[q]
		cmp eax,[h2]
		jae _10
			mov eax,[h2]
			mov ebx,[w]
			mul ebx
			add eax,[q]
			lea eax,[aa+eax*4]
			mov eax,[eax]
			mov [a],eax
			mov eax,[h3]
			mov ebx,[q]
			mul ebx
			add eax,[h]
			lea eax,[bb+eax*4]
			mov eax,[eax]
			mov ebx,[a]
			mul ebx
			add [s],eax
		inc dword [q]
		jmp _9
		_10:
		mov eax,[h3]
		mov ebx,[w]
		mul ebx
		add eax,[h]
		lea eax,[cc+eax*4]
		mov ebx,[s]
		mov [eax],ebx
	inc dword [h]
	jmp _3
	_4:
inc dword [w]
jmp _1
_2:
mov dword [w],0
_5:
mov eax,[w]
cmp eax,[h1]
jae _6
	mov dword [h],0
	_7:
	mov eax,[h]
	cmp eax,[h3]
	jae _8
		mov eax,[h3]
		mov ebx,[w]
		mul ebx
		add eax,[h]
		lea eax,[cc+eax*4]
		mov eax,[eax]
		mov [c],eax
		UNSINT [c]
		PRINT " "
	inc dword [h]
	jmp _7
	_8:
	PUTCHAR 10
inc dword [w]
jmp _5
_6:
FINISH
