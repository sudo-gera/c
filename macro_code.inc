%ifndef macro_code
	%macro macro_eg 1
	%ifdef macro
		%ifndef macro_code
			extern %1
		%endif
	%else
		global %1
	%endif
	%endmacro
%endif

macro_eg macro_pr_jmp
macro_eg macro_bops
macro_eg macro_expr_hash_jmp
macro_eg macro_var_jmp
macro_eg macro_expr_jmp
macro_eg macro_set_jmp
macro_eg macro_regout
macro_eg macro_pre_start
macro_eg _macro_duput
macro_eg _macro_wuput
macro_eg _macro_buput
macro_eg _macro_dsput
macro_eg _macro_wsput
macro_eg _macro_bsput

macro_eg _macro_cput

macro_eg _macro_duprint
macro_eg _macro_wuprint
macro_eg _macro_buprint
macro_eg _macro_dsprint
macro_eg _macro_wsprint
macro_eg _macro_bsprint

macro_eg _macro_duwrite
macro_eg _macro_wuwrite
macro_eg _macro_buwrite
macro_eg _macro_dswrite
macro_eg _macro_wswrite
macro_eg _macro_bswrite

macro_eg _macro_cprint
macro_eg _macro_cwrite

macro_eg __best_duput
macro_eg __best_dsput
macro_eg __best_wuput
macro_eg __best_wsput
macro_eg __best_buput
macro_eg __best_bsput
macro_eg __best_cput
macro_eg __best_sput
macro_eg __best_duwrite
macro_eg __best_dswrite
macro_eg __best_wuwrite
macro_eg __best_wswrite
macro_eg __best_buwrite
macro_eg __best_bswrite
macro_eg __best_cwrite
macro_eg __best_swrite
macro_eg __best_duprint
macro_eg __best_dsprint
macro_eg __best_wuprint
macro_eg __best_wsprint
macro_eg __best_buprint
macro_eg __best_bsprint
macro_eg __best_cprint
macro_eg __best_sprint

