%include "macro.inc"

%if __BITS__ == 64
%define _get _qsget
%endif

begin

_get [n]
_push [n]
call func_f
_pop [f]
print [f]
_push [n]
call func_g
_pop [g]
print [g]

end


func_f:
	db 'PQRSTUVW'
	mov _ax,[_sp+9*rsize]
	cmp _ax,2
	jl _1
	; if _ax,>=,2
		dec _ax
		push _ax
		call func_f
		pop _bx
		push _ax
		call func_g
		pop _cx
		_mul _cx,3
		add _bx,_cx
		mov [_sp+9*rsize],_bx
	jmp _2
	_1:
	; else
		mov _word [_sp+9*rsize],_word 1
	_2:
	db '_^]X[ZYX'
	ret

func_g:
	db 'PQRSTUVW'
	mov _ax,[_sp+9*rsize]
	cmp _ax,2
	jl _2
	; if _ax,>=,2
		dec _ax
		push _ax
		call func_f
		pop _bx
		push _ax
		call func_g
		pop _cx
		_mul _cx,2
		sub _bx,_cx
		mov [_sp+9*rsize],_bx
	jmp _4
	_3:
	; else
		mov _word [_sp+9*rsize],_word 1
	_4:
	; end
	db '_^]X[ZYX'
	ret
