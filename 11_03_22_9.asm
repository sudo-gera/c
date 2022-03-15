%include "st_io.inc"
global _start
section .data
section .bss
w resb 4
section .text
_start:
mov [w],dword 4294967295
; mov ecx,dword 4294967295
for:
dec dword[w]
; dec ecx
cmp [w],dword 0
je end
; jcxz end
jmp for
end:
FINISH
