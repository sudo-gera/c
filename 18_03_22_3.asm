

%include "st_io.inc"
global _start
section .data
a db -1,-2,3,4
la dd 4
lb dd 0
lc dd 0
w dd 0
section .bss
b resb 6
c resb 6
section .text
_start:

mov [w],dword 0
_1:
mov ebx,[la]
cmp [w],ebx
jge _2
mov ebx,[w]
lea ebx,[a+ebx*1]
mov bl,[ebx]
movsx ebx,bl
mov eax,ebx
mov ecx,2
mov edx,0
div ecx
cmp edx,0
jne _3
mov ecx,[lb]
lea ecx,[b+ecx*1]
mov [ecx],bl
inc dword [lb]
jmp _4
_3:
mov ecx,[lc]
lea ecx,[c+ecx*1]
mov [ecx],bl
inc dword [lc]
_4:
inc dword[w]
jmp _1
_2:

mov [w],dword 0
_5:
mov ebx,[lb]
cmp [w],ebx
jge _6
mov ebx,[w]
lea ebx,[b+ebx*1]
mov bl,[ebx]
movsx ebx,bl
SIGNINT ebx
PUTCHAR 10
inc dword[w]
jmp _5
_6:
PUTCHAR 10

mov [w],dword 0
_7:
mov ebx,[lc]
cmp [w],ebx
jge _8
mov ebx,[w]
lea ebx,[c+ebx*1]
mov bl,[ebx]
movsx ebx,bl
SIGNINT ebx
PUTCHAR 10
inc dword[w]
jmp _7
_8:
PUTCHAR 10

end:
FINISH
