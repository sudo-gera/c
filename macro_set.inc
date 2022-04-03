%macro set 1-*
	%rep %0-1
		%rotate -1
		%ifidni %1,<
			dpush '<'
			dpush 2
		%elifidni %1,>
			dpush '>'
			dpush 2
		%elifidni %1,<=
			dpush '<='
			dpush 2
		%elifidni %1,>=
			dpush '<='
			dpush 2
		%elifidni %1,==
			dpush '=='
			dpush 2
		%elifidni %1,!=
			dpush '!='
			dpush 2
		%elifidni %1,+
			dpush '+'
			dpush 2
		%elifidni %1,-
			dpush '-'
			dpush 2
		%elifidni %1,*
			dpush '*'
			dpush 2
		%elifidni %1,/
			dpush '/'
			dpush 2
		%elifidni %1,\%
			dpush '%'
			dpush 2
		%elifidni %1,(
			dpush '('
			dpush 2
		%elifidni %1,)
			dpush ')'
			dpush 2
		%elifidni %1,and
			dpush 'and'
			dpush 2
		%elifidni %1,or
			dpush 'or'
			dpush 2
		%else
			dpush %1
			dpush 1
		%endif
	%endrep
	%rotate -1
	macro_args_read_
	macro_args_offset eax
	add eax,esp
	mov ebx,eax
	add ebx,(%0-1)*8
	call0 macro_bops,eax,ebx,ebx
	mov eax,[eax+4]
	macro_args_save_d %1
	add esp,(%0-1)*8
%endmacro

%macro macro_set_memmove 0
dmov [edx],0
dmov [edx+4],0
dmov [edx-8],0
dmov [edx+4-8],0
dsub esi,edx,8
dadd edi,edx,8
dsub ebp,ecx,edx
dsub ebp,8
dmemmove esi,edi,ebp
dsub ecx,16
dsub ebx,16
dsub edx,16
%endmacro

def macro_ops1
	for edx,eax,ebx,8
		if [edx],==,2
			if [edx+4],==,'*'
				dmul [edx+4+8],[edx+4-8]
				macro_set_memmove
			elif [edx+4],==,'/'
				ddiv [edx+4+8],[edx+4-8],[edx+4+8]
				macro_set_memmove
			elif [edx+4],==,'%'
				dmod [edx+4+8],[edx+4-8],[edx+4+8]
				macro_set_memmove
			end
		end
	end
	mov eax,ecx
end

def macro_ops2
	for edx,eax,ebx,8
		if [edx],==,2
			if [edx+4],==,'+'
				dadd [edx+4+8],[edx+4-8]
				macro_set_memmove
			elif [edx+4],==,'-'
				dsub [edx+4+8],[edx+4-8],[edx+4+8]
				macro_set_memmove
			end
		end
	end
	mov eax,ecx
end

def macro_ops3
	for edx,eax,ebx,8
		if [edx],==,2
			if [edx+4],==,'<'
				if [edx+4-8],<,[edx+4+8]
					dmov [edx+4+8],1
				else
					dmov [edx+4+8],0
				end
				macro_set_memmove
			elif [edx+4],==,'>'
				if [edx+4-8],>,[edx+4+8]
					dmov [edx+4+8],1
				else
					dmov [edx+4+8],0
				end
				macro_set_memmove
			elif [edx+4],==,'>='
				if [edx+4-8],>=,[edx+4+8]
					dmov [edx+4+8],1
				else
					dmov [edx+4+8],0
				end
				macro_set_memmove
			elif [edx+4],==,'<='
				if [edx+4-8],<=,[edx+4+8]
					dmov [edx+4+8],1
				else
					dmov [edx+4+8],0
				end
				macro_set_memmove
			elif [edx+4],==,'=='
				if [edx+4-8],==,[edx+4+8]
					dmov [edx+4+8],1
				else
					dmov [edx+4+8],0
				end
				macro_set_memmove
			elif [edx+4],==,'!='
				if [edx+4-8],!=,[edx+4+8]
					dmov [edx+4+8],1
				else
					dmov [edx+4+8],0
				end
				macro_set_memmove
			end
		end
	end
	mov eax,ecx
end

def macro_ops4
	for edx,eax,ebx,8
		if [edx],==,2
			if [edx+4],==,'and'
				if [edx+4-8],!=,0
					if 0,!=,[edx+4+8]
						dmov [edx+4+8],1
					else
						dmov [edx+4+8],0
					end
				else
					dmov [edx+4+8],0
				end
				macro_set_memmove
			end
		end
	end
	mov eax,ecx
end

def macro_ops5
	for edx,eax,ebx,8
		if [edx],==,2
			if [edx+4],==,'or'
				if [edx+4-8],!=,0
					dmov [edx+4+8],1
				else
					if 0,!=,[edx+4+8]
						dmov [edx+4+8],1
					else
						dmov [edx+4+8],0
					end
				end
				macro_set_memmove
			end
		end
	end
	mov eax,ecx
end



def macro_ops
	call2 ecx,ebx,macro_ops1,eax,ebx,ecx
	call2 ecx,ebx,macro_ops2,eax,ebx,ecx
	call2 ecx,ebx,macro_ops3,eax,ebx,ecx
	call2 ecx,ebx,macro_ops4,eax,ebx,ecx
	call2 ecx,ebx,macro_ops5,eax,ebx,ecx
	mov eax,ecx
end

def macro_bops
	for edx,eax,ebx,8
		if [edx],==,2
			if [edx+4],==,'('
				add edx,8
				push edx
				sub edx,8
			elif [edx+4],==,')'
				mov edi,edx
				pop esi
				call2 ecx,edx,macro_ops,esi,edx,ecx
				sub edi,edx
				sub ebx,edi
				dmov [edx],1
				dmov [edx+4],[edx-8+4]
				sub edx,8
				macro_set_memmove
				add edx,8
			end
		end
	end
	call2 ecx,ebx,macro_ops,eax,ebx,ecx	
	mov eax,ecx
end


