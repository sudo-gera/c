%macro regout 0
sput "eax == "
cput 27
sput "[32m"
dsput eax
cput 27
sput "[0m"

cput 9

sput "ebx == "
cput 27
sput "[32m"
dsput ebx
cput 27
sput "[0m"

cput 9

sput "ecx == "
cput 27
sput "[32m"
dsput ecx
cput 27
sput "[0m"

cput 9

sput "edx == "
cput 27
sput "[32m"
dsput edx
cput 27
sput "[0m"

cput 9

sput " esi == "
cput 27
sput "[32m"
dsput esi
cput 27
sput "[0m"

cput 9

sput " edi == "
cput 27
sput "[32m"
dsput edi
cput 27
sput "[0m"

cput 9

sput " ebp == "
cput 27
sput "[32m"
dsput ebp
cput 27
sput "[0m"

cput 9

sput " esp == "
cput 27
sput "[32m"
sub [esp_base],esp
neg dword [esp_base]
dsput [esp_base]
neg dword [esp_base]
add [esp_base],esp
cput 27
sput "[0m"

cput 10
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
%ifnidni %1,al
%ifnidni %1,byte al
%ifnidni %1,byte byte al
%ifnidni %1,byte byte byte al
%ifnidni %1,byte byte byte byte al
%ifnidni %1,byte byte byte byte byte al
%ifnidni %1,byte byte byte byte byte byte al
%ifnidni %1,byte byte byte byte byte byte byte al
mov al,[esp+1]
%endif
%endif
%endif
%endif
%endif
%endif
%endif
%endif
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
cmp al,bl
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

