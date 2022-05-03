%define macro
%macro alld 0
a times 1024 d_ 0
b times 1024 d_ 0
c times 1024 d_ 0
d times 1024 d_ 0
e times 1024 d_ 0
f times 1024 d_ 0
g times 1024 d_ 0
h times 1024 d_ 0
i times 1024 d_ 0
j times 1024 d_ 0
k times 1024 d_ 0
l times 1024 d_ 0
m times 1024 d_ 0
n times 1024 d_ 0
o times 1024 d_ 0
p times 1024 d_ 0
q times 1024 d_ 0
r times 1024 d_ 0
s times 1024 d_ 0
t times 1024 d_ 0
u times 1024 d_ 0
v times 1024 d_ 0
w times 1024 d_ 0
x times 1024 d_ 0
y times 1024 d_ 0
z times 1024 d_ 0
%endmacro

%macro pre_start 0
global _start
global main
section .data
args_tmp times 4 d_ 0
ad_tmp d_ 0
mov_tmp d_ 0
alld
esp_base d_ 0
ch_val d_ 0
section .data
vars_names times 100003 d_ 0
len_vars_names d_ 100003
operators d_ '+','-','*','/','%','(',')','<','>','<=','>=','==','!=','&&','||','[',']','=','+=','-=','*=','/=','%='
len_operators d_ 23
%endmacro

%macro start 0
section .text
_start:
main:
mov [esp_base],_sp
var a
var b
var c
var d
var e
var f
var g
var h
var i
var j
var k
var l
var m
var n
var o
var p
var q
var r
var s
var t
var u
var v
var w
var x
var y
var z
%endmacro

%macro begin 0
%push main
start
jmp %%_start
%$__jup:
cmp [esp_base],_sp
je %%_2
sprint "warning: stack not empty"
%%_2:
stop
jmp %$__jdown
%%_start:
%endmacro

%macro stop 0-1 0
mov _ax,1
mov _bx,%1
int 0x80
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%include "best_io.inc"
%include "macro_tools.inc"
%include "macro_usual.inc"
%include "macro_universal.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; %macro dmov 2
; macro_args_read d, %2
; macro_args_save d, %1
; %endmacro

; %macro wmov 2
; macro_args_read w, %2
; macro_args_save w, %1
; %endmacro

; %macro bmov 2
; macro_args_read b, %2
; macro_args_save b, %1
; %endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _xchg _ %+ xchg

%macro qxchg 2
macro_args_read q,q, %2,%1
macro_args_save q,q, %1,%2
%endmacro

%macro dxchg 2
macro_args_read d,d, %2,%1
macro_args_save d,d, %1,%2
%endmacro

%macro wxchg 2
macro_args_read w,w, %2,%1
macro_args_save w,w, %1,%2
%endmacro

%macro bxchg 2
macro_args_read b,b, %2,%1
macro_args_save b,b, %1,%2
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _add _ %+ add

%macro qadd 3
macro_args_read q,q, %2,%3
add rax,rbx
macro_args_save q, %1
%endmacro

%macro dadd 3
macro_args_read d,d, %2,%3
add eax,ebx
macro_args_save d, %1
%endmacro

%macro wadd 3
macro_args_read w,w, %2,%3
add ax,bx
macro_args_save w, %1
%endmacro

%macro badd 3
macro_args_read b,b, %2,%3
add al,bl
macro_args_save b, %1
%endmacro

%macro qadd 2
macro_args_read q,q, %1,%2
add rax,rbx
macro_args_save q, %1
%endmacro

%macro dadd 2
macro_args_read d,d, %1,%2
add eax,ebx
macro_args_save d, %1
%endmacro

%macro wadd 2
macro_args_read w,w, %1,%2
add ax,bx
macro_args_save w, %1
%endmacro

%macro badd 2
macro_args_read b,b, %1,%2
add al,bl
macro_args_save b, %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _sub _ %+ sub

%macro qsub 3
macro_args_read q,q, %2,%3
sub rax,rbx
macro_args_save q, %1
%endmacro

%macro dsub 3
macro_args_read d,d, %2,%3
sub eax,ebx
macro_args_save d, %1
%endmacro

%macro wsub 3
macro_args_read w,w, %2,%3
sub ax,bx
macro_args_save w, %1
%endmacro

%macro bsub 3
macro_args_read b,b, %2,%3
sub al,bl
macro_args_save b, %1
%endmacro

%macro qsub 2
macro_args_read q,q, %1,%2
sub rax,rbx
macro_args_save q, %1
%endmacro

%macro dsub 2
macro_args_read d,d, %1,%2
sub eax,ebx
macro_args_save d, %1
%endmacro

%macro wsub 2
macro_args_read w,w, %1,%2
sub ax,bx
macro_args_save w, %1
%endmacro

%macro bsub 2
macro_args_read b,b, %1,%2
sub al,bl
macro_args_save b, %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _mul _ %+ mul

%macro qmul 3
macro_args_read q,q, %2,%3
mul rbx
macro_args_save q, %1
%endmacro

%macro dmul 3
macro_args_read d,d, %2,%3
mul ebx
macro_args_save d, %1
%endmacro

%macro wmul 3
macro_args_read w,w, %2,%3
mul bx
macro_args_save w, %1
%endmacro

%macro bmul 3
macro_args_read b,b, %2,%3
mul bl
macro_args_save b, %1
%endmacro

%macro qmul 2
macro_args_read q,q, %1,%2
mul rbx
macro_args_save q, %1
%endmacro

%macro dmul 2
macro_args_read d,d, %1,%2
mul ebx
macro_args_save d, %1
%endmacro

%macro wmul 2
macro_args_read w,w, %1,%2
mul bx
macro_args_save w, %1
%endmacro

%macro bmul 2
macro_args_read b,b, %1,%2
mul bl
macro_args_save b, %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _udiv _ %+ udiv

