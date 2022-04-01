%macro alld 0
a dd 0
b dd 0
c dd 0
d dd 0
e dd 0
f dd 0
g dd 0
h dd 0
i dd 0
j dd 0
k dd 0
l dd 0
m dd 0
n dd 0
o dd 0
p dd 0
q dd 0
r dd 0
s dd 0
t dd 0
u dd 0
v dd 0
w dd 0
x dd 0
y dd 0
z dd 0
%endmacro

%macro start 0
global _start
section .data
alld
esp_base dd 0
section .text

macro_print_call macro_duput
macro_print_call macro_wuput
macro_print_call macro_buput
macro_print_call macro_dsput
macro_print_call macro_wsput
macro_print_call macro_bsput

macro_print_call macro_cput

macro_print_call macro_duprint
macro_print_call macro_wuprint
macro_print_call macro_buprint
macro_print_call macro_dsprint
macro_print_call macro_wsprint
macro_print_call macro_bsprint

macro_print_call macro_duwrite
macro_print_call macro_wuwrite
macro_print_call macro_buwrite
macro_print_call macro_dswrite
macro_print_call macro_wswrite
macro_print_call macro_bswrite

_start:
mov [esp_base],esp
%endmacro

%macro stop 0-1 0
_stop:
cmp [esp_base],esp
je %%_1
sprint "warning: stack not empty"
%%_1:
mov ebx, %1
mov eax, 1
int 0x80
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%include "macro_tools.inc"
%include "macro_usual.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro daget 3
macro_args_read_dd %2,%3
lea ebx,[eax+ebx*4]
mov eax,[ebx]
macro_args_save_d %1
%endmacro

%macro waget 3
macro_args_read_dd %2,%3
lea ebx,[eax+ebx*2]
mov ax,[ebx]
macro_args_save_w %1
%endmacro

%macro baget 3
macro_args_read_dd %2,%3
lea ebx,[eax+ebx*1]
mov al,[ebx]
macro_args_save_b %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro daput 3
macro_args_read_ddd %1,%2,%3
lea ebx,[eax+ebx*4]
mov [ebx],ecx
macro_args_save_
%endmacro

%macro waput 3
macro_args_read_ddw %1,%2,%3
lea ebx,[eax+ebx*2]
mov [ebx],cx
macro_args_save_
%endmacro

%macro baput 3
macro_args_read_ddb %1,%2,%3
lea ebx,[eax+ebx*1]
mov [ebx],cl
macro_args_save_
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dmov 2
macro_args_read_d %2
macro_args_save_d %1
%endmacro

%macro wmov 2
macro_args_read_w %2
macro_args_save_w %1
%endmacro

%macro bmov 2
macro_args_read_b %2
macro_args_save_b %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dxchg 2
macro_args_read_dd %2,%1
macro_args_save_dd %1,%2
%endmacro

%macro wxchg 2
macro_args_read_ww %2,%1
macro_args_save_ww %1,%2
%endmacro

%macro bxchg 2
macro_args_read_bb %2,%1
macro_args_save_bb %1,%2
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dadd 3
macro_args_read_dd %2,%3
add eax,ebx
macro_args_save_d %1
%endmacro

%macro wadd 3
macro_args_read_ww %2,%3
add ax,bx
macro_args_save_w %1
%endmacro

%macro badd 3
macro_args_read_bb %2,%3
add al,bl
macro_args_save_b %1
%endmacro

%macro dadd 2
macro_args_read_dd %1,%2
add eax,ebx
macro_args_save_d %1
%endmacro

%macro wadd 2
macro_args_read_ww %1,%2
add ax,bx
macro_args_save_w %1
%endmacro

%macro badd 2
macro_args_read_bb %1,%2
add al,bl
macro_args_save_b %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dsub 3
macro_args_read_dd %2,%3
sub eax,ebx
macro_args_save_d %1
%endmacro

%macro wsub 3
macro_args_read_ww %2,%3
sub ax,bx
macro_args_save_w %1
%endmacro

%macro bsub 3
macro_args_read_bb %2,%3
sub al,bl
macro_args_save_b %1
%endmacro

%macro dsub 2
macro_args_read_dd %1,%2
sub eax,ebx
macro_args_save_d %1
%endmacro

%macro wsub 2
macro_args_read_ww %1,%2
sub ax,bx
macro_args_save_w %1
%endmacro