%ifndef macro
	%define macro_code
	%include "macro.inc"
	; %define macro_set_log

	section .text
		macro_pr_jmp:
	%ifdef macro_set_log
		pushad
		mov ebp,[esp+32]
		cput 27
		sput "[31m"
		write ebp
		cput 27
		sput "[0m"
		dufor ebp,eax,edx,macro_set_len*4
			cput 27
			sput "[34m"
			write [ebp]
			cput 27
			sput "[0m"
			write [ebp+4]
			cput 27
			sput "[35m"
			write [ebp+8]
		end
		duif edx,<,ebx
			cput 27
			sput "[34m"
			write [ebp]
			cput 27
			sput "[33m"
			write [ebp+4]
			cput 27
			sput "[35m"
			write [ebp+8]
		end
		add edx,macro_set_len*4
		dufor ebp,edx,ebx,macro_set_len*4
			cput 27
			sput "[34m"
			write [ebp]
			cput 27
			sput "[32m"
			write [ebp+4]
			cput 27
			sput "[35m"
			write [ebp+8]
		end
		sub edx,macro_set_len*4
		cput 27
		sput "[0m"
		cput 10
		popad
	%endif
		add esp,8
		jmp [esp-4]


	def macro_ops
		mov edx,ebx
		_________macro_ops_for_begin8:
		cmp edx,eax
		jbe _________macro_ops_for_end8
		sub edx,macro_set_len*4
			macro_set_pr
			cmp [edx],dword 2
			jne _________macro_ops_part8
				mov ebp,[edx+4]
				cmp ebp,'*'
				jne _________macro_ops_not8_1
					mov ebp,edx
					sub ebp,macro_set_len*4
					cmp eax,ebp
					ja _________macro_ops_un8_1
					cmp [edx-macro_set_len*4],dword 2
					jne _________macro_ops_bin8_1
						_________macro_ops_un8_1:
						pushad
						mov eax,[edx+4+macro_set_len*4]
						mov ebx,[eax]
						mov [edx+4+macro_set_len*4],ebx
						mov [edx+macro_set_len*4],eax
						mov [edx+8+macro_set_len*4],dword 4
						popad
						macro_set_memmove 1
						add edx,macro_set_len*4
					_________macro_ops_bin8_1:
				jmp _________macro_ops_end8
				_________macro_ops_not8_1:
				cmp ebp,'-'
				jne _________macro_ops_not8_2
					mov ebp,edx
					sub ebp,macro_set_len*4
					cmp eax,ebp
					ja _________macro_ops_un8_2
					cmp [edx-macro_set_len*4],dword 2
					jne _________macro_ops_bin8_2
						_________macro_ops_un8_2:
						neg dword [edx+4+macro_set_len*4]
						macro_set_memmove 1
						add edx,macro_set_len*4
					_________macro_ops_bin8_2:
				jmp _________macro_ops_end8
				_________macro_ops_not8_2:
				cmp ebp,'+'
				jne _________macro_ops_not8_3
					mov ebp,edx
					sub ebp,macro_set_len*4
					cmp eax,ebp
					ja _________macro_ops_un8_3
					cmp [edx-macro_set_len*4],dword 2
					jne _________macro_ops_bin8_3
						_________macro_ops_un8_3:
						macro_set_memmove 1
						add edx,macro_set_len*4
					_________macro_ops_bin8_3:
				jmp _________macro_ops_end8
				_________macro_ops_not8_3:
				_________macro_ops_end8:
			_________macro_ops_part8:
		jmp _________macro_ops_for_begin8
		_________macro_ops_for_end8:

		mov edx,eax
		_________macro_ops_for_begin1:
		cmp edx,ebx
		jae _________macro_ops_for_end1
			macro_set_pr
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
			macro_set_pr
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
			macro_set_pr
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
			macro_set_pr
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
				cmp ebp,'&&'
				jne _________macro_ops_not4_2
					mov esi,[edx+4-macro_set_len*4]
					cmp esi,0
					je _________macro_ops_cmp_begin11
						mov esi,[edx+4+macro_set_len*4]
						cmp esi,0
						je _________macro_ops_cmp_begin12
							mov dword [edx+4+macro_set_len*4],1
						jmp _________macro_ops_cmp_end12
						_________macro_ops_cmp_begin12:
							mov dword [edx+4+macro_set_len*4],0
						_________macro_ops_cmp_end12:
					jmp _________macro_ops_cmp_end11
					_________macro_ops_cmp_begin11:
						mov dword [edx+4+macro_set_len*4],0
					_________macro_ops_cmp_end11:
					macro_set_memmove 2
				jmp _________macro_ops_end4
				_________macro_ops_not4_2:
				_________macro_ops_end4:
			_________macro_ops_part4:
		add edx,macro_set_len*4
		jmp _________macro_ops_for_begin4
		_________macro_ops_for_end4:

		mov edx,eax
		_________macro_ops_for_begin5:
		cmp edx,ebx
		jae _________macro_ops_for_end5
			macro_set_pr
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
				cmp ebp,'||'
				jne _________macro_ops_not5_2
					mov esi,[edx+4-macro_set_len*4]
					cmp esi,0
					je _________macro_ops_cmp_begin13
						mov dword [edx+4+macro_set_len*4],1
					jmp _________macro_ops_cmp_end13
					_________macro_ops_cmp_begin13:
						mov esi,[edx+4+macro_set_len*4]
						cmp esi,0
						je _________macro_ops_cmp_begin14
							mov dword [edx+4+macro_set_len*4],1
						jmp _________macro_ops_cmp_end13
						_________macro_ops_cmp_begin14:
							mov dword [edx+4+macro_set_len*4],0
						_________macro_ops_cmp_end14:
					_________macro_ops_cmp_end13:
					macro_set_memmove 2
				jmp _________macro_ops_end5
				_________macro_ops_not5_2:
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
			macro_set_pr
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
			macro_set_pr
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
						dmov [edx],[edx-macro_set_len*4]
						dmov [edx+4],[edx+4-macro_set_len*4]
						dmov [edx+8],[edx+8-macro_set_len*4]
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


	section .text
		macro_expr_hash_jmp:
		pushad
		add esp,32
		pop ebx
		pop eax
		sub esp,40

		mov ebp,eax
		mov edi,ebx
		mov ecx,ebx
		mov ebx,eax
		mov eax,0
		mov esi,75
		_________macro_expr_hash_1:
		mul esi
		mov edx,0
		mov dl,[ebx]
		sub dl,48
		add eax,edx
		inc ebx
		loop _________macro_expr_hash_1
		div dword [len_vars_names]
		lea eax,[vars_names+edx*4]
		mov ebx,[esp+40]
		mov [esp+40],eax
		mov [esp+36],ebx
		popad
		add esp,8
		jmp [esp-4]	

	section .text
		macro_var_jmp:
		pushad
		mov esi,[esp+32]
		mov edi,[esp+40]
		mov ebp,edi
		sub ebp,esi
		mov ecx,ebp
		mov ebx,esi
		macro_set_hash ebx,esi,ebp
		mov ecx,[esp+36]
		cmp [ebx],dword 0
		je _________macro_var_stay_calm
			swrite "warning:"
			pushad
			mov eax,4
			mov ebx,1
			mov ecx,esi
			mov edx,ebp
			int 0x80
			popad
			sprint " redefined"
		_________macro_var_stay_calm:
		mov [ebx],ecx
		popad
		add esp,12
		jmp [esp-4]


	section .text
		macro_expr_jmp:
		pushad
		add esp,32
		pop ebp
		pop edi
		sub esp,40
		push esp
		mov eax,0
		mov ebx,0
		mov ecx,0
		mov esi,0
		mov dh,-1
		mov ebx,ebp
		_________macro_expr_main_loop_begin:
		cmp ebx,edi
		jae _________macro_expr_main_loop_end
			mov cl,[ebx]
			mov ch,0
			cmp cl,'0'
			jb _________macro_expr_l0
				cmp cl,'9'
				ja _________macro_expr_g9
					mov ch,1
				_________macro_expr_g9:
			_________macro_expr_l0:
			cmp cl,'a'
			jb _________macro_expr_la
				cmp cl,'z'
				ja _________macro_expr_gz
					mov ch,2
				_________macro_expr_gz:
			_________macro_expr_la:
			cmp cl,'A'
			jb _________macro_expr_lA
				cmp cl,'Z'
				ja _________macro_expr_gZ
					mov ch,2
				_________macro_expr_gZ:
			_________macro_expr_lA:
			cmp cl,'_'
			jne _________macro_expr_nu
				mov ch,2
			_________macro_expr_nu:
			cmp cl,'@'
			jne _________macro_expr_na
				mov ch,2
			_________macro_expr_na:
			cmp cl,'.'
			jne _________macro_expr_nd
				mov ch,2
			_________macro_expr_nd:
			cmp cl,' '
			jne _________macro_expr_ns
				mov ch,3
			_________macro_expr_ns:
			cmp cl,9
			jne _________macro_expr_nt
				mov ch,3
			_________macro_expr_nt:
			cmp cl,','
			jne _________macro_expr_nc
				mov ch,4
			_________macro_expr_nc:
			cmp cl,'|'
			jne _________macro_expr_nv
				mov ch,5
			_________macro_expr_nv:
			cmp ch,dh
			je _________macro_expr_continuing
				cmp dh,0
				jne _________macro_expr_dh_n0
					pop dword eax
					push dword 2
					push dword esi
					push dword 0
					push dword eax
				jmp _________macro_expr_dh_end
				_________macro_expr_dh_n0:
				cmp dh,1
				jne _________macro_expr_dh_n1
					pop dword eax
					push dword 1
					push dword esi
					push dword 0
					push dword eax
				jmp _________macro_expr_dh_end
				_________macro_expr_dh_n1:
				cmp dh,2
				jne _________macro_expr_dh_n2
					sub ebx,esi
					macro_set_hash eax,esi,ebx
					cmp [eax],dword 0
					jne _________macro_expr_stay_calm
						swrite "warning:"
						pushad
						mov edx,ebx
						mov eax,4
						mov ebx,2
						mov ecx,esi
						int 0x80
						popad
						sprint " not found"
					_________macro_expr_stay_calm:
					add ebx,esi
					mov eax,[eax]
					mov esi,eax
					pop dword eax
					push dword 1
					push dword esi
					push dword 0
					push dword eax
				_________macro_expr_dh_n2:
				_________macro_expr_dh_end:
				cmp ch,0
				jne _________macro_expr_ch_n0
					movzx esi,cl
				jmp _________macro_expr_ch_end
				_________macro_expr_ch_n0:
				cmp ch,1
				jne _________macro_expr_ch_n1
					movzx esi,cl
					sub esi,'0'
				jmp _________macro_expr_ch_end
				_________macro_expr_ch_n1:
				cmp ch,2
				jne _________macro_expr_ch_n2
					mov esi,ebx
				jmp _________macro_expr_ch_end
				_________macro_expr_ch_n2:
				cmp ch,4
				jne _________macro_expr_ch_n4
					pop dword eax
					push dword 1
					push dword 0
					push dword 0
					push dword 2
					push dword '+'
					push dword 0
					push dword eax
				jmp _________macro_expr_ch_end
				_________macro_expr_ch_n4:
				cmp ch,5
				jne _________macro_expr_ch_n5
					pop dword eax
					push dword 2
					push dword ')'
					push dword 0
					push dword 1
					push dword 0
					push dword 0
					push dword 2
					push dword '+'
					push dword 0
					push dword 2
					push dword '('
					push dword 0
					push dword eax
				_________macro_expr_ch_end:
				_________macro_expr_ch_n5:
			jmp _________macro_expr_contend
			_________macro_expr_continuing:
				cmp ch,0
				jne _________macro_expr_same_n0
					cmp esi,256
					jae _________macro_expr_oper_ge256
						mov eax,0
						mov al,cl
						push edx
						mov edx,256
						mul edx
						pop edx
						add esi,eax
						push edx
						push ebx
						push ebp
						mov edx,0
						mov ebx,0
						_________macro_expr_oper_1_for_begin:
						cmp ebx,[len_operators]
						jae _________macro_expr_oper_1_for_end
							lea ebp,[operators+ebx*4]
							mov ebp,[ebp]
							cmp ebp,esi
							jne _________macro_expr_oper_1_nc
								mov edx,1
							_________macro_expr_oper_1_nc:
						inc ebx
						jmp _________macro_expr_oper_1_for_begin
						_________macro_expr_oper_1_for_end:
						cmp edx,0
						jne _________macro_expr_oper_1_f
							sub esi,eax
							pop ebp
							pop ebx
							pop edx
							pop dword eax
							push dword 2
							push dword esi
							push dword 0
							push dword eax
							push edx
							push ebx
							push ebp
							mov esi,0
							mov eax,0
							mov al,cl
							mov esi,eax
						_________macro_expr_oper_1_f:
						pop ebp
						pop ebx
						pop edx
					jmp _________macro_expr_oper_end
					_________macro_expr_oper_ge256:
					cmp esi,256*256
					jae _________macro_expr_oper_ge256_256
						mov eax,0
						mov al,cl
						push edx
						mov edx,256*256
						mul edx
						pop edx
						add esi,eax
						push edx
						push ebx
						push ebp
						mov edx,0
						mov ebx,0
						_________macro_expr_oper_2_for_begin:
						cmp ebx,[len_operators]
						jae _________macro_expr_oper_2_for_end
							lea ebp,[operators+ebx*4]
							mov ebp,[ebp]
							cmp ebp,esi
							jne _________macro_expr_oper_2_nc
								mov edx,1
							_________macro_expr_oper_2_nc:
						inc ebx
						jmp _________macro_expr_oper_2_for_begin
						_________macro_expr_oper_2_for_end:
						cmp edx,0
						jne _________macro_expr_oper_2_f
							sub esi,eax
							pop ebp
							pop ebx
							pop edx
							pop dword eax
							push dword 2
							push dword esi
							push dword 0
							push dword eax
							push edx
							push ebx
							push ebp
							mov esi,0
							mov eax,0
							mov al,cl
							mov esi,eax
						_________macro_expr_oper_2_f:
						pop ebp
						pop ebx
						pop edx
					jmp _________macro_expr_oper_end
					_________macro_expr_oper_ge256_256:
					cmp esi,256*256*256
					jae _________macro_expr_oper_ge256_256_256
						mov eax,0
						mov al,cl
						push edx
						mov edx,256*256*256
						mul edx
						pop edx
						add esi,eax
						push edx
						push ebx
						push ebp
						mov edx,0
						mov ebx,0
						_________macro_expr_oper_3_for_begin:
						cmp ebx,[len_operators]
						jae _________macro_expr_oper_3_for_end
							lea ebp,[operators+ebx*4]
							mov ebp,[ebp]
							cmp ebp,esi
							jne _________macro_expr_oper_3_nc
								mov edx,1
							_________macro_expr_oper_3_nc:
						inc ebx
						jmp _________macro_expr_oper_3_for_begin
						_________macro_expr_oper_3_for_end:
						cmp edx,0
						jne _________macro_expr_oper_3_f
							sub esi,eax
							pop ebp
							pop ebx
							pop edx
							pop dword eax
							push dword 2
							push dword esi
							push dword 0
							push dword eax
							push edx
							push ebx
							push ebp
							mov esi,0
							mov eax,0
							mov al,cl
							mov esi,eax
						_________macro_expr_oper_3_f:
						pop ebp
						pop ebx
						pop edx
					_________macro_expr_oper_end:
					_________macro_expr_oper_ge256_256_256:
				jmp _________macro_expr_same_end
				_________macro_expr_same_n0:
				cmp ch,1
				jne _________macro_expr_same_n1
					mov eax,0
					mov al,cl
					sub eax,'0'
					push eax
					push edx
					mov eax,esi
					mov edx,10
					mul edx
					mov esi,eax
					pop edx
					pop eax
					add esi,eax
				_________macro_expr_same_end:
				_________macro_expr_same_n1:
			_________macro_expr_contend:
			mov dh,ch
		inc ebx
		jmp _________macro_expr_main_loop_begin
		_________macro_expr_main_loop_end:
		pop ebx
		mov eax,esp
		mov edx,eax

		mov esi,eax
		mov edi,ebx

		_________macro_expr_swap_begin:
		cmp eax,ebx
		jae _________macro_expr_swap_end
			mov ecx,[eax]
			mov ebp,[ebx-4]
			mov [eax],ebp
			mov [ebx-4],ecx
			add eax,4
			sub ebx,4
		jmp _________macro_expr_swap_begin
		_________macro_expr_swap_end:

		mov eax,esi
		mov ebx,edi

		macro_set_pr
		call0 macro_bops,eax,ebx,ebx

		mov esp,ebx
		popad
		add esp,8
		jmp dword [esp-4]

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

	section .text
		macro_regout:


		sput "eax == "
		cput 27
		sput "[32m"
		dsput eax
		cput 27
		sput "[0m"

		cput 9

		sput "ebx == "
		cput 27
		sput "[32m"
		dsput ebx
		cput 27
		sput "[0m"

		cput 9

		sput "ecx == "
		cput 27
		sput "[32m"
		dsput ecx
		cput 27
		sput "[0m"

		cput 9

		sput "edx == "
		cput 27
		sput "[32m"
		dsput edx
		cput 27
		sput "[0m"

		cput 9

		sput " esi == "
		cput 27
		sput "[32m"
		dsput esi
		cput 27
		sput "[0m"

		cput 9

		sput " edi == "
		cput 27
		sput "[32m"
		dsput edi
		cput 27
		sput "[0m"

		cput 9

		sput " ebp == "
		cput 27
		sput "[32m"
		dsput ebp
		cput 27
		sput "[0m"

		cput 9

		sput " esp == "
		cput 27
		sput "[32m"

		sub [esp],esp
		neg dword [esp]
		xchg eax,[esp]
		add eax,12
		dsput eax
		sub eax,12
		xchg eax,[esp]
		neg dword [esp]
		add [esp],esp

		cput 27
		sput "[0m"

		cput 9

		sput " line = "
		cput 27
		sput "[32m"

		xchg eax,[esp+4]
		dsput eax
		xchg eax,[esp+4]
		cput 27
		sput "[0m"

		cput 10

		add esp,12
		jmp [esp-4]

	section .text
		macro_pre_start:
		ret


section .text

	__best_duput_one:
		pushfd
		pushad

		mov edx,0
		mov ecx,0
		mov esi,0
		mov ebp,0

		mov ebx,10
		mov edi,eax

		__best_duput_one_1:
		inc ecx
		div ebx
		mov edx,0
		cmp eax,0
		jne __best_duput_one_1

		mov esi,ecx
		mov edx,0
		mov eax,1

		__best_duput_one_2:
		push eax
		mul ebx
		loop __best_duput_one_2

		mov ecx,esi
		mov eax,edi

		__best_duput_one_3:
		pop ebx
		mov edx,0
		div ebx
		add eax,48
		cput al
		mov eax,edx
		loop __best_duput_one_3

		popad
		popfd
		ret

	__best_dsput_one:
		cmp eax,0
		jge __best_dsput_one_1		
			cput '-'
			neg eax
		__best_dsput_one_1:
		call __best_duput_one
		ret

	__best_wuput_one:
		movzx eax,ax
		call __best_duput_one
		ret

	__best_wsput_one:
		movsx eax,ax
		call __best_dsput_one
		ret

	__best_buput_one:
		__best_byte_get
		call __best_duput_one
		__best_byte_set
		ret

	__best_bsput_one:
		__best_byte_get
		movsx eax,al
		call __best_dsput_one
		__best_byte_set
		ret

	__best_cput_one:
		__best_byte_get
		pushfd
		pushad
		push eax
		mov eax,4
		mov ebx,1
		mov ecx,esp
		mov edx,1
		int 0x80
		add esp,4
		popad
		popfd
		__best_byte_set
		ret

	__best_sput_one:
		cput al
		ret



	__best_duput:   __best_multiple 4,__best_duput_one,nop,nop,32,0
	__best_dsput:   __best_multiple 4,__best_dsput_one,nop,nop,32,0
	__best_wuput:   __best_multiple 2,__best_wuput_one,nop,nop,32,0
	__best_wsput:   __best_multiple 2,__best_wsput_one,nop,nop,32,0
	__best_buput:   __best_multiple 2,__best_buput_one,__best_alr,nop,32,0
	__best_bsput:   __best_multiple 2,__best_bsput_one,__best_alr,nop,32,0
	__best_cput:    __best_multiple 2, __best_cput_one,__best_alr,nop,32,0
	__best_sput:    __best_multiple 1, __best_sput_one,nop,__best_strp,0,0
	__best_duwrite: __best_multiple 4,__best_duput_one,nop,nop,32,32
	__best_dswrite: __best_multiple 4,__best_dsput_one,nop,nop,32,32
	__best_wuwrite: __best_multiple 2,__best_wuput_one,nop,nop,32,32
	__best_wswrite: __best_multiple 2,__best_wsput_one,nop,nop,32,32
	__best_buwrite: __best_multiple 2,__best_buput_one,__best_alr,nop,32,32
	__best_bswrite: __best_multiple 2,__best_bsput_one,__best_alr,nop,32,32
	__best_cwrite:  __best_multiple 2, __best_cput_one,__best_alr,nop,32,32
	__best_swrite:  __best_multiple 1, __best_sput_one,nop,__best_strp,0,32
	__best_duprint: __best_multiple 4,__best_duput_one,nop,nop,32,10
	__best_dsprint: __best_multiple 4,__best_dsput_one,nop,nop,32,10
	__best_wuprint: __best_multiple 2,__best_wuput_one,nop,nop,32,10
	__best_wsprint: __best_multiple 2,__best_wsput_one,nop,nop,32,10
	__best_buprint: __best_multiple 2,__best_buput_one,__best_alr,nop,32,10
	__best_bsprint: __best_multiple 2,__best_bsput_one,__best_alr,nop,32,10
	__best_cprint:  __best_multiple 2, __best_cput_one,__best_alr,nop,32,10
	__best_sprint:  __best_multiple 1, __best_sput_one,nop,__best_strp,0,10



%endif