%macro qudiv 3
macro_args_read q,q, %2,%3
div rbx
macro_args_save q, %1
%endmacro

%macro dudiv 3
macro_args_read d,d, %2,%3
div ebx
macro_args_save d, %1
%endmacro

%macro wudiv 3
macro_args_read w,w, %2,%3
div bx
macro_args_save w, %1
%endmacro

%macro budiv 3
macro_args_read b,b, %2,%3
div bl
macro_args_save b, %1
%endmacro

%macro qudiv 2
macro_args_read q,q, %1,%2
div rbx
macro_args_save d, %1
%endmacro

%macro dudiv 2
macro_args_read d,d, %1,%2
div ebx
macro_args_save d, %1
%endmacro

%macro wudiv 2
macro_args_read w,w, %1,%2
div bx
macro_args_save w, %1
%endmacro

%macro budiv 2
macro_args_read b,b, %1,%2
div bl
macro_args_save b, %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _sdiv _ %+ sdiv

%macro qsdiv 3
macro_args_read q,q, %2,%3
cqo
idiv rbx
macro_args_save q, %1
%endmacro

%macro dsdiv 3
macro_args_read d,d, %2,%3
cdq
idiv ebx
macro_args_save d, %1
%endmacro

%macro wsdiv 3
macro_args_read w,w, %2,%3
cwd
idiv bx
macro_args_save w, %1
%endmacro

%macro bsdiv 3
macro_args_read b,b, %2,%3
cbw
idiv bl
macro_args_save b, %1
%endmacro

%macro qsdiv 2
macro_args_read q,q, %1,%2
cqo
idiv rbx
macro_args_save q, %1
%endmacro

%macro dsdiv 2
macro_args_read d,d, %1,%2
cdq
idiv ebx
macro_args_save d, %1
%endmacro

%macro wsdiv 2
macro_args_read w,w, %1,%2
cwd
idiv bx
macro_args_save w, %1
%endmacro

%macro bsdiv 2
macro_args_read b,b, %1,%2
cbw
idiv bl
macro_args_save b, %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _umod _ %+ umod

%macro qumod 3
macro_args_read q,q, %2,%3
div rbx
mov rax,rdx
macro_args_save q, %1
%endmacro

%macro dumod 3
macro_args_read d,d, %2,%3
div ebx
mov eax,edx
macro_args_save d, %1
%endmacro

%macro wumod 3
macro_args_read w,w, %2,%3
div bx
mov ax,dx
macro_args_save w, %1
%endmacro

%macro bumod 3
macro_args_read b,b, %2,%3
div bl
mov al,ah
macro_args_save b, %1
%endmacro

%macro qumod 2
macro_args_read q,q, %1,%2
div rbx
mov rax,rdx
macro_args_save q, %1
%endmacro

%macro dumod 2
macro_args_read d,d, %1,%2
div ebx
mov eax,edx
macro_args_save d, %1
%endmacro

%macro wumod 2
macro_args_read w,w, %1,%2
div bx
mov ax,dx
macro_args_save w, %1
%endmacro

%macro bumod 2
macro_args_read b,b, %1,%2
div bl
mov al,ah
macro_args_save b, %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _smod _ %+ smod

%macro qsmod 3
macro_args_read q,q, %2,%3
cqo
idiv rbx
mov rax,rdx
macro_args_save q, %1
%endmacro

%macro dsmod 3
macro_args_read d,d, %2,%3
cdq
idiv ebx
mov eax,edx
macro_args_save d, %1
%endmacro

%macro wsmod 3
macro_args_read w,w, %2,%3
cwd
idiv bx
mov ax,dx
macro_args_save w, %1
%endmacro

%macro bsmod 3
macro_args_read b,b, %2,%3
cbw
idiv bl
mov al,ah
macro_args_save b, %1
%endmacro

%macro qsmod 2
macro_args_read q,q, %1,%2
cqo
idiv rbx
mov rax,rdx
macro_args_save q, %1
%endmacro

%macro dsmod 2
macro_args_read d,d, %1,%2
cdq
idiv ebx
mov eax,edx
macro_args_save d, %1
%endmacro

%macro wsmod 2
macro_args_read w,w, %1,%2
cwd
idiv bx
mov ax,dx
macro_args_save w, %1
%endmacro

%macro bsmod 2
macro_args_read b,b, %1,%2
cbw
idiv bl
mov al,ah
macro_args_save b, %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _udivmod _ %+ udivmod

%macro qudivmod 4
macro_args_read q,q, %3,%4
div rbx
mov rbx,rdx
macro_args_save q,q, %1,%2
%endmacro

%macro dudivmod 4
macro_args_read d,d, %3,%4
div ebx
mov ebx,edx
macro_args_save d,d, %1,%2
%endmacro

%macro wudivmod 4
macro_args_read w,w, %3,%4
div bx
mov bx,dx
macro_args_save w,w, %1,%2
%endmacro

%macro budivmod 4
macro_args_read b,b, %3,%4
div bl
mov bl,ah
macro_args_save b,b, %1,%2
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _sdivmod _ %+ sdivmod

%macro qsdivmod 4
macro_args_read q,q, %3,%4
cqo
idiv rbx
mov rbx,rdx
macro_args_save q,q, %1,%2
%endmacro

%macro dsdivmod 4
macro_args_read d,d, %3,%4
cdq
idiv ebx
mov ebx,edx
macro_args_save d,d, %1,%2
%endmacro

%macro wsdivmod 4
macro_args_read w,w, %3,%4
cwd
idiv bx
mov bx,dx
macro_args_save w,w, %1,%2
%endmacro

%macro bsdivmod 4
macro_args_read b,b, %3,%4
cbw
idiv bl
mov bl,ah
macro_args_save b,b, %1,%2
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _slt _ %+ slt

%macro qslt 3
macro_cmp_q %1,%2,%3,jl
%endmacro

%macro dslt 3
macro_cmp_d %1,%2,%3,jl
%endmacro

