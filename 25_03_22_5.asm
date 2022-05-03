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
		mov [q],eax
		mov eax,[h]
		add [q],eax
		GETUN [c]
		mov eax,[q]
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
_15:
mov eax,[w]
cmp eax,[h1]
jae _16
	mov dword [h],0
	_17:
	mov eax,[h]
	cmp eax,[w]
	jae _18
		mov eax,[w]
		mov ebx,[h2]
		mul ebx
		mov [q],eax
		mov eax,[h]
		add [q],eax
		mov eax,[h]
		mov ebx,[h1]
		mul ebx
		mov [e],eax
		mov eax,[w]
		add [e],eax
		mov eax,[q]
		lea eax,[aa+eax*4]
		mov eax,[eax]
		mov [z],eax
		mov eax,[e]
		lea eax,[aa+eax*4]
		mov eax,[eax]
		mov [x],eax
		mov eax,[q]
		lea eax,[aa+eax*4]
		mov ebx,[x]
		mov [eax],ebx
		mov eax,[e]
		lea eax,[aa+eax*4]
		mov ebx,[z]
		mov [eax],ebx
	inc dword [h]
	jmp _17
	_18:
inc dword [w]
jmp _15
_16:
mov dword [w],0
_19:
mov eax,[w]
cmp eax,[h1]
jae _20
	mov dword [h],0
	_21:
	mov eax,[h]
	cmp eax,[h2]
	jae _22
		mov eax,[w]
		mov ebx,[h2]
		mul ebx
		mov [q],eax
		mov eax,[h]
		add [q],eax
		mov eax,[q]
		lea eax,[aa+eax*4]
		mov eax,[eax]
		mov [z],eax
		UNSINT [z]
		PRINT " "
	inc dword [h]
	jmp _21
	_22:
	PUTCHAR 10
inc dword [w]
jmp _19
_20:
FINISH
