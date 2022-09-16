


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; best_io.inc ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   best input/output library for nasm
;   up-to-date version: https://vk.cc/cfB1SZ
;   contact me:
;       tatarinov.gp@phystech.edu
;       https://twitter.com/sudo_gera
;       https://github.com/sudo-gera
;       https://vk.com/sudo_gera
;       https://t.me/sudo_gera



;;;;;;;;;;;;;;;;;;;;;;;;;;;; this library supports ;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   32-bit mode                 nasm -felf32 FILE.asm -o a.o && ld -m elf_i386   a.o && ./a.out
;   64-bit mode (without gcc)   nasm -felf64 FILE.asm -o a.o && ld -m elf_x86_64 a.o && ./a.out
;   64-bit mode (with gcc)      nasm -felf64 FILE.asm -o a.o && gcc -no-pie      a.o && ./a.out



;;;;;;;;;;;;;;;;;;;;;;;;;;;; this library provides ;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   putstr begin,end
;   getstr begin,end
;       - put or get strings from memory [BEGIN,END), (c++ style)
;         getstr will read string into given range until it reaches END or \n
;         in case of \n getstr puts \n into buffer and leaves other bytes unchanged
;   putcstr (quoted string)
;       - put given string
;   putchar (char)
;   getchar (location)
;       - put or get single char
;   putsbyte (int)
;   putubyte (int)
;   getbyte (location)
;       - put signed or unsigned or get one byte int
;   putsword (int)
;   putuword (int)
;   getword (location)
;       - same, but works with word int, instead of byte int
;   putsword (int)
;   putuword (int)
;   getword (location)
;       - same, but dword int
;   putsword (int)
;   putuword (int)
;   getword (location)
;       - same, but qword int (only when 64 bit)
;
;       - get(intsize) can read multiple numbers from one string (like cin in c++)
;       - get(intsize) is universal for signed and unsigned values
;       - get(intsize) will read and delete all symbols before digits (but minus sign matters)
;       - get(intsize) will also read and delete one byte after last digit
;       - put(s|u)(intsize|char) can correctly print expressions with esp|rsp, but only without stack_unsafe
;           intsize means one of byte,word,dword,qword
;
;   start
;       - starts programm (when linked without gcc)
;   start gcc
;       - starts programm (when linked with gcc)
;   stop (int)
;       - stops programm with given return code
;   stop
;       - stops programm (return code 0)
;
;   putreg
;       - print all registers and line number, where putreg was called
;       - (for debugging printreg is better)
;
;   putchar, putreg, putuword... won't put new line or space after calling
;   but they have print* forms (printchar, printreg, printuword...) which print \n at the end
;   for example,
;       printuword [eax]
;   is same as
;       putuword [eax]
;       putchar 10
;   aslo they have write* form which prints space at the end
;
;   all macros work normally even if esp|rsp is invalid, for example, if esp|rsp is nullptr
;   to disable this feature, add '%define stack_unsafe' line before including best_io.inc.
;   disabling this feature will make almost all macros significantly smaller
;   it is useful when trying to put lots of code into loop commad (but only if stack is ok)



;;;;;;;;;;;;;;;;;;;;;;;;;;;;        example        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;
%if 0 ; begin multiline comment (you should delete this line when trying example)
    ; you can copy this example into other file and run in any arch, but without gcc
    %include "best_io.inc"
    section .data
        somestring db 'hello'
        freespace times 64 db ' ' ; 64 spaces
        someint dd 256+44 ; = 300
    section .text
        start
        ; this code is not optimal way to do things.
        ; it just shows how to use macros.
        ; print hello world:
        putstr    somestring,freespace ; will put 'hello' (without quotes)
        ; freespace is located to the right of 'hello'
        ; so freespace pointer points to end of somestring
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
        getstr    freespace,someint ; now freespace is equal to your name
        putstr    somestring,freespace ; will print 'hello'
        putchar   [someint] ; chr(44) is ','
        putchar   ' '
        putstr    freespace,someint
        putchar   10 ; new line
        putcstr   'what is your age?',10
        getdword  [someint] ; now someint is equal to your age
        putcstr     'your age is '
        printudword [someint]
        stop
%endif ; end multiline comment (you should delete this line when trying example)