%macro wslt 3
macro_cmp_w %1,%2,%3,jl
%endmacro

%macro bslt 3
macro_cmp_b %1,%2,%3,jl
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _sle _ %+ sle

%macro qsle 3
macro_cmp_q %1,%2,%3,jle
%endmacro

%macro dsle 3
macro_cmp_d %1,%2,%3,jle
%endmacro

%macro wsle 3
macro_cmp_w %1,%2,%3,jle
%endmacro

%macro bsle 3
macro_cmp_b %1,%2,%3,jle
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _sgt _ %+ sgt

%macro qsgt 3
macro_cmp_q %1,%2,%3,jg
%endmacro

%macro dsgt 3
macro_cmp_d %1,%2,%3,jg
%endmacro

%macro wsgt 3
macro_cmp_w %1,%2,%3,jg
%endmacro

%macro bsgt 3
macro_cmp_b %1,%2,%3,jg
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _sge _ %+ sge

%macro qsge 3
macro_cmp_q %1,%2,%3,jge
%endmacro

%macro dsge 3
macro_cmp_d %1,%2,%3,jge
%endmacro

%macro wsge 3
macro_cmp_w %1,%2,%3,jge
%endmacro

%macro bsge 3
macro_cmp_b %1,%2,%3,jge
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _eq _ %+ eq

%macro qeq 3
macro_cmp_q %1,%2,%3,je
%endmacro

%macro deq 3
macro_cmp_d %1,%2,%3,je
%endmacro

%macro weq 3
macro_cmp_w %1,%2,%3,je
%endmacro

%macro beq 3
macro_cmp_b %1,%2,%3,je
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _ne _ %+ ne

%macro qne 3
macro_cmp_q %1,%2,%3,jne
%endmacro

%macro dne 3
macro_cmp_d %1,%2,%3,jne
%endmacro

%macro wne 3
macro_cmp_w %1,%2,%3,jne
%endmacro

%macro bne 3
macro_cmp_b %1,%2,%3,jne
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _ult _ %+ ult

%macro qult 3
macro_cmp_q %1,%2,%3,jb
%endmacro

%macro dult 3
macro_cmp_d %1,%2,%3,jb
%endmacro

%macro wult 3
macro_cmp_w %1,%2,%3,jb
%endmacro

%macro bult 3
macro_cmp_b %1,%2,%3,jb
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _ule _ %+ ule

%macro qule 3
macro_cmp_q %1,%2,%3,jbe
%endmacro

%macro dule 3
macro_cmp_d %1,%2,%3,jbe
%endmacro

%macro wule 3
macro_cmp_w %1,%2,%3,jbe
%endmacro

%macro bule 3
macro_cmp_b %1,%2,%3,jbe
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _uge _ %+ uge

%macro qugt 3
macro_cmp_q %1,%2,%3,ja
%endmacro

%macro dugt 3
macro_cmp_d %1,%2,%3,ja
%endmacro

%macro wugt 3
macro_cmp_w %1,%2,%3,ja
%endmacro

%macro bugt 3
macro_cmp_b %1,%2,%3,ja
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _uge _ %+ uge

%macro quge 3
macro_cmp_q %1,%2,%3,jae
%endmacro

%macro duge 3
macro_cmp_d %1,%2,%3,jae
%endmacro

%macro wuge 3
macro_cmp_w %1,%2,%3,jae
%endmacro

%macro buge 3
macro_cmp_b %1,%2,%3,jae
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _neg _ %+ neg

%macro qneg 1
neg qword %1
%endmacro

%macro dneg 1
neg dword %1
%endmacro

%macro wneg 1
neg word %1
%endmacro

%macro bneg 1
neg byte %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _inc _ %+ inc

%macro qinc 1
inc qword %1
%endmacro

%macro dinc 1
inc dword %1
%endmacro

%macro winc 1
inc word %1
%endmacro

%macro binc 1
inc byte %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _dec _ %+ dec

%macro qdec 1
dec qword %1
%endmacro

%macro ddec 1
dec dword %1
%endmacro

%macro wdec 1
dec word %1
%endmacro

%macro bdec 1
dec byte %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _array _ %+ array

%macro qarray 1
section .data
len_ %+ %1 dd 0
size_ %+ %1 dd 8
%1 times 1024 dq 0
section .text
%endmacro

%macro darray 1
section .data
len_ %+ %1 dd 0
size_ %+ %1 dd 4
%1 times 1024 dd 0
section .text
%endmacro

%macro warray 1
section .data
len_ %+ %1 dd 0
size_ %+ %1 dd 2
%1 times 1024 dw 0
section .text
%endmacro

%macro barray 1
section .data
len_ %+ %1 dd 0
size_ %+ %1 dd 1
%1 times 1024 db 0
section .text
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _aget _ %+ aget

%macro qaget 3
macro_args_read _,_, %2,%3
lea _bx,[_ax+_bx*8]
mov rax,[_bx]
macro_args_save q, %1
%endmacro

%macro daget 3
macro_args_read _,_, %2,%3
lea _bx,[_ax+_bx*4]
mov eax,[_bx]
macro_args_save d, %1
%endmacro

%macro waget 3
macro_args_read _,_, %2,%3
lea _bx,[_ax+_bx*2]
mov ax,[_bx]
macro_args_save w, %1
%endmacro

%macro baget 3
macro_args_read _,_, %2,%3
lea _bx,[_ax+_bx*1]
mov al,[_bx]
macro_args_save b, %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _aput _ %+ aput

%macro qaput 3
macro_args_read _,_,q, %1,%2,%3
lea _bx,[_ax+_bx*4]
mov [_bx],rcx
macro_args_save
%endmacro

%macro daput 3
macro_args_read _,_,d, %1,%2,%3
lea _bx,[_ax+_bx*4]
mov [_bx],ecx
macro_args_save
%endmacro

%macro waput 3
macro_args_read _,_,w %1,%2,%3
lea _bx,[_ax+_bx*2]
mov [_bx],cx
macro_args_save
%endmacro

