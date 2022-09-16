%include "macro.inc"
data dd 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
begin
	dmov [c],0
	for [w],16
		daget eax,data,[w]
		for [e],32
			shl eax,1
			jnc _1
				dinc [c]
			_1:
		end
	end
	print [c]
	dget [n]
	dmov [m],[n]
	and dword [m],31
	shr dword [n],5
	daget [z],data,[n]
	mov cl,[m]
	shr dword [z],cl
	shr dword[z],1
	jc _2
		print 0
	jmp _3
	_2:
		print 1
	_3:
end
