
extern printf
extern scanf

section .data
_q dq 0
_sctmp dq 0
<<<<<<< HEAD
=======
_prstr db "%u",10,0
_scstr db "%i",0

>>>>>>> 49ce0d89a0ab6076190c132564bc397e3a6ff68e


global _start
global main

section .bss

mas resd 16
chis resd 1

section .text

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
<<<<<<< HEAD
	mov [_q],rsp
	push rax
	push rcx
	push rdx
	push rbx
	push qword [_q]
	push rbp
	push rsi
	push rdi
sub rsp,4096
jmp ______8_2
______8_1:
db "%i",0
______8_2:
push qword 0
mov rsi,_sctmp
mov rdi,______8_1
mov rax,0
call scanf
add rsp,8
add rsp,4096
	pop rdi
	pop rsi
	pop rbp
	add rsp,8
	pop rbx
	pop rdx
	pop rcx
=======
	push rax
	push rsi
	push rdi
mov rsi,_sctmp
mov rdi,_scstr
mov rax,0
call scanf
	pop rdi
	pop rsi
>>>>>>> 49ce0d89a0ab6076190c132564bc397e3a6ff68e
	pop rax
push qword [_sctmp]
pop qword [chis]

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

<<<<<<< HEAD
	mov [_q],rsp
	push rax
	push rcx
	push rdx
	push rbx
	push qword [_q]
	push rbp
	push rsi
	push rdi
sub rsp,4096
jmp ______11_2
______11_1:
db "%u",10,0
______11_2:
mov rsi,[mas + 4 * eax]
mov rdi,______11_1
mov rax,0
call printf
add rsp,4096
	pop rdi
	pop rsi
	pop rbp
	add rsp,8
	pop rbx
	pop rdx
	pop rcx
=======
	push rax
	push rsi
	push rdi
mov rsi,[mas + 4 * eax]
mov rdi,_prstr
mov rax,0
call printf
	pop rdi
	pop rsi
>>>>>>> 49ce0d89a0ab6076190c132564bc397e3a6ff68e
	pop rax


	inc eax
	cmp eax, 16
jl print_





mov eax,1
mov ebx,0
int 0x80
