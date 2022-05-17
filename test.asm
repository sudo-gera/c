%include "macro.inc"
; begin


; _ufor _ax,_1,_2
; 	buwrite [_ax]
; end
; cput 10

; jmp _2

; _1:
; or bh,bh
; ; or eax,eax
; ; pushad
; ; pushad
; ; and ebp,ebp
; ; xor ebp,ebp
; ; sub ebp,ebp
; ; ja $
; ; jmp 0
; ; jmp $+2
; ; div eax
; ; sub eax,ebx
; ; mov eax,1
; ; xor eax,eax
; ; inc eax
; ; int 0x80
; _2:


%macro view_one 1
%%_begin:
db %1
%%_end:
%endmacro

%macro view 1-*
%rep %0
view_one %1
%rotate 1
%endrep
%endmacro

; end
global main
global _start
section .text
_start:
main:
; jmp _stop

; db 'PQRSTUVW'

; view 0

; db '_^]X[ZYX'

; mov eax,[edi]

sub [eax+edi+32],eax

; xor _ax,_ax
; inc _ax
; int 0x80

; push word 0x80*256+0xcd
; jmp esp

; push word 32973
; push word 32973
; push word 32973
; push word 32973
; mov eax,esp
; wsprint [eax]

; mov ax,34

; inc byte [eax]

; sub eax,[ebx]

; push esp
; pop esp

; _1:
; dec ax
; jnz _1

; sub eax,3


; shl eax,3

; cmp eax,0

; print eax
; jmp esp

; dw 32973


; mov rax,1
; int 0x80

; pushad


; view 'da','db','dc','dd','de','df','dg','dh','di','dj','dk','dl','dm','dn','do','dp','dq','dr','ds','dt','du','dv','dw','dx','dy','dz'
; jz $
; db 't','t'


_stop:
mov eax,1
int 0x80
