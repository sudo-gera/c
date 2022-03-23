%include "st_io.inc"
%include "macro.inc"

darray aa
start
GETUN eax
dmov ebx,2
_1:
dmov ecx,_2
dule eax,1,ecx
	dumod ecx,eax,ebx
	cmp ecx,0
	je _3
		dadd ebx,ebx,1
		jmp _4
	_3:
		dapush aa,ebx
		dudiv eax,eax,ebx
	_4:
jmp _1
_2:
dmov eax,0
_5:
duge eax,[len_aa],_6
	dapop ebx,aa
	UNSINT ebx
	PUTCHAR 10
jmp _5
_6:
stop
