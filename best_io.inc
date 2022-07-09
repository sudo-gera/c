;;;;;;;;;;;;;;;;;;;;;;;;;;;; this library supports ;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 	32-bit mode                 nasm -felf   FILE.asm -o a.o && ld -m elf_i386 a.o && ./a.out
; 	64-bit mode (without gcc)   nasm -felf64 FILE.asm -o a.o && ld             a.o && ./a.out
; 	64-bit mode (with gcc)      nasm -felf64 FILE.asm -o a.o && gcc -no-pie    a.o && ./a.out


;;;;;;;;;;;;;;;;;;;;;;;;;;;; this library provides ;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 	putstr begin,end
; 	getstr begin,end
; 		- put or get strings from memory [BEGIN,END), (c++ style)
; 		  getstr will read string into given range until it reaches END or \n
; 		  in case of \n getstr puts \n into buffer and leaves other bytes unchanged
; 	putcstr (quoted string)
; 		- put given string
; 	putchar (char)
; 	getchar (location)
; 		- put or get single char
; 	putsbyte (int)
; 	putubyte (int)
; 	getbyte (location)
; 		- put signed or unsigned or get one byte int
; 		- getbyte can read multiple numbers from one string (like cin in c++)
; 		- getbyte is universal for signed and unsigned values
; 	putsword (int)
; 	putuword (int)
; 	getword (location)
; 		- same, but works with word int, instead of byte int
; 	putsword (int)
; 	putuword (int)
; 	getword (location)
; 		- same, but dword int
; 	putsword (int)
; 	putuword (int)
; 	getword (location)
; 		- same, but qword int (only when 64 bit)
; 
; 	start
; 		- starts programm (when linked without gcc)
; 	start gcc
; 		- starts programm (when linked with gcc)
; 	stop (int)
; 		- stops programm with given return code
; 	stop
; 		- stops programm (return code 0)
; 
; 	putreg
; 		- print all registers and line number, where putreg was called
; 		- (for debugging printreg is better)
; 
; 	putchar, putreg, putuword... won't put new line or space after calling
; 	but they have print* forms (printchar, printreg, printuword...) which print \n at the end
; 	for example,
; 		printuword [eax]
; 	is same as
; 		putuword [eax]
; 		putchar 10
; 	aslo they have write* form which prints space at the end
; 
; 	all macros work normally even if esp|rsp is invalid
; 	to disable this feature, add '%define stack_unsafe' line before including __best__io.inc.
; 	disabling this feature will make almost all macros significantly smaller
; 	useful when trying to put lots of code into loop commad (but only if stack is ok)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;        example        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;
%if 0 ; multiline comment
	; you can copy this example into other file and run
	%include "best_io.inc"
	section .data
		somestring db 'hello'
		emptystr db '                              ' ; 30 spaces
		someint dd 256+44 ; = 300
	section .text
		start
		; this code is not optimal way to do things
		; it just shows as much as posible
		; print hello world:
		putstr    somestring,emptystr ; will put 'hello' (without quotes)
		; emptystr is located to the right of 'hello'
		; so emptystr pointer points to end of somestring
		putcstr   ' world' ; will put ' world' (without quotes)
		putchar   10 ; will put enter
		; print hello world (again)
		putcstr   'hello world',10
		; print some numbers
		putubyte  [someint] ; 44
		putchar   10 ; new line
		putubyte  [someint+1] ; 1
		putchar   10 ; new line
		putuword  [someint] ; 300
		putchar   10 ; new line
		putuword  [someint+1] ; 1
		putchar   10 ; new line
		printudword [someint] ; 300 with new line
		putcstr   'what is your name?',10
		getstr    emptystr,someint ; now emptystr is equal to your name
		; don't worry, your name is not empty :)
		putstr    somestring,emptystr ; will print 'hello'
		putchar   [someint] ; chr(44) is ','
		putchar   ' '
		putstr    emptystr,someint
		putchar   10 ; new line
		putcstr   'what is your age?',10
		getdword  [someint] ; now someint is equal to your age
		putcstr  'your age is '
		printudword [someint]
		stop
%endif

;;;;;;;;;;;;;;;;;;;;;;;;;;;;      source code      ;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%if __BITS__ ==  64
; 	x86_64 or AMD64
	%define __best__max_word qword
	%define __best__max_d    dq
	%define __best__max_register(x) r %+ x ; __best__max_register(ax) is rax
	%define __best__reg_size 8
	%define __best__max_r 'r'
