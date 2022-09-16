%include "best_io.inc"
start
	getdword eax
	call root
	printudword ebx
stop


root:
	mov ebx,0
	mov ecx,1<<(__BITS__-2)
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
