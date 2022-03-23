%include "st_io.inc"
%include "macro.inc"

start

mov ebx,17
mov eax,4
mov ecx,19
mov edx,20

regout
_divmod ebx,eax,ebx,eax
regout

UNSINT ebx
PUTCHAR 10
UNSINT eax
PUTCHAR 10


stop
