%include "st_io.inc"
%include "macro.inc"

start

mov ebx,16
mov eax,3


_divmod ebx,eax,ebx,eax

UNSINT ebx
PUTCHAR 10
UNSINT eax
PUTCHAR 10


stop
