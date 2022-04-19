%include "macro.inc"

fib:
pushfd
pushad
mov eax,[esp+40]
cmp eax,2
jl _0
mov ecx,0
dec eax
push eax
call fib
pop ebx
dec eax
push eax
call fib
pop ecx
add ebx,ecx
mov [esp+40],ebx
_0:
popad
popfd
ret


begin
push 10
call fib
pop eax
print eax


end
