global main
%if __BITS__ == 32
global _start
%endif
section .text
main:
_start:


; %include "best_io.inc"
; section .data
; a dd 0
; section .text


; scan "%c",[a]
; print "%i",[a]
; print 10


mov eax,1
int 0x80
