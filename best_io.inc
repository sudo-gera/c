%assign max_args 32

%macro stop 0-1 0
mov eax,1
mov ebx,%1
int 0x80
%endmacro

%macro multiput 1-*
%define __best_modificator1 %2
%define __best_modificator2 %3
%rep %0-3
%rotate -1
__best_modificator1
__best_modificator2 %1
%endrep
%rotate -3
call (%1)+(%0-3)*2
%undef __best_modificator1
%undef __best_modificator2
%endmacro

%macro __best_moval 1
mov al,%1
%endmacro

%macro __best_alr 0
mov ax,[esp-40]
%endmacro

%macro __best_strp 0
mov ecx,[edx]
add [edx],ebx
mov edx,ecx
sub edx,4
mov ecx,0
%endmacro

%macro __best_byte_get 0
mov eax,edi
cmp ah,0
je %%_1
	mov eax,0
	mov esi,[esp+8]
	mov al,[esi-2]
%%_1:
%endmacro

%macro __best_byte_set 0
mov ah,1
mov edi,eax
%endmacro

%define duput multiput __best_duput,nop,push dword,
%define dsput multiput __best_dsput,nop,push dword,
%define wuput multiput __best_wuput,nop,push word,
%define wsput multiput __best_wsput,nop,push word,
%define buput multiput __best_buput,push ax,__best_moval,
%define bsput multiput __best_bsput,push ax,__best_moval,
%define cput  multiput __best_cput, push ax,__best_moval,

%define duwrite multiput __best_duwrite,nop,push dword,
%define dswrite multiput __best_dswrite,nop,push dword,
%define wuwrite multiput __best_wuwrite,nop,push word,
%define wswrite multiput __best_wswrite,nop,push word,
%define buwrite multiput __best_buwrite,push ax,__best_moval,
%define bswrite multiput __best_bswrite,push ax,__best_moval,
%define cwrite  multiput __best_cwrite, push ax,__best_moval,

%define duprint multiput __best_duprint,nop,push dword,
%define dsprint multiput __best_dsprint,nop,push dword,
%define wuprint multiput __best_wuprint,nop,push word,
%define wsprint multiput __best_wsprint,nop,push word,
%define buprint multiput __best_buprint,push ax,__best_moval,
%define bsprint multiput __best_bsprint,push ax,__best_moval,
%define cprint  multiput __best_cprint, push ax,__best_moval,

%macro sput 1
call __best_sput+(%%_2-%%_1)*2
%%_1:
db %1
%%_2:
%endmacro

%macro swrite 1
call __best_swrite+(%%_2-%%_1)*2
%%_1:
db %1
%%_2:
%endmacro

%macro sprint 1
call __best_sprint+(%%_2-%%_1)*2
%%_1:
db %1
%%_2:
%endmacro

%macro __best_multiple 6
%rep max_args
push dword 0
%endrep
push dword max_args
pushfd
pushad
mov edi,0
mov ah,0
mov di,ax
mov eax,esp
add eax,36
mov ecx,[eax]
add eax,4
%%_1:
cmp [eax],dword 0
jne %%_2
	dec ecx
	add eax,4
jmp %%_1
%%_2:
mov ebx,ecx
mov edx,eax
%4
pushad
mov ecx,ebx
add edx,4
%%__1:
cmp ecx,1
jl %%__2
	push dword edx
	push dword [edx]
	mov eax,[edx]
	call %2
	add esp,8
	add edx,%1
dec ecx
cmp ecx,1
jl %%__2
	%if %5
		cput %5
	%endif
jmp %%__1
%%__2:
%if %6
cput %6
%endif
popad
mov ebx,ecx
mov edx,eax
inc ecx
%%_4:
add edx,%1
loop %%_4
sub edx,%1
mov ebp,[edx+2]
mov ecx,ebx
mov esi,[eax]
mov [edx],esi
mov eax,edx
sub eax,36
mov edi,eax
mov esi,esp
cld
mov ecx,36
mov ebx,ecx
rep movsb
mov esp,eax
push ebp
add esp,4
popad
popfd
%3
ret
%endmacro

