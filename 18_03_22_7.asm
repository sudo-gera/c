%include "st_io.inc"
global _start
section .data
la dd 0
w dd 0
p dd 9
e dd 0
minv dd -32000
mini dd 65535
section .bss
a resw 999
section .text
_start:

GETUN [la]
mov [w],dword 0
_9:
mov ebx,[la]
cmp [w],ebx
jge _10
GETSIG eax
mov ebx,[w]
lea ebx,[a+ebx*2]
mov [ebx],ax
inc dword[w]
jmp _9
_10:



mov [w],dword 0
_5:
mov ebx,[la]
cmp [w],ebx
jge _6
mov ebx,[w]
lea ebx,[a+ebx*2]
mov bx,[ebx]
movsx ebx,bx
cmp ebx,[minv]
jle _0
cmp ebx,0
jge _0
mov [minv],ebx
mov ebx,[w]
mov [mini],ebx
_0:
inc dword[w]
jmp _5
_6:

PUTCHAR 10
mov ebx,[la]
dec ebx
mov [e],ebx
_3:
mov ebx,[mini]
dec ebx
cmp [e],ebx
jle _4

mov ebx,[e]
lea ebx,[a+ebx*2]
mov bx,[ebx]
movsx ebx,bx
mov eax,ebx
mov ebx,[e]
inc ebx
lea ebx,[a+ebx*2]
mov [ebx],ax

dec dword[e]
jmp _3
_4:

inc dword[la]
mov ebx,[mini]
inc ebx
lea ebx,[a+ebx*2]
mov eax,[p]
mov [ebx],ax


mov [w],dword 0
_7:
mov ebx,[la]
cmp [w],ebx
jge _8
mov ebx,[w]
lea ebx,[a+ebx*2]
mov bx,[ebx]
movsx ebx,bx
SIGNINT ebx
PUTCHAR 10
inc dword[w]
jmp _7
_8:

end:
FINISH