%else
; 	x86 or i386
	%define __best__max_word dword
	%define __best__max_d    dd
	%define __best__max_register(x) e %+ x ; __best__max_register(ax) is eax
	%define __best__reg_size 4
	%define __best__max_r 'e'
%endif

%define __best__max_ax __best__max_register(ax)
%define __best__max_bx __best__max_register(bx)
%define __best__max_cx __best__max_register(cx)
%define __best__max_dx __best__max_register(dx)
%define __best__max_si __best__max_register(si)
%define __best__max_di __best__max_register(di)
%define __best__max_bp __best__max_register(bp)
%define __best__max_sp __best__max_register(sp)

section .data
align 16,db 0
times 16*16*16*16 db 0
__best__fake_stack __best__max_d __best__fake_stack
; macros will work even if esp|rsp is invalid

%ifndef stack_unsafe
	%define stack_unsafe xchg __best__max_sp,[__best__fake_stack]
%endif

section .text

%macro __best__arch_select 2 ; selecting command depending on arch
	%if __BITS__ == 64
		%2
	%else
		%1
	%endif
%endmacro

%macro __best__start_ 2-*
	%1:
	%rep %2
		push __best__max_word [__best__max_sp] ; allocating place on stack for return values
	%endrep
	db 'PQRSTUVW' ; push all registers to stack (binary code insertion)
	%rep (%0-2)/2
		mov %3,[__best__max_sp+(8+%4)*__best__reg_size]
		%rotate 2
	%endrep
%endmacro

%macro __best__stop_ 1-*
	%rep (%0-1)/2
		mov [__best__max_sp+(8+%1)*__best__reg_size],%2
		%rotate 2
	%endrep
	db '_^]X[ZYX' ; pop all registers from stack (binary code insertion)
	%rep %1
		pop __best__max_word [__best__max_sp] ; deleting arguments from stack
	%endrep
	ret
%endmacro

%macro __best__put_get_str_ 2 ; 1 if write, 0 if read
	__best__start_ %1,0,__best__max_cx,2,__best__max_dx,1
		sub __best__max_dx,__best__max_cx
		__best__arch_select {mov eax, 3 + %2},{mov rax,%2}
		__best__arch_select {mov ebx, 2 - %2},{mov rdi,%2}
		mov __best__max_si,__best__max_cx
		__best__arch_select {int 0x80},{syscall}
	__best__stop_ 2
%endmacro

__best__put_get_str_ __best__putstr,1

__best__put_get_str_ __best__getstr,0

%macro __best__put_get_char_ 1 ; 1 if write, 0 if read
	push __best__max_sp
	add __best__max_word [__best__max_sp],__best__reg_size
	push __best__max_sp
	add __best__max_word [__best__max_sp],__best__reg_size*2+1
	call __best__putstr*%1+__best__getstr*(1-%1)
	ret
%endmacro

__best__putchar_s: __best__put_get_char_ 1

__best__getchar_s: __best__put_get_char_ 0

__best__start_ __best__putchar,0,__best__max_ax,1
	push __best__max_ax
	call __best__putchar_s
	add __best__max_sp,__best__reg_size
__best__stop_ 1

__best__start_ __best__getchar,1
	push __best__max_word 0
	call __best__getchar_s
	pop __best__max_ax
__best__stop_ 1,__best__max_ax,0

__best__start_ __best__putuint,0,__best__max_ax,1
	mov __best__max_bx,__best__max_sp
	mov __best__max_bp,__best__max_sp
	sub __best__max_sp,80
	mov __best__max_dx,0
	mov __best__max_di,10
	mov cx,20
	__best__20:
		div __best__max_di
		add dl,48
		dec __best__max_bx
		mov [__best__max_bx],dl
		mov dx,0
		cmp __best__max_ax,0
	loopne __best__20
	push __best__max_bx
	push __best__max_bp
	call __best__putstr
	add __best__max_sp,80
__best__stop_ 1

__best__start_ __best__putsint,0,__best__max_ax,1
	cmp __best__max_ax,0
	jge __best__33
		push __best__max_word '-'
		call __best__putchar
		neg __best__max_ax
	__best__33:
	push __best__max_ax
	call __best__putuint
__best__stop_ 1

