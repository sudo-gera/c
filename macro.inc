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
_start:
mov [esp_base],esp
%endmacro

%macro stop 0-1 0
mov ebx, %1
mov eax, 1
int 0x80
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%include "macro_tools.inc"

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

