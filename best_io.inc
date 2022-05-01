; %if __BITS__ == 32
%assign max_args 32

%macro multiput 1-*
%define __best_modificator %2
%rep %0-2
%rotate -1
__best_modificator %1
%endrep
%rotate -2
call (%1)+(%0-2)*2
%undef __best_modificator
%endmacro

%macro multiget 1-*
%define __best_modificator %2
call (%1)+(%0-2)*2
%rep %0-2
%rotate -1
__best_modificator %1
%endrep
%rotate -2
%undef __best_modificator
%endmacro

%macro __best__sign 1
%rep rsize-%1
shl _ax,8
%endrep
cmp _ax,0
jge %%_1
	cput '-'
	neg _ax
%%_1:
%rep rsize-%1
shr _ax,8
%endrep
%endmacro

%define _uput _ %+ uput
%define _sput _ %+ sput

%define quput multiput __best_quput,qpush,
%define qsput multiput __best_qsput,qpush,
%define duput multiput __best_duput,dpush,
%define dsput multiput __best_dsput,dpush,
%define wuput multiput __best_wuput,wpush,
%define wsput multiput __best_wsput,wpush,
%define buput multiput __best_buput,bpush,
%define bsput multiput __best_bsput,bpush,
%define cput  multiput __best_cput, bpush,

%define _uwrite _ %+ uwrite
%define _swrite _ %+ swrite

%define quwrite multiput __best_quwrite,qpush,
%define qswrite multiput __best_qswrite,qpush,
%define duwrite multiput __best_duwrite,dpush,
%define dswrite multiput __best_dswrite,dpush,
%define wuwrite multiput __best_wuwrite,wpush,
%define wswrite multiput __best_wswrite,wpush,
%define buwrite multiput __best_buwrite,bpush,
%define bswrite multiput __best_bswrite,bpush,
%define cwrite  multiput __best_cwrite, bpush,

%define _uprint _ %+ uprint
%define _sprint _ %+ sprint

%define quprint multiput __best_quprint,qpush,
%define qsprint multiput __best_qsprint,qpush,
%define duprint multiput __best_duprint,dpush,
%define dsprint multiput __best_dsprint,dpush,
%define wuprint multiput __best_wuprint,wpush,
%define wsprint multiput __best_wsprint,wpush,
%define buprint multiput __best_buprint,bpush,
%define bsprint multiput __best_bsprint,bpush,
%define cprint  multiput __best_cprint, bpush,

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

%macro sput 1
call __best_sput+(%%_2-%%_1)*2
%%_1:
db %1
%%_2:
%endmacro

%macro count_args 0
%%_1:
cmp _word [_sp+rsize], _word 0
jne %%_2
dec _word [_sp]
pop _word [_sp]
jmp %%_1
%%_2:
%endmacro

%macro __best_strp 0
mov _dx,[_sp+(8+1)*rsize]
add [_sp+(8+1)*rsize],_cx
mov _cx,0
%endmacro

%macro __best_multiple 7
%rep max_args
push _word 0
%endrep
push _word max_args
count_args
pushad
mov _cx,[_sp+8*rsize]
mov _dx,_sp
add _dx,(8+2)*rsize
mov _bx,_cx
%5
pushad
mov _cx,_bx

%%_2:
cmp _cx,1
jl %%_1
mov _ax,0
mov _ax,[_dx]
%rep rsize-%1
shl _ax,8
%endrep
%rep rsize-%1
shr _ax,8
%endrep
call %3
add _dx,%1
dec _cx
cmp _cx,1
jl %%_1
%if %6
	cput %6
%endif
jmp %%_2
%%_1:
%if %7
	cput %7
%endif

popad

mov _ax,_cx
mov _bx,%1
mul _bx

mov _bx,_sp
mov _si,_bx
mov _di,_bx
add _di,_ax
mov _cx,rsize*(8+2)
add _di,_cx
add _si,_cx
dec _di
dec _si
std
rep movsb
cld

add _sp,_ax
popad
add _sp,rsize

ret


%endmacro

; %else;;;;;;;;;;;;;;;;;;;;;;;;;;

; extern printf
; extern scanf

section .data
__quprint db '%d',10,0
__quget db '%d',0
__quvar8 dq 0
__cprint db '%c',10,0
__cput db '%c',0

%macro scan_f 2
pushad
sub rsp,4096
jmp %%_2
%%_1:
db %1,0
%%_2:
push qword 0
mov rsi,__quvar8
mov rdi,%%_1
mov rax,0
call scanf
add rsp,4096
popad
push qword [__quvar8]
pop qword %2
%endmacro

%macro print_f 1-2
pushad
sub rsp,4096
jmp %%_2
%%_1:
db %1,0
%%_2:
%if %0>1
mov rsi,%2
%endif
mov rdi,%%_1
mov rax,0
call printf
add rsp,4096
popad
%endmacro

; %macro qsget 1
; macro_args_read
; push rax
; mov rax,rsp
; scan_f "%li",rax
; pop rax
; macro_args_save q,%1
; %endmacro

%macro _quprint 1
macro_args_read q,%1
xchg rax,rbx
print_f {27,"[34m%lu",27,"[0m",10},rbx
macro_args_save
%endmacro

%macro _quwrite 1
macro_args_read q,%1
xchg rax,rbx
print_f {27,"[34m%lu",27,"[0m",32},rbx
macro_args_save
%endmacro

%macro _quput 1
macro_args_read q,%1
xchg rax,rbx
print_f {27,"[34m%lu",27,"[0m"},rbx
macro_args_save
%endmacro

%macro _qsput 1
macro_args_read q,%1
xchg rax,rbx
print_f {27,"[34m%li",27,"[0m"},rbx
macro_args_save
%endmacro

%macro _qswrite 1
macro_args_read q,%1
xchg rax,rbx
print_f {27,"[34m%li",27,"[0m",32},rbx
macro_args_save
%endmacro

%macro _qsprint 1
macro_args_read q,%1
xchg rax,rbx
print_f {27,"[34m%li",27,"[0m",10},rbx
macro_args_save
%endmacro

%macro _cput 1
macro_args_read b,%1
xchg rax,rbx
print_f {27,"[34m%c",27,"[0m"},rbx
macro_args_save
%endmacro

%macro _sput 1
jmp %%_2
%%_1:
db %1,0
%%_2:
print_f {27,"[34m%s",27,"[0m"},%%_1
%endmacro


; %macro duput 1
; macro_args_read d,%1
; movzx rbx,eax
; print_f "%lu",rbx
; macro_args_save
; %endmacro

; %macro dsput 1
; macro_args_read d,%1
; movsx rbx,eax
; print_f "%li",rbx
; macro_args_save
; %endmacro

; %macro wuput 1
; macro_args_read w,%1
; movzx rbx,ax
; print_f "%lu",rbx
; macro_args_save
; %endmacro

; %macro wsput 1
; macro_args_read w,%1
; movsx rbx,ax
; print_f "%li",rbx
; macro_args_save
; %endmacro

; %macro buput 1
; macro_args_read b,%1
; movzx rbx,al
; print_f "%lu",rbx
; macro_args_save
; %endmacro

; %macro bsput 1
; macro_args_read b,%1
; movsx rbx,al
; print_f "%li",rbx
; macro_args_save
; %endmacro

%define _uput _ %+ uput
%define _sput _ %+ sput
%define _uprint _ %+ uprint
%define _sprint _ %+ sprint
%define _uwrite _ %+ uwrite
%define _swrite _ %+ swrite












; %endif
