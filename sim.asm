%include "st_io.inc"
section .data
x times 40 db 0
y times 40 db 0
ent db 10
section .text
global _start
_start:
GETSIG [x]
GETSIG [y]

%rep 32
; mov ecx,32
; moveloop:
rcl dword [x],1
rcl dword [y],1
%endrep
; loop moveloop
rcl dword [x],1

SIGNINT [x]
PUTCHAR 10
SIGNINT [y]
PUTCHAR 10
FINISH

