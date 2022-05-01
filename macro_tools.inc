%macro macro_args_read_near 0-8
mov _word [args_tmp+rsize*0],_word 0
mov _word [args_tmp+rsize*1],_word 0
mov _word [args_tmp+rsize*2],_word 0
mov _word [args_tmp+rsize*3],_word 0
%assign __args__w 0
%rep %0/2
	%1 %+ mov [args_tmp+rsize*__args__w],%2
	%rotate 2
	%assign __args__w __args__w+1
%endrep
pushad
mov _ax,[args_tmp+rsize*0]
mov _bx,[args_tmp+rsize*1]
mov _cx,[args_tmp+rsize*2]
mov _dx,[args_tmp+rsize*3]
mov _si,0
mov _di,0
mov _bp,0
%endmacro

%macro macro_args_save_near 0-8
mov [args_tmp+rsize*0],_ax
mov [args_tmp+rsize*1],_bx
mov [args_tmp+rsize*2],_cx
mov [args_tmp+rsize*3],_dx
%assign __args__w 0
popad
%rep %0/2
	%1 %+ mov %2,[args_tmp+rsize*__args__w]
	%rotate 2
	%assign __args__w __args__w+1
%endrep
%endmacro

%macro macro_args_con 1-9
%rotate 1
%if %0==1
	%1
%elif %0==3
	%3 %1,%2
%elif %0==5
	%5 %1,%3,%2,%4
%elif %0==7
	%7 %1,%4,%2,%5,%3,%6
%elif %0==9
	%9 %1,%5,%2,%6,%3,%7,%4,%8
%endif
%endmacro

%macro macro_args_read 1+
macro_args_con macro_args_read_near,%1
%endmacro

%macro macro_args_save 1+
macro_args_con macro_args_save_near,%1
%endmacro

%macro macro_args_read 0
macro_args_con macro_args_read_near
%endmacro

%macro macro_args_save 0
macro_args_con macro_args_save_near
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro regout 0
push %%_1
push _word __LINE__
push _word [esp_base]
jmp macro_regout
%%_1:
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; %macro pushbw 1
; push word 0
; mov [esp+1],al
; mov al,byte %1
; mov [esp],al
; mov al,[esp+1]
; mov [esp+1],byte 0
; %endmacro

; %macro popbw 1
; mov [esp+1],al
; mov al,[esp]
; mov byte %1,al
; %ifnidni %1,al
; %ifnidni %1,byte al
; %ifnidni %1,byte byte al
; %ifnidni %1,byte byte byte al
; %ifnidni %1,byte byte byte byte al
; %ifnidni %1,byte byte byte byte byte al
; %ifnidni %1,byte byte byte byte byte byte al
; %ifnidni %1,byte byte byte byte byte byte byte al
; mov al,[esp+1]
; %endif
; %endif
; %endif
; %endif
; %endif
; %endif
; %endif
; %endif
; mov [esp+1],byte 0
; add esp,2
; %endmacro

; %macro regsave 0
; push eax
; push ebx
; push ecx
; push edx
; %endmacro

; %macro regload 0
; pop edx
; pop ecx
; pop ebx
; pop eax
; %endmacro

; %macro regnull 0
; mov eax,0
; mov ebx,0
; mov ecx,0
; mov edx,0
; %endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; %include "macro_args_read.inc"
; %include "macro_args_save.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro macro_cmp_q 4
push _word %3
macro_args_read q,q, %1,%2
cmp rax,rbx
%4 %%_jmp
macro_args_save
add _sp,rsize
jmp %%_end
%%_jmp:
macro_args_save
add _sp,rsize
jmp [_sp-rsize]
%%_end:
%endmacro

%macro macro_cmp_d 4
push _word %3
macro_args_read d,d, %1,%2
cmp eax,ebx
%4 %%_jmp
macro_args_save
add _sp,rsize
jmp %%_end
%%_jmp:
macro_args_save
add _sp,rsize
jmp [_sp-rsize]
%%_end:
%endmacro

%macro macro_cmp_w 4
push _word %3
macro_args_read __args__w,__args__w, %1,%2
cmp ax,bx
%4 %%_jmp
macro_args_save
add _sp,rsize
jmp %%_end
%%_jmp:
macro_args_save
add _sp,rsize
jmp [_sp-rsize]
%%_end:
%endmacro

%macro macro_cmp_b 4
push _word %3
macro_args_read b,b, %1,%2
cmp al,bl
%4 %%_jmp
macro_args_save
add _sp,rsize
jmp %%_end
%%_jmp:
macro_args_save
add _sp,rsize
jmp [_sp-rsize]
%%_end:
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro macro_call 0-5
%if %0>1
	_push %2
