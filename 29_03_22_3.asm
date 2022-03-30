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
mov ebx,esp
add ebx,40
dmov [e],-1
dmov [w],-1
_3:
dsle [w],-11,_4
	daget [z],ebx,[w]
	deq [z],0,_5
		daput ebx,[e],[z]
		ddec [e]
	_5:
ddec [w]
jmp _3
_4:
dsub [z],[e],[w]
dmul [z],4
add esp,dword [z]
dneg [e]
ddec [e]
dmov [w],0
_6:
duge [w],[e],_7
	pop dword [q]
	UNSINT [q]
	PUTCHAR 10
dinc [w]
jmp _6
_7:
stop
