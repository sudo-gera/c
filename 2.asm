	%macro pushad 0
		mov [ad_tmp],rsp
		push rax
		push rcx
		push rdx
		push rbx
		push qword [ad_tmp]
		push rbp
		push rsi
		push rdi
	%endmacro
	%macro popad 0
		pop rdi
		pop rsi
		pop rbp
		add rsp,8
		pop rbx
		pop rdx
		pop rcx
		pop rax
	%endmacro

extern printf
extern scanf

section .data
ad_tmp dq 0
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
add rsp,8
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


global _start
global main


section .data

section .bss

mas resd 16
chis resd 1

section .text
; _start:
main:

mov ecx, 16
mov eax, 0
mov ebx, 11111111111111111111111111111111b
putt:
	mov [mas + 4 * eax], ebx
	inc eax
loop putt

mov eax, 5

scan:
	scan_f "%i",[chis]
	; GETUN dword [chis]
	mov ebx, 11111111111111111111111111111110b
	mov ecx, [chis]
	shl ecx, 11
	shr ecx, 11
	shr dword [chis], 5
	rol ebx, cl
	mov ecx, ebx
	mov ebx, [chis]
	and [mas + 4 * ebx], ecx
	dec eax
	cmp eax, 0
jg scan

mov eax, 0
print_:
	; duprint [mas + 4 * eax]
	print_f {"%u",10},[mas + 4 * eax]
	; UNSINT [mas + 4 * eax]
	; PUTCHAR 0xA
	inc eax
	cmp eax, 16
jl print_
	
;PUTCHAR 0xA
; FINISH
; stop

mov eax,1
mov ebx,0
int 0x80
