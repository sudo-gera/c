%include "st_io.inc"
global _start
section .bss
section .data
x dd 4294967293
section .text
_start:
mov al,[x]
mov ah,[x+1]
mov bl,[x+2]
mov bh,[x+3]
add al,1
adc ah,0
adc bl,0
adc bh,0
mov [x],al
mov [x+1],ah
mov [x+2],bl
mov [x+3],bh
UNSINT [x]
PUTCHAR 10
FINISH
