%include "st_io.inc"
%include "macro.inc"
section .bss
aa resd 9999
bb resd 9999
cc resd 9999
h1 resd 1
h2 resd 1
h3 resd 1
start
GETUN [h1]
GETUN [h2]
GETUN [h3]
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
_22:
duge [w],[h2],_23
	dmov [h],0
	_24:
	duge [h],[h3],_25
		dmul [q],[h3],[w]
		dadd [q],[h]
		GETUN [c]
		daput bb,[q],[c]
	dinc [h]
	jmp _24
	_25:
	PUTCHAR 10
dinc [w]
jmp _22
_23:
dmov [w],0
_1:
duge [w],[h1],_2
	dmov [h],0
	_3:
	duge [h],[h3],_4
		dmov [s],0
		dmov [q],0
		_9:
		duge [q],[h2],_10
			dmul [z],[w],[h2]
			dadd [z],[q]
			daget [a],aa,[z]
			dmul [z],[q],[h3]
			dadd [z],[h]
			daget [b],bb,[z]
			dmul [a],[b]
			dadd [s],[a]
		dinc [q]
		jmp _9
		_10:
		dmul [z],[h3],[w]
		dadd [z],[h]
		daput cc,[z],[s]
	dinc [h]
	jmp _3
	_4:
dinc [w]
jmp _1
_2:
dmov [w],0
_5:
duge [w],[h1],_6
	dmov [h],0
	_7:
	duge [h],[h3],_8
		dmul [q],[h3],[w]
		dadd [q],[h]
		daget [c],cc,[q]
		UNSINT [c]
		PRINT " "
	dinc [h]
	jmp _7
	_8:
	PUTCHAR 10
dinc [w]
jmp _5
_6:
stop
