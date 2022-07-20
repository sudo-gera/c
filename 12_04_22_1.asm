%include "macro.inc"
begin
	mov eax,5
	sub eax,2

	pushfd
	pop eax
	xor eax,10000000b
	push eax
	popfd

	js _1
		print 0
	jmp _2
	_1:
		print 1
	_2:
end