%macro bsub 2
macro_args_read_bb %1,%2
sub al,bl
macro_args_save_b %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dmul 3
macro_args_read_dd %2,%3
mul ebx
macro_args_save_d %1
%endmacro

%macro wmul 3
macro_args_read_ww %2,%3
mul bx
macro_args_save_w %1
%endmacro

%macro bmul 3
macro_args_read_bb %2,%3
mul bl
macro_args_save_b %1
%endmacro

%macro dmul 2
macro_args_read_dd %1,%2
mul ebx
macro_args_save_d %1
%endmacro

%macro wmul 2
macro_args_read_ww %1,%2
mul bx
macro_args_save_w %1
%endmacro

%macro bmul 2
macro_args_read_bb %1,%2
mul bl
macro_args_save_b %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dudiv 3
macro_args_read_dd %2,%3
div ebx
macro_args_save_d %1
%endmacro

%macro wudiv 3
macro_args_read_ww %2,%3
div bx
macro_args_save_w %1
%endmacro

%macro budiv 3
macro_args_read_bb %2,%3
div bl
macro_args_save_b %1
%endmacro

%macro dudiv 2
macro_args_read_dd %1,%2
div ebx
macro_args_save_d %1
%endmacro

%macro wudiv 2
macro_args_read_ww %1,%2
div bx
macro_args_save_w %1
%endmacro

%macro budiv 2
macro_args_read_bb %1,%2
div bl
macro_args_save_b %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dsdiv 3
macro_args_read_dd %2,%3
idiv ebx
macro_args_save_d %1
%endmacro

%macro wsdiv 3
macro_args_read_ww %2,%3
idiv bx
macro_args_save_w %1
%endmacro

%macro bsdiv 3
macro_args_read_bb %2,%3
idiv bl
macro_args_save_b %1
%endmacro

%macro dsdiv 2
macro_args_read_dd %1,%2
idiv ebx
macro_args_save_d %1
%endmacro

%macro wsdiv 2
macro_args_read_ww %1,%2
idiv bx
macro_args_save_w %1
%endmacro

%macro bsdiv 2
macro_args_read_bb %1,%2
idiv bl
macro_args_save_b %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dumod 3
macro_args_read_dd %2,%3
div ebx
mov eax,edx
macro_args_save_d %1
%endmacro

%macro wumod 3
macro_args_read_ww %2,%3
div bx
mov ax,dx
macro_args_save_w %1
%endmacro

%macro bumod 3
macro_args_read_bb %2,%3
div bl
mov al,ah
macro_args_save_b %1
%endmacro

%macro dumod 2
macro_args_read_dd %1,%2
div ebx
mov eax,edx
macro_args_save_d %1
%endmacro

%macro wumod 2
macro_args_read_ww %1,%2
div bx
mov ax,dx
macro_args_save_w %1
%endmacro

%macro bumod 2
macro_args_read_bb %1,%2
div bl
mov al,ah
macro_args_save_b %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dsmod 3
macro_args_read_dd %2,%3
idiv ebx
mov eax,edx
macro_args_save_d %1
%endmacro

%macro wsmod 3
macro_args_read_ww %2,%3
idiv bx
mov ax,dx
macro_args_save_w %1
%endmacro

%macro bsmod 3
macro_args_read_bb %2,%3
idiv bl
mov al,ah
macro_args_save_b %1
%endmacro

%macro dsmod 2
macro_args_read_dd %1,%2
idiv ebx
mov eax,edx
macro_args_save_d %1
%endmacro

%macro wsmod 2
macro_args_read_ww %1,%2
idiv bx
mov ax,dx
macro_args_save_w %1
%endmacro

%macro bsmod 2
macro_args_read_bb %1,%2
idiv bl
mov al,ah
macro_args_save_b %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dudivmod 4
macro_args_read_dd %3,%4
div ebx
mov ebx,edx
macro_args_save_dd %1,%2
%endmacro

%macro wudivmod 4
macro_args_read_ww %3,%4
div bx
mov bx,dx
macro_args_save_ww %1,%2
%endmacro

%macro budivmod 4
macro_args_read_bb %3,%4
div bl
mov bl,ah
macro_args_save_bb %1,%2
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dsdivmod 4
macro_args_read_dd %3,%4
idiv ebx
mov ebx,edx
macro_args_save_dd %1,%2
%endmacro

