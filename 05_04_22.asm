section .data
aa times 999 db 0
yy db 121,10
nn db 110,10
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



global _start
section .text
_start:

mov eax,3
mov ebx,2
mov ecx,aa
mov edx,999
int 0x80
mov dword [e],aa
push dword 0
mov dword [g],0
_while:
	mov dword [c],0
	mov esi,[e]
	mov eax,0
	mov al,[esi]
	mov [c],al
	cmp [c],dword 10
	jne cont
		jmp _lend
	cont:
	cmp [c],dword '('
	jne _1
		inc dword [g]
		mov dword [z],')'
		push dword [z]
	_1:
	cmp [c],dword'['
	jne _2
		inc dword [g]
		mov dword [z],']'
		push dword [z]
	_2:
	cmp [c],dword'{'
	jne _3
		inc dword [g]
		mov dword [z],'}'
		push dword [z]
	_3:
	cmp [c],dword')'
	jne _4
		cmp [g],dword 0
		jge ___4
			jmp _nend
		___4:
		dec dword [g]
		pop dword [d]
		mov eax,[d]
		cmp eax,[c]
		je __4
			jmp _nend
		__4:
	_4:
	cmp [c],dword']'
	jne _5
		cmp [g],dword 0
		jge ___5
			jmp _nend
		___5:
		dec dword [g]
		pop dword [d]
		mov eax,[d]
		cmp eax,[c]
		je __5
			jmp _nend
		__5:
	_5:
	cmp [c],dword'}'
	jne _6
		cmp [g],dword 0
		jge ___6
			jmp _nend
		___6:
		dec dword [g]
		pop dword [d]
		mov eax,[d]
		cmp eax,[c]
		je __6
			jmp _nend
		__6:
	_6:
	inc dword [e]
jmp _while
_lend:
cmp [g],dword 0
je _yend
	jmp _nend
_yend:

mov eax,4
mov ebx,1
mov ecx,yy
mov edx,2
int 0x80

jmp _end

_nend:
mov eax,4
mov ebx,1
mov ecx,nn
mov edx,2
int 0x80

_end:


mov eax,1
mov ebx,0
int 0x80
