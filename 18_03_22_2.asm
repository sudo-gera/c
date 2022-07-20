%include "st_io.inc"
global _start
section .data
l dd 0
c dd 0
s dd 0
lb dd 0
section .bss
a resd 99
b resd 99
section .text
_start:
GETUN [l]

mov eax,0
_4:
mov ebx,eax
lea ebx,[a+ebx*4]
GETUN [ebx]
inc eax
cmp eax,[l]
jne _4

PUTCHAR 10

mov eax,0
_5:
mov ebx,eax
lea ebx,[a+ebx*4]
cmp [ebx],dword 12
jle _6
cmp [ebx],dword 25
jge _6
mov ecx,[ebx]
inc dword[c]
add [s],ecx
mov ecx,ebx
mov ebx,[lb]
lea ebx,[b+ebx*4]
mov [ebx],eax
inc dword[lb]
_6:
inc eax
cmp eax,[l]
jne _5

mov eax,[s]
mov ebx,[c]
div ebx
UNSINT eax
PUTCHAR 10
PUTCHAR 10

mov eax,0
_7:
mov ebx,eax
lea ebx,[b+ebx*4]
UNSINT [ebx]
PUTCHAR 10
inc eax
cmp eax,[lb]
jne _7



end:
FINISH
