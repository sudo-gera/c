%include "macro.inc"
begin
	regout
	_3:
	push _2
	jmp _1
	; call _1
	_2:
	print _3,_2
	regout
end

_1:
	regout
	xchg eax,[esp]
	print eax
	xchg eax,[esp]
	; add esp,4
	; jmp [esp-4]
ret
