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
regout
pushad
add esp,32
mov eax,dword [esp]
mov ebx,dword [esp+4]
mov dword [esp],ebx
mov dword [esp+4],eax
sub esp,32
popad
regout
dmov [w],0
_3:
duge [w],10,_4
	pop dword [q]
	UNSINT [q]
	PUTCHAR 10
dinc [w]
jmp _3
_4:
stop
