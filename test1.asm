
extern printf
extern scanf

section .data
_q dq 0
_sctmp dq 0
_prstr db "%u",10,0
_scstr db "%i",0



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
	push rax
	push rsi
	push rdi
mov rsi,_sctmp
mov rdi,_scstr
mov rax,0
call scanf
	pop rdi
	pop rsi
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

	push rax
	push rsi
	push rdi
mov rsi,[mas + 4 * eax]
mov rdi,_prstr
mov rax,0
call printf
	pop rdi
	pop rsi
	pop rax


	inc eax
	cmp eax, 16
jl print_





mov eax,1
mov ebx,0
int 0x80
