; %define __BITS__ 32 
%include "macro.inc"

struc com
	com.real res_ 1
	com.imag res_ 1
endstruc

section .data
_q istruc com
	at com.real
		d_ 1
	at com.imag
		d_ 2
_w istruc com
	at com.real
		d_ 3
	at com.imag
		d_ 4
iend

def com_add
	add _ax,_cx
	add _bx,_dx
end

def com_sub
	sub _ax,_cx
	sub _bx,_dx
end

def com_mul
	_push 0
	_push 0
	push _dx
	push _cx
	push _bx
	push _ax
	mov _si,_sp
	set [_si+rsize*4],=,[_si+rsize*0],*,[_si+rsize*2],-,[_si+rsize*1],*,[_si+rsize*3]
	set [_si+rsize*5],=,[_si+rsize*0],*,[_si+rsize*3],+,[_si+rsize*2],*,[_si+rsize*1]
	add _sp,rsize*4
	pop _ax
	pop _bx
end

def root
	while _bx,*,_bx,<=,_ax
		inc _bx
	end
	dec _bx
	mov _ax,_bx
end

def com_abs
	_push 0
	push _bx
	push _ax
	mov _si,_sp
	set [_si+rsize*2],=,[_si+rsize*0],*,[_si+rsize*0],+,[_si+rsize*1],*,[_si+rsize*1]
	add _sp,rsize*2
	pop _ax
	call1 _ax,root,_ax
end



begin

; call2 [_q+com.real],[_q+com.imag],com_mul,[_q+com.real],[_q+com.imag],[_w+com.real],[_w+com.imag]

; call1 [q],com_abs,[_w+com.real],[_w+com.imag]

; print [q]

; print [_q+com.real],[_q+com.imag]

while 1
	_get [q]
	_mov [r],0
	_mov [p],1
	ror _word [p],2
	while p
		_mov [u],[r]
		_add [u],[p]
		if [q],>=,[u]
			_sub [q],[u]
			_add [r],[p]
			_add [r],[p]
		end
		shr _word [r],1
		shr _word [p],2
	end
	print [r]
end

end
