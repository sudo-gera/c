%include "st_io.inc"
global _start
section .data
a dd -2,-4,8,-16,-32
l dd 5
section .bss
k resd 1
res resd 1
section .text
_start:
GETUN [k]
mov [res],dword 0
mov ecx,[l]
sub ecx,[k]
jcxz end
do:
mov ebx,[l]
sub ebx,ecx
lea ebx,[a+ebx*4]
mov ebx,[ebx]
cmp ebx,0
jge _1
add [res],ebx
_1:
loop do
end:
SIGNINT [res]
PUTCHAR 10
FINISH
