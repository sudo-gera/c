%macro regout 0
PRINT "eax == "
PUTCHAR 27
PRINT "[32m"
SIGNINT eax
PUTCHAR 27
PRINT "[0m"

PUTCHAR 9

PRINT "ebx == "
PUTCHAR 27
PRINT "[32m"
SIGNINT ebx
PUTCHAR 27
PRINT "[0m"

PUTCHAR 9

PRINT "ecx == "
PUTCHAR 27
PRINT "[32m"
SIGNINT ecx
PUTCHAR 27
PRINT "[0m"

PUTCHAR 9

PRINT "edx == "
PUTCHAR 27
PRINT "[32m"
SIGNINT edx
PUTCHAR 27
PRINT "[0m"

PUTCHAR 9

PRINT " esi == "
PUTCHAR 27
PRINT "[32m"
SIGNINT esi
PUTCHAR 27
PRINT "[0m"

PUTCHAR 9

PRINT " edi == "
PUTCHAR 27
PRINT "[32m"
SIGNINT edi
PUTCHAR 27
PRINT "[0m"

PUTCHAR 9

PRINT " ebp == "
PUTCHAR 27
PRINT "[32m"
SIGNINT ebp
PUTCHAR 27
PRINT "[0m"

PUTCHAR 9

PRINT " esp == "
PUTCHAR 27
PRINT "[32m"
sub [esp_base],esp
neg dword [esp_base]
SIGNINT [esp_base]
neg dword [esp_base]
add [esp_base],esp
PUTCHAR 27
PRINT "[0m"

PUTCHAR 10
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro pushbw 1
push word 0
mov [esp+1],al
mov al,byte %1
mov [esp],al
mov al,[esp+1]
mov [esp+1],byte 0
%endmacro

%macro popbw 1
mov [esp+1],al
mov al,[esp]
mov byte %1,al
mov al,[esp+1]
add esp,2
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

%macro macro_cmp_d 4
push dword %3
macro_args_read_dd %1,%2
cmp eax,ebx
%4 %%_jmp
macro_args_save_
add esp,4
jmp %%_end
%%_jmp:
macro_args_save_
add esp,4
jmp dword [esp-4]
%%_end:
%endmacro

%macro macro_cmp_w 4
push dword %3
macro_args_read_ww %1,%2
cmp ax,bx
%4 %%_jmp
macro_args_save_
add esp,4
jmp %%_end
%%_jmp:
macro_args_save_
add esp,4
jmp dword [esp-4]
%%_end:
%endmacro

%macro macro_cmp_b 4
push dword %3
macro_args_read_bb %1,%2
cmp ax,bx
%4 %%_jmp
macro_args_save_
add esp,4
jmp %%_end
%%_jmp:
macro_args_save_
add esp,4
jmp dword [esp-4]
%%_end:
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