%macro wsdivmod 4
macro_args_read_ww %3,%4
idiv bx
mov bx,dx
macro_args_save_ww %1,%2
%endmacro

%macro bsdivmod 4
macro_args_read_bb %3,%4
idiv bl
mov bl,ah
macro_args_save_bb %1,%2
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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

%macro dapush 2
macro_args_read_dd %1,%2
daput eax,[eax-8],ebx
dinc [eax-8]
macro_args_save_
%endmacro

%macro wapush 2
macro_args_read_dw %1,%2
waput eax,[eax-8],bx
dinc [eax-8]
macro_args_save_
%endmacro

%macro bapush 2
macro_args_read_db %1,%2
baput eax,[eax-8],bl
dinc [eax-8]
macro_args_save_
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dapop 2
macro_args_read_d %2
ddec [eax-8]
daget eax,eax,[eax-8]
macro_args_save_d %1
%endmacro

%macro wapop 2
macro_args_read_d %2
ddec [eax-8]
waget cx,eax,[eax-8]
mov eax,ecx
macro_args_save_w %1
%endmacro

%macro bapop 2
macro_args_read_d %2
ddec [eax-8]
baget cl,eax,[eax-8]
mov eax,ecx
macro_args_save_b %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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

%macro duput 1
push %%_1
push dword %1
jmp _macro_duput
%%_1:
%endmacro

%macro wuput 1
push %%_1
push word 0
push word %1
jmp _macro_wuput
%%_1:
%endmacro

%macro buput 1
push %%_1
push word 0
pushbw %1
jmp _macro_buput
%%_1:
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dsput 1
push %%_1
push dword %1
jmp _macro_dsput
%%_1:
%endmacro

%macro wsput 1
push %%_1
push word 0
push word %1
jmp _macro_wsput
%%_1:
%endmacro

%macro bsput 1
push %%_1
push word 0
pushbw %1
jmp _macro_bsput
%%_1:
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro cput 1
push %%_1
push word 0
pushbw %1
jmp _macro_cput
%%_1:
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro duprint 1-*
%if %0==1
	push %%_1
	push dword %1
	jmp _macro_duprint
	%%_1:
%else
	%rep %0-1
	duput %1
	cput 32
	%rotate 1
	%endrep
	duput %1
	cput 10
%endif
%endmacro

%macro wuprint 1-*
%if %0==1
	push %%_1
	push word 0
	push word %1
	jmp _macro_wuprint
	%%_1:
%else
	%rep %0-1
	wuput %1
	cput 32
	%rotate 1
	%endrep
	wuput %1
	cput 10
%endif
%endmacro

%macro buprint 1-*
%if %0==1
	push %%_1
	push word 0
	pushbw %1
	jmp _macro_buprint
	%%_1:
%else
	%rep %0-1
	buput %1
	cput 32
	%rotate 1
	%endrep
	buput %1
	cput 10
%endif
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro duwrite 1-*
%if %0==1
	push %%_1
	push dword %1
	jmp _macro_duwrite
	%%_1:
%else
	%rep %0
	duput %1
	cput 32
	%rotate 1
	%endrep
%endif
%endmacro

%macro wuwrite 1-*
%if %0==1
	push %%_1
	push word 0
	push word %1
	jmp _macro_wuwrite
	%%_1:
%else
	%rep %0
	wuput %1
	cput 32
	%rotate 1
	%endrep
%endif
%endmacro

%macro buwrite 1-*
%if %0==1
	push %%_1
	push word 0
	pushbw %1
	jmp _macro_buwrite
	%%_1:
%else
	%rep %0
	buput %1
	cput 32
	%rotate 1
	%endrep
%endif
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dsprint 1-*
%if %0==1
	push %%_1
	push dword %1
	jmp _macro_dsprint
	%%_1:
%else
	%rep %0-1
	dsput %1
	cput 32
	%rotate 1
	%endrep
	dsput %1
	cput 10
%endif
%endmacro

%macro wsprint 1-*
%if %0==1
	push %%_1
	push word 0
	push word %1
	jmp _macro_wsprint
	%%_1:
%else
	%rep %0-1
	wsput %1
	cput 32
	%rotate 1
	%endrep
	wsput %1
	cput 10
