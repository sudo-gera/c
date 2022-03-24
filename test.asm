%include "st_io.inc"
%include "macro.inc"

darray aa
start
GETUN eax
dmov ebx,2
dmov ecx,_2
_1:
dule eax,1,ecx
	dumod ecx,eax,ebx
	deq ecx,0,_3
		dadd ebx,1
		jmp _4
	_3:
		dapush aa,ebx
		dudiv eax,ebx
	_4:
jmp _1
_2:
_5:
duge 0,[len_aa],_6
	dapop ebx,aa
	UNSINT ebx
	PUTCHAR 10
jmp _5
_6:
stop
