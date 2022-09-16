%include "st_io.inc"
%include "best_io.inc"
start
	printreg
	GETUN eax
	; getdword eax
	printreg
	call root
	printreg
	printudword ebx
	printreg
stop


root:
	mov ebx,0
	mov ecx,1<<30
	_2:
		lea edx,[ebx+ecx]
		cmp eax,edx
		jb _1
			sub eax,edx
			lea ebx,[ebx+ecx*2]
		_1:
		shr ebx,1
		shr ecx,2
	jnz _2
	mov eax,ebx
ret
