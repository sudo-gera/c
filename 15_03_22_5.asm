%include "st_io.inc"
global _start
section .data
a dd -2,-4,8,0,-16,-32
section .bss
sum resd 1
count resd 1
min resd 1
max resd 1
l resd 1
section .text
_start:
mov [sum],dword 0
mov [count],dword 0
mov [min],dword 0
mov [max],dword 0
mov [l],dword 0
ll:
mov ebx,[l]
lea ebx,[a+ebx*4]
mov ebx,[ebx]
cmp ebx,0
jne _4
mov ecx,1
_4:
inc dword [l]
loop ll
mov ecx,[l]
jcxz end
do:
mov ebx,[l]
sub ebx,ecx
lea ebx,[a+ebx*4]
mov ebx,[ebx]
cmp ebx,0
jge _1
add [sum],ebx
inc dword [count]
_1:
cmp ebx,[min]
jge _2
mov [min],ebx
_2:
cmp ebx,[max]
jle _3
mov [max],ebx
_3:
loop do
end:
SIGNINT [sum]
PUTCHAR 10
SIGNINT [count]
PUTCHAR 10
SIGNINT [min]
PUTCHAR 10
SIGNINT [max]
PUTCHAR 10
FINISH
