%include "macro.inc"

fact:
pushfd
pushad
mov eax,[esp+40]
cmp eax,2
jl _0
mov ecx,0
dec eax
push eax
call fact
pop ebx
inc eax
mul ebx
mov [esp+40],eax
_0:
popad
popfd
ret


begin
push 6
call fact
pop eax
print eax


end
