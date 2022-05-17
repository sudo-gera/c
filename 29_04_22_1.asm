%include "macro.inc"
struc tree
.z resd 1
.x resd 1
.v resd 1
endstruc

section .data
init_break dd 0
curr_break dd 0
unused dd 0
up dd 0



alloc:
	pushad
	cmp dword [init_break],0
	jne _alloc_no_init
		mov eax,45
		mov ebx,0
		int 0x80
		mov [init_break],eax
		mov [curr_break],eax
	_alloc_no_init:
	cmp dword [unused],0
	jne _alloc_no_new
		mov ebx,[curr_break]
		add ebx,tree_size
		mov eax,45
		int 0x80
		mov [curr_break],eax
		sub ebx,tree_size
		mov edx,[unused]
		mov [ebx],edx
		mov [unused],ebx
	_alloc_no_new:
	mov eax,[unused]
	mov ebx,[eax]
	mov [unused],ebx
	add esp,36
	mov [esp],eax
	sub esp,36
	popad
	ret

free:
	pushad
	add esp,36
	mov eax,[esp]
	sub esp,36
	mov ebx,[unused]
	mov [eax],ebx
	mov [unused],ebx
	ret

tree_print:
	pushad
	add esp,36
	mov eax,[esp]
	sub esp,36
	if eax
		push dword [eax+tree.z]
		call tree_print
		add esp,4
		write [eax+tree.v]
		push dword [eax+tree.x]
		call tree_print
		add esp,4
	end
	popad
	ret

begin

for [j],9
	dget [q]
	if [q],==,1
		dget [q]
		mov eax,[up]
		mov ebx,0
		mov edx,up
		while eax
			if [eax+tree.v],<,[q]
				mov ebx,eax
				lea edx,[eax+tree.z]
				mov eax,[edx]
			else
				mov ebx,eax
				lea edx,[eax+tree.x]
				mov eax,[edx]
			end
		end
		push dword 0
		call alloc
		pop ecx
		dmov [ecx+tree.z],0
		dmov [ecx+tree.x],0
		dmov [ecx+tree.v],[q]
		dmov [edx],ecx
		push dword[up]
		call tree_print
		add esp,4
		cput 10
	else
		dget [q]
		mov eax,[up]
		mov ebx,0
		mov edx,up
		while eax
			if [eax+tree.v],<,[q]
				mov ebx,eax
				mov eax,[edx]
			elif [eax+tree.v],>,[q]
				mov ebx,eax
				mov eax,[edx]
			else [eax+tree.v],==,[q]
				mov ebx,eax
				mov eax,0
			end
		end

end


end
