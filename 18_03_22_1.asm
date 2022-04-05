%include "st_io.inc"
global _start
section .data
a dd 4,5,1,20,3,8
l dd 6
section .bss
min resd 1
max resd 1
minp resd 1
maxp resd 1
section .text
_start:
cmp [l],dword 0
je end
mov ebx,[l]
dec ebx
lea ebx,[a+ebx*4]
mov eax,[ebx]
mov [minp],ebx
mov [min],eax
mov [maxp],ebx
mov [max],eax

mov ecx,[l]
_3:
mov ebx,ecx
dec ebx
lea ebx,[a+ebx*4]
mov eax,[ebx]
cmp eax,[min]
jge _1
mov [minp],ebx
mov [min],eax
_1:
cmp eax,[max]
jle _2
mov [maxp],ebx
mov [max],eax
_2:
mov ebx,ecx
dec ebx
loopne _3

mov ebx,[minp]
mov eax,[maxp]
mov ecx,[ebx]
xchg ecx,[eax]
mov [ebx],ecx

mov eax,0
_4:
mov ebx,eax
lea ebx,[a+ebx*4]
UNSINT [ebx]
PUTCHAR 32
inc eax
cmp eax,[l]
jne _4
PUTCHAR 10
end:
FINISH
