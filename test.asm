%include "st_io.inc"
%include "macro.inc"

start

mov ebx,13
mov eax,4


regout
_divmod [a],[s],ebx,eax
regout

UNSINT [a]
PUTCHAR 10
UNSINT [s]
PUTCHAR 10


stop
