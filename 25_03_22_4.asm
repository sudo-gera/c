%include "st_io.inc"
%include "macro.inc"
section .bss
aa resd 9999
start
GETUN [n]
PUTCHAR 27
PRINT "[32m"
PUTCHAR 9
dmov [b],1
_5:
dugt [b],[n],_6
	UNSINT [b]
	PUTCHAR 9
dinc [b]
jmp _5
_6:
PUTCHAR 27
PRINT "[0m"
PUTCHAR 10
dmov [a],1
_1:
dugt [a],[n],_2
	PUTCHAR 27
	PRINT "[32m"
	UNSINT [a]
	PUTCHAR 9
	PUTCHAR 27
	PRINT "[0m"
	dmov [b],1
	_3:
	dugt [b],[n],_4
		dmov [c],[a]
		dmov [d],[b]
		_7:
		dmul [z],[a],[b]
		deq [z],0,_8
			dumod [a],[b]
			dxchg [a],[b]
		jmp _7
		_8:
		dadd [a],[b]
		UNSINT [a]
		dmov [a],[c]
		dmov [b],[d]
		PUTCHAR 9
	dinc [b]
	jmp _3
	_4:
	PUTCHAR 10
dinc [a]
jmp _1
_2:
stop
