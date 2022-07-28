%include "st_io.inc"
section .data
aa dd 7,2,6,8,3,6,8,3,7
hh dd 3
ww dd 3
w dd 0
b dd 0
h dd 0
len_bb dd 0
bb times 1024 dd 0
section .text
global _start
_start:
mov ecx,0
_1:
cmp ecx,[ww]
jae _2
	mov dword [b],0
	mov esi,0
	_3:
	cmp esi,[hh]
	jae _4
		mov eax,[ww]
		mov ebx,ecx
		mul ebx
		add eax,esi
		lea eax,[aa+eax*4]
		mov eax,[eax]
		add [b],eax
	inc esi
	jmp _3
	_4:
	mov eax,[len_bb]
	lea eax,[bb+eax*4]
	mov ebx,[b]
	mov [eax],ebx
	inc dword [len_bb]
inc ecx
jmp _1
_2:
mov ecx,0
_5:
cmp ecx,[len_bb]
jae _6
	mov eax,ecx
	lea eax,[bb+eax*4]
	mov eax,[eax]
	UNSINT eax
	PUTCHAR 10
inc ecx
jmp _5
_6:

FINISH
