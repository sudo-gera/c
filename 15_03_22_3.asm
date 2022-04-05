%include "st_io.inc"
global _start
section .bss
a resd 1
b resd 1
h resd 1
w resd 1
e resd 1
ar resd 99999
sr resd 99999
l resd 1
section .text
_start:
GETUN [a]
GETUN [b]
GETUN [h]
mov [l],dword 0
mov [e],dword 1
mov ecx,-1
mov ebx,[a]
mov [w],ebx
mov ebx,[h]
sub [w],ebx
do:
mov ebx,[h]
add [w],ebx
mov ebx,[w]
cmp ebx,[b]
jle _1
mov [e],dword 0
_1:
mov ebx,[l]
lea ebx,[ar+ebx*4]
mov eax,[w]
mov [ebx],eax
mov eax,[w]
mov edx,0
mov ebx,3
div ebx
mov ebx,[l]
lea ebx,[sr+ebx*4]
mov [ebx],edx
inc dword [l]
add [e],dword 0
loopne do
mov ecx,[l]
cmp ecx,0
je end
dec ecx
cmp ecx,0
je end
pr:
dec ecx
mov ebx,ecx
sub ebx,[l]
neg ebx
dec ebx
dec ebx
lea ebx,[ar+ebx*4]
PRINT "mod("
UNSINT [ebx]
PRINT ",3)="
mov ebx,ecx
sub ebx,[l]
neg ebx
dec ebx
dec ebx
lea ebx,[sr+ebx*4]
UNSINT [ebx]
PUTCHAR 10
cmp ecx,0
jne pr
end:
FINISH


