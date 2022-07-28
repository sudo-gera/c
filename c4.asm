%include "st_io.inc"
global _start
extern is_equal
section .text
struc time_struct
	time_struct.h resd 1
	time_struct.min resd 1
endstruc


section .data

a istruc time_struct
	at time_struct.h
		dd 0
	at time_struct.min
		dd 0
iend

b istruc time_struct
	at time_struct.h
		dd 0
	at time_struct.min
		dd 0
iend


_start:

GETUN [a+time_struct+time_struct.h]
GETUN [a+time_struct+time_struct.min]
PUTCHAR 10
GETUN [b+time_struct+time_struct.h]
GETUN [b+time_struct+time_struct.min]
PUTCHAR 10

push dword [a+time_struct+time_struct.h]
push dword [a+time_struct+time_struct.min]
push dword [b+time_struct+time_struct.h]
push dword [b+time_struct+time_struct.min]

call is_equal

pop eax
UNSINT eax
PUTCHAR 10

FINISH
