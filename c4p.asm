section .text
global is_equal
is_equal:
	pushad
	add esp,36
	mov eax,[esp+0]
	mov ebx,[esp+4]
	mov ecx,[esp+8]
	mov edx,[esp+12]
	cmp eax,ecx
	jne _not
		cmp ebx,edx
		jne _not
			mov [esp],dword 1
			jmp _end
	_not:
	mov [esp],dword 0
	_end:
	sub esp,36
	popad
	ret
