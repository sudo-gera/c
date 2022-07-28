%include "st_io.inc"
global _start
section .bss
section .data
a dd 16777216
b dd 1
c dd 5
d dd 1
section .text
_start:
mov al,[b+0]
mov bl,[b+1]
mov cl,[b+2]
sub al,1
sbb bl,0
sbb cl,0
add al,[a]
adc bl,[a+1]
adc cl,[a+2]
sub al,[c]
sbb bl,[c+1]
sbb cl,[c+2]
mov [d],al
mov [d+1],bl
mov [d+2],cl
mov [d+3],byte 0
UNSINT [d]
PUTCHAR 10
FINISH
