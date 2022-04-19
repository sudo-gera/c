%include "macro.inc"

matr:
pushfd
pushad
mov eax,[esp+40]
mov ebx,0
if eax,<,0
	mov ebx,[esp+44]
	neg eax
end
dec ebx
for ecx,ebx
	cput 32
end
inc ebx
if ebx
	sput "┗"
end
sprint "┓"
if ebx,<,eax
	inc ebx
	push ebx
	dec ebx
	neg eax
	push eax
	neg eax
	call matr
	add esp,8
else
	for ecx,ebx
		cput 32
	end
	sprint "┃"
end
dec ebx
for ecx,ebx
	cput 32
end
inc ebx
if ebx
	sput "┏"
end
sprint "┛"
popad
popfd
ret


begin
push 5
call matr
add esp,4


end
