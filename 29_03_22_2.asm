%include "st_io.inc"
%include "macro.inc"
start
dmov [w],0
_1:
duge [w],10,_2
	GETUN [q]
	push dword [q]
dinc [w]
jmp _1
_2:
mov dword [w],0
_3:
mov ecx,10
cmp [w],ecx
jge _4
	mov ebx,esp
	add ebx,[w]
	add ebx,[w]
	add ebx,[w]
	add ebx,[w]
	mov edx,0
	cmp [ebx],edx
	jne _5
		inc al
	_5:
inc dword [w]
jmp _3
_4:
dmov [w],0
_6:
duge [w],10,_7
	pop dword [q]
	UNSINT [q]
	PUTCHAR 10
dinc [w]
jmp _6
_7:
UNSINT eax
PUTCHAR 10
stop