%macro baput 3
macro_args_read _,_,b %1,%2,%3
lea _bx,[_ax+_bx*1]
mov [_bx],cl
macro_args_save
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _apush _ %+ apush

%macro qapush 2
macro_args_read _,q, %1,%2
qaput _ax,[_ax-8],rbx
_inc [_ax-8]
macro_args_save
%endmacro

%macro dapush 2
macro_args_read _,d, %1,%2
daput _ax,[_ax-8],ebx
_inc [_ax-8]
macro_args_save
%endmacro

%macro wapush 2
macro_args_read _,w, %1,%2
waput _ax,[_ax-8],bx
_inc [_ax-8]
macro_args_save
%endmacro

%macro bapush 2
macro_args_read _,b, %1,%2
baput _ax,[_ax-8],bl
_inc [_ax-8]
macro_args_save
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _apop _ %+ apop

%macro qapop 2
macro_args_read _, %2
_dec [_ax-8]
qaget rax,_ax,[_ax-8]
macro_args_save d, %1
%endmacro

%macro dapop 2
macro_args_read _, %2
_dec [_ax-8]
daget eax,_ax,[_ax-8]
macro_args_save d, %1
%endmacro

%macro wapop 2
macro_args_read _, %2
_dec [_ax-8]
waget ax,_ax,[_ax-8]
macro_args_save w, %1
%endmacro

%macro bapop 2
macro_args_read _, %2
_dec [_ax-8]
baget al,_ax,[_ax-8]
macro_args_save b, %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _ufor _ %+ ufor

%macro qufor 4
%push for
qmov %1,%2
qsub %1,%4
%$__jup:
qadd %1,%4
qslt %4,0,%%_less
quge %1,%3,%$__jdown
jmp %%_end
%%_less:
qule %1,%3,%$__jdown
%%_end:
%endmacro

%macro dufor 4
%push for
dmov %1,%2
dsub %1,%4
%$__jup:
dadd %1,%4
dslt %4,0,%%_less
duge %1,%3,%$__jdown
jmp %%_end
%%_less:
dule %1,%3,%$__jdown
%%_end:
%endmacro

%macro wufor 4
%push for
wmov %1,%2
wsub %1,%4
%$__jup:
wadd %1,%4
wslt %4,0,%%_less
wuge %1,%3,%$__jdown
jmp %%_end
%%_less:
wule %1,%3,%$__jdown
%%_end:
%endmacro

%macro bufor 4
%push for
bmov %1,%2
bsub %1,%4
%$__jup:
badd %1,%4
bslt %4,0,%%_less
buge %1,%3,%$__jdown
jmp %%_end
%%_less:
bule %1,%3,%$__jdown
%%_end:
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _sfor _ %+ sfor

%macro qsfor 4
%push for
qmov %1,%2
qsub %1,%4
%$__jup:
qadd %1,%4
qslt %4,0,%%_less
qsge %1,%3,%$__jdown
jmp %%_end
%%_less:
qsle %1,%3,%$__jdown
%%_end:
%endmacro

%macro dsfor 4
%push for
dmov %1,%2
dsub %1,%4
%$__jup:
dadd %1,%4
dslt %4,0,%%_less
dsge %1,%3,%$__jdown
jmp %%_end
%%_less:
dsle %1,%3,%$__jdown
%%_end:
%endmacro

%macro wsfor 4
%push for
wmov %1,%2
wsub %1,%4
%$__jup:
wadd %1,%4
wslt %4,0,%%_less
wsge %1,%3,%$__jdown
jmp %%_end
%%_less:
wsle %1,%3,%$__jdown
%%_end:
%endmacro

%macro bsfor 4
%push for
bmov %1,%2
bsub %1,%4
%$__jup:
badd %1,%4
bslt %4,0,%%_less
bsge %1,%3,%$__jdown
jmp %%_end
%%_less:
bsle %1,%3,%$__jdown
%%_end:
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro qufor 3
qufor %1,%2,%3,1
%endmacro

%macro dufor 3
dufor %1,%2,%3,1
%endmacro

%macro wufor 3
wufor %1,%2,%3,1
%endmacro

%macro bufor 3
bufor %1,%2,%3,1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro qsfor 3
qsfor %1,%2,%3,1
%endmacro

%macro dsfor 3
dsfor %1,%2,%3,1
%endmacro

%macro wsfor 3
wsfor %1,%2,%3,1
%endmacro

%macro bsfor 3
bsfor %1,%2,%3,1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro qufor 2
qufor %1,0,%2,1
%endmacro

%macro dufor 2
dufor %1,0,%2,1
%endmacro

%macro wufor 2
wufor %1,0,%2,1
%endmacro

%macro bufor 2
bufor %1,0,%2,1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro qsfor 2
qsfor %1,0,%2,1
%endmacro

%macro dsfor 2
dsfor %1,0,%2,1
%endmacro

%macro wsfor 2
wsfor %1,0,%2,1
%endmacro

%macro bsfor 2
bsfor %1,0,%2,1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; %macro duput 1
; push %%_1
; push dword %1
; jmp _macro_duput
; %%_1:
; %endmacro

; %macro wuput 1
; push %%_1
; push word 0
; push word %1
; jmp _macro_wuput
; %%_1:
; %endmacro

; %macro buput 1
; push %%_1
; push word 0
; pushbw %1
; jmp _macro_buput
; %%_1:
; %endmacro

; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; %macro dsput 1
; push %%_1
; push dword %1
; jmp _macro_dsput
; %%_1:
; %endmacro

; %macro wsput 1
; push %%_1
; push word 0
; push word %1
; jmp _macro_wsput
; %%_1:
; %endmacro

; %macro bsput 1
; push %%_1
; push word 0
; pushbw %1
; jmp _macro_bsput
; %%_1:
; %endmacro

; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; %macro cput 1
; push %%_1
; push word 0
; pushbw %1
; jmp _macro_cput
; %%_1:
; %endmacro

; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; %macro duprint 1-*
; %if %0==1
; 	push %%_1
; 	push dword %1
; 	jmp _macro_duprint
; 	%%_1:
; %else
; 	%rep %0-1
; 	duput %1
; 	cput 32
; 	%rotate 1
; 	%endrep
; 	duput %1
; 	cput 10
; %endif
; %endmacro

; %macro wuprint 1-*
; %if %0==1
; 	push %%_1
; 	push word 0
; 	push word %1
; 	jmp _macro_wuprint
; 	%%_1:
; %else
; 	%rep %0-1
; 	wuput %1
; 	cput 32
; 	%rotate 1
; 	%endrep
; 	wuput %1
; 	cput 10
; %endif
; %endmacro

; %macro buprint 1-*
; %if %0==1
; 	push %%_1
; 	push word 0
; 	pushbw %1
; 	jmp _macro_buprint
; 	%%_1:
; %else
; 	%rep %0-1
; 	buput %1
; 	cput 32
; 	%rotate 1
; 	%endrep
; 	buput %1
; 	cput 10
; %endif
; %endmacro

; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; %macro duwrite 1-*
; %if %0==1
; 	push %%_1
; 	push dword %1
; 	jmp _macro_duwrite
; 	%%_1:
; %else
; 	%rep %0
; 	duput %1
; 	cput 32
; 	%rotate 1
; 	%endrep
; %endif
; %endmacro

; %macro wuwrite 1-*
; %if %0==1
; 	push %%_1
; 	push word 0
; 	push word %1
; 	jmp _macro_wuwrite
; 	%%_1:
; %else
; 	%rep %0
; 	wuput %1
; 	cput 32
; 	%rotate 1
; 	%endrep
; %endif
; %endmacro

; %macro buwrite 1-*
; %if %0==1
; 	push %%_1
; 	push word 0
; 	pushbw %1
; 	jmp _macro_buwrite
; 	%%_1:
; %else
; 	%rep %0
; 	buput %1
; 	cput 32
; 	%rotate 1
; 	%endrep
; %endif
; %endmacro

; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; %macro dsprint 1-*
; %if %0==1
; 	push %%_1
; 	push dword %1
; 	jmp _macro_dsprint
; 	%%_1:
; %else
; 	%rep %0-1
; 	dsput %1
; 	cput 32
; 	%rotate 1
; 	%endrep
; 	dsput %1
; 	cput 10
; %endif
; %endmacro

; %macro wsprint 1-*
; %if %0==1
; 	push %%_1
; 	push word 0
; 	push word %1
; 	jmp _macro_wsprint
; 	%%_1:
; %else
; 	%rep %0-1
; 	wsput %1
; 	cput 32
; 	%rotate 1
; 	%endrep
; 	wsput %1
; 	cput 10
; %endif
; %endmacro

; %macro bsprint 1-*
; %if %0==1
; 	push %%_1
; 	push word 0
; 	pushbw %1
; 	jmp _macro_bsprint
; 	%%_1:
; %else
; 	%rep %0-1
; 	bsput %1
; 	cput 32
; 	%rotate 1
; 	%endrep
; 	bsput %1
; 	cput 10
; %endif
; %endmacro

; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; %macro dswrite 1-*
; %if %0==1
; 	push %%_1
; 	push dword %1
; 	jmp _macro_dswrite
; 	%%_1:
; %else
; 	%rep %0
; 	dsput %1
; 	cput 32
; 	%rotate 1
; 	%endrep
; %endif
; %endmacro

; %macro wswrite 1-*
; %if %0==1
; 	push %%_1
; 	push word 0
; 	push word %1
; 	jmp _macro_wswrite
; 	%%_1:
; %else
; 	%rep %0
; 	wsput %1
; 	cput 32
; 	%rotate 1
; 	%endrep
; %endif
; %endmacro

; %macro bswrite 1-*
; %if %0==1
; 	push %%_1
; 	push word 0
; 	pushbw %1
; 	jmp _macro_bswrite
; 	%%_1:
; %else
; 	%rep %0
; 	bsput %1
; 	cput 32
; 	%rotate 1
; 	%endrep
; %endif
; %endmacro

; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; %macro cprint 1-*
; %if %0==1
; 	push %%_1
; 	push word 0
; 	pushbw %1
; 	jmp _macro_cprint
; 	%%_1:
; %else
; 	%rep %0-1
; 	cput %1
; 	cput 32
; 	%rotate 1
; 	%endrep
; 	cput %1
; 	cput 10
; %endif
; %endmacro

; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; %macro cwrite 1-*
; %if %0==1
; 	push %%_1
; 	push word 0
; 	pushbw %1
; 	jmp _macro_cwrite
; 	%%_1:
; %else
; 	%rep %0
; 	cput %1
; 	cput 32
; 	%rotate 1
; 	%endrep
; %endif
; %endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; %macro sput 1
; macro_args_read
; jmp %%_1
; %%_2:
; db %1
; %%_1:
; mov eax,4
; mov ebx,1
; mov ecx,%%_2
; mov edx,%%_1-%%_2
; int 0x80
; macro_args_save
; %endmacro

; %macro sprint 1-*
; %rep %0-1
; sput %1
; cput 32
; %rotate 1
; %endrep
; sput %1
; cput 10
; %endmacro

; %macro swrite 1-*
; %rep %0
; sput %1
; cput 32
; %rotate 1
; %endrep
; %endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro snput 2
macro_args_read _,_, %1,%2
mov _cx,_ax
mov _dx,_bx
mov _ax,4
mov _bx,1
int 0x80
macro_args_save
%endmacro

%macro snprint 1-*
%rep %0/2-1
snput %1,%2
cput 32
%rotate 2
%endrep
snput %1,%2
cput 10
%endmacro

