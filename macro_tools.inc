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
mov [esp+1],byte 0
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

%macro macro_call 1-5
%if %0>1
	push dword %2
%else
	push dword 0
%endif
%if %0>2
	push dword %3
%else
	push dword 0
%endif
%if %0>3
	push dword %4
%else
	push dword 0
%endif
%if %0>4
	push dword %5
%else
	push dword 0
%endif
push dword %%_1
jmp func_ %+ %1
%%_1:
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro macro_duput_eax 0
mov ebx,10
mov edi,eax

%%_1:
inc ecx
div ebx
mov edx,0
cmp eax,0
jne %%_1

mov esi,ecx
mov edx,0
mov eax,1

%%_2:
push eax
mul ebx
loop %%_2

mov ecx,esi
mov eax,edi

%%_3:
pop ebx
mov edx,0
div ebx
add eax,48
cput al
mov eax,edx
loop %%_3
%endmacro

%macro macro_print_call 1
_ %+ %1:
push eax
add esp,4
pop eax
sub esp,8
%1 eax
pop eax
add esp,8
jmp dword [esp-4]
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro macro_duput 1
macro_args_read_d %1
macro_duput_eax
macro_args_save_
%endmacro

%macro macro_wuput 1
macro_args_read_d %1
macro_duput_eax
macro_args_save_
%endmacro

%macro macro_buput 1
macro_args_read_d %1
macro_duput_eax
macro_args_save_
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro macro_dsput 1
macro_args_read_d %1
cmp eax,0
jge %%_1
cput '-'
neg eax
%%_1:
macro_duput_eax
macro_args_save_
%endmacro

%macro macro_wsput 1
macro_args_read_d %1
movsx eax,ax
dsput eax
macro_args_save_
%endmacro

%macro macro_bsput 1
macro_args_read_d %1
movsx eax,al
dsput eax
macro_args_save_
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro macro_cput 1
macro_args_read_d %1
pushbw al
mov eax,4
mov ebx,1
mov ecx,esp
mov edx,1
int 0x80
add esp,2
macro_args_save_
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro macro_duprint 1
duput %1
cput 10
%endmacro

%macro macro_wuprint 1
macro_args_read_d %1
macro_duput_eax
macro_args_save_
cput 10
%endmacro

%macro macro_buprint 1
macro_args_read_d %1
macro_duput_eax
macro_args_save_
cput 10
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro macro_dsprint 1
dsput %1
cput 10
%endmacro

%macro macro_wsprint 1
macro_args_read_d %1
movsx eax,ax
dsput eax
macro_args_save_
cput 10
%endmacro

%macro macro_bsprint 1
macro_args_read_d %1
movsx eax,al
dsput eax
macro_args_save_
cput 10
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro macro_duwrite 1
duput %1
cput 32
%endmacro

%macro macro_wuwrite 1
macro_args_read_d %1
macro_duput_eax
macro_args_save_
cput 32
%endmacro

%macro macro_buwrite 1
macro_args_read_d %1
macro_duput_eax
macro_args_save_
cput 32
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro macro_dswrite 1
dsput %1
cput 32
%endmacro

%macro macro_wswrite 1
macro_args_read_d %1
movsx eax,ax
dsput eax
macro_args_save_
cput 32
%endmacro

%macro macro_bswrite 1
macro_args_read_d %1
movsx eax,al
dsput eax
macro_args_save_
cput 32
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro macro_cprint 1
macro_args_read_d %1
cput al
macro_args_save_
cput 10
%endmacro

%macro macro_cwrite 1
macro_args_read_d %1
cput al
macro_args_save_
cput 32
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro macro_args_offset 1
macro_args_read_
mov eax,esp
macro_args_read_d eax
sub eax,esp
macro_args_save_d eax
macro_args_save_d %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

