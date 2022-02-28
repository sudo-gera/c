;; File stud_io.inc for Linux O.S.
;; Copyright (c) Andrey Vikt. Stolyarov, 2009.
;; I, the author, hereby grant everyone the right to use this
;; file for any purpose, in any manner, in it's original or
;; modified form, provided that any modified versions are
;; clearly marked as such.
;; file changed, macros added (by Divari I.N.,
;; Department of computer science, MIPT, 2019-2020) 

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; system dependend part

; generic 3-param syscall
%macro _syscall_3 4
	push edx
	push ecx
	push ebx ; it is senseless to save eax as it holds the return
	push %1
	push %2
	push %3
	push %4
	pop edx
	pop ecx
	pop ebx
	pop eax 
	int 0x80
	pop ebx
	pop ecx
	pop edx
%endmacro

; syscall_exit is the only syscall we use that has 1 parameter
%macro _syscall_exit 1
	mov ebx, %1	; exit code
	mov eax, 1	; 1 = sys_exit
	int 0x80
%endmacro

;; system dependent part ends here
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; %1: descriptor   %2: buffer addr   %3: buffer length 
; output: eax: read bytes
%macro _syscall_read 3
	_syscall_3 3,%1,%2,%3
%endmacro

; %1: descriptor   %2: buffer addr   %3: buffer length 
; output: eax: written bytes
%macro _syscall_write 3
	_syscall_3 4,%1,%2,%3
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
%macro 	PRINT 1
	pusha
	pushf
	jmp %%astr
%%str	db	%1, 0
%%strln	equ	$-%%str
%%astr:	_syscall_write 1, %%str, %%strln
	popf
	popa
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
%macro	PUTCHAR 1
	pusha
	pushf
%ifstr %1
	mov	al, %1
%elifnum %1
	mov	al, %1
%elifidni %1,al
	nop
%elifidni %1,ah
	mov	al, ah
%elifidni %1,bl
	mov	al, bl
%elifidni %1,bh
	mov	al, bh
%elifidni %1,cl
	mov	al, cl
%elifidni %1,ch
	mov	al, ch
%elifidni %1,dl
	mov	al, dl
%elifidni %1,dh
	mov	al, dh
%else
	mov	al, %1  ; let's hope it is a memory location such as [var]
%endif
	sub	esp, 2  ; reserve memory for buffer
	mov	edi, esp
	mov	[edi], al
	_syscall_write 1, edi, 1
	add	esp, 2
	popf
	popa
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
%macro	GETCHAR 0
	pushf
	push	edi
	sub	esp, 2
	mov	edi, esp
	_syscall_read 0, edi, 1
	cmp	eax, 1
	jne	%%eof_reached
	xor	eax,eax
	mov	al, [edi]
	jmp	%%gcquit
%%eof_reached:
	xor	eax, eax
	not	eax 		; eax := -1
%%gcquit:
	add	esp, 2
	pop	edi
	popf
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
%macro FINISH 0-1 0
	_syscall_exit %1
%endmacro
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
%macro UNSINT 1
pusha
pushf
push dword %1
pop eax
mov edi,eax
mov esi,10
  xor ebx,ebx
%%m1:
   xor edx,edx
   div esi
   inc ebx
   cmp eax,0
   jne %%m1
    
   mov eax,1
   mov ecx,ebx
   dec ecx
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    cmp ecx,0
     je %%m4
%%m2:  mul esi
       loop %%m2

       mov ebx,eax

%%m3:       
      mov eax,edi 
      xor edx,edx 
      div ebx
      add al,'0'
      PUTCHAR al
      mov edi,edx
      xor edx,edx
      mov eax,ebx
      div esi
      cmp eax,1
      je %%m4
      mov ebx,eax
      jmp %%m3
 %%m4:      
      mov edx,edi
      add dl,'0'
      PUTCHAR dl
       
  
popf
popa
%endmacro
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
%macro SIGNINT 1
pusha
pushf
push dword %1
pop eax
    cmp eax,0
    jge %%m5
    PUTCHAR '-'
    neg eax
%%m5:
      UNSINT eax
popf
popa
%endmacro
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
%macro GETUN 1
pushad
pushfd
;;;;;;;;;;;;;;;;;;;;;;
xor edi,edi
xor esi,esi
%%m1:
GETCHAR
cmp al,0xA
je %%m2
cmp al,'0'
jb %%m_err
cmp al,'9'
ja %%m_err
inc edi
xor ecx,ecx
mov cl,al
mov eax,esi
mov ebx,10
mul ebx
sub cl,48
add eax,ecx
jc %%m3
mov esi,eax
jmp %%m1
%%m2: 
cmp edi,0
je %%m1
jmp %%m4
%%m3: PRINT "too big number"
PUTCHAR 10
jmp %%m4
%%m_err: PRINT "ERROR!!!"
PUTCHAR 0xa
%%m4:
;;;;;;;;;;;;;;;;;;
push esi
add esp,4
popfd
popad
sub esp,40
pop dword %1
add esp,36
%endmacro
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
%macro GETSIG 1
pushad
pushfd
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
xor edi,edi
xor esi,esi
mov ebx,10
%%m_st1: GETCHAR
cmp al,0xa
je %%m_st1
cmp al,'-'
jne %%s1
mov ebx,-10
push ebx
GETCHAR
cmp al,0xa
je %%m_err
jmp %%m_st21
%%s1: push ebx 
cmp al,'+'
jne %%m_st21
GETCHAR 
cmp al,0xa
je %%m_err
jmp %%m_st21
%%m_st2: GETCHAR
%%m_st21:  cmp al,0xa
je %%pr_end
cmp al,'0'
jb %%m_err
cmp al,'9'
ja %%m_err
inc edi
xor ecx,ecx
mov cl,al
mov eax,esi
imul ebx
sub cl,48
cmp dword[esp],-10
je %%j_s
add eax,ecx
jmp %%j_per
%%j_s: sub eax,ecx
%%j_per: jo %%m_b
mov esi,eax
cmp dword[esp],-10
jne %%m_st2
neg esi
jmp %%m_st2
%%pr_end:  cmp edi,0
je %%m_st2
jmp %%m_k
;;;;;;;;;
%%m_err: pop ebx 
PRINT "ERROR"
PUTCHAR 0xa
jmp %%m_end
%%m_b: pop ebx 
cmp ebx,-10
je  %%m_l
PRINT "too big"
PUTCHAR 0xa
jmp %%m_end
%%m_l: PRINT "too less"
PUTCHAR 0xa
jmp %%m_end
%%m_k: pop ebx
cmp ebx,-10
jne %%m_p
neg esi 
%%m_p: 

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

push esi
add esp,4
popfd
popad
sub esp,40
pop dword %1
add esp,36
jmp %%mm_e
%%m_end:
popfd
popad
%%mm_e:
%endmacro