%macro snwrite 1-*
%rep %0/2
snput %1,%2
cput 32
%rotate 2
%endrep
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro cget 1
macro_args_read
push word 0
mov _ax,3
mov _bx,2
mov _cx,_sp
mov _dx,1
int 0x80
pop ax
macro_args_save b, %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro _get 1
macro_args_read
%%_1:
mov _ax,0
cget al
bne al,'-',%%_2
mov _dx,1
jmp %%_1
%%_2:
bult al,'0',%%_4
bugt al,'9',%%_4
jmp %%_3
%%_4:
deq _cx,0,%%_1
jmp %%_6
%%_3:
mov _cx,1
sub _ax,48
dmul _bx,10
add _bx,_ax
jmp %%_1
%%_6:
dne _dx,1,%%_5
neg _bx
%%_5:
mov _ax,_bx
macro_args_save _, %1
%endmacro

%macro qget 1
macro_args_read
_get _ax
macro_args_save q, %1
%endmacro

%macro dget 1
macro_args_read
_get _ax
macro_args_save d, %1
%endmacro

%macro wget 1
macro_args_read
_get _ax
macro_args_save w, %1
%endmacro

%macro bget 1
macro_args_read
_get _ax
macro_args_save b, %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; %macro dpush 1
; push dword %1
; %endmacro

; %macro wpush 1
; push word %1
; %endmacro

; %macro bpush 1
; pushbw %1
; %endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; %macro dpop 1
; pop dword %1
; %endmacro

; %macro wpop 1
; pop word %1
; %endmacro

; %macro bpop 1
; popbw %1
; %endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _uwhile _ %+ uwhile

%macro quwhile 3
%push while
%$__jup:
%ifidni %2,<
quge %1,%3,%$__jdown
%elifidni %2,<=
qugt %1,%3,%$__jdown
%elifidni %2,>=
qult %1,%3,%$__jdown
%elifidni %2,>
qule %1,%3,%$__jdown
%elifidni %2,==
qne %1,%3,%$__jdown
%elifidni %2,!=
qeq %1,%3,%$__jdown
%endif
%endmacro

%macro duwhile 3
%push while
%$__jup:
%ifidni %2,<
duge %1,%3,%$__jdown
%elifidni %2,<=
dugt %1,%3,%$__jdown
%elifidni %2,>=
dult %1,%3,%$__jdown
%elifidni %2,>
dule %1,%3,%$__jdown
%elifidni %2,==
dne %1,%3,%$__jdown
%elifidni %2,!=
deq %1,%3,%$__jdown
%endif
%endmacro

%macro wuwhile 3
%push while
%$__jup:
%ifidni %2,<
wuge %1,%3,%$__jdown
%elifidni %2,<=
wugt %1,%3,%$__jdown
%elifidni %2,>=
wult %1,%3,%$__jdown
%elifidni %2,>
wule %1,%3,%$__jdown
%elifidni %2,==
wne %1,%3,%$__jdown
%elifidni %2,!=
weq %1,%3,%$__jdown
%endif
%endmacro

%macro buwhile 3
%push while
%$__jup:
%ifidni %2,<
buge %1,%3,%$__jdown
%elifidni %2,<=
bugt %1,%3,%$__jdown
%elifidni %2,>=
bult %1,%3,%$__jdown
%elifidni %2,>
bule %1,%3,%$__jdown
%elifidni %2,==
bne %1,%3,%$__jdown
%elifidni %2,!=
beq %1,%3,%$__jdown
%endif
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _swhile _ %+ swhile

%macro qswhile 3
%push while
%$__jup:
%ifidni %2,<
qsge %1,%3,%$__jdown
%elifidni %2,<=
qsgt %1,%3,%$__jdown
%elifidni %2,>=
qslt %1,%3,%$__jdown
%elifidni %2,>
qsle %1,%3,%$__jdown
%elifidni %2,==
qne %1,%3,%$__jdown
%elifidni %2,!=
qeq %1,%3,%$__jdown
%endif
%endmacro

%macro dswhile 3
%push while
%$__jup:
%ifidni %2,<
dsge %1,%3,%$__jdown
%elifidni %2,<=
dsgt %1,%3,%$__jdown
%elifidni %2,>=
dslt %1,%3,%$__jdown
%elifidni %2,>
dsle %1,%3,%$__jdown
%elifidni %2,==
dne %1,%3,%$__jdown
%elifidni %2,!=
deq %1,%3,%$__jdown
%endif
%endmacro

%macro wswhile 3
%push while
%$__jup:
%ifidni %2,<
wsge %1,%3,%$__jdown
%elifidni %2,<=
wsgt %1,%3,%$__jdown
%elifidni %2,>=
wslt %1,%3,%$__jdown
%elifidni %2,>
wsle %1,%3,%$__jdown
%elifidni %2,==
wne %1,%3,%$__jdown
%elifidni %2,!=
weq %1,%3,%$__jdown
%endif
%endmacro

%macro bswhile 3
%push while
%$__jup:
%ifidni %2,<
bsge %1,%3,%$__jdown
%elifidni %2,<=
bsgt %1,%3,%$__jdown
%elifidni %2,>=
bslt %1,%3,%$__jdown
%elifidni %2,>
bsle %1,%3,%$__jdown
%elifidni %2,==
bne %1,%3,%$__jdown
%elifidni %2,!=
beq %1,%3,%$__jdown
%endif
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro end 0
jmp %$__jup
%$__jdown:
%$__jelse:
%pop
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _uif _ %+ uif

%macro quif 3
%push if
jmp %%_1
%$__jup:
jmp %$__jdown
%%_1:
%ifidni %2,<
quge %1,%3,%$__jelse
%elifidni %2,<=
qugt %1,%3,%$__jelse
%elifidni %2,>=
qult %1,%3,%$__jelse
%elifidni %2,>
qule %1,%3,%$__jelse
%elifidni %2,==
qne %1,%3,%$__jelse
%elifidni %2,!=
qeq %1,%3,%$__jelse
%endif
%endmacro

