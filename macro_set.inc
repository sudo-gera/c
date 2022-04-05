%assign macro_set_len 3

%macro set 1-*
	push %%_1
	%rep %0
		%rotate -1
		%ifidni %1,+
			dpush 0
			dpush '+'
			dpush 2
		%elifidni %1,-
			dpush 0
			dpush '-'
			dpush 2
		%elifidni %1,*
			dpush 0
			dpush '*'
			dpush 2
		%elifidni %1,/
			dpush 0
			dpush '/'
			dpush 2
		%elifidni %1,%
			dpush 0
			dpush '%'
			dpush 2
		%elifidni %1,(
			dpush 0
			dpush '('
			dpush 2
		%elifidni %1,)
			dpush 0
			dpush ')'
			dpush 2
		%elifidni %1,<
			dpush 0
			dpush '<'
			dpush 2
		%elifidni %1,>
			dpush 0
			dpush '>'
			dpush 2
		%elifidni %1,<=
			dpush 0
			dpush '<='
			dpush 2
		%elifidni %1,>=
			dpush 0
			dpush '<='
			dpush 2
		%elifidni %1,==
			dpush 0
			dpush '=='
			dpush 2
		%elifidni %1,!=
			dpush 0
			dpush '!='
			dpush 2
		%elifidni %1,and
			dpush 0
			dpush 'and'
			dpush 2
		%elifidni %1,or
			dpush 0
			dpush 'or'
			dpush 2
		%elifidni %1,[
			dpush 0
			dpush '['
			dpush 2
		%elifidni %1,]
			dpush 0
			dpush ']'
			dpush 2
		%elifidni %1,b[
			dpush 0
			dpush 'b['
			dpush 2
		%elifidni %1,w[
			dpush 0
			dpush 'w['
			dpush 2
		%elifidni %1,d[
			dpush 0
			dpush 'd['
			dpush 2
		%elifidni %1,=
			dpush 0
			dpush '='
			dpush 2
		%elifidni %1,+=
			dpush 0
			dpush '+='
			dpush 2
		%elifidni %1,-=
			dpush 0
			dpush '-='
			dpush 2
		%elifidni %1,*=
			dpush 0
			dpush '*='
			dpush 2
		%elifidni %1,/=
			dpush 0
			dpush '/='
			dpush 2
		%elifidni %1,%=
			dpush 0
			dpush '%='
			dpush 2
		%elifidni %1,eax
			dpush 4
			dpush %1
			dpush 3
		%elifidni %1,ebx
			dpush 4
			dpush %1
			dpush 4
		%elifidni %1,ecx
			dpush 4
			dpush %1
			dpush 5
		%elifidni %1,edx
			dpush 4
			dpush %1
			dpush 6
		%elifidni %1,esi
			dpush 4
			dpush %1
			dpush 7
		%elifidni %1,edi
			dpush 4
			dpush %1
			dpush 8
		%elifidni %1,ebp
			dpush 4
			dpush %1
			dpush 9
		%elifidni %1,ax
			dpush 2
			wpush 0
			wpush %1
			dpush 3
		%elifidni %1,bx
			dpush 2
			wpush 0
			wpush %1
			dpush 4
		%elifidni %1,cx
			dpush 2
			wpush 0
			wpush %1
			dpush 5
		%elifidni %1,dx
			dpush 2
			wpush 0
			wpush %1
			dpush 6
		%elifidni %1,si
			dpush 2
			wpush 0
			wpush %1
			dpush 7
		%elifidni %1,di
			dpush 2
			wpush 0
			wpush %1
			dpush 8
		%elifidni %1,bp
			dpush 2
			wpush 0
			wpush %1
			dpush 9
		%elifidni %1,al
			dpush 1
			wpush 0
			bpush %1
			dpush 3
		%elifidni %1,bl
			dpush 1
			wpush 0
			bpush %1
			dpush 4
		%elifidni %1,cl
			dpush 1
			wpush 0
			bpush %1
			dpush 5
		%elifidni %1,dl
			dpush 1
			wpush 0
			bpush %1
			dpush 6
		%else
			%defstr %$arg %1
			%strlen %$lll %$arg
			%substr %$arg1 %$arg 1,1
			%substr %$arg2 %$arg %$lll,1
			%if %$arg1 == '[' && %$arg2 == ']'
				dpush 4
				push dword %1
				dpush 0
				pushad
				lea eax,%1
				mov [esp+32],eax
				popad
			%else
				dpush 0
				push dword %1
				dpush 1
			%endif
		%endif
	%endrep
	dpush (%0)*macro_set_len*4
	jmp macro_set_jmp
	%%_1:
%endmacro

section .text
	macro_set_jmp:
	macro_args_read_
	macro_args_offset eax
	add eax,esp
	mov ecx,[eax]
	add eax,4
	mov ebx,eax
	add ebx,ecx
	call0 macro_bops,eax,ebx,ebx
	dmov [ebx-4],[eax+4]
	macro_args_save_
	add esp,[esp]
	add esp,8
	jmp [esp-8+4]

%macro macro_set_memmove 1
dufor esi,%1
	mov edi,edx
	add edi,macro_set_len*4
	mov ebp,ecx
	sub ebp,edi
	dmemmove edx,edi,ebp
	sub ecx,macro_set_len*4
	sub ebx,macro_set_len*4
	sub edx,macro_set_len*4
end
%endmacro


%macro pr 0
; cput 27
; sput "[31m"
; write __LINE__
; cput 27
; sput "[0m"
; dufor ebp,eax,edx,macro_set_len*4
; 	cput 27
; 	sput "[34m"
; 	write [ebp]
; 	cput 27
; 	sput "[0m"
; 	write [ebp+4]
; 	cput 27
; 	sput "[35m"
; 	write [ebp+8]
; end
; dufor ebp,edx,ebx,macro_set_len*4
; 	cput 27
; 	sput "[34m"
; 	write [ebp]
; 	cput 27
; 	sput "[32m"
; 	write [ebp+4]
; 	cput 27
; 	sput "[35m"
; 	write [ebp+8]
; end
; cput 27
; sput "[0m"
; cput 10
%endmacro

def macro_ops
	mov edx,eax
	_________macro_ops_for_begin1:
	cmp edx,ebx
	jae _________macro_ops_for_end1
		pr
		cmp [edx],dword 2
		jne _________macro_ops_part1
			mov ebp,[edx+4]
			cmp ebp,'*'
			jne _________macro_ops_not1_1
				pushad
				mov eax,[edx+4+macro_set_len*4]
				mov ebx,[edx+4-macro_set_len*4]
				mov ecx,edx
				mul ebx
				mov [ecx+4+macro_set_len*4],eax
				popad
				macro_set_memmove 2
			jmp _________macro_ops_end1
			_________macro_ops_not1_1:
			cmp ebp,'/'
			jne _________macro_ops_not1_2
				pushad
				mov eax,[edx+4-macro_set_len*4]
				mov ebx,[edx+4+macro_set_len*4]
				mov ecx,edx
				cdq
				idiv ebx
				mov [ecx+4+macro_set_len*4],eax
				popad
				macro_set_memmove 2
			jmp _________macro_ops_end1
			_________macro_ops_not1_2:
			cmp ebp,'%'
			jne _________macro_ops_not1_3
				pushad
				mov eax,[edx+4-macro_set_len*4]
				mov ebx,[edx+4+macro_set_len*4]
				mov ecx,edx
				cdq
				idiv ebx
				mov [ecx+4+macro_set_len*4],edx
				popad
				macro_set_memmove 2
			jmp _________macro_ops_end1
			_________macro_ops_not1_3:
			_________macro_ops_end1:
		_________macro_ops_part1:
	add edx,macro_set_len*4
	jmp _________macro_ops_for_begin1
	_________macro_ops_for_end1:

	mov edx,eax
	_________macro_ops_for_begin2:
	cmp edx,ebx
	jae _________macro_ops_for_end2
		pr
		cmp [edx],dword 2
		jne _________macro_ops_part2
			mov ebp,[edx+4]
			cmp ebp,'+'
			jne _________macro_ops_not2_1
				pushad
				mov eax,[edx+4-macro_set_len*4]
				add eax,[edx+4+macro_set_len*4]
				mov [edx+4+macro_set_len*4],eax
				popad
				macro_set_memmove 2
			jmp _________macro_ops_end2
			_________macro_ops_not2_1:
			cmp ebp,'-'
			jne _________macro_ops_not2_2
				pushad
				mov eax,[edx+4-macro_set_len*4]
				sub eax,[edx+4+macro_set_len*4]
				mov [edx+4+macro_set_len*4],eax
				popad
				macro_set_memmove 2
			jmp _________macro_ops_end2
			_________macro_ops_not2_2:
			_________macro_ops_end2:
		_________macro_ops_part2:
	add edx,macro_set_len*4
	jmp _________macro_ops_for_begin2
	_________macro_ops_for_end2:

	mov edx,eax
	_________macro_ops_for_begin3:
	cmp edx,ebx
	jae _________macro_ops_for_end3
		pr
		cmp [edx],dword 2
		jne _________macro_ops_part3
			mov ebp,[edx+4]
			cmp ebp,'<'
			jne _________macro_ops_not3_1
				mov esi,[edx+4-macro_set_len*4]
				cmp esi,[edx+4+macro_set_len*4]
				jge _________macro_ops_cmp_begin1
					mov dword [edx+4+macro_set_len*4],1
				jmp _________macro_ops_cmp_end1
				_________macro_ops_cmp_begin1:
					mov dword [edx+4+macro_set_len*4],0
				_________macro_ops_cmp_end1:
				macro_set_memmove 2
			jmp _________macro_ops_end3
			_________macro_ops_not3_1:
			cmp ebp,'>'
			jne _________macro_ops_not3_2
				mov esi,[edx+4-macro_set_len*4]
				cmp esi,[edx+4+macro_set_len*4]
				jle _________macro_ops_cmp_begin2
					mov dword [edx+4+macro_set_len*4],1
				jmp _________macro_ops_cmp_end2
				_________macro_ops_cmp_begin2:
					mov dword [edx+4+macro_set_len*4],0
				_________macro_ops_cmp_end2:
				macro_set_memmove 2
			jmp _________macro_ops_end3
			_________macro_ops_not3_2:
			cmp ebp,'>='
			jne _________macro_ops_not3_3
				mov esi,[edx+4-macro_set_len*4]
				cmp esi,[edx+4+macro_set_len*4]
				jl _________macro_ops_cmp_begin3
					mov dword [edx+4+macro_set_len*4],1
				jmp _________macro_ops_cmp_end3
				_________macro_ops_cmp_begin3:
					mov dword [edx+4+macro_set_len*4],0
				_________macro_ops_cmp_end3:
				macro_set_memmove 2
			jmp _________macro_ops_end3
			_________macro_ops_not3_3:
			cmp ebp,'<='
			jne _________macro_ops_not3_4
				mov esi,[edx+4-macro_set_len*4]
				cmp esi,[edx+4+macro_set_len*4]
				jg _________macro_ops_cmp_begin4
					mov dword [edx+4+macro_set_len*4],1
				jmp _________macro_ops_cmp_end4
				_________macro_ops_cmp_begin4:
					mov dword [edx+4+macro_set_len*4],0
				_________macro_ops_cmp_end4:
				macro_set_memmove 2
			jmp _________macro_ops_end3
			_________macro_ops_not3_4:
			cmp ebp,'=='
			jne _________macro_ops_not3_5
				mov esi,[edx+4-macro_set_len*4]
				cmp esi,[edx+4+macro_set_len*4]
				jne _________macro_ops_cmp_begin5
					mov dword [edx+4+macro_set_len*4],1
				jmp _________macro_ops_cmp_end5
				_________macro_ops_cmp_begin5:
					mov dword [edx+4+macro_set_len*4],0
				_________macro_ops_cmp_end5:
				macro_set_memmove 2
			jmp _________macro_ops_end3
			_________macro_ops_not3_5:
			cmp ebp,'!='
			jne _________macro_ops_not3_6
				mov esi,[edx+4-macro_set_len*4]
				cmp esi,[edx+4+macro_set_len*4]
				je _________macro_ops_cmp_begin6
					mov dword [edx+4+macro_set_len*4],1
				jmp _________macro_ops_cmp_end6
				_________macro_ops_cmp_begin6:
					mov dword [edx+4+macro_set_len*4],0
				_________macro_ops_cmp_end6:
				macro_set_memmove 2
			jmp _________macro_ops_end3
			_________macro_ops_not3_6:
			_________macro_ops_end3:
		_________macro_ops_part3:
	add edx,macro_set_len*4
	jmp _________macro_ops_for_begin3
	_________macro_ops_for_end3:

	mov edx,eax
	_________macro_ops_for_begin4:
	cmp edx,ebx
	jae _________macro_ops_for_end4
		pr
		cmp [edx],dword 2
		jne _________macro_ops_part4
			mov ebp,[edx+4]
			cmp ebp,'and'
			jne _________macro_ops_not4_1
				mov esi,[edx+4-macro_set_len*4]
				cmp esi,0
				je _________macro_ops_cmp_begin7
					mov esi,[edx+4+macro_set_len*4]
					cmp esi,0
					je _________macro_ops_cmp_begin8
						mov dword [edx+4+macro_set_len*4],1
					jmp _________macro_ops_cmp_end8
					_________macro_ops_cmp_begin8:
						mov dword [edx+4+macro_set_len*4],0
					_________macro_ops_cmp_end8:
				jmp _________macro_ops_cmp_end7
				_________macro_ops_cmp_begin7:
					mov dword [edx+4+macro_set_len*4],0
				_________macro_ops_cmp_end7:
				macro_set_memmove 2
			jmp _________macro_ops_end4
			_________macro_ops_not4_1:
			_________macro_ops_end4:
		_________macro_ops_part4:
	add edx,macro_set_len*4
	jmp _________macro_ops_for_begin4
	_________macro_ops_for_end4:

	mov edx,eax
	_________macro_ops_for_begin5:
	cmp edx,ebx
	jae _________macro_ops_for_end5
		pr
		cmp [edx],dword 2
		jne _________macro_ops_part5
			mov ebp,[edx+4]
			cmp ebp,'or'
			jne _________macro_ops_not5_1
				mov esi,[edx+4-macro_set_len*4]
				cmp esi,0
				je _________macro_ops_cmp_begin9
					mov dword [edx+4+macro_set_len*4],1
				jmp _________macro_ops_cmp_end9
				_________macro_ops_cmp_begin9:
					mov esi,[edx+4+macro_set_len*4]
					cmp esi,0
					je _________macro_ops_cmp_begin10
						mov dword [edx+4+macro_set_len*4],1
					jmp _________macro_ops_cmp_end10
					_________macro_ops_cmp_begin10:
						mov dword [edx+4+macro_set_len*4],0
					_________macro_ops_cmp_end10:
				_________macro_ops_cmp_end9:
				macro_set_memmove 2
			jmp _________macro_ops_end5
			_________macro_ops_not5_1:
			_________macro_ops_end5:
		_________macro_ops_part5:
	add edx,macro_set_len*4
	jmp _________macro_ops_for_begin5
	_________macro_ops_for_end5:


	mov edx,ebx
	_________macro_ops_for_begin7:
	cmp edx,eax
	jbe _________macro_ops_for_end7
	sub edx,macro_set_len*4
		pr
		cmp [edx],dword 2
		jne _________macro_ops_part7
			mov ebp,[edx+4]
			cmp ebp,'='
			jne _________macro_ops_not7_1
				pushad
				mov eax,[edx+4+macro_set_len*4]
				mov ebx,[edx-macro_set_len*4]
				mov [edx+macro_set_len*4],ebx
				mov esi,[edx+8-macro_set_len*4]
				mov [edx+8+macro_set_len*4],esi
				cmp esi,4
				jne _________macro_ops_assign7_1_n4
					mov [ebx],eax
				_________macro_ops_assign7_1_n4:
				cmp esi,2
				jne _________macro_ops_assign7_1_n2
					mov [ebx],ax
				_________macro_ops_assign7_1_n2:
				cmp esi,1
				jne _________macro_ops_assign7_1_n1
					mov [ebx],al
				_________macro_ops_assign7_1_n1:
				popad
				macro_set_memmove 2
				add edx,macro_set_len*4*2
			jmp _________macro_ops_end7
			_________macro_ops_not7_1:
			cmp ebp,'+='
			jne _________macro_ops_not7_2
				pushad
				mov eax,[edx+4-macro_set_len*4]
				add eax,[edx+4+macro_set_len*4]
				mov [edx+4+macro_set_len*4],eax
				mov ebx,[edx-macro_set_len*4]
				mov [edx+macro_set_len*4],ebx
				mov esi,[edx+8-macro_set_len*4]
				mov [edx+8+macro_set_len*4],esi
				cmp esi,4
				jne _________macro_ops_assign7_1_n4
					mov [ebx],eax
				_________macro_ops_assign7_2_n4:
				cmp esi,2
				jne _________macro_ops_assign7_2_n2
					mov [ebx],ax
				_________macro_ops_assign7_2_n2:
				cmp esi,1
				jne _________macro_ops_assign7_2_n1
					mov [ebx],al
				_________macro_ops_assign7_2_n1:
				popad
				macro_set_memmove 2
				add edx,macro_set_len*4*2
			jmp _________macro_ops_end7
			_________macro_ops_not7_2:
			cmp ebp,'-='
			jne _________macro_ops_not7_3
				pushad
				mov eax,[edx+4-macro_set_len*4]
				sub eax,[edx+4+macro_set_len*4]
				mov [edx+4+macro_set_len*4],eax
				mov ebx,[edx-macro_set_len*4]
				mov [edx+macro_set_len*4],ebx
				mov esi,[edx+8-macro_set_len*4]
				mov [edx+8+macro_set_len*4],esi
				cmp esi,4
				jne _________macro_ops_assign7_3_n4
					mov [ebx],eax
				_________macro_ops_assign7_3_n4:
				cmp esi,2
				jne _________macro_ops_assign7_3_n2
					mov [ebx],ax
				_________macro_ops_assign7_3_n2:
				cmp esi,1
				jne _________macro_ops_assign7_3_n1
					mov [ebx],al
				_________macro_ops_assign7_3_n1:
				popad
				macro_set_memmove 2
				add edx,macro_set_len*4*2
			jmp _________macro_ops_end7
			_________macro_ops_not7_3:
			cmp ebp,'*='
			jne _________macro_ops_not7_4
				pushad
				mov ecx,edx
				mov eax,[ecx+4-macro_set_len*4]
				mov ebx,[ecx+4+macro_set_len*4]
				mul ebx
				mov edx,ecx
				mov [ecx+4+macro_set_len*4],eax
				mov ebx,[edx-macro_set_len*4]
				mov [edx+macro_set_len*4],ebx
				mov esi,[edx+8-macro_set_len*4]
				mov [edx+8+macro_set_len*4],esi
				cmp esi,4
				jne _________macro_ops_assign7_4_n4
					mov [ebx],eax
				_________macro_ops_assign7_4_n4:
				cmp esi,2
				jne _________macro_ops_assign7_4_n2
					mov [ebx],ax
				_________macro_ops_assign7_4_n2:
				cmp esi,1
				jne _________macro_ops_assign7_4_n1
					mov [ebx],al
				_________macro_ops_assign7_4_n1:
				popad
				macro_set_memmove 2
				add edx,macro_set_len*4*2
			jmp _________macro_ops_end7
			_________macro_ops_not7_4:
			cmp ebp,'/='
			jne _________macro_ops_not7_5
				pushad
				mov ecx,edx
				mov eax,[ecx+4-macro_set_len*4]
				mov ebx,[ecx+4+macro_set_len*4]
				cdq
				idiv ebx
				mov edx,ecx
				mov [ecx+4+macro_set_len*4],eax
				mov ebx,[edx-macro_set_len*4]
				mov [edx+macro_set_len*4],ebx
				mov esi,[edx+8-macro_set_len*4]
				mov [edx+8+macro_set_len*4],esi
				cmp esi,4
				jne _________macro_ops_assign7_5_n4
					mov [ebx],eax
				_________macro_ops_assign7_5_n4:
				cmp esi,2
				jne _________macro_ops_assign7_5_n2
					mov [ebx],ax
				_________macro_ops_assign7_5_n2:
				cmp esi,1
				jne _________macro_ops_assign7_5_n1
					mov [ebx],al
				_________macro_ops_assign7_5_n1:
				popad
				macro_set_memmove 2
				add edx,macro_set_len*4*2
			jmp _________macro_ops_end7
			_________macro_ops_not7_5:
			cmp ebp,'%='
			jne _________macro_ops_not7_6
				pushad
				mov ecx,edx
				mov eax,[ecx+4-macro_set_len*4]
				mov ebx,[ecx+4+macro_set_len*4]
				cdq
				idiv ebx
				mov eax,edx
				mov edx,ecx
				mov [ecx+4+macro_set_len*4],eax
				mov ebx,[edx-macro_set_len*4]
				mov [edx+macro_set_len*4],ebx
				mov esi,[edx+8-macro_set_len*4]
				mov [edx+8+macro_set_len*4],esi
				cmp esi,4
				jne _________macro_ops_assign7_6_n4
					mov [ebx],eax
				_________macro_ops_assign7_6_n4:
				cmp esi,2
				jne _________macro_ops_assign7_6_n2
					mov [ebx],ax
				_________macro_ops_assign7_6_n2:
				cmp esi,1
				jne _________macro_ops_assign7_6_n1
					mov [ebx],al
				_________macro_ops_assign7_6_n1:
				popad
				macro_set_memmove 2
				add edx,macro_set_len*4*2
			jmp _________macro_ops_end7
			_________macro_ops_not7_6:
			_________macro_ops_end7:
		_________macro_ops_part7:
	jmp _________macro_ops_for_begin7
	_________macro_ops_for_end7:

	mov eax,ecx
end

def macro_bops
	mov edx,eax
	_________macro_ops_for_begin6:
	cmp edx,ebx
	jae _________macro_ops_for_end6
		pr
		cmp [edx],dword 2
		jne _________macro_ops_part6
			mov ebp,[edx+4]
			cmp ebp,'('
			jne _________macro_ops_not6_1
				add edx,macro_set_len*4
				push edx
				push dword 0
				sub edx,macro_set_len*4
			jmp _________macro_ops_end6
			_________macro_ops_not6_1:
			cmp ebp,')'
			jne _________macro_ops_not6_2
				mov edi,edx
				pop ebp
				pop esi
				call2 ecx,edx,macro_ops,esi,edx,ecx
				sub edi,edx
				sub ebx,edi
				mov ebp,esi
				sub ebp,macro_set_len*4*2
				cmp eax,ebp
				ja _________macro_ops_ncall
					cmp [ebp],dword 1
					jne _________macro_ops_nfunc
						mov ebp,1
					jmp _________macro_ops_func
					_________macro_ops_nfunc:
						mov ebp,0
					_________macro_ops_func:
				jmp _________macro_ops_call
				_________macro_ops_ncall:
					mov ebp,0
				_________macro_ops_call:
				cmp ebp,0
				je _________macro_ops_par
					mov ebp,esi
					sub ebp,macro_set_len*4*2
					mov edi,edx
					sub edi,esi
					ddiv edi,macro_set_len*4
					mov dword [edx],1
					cmp edi,0
					jne _________macro_ops_call_args_0
						call1 [edx+4],[ebp+4]
					jmp _________macro_ops_call_args_end
					_________macro_ops_call_args_0:
					cmp edi,1
					jne _________macro_ops_call_args_1
						call1 [edx+4],[ebp+4],[esi+4]
					jmp _________macro_ops_call_args_end
					_________macro_ops_call_args_1:
					cmp edi,2
					jne _________macro_ops_call_args_2
						call1 [edx+4],[ebp+4],[esi+4],[esi+4+macro_set_len*4]
					jmp _________macro_ops_call_args_end
					_________macro_ops_call_args_2:
					cmp edi,3
					jne _________macro_ops_call_args_3
						call1 [edx+4],[ebp+4],[esi+4],[esi+4+macro_set_len*4],[esi+4+macro_set_len*4*2]
					jmp _________macro_ops_call_args_end
					_________macro_ops_call_args_3:
						call1 [edx+4],[ebp+4],[esi+4],[esi+4+macro_set_len*4],[esi+4+macro_set_len*4*2],[esi+4+macro_set_len*4*3]
					_________macro_ops_call_args_end:
					dsub esi,macro_set_len*4
				jmp _________macro_ops_par_end
				_________macro_ops_par:
					mov dword [edx],1
					dmov [edx+4],[edx+4-macro_set_len*4]
				_________macro_ops_par_end:
				push eax
				mov eax,edx
				sub eax,esi
				add eax,macro_set_len*4
				ddiv eax,macro_set_len*4
				sub edx,macro_set_len*4
				macro_set_memmove eax
				add edx,macro_set_len*4
				pop eax
			jmp _________macro_ops_end6
			_________macro_ops_not6_2:
			cmp ebp,'b['
			jne _________macro_ops_not6_3
				add edx,macro_set_len*4
				push edx
				push dword 1
				sub edx,macro_set_len*4
			jmp _________macro_ops_end6
			_________macro_ops_not6_3:
			cmp ebp,'w['
			jne _________macro_ops_not6_4
				add edx,macro_set_len*4
				push edx
				push dword 2
				sub edx,macro_set_len*4
			jmp _________macro_ops_end6
			_________macro_ops_not6_4:
			cmp ebp,'d['
			jne _________macro_ops_not6_5
				add edx,macro_set_len*4
				push edx
				push dword 4
				sub edx,macro_set_len*4
			jmp _________macro_ops_end6
			_________macro_ops_not6_5:
			cmp ebp,'['
			jne _________macro_ops_not6_6
				add edx,macro_set_len*4
				push edx
				push dword 4
				sub edx,macro_set_len*4
			jmp _________macro_ops_end6
			_________macro_ops_not6_6:
			cmp ebp,']'
			jne _________macro_ops_not6_7
				mov edi,edx
				pop ebp
				pop esi
				call2 ecx,edx,macro_ops,esi,edx,ecx
				sub edi,edx
				sub ebx,edi
				cmp ebp,1
				jne _________macro_ops_get_n1
					pushad
					mov ebx,[edx+4-macro_set_len*4]
					mov ecx,[edx+4-macro_set_len*4*3]
					lea ebx,[ecx+ebx*1]
					mov al,[ebx]
					movsx eax,al
					mov [edx+4],eax
					mov [edx],ebx
					mov [edx+8],dword 1
					popad
				jmp _________macro_ops_get_end
				_________macro_ops_get_n1:
				cmp ebp,2
				jne _________macro_ops_get_n2
					pushad
					mov ebx,[edx+4-macro_set_len*4]
					mov ecx,[edx+4-macro_set_len*4*3]
					lea ebx,[ecx+ebx*2]
					mov ax,[ebx]
					movsx eax,ax
					mov [edx+4],eax
					mov [edx],ebx
					mov [edx+8],dword 2
					popad
				jmp _________macro_ops_get_end
				_________macro_ops_get_n2:
				cmp ebp,4
				jne _________macro_ops_get_n4
					pushad
					mov ebx,[edx+4-macro_set_len*4]
					mov ecx,[edx+4-macro_set_len*4*3]
					lea ebx,[ecx+ebx*4]
					mov eax,[ebx]
					mov [edx+4],eax
					mov [edx],ebx
					mov [edx+8],dword 4
					popad
				jmp _________macro_ops_get_end
				_________macro_ops_get_n4:
				_________macro_ops_get_end:
				sub edx,macro_set_len*4
				macro_set_memmove 3
				add edx,macro_set_len*4
			jmp _________macro_ops_end6
			_________macro_ops_not6_7:
			_________macro_ops_end6:
		cmp [edx],dword 2
		_________macro_ops_part6:
	add edx,macro_set_len*4
	jmp _________macro_ops_for_begin6
	_________macro_ops_for_end6:
	call2 ecx,ebx,macro_ops,eax,ebx,ecx	
	mov eax,ecx
end


