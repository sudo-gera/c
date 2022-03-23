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
regsave
mov eax,%2
mov ebx,%3
lea ebx,[eax+ebx*4]
mov ebx,[ebx]
mov %1,bx
regload
%endmacro

%macro waget 3
regsave
mov eax,%2
mov ebx,%3
lea ebx,[eax+ebx*2]
mov bx,[ebx]
mov %1,bx
regload
%endmacro

%macro baget 3
regsave
mov eax,%2
mov ebx,%3
lea ebx,[eax+ebx*1]
mov bl,[ebx]
mov %1,bl
regload
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro daput 3
regsave
mov eax,%1
mov ebx,%2
lea ebx,[eax+ebx*4]
mov eax,%3
mov [ebx],eax
regload
%endmacro

%macro waput 3
regsave
mov eax,%1
mov ebx,%2
lea ebx,[eax+ebx*2]
mov ax,%3
mov [ebx],ax
regload
%endmacro

%macro baput 3
regsave
mov eax,%1
mov ebx,%2
lea ebx,[eax+ebx*1]
mov al,%3
mov [ebx],al
regload
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dmov 2
regsave
mov ebx,%2
mov %1,ebx
regload
%endmacro

%macro wmov 2
regsave
mov bx,%2
mov %1,bx
regload
%endmacro

%macro bmov 2
regsave
mov bl,%2
mov %1,bl
regload
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dxchg 2
regsave
mov ebx,%2
xchg ebx,%1
mov %2,ebx
regload
%endmacro

%macro wxchg 2
regsave
mov bx,%2
xchg bx,%1
mov %2,bx
regload
%endmacro

%macro bxchg 2
regsave
mov bx,%2
xchg bl,%1
mov %2,bl
regload
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dadd 3
regsave
mov ebx,%2
add ebx,%3
mov %1,ebx
regload
%endmacro

%macro wadd 3
regsave
mov bx,%2
add bx,%3
mov %1,bx
regload
%endmacro

%macro badd 3
regsave
mov bl,%2
add bl,%3
mov %1,bl
regload
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dsub 3
regsave
mov ebx,%2
sub ebx,%3
mov %1,ebx
regload
%endmacro

%macro wsub 3
regsave
mov bx,%2
sub bx,%3
mov %1,bx
regload
%endmacro

%macro bsub 3
regsave
mov bl,%2
sub bl,%3
mov %1,bl
regload
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dmul 3
regsave
mov eax,%2
mov ebx,%3
mul ebx
mov %1,eax
regload
%endmacro

%macro wmul 3
regsave
mov ax,%2
mov bx,%3
mul bx
mov %1,ax
regload
%endmacro

%macro bmul 3
regsave
mov al,%2
mov bl,%3
mul bl
mov %1,bl
regload
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dudiv 3
regsave
mov eax,%2
mov ebx,%3
mov edx,0
div ebx
mov %1,eax
regload
%endmacro

%macro wudiv 3
regsave
mov ax,%2
mov bx,%3
mov dx,0
div bx
mov %1,ax
regload
%endmacro

%macro budiv 3
regsave
mov al,%2
mov bl,%3
div bl
mov %1,al
regload
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dsdiv 3
regsave
mov eax,%2
mov ebx,%3
mov edx,0
idiv ebx
mov %1,eax
regload
%endmacro

%macro wsdiv 3
regsave
mov ax,%2
mov bx,%3
mov dx,0
idiv bx
mov %1,ax
regload
%endmacro

%macro bsdiv 3
regsave
mov al,%2
mov bl,%3
idiv bl
mov %1,al
regload
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dumod 3
regsave
mov eax,%2
mov ebx,%3
mov edx,0
div ebx
mov %1,edx
regload
%endmacro

%macro wumod 3
regsave
mov ax,%2
mov bx,%3
mov dx,0
div bx
mov %1,dx
regload
%endmacro

%macro bumod 3
regsave
mov al,%2
mov bl,%3
div bl
mov %1,ah
regload
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dsmod 3
regsave
mov eax,%2
mov ebx,%3
mov edx,0
idiv ebx
mov %1,edx
regload
%endmacro

%macro wsmod 3
regsave
mov ax,%2
mov bx,%3
mov dx,0
idiv bx
mov %1,dx
regload
%endmacro

%macro bsmod 3
regsave
mov al,%2
mov bl,%3
idiv bl
mov %1,ah
regload
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dslt 3
regsave
mov eax,%1
mov ebx,%2
cmp eax,ebx
jl %3
regload
%endmacro

%macro wslt 3
regsave
mov ax,%1
mov bx,%2
cmp ax,bx
jl %3
regload
%endmacro

%macro bslt 3
regsave
mov al,%1
mov bl,%2
cmp al,bl
jl %3
regload
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dsle 3
regsave
mov eax,%1
mov ebx,%2
cmp eax,ebx
jle %3
regload
%endmacro

%macro wsle 3
regsave
mov ax,%1
mov bx,%2
cmp ax,bx
jle %3
regload
%endmacro

