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

%macro read_args 0
regsave
regnull
%endmacro

%macro read_argsd 1
regsave
push dword %1
regnull
pop eax
%endmacro

%macro read_argsw 1
regsave
push word %1
regnull
pop ax
%endmacro

%macro read_argsb 1
regsave
push byte %1
regnull
pop al
%endmacro

%macro read_argsdd 2
regsave
push dword %1
push dword %2
regnull
pop ebx
pop eax
%endmacro

%macro read_argswd 2
regsave
push word %1
push dword %2
regnull
pop ebx
pop ax
%endmacro

%macro read_argsbd 2
regsave
push byte %1
push dword %2
regnull
pop ebx
pop al
%endmacro

%macro read_argsdw 2
regsave
push dword %1
push word %2
regnull
pop bx
pop eax
%endmacro

%macro read_argsww 2
regsave
push word %1
push word %2
regnull
pop bx
pop ax
%endmacro

%macro read_argsbw 2
regsave
push byte %1
push word %2
regnull
pop bx
pop al
%endmacro

%macro read_argsdb 2
regsave
push dword %1
push word %2
regnull
pop bx
pop eax
%endmacro

%macro read_argswb 2
regsave
push word %1
push word %2
regnull
pop bx
pop ax
%endmacro

%macro read_argsbb 2
regsave
push byte %1
push word %2
regnull
pop bx
pop al
%endmacro
