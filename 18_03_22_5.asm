%include "st_io.inc"
global _start
section .data
la dd 0
w dd 0
e dd 0
section .bss
a resw 999
section .text
_start:

GETUN [la]
mov [w],dword 0
_9:
mov ebx,[la]
cmp [w],ebx
jge _10
GETSIG eax
mov ebx,[w]
lea ebx,[a+ebx*2]
mov [ebx],ax
inc dword[w]
jmp _9
_10:

mov [w],dword 0
_1:
mov ebx,[la]
cmp [w],ebx
jge _2
mov ebx,[w]
lea ebx,[a+ebx*2]
mov bx,[ebx]
movsx ebx,bx
mov ecx,ebx

	mov ebx,[w]
	add ebx,1
	mov [e],ebx
	_3:
	mov ebx,[la]
	cmp [e],ebx
	jge _4
	mov ebx,[e]
	lea ebx,[a+ebx*2]
	mov bx,[ebx]
	movsx ebx,bx

		cmp ecx,ebx
		jl _5
		xchg ecx,ebx
		_5:

		mov eax,ebx
		mov ebx,[e]
		lea ebx,[a+ebx*2]
		mov [ebx],ax

		mov eax,ecx
		mov ebx,[w]
		lea ebx,[a+ebx*2]
		mov [ebx],ax

	inc dword[e]
	jmp _3
	_4:

inc dword[w]
jmp _1
_2:

PUTCHAR 10
mov [w],dword 0
_7:
mov ebx,[la]
cmp [w],ebx
jge _8
mov ebx,[w]
lea ebx,[a+ebx*2]
mov bx,[ebx]
movsx ebx,bx
SIGNINT ebx
PUTCHAR 10
inc dword[w]
jmp _7
_8:

end:
FINISH