%macro duif 3
%push if
jmp %%_1
%$__jup:
jmp %$__jdown
%%_1:
%ifidni %2,<
duge %1,%3,%$__jelse
%elifidni %2,<=
dugt %1,%3,%$__jelse
%elifidni %2,>=
dult %1,%3,%$__jelse
%elifidni %2,>
dule %1,%3,%$__jelse
%elifidni %2,==
dne %1,%3,%$__jelse
%elifidni %2,!=
deq %1,%3,%$__jelse
%endif
%endmacro

%macro wuif 3
%push if
jmp %%_1
%$__jup:
jmp %$__jdown
%%_1:
%ifidni %2,<
wuge %1,%3,%$__jelse
%elifidni %2,<=
wugt %1,%3,%$__jelse
%elifidni %2,>=
wult %1,%3,%$__jelse
%elifidni %2,>
wule %1,%3,%$__jelse
%elifidni %2,==
wne %1,%3,%$__jelse
%elifidni %2,!=
weq %1,%3,%$__jelse
%endif
%endmacro

%macro buif 3
%push if
jmp %%_1
%$__jup:
jmp %$__jdown
%%_1:
%ifidni %2,<
buge %1,%3,%$__jelse
%elifidni %2,<=
bugt %1,%3,%$__jelse
%elifidni %2,>=
bult %1,%3,%$__jelse
%elifidni %2,>
bule %1,%3,%$__jelse
%elifidni %2,==
bne %1,%3,%$__jelse
%elifidni %2,!=
beq %1,%3,%$__jelse
%endif
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _sif _ %+ sif

%macro qsif 3
%push if
jmp %%_1
%$__jup:
jmp %$__jdown
%%_1:
%ifidni %2,<
qsge %1,%3,%$__jelse
%elifidni %2,<=
qsgt %1,%3,%$__jelse
%elifidni %2,>=
qslt %1,%3,%$__jelse
%elifidni %2,>
qsle %1,%3,%$__jelse
%elifidni %2,==
qne %1,%3,%$__jelse
%elifidni %2,!=
qeq %1,%3,%$__jelse
%endif
%endmacro

%macro dsif 3
%push if
jmp %%_1
%$__jup:
jmp %$__jdown
%%_1:
%ifidni %2,<
dsge %1,%3,%$__jelse
%elifidni %2,<=
dsgt %1,%3,%$__jelse
%elifidni %2,>=
dslt %1,%3,%$__jelse
%elifidni %2,>
dsle %1,%3,%$__jelse
%elifidni %2,==
dne %1,%3,%$__jelse
%elifidni %2,!=
deq %1,%3,%$__jelse
%endif
%endmacro

%macro wsif 3
%push if
jmp %%_1
%$__jup:
jmp %$__jdown
%%_1:
%ifidni %2,<
wsge %1,%3,%$__jelse
%elifidni %2,<=
wsgt %1,%3,%$__jelse
%elifidni %2,>=
wslt %1,%3,%$__jelse
%elifidni %2,>
wsle %1,%3,%$__jelse
%elifidni %2,==
wne %1,%3,%$__jelse
%elifidni %2,!=
weq %1,%3,%$__jelse
%endif
%endmacro

%macro bsif 3
%push if
jmp %%_1
%$__jup:
jmp %$__jdown
%%_1:
%ifidni %2,<
bsge %1,%3,%$__jelse
%elifidni %2,<=
bsgt %1,%3,%$__jelse
%elifidni %2,>=
bslt %1,%3,%$__jelse
%elifidni %2,>
bsle %1,%3,%$__jelse
%elifidni %2,==
bne %1,%3,%$__jelse
%elifidni %2,!=
beq %1,%3,%$__jelse
%endif
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro else 0
jmp %%_1
%$__jelse:
jmp %%_2
%%_1:
%$__jdown:
%pop
%push if
%$__jup:
jmp %$__jdown
%%_2:
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _uelif _ %+ uelif

%macro quelif 3
jmp %%_1
%$__jelse:
jmp %%_2
%%_1:
%$__jdown:
%pop
%push if
%$__jup:
jmp %$__jdown
%%_2:
%ifidni %2,<
quge %1,%3,%$__jelse
%elifidni %2,<=
qugt %1,%3,%$__jelse
%elifidni %2,>=
qult %1,%3,%$__jelse
%elifidni %2,>
qule %1,%3,%$__jelse
%elifidni %2,==
qne %1,%3,%$__jelse
%elifidni %2,!=
qeq %1,%3,%$__jelse
%endif
%endmacro

%macro duelif 3
jmp %%_1
%$__jelse:
jmp %%_2
%%_1:
%$__jdown:
%pop
%push if
%$__jup:
jmp %$__jdown
%%_2:
%ifidni %2,<
duge %1,%3,%$__jelse
%elifidni %2,<=
dugt %1,%3,%$__jelse
%elifidni %2,>=
dult %1,%3,%$__jelse
%elifidni %2,>
dule %1,%3,%$__jelse
%elifidni %2,==
dne %1,%3,%$__jelse
%elifidni %2,!=
deq %1,%3,%$__jelse
%endif
%endmacro

%macro wuelif 3
jmp %%_1
%$__jelse:
jmp %%_2
%%_1:
%$__jdown:
%pop
%push if
%$__jup:
jmp %$__jdown
%%_2:
%ifidni %2,<
wuge %1,%3,%$__jelse
%elifidni %2,<=
wugt %1,%3,%$__jelse
%elifidni %2,>=
wult %1,%3,%$__jelse
%elifidni %2,>
wule %1,%3,%$__jelse
%elifidni %2,==
wne %1,%3,%$__jelse
%elifidni %2,!=
weq %1,%3,%$__jelse
%endif
%endmacro

