%include "st_io.inc"
global _start
section .data
section .bss
n resd 2
d resb 99
l resd 1
section .text
_start:
GETUN eax
GETUN ebx
mul ebx
mov [n],eax
mov [n+4],edx
_1:
mov eax,[n]
mov edx,[n+4]
mov ebx,10
div ebx
mov [n],eax
mov ebx,[l]
lea ebx,[d+ebx*1]
mov [ebx],dl
inc dword[l]
mov [n+4],dword 0
add [n],dword 0
loopne _1
_2:
mov ebx,[l]
dec ebx
lea ebx,[d+ebx*1]
mov al,[ebx]
add al,48
mov [n],al
mov eax,4
mov ebx,1
mov ecx,n
mov edx,1
int 0x80
mov ebx,[l]
dec ebx
mov [l],ebx
add ebx,0
loopne _2
mov byte[n],10
mov eax,4
mov ebx,1
mov ecx,n
mov edx,1
int 0x80
mov eax,1
mov ebx,0
int 0x80
