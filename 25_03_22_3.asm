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
GETUN [h2]
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
dmov [min],-1
dmov [max],0
dmov [min_1],-1
dmov [min_2],-1
dmov [max_1],-1
dmov [max_2],-1
dmov [w],0
_15:
duge [w],[h1],_16
	dmov [h],0
	_17:
	duge [h],[h2],_18
		dmul [q],[h2],[w]
		dadd [q],[h]
		daget [q],aa,[q]
		duge [q],[min],_19
			dmov [min_1],[w]
			dmov [min_2],[h]
			dmov [min],[q]
		_19:
		dule [q],[max],_20
			dmov [max_1],[w]
			dmov [max_2],[h]
			dmov [max],[q]
		_20:
	dinc [h]
	jmp _17
	_18:
	PUTCHAR 10
dinc [w]
jmp _15
_16:
UNSINT [min_1]
PRINT " "
UNSINT [min_2]
PRINT " "
UNSINT [min]
PUTCHAR 10
UNSINT [max_1]
PRINT " "
UNSINT [max_2]
PRINT " "
UNSINT [max]
PUTCHAR 10
stop
