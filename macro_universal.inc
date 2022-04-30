%if __BITS__ == 64
	%define rsize 8
	%define _word qword
	%define _ax rax
	%define _bx rbx
	%define _cx rcx
	%define _dx rdx
	%define _si rsi
	%define _di rdi
	%define _bp rbp
	%define _sp rsp
	%define d_ dq
	%define res_ resq
	%define _ q
	%macro pushad 0
		mov [ad_tmp],_sp
		push _ax
		push _cx
		push _dx
		push _bx
		push _word [ad_tmp]
		push _bp
		push _si
		push _di
	%endmacro
	%macro popad 0
		pop _di
		pop _si
		pop _bp
		add _sp,rsize
		pop _bx
		pop _dx
		pop _cx
		pop _ax
	%endmacro
%else
	%define rsize 4
	%define _word dword
	%define _ax eax
	%define _bx ebx
	%define _cx ecx
	%define _dx edx
	%define _si esi
	%define _di edi
	%define _bp ebp
	%define _sp esp
	%define d_ dd
	%define res_ resd
	%define _ d
%endif

%macro macro_restore 3
%ifnidni %1,%3
%ifnidni %1,%2 %3
%ifnidni %1,%2 %2 %3
%ifnidni %1,%2 %2 %2 %3
%ifnidni %1,%2 %2 %2 %2 %3
%ifnidni %1,%2 %2 %2 %2 %2 %3
%ifnidni %1,%2 %2 %2 %2 %2 %2 %3
%ifnidni %1,%2 %2 %2 %2 %2 %2 %2 %3
mov _ax,[mov_tmp]
%endif
%endif
%endif
%endif
%endif
%endif
%endif
%endif
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro bmov 2
mov [mov_tmp],_ax
mov al,%2
mov %1,al
macro_restore %1,byte,al
%endmacro

%macro wmov 2
mov [mov_tmp],_ax
mov ax,%2
mov %1,ax
macro_restore %1,word,ax
%endmacro

%if __BITS__==32
	%macro dmov 2
	dpush %2
	dpop %1
	%endmacro
%else
	%macro dmov 2
	mov [mov_tmp],_ax
	mov eax,%2
	mov %1,eax
	macro_restore %1,dword,eax
	%endmacro

	; %macro qmov 2
	; mov [mov_tmp],_ax
	; mov rax,%2
	; mov %1,rax
	; macro_restore %1,qword,rax
	; %endmacro

	%macro qmov 2
	qpush %2
	qpop %1
	%endmacro
%endif


%define _mov _ %+ mov

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro bpush 1
mov [_sp-1],byte 0
bmov [_sp-2],%1
sub _sp,2
%endmacro

%macro wpush 1
wmov [_sp-2],%1
sub _sp,2
%endmacro

%if __BITS__==32
	%macro dpush 1
	push dword %1
	%endmacro
%else

	%macro dpush 1
	dmov [_sp-4],%1
	sub _sp,4
	%endmacro

	%macro qpush 1
	push qword %1
	%endmacro
%endif

	; %macro qpush 1
	; qmov [_sp-8],%1
	; sub _sp,8
	; %endmacro

%define _push _ %+ push

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro bpop 1
add _sp,2
bmov %1,[_sp-2]
%endmacro

%macro wpop 1
add _sp,2
wmov %1,[_sp-2]
%endmacro

%if __BITS__==32
	%macro dpop 1
	pop dword %1
	%endmacro
%else

	%macro dpop 1
	add _sp,4
	dmov %1,[_sp-4]
	%endmacro

	; %macro qpop 1
	; add _sp,8
	; qmov %1,[_sp-8]
	; %endmacro

	%macro qpop 1
	pop qword %1
	%endmacro
%endif



%define _pop _ %+ pop

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

















