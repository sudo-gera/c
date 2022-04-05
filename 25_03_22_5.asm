%include "st_io.inc"
%include "macro.inc"
section .bss
aa resd 9999
h1 resd 1
h2 resd 1
min resd 1
min_1 resd 1
min_2 resd 1
max resd 1
max_1 resd 1
max_2 resd 1
start
GETUN [h1]
dmov [h2],[h1]
PUTCHAR 10
dmov [w],0
_11:
duge [w],[h1],_12
	dmov [h],0
	_13:
	duge [h],[h2],_14
		dmul [q],[h2],[w]
		dadd [q],[h]
		GETUN [c]
		daput aa,[q],[c]
	dinc [h]
	jmp _13
	_14:
	PUTCHAR 10
dinc [w]
jmp _11
_12:
dmov [w],0
_15:
duge [w],[h1],_16
	dmov [h],0
	_17:
	duge [h],[w],_18
		dmul [q],[h2],[w]
		dadd [q],[h]
		dmul [e],[h1],[h]
		dadd [e],[w]
		daget [z],aa,[q]
		daget [x],aa,[e]
		daput aa,[q],[x]
		daput aa,[e],[z]
	dinc [h]
	jmp _17
	_18:
dinc [w]
jmp _15
_16:
dmov [w],0
_19:
duge [w],[h1],_20
	dmov [h],0
	_21:
	duge [h],[h2],_22
		dmul [q],[h2],[w]
		dadd [q],[h]
		daget [z],aa,[q]
		UNSINT [z]
		PRINT " "
	dinc [h]
	jmp _21
	_22:
	PUTCHAR 10
dinc [w]
jmp _19
_20:
stop