__best__start_ __best__getint,1
	mov __best__max_ax,0
	mov __best__max_bx,0
	mov __best__max_cx,0
	push word 0
	mov cl,10
	__best__32:
		call __best__getchar_s
		mov bl,byte [__best__max_sp]
		sub bl,48
		cmp bl,253
		jne __best__30
			mov byte [__best__max_sp+1],1
			mov bl,0
		__best__30:
		cmp bl,9
		ja __best__31
		mul __best__max_cx
		add __best__max_ax,__best__max_bx
		jmp __best__32
	__best__31:
	mov bl,0
	cmp [__best__max_sp+1],bl
	je __best__18
		neg __best__max_ax
	__best__18:
	add __best__max_sp,2
__best__stop_ 1,__best__max_ax,0


section .data
__best__putreg_names_pos __best__max_d 64,56,49,42,35,28,21,14,7,0
__best__putreg_names:
	db __best__max_r,'ax == ',__best__max_r,'bx == ',__best__max_r,'cx == ',
	db __best__max_r,'dx == ',__best__max_r,'si == ',__best__max_r,'di == ',
	db __best__max_r,'bp == ',__best__max_r,'sp == line == 0'
__best__putreg_stack_pos:
	__best__max_d __best__reg_size*0,__best__reg_size*18,__best__reg_size*3,__best__reg_size*2,__best__reg_size*0
	__best__max_d __best__reg_size*1,__best__reg_size*5 ,__best__reg_size*6,__best__reg_size*4,__best__reg_size*7

section .text
__best__start_ __best__put_reg,0
	add __best__max_word[__best__max_sp+__best__reg_size*3],__best__reg_size*15
	mov __best__max_cx,9
	__best__50:
		push __best__max_word [__best__putreg_names_pos+__best__max_cx*__best__reg_size]
		add __best__max_word[__best__max_sp],__best__putreg_names
		push __best__max_word [__best__putreg_names_pos-__best__reg_size+__best__reg_size*__best__max_cx]
		add __best__max_word[__best__max_sp],__best__putreg_names
		call __best__putstr
		mov __best__max_ax,[__best__putreg_stack_pos+__best__max_cx*__best__reg_size]
		mov __best__max_ax,[__best__putreg_stack_pos+__best__max_cx*__best__reg_size]
		add __best__max_ax,__best__max_sp
		push __best__max_word[__best__max_ax]
		call __best__putsint
		push __best__max_word 9
		call __best__putchar
	loop __best__50
__best__stop_ 0

__best__start_ __best__printreg,0
	call __best__put_reg
	push __best__max_word 10
	call __best__putchar
__best__stop_ 1

__best__start_ __best__writereg,0
	call __best__put_reg
	push __best__max_word 10
	call __best__putchar
__best__stop_ 1

__best__start_ __best__putreg,0
	call __best__put_reg
__best__stop_ 1

%macro __best__begin_end_ 4 ; end char, what to call, begin, end
	%%begin %+ %2: ; for disassembling
	stack_unsafe
	push __best__max_word %3
	push __best__max_word %4
	call %2
	%if %1
		push __best__max_word %1
		call __best__putchar
	%endif
	stack_unsafe
	%%end %+ %2: ; for disassembling
%endmacro

%macro __best__sized_put_ 5 ; form of ax, mov[sz]x, end char, what to call, what to print
	%%begin %+ %4: ; for disassembling
	stack_unsafe
	push __best__max_ax
	mov %1,%5 ; moving given value to form of ax of same size (al,ax,eax,rax)
	%ifnidni %1,__best__max_ax
		%2 __best__max_ax,%1 ; mov[sz]x
	%endif
	push __best__max_ax
	call %4
	pop __best__max_ax
	%if %3 ; if end char not 0
		push __best__max_word %3
		call __best__putchar
	%endif
	stack_unsafe
	%%end %+ %4: ; for disassembling
%endmacro

%macro __best__sized_get_ 4 ; _word modifer, size in bits, what to call, where to store
	%%begin %+ %3: ; for disassembling
	stack_unsafe
	call %3
	%if %2==8 || %2==32 && __BITS__==64 ; no pop command with this size
		%rep %2 ; swap bit-by-bit
		rcl %1 [__best__max_sp],1
		rcl %1 %4,1
		%endrep
		rcl %1 [__best__max_sp],1
		add __best__max_sp,__best__reg_size
	%else
		pop %1 %4
		add __best__max_sp,__best__reg_size-%2/8
	%endif
	stack_unsafe
	%%end %+ %3: ; for disassembling
%endmacro

