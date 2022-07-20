%include "st_io.inc"
; %include "macro.inc"
section .text
global _start
_start:
mov ecx,0
_1:
cmp ecx,10
jae _2
	GETUN eax
	push eax
inc ecx
jmp _1
_2:
mov ebx,esp
add ebx,40
mov esi,-1
mov ecx,-1
_3:
cmp ecx,-11
jle _4
	lea eax,[ebx+ecx*4]
	mov edi,[eax]
	cmp edi,0
	je _5
		mov eax,ebx
		lea eax,[eax+esi*4]
		mov [eax],edi
		dec esi
	_5:
dec ecx
jmp _3
_4:
mov edi,esi
sub edi,ecx
lea esp,[esp+edi*4]
neg esi
dec esi
PUTCHAR 10
mov ecx,0
_6:
cmp ecx,esi
jae _7
	pop eax
	UNSINT eax
	PUTCHAR 10
inc ecx
jmp _6
_7:
FINISH