%macro bsle 3
regsave
mov al,%1
mov bl,%2
cmp al,bl
jle %3
regload
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dsgt 3
regsave
mov eax,%1
mov ebx,%2
cmp eax,ebx
jg %3
regload
%endmacro

%macro wsgt 3
regsave
mov ax,%1
mov bx,%2
cmp ax,bx
jg %3
regload
%endmacro

%macro bsgt 3
regsave
mov al,%1
mov bl,%2
cmp al,bl
jg %3
regload
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dsge 3
regsave
mov eax,%1
mov ebx,%2
cmp eax,ebx
jge %3
regload
%endmacro

%macro wsge 3
regsave
mov ax,%1
mov bx,%2
cmp ax,bx
jge %3
regload
%endmacro

%macro bsge 3
regsave
mov al,%1
mov bl,%2
cmp al,bl
jge %3
regload
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro deq 3
regsave
mov eax,%1
mov ebx,%2
cmp eax,ebx
je %3
regload
%endmacro

%macro weq 3
regsave
mov ax,%1
mov bx,%2
cmp ax,bx
je %3
regload
%endmacro

%macro beq 3
regsave
mov al,%1
mov bl,%2
cmp al,bl
je %3
regload
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dne 3
regsave
mov eax,%1
mov ebx,%2
cmp eax,ebx
jne %3
regload
%endmacro

%macro wne 3
regsave
mov ax,%1
mov bx,%2
cmp ax,bx
jne %3
regload
%endmacro

%macro bne 3
regsave
mov al,%1
mov bl,%2
cmp al,bl
jne %3
regload
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dult 3
regsave
mov eax,%1
mov ebx,%2
cmp eax,ebx
jb %3
regload
%endmacro

%macro wult 3
regsave
mov ax,%1
mov bx,%2
cmp ax,bx
jb %3
regload
%endmacro

%macro bult 3
regsave
mov al,%1
mov bl,%2
cmp al,bl
jb %3
regload
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dule 3
regsave
mov eax,%1
mov ebx,%2
cmp eax,ebx
jbe %3
regload
%endmacro

%macro wule 3
regsave
mov ax,%1
mov bx,%2
cmp ax,bx
jbe %3
regload
%endmacro

%macro bule 3
regsave
mov al,%1
mov bl,%2
cmp al,bl
jbe %3
regload
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dugt 3
regsave
mov eax,%1
mov ebx,%2
cmp eax,ebx
ja %3
regload
%endmacro

%macro wugt 3
regsave
mov ax,%1
mov bx,%2
cmp ax,bx
ja %3
regload
%endmacro

%macro bugt 3
regsave
mov al,%1
mov bl,%2
cmp al,bl
ja %3
regload
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro duge 3
regsave
mov eax,%1
mov ebx,%2
cmp eax,ebx
jae %3
regload
%endmacro

%macro wuge 3
regsave
mov ax,%1
mov bx,%2
cmp ax,bx
jae %3
regload
%endmacro

%macro buge 3
regsave
mov al,%1
mov bl,%2
cmp al,bl
jae %3
regload
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro dinc 1
regsave
inc dword %1
regload
%endmacro

%macro winc 1
regsave
inc dword %1
regload
%endmacro

%macro binc 1
regsave
inc dword %1
regload
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro ddec 1
regsave
dec dword %1
regload
%endmacro

%macro wdec 1
regsave
dec dword %1
regload
%endmacro

%macro bdec 1
regsave
dec dword %1
regload
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro darray 1
regsave
section .data
len_ %+ %1 dd 0
size_ %+ %1 dd 4
%1 times 1024 dd 0
section .text
regload
%endmacro

%macro warray 1
regsave
section .data
len_ %+ %1 dd 0
size_ %+ %1 dd 2
%1 times 1024 dw 0
section .text
regload
%endmacro

%macro barray 1
regsave
section .data
len_ %+ %1 dd 0
size_ %+ %1 dd 1
%1 times 1024 db 0
section .text
regload
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro aget 3
regsave
mov edx,%2
daget ecx,edx,-1
cmp ecx,1
je %%_1
cmp ecx,2
je %%_2
cmp ecx,4
je %%_4
%%_1:
baget %1,edx,%3
jmp %%_5
%%_2:
waget %1,edx,%3
jmp %%_5
%%_4:
daget %1,edx,%3
jmp %%_5
%%_5:
regload
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro aput 3
regsave
mov edx,%1
daget ecx,edx,-1
cmp ecx,1
je %%_1
cmp ecx,2
je %%_2
cmp ecx,4
je %%_4
%%_1:
baput edx,%2,%3
jmp %%_5
%%_2:
waput edx,%2,%3
jmp %%_5
%%_4:
daput edx,%2,%3
jmp %%_5
%%_5:
regload
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; %macro apush 2
; regsave
; mov ebx,%1
; mov ecx,[ebx-2]
; aput ebx,ecx,%2
; inc ecx
; mov [ebx-2],ecx
; regload
; %endmacro
