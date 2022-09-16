%include "macro.inc"
s1 db "123456"
s2 db "asdfgh"
begin
	mov esi,s1
	mov edi,s2
	mov ecx,6
	cld
	rep
	movsb
	snprint s1,6,s2,6
end