%else
	_push 0
%endif
%if %0>2
	_push %3
%else
	_push 0
%endif
%if %0>3
	_push %4
%else
	_push 0
%endif
%if %0>4
	_push %5
%else
	_push 0
%endif
call %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; %macro macro_duput_eax 0
; mov ebx,10
; mov edi,eax

; %%_1:
; inc ecx
; div ebx
; mov edx,0
; cmp eax,0
; jne %%_1

; mov esi,ecx
; mov edx,0
; mov eax,1

; %%_2:
; push eax
; mul ebx
; loop %%_2

; mov ecx,esi
; mov eax,edi

; %%_3:
; pop ebx
; mov edx,0
; div ebx
; add eax,48
; cput al
; mov eax,edx
; loop %%_3
; %endmacro

; %macro macro_print_call 1
; _ %+ %1:
; push eax
; add esp,4
; pop eax
; sub esp,8
; %1 eax
; pop eax
; add esp,8
; jmp dword [esp-4]
; %endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; %macro macro_duput 1
; macro_args_read_d %1
; macro_duput_eax
; macro_args_save_
; %endmacro

; %macro macro_wuput 1
; macro_args_read_d %1
; macro_duput_eax
; macro_args_save_
; %endmacro

; %macro macro_buput 1
; macro_args_read_d %1
; macro_duput_eax
; macro_args_save_
; %endmacro

; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; %macro macro_dsput 1
; macro_args_read_d %1
; cmp eax,0
; jge %%_1
; cput '-'
; neg eax
; %%_1:
; macro_duput_eax
; macro_args_save_
; %endmacro

; %macro macro_wsput 1
; macro_args_read_d %1
; movsx eax,ax
; dsput eax
; macro_args_save_
; %endmacro

; %macro macro_bsput 1
; macro_args_read_d %1
; movsx eax,al
; dsput eax
; macro_args_save_
; %endmacro

; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; %macro macro_cput 1
; macro_args_read_d %1
; pushbw al
; mov eax,4
; mov ebx,1
; mov ecx,esp
; mov edx,1
; int 0x80
; add esp,2
; macro_args_save_
; %endmacro

; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; %macro macro_duprint 1
; duput %1
; cput 10
; %endmacro

; %macro macro_wuprint 1
; macro_args_read_d %1
; macro_duput_eax
; macro_args_save_
; cput 10
; %endmacro

; %macro macro_buprint 1
; macro_args_read_d %1
; macro_duput_eax
; macro_args_save_
; cput 10
; %endmacro

; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; %macro macro_dsprint 1
; dsput %1
; cput 10
; %endmacro

; %macro macro_wsprint 1
; macro_args_read_d %1
; movsx eax,ax
; dsput eax
; macro_args_save_
; cput 10
; %endmacro

; %macro macro_bsprint 1
; macro_args_read_d %1
; movsx eax,al
; dsput eax
; macro_args_save_
; cput 10
; %endmacro

; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; %macro macro_duwrite 1
; duput %1
; cput 32
; %endmacro

; %macro macro_wuwrite 1
; macro_args_read_d %1
; macro_duput_eax
; macro_args_save_
; cput 32
; %endmacro

; %macro macro_buwrite 1
; macro_args_read_d %1
; macro_duput_eax
; macro_args_save_
; cput 32
; %endmacro

; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; %macro macro_dswrite 1
; dsput %1
; cput 32
; %endmacro

; %macro macro_wswrite 1
; macro_args_read_d %1
; movsx eax,ax
; dsput eax
; macro_args_save_
; cput 32
; %endmacro

; %macro macro_bswrite 1
; macro_args_read_d %1
; movsx eax,al
; dsput eax
; macro_args_save_
; cput 32
; %endmacro

; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; %macro macro_cprint 1
; macro_args_read_d %1
; cput al
; macro_args_save_
; cput 10
; %endmacro

; %macro macro_cwrite 1
; macro_args_read_d %1
; cput al
; macro_args_save_
; cput 32
; %endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro macro_args_offset 1
macro_args_read
mov _ax,_sp
macro_args_read _, _ax
sub _ax,_sp
macro_args_save _, _ax
macro_args_save _, %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro aput 1
%defstr %%str %1
sput %%str
%endmacro

%macro awrite 1
%defstr %%str %1
swrite %%str
%endmacro

%macro aprint 1
%defstr %%str %1
sprint %%str
%endmacro
