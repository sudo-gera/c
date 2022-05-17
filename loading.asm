section .data
ll dd 32 ,9410274, 9344738, 9279202, 9213666, 9148130, 9082594, 9017058, 8951522,13,32
w dq 0
e dq 0
r dq 0
l dq 0
v dq 0
f dq 0
global main

main:

mov rax,16
mov rdi,1
mov rsi,0x5413
mov rdx,l
syscall

mov rax,0
mov ax,[l+2]
mov rbp,rax

mov rax,1
mov rdi,1
mov rdx,4

mov qword [w],0
_1:
cmp qword [w],rbp
je _2
	mov qword [v],ll
	_3:
	cmp qword [v],ll+8*4
	je _4
		mov qword [f],0
		_5:
		cmp qword [f],8
		je _6
			mov qword [e],0
			_7:
			mov rbx,[e]
			cmp rbx,[w]
			je _8
				mov rax,1
				mov rsi,ll+32
				syscall
			inc qword [e]
			jmp _7
			_8:
			sub rbp,[w]
			mov [r],rbp
			add ebp,[w]
			mov rax,1
			mov rsi,qword [v]
			syscall
			dec qword [r]
			mov qword [e],0
			_9:
			mov rbx,[e]
			cmp rbx,[r]
			je _10
				mov rax,1
				mov rsi,ll
				syscall
			inc qword [e]
			jmp _9
			_10:
			mov rax,1
			mov rsi,ll+36
			syscall
		inc qword [f]
		jmp _5
		_6:
		add qword [v],4
	jmp _3
	_4:
inc qword [w]
jmp _1
_2:

mov qword [v],0
_11:
cmp qword [v],8
je _12
	mov qword [w],0
	_13:
	cmp qword [w],rbp
	je _14
		mov rax,1
		mov rsi,ll+32
		syscall
	inc qword [w]
	jmp _13
	_14:
	mov rax,1
	mov rsi,ll+36
	syscall
inc qword [v]
jmp _11
_12:


mov qword [w],0
_15:
cmp qword [w],rbp
je _16
	mov rax,1
	mov rsi,ll+40
	syscall
inc qword [w]
jmp _15
_16:

mov rax,1
mov rsi,ll+36
syscall

mov rax,0x3C
mov rbx,0
syscall