%endif
%endmacro

%macro bsprint 1-*
%if %0==1
	push %%_1
	push word 0
	pushbw %1
	jmp _macro_bsprint
	%%_1:
%else
	%rep %0-1
	bsput %1
	cput 32
	%rotate 1
	%endrep
	bsput %1
	cput 10
%endif
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dswrite 1-*
%if %0==1
	push %%_1
	push dword %1
	jmp _macro_dswrite
	%%_1:
%else
	%rep %0
	dsput %1
	cput 32
	%rotate 1
	%endrep
%endif
%endmacro

%macro wswrite 1-*
%if %0==1
	push %%_1
	push word 0
	push word %1
	jmp _macro_wswrite
	%%_1:
%else
	%rep %0
	wsput %1
	cput 32
	%rotate 1
	%endrep
%endif
%endmacro

%macro bswrite 1-*
%if %0==1
	push %%_1
	push word 0
	pushbw %1
	jmp _macro_bswrite
	%%_1:
%else
	%rep %0
	bsput %1
	cput 32
	%rotate 1
	%endrep
%endif
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro cprint 1-*
%if %0==1
	push %%_1
	push word 0
	pushbw %1
	jmp _macro_cprint
	%%_1:
%else
	%rep %0-1
	cput %1
	cput 32
	%rotate 1
	%endrep
	cput %1
	cput 10
%endif
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro cwrite 1-*
%if %0==1
	push %%_1
	push word 0
	pushbw %1
	jmp _macro_cwrite
	%%_1:
%else
	%rep %0
	cput %1
	cput 32
	%rotate 1
	%endrep
%endif
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro sput 1
macro_args_read_
jmp %%_1
%%_2:
db %1
%%_1:
mov eax,4
mov ebx,1
mov ecx,%%_2
mov edx,%%_1-%%_2
int 0x80
macro_args_save_
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro sprint 1-*
%rep %0-1
sput %1
cput 32
%rotate 1
%endrep
sput %1
cput 10
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro swrite 1-*
%rep %0
sput %1
cput 32
%rotate 1
%endrep
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro cget 1
macro_args_read_
push word 0
mov eax,3
mov ebx,2
mov ecx,esp
mov edx,1
int 0x80
pop ax
macro_args_save_b %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dget 1
macro_args_read_
%%_1:
mov eax,0
cget al
bne al,'-',%%_2
mov edx,1
jmp %%_1
%%_2:
bult al,'0',%%_4
bugt al,'9',%%_4
jmp %%_3
%%_4:
deq ecx,0,%%_1
jmp %%_6
%%_3:
mov ecx,1
sub eax,48
dmul ebx,10
add ebx,eax
jmp %%_1
%%_6:
dne edx,1,%%_5
neg ebx
%%_5:
mov eax,ebx
macro_args_save_d %1
%endmacro

%macro wget 1
macro_args_read_
dget eax
macro_args_save_w %1
%endmacro

%macro bget 1
macro_args_read_
dget eax
macro_args_save_b %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dpush 1
push dword %1
%endmacro

%macro wpush 1
push word %1
%endmacro

%macro bpush 1
pushbw %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dpop 1
pop dword %1
%endmacro

%macro wpop 1
pop word %1
%endmacro

%macro bpop 1
popbw %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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

%macro def 1-5
%push func
jmp %$__jdown
func_ %+ %1:
push eax
mov eax,esp
macro_args_read_dddd [eax+20],[eax+16],[eax+12],[eax+8]
jmp %%_2

%$__jup:
macro_args_save_dddd [eax+8],[eax+12],[eax+16],[eax+20]
pop eax
add esp,4
jmp [esp-4]

%%_2:
%endmacro

%macro call0 1+
macro_call %1
add esp,16
%endmacro

%macro call1 2+
macro_call %2
pop dword %1
add esp,12
%endmacro

%macro call2 3+
macro_call %3
pop dword %1
pop dword %2
add esp,8
%endmacro

%macro call3 4+
macro_call %4
pop dword %1
pop dword %2
pop dword %3
add esp,4
%endmacro

%macro call4 5+
macro_call %5
pop dword %1
pop dword %2
pop dword %3
pop dword %4
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro duassert 1+
duif %1
else
sprint "assertion failed"
sprint "%1"
end
%endmacro
