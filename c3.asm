%include "st_io.inc"
section .text
global _start

print:
	pushad
	add esp,36
	pop eax
	sub esp,40
	cmp eax,0
	je zero
		PRINT "top_matr "
		UNSINT eax
		PUTCHAR 10
		dec eax
		push eax
		inc eax
		call print
		add esp,4
		PRINT "bottom_matr "
		UNSINT eax
		PUTCHAR 10
		jmp end
	zero:
		PRINT "matr "
		UNSINT eax
		PUTCHAR 10
	end:
	popad
	ret


_start:

GETUN eax
push dword eax
call print


FINISH
