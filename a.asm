

%include "st_io.inc"
global _start
section .bss
c resd 1991
section .text
_start:
;mov bx,[b]
;add [a],bx
;mov cx,[b+2]
;adc [a+2],cx
GETUN [a]
UNSINT [a]
PUTCHAR 10
FINISH
section .data
a dd 1123456780
b dd 1876543210
