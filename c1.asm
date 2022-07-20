extern printf
extern scanf

section .data
mz_g dq 0
mz_w dq 0
mz_e dq 0
mz_l dq 0
mz_m dq 1
mz_n dq 1
mz_c dq 0
mz_f dq 0
mz_a dq 1024
section .text

make_zero:
	push rax
	push rbx
	push rcx
	push rdx
	push rsi
	push rdi
	push rbp
	push rbp
	add rsp,9*8
	pop qword [mz_l]
	pop rbx
	pop rbp
	sub rsp,8*8+8*4
	push qword -1
	push qword -1
	mov qword [mz_w],0
	for_1:
	mov rax,[mz_w]
	cmp rax,[mz_l]
	jae for_2
		mov qword [mz_e],0
		for_3:
		mov rax,[mz_e]
		cmp rax,[mz_w]
		jae for_4
			mov rax,[mz_w]
			mul rbx
			lea rax,[rax*8]
			add rax,rbp
			mov rsi,rax
			mov rax,[mz_e]
			mul rbx
			lea rax,[rax*8]
			add rax,rbp
			mov rdi,rax
			mov rcx,rbx
			cld
			rep cmpsq
			jne not_eq
				sub rdi,8
				std
				mov rcx,rbx
				mov rax,0
				rep stosq
			not_eq:
		inc qword [mz_e]
		jmp for_3
		for_4:
	inc qword [mz_w]
	jmp for_1
	for_2:
	add rsp,8*2
	pop rbp
	pop rbp
	pop rdi
	pop rsi
	pop rdx
	pop rcx
	pop rbx
	pop rax
	ret


section .text
global main
main:











jmp _1_2
_1_1:
db "%li",0
_1_2:
push qword 0
mov rsi,mz_g
mov rdi,_1_1
mov rax,0
call scanf
add rsp,8

push qword [mz_g]
pop qword [mz_n]



jmp _2_2
_2_1:
db "%li",0
_2_2:
push qword 0
mov rsi,mz_g
mov rdi,_2_1
mov rax,0
call scanf
add rsp,8

push qword [mz_g]
pop qword [mz_m]











mov qword [mz_c],0
mov qword [mz_w],0
_1:
mov rax,[mz_w]
cmp rax,[mz_n]
jae _2
	mov qword [mz_e],0
	_3:
	mov rax,[mz_e]
	cmp rax,[mz_m]
	jae _4
			jmp _3_2
			_3_1:
			db "%li",0
			_3_2:
			push qword 0
			mov rsi,mz_g
			mov rdi,_3_1
			mov rax,0
			call scanf
			add rsp,8

			push qword [mz_g]
			pop qword [mz_f]
		mov rax,[mz_c]
		lea rax,[mz_a+rax*8]
		mov rdx,[mz_f]
		mov [rax],rdx
		inc qword [mz_c]
	inc qword [mz_e]
	jmp _3
	_4:
inc qword [mz_w]
jmp _1
_2:

push qword mz_a
push qword [mz_m]
push qword [mz_n]
call make_zero
add rsp,8*3

mov qword [mz_c],0
mov qword [mz_w],0
__1:
mov rax,[mz_w]
cmp rax,[mz_n]
jae __2
	mov qword [mz_e],0
	__3:
	mov rax,[mz_e]
	cmp rax,[mz_m]
	jae __4
		mov rax,[mz_c]
		lea rax,[mz_a+rax*8]
		mov rax,[rax]
		mov [mz_f],rax
			jmp _4_2
			_4_1:
			db "%li ",0
			_4_2:
			mov rsi,[mz_f]
			mov rdi,_4_1
			mov rax,0
			call printf
		inc qword [mz_c]
	inc qword [mz_e]
	jmp __3
	__4:
		jmp _5_2
		_5_1:
		db 10,0
		_5_2:
		mov rsi,0
		mov rdi,_5_1
		mov rax,0
		call printf
inc qword [mz_w]
jmp __1
__2:

