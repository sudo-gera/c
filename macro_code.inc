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

macro_eg __best_quput
macro_eg __best_qsput
macro_eg __best_duput
macro_eg __best_dsput
macro_eg __best_wuput
macro_eg __best_wsput
macro_eg __best_buput
macro_eg __best_bsput
macro_eg __best_cput
macro_eg __best_sput
macro_eg __best_quwrite
macro_eg __best_qswrite
macro_eg __best_duwrite
macro_eg __best_dswrite
macro_eg __best_wuwrite
macro_eg __best_wswrite
macro_eg __best_buwrite
macro_eg __best_bswrite
macro_eg __best_cwrite
macro_eg __best_swrite
macro_eg __best_quprint
macro_eg __best_qsprint
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
		mov _bp,[_sp+rsize*8]
		cput 27
		sput "[31m"
		_swrite _bp
		cput 27
		sput "[0m"
		_ufor _bp,_ax,_dx,macro_set_len*rsize
			cput 27
			sput "[34m"
			write [_bp]
			cput 27
			sput "[0m"
			write [_bp+rsize]
			cput 27
			sput "[35m"
			write [_bp+rsize*2]
		end
		_uif _dx,<,_bx
			cput 27
			sput "[34m"
			write [_bp]
			cput 27
			sput "[33m"
			write [_bp+rsize]
			cput 27
			sput "[35m"
			write [_bp+rsize*2]
		end
		add _dx,macro_set_len*rsize
		_ufor _bp,_dx,_bx,macro_set_len*rsize
			cput 27
			sput "[34m"
			write [_bp]
			cput 27
			sput "[32m"
			write [_bp+rsize]
			cput 27
			sput "[35m"
			write [_bp+rsize*2]
		end
		sub _dx,macro_set_len*rsize
		cput 27
		sput "[0m"
		cput 10
		popad
	%endif
		add _sp,rsize*2
		jmp [_sp-rsize]


	def macro_ops
		mov _dx,_bx
		_________macro_ops_for_begin8:
		cmp _dx,_ax
		jbe _________macro_ops_for_end8
		sub _dx,macro_set_len*rsize
			macro_set_pr
			cmp _word [_dx],_word 2
			jne _________macro_ops_part8
				mov _bp,[_dx+rsize]
				cmp _bp,'*'
				jne _________macro_ops_not8_1
					mov _bp,_dx
					sub _bp,macro_set_len*rsize
					cmp _ax,_bp
					ja _________macro_ops_un8_1
					cmp _word [_dx-macro_set_len*rsize],_word 2
					jne _________macro_ops_bin8_1
						_________macro_ops_un8_1:
						pushad
						mov _ax,[_dx+rsize+macro_set_len*rsize]
						mov _bx,[_ax]
						mov _word[_dx+rsize+macro_set_len*rsize],_bx
						mov _word[_dx+macro_set_len*rsize],_ax
						mov _word [_dx+rsize*2+macro_set_len*rsize],_word rsize
						popad
						macro_set_memmove 1
						add _dx,macro_set_len*rsize
					_________macro_ops_bin8_1:
				jmp _________macro_ops_end8
				_________macro_ops_not8_1:
				cmp _bp,'-'
				jne _________macro_ops_not8_2
					mov _bp,_dx
					sub _bp,macro_set_len*rsize
					cmp _ax,_bp
					ja _________macro_ops_un8_2
					cmp _word [_dx-macro_set_len*rsize],_word 2
					jne _________macro_ops_bin8_2
						_________macro_ops_un8_2:
						neg _word [_dx+rsize+macro_set_len*rsize]
						macro_set_memmove 1
						add _dx,macro_set_len*rsize
					_________macro_ops_bin8_2:
				jmp _________macro_ops_end8
				_________macro_ops_not8_2:
				cmp _bp,'+'
				jne _________macro_ops_not8_3
					mov _bp,_dx
					sub _bp,macro_set_len*rsize
					cmp _ax,_bp
					ja _________macro_ops_un8_3
					cmp _word [_dx-macro_set_len*rsize],_word 2
					jne _________macro_ops_bin8_3
						_________macro_ops_un8_3:
						macro_set_memmove 1
						add _dx,macro_set_len*rsize
					_________macro_ops_bin8_3:
				jmp _________macro_ops_end8
				_________macro_ops_not8_3:
				_________macro_ops_end8:
			_________macro_ops_part8:
		jmp _________macro_ops_for_begin8
		_________macro_ops_for_end8:

		mov _dx,_ax
		_________macro_ops_for_begin1:
		cmp _dx,_bx
		jae _________macro_ops_for_end1
			macro_set_pr
			cmp _word [_dx],_word 2
			jne _________macro_ops_part1
				mov _bp,[_dx+rsize]
				cmp _bp,'*'
				jne _________macro_ops_not1_1
					pushad
					mov _ax,[_dx+rsize+macro_set_len*rsize]
					mov _bx,[_dx+rsize-macro_set_len*rsize]
					mov _cx,_dx
					mul _bx
					mov _word[_cx+rsize+macro_set_len*rsize],_ax
					popad
					macro_set_memmove 2
				jmp _________macro_ops_end1
				_________macro_ops_not1_1:
				cmp _bp,'/'
				jne _________macro_ops_not1_2
					_sdiv [_dx+rsize+macro_set_len*rsize],[_dx+rsize-macro_set_len*rsize],[_dx+rsize+macro_set_len*rsize]
					macro_set_memmove 2
				jmp _________macro_ops_end1
				_________macro_ops_not1_2:
				cmp _bp,'%'
				jne _________macro_ops_not1_3
					_smod [_dx+rsize+macro_set_len*rsize],[_dx+rsize-macro_set_len*rsize],[_dx+rsize+macro_set_len*rsize]
					macro_set_memmove 2
				jmp _________macro_ops_end1
				_________macro_ops_not1_3:
				_________macro_ops_end1:
			_________macro_ops_part1:
		add _dx,macro_set_len*rsize
		jmp _________macro_ops_for_begin1
		_________macro_ops_for_end1:

		mov _dx,_ax
		_________macro_ops_for_begin2:
		cmp _dx,_bx
		jae _________macro_ops_for_end2
			macro_set_pr
			cmp _word [_dx],_word 2
			jne _________macro_ops_part2
				mov _bp,[_dx+rsize]
				cmp _bp,'+'
				jne _________macro_ops_not2_1
					pushad
					mov _ax,[_dx+rsize-macro_set_len*rsize]
					add _ax,[_dx+rsize+macro_set_len*rsize]
					mov _word[_dx+rsize+macro_set_len*rsize],_ax
					popad
					macro_set_memmove 2
				jmp _________macro_ops_end2
				_________macro_ops_not2_1:
				cmp _bp,'-'
				jne _________macro_ops_not2_2
					pushad
					mov _ax,[_dx+rsize-macro_set_len*rsize]
					sub _ax,[_dx+rsize+macro_set_len*rsize]
					mov _word[_dx+rsize+macro_set_len*rsize],_ax
					popad
					macro_set_memmove 2
				jmp _________macro_ops_end2
				_________macro_ops_not2_2:
				_________macro_ops_end2:
			_________macro_ops_part2:
		add _dx,macro_set_len*rsize
		jmp _________macro_ops_for_begin2
		_________macro_ops_for_end2:

		mov _dx,_ax
		_________macro_ops_for_begin3:
		cmp _dx,_bx
		jae _________macro_ops_for_end3
			macro_set_pr
			cmp _word [_dx],_word 2
			jne _________macro_ops_part3
				mov _bp,[_dx+rsize]
				cmp _bp,'<'
				jne _________macro_ops_not3_1
					mov _si,[_dx+rsize-macro_set_len*rsize]
					cmp _si,[_dx+rsize+macro_set_len*rsize]
					jge _________macro_ops_cmp_begin1
						mov _word [_dx+rsize+macro_set_len*rsize],1
					jmp _________macro_ops_cmp_end1
					_________macro_ops_cmp_begin1:
						mov _word [_dx+rsize+macro_set_len*rsize],0
					_________macro_ops_cmp_end1:
					macro_set_memmove 2
				jmp _________macro_ops_end3
				_________macro_ops_not3_1:
				cmp _bp,'>'
				jne _________macro_ops_not3_2
					mov _si,[_dx+rsize-macro_set_len*rsize]
					cmp _si,[_dx+rsize+macro_set_len*rsize]
					jle _________macro_ops_cmp_begin2
						mov _word [_dx+rsize+macro_set_len*rsize],1
					jmp _________macro_ops_cmp_end2
					_________macro_ops_cmp_begin2:
						mov _word [_dx+rsize+macro_set_len*rsize],0
					_________macro_ops_cmp_end2:
					macro_set_memmove 2
				jmp _________macro_ops_end3
				_________macro_ops_not3_2:
				cmp _bp,'>='
				jne _________macro_ops_not3_3
					mov _si,[_dx+rsize-macro_set_len*rsize]
					cmp _si,[_dx+rsize+macro_set_len*rsize]
					jl _________macro_ops_cmp_begin3
						mov _word [_dx+rsize+macro_set_len*rsize],1
					jmp _________macro_ops_cmp_end3
					_________macro_ops_cmp_begin3:
						mov _word [_dx+rsize+macro_set_len*rsize],0
					_________macro_ops_cmp_end3:
					macro_set_memmove 2
				jmp _________macro_ops_end3
				_________macro_ops_not3_3:
				cmp _bp,'<='
				jne _________macro_ops_not3_4
					mov _si,[_dx+rsize-macro_set_len*rsize]
					cmp _si,[_dx+rsize+macro_set_len*rsize]
					jg _________macro_ops_cmp_begin4
						mov _word [_dx+rsize+macro_set_len*rsize],1
					jmp _________macro_ops_cmp_end4
					_________macro_ops_cmp_begin4:
						mov _word [_dx+rsize+macro_set_len*rsize],0
					_________macro_ops_cmp_end4:
					macro_set_memmove 2
				jmp _________macro_ops_end3
				_________macro_ops_not3_4:
				cmp _bp,'=='
				jne _________macro_ops_not3_5
					mov _si,[_dx+rsize-macro_set_len*rsize]
					cmp _si,[_dx+rsize+macro_set_len*rsize]
					jne _________macro_ops_cmp_begin5
						mov _word [_dx+rsize+macro_set_len*rsize],1
					jmp _________macro_ops_cmp_end5
					_________macro_ops_cmp_begin5:
						mov _word [_dx+rsize+macro_set_len*rsize],0
					_________macro_ops_cmp_end5:
					macro_set_memmove 2
				jmp _________macro_ops_end3
				_________macro_ops_not3_5:
				cmp _bp,'!='
				jne _________macro_ops_not3_6
					mov _si,[_dx+rsize-macro_set_len*rsize]
					cmp _si,[_dx+rsize+macro_set_len*rsize]
					je _________macro_ops_cmp_begin6
						mov _word [_dx+rsize+macro_set_len*rsize],1
					jmp _________macro_ops_cmp_end6
					_________macro_ops_cmp_begin6:
						mov _word [_dx+rsize+macro_set_len*rsize],0
					_________macro_ops_cmp_end6:
					macro_set_memmove 2
				jmp _________macro_ops_end3
				_________macro_ops_not3_6:
				_________macro_ops_end3:
			_________macro_ops_part3:
		add _dx,macro_set_len*rsize
		jmp _________macro_ops_for_begin3
		_________macro_ops_for_end3:

		mov _dx,_ax
		_________macro_ops_for_begin4:
		cmp _dx,_bx
		jae _________macro_ops_for_end4
			macro_set_pr
			cmp _word[_dx],_word 2
			jne _________macro_ops_part4
				mov _bp,[_dx+rsize]
				cmp _bp,'and'
				jne _________macro_ops_not4_1
					mov _si,[_dx+rsize-macro_set_len*rsize]
					cmp _si,0
					je _________macro_ops_cmp_begin7
						mov _si,[_dx+rsize+macro_set_len*rsize]
						cmp _si,0
						je _________macro_ops_cmp_begin8
							mov _word [_dx+rsize+macro_set_len*rsize],1
						jmp _________macro_ops_cmp_end8
						_________macro_ops_cmp_begin8:
							mov _word [_dx+rsize+macro_set_len*rsize],0
						_________macro_ops_cmp_end8:
					jmp _________macro_ops_cmp_end7
					_________macro_ops_cmp_begin7:
						mov _word [_dx+rsize+macro_set_len*rsize],0
					_________macro_ops_cmp_end7:
					macro_set_memmove 2
				jmp _________macro_ops_end4
				_________macro_ops_not4_1:
				cmp _bp,'&&'
				jne _________macro_ops_not4_2
					mov _si,[_dx+rsize-macro_set_len*rsize]
					cmp _si,0
					je _________macro_ops_cmp_begin11
						mov _si,[_dx+rsize+macro_set_len*rsize]
						cmp _si,0
						je _________macro_ops_cmp_begin12
							mov _word [_dx+rsize+macro_set_len*rsize],1
						jmp _________macro_ops_cmp_end12
						_________macro_ops_cmp_begin12:
							mov _word [_dx+rsize+macro_set_len*rsize],0
						_________macro_ops_cmp_end12:
					jmp _________macro_ops_cmp_end11
					_________macro_ops_cmp_begin11:
						mov _word [_dx+rsize+macro_set_len*rsize],0
					_________macro_ops_cmp_end11:
					macro_set_memmove 2
				jmp _________macro_ops_end4
				_________macro_ops_not4_2:
				_________macro_ops_end4:
			_________macro_ops_part4:
		add _dx,macro_set_len*rsize
		jmp _________macro_ops_for_begin4
		_________macro_ops_for_end4:

		mov _dx,_ax
		_________macro_ops_for_begin5:
		cmp _dx,_bx
		jae _________macro_ops_for_end5
			macro_set_pr
			cmp _word [_dx],_word 2
			jne _________macro_ops_part5
				mov _bp,[_dx+rsize]
				cmp _bp,'or'
				jne _________macro_ops_not5_1
					mov _si,[_dx+rsize-macro_set_len*rsize]
					cmp _si,0
					je _________macro_ops_cmp_begin9
						mov _word [_dx+rsize+macro_set_len*rsize],1
					jmp _________macro_ops_cmp_end9
					_________macro_ops_cmp_begin9:
						mov _si,[_dx+rsize+macro_set_len*rsize]
						cmp _si,0
						je _________macro_ops_cmp_begin10
							mov _word [_dx+rsize+macro_set_len*rsize],1
						jmp _________macro_ops_cmp_end10
						_________macro_ops_cmp_begin10:
							mov _word [_dx+rsize+macro_set_len*rsize],0
						_________macro_ops_cmp_end10:
					_________macro_ops_cmp_end9:
					macro_set_memmove 2
				jmp _________macro_ops_end5
				_________macro_ops_not5_1:
				cmp _bp,'||'
				jne _________macro_ops_not5_2
					mov _si,[_dx+rsize-macro_set_len*rsize]
					cmp _si,0
					je _________macro_ops_cmp_begin13
						mov _word [_dx+rsize+macro_set_len*rsize],1
					jmp _________macro_ops_cmp_end13
					_________macro_ops_cmp_begin13:
						mov _si,[_dx+rsize+macro_set_len*rsize]
						cmp _si,0
						je _________macro_ops_cmp_begin14
							mov _word [_dx+rsize+macro_set_len*rsize],1
						jmp _________macro_ops_cmp_end13
						_________macro_ops_cmp_begin14:
							mov _word [_dx+rsize+macro_set_len*rsize],0
						_________macro_ops_cmp_end14:
					_________macro_ops_cmp_end13:
					macro_set_memmove 2
				jmp _________macro_ops_end5
				_________macro_ops_not5_2:
				_________macro_ops_end5:
			_________macro_ops_part5:
		add _dx,macro_set_len*rsize
		jmp _________macro_ops_for_begin5
		_________macro_ops_for_end5:


		mov _dx,_bx
		_________macro_ops_for_begin7:
		cmp _dx,_ax
		jbe _________macro_ops_for_end7
		sub _dx,macro_set_len*rsize
			macro_set_pr
			cmp _word[_dx],_word 2
			jne _________macro_ops_part7
				mov _bp,[_dx+rsize]
				cmp _bp,'='
				jne _________macro_ops_not7_1
					pushad
					mov _ax,[_dx+rsize+macro_set_len*rsize]
					mov _bx,[_dx-macro_set_len*rsize]
					mov _word[_dx+macro_set_len*rsize],_bx
					mov _si,[_dx+rsize*2-macro_set_len*rsize]
					mov _word[_dx+rsize*2+macro_set_len*rsize],_si
				%if __BITS__==64
					cmp _si,8
					jne _________macro_ops_assign7_1_n8
						mov [_bx],rax
					_________macro_ops_assign7_1_n8:
				%endif
					cmp _si,4
					jne _________macro_ops_assign7_1_n4
						mov [_bx],eax
					_________macro_ops_assign7_1_n4:
					cmp _si,2
					jne _________macro_ops_assign7_1_n2
						mov [_bx],ax
					_________macro_ops_assign7_1_n2:
					cmp _si,1
					jne _________macro_ops_assign7_1_n1
						mov [_bx],al
					_________macro_ops_assign7_1_n1:
					popad
					macro_set_memmove 2
					add _dx,macro_set_len*rsize*2
				jmp _________macro_ops_end7
				_________macro_ops_not7_1:
				cmp _bp,'+='
				jne _________macro_ops_not7_2
					pushad
					mov _ax,[_dx+rsize-macro_set_len*rsize]
					add _ax,[_dx+rsize+macro_set_len*rsize]
					mov _word[_dx+rsize+macro_set_len*rsize],_ax
					mov _bx,[_dx-macro_set_len*rsize]
					mov _word[_dx+macro_set_len*rsize],_bx
					mov _si,[_dx+rsize*2-macro_set_len*rsize]
					mov _word[_dx+rsize*2+macro_set_len*rsize],_si
				%if __BITS__==64
					cmp _si,8
					jne _________macro_ops_assign7_2_n8
						mov [_bx],rax
					_________macro_ops_assign7_2_n8:
				%endif
					cmp _si,4
					jne _________macro_ops_assign7_2_n4
						mov [_bx],eax
					_________macro_ops_assign7_2_n4:
					cmp _si,2
					jne _________macro_ops_assign7_2_n2
						mov [_bx],ax
					_________macro_ops_assign7_2_n2:
					cmp _si,1
					jne _________macro_ops_assign7_2_n1
						mov [_bx],al
					_________macro_ops_assign7_2_n1:
					popad
					macro_set_memmove 2
					add _dx,macro_set_len*rsize*2
				jmp _________macro_ops_end7
				_________macro_ops_not7_2:
				cmp _bp,'-='
				jne _________macro_ops_not7_3
					pushad
					mov _ax,[_dx+rsize-macro_set_len*rsize]
					sub _ax,[_dx+rsize+macro_set_len*rsize]
					mov _word[_dx+rsize+macro_set_len*rsize],_ax
					mov _bx,[_dx-macro_set_len*rsize]
					mov _word[_dx+macro_set_len*rsize],_bx
					mov _si,[_dx+rsize*2-macro_set_len*rsize]
					mov _word[_dx+rsize*2+macro_set_len*rsize],_si
				%if __BITS__==64
					cmp _si,8
					jne _________macro_ops_assign7_3_n8
						mov [_bx],rax
					_________macro_ops_assign7_3_n8:
				%endif
					cmp _si,4
					jne _________macro_ops_assign7_3_n4
						mov [_bx],eax
					_________macro_ops_assign7_3_n4:
					cmp _si,2
					jne _________macro_ops_assign7_3_n2
						mov [_bx],ax
					_________macro_ops_assign7_3_n2:
					cmp _si,1
					jne _________macro_ops_assign7_3_n1
						mov [_bx],al
					_________macro_ops_assign7_3_n1:
					popad
					macro_set_memmove 2
					add _dx,macro_set_len*rsize*2
				jmp _________macro_ops_end7
				_________macro_ops_not7_3:
				cmp _bp,'*='
				jne _________macro_ops_not7_4
					pushad
					mov _cx,_dx
					mov _ax,[_cx+rsize-macro_set_len*rsize]
					mov _bx,[_cx+rsize+macro_set_len*rsize]
					mul _bx
					mov _dx,_cx
					mov _word[_cx+rsize+macro_set_len*rsize],_ax
					mov _bx,[_dx-macro_set_len*rsize]
					mov _word[_dx+macro_set_len*rsize],_bx
					mov _si,[_dx+rsize*2-macro_set_len*rsize]
					mov _word[_dx+rsize*2+macro_set_len*rsize],_si
				%if __BITS__==64
					cmp _si,8
					jne _________macro_ops_assign7_4_n8
						mov [_bx],rax
					_________macro_ops_assign7_4_n8:
				%endif
					cmp _si,4
					jne _________macro_ops_assign7_4_n4
						mov [_bx],eax
					_________macro_ops_assign7_4_n4:
					cmp _si,2
					jne _________macro_ops_assign7_4_n2
						mov [_bx],ax
					_________macro_ops_assign7_4_n2:
					cmp _si,1
					jne _________macro_ops_assign7_4_n1
						mov [_bx],al
					_________macro_ops_assign7_4_n1:
					popad
					macro_set_memmove 2
					add _dx,macro_set_len*rsize*2
				jmp _________macro_ops_end7
				_________macro_ops_not7_4:
				cmp _bp,'/='
				jne _________macro_ops_not7_5
					pushad
					mov _cx,_dx
					mov _ax,[_cx+rsize-macro_set_len*rsize]
					mov _bx,[_cx+rsize+macro_set_len*rsize]
					c__
					idiv _bx
					mov _dx,_cx
					mov _word[_cx+rsize+macro_set_len*rsize],_ax
					mov _bx,[_dx-macro_set_len*rsize]
					mov _word[_dx+macro_set_len*rsize],_bx
					mov _si,[_dx+rsize*2-macro_set_len*rsize]
					mov _word[_dx+rsize*2+macro_set_len*rsize],_si
				%if __BITS__==64
					cmp _si,8
					jne _________macro_ops_assign7_5_n8
						mov [_bx],rax
					_________macro_ops_assign7_5_n8:
				%endif
					cmp _si,4
					jne _________macro_ops_assign7_5_n4
						mov [_bx],eax
					_________macro_ops_assign7_5_n4:
					cmp _si,2
					jne _________macro_ops_assign7_5_n2
						mov [_bx],ax
					_________macro_ops_assign7_5_n2:
					cmp _si,1
					jne _________macro_ops_assign7_5_n1
						mov [_bx],al
					_________macro_ops_assign7_5_n1:
					popad
					macro_set_memmove 2
					add _dx,macro_set_len*rsize*2
				jmp _________macro_ops_end7
				_________macro_ops_not7_5:
				cmp _bp,'%='
				jne _________macro_ops_not7_6
					pushad
					mov _cx,_dx
					mov _ax,[_cx+rsize-macro_set_len*rsize]
					mov _bx,[_cx+rsize+macro_set_len*rsize]
					c__
					idiv _bx
					mov _ax,_dx
					mov _dx,_cx
					mov _word[_cx+rsize+macro_set_len*rsize],_ax
					mov _bx,[_dx-macro_set_len*rsize]
					mov _word[_dx+macro_set_len*rsize],_bx
					mov _si,[_dx+rsize*2-macro_set_len*rsize]
					mov _word[_dx+rsize*2+macro_set_len*rsize],_si
				%if __BITS__==64
					cmp _si,8
					jne _________macro_ops_assign7_6_n8
						mov [_bx],rax
					_________macro_ops_assign7_6_n8:
				%endif
					cmp _si,4
					jne _________macro_ops_assign7_6_n4
						mov [_bx],eax
					_________macro_ops_assign7_6_n4:
					cmp _si,2
					jne _________macro_ops_assign7_6_n2
						mov [_bx],ax
					_________macro_ops_assign7_6_n2:
					cmp _si,1
					jne _________macro_ops_assign7_6_n1
						mov [_bx],al
					_________macro_ops_assign7_6_n1:
					popad
					macro_set_memmove 2
					add _dx,macro_set_len*rsize*2
				jmp _________macro_ops_end7
				_________macro_ops_not7_6:
				_________macro_ops_end7:
			_________macro_ops_part7:
		jmp _________macro_ops_for_begin7
		_________macro_ops_for_end7:

		mov _ax,_cx
	end

	def macro_bops
		mov _dx,_ax
		_________macro_ops_for_begin6:
		cmp _dx,_bx
		jae _________macro_ops_for_end6
			macro_set_pr
			cmp _word[_dx],_word 2
			jne _________macro_ops_part6
				mov _bp,[_dx+rsize]
				cmp _bp,'('
				jne _________macro_ops_not6_1
					add _dx,macro_set_len*rsize
					push _dx
					push _word 0
					sub _dx,macro_set_len*rsize
				jmp _________macro_ops_end6
				_________macro_ops_not6_1:
				cmp _bp,')'
				jne _________macro_ops_not6_2
					mov _di,_dx
					pop _bp
					pop _si
					call2 _cx,_dx,macro_ops,_si,_dx,_cx
					sub _di,_dx
					sub _bx,_di
					mov _bp,_si
					sub _bp,macro_set_len*rsize*2
					cmp _ax,_bp
					ja _________macro_ops_ncall
						cmp _word[_bp],_word 1
						jne _________macro_ops_nfunc
							mov _bp,1
						jmp _________macro_ops_func
						_________macro_ops_nfunc:
							mov _bp,0
						_________macro_ops_func:
					jmp _________macro_ops_call
					_________macro_ops_ncall:
						mov _bp,0
					_________macro_ops_call:
					cmp _bp,0
					je _________macro_ops_par
						mov _bp,_si
						sub _bp,macro_set_len*rsize*2
						mov _di,_dx
						sub _di,_si
						_sdiv _di,macro_set_len*rsize
						mov _word [_dx],1
						cmp _di,0
						jne _________macro_ops_call_args_0
							call1 [_dx+rsize],[_bp+rsize]
						jmp _________macro_ops_call_args_end
						_________macro_ops_call_args_0:
						cmp _di,1
						jne _________macro_ops_call_args_1
							call1 [_dx+rsize],[_bp+rsize],[_si+rsize]
						jmp _________macro_ops_call_args_end
						_________macro_ops_call_args_1:
						cmp _di,2
						jne _________macro_ops_call_args_2
							call1 [_dx+rsize],[_bp+rsize],[_si+rsize],[_si+rsize+macro_set_len*rsize]
						jmp _________macro_ops_call_args_end
						_________macro_ops_call_args_2:
						cmp _di,3
						jne _________macro_ops_call_args_3
							call1 [_dx+rsize],[_bp+rsize],[_si+rsize],[_si+rsize+macro_set_len*rsize],[_si+rsize+macro_set_len*rsize*2]
						jmp _________macro_ops_call_args_end
						_________macro_ops_call_args_3:
							call1 [_dx+rsize],[_bp+rsize],[_si+rsize],[_si+rsize+macro_set_len*rsize],[_si+rsize+macro_set_len*rsize*2],[_si+rsize+macro_set_len*rsize*3]
						_________macro_ops_call_args_end:
						_sub _si,macro_set_len*rsize
					jmp _________macro_ops_par_end
					_________macro_ops_par:
						_mov _word[_dx],[_dx-macro_set_len*rsize]
						_mov _word[_dx+rsize],[_dx+rsize-macro_set_len*rsize]
						_mov _word[_dx+rsize*2],[_dx+rsize*2-macro_set_len*rsize]
					_________macro_ops_par_end:
					push _ax
					mov _ax,_dx
					sub _ax,_si
					add _ax,macro_set_len*rsize
					_div _ax,macro_set_len*rsize
					sub _dx,macro_set_len*rsize
					macro_set_memmove _ax
					add _dx,macro_set_len*rsize
					pop _ax
				jmp _________macro_ops_end6
				_________macro_ops_not6_2:
				cmp _bp,'b['
				jne _________macro_ops_not6_3
					add _dx,macro_set_len*rsize
					push _dx
					push _word 1
					sub _dx,macro_set_len*rsize
				jmp _________macro_ops_end6
				_________macro_ops_not6_3:
				cmp _bp,'w['
				jne _________macro_ops_not6_4
					add _dx,macro_set_len*rsize
					push _dx
					push _word 2
					sub _dx,macro_set_len*rsize
				jmp _________macro_ops_end6
				_________macro_ops_not6_4:
				cmp _bp,'d['
				jne _________macro_ops_not6_5
					add _dx,macro_set_len*rsize
					push _dx
					push _word 4
					sub _dx,macro_set_len*rsize
				jmp _________macro_ops_end6
				_________macro_ops_not6_5:
				cmp _bp,'q['
				jne _________macro_ops_not6_7
					add _dx,macro_set_len*rsize
					push _dx
					push _word 8
					sub _dx,macro_set_len*rsize
				jmp _________macro_ops_end6
				_________macro_ops_not6_7:
				cmp _bp,'['
				jne _________macro_ops_not6_6
					add _dx,macro_set_len*rsize
					push _dx
					push _word rsize
					sub _dx,macro_set_len*rsize
				jmp _________macro_ops_end6
				_________macro_ops_not6_6:
				cmp _bp,']'
				jne _________macro_ops_not6_8
					mov _di,_dx
					pop _bp
					pop _si
					call2 _cx,_dx,macro_ops,_si,_dx,_cx
					sub _di,_dx
					sub _bx,_di
					cmp _bp,1
					jne _________macro_ops_get_n1
						pushad
						mov _bx,[_dx+rsize-macro_set_len*rsize]
						mov _cx,[_dx+rsize-macro_set_len*rsize*3]
						lea _bx,[_cx+_bx*1]
						mov al,[_bx]
						movsx _ax,al
						mov _word[_dx+rsize],_ax
						mov _word[_dx],_bx
						mov _word[_dx+rsize*2],_word 1
						popad
					jmp _________macro_ops_get_end
					_________macro_ops_get_n1:
					cmp _bp,2
					jne _________macro_ops_get_n2
						pushad
						mov _bx,[_dx+rsize-macro_set_len*rsize]
						mov _cx,[_dx+rsize-macro_set_len*rsize*3]
						lea _bx,[_cx+_bx*2]
						mov ax,[_bx]
						movsx _ax,ax
						mov [_dx+rsize],_ax
						mov _word[_dx],_bx
						mov _word[_dx+rsize*2],_word 2
						popad
					jmp _________macro_ops_get_end
					_________macro_ops_get_n2:
					cmp _bp,4
					jne _________macro_ops_get_n4
						pushad
						mov _bx,[_dx+rsize-macro_set_len*rsize]
						mov _cx,[_dx+rsize-macro_set_len*rsize*3]
						lea _bx,[_cx+_bx*4]
						mov eax,[_bx]
						mov [_dx+rsize],eax
						mov _word[_dx],_bx
						mov _word[_dx+rsize*2],_word 4
						popad
					jmp _________macro_ops_get_end
					_________macro_ops_get_n4:
				%if __BITS__=64
					cmp _bp,8
					jne _________macro_ops_get_n8
						pushad
						mov _bx,[_dx+rsize-macro_set_len*rsize]
						mov _cx,[_dx+rsize-macro_set_len*rsize*3]
						lea _bx,[_cx+_bx*8]
						mov rax,[_bx]
						mov [_dx+rsize],rax
						mov _word[_dx],_bx
						mov _word[_dx+rsize*2],_word 8
						popad
					jmp _________macro_ops_get_end
					_________macro_ops_get_n8:
				%endif
					_________macro_ops_get_end:
					sub _dx,macro_set_len*rsize
					macro_set_memmove 3
					add _dx,macro_set_len*rsize
				jmp _________macro_ops_end6
				_________macro_ops_not6_8:
				_________macro_ops_end6:
			_________macro_ops_part6:
		add _dx,macro_set_len*rsize
		jmp _________macro_ops_for_begin6
		_________macro_ops_for_end6:
		call2 _cx,_bx,macro_ops,_ax,_bx,_cx	
		mov _ax,_cx
	end


	section .text
		macro_expr_hash_jmp:
		pushad
		add _sp,rsize*8
		pop _bx
		pop _ax
		sub _sp,rsize*10

		mov _bp,_ax
		mov _di,_bx
		mov _cx,_bx
		mov _bx,_ax
		mov _ax,0
		mov _si,75
		_________macro_expr_hash_1:
		mul _si
		mov _dx,0
		mov dl,[_bx]
		sub dl,48
		add _ax,_dx
		inc _bx
		loop _________macro_expr_hash_1
		div _word [len_vars_names]
		lea _ax,[vars_names+_dx*8 ]
		mov _bx,[_sp+rsize*10]
		mov _word[_sp+rsize*10],_ax
		mov _word[_sp+rsize*9],_bx
		popad
		add _sp,rsize*2
		jmp [_sp-rsize]	

	section .text
		macro_var_jmp:
		pushad
		mov _si,[_sp+rsize*8]
		mov _di,[_sp+rsize*10]
		mov _bp,_di
		sub _bp,_si
		mov _cx,_bp
		mov _bx,_si
		macro_set_hash _bx,_si,_bp
		mov _cx,[_sp+rsize*9]
		cmp _word[_bx],_word 0
		je _________macro_var_stay_calm
			swrite "warning:"
			pushad
			mov _ax,4
			mov _bx,1
			mov _cx,_si
			mov _dx,_bp
			int 0x80
			popad
			sprint " redefined"
		_________macro_var_stay_calm:
		mov _word[_bx],_cx
		popad
		add _sp,3*rsize
		jmp [_sp-rsize]


	section .text
		macro_expr_jmp:
		pushad
		add _sp,rsize*8
		pop _bp
		pop _di
		sub _sp,rsize*10
		push _sp
		mov _ax,0
		mov _bx,0
		mov _cx,0
		mov _si,0
		mov dh,-1
		mov _bx,_bp
		_________macro_expr_main_loop_begin:
		cmp _bx,_di
		jae _________macro_expr_main_loop_end
			mov cl,[_bx]
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
					pop _word _ax
					push _word 2
					push _word _si
					push _word 0
					push _word _ax
				jmp _________macro_expr_dh_end
				_________macro_expr_dh_n0:
				cmp dh,1
				jne _________macro_expr_dh_n1
					pop _word _ax
					push _word 1
					push _word _si
					push _word 0
					push _word _ax
				jmp _________macro_expr_dh_end
				_________macro_expr_dh_n1:
				cmp dh,2
				jne _________macro_expr_dh_n2
					sub _bx,_si
					macro_set_hash _ax,_si,_bx
					cmp _word[_ax],_word 0
					jne _________macro_expr_stay_calm
						swrite "warning:"
						pushad
						mov _dx,_bx
						mov _ax,4
						mov _bx,2
						mov _cx,_si
						int 0x80
						popad
						sprint " not found"
					_________macro_expr_stay_calm:
					add _bx,_si
					mov _ax,[_ax]
					mov _si,_ax
					pop _word _ax
					push _word 1
					push _word _si
					push _word 0
					push _word _ax
				_________macro_expr_dh_n2:
				_________macro_expr_dh_end:
				cmp ch,0
				jne _________macro_expr_ch_n0
					movzx _si,cl
				jmp _________macro_expr_ch_end
				_________macro_expr_ch_n0:
				cmp ch,1
				jne _________macro_expr_ch_n1
					movzx _si,cl
					sub _si,'0'
				jmp _________macro_expr_ch_end
				_________macro_expr_ch_n1:
				cmp ch,2
				jne _________macro_expr_ch_n2
					mov _si,_bx
				jmp _________macro_expr_ch_end
				_________macro_expr_ch_n2:
				cmp ch,4
				jne _________macro_expr_ch_n4
					pop _word _ax
					push _word 1
					push _word 0
					push _word 0
					push _word 2
					push _word '+'
					push _word 0
					push _word _ax
				jmp _________macro_expr_ch_end
				_________macro_expr_ch_n4:
				cmp ch,5
				jne _________macro_expr_ch_n5
					pop _word _ax
					push _word 2
					push _word ')'
					push _word 0
					push _word 1
					push _word 0
					push _word 0
					push _word 2
					push _word '+'
					push _word 0
					push _word 2
					push _word '('
					push _word 0
					push _word _ax
				_________macro_expr_ch_end:
				_________macro_expr_ch_n5:
			jmp _________macro_expr_contend
			_________macro_expr_continuing:
				cmp ch,0
				jne _________macro_expr_same_n0
					cmp _si,256
					jae _________macro_expr_oper_ge256
						mov _ax,0
						mov al,cl
						push _dx
						mov _dx,256
						mul _dx
						pop _dx
						add _si,_ax
						push _dx
						push _bx
						push _bp
						mov _dx,0
						mov _bx,0
						_________macro_expr_oper_1_for_begin:
						cmp _bx,[len_operators]
						jae _________macro_expr_oper_1_for_end
							lea _bp,[operators+_bx*rsize]
							mov _bp,[_bp]
							cmp _bp,_si
							jne _________macro_expr_oper_1_nc
								mov _dx,1
							_________macro_expr_oper_1_nc:
						inc _bx
						jmp _________macro_expr_oper_1_for_begin
						_________macro_expr_oper_1_for_end:
						cmp _dx,0
						jne _________macro_expr_oper_1_f
							sub _si,_ax
							pop _bp
							pop _bx
							pop _dx
							pop _word _ax
							push _word 2
							push _word _si
							push _word 0
							push _word _ax
							push _dx
							push _bx
							push _bp
							mov _si,0
							mov _ax,0
							mov al,cl
							mov _si,_ax
						_________macro_expr_oper_1_f:
						pop _bp
						pop _bx
						pop _dx
					jmp _________macro_expr_oper_end
					_________macro_expr_oper_ge256:
					cmp _si,256*256
					jae _________macro_expr_oper_ge256_256
						mov _ax,0
						mov al,cl
						push _dx
						mov _dx,256*256
						mul _dx
						pop _dx
						add _si,_ax
						push _dx
						push _bx
						push _bp
						mov _dx,0
						mov _bx,0
						_________macro_expr_oper_2_for_begin:
						cmp _bx,[len_operators]
						jae _________macro_expr_oper_2_for_end
							lea _bp,[operators+_bx*rsize]
							mov _bp,[_bp]
							cmp _bp,_si
							jne _________macro_expr_oper_2_nc
								mov _dx,1
							_________macro_expr_oper_2_nc:
						inc _bx
						jmp _________macro_expr_oper_2_for_begin
						_________macro_expr_oper_2_for_end:
						cmp _dx,0
						jne _________macro_expr_oper_2_f
							sub _si,_ax
							pop _bp
							pop _bx
							pop _dx
							pop _word _ax
							push _word 2
							push _word _si
							push _word 0
							push _word _ax
							push _dx
							push _bx
							push _bp
							mov _si,0
							mov _ax,0
							mov al,cl
							mov _si,_ax
						_________macro_expr_oper_2_f:
						pop _bp
						pop _bx
						pop _dx
					jmp _________macro_expr_oper_end
					_________macro_expr_oper_ge256_256:
					cmp _si,256*256*256
					jae _________macro_expr_oper_ge256_256_256
						mov _ax,0
						mov al,cl
						push _dx
						mov _dx,256*256*256
						mul _dx
						pop _dx
						add _si,_ax
						push _dx
						push _bx
						push _bp
						mov _dx,0
						mov _bx,0
						_________macro_expr_oper_3_for_begin:
						cmp _bx,[len_operators]
						jae _________macro_expr_oper_3_for_end
							lea _bp,[operators+_bx*rsize]
							mov _bp,[_bp]
							cmp _bp,_si
							jne _________macro_expr_oper_3_nc
								mov _dx,1
							_________macro_expr_oper_3_nc:
						inc _bx
						jmp _________macro_expr_oper_3_for_begin
						_________macro_expr_oper_3_for_end:
						cmp _dx,0
						jne _________macro_expr_oper_3_f
							sub _si,_ax
							pop _bp
							pop _bx
							pop _dx
							pop _word _ax
							push _word 2
							push _word _si
							push _word 0
							push _word _ax
							push _dx
							push _bx
							push _bp
							mov _si,0
							mov _ax,0
							mov al,cl
							mov _si,_ax
						_________macro_expr_oper_3_f:
						pop _bp
						pop _bx
						pop _dx
					_________macro_expr_oper_end:
					_________macro_expr_oper_ge256_256_256:
				jmp _________macro_expr_same_end
				_________macro_expr_same_n0:
				cmp ch,1
				jne _________macro_expr_same_n1
					mov _ax,0
					mov al,cl
					sub _ax,'0'
					push _ax
					push _dx
					mov _ax,_si
					mov _dx,10
					mul _dx
					mov _si,_ax
					pop _dx
					pop _ax
					add _si,_ax
				_________macro_expr_same_end:
				_________macro_expr_same_n1:
			_________macro_expr_contend:
			mov dh,ch
		inc _bx
		jmp _________macro_expr_main_loop_begin
		_________macro_expr_main_loop_end:
		pop _bx
		mov _ax,_sp
		mov _dx,_ax

		mov _si,_ax
		mov _di,_bx

		_________macro_expr_swap_begin:
		cmp _ax,_bx
		jae _________macro_expr_swap_end
			mov _cx,[_ax]
			mov _bp,[_bx-rsize]
			mov _word[_ax],_bp
			mov _word[_bx-rsize],_cx
			add _ax,rsize
			sub _bx,rsize
		jmp _________macro_expr_swap_begin
		_________macro_expr_swap_end:

		mov _ax,_si
		mov _bx,_di

		macro_set_pr
		call0 macro_bops,_ax,_bx,_bx

		mov _sp,_bx
		popad
		add _sp,rsize*2
		jmp _word [_sp-rsize]

	section .text
		macro_set_jmp:
		macro_args_read
		macro_args_offset _ax
		add _ax,_sp
		mov _cx,[_ax]
		add _ax,rsize
		mov _bx,_ax
		add _bx,_cx
		call0 macro_bops,_ax,_bx,_bx
		_mov _word[_bx-rsize],[_ax+rsize]
		macro_args_save
		add _sp,[_sp]
		add _sp,rsize*2
		jmp [_sp-rsize]


	section .text
		macro_regout:


		aput _ax
		sput " == "
		cput 27
		sput "[32m"
		_sput _ax
		cput 27
		sput "[0m"

		cput 9

		sput " "
		aput _bx
		sput " == "
		cput 27
		sput "[32m"
		_sput _bx
		cput 27
		sput "[0m"

		cput 9

		sput " "
		aput _cx
		sput " == "
		cput 27
		sput "[32m"
		_sput _cx
		cput 27
		sput "[0m"

		cput 9

		sput " "
		aput _dx
		sput " == "
		cput 27
		sput "[32m"
		_sput _dx
		cput 27
		sput "[0m"

		cput 9

		sput " "
		aput _si
		sput " == "
		cput 27
		sput "[32m"
		_sput _si
		cput 27
		sput "[0m"

		cput 9

		sput " "
		aput _di
		sput " == "
		cput 27
		sput "[32m"
		_sput _di
		cput 27
		sput "[0m"

		cput 9

		sput " "
		aput _bp
		sput " == "
		cput 27
		sput "[32m"
		_sput _bp
		cput 27
		sput "[0m"

		cput 9

		sput " "
		aput _sp
		sput " == "
		cput 27
		sput "[32m"

		sub [_sp],_sp
		neg _word [_sp]
		xchg _ax,[_sp]
		add _ax,rsize*3
		_sput _ax
		sub _ax,rsize*3
		xchg _ax,[_sp]
		neg _word [_sp]
		add [_sp],_sp

		cput 27
		sput "[0m"

		cput 9

		sput " line = "
		cput 27
		sput "[32m"

		xchg _ax,[_sp+rsize]
		_sput _ax
		xchg _ax,[_sp+rsize]
		cput 27
		sput "[0m"

		cput 10

		add _sp,2*rsize
		ret

	; section .text
	; 	macro_pre_start:
	; 	ret


	; %if __BITS__ == 32
section .text

	__best__uput_one:
		pushad

		mov _dx,0
		mov _cx,0
		mov _si,0
		mov _bp,0

		mov _bx,10
		mov _di,_ax

		__best__uput_one_1:
		inc _cx
		div _bx
		mov _dx,0
		cmp _ax,0
		jne __best__uput_one_1

		mov _si,_cx
		mov _dx,0
		mov _ax,1

		__best__uput_one_2:
		push _ax
		mul _bx
		loop __best__uput_one_2

		mov _cx,_si
		mov _ax,_di

		__best__uput_one_3:
		pop _bx
		mov _dx,0
		div _bx
		add _ax,48
		cput al
		mov _ax,_dx
		loop __best__uput_one_3

		popad
		ret

	__best_quput_one:
		call __best__uput_one
		ret

	__best_qsput_one:
		__best__sign 8
		call __best__uput_one
		ret

	__best_duput_one:
		call __best__uput_one
		ret

	__best_dsput_one:
		__best__sign 4
		call __best__uput_one
		ret

	__best_wuput_one:
		call __best__uput_one
		ret

	__best_wsput_one:
		__best__sign 2
		call __best__uput_one
		ret

	__best_buput_one:
		call __best__uput_one
		ret

	__best_bsput_one:
		__best__sign 1
		call __best__uput_one
		ret

	__best_cput_one:
		pushad
		push ax
		%if __BITS__==32
			mov eax,4
			mov ebx,1
			mov ecx,esp
			mov edx,1
			int 0x80
		%else
			mov rax,1
			mov rdi,1
			mov rsi,rsp
			mov rdx,1
			syscall
		%endif
		add _sp,2
		popad
		ret

	__best_sput_one:
		cput al
		ret



	__best_quput:   __best_multiple 8,rax,__best_quput_one,nop,nop,32,0
	__best_qsput:   __best_multiple 8,rax,__best_qsput_one,nop,nop,32,0
	__best_duput:   __best_multiple 4,_ax,__best_duput_one,nop,nop,32,0
	__best_dsput:   __best_multiple 4,_ax,__best_dsput_one,nop,nop,32,0
	__best_wuput:   __best_multiple 2,ax,__best_wuput_one,nop,nop,32,0
	__best_wsput:   __best_multiple 2,ax,__best_wsput_one,nop,nop,32,0
	__best_buput:   __best_multiple 2,al,__best_buput_one,__best_alr,nop,32,0
	__best_bsput:   __best_multiple 2,al,__best_bsput_one,__best_alr,nop,32,0
	__best_cput:    __best_multiple 2,al,__best_cput_one,__best_alr,nop,32,0
	__best_sput:    __best_multiple 1,al,__best_sput_one,nop,__best_strp,0,0
	__best_quwrite: __best_multiple 8,_ax,__best_quput_one,nop,nop,32,32
	__best_qswrite: __best_multiple 8,_ax,__best_qsput_one,nop,nop,32,32
	__best_duwrite: __best_multiple 4,_ax,__best_duput_one,nop,nop,32,32
	__best_dswrite: __best_multiple 4,_ax,__best_dsput_one,nop,nop,32,32
	__best_wuwrite: __best_multiple 2,ax,__best_wuput_one,nop,nop,32,32
	__best_wswrite: __best_multiple 2,ax,__best_wsput_one,nop,nop,32,32
	__best_buwrite: __best_multiple 2,al,__best_buput_one,__best_alr,nop,32,32
	__best_bswrite: __best_multiple 2,al,__best_bsput_one,__best_alr,nop,32,32
	__best_cwrite:  __best_multiple 2,al,__best_cput_one,__best_alr,nop,32,32
	__best_swrite:  __best_multiple 1,al,__best_sput_one,nop,__best_strp,0,32
	__best_quprint: __best_multiple 8,_ax,__best_quput_one,nop,nop,32,10
	__best_qsprint: __best_multiple 8,_ax,__best_qsput_one,nop,nop,32,10
	__best_duprint: __best_multiple 4,_ax,__best_duput_one,nop,nop,32,10
	__best_dsprint: __best_multiple 4,_ax,__best_dsput_one,nop,nop,32,10
	__best_wuprint: __best_multiple 2,ax,__best_wuput_one,nop,nop,32,10
	__best_wsprint: __best_multiple 2,ax,__best_wsput_one,nop,nop,32,10
	__best_buprint: __best_multiple 2,al,__best_buput_one,__best_alr,nop,32,10
	__best_bsprint: __best_multiple 2,al,__best_bsput_one,__best_alr,nop,32,10
	__best_cprint:  __best_multiple 2,al,__best_cput_one,__best_alr,nop,32,10
	__best_sprint:  __best_multiple 1,al,__best_sput_one,nop,__best_strp,0,10

	; __best_duput:   __best_multiple 4,__best_duput_one,nop,nop,32,0
	; __best_dsput:   __best_multiple 4,__best_dsput_one,nop,nop,32,0
	; __best_wuput:   __best_multiple 2,__best_wuput_one,nop,nop,32,0
	; __best_wsput:   __best_multiple 2,__best_wsput_one,nop,nop,32,0
	; __best_buput:   __best_multiple 2,__best_buput_one,__best_alr,nop,32,0
	; __best_bsput:   __best_multiple 2,__best_bsput_one,__best_alr,nop,32,0
	; __best_cput:    __best_multiple 2, __best_cput_one,__best_alr,nop,32,0
	; __best_sput:    __best_multiple 1, __best_sput_one,nop,__best_strp,0,0
	; __best_duwrite: __best_multiple 4,__best_duput_one,nop,nop,32,32
	; __best_dswrite: __best_multiple 4,__best_dsput_one,nop,nop,32,32
	; __best_wuwrite: __best_multiple 2,__best_wuput_one,nop,nop,32,32
	; __best_wswrite: __best_multiple 2,__best_wsput_one,nop,nop,32,32
	; __best_buwrite: __best_multiple 2,__best_buput_one,__best_alr,nop,32,32
	; __best_bswrite: __best_multiple 2,__best_bsput_one,__best_alr,nop,32,32
	; __best_cwrite:  __best_multiple 2, __best_cput_one,__best_alr,nop,32,32
	; __best_swrite:  __best_multiple 1, __best_sput_one,nop,__best_strp,0,32
	; __best_duprint: __best_multiple 4,__best_duput_one,nop,nop,32,10
	; __best_dsprint: __best_multiple 4,__best_dsput_one,nop,nop,32,10
	; __best_wuprint: __best_multiple 2,__best_wuput_one,nop,nop,32,10
	; __best_wsprint: __best_multiple 2,__best_wsput_one,nop,nop,32,10
	; __best_buprint: __best_multiple 2,__best_buput_one,__best_alr,nop,32,10
	; __best_bsprint: __best_multiple 2,__best_bsput_one,__best_alr,nop,32,10
	; __best_cprint:  __best_multiple 2, __best_cput_one,__best_alr,nop,32,10
	; __best_sprint:  __best_multiple 1, __best_sput_one,nop,__best_strp,0,10

	; %endif

%endif