;;;;;;;;;;;;;;;;;;;;;;;;;;;;      source code      ;;;;;;;;;;;;;;;;;;;;;;;;;;;;
%if __BITS__ ==  64
;   x86_64 or AMD64
    %define __best__max_word qword
    %define __best__max_d    dq
    %define __best__max_register(x) r %+ x ; __best__max_register(ax) is rax
    %define __best__reg_size 8
    %define __best__max_r 'r'
%else
;   x86 or i386
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
__best__fake_stack __best__max_d __best__fake_stack,0
; macros will work even if esp|rsp is invalid

%ifndef stack_unsafe
    %define stack_unsafe xchg __best__max_sp,[__best__fake_stack]
    %define __best__save_ax mov [__best__fake_stack+__best__reg_size],__best__max_ax
    %define __best__recover_ax mov __best__max_ax,[__best__fake_stack+__best__reg_size]
%else
    %define __best__save_ax push __best__max_ax
    %define __best__recover_ax pop __best__max_ax
%endif

section .text

%macro __best__arch_select 2 ; selecting command depending on arch
    %if __BITS__ == 64
        %2
    %else
        %1
    %endif
%endmacro

%macro __best__start_ 2-* ; name, number of return places, how to read args
    %1:
    %rep %2
        push __best__max_word [__best__max_sp] ; allocating place on stack for return values
    %endrep
    db 'PQRSTUVW' ; push all registers to stack (binary code insertion)
    %rep (%0-2)/2
        mov %3,[__best__max_sp+(8+%4)*__best__reg_size] ; reading arguments
        %rotate 2
    %endrep
%endmacro

%macro __best__stop_ 1-* ; how to save return values, number of arguments
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

%macro __best__put_get_str_ 2 ; name,1 if write, 0 if read
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

__best__start_ __best__putuint,0,__best__max_ax,1 ; put unsigned int
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

__best__start_ __best__putsint,0,__best__max_ax,1 ; put signed int
    cmp __best__max_ax,0
    jge __best__33
        push __best__max_word '-'
        call __best__putchar
        neg __best__max_ax
    __best__33:
    push __best__max_ax
    call __best__putuint
__best__stop_ 1

__best__start_ __best__getint,1 ; get signed or unsigned int
    mov __best__max_ax,0
    mov __best__max_bx,0
    mov __best__max_cx,0
    push word 0
    mov cl,10
    __best__70:
        call __best__getchar_s
        mov bl,byte [__best__max_sp]
        sub bl,48
        cmp bl,253
        jne __best__30
            mov byte [__best__max_sp+1],1
        __best__30:
        cmp bl,9
        ja __best__70
        jmp __best__71
    __best__32:
        call __best__getchar_s
        mov bl,byte [__best__max_sp]
        sub bl,48
        __best__71:
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
    db __best__max_r,'bp == ',__best__max_r,'sp == ',            'line == 0'
__best__putreg_stack_pos:
    __best__max_d __best__reg_size*0,__best__reg_size*18,__best__reg_size*3,__best__reg_size*2,__best__reg_size*0
    __best__max_d __best__reg_size*1,__best__reg_size*5 ,__best__reg_size*6,__best__reg_size*4,__best__reg_size*7

section .text
__best__start_ __best__put_reg,0 ; put all registers
    mov __best__max_cx,9
    mov __best__max_dx,__best__fake_stack
    sub __best__max_dx,__best__max_sp
    cmp __best__max_dx,16*16*16*16
    jae __best__51
        mov __best__max_ax,[__best__fake_stack]
        mov __best__max_word[__best__max_sp+__best__reg_size*3],__best__max_ax
    jmp __best__50
    __best__51:
        add __best__max_word[__best__max_sp+__best__reg_size*3],__best__reg_size*15
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
    push __best__max_word 32
    call __best__putchar
__best__stop_ 1

__best__start_ __best__putreg,0
    call __best__put_reg
__best__stop_ 1

__best__movzx_dword_to_qword:
    __best__arch_select,{shl rax,32}
    __best__arch_select,{shr rax,32}
ret


__best__call_putint_for_sbyte: ; output from ax
    cbw
__best__call_putint_for_sword:
    cwde