%macro buelif 3
jmp %%_1
%$__jelse:
jmp %%_2
%%_1:
%$__jdown:
%pop
%push if
%$__jup:
jmp %$__jdown
%%_2:
%ifidni %2,<
buge %1,%3,%$__jelse
%elifidni %2,<=
bugt %1,%3,%$__jelse
%elifidni %2,>=
bult %1,%3,%$__jelse
%elifidni %2,>
bule %1,%3,%$__jelse
%elifidni %2,==
bne %1,%3,%$__jelse
%elifidni %2,!=
beq %1,%3,%$__jelse
%endif
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _selif _ %+ selif

%macro qselif 3
jmp %%_1
%$__jelse:
jmp %%_2
%%_1:
%$__jdown:
%pop
%push if
%$__jup:
jmp %$__jdown
%%_2:
%ifidni %2,<
qsge %1,%3,%$__jelse
%elifidni %2,<=
qsgt %1,%3,%$__jelse
%elifidni %2,>=
qslt %1,%3,%$__jelse
%elifidni %2,>
qsle %1,%3,%$__jelse
%elifidni %2,==
qne %1,%3,%$__jelse
%elifidni %2,!=
qeq %1,%3,%$__jelse
%endif
%endmacro

%macro dselif 3
jmp %%_1
%$__jelse:
jmp %%_2
%%_1:
%$__jdown:
%pop
%push if
%$__jup:
jmp %$__jdown
%%_2:
%ifidni %2,<
dsge %1,%3,%$__jelse
%elifidni %2,<=
dsgt %1,%3,%$__jelse
%elifidni %2,>=
dslt %1,%3,%$__jelse
%elifidni %2,>
dsle %1,%3,%$__jelse
%elifidni %2,==
dne %1,%3,%$__jelse
%elifidni %2,!=
deq %1,%3,%$__jelse
%endif
%endmacro

%macro wselif 3
jmp %%_1
%$__jelse:
jmp %%_2
%%_1:
%$__jdown:
%pop
%push if
%$__jup:
jmp %$__jdown
%%_2:
%ifidni %2,<
wsge %1,%3,%$__jelse
%elifidni %2,<=
wsgt %1,%3,%$__jelse
%elifidni %2,>=
wslt %1,%3,%$__jelse
%elifidni %2,>
wsle %1,%3,%$__jelse
%elifidni %2,==
wne %1,%3,%$__jelse
%elifidni %2,!=
weq %1,%3,%$__jelse
%endif
%endmacro

%macro bselif 3
jmp %%_1
%$__jelse:
jmp %%_2
%%_1:
%$__jdown:
%pop
%push if
%$__jup:
jmp %$__jdown
%%_2:
%ifidni %2,<
bsge %1,%3,%$__jelse
%elifidni %2,<=
bsgt %1,%3,%$__jelse
%elifidni %2,>=
bslt %1,%3,%$__jelse
%elifidni %2,>
bsle %1,%3,%$__jelse
%elifidni %2,==
bne %1,%3,%$__jelse
%elifidni %2,!=
beq %1,%3,%$__jelse
%endif
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro def 1
section .text
%push func
%ifdef macro_var
var %1
%endif
jmp %$__jdown
%1:
macro_args_read _,_,_,_, [_sp+rsize*4],[_sp+rsize*3],[_sp+rsize*2],[_sp+rsize*1]
jmp %%_2

%$__jup:
macro_args_save _,_,_,_, [_sp+rsize*1],[_sp+rsize*2],[_sp+rsize*3],[_sp+rsize*4]
ret

%%_2:
%endmacro

%macro call0 1+
macro_call %1
add _sp,rsize*4
%endmacro

%macro call1 2+
macro_call %2
pop _word %1
add _sp,rsize*3
%endmacro

%macro call2 3+
macro_call %3
pop _word %1
pop _word %2
add _sp,rsize*2
%endmacro

%macro call3 4+
macro_call %4
pop _word %1
pop _word %2
pop _word %3
add _sp,rsize*1
%endmacro

%macro call4 5+
macro_call %5
pop _word %1
pop _word %2
pop _word %3
pop _word %4
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro pass 0
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%define _memmove _ %+ memmove

%macro qmemmove 3
macro_args_read _,_,_, %1,%2,%3
cmp _ax,_bx
jb %%left
add _ax,_cx
add _bx,_cx
%%right:
dec _ax
dec _bx
mov rdx,[_bx]
mov [_ax],rdx
loop %%right
jmp %%end
%%left:
mov rdx,[_bx]
mov [_ax],rdx
inc _ax
inc _bx
loop %%left
%%end:
macro_args_save
%endmacro

%macro dmemmove 3
macro_args_read _,_,_, %1,%2,%3
cmp _ax,_bx
jb %%left
add _ax,_cx
add _bx,_cx
%%right:
dec _ax
dec _bx
mov edx,[_bx]
mov [_ax],edx
loop %%right
jmp %%end
%%left:
mov edx,[_bx]
mov [_ax],edx
inc _ax
inc _bx
loop %%left
%%end:
macro_args_save
%endmacro

%macro wmemmove 3
macro_args_read _,_,_, %1,%2,%3
cmp _ax,_bx
jb %%left
add _ax,_cx
add _bx,_cx
%%right:
dec _ax
dec _bx
mov dx,[_bx]
mov [_ax],dx
loop %%right
jmp %%end
%%left:
mov dx,[_bx]
mov [_ax],dx
inc _ax
inc _bx
loop %%left
%%end:
macro_args_save
%endmacro

%macro bmemmove 3
macro_args_read _,_,_, %1,%2,%3
cmp _ax,_bx
jb %%left
add _ax,_cx
add _bx,_cx
%%right:
dec _ax
dec _bx
mov dl,[_bx]
mov [_ax],dl
loop %%right
jmp %%end
%%left:
mov dl,[_bx]
mov [_ax],dl
inc _ax
inc _bx
loop %%left
%%end:
macro_args_save
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%include "macro_set.inc"
%include "macro_code.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

pre_start

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

