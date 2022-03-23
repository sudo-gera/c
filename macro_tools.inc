%macro regout 0
PRINT "eax = "
PUTCHAR 27
PRINT "[32m"
SIGNINT eax
PUTCHAR 27
PRINT "[0m"

PUTCHAR 9

PRINT "ebx = "
PUTCHAR 27
PRINT "[32m"
SIGNINT ebx
PUTCHAR 27
PRINT "[0m"

PUTCHAR 9

PRINT "ecx = "
PUTCHAR 27
PRINT "[32m"
SIGNINT ecx
PUTCHAR 27
PRINT "[0m"

PUTCHAR 9

PRINT "edx = "
PUTCHAR 27
PRINT "[32m"
SIGNINT edx
PUTCHAR 27
PRINT "[0m"

PUTCHAR 9

PRINT " esi = "
PUTCHAR 27
PRINT "[32m"
SIGNINT esi
PUTCHAR 27
PRINT "[0m"

PUTCHAR 9

PRINT " edi = "
PUTCHAR 27
PRINT "[32m"
SIGNINT edi
PUTCHAR 27
PRINT "[0m"

PUTCHAR 9

PRINT " ebp = "
PUTCHAR 27
PRINT "[32m"
SIGNINT ebp
PUTCHAR 27
PRINT "[0m"

PUTCHAR 9

PRINT " esp = "
PUTCHAR 27
PRINT "[32m"
SIGNINT esp
PUTCHAR 27
PRINT "[0m"

PUTCHAR 10
%endmacro

%macro regsave 0
push eax
push ebx
push ecx
push edx
%endmacro

%macro regload 0
pop edx
pop ecx
pop ebx
pop eax
%endmacro

%macro regnull 0
mov eax,0
mov ebx,0
mov ecx,0
mov edx,0
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%include "macro_args_read.inc"
%include "macro_args_save.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro _divmod 4
macro_args_read_dd 8,%3,%4
div ebx
macro_args_save_dd %1,%2
%endmacro