__best__call_putint_for_sdword:
    __best__arch_select,cdqe
__best__call_putint_for_sqword:
    push __best__max_ax
    call __best__putsint
ret

__best__call_putint_for_ubyte:
    shl __best__max_ax,__BITS__-8
    shr __best__max_ax,__BITS__-8
__best__call_putint_for_uword:
    shl __best__max_ax,__BITS__-16
    shr __best__max_ax,__BITS__-16
__best__call_putint_for_udword:
    shl __best__max_ax,__BITS__-32
    shr __best__max_ax,__BITS__-32
__best__call_putint_for_uqword:
    push __best__max_ax
    call __best__putuint
ret

__best__call_putchar:
    push __best__max_ax
    call __best__putsint
ret

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

%macro __best__sized_put_ 4 ; form of ax, end char, what to call, what to print
    %%begin %+ %3: ; for disassembling
    __best__save_ax
    ; mov __best__max_ax,0
    mov %1,%4 ; moving given value to form of ax of same size (al,ax,eax,rax)
    stack_unsafe
    call %3
    %if %2 ; if end char not 0
        push __best__max_word %2
        call __best__putchar
    %endif
    stack_unsafe
    __best__recover_ax
    %%end %+ %3: ; for disassembling
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

%define getstr      __best__begin_end_        0,__best__getstr,
%define getchar     __best__sized_get_  byte, 8,__best__getchar,
%define getbyte     __best__sized_get_  byte, 8,__best__getint,
%define getword     __best__sized_get_  word,16,__best__getint,
%define getdword    __best__sized_get_ dword,32,__best__getint,
%define getqword    __best__sized_get_ qword,64,__best__getint,

%define putstr      __best__begin_end_        0,__best__putstr,
%define putchar     __best__sized_put_    al, 0,__best__call_putchar,
%define putsbyte    __best__sized_put_    al, 0,__best__call_putint_for_sbyte,
%define putsword    __best__sized_put_    ax, 0,__best__call_putint_for_sword,
%define putsdword   __best__sized_put_   eax, 0,__best__call_putint_for_sdword,
%define putsqword   __best__sized_put_   rax, 0,__best__call_putint_for_sqword,
%define putubyte    __best__sized_put_    al, 0,__best__call_putint_for_ubyte,
%define putuword    __best__sized_put_    ax, 0,__best__call_putint_for_uword,
%define putudword   __best__sized_put_   eax, 0,__best__call_putint_for_udword,
%define putuqword   __best__sized_put_   rax, 0,__best__call_putint_for_uqword,

%define printstr    __best__begin_end_       10, __best__putstr,
%define printchar   __best__sized_put_    al,10,__best__call_putchar,
%define printsbyte  __best__sized_put_    al,10,__best__call_putint_for_sbyte,
%define printsword  __best__sized_put_    ax,10,__best__call_putint_for_sword,
%define printsdword __best__sized_put_   eax,10,__best__call_putint_for_sdword,
%define printsqword __best__sized_put_   rax,10,__best__call_putint_for_sqword,
%define printubyte  __best__sized_put_    al,10,__best__call_putint_for_ubyte,
%define printuword  __best__sized_put_    ax,10,__best__call_putint_for_uword,
%define printudword __best__sized_put_   eax,10,__best__call_putint_for_udword,
%define printuqword __best__sized_put_   rax,10,__best__call_putint_for_uqword,

%define writestr    __best__begin_end_       32, __best__putstr,
%define writechar   __best__sized_put_    al,32,__best__call_putchar,
%define writesbyte  __best__sized_put_    al,32,__best__call_putint_for_sbyte,
%define writesword  __best__sized_put_    ax,32,__best__call_putint_for_sword,
%define writesdword __best__sized_put_   eax,32,__best__call_putint_for_sdword,
%define writesqword __best__sized_put_   rax,32,__best__call_putint_for_sqword,
%define writeubyte  __best__sized_put_    al,32,__best__call_putint_for_ubyte,
%define writeuword  __best__sized_put_    ax,32,__best__call_putint_for_uword,
%define writeudword __best__sized_put_   eax,32,__best__call_putint_for_udword,
%define writeuqword __best__sized_put_   rax,32,__best__call_putint_for_uqword,

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




