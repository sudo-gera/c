%define _div _ %+ div

%macro qdiv 1+
qsdiv %1
%endmacro

%macro ddiv 1+
dsdiv %1
%endmacro

%macro wdiv 1+
wsdiv %1
%endmacro

%macro bdiv 1+
bsdiv %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _mod _ %+ mod

%macro qmod 1+
qsmod %1
%endmacro

%macro dmod 1+
dsmod %1
%endmacro

%macro wmod 1+
wsmod %1
%endmacro

%macro bmod 1+
bsmod %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _divmod _ %+ divmod

%macro qdivmod 1+
qsdivmod %1
%endmacro

%macro ddivmod 1+
dsdivmod %1
%endmacro

%macro wdivmod 1+
wsdivmod %1
%endmacro

%macro bdivmod 1+
bsdivmod %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro write 1+
_swrite %1
%endmacro

%macro print 1+
_sprint %1
%endmacro

%macro put 1+
_sput %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro for 1+
_sfor %1
%endmacro

%macro if 1+
%push if
jmp %%_1
%$__jup:
jmp %$__jdown
%%_1:
set [ch_val],=,(,%1,)
_eq [ch_val],0,%$__jelse
%endmacro

%macro elif 1+
jmp %%_1
%$__jelse:
jmp %%_2
%%_1:
%$__jdown:
%pop
%push if
%$__jup:
jmp %$__jdown
%%_2:
set [ch_val],=,(,%1,)
_eq [ch_val],0,%$__jelse
%endmacro

%macro while 1+
%push while
%$__jup:
set [ch_val],=,(,%1,)
_eq [ch_val],0,%$__jdown
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

