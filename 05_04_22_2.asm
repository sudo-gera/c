%include "st_io.inc"
section .text
global _start
_start:

GETUN eax
GETUN ebx
GETUN ecx
GETUN esi
GETUN edi
GETUN ebp

sub eax,esi
sub ebx,edi
add ecx,ebp

mul eax
xchg eax,ebx
mul eax
xchg eax,ecx
mul eax

add ebx,ecx
cmp ebx,eax
jbe _1
	PRINT "N"
jmp _2
_1:
	PRINT "Y"
_2:
PUTCHAR 10


FINISH
