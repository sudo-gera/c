%include "st_io.inc"
section .data
a times 5 db 0
b times 5 db 0
section .text
global _start
_start:
mov ecx,0
_3:
cmp ecx,5
jae _4
	GETUN eax
	mov [a+ecx],al
inc ecx
jmp _3
_4:

PUTCHAR 10

mov ecx,0
_5:
cmp ecx,5
jae _6
	GETUN eax
	mov [b+ecx],al
inc ecx
jmp _5
_6:

PUTCHAR 10

mov ecx,0
_1:
cmp ecx,5
jae _2
	mov al,[a+ecx]
	mov dl,[b+ecx]
	mov ah,0
	div dl
	movzx eax,ah
	add ebx,eax
inc ecx
jmp _1
_2:

UNSINT ebx
PUTCHAR 10

FINISH