%macro __best__putcstr_end 2+
	%%begin_putcstr: ; for disassembling
	jmp %%__best__end
	%%__best__begin:
	db %2
	%if %1
		db %1 ; last char
	%endif
	%%__best__end:
	putstr %%__best__begin,%%__best__end
	%%end_putcstr: ; for disassembling
%endmacro

%macro __best__out_reg 1
	%%begin_putreg: ; for disassembling
	stack_unsafe
	push __best__max_word __LINE__
	call %1
	stack_unsafe
	%%end_putreg: ; for disassembling
%endmacro

%define getstr      __best__begin_end_            0, __best__getstr,
%define getchar     __best__sized_get_      byte, 8,__best__getchar,
%define getbyte     __best__sized_get_      byte, 8, __best__getint,
%define getword     __best__sized_get_      word,16, __best__getint,
%define getdword    __best__sized_get_     dword,32, __best__getint,
%define getqword    __best__sized_get_     qword,64, __best__getint,

%define putstr      __best__begin_end_            0, __best__putstr,
%define putchar     __best__sized_put_ al, movzx, 0,__best__putchar,
%define putsbyte    __best__sized_put_ al, movsx, 0,__best__putsint,
%define putsword    __best__sized_put_ ax, movsx, 0,__best__putsint,
%define putsdword   __best__sized_put_ eax,movsx, 0,__best__putsint,
%define putsqword   __best__sized_put_ rax,movsx, 0,__best__putsint,
%define putubyte    __best__sized_put_ al, movzx, 0,__best__putuint,
%define putuword    __best__sized_put_ ax, movzx, 0,__best__putuint,
%define putudword   __best__sized_put_ eax,movzx, 0,__best__putuint,
%define putuqword   __best__sized_put_ rax,movzx, 0,__best__putuint,

%define printstr    __best__begin_end_           10, __best__putstr,
%define printchar   __best__sized_put_ al, movzx,10,__best__putchar,
%define printsbyte  __best__sized_put_ al, movsx,10,__best__putsint,
%define printsword  __best__sized_put_ ax, movsx,10,__best__putsint,
%define printsdword __best__sized_put_ eax,movsx,10,__best__putsint,
%define printsqword __best__sized_put_ rax,movsx,10,__best__putsint,
%define printubyte  __best__sized_put_ al, movzx,10,__best__putuint,
%define printuword  __best__sized_put_ ax, movzx,10,__best__putuint,
%define printudword __best__sized_put_ eax,movzx,10,__best__putuint,
%define printuqword __best__sized_put_ rax,movzx,10,__best__putuint,

%define writestr    __best__begin_end_           32, __best__putstr,
%define writechar   __best__sized_put_ al, movzx,32,__best__putchar,
%define writesbyte  __best__sized_put_ al, movsx,32,__best__putsint,
%define writesword  __best__sized_put_ ax, movsx,32,__best__putsint,
%define writesdword __best__sized_put_ eax,movsx,32,__best__putsint,
%define writesqword __best__sized_put_ rax,movsx,32,__best__putsint,
%define writeubyte  __best__sized_put_ al, movzx,32,__best__putuint,
%define writeuword  __best__sized_put_ ax, movzx,32,__best__putuint,
%define writeudword __best__sized_put_ eax,movzx,32,__best__putuint,
%define writeuqword __best__sized_put_ rax,movzx,32,__best__putuint,

%define putcstr __best__putcstr_end 0,
%define printcstr __best__putcstr_end 10,
%define writecstr __best__putcstr_end 32,

%define putreg __best__out_reg __best__putreg
%define printreg __best__out_reg __best__printreg
%define writereg __best__out_reg __best__writereg

%macro start 0-1
	%%begin_start: ; for disassembling
	section .text
	%if %0
		global main
		main:
	%else
		global _start
		_start:
	%endif
	mov __best__max_ax,0
	mov __best__max_bx,0
	mov __best__max_cx,0
	mov __best__max_dx,0
	mov __best__max_si,0
	mov __best__max_di,0
	mov __best__max_bp,0
	%%end_start: ; for disassembling
%endmacro

%macro stop 0-1 0
	%%begin_stop: ; for disassembling
	__best__arch_select {mov eax,1}, {mov rax,60}
	__best__arch_select {mov ebx,%1},{mov rdi,%1}
	__best__arch_select {int 0x80},  {syscall}
	%%end_stop: ; for disassembling
%endmacro




