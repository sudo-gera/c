%macro regout 0
PRINT "eax = "
PUTCHAR 27
PRINT "[32m"
UNSINT eax
PUTCHAR 27
PRINT "[0m"
PRINT " ebx = "
PUTCHAR 27
PRINT "[32m"
UNSINT ebx
PUTCHAR 27
PRINT "[0m"
PRINT " ecx = "
PUTCHAR 27
PRINT "[32m"
UNSINT ecx
PUTCHAR 27
PRINT "[0m"
PRINT " edx = "
PUTCHAR 27
PRINT "[32m"
UNSINT edx
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

