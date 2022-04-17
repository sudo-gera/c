%include "macro.inc"

section .data
; q dd 0
global _start
section .text
; _start:
begin


; jmp _2
; _1:
; buprint 1,2,34
; _2:
; dsput _2-_1

mov eax,840633404
mov ebx,1441998478
mov ecx,202105529
mov edx,180003570
mov esi,1520564170
mov edi,2123457867
mov ebp,1355131955


regout
sput "$$$"
regout


; stop
end
