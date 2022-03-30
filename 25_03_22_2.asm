%include "st_io.inc"
%include "macro.inc"
section .data
aa dd 1,1,1,2,2,2,3,3,3
hh dd 3
ww dd 3
darray bb
start
_1:
duge [w],[ww],_2
	dmov [b],0
	dmov [h],0
	_3:
	duge [h],[hh],_4
		dmul [q],[w],[ww]
		dadd [q],[h]
		daget [a],aa,[q]
		dadd [b],[a]
	dinc [h]
	jmp _3
	_4:
	dapush bb,[b]
dinc [w]
jmp _1
_2:
dmov [w],0
_5:
duge [w],[len_bb],_6
	daget [a],bb,[w]
	UNSINT [a]
	PUTCHAR 10
dinc [w]
jmp _5
_6:

stop
