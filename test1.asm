%line 160+1 best_io.inc
[section .data]
[sectalign 16]
%line 161+0 best_io.inc
times (((16) - (($-$$) % (16))) % (16)) db 0
%line 162+1 best_io.inc
times 16*16*16*16 db 0
__best__fake_stack dd __best__fake_stack,0


%line 174+1 best_io.inc

[section .text]

%line 184+1 best_io.inc

%line 196+1 best_io.inc

%line 208+1 best_io.inc

%line 218+1 best_io.inc

%line 186+1 test.asm
 __best__putstr:
%line 190+1 test.asm
 db 'PQRSTUVW'

 mov ecx,[esp+(8+2)*4]
%line 192+0 test.asm
 mov edx,[esp+(8+1)*4]
%line 211+0 test.asm
 sub edx,ecx
%line 181+0 test.asm
 mov eax, 3 + 1
 mov ebx, 2 - 1
%line 214+0 test.asm
 mov esi,ecx
%line 181+0 test.asm
 int 0x80
%line 202+0 test.asm
 db '_^]X[ZYX'
%line 204+0 test.asm
 pop dword [esp]
 pop dword [esp]
%line 206+0 test.asm
 ret
%line 220+0 test.asm

%line 186+0 test.asm
 __best__getstr:
%line 190+0 test.asm
 db 'PQRSTUVW'
%line 192+0 test.asm
 mov ecx,[esp+(8+2)*4]
 mov edx,[esp+(8+1)*4]
%line 211+0 test.asm
 sub edx,ecx
%line 181+0 test.asm
 mov eax, 3 + 0
 mov ebx, 2 - 0
%line 214+0 test.asm
 mov esi,ecx
%line 181+0 test.asm
 int 0x80
%line 202+0 test.asm
 db '_^]X[ZYX'
%line 204+0 test.asm
 pop dword [esp]
 pop dword [esp]
%line 206+0 test.asm
 ret
%line 222+0 test.asm

%line 231+0 test.asm

%line 232+1 test.asm
__best__putchar_s: 
%line 224+1 test.asm
 push esp
 add dword [esp],4
 push esp
 add dword [esp],4*2+1
 call __best__putstr*1+__best__getstr*(1-1)
 ret
%line 233+1 test.asm

__best__getchar_s: 
%line 224+1 test.asm
 push esp
 add dword [esp],4
 push esp
 add dword [esp],4*2+1
 call __best__putstr*0+__best__getstr*(1-0)
 ret
%line 235+1 test.asm

%line 186+1 test.asm
 __best__putchar:
%line 190+1 test.asm
 db 'PQRSTUVW'

 mov eax,[esp+(8+1)*4]
%line 237+1 test.asm
 push eax
 call __best__putchar_s
 add esp,4
%line 202+1 test.asm
 db '_^]X[ZYX'

 pop dword [esp]

 ret
%line 241+1 test.asm

%line 186+1 test.asm
 __best__getchar:

 push dword [esp]

 db 'PQRSTUVW'
%line 243+1 test.asm
 push dword 0
 call __best__getchar_s
 pop eax
%line 199+1 test.asm
 mov [esp+(8+1)*4],eax
%line 202+1 test.asm
 db '_^]X[ZYX'
%line 206+1 test.asm
 ret
%line 247+1 test.asm

%line 186+1 test.asm
 __best__putuint:
%line 190+1 test.asm
 db 'PQRSTUVW'

 mov eax,[esp+(8+1)*4]
%line 249+1 test.asm
 mov ebx,esp
 mov ebp,esp
 sub esp,80
 mov edx,0
 mov edi,10
 mov cx,20
 __best__20:
 div edi
 add dl,48
 dec ebx
 mov [ebx],dl
 mov dx,0
 cmp eax,0
 loopne __best__20
 push ebx
 push ebp
 call __best__putstr
 add esp,80
%line 202+1 test.asm
 db '_^]X[ZYX'

 pop dword [esp]

 ret
%line 268+1 test.asm

%line 186+1 test.asm
 __best__putsint:
%line 190+1 test.asm
 db 'PQRSTUVW'

 mov eax,[esp+(8+1)*4]
%line 270+1 test.asm
 cmp eax,0
 jge __best__33
 push dword '-'
 call __best__putchar
 neg eax
 __best__33:
 push eax
 call __best__putuint
%line 202+1 test.asm
 db '_^]X[ZYX'

 pop dword [esp]

 ret
%line 279+1 test.asm

%line 186+1 test.asm
 __best__getint:

 push dword [esp]

 db 'PQRSTUVW'
%line 281+1 test.asm
 mov eax,0
 mov ebx,0
 mov ecx,0
 push word 0
 mov cl,10
 __best__70:
 call __best__getchar_s
 mov bl,byte [esp]
 sub bl,48
 cmp bl,253
 jne __best__30
 mov byte [esp+1],1
 __best__30:
 cmp bl,9
 ja __best__70
 jmp __best__71
 __best__32:
 call __best__getchar_s
 mov bl,byte [esp]
 sub bl,48
 __best__71:
 cmp bl,9
 ja __best__31
 mul ecx
 add eax,ebx
 jmp __best__32
 __best__31:
 mov bl,0
 cmp [esp+1],bl
 je __best__18
 neg eax
 __best__18:
 add esp,2
%line 199+1 test.asm
 mov [esp+(8+1)*4],eax
%line 202+1 test.asm
 db '_^]X[ZYX'
%line 206+1 test.asm
 ret
%line 315+1 test.asm

[section .data]
__best__putreg_names_pos dd 64,56,49,42,35,28,21,14,7,0
__best__putreg_names:
 db 'e','ax == ','e','bx == ','e','cx == ',
 db 'e','dx == ','e','si == ','e','di == ',
 db 'e','bp == ','e','sp == ', 'line == 0'
__best__putreg_stack_pos:
 dd 4*0,4*18,4*3,4*2,4*0
 dd 4*1,4*5 ,4*6,4*4,4*7

[section .text]
%line 186+1 test.asm
 __best__put_reg:
%line 190+1 test.asm
 db 'PQRSTUVW'
%line 328+1 test.asm
 mov ecx,9
 mov edx,__best__fake_stack
 sub edx,esp
 cmp edx,16*16*16*16
 jae __best__51
 mov eax,[__best__fake_stack]
 mov dword[esp+4*3],eax
 jmp __best__50
 __best__51:
 add dword[esp+4*3],4*15
 __best__50:
 push dword [__best__putreg_names_pos+ecx*4]
 add dword[esp],__best__putreg_names
 push dword [__best__putreg_names_pos-4+4*ecx]
 add dword[esp],__best__putreg_names
 call __best__putstr
 mov eax,[__best__putreg_stack_pos+ecx*4]
 mov eax,[__best__putreg_stack_pos+ecx*4]
 add eax,esp
 push dword[eax]
 call __best__putsint
 push dword 9
 call __best__putchar
 loop __best__50
%line 202+1 test.asm
 db '_^]X[ZYX'
%line 206+1 test.asm
 ret
%line 353+1 test.asm

%line 186+1 test.asm
 __best__printreg:
%line 190+1 test.asm
 db 'PQRSTUVW'
%line 355+1 test.asm
 call __best__put_reg
 push dword 10
 call __best__putchar
%line 202+1 test.asm
 db '_^]X[ZYX'

 pop dword [esp]

 ret
%line 359+1 test.asm

%line 186+1 test.asm
 __best__writereg:
%line 190+1 test.asm
 db 'PQRSTUVW'
%line 361+1 test.asm
 call __best__put_reg
 push dword 32
 call __best__putchar
%line 202+1 test.asm
 db '_^]X[ZYX'

 pop dword [esp]

 ret
%line 365+1 test.asm

%line 186+1 test.asm
 __best__putreg:
%line 190+1 test.asm
 db 'PQRSTUVW'
%line 367+1 test.asm
 call __best__put_reg
%line 202+1 test.asm
 db '_^]X[ZYX'

 pop dword [esp]

 ret
%line 369+1 test.asm

__best__movzx_dword_to_qword:
%line 181+1 test.asm
 
%line 181+0 test.asm
 
%line 373+0 test.asm
ret
%line 374+1 test.asm


__best__call_putint_for_sbyte:
 cbw
__best__call_putint_for_sword:
 cwde
__best__call_putint_for_sdword:
%line 181+1 test.asm
 
%line 382+1 test.asm
__best__call_putint_for_sqword:
 push eax
 call __best__putsint
ret

__best__call_putint_for_ubyte:
 shl eax,0-8
 shr eax,0-8
__best__call_putint_for_uword:
 shl eax,0-16
 shr eax,0-16
__best__call_putint_for_udword:
 shl eax,0-32
 shr eax,0-32
__best__call_putint_for_uqword:
 push eax
 call __best__putuint
ret

__best__call_putchar:
 push eax
 call __best__putsint
ret

%line 419+1 test.asm

%line 435+1 test.asm

%line 454+1 test.asm

%line 467+1 test.asm

%line 476+1 test.asm

%line 483+1 test.asm

%line 494+1 test.asm

%line 505+1 test.asm

%line 516+1 test.asm

%line 520+1 test.asm

%line 524+1 test.asm

%line 544+1 test.asm

%line 552+1 test.asm




%line 526+1 test.asm
 ..@41.begin_start:
[section .text]
%line 532+1 test.asm
[global _start]
 _start:

 mov eax,0
 mov ebx,0
 mov ecx,0
 mov edx,0
 mov esi,0
 mov edi,0
 mov ebp,0
 ..@41.end_start:
%line 437+1 test.asm
 ..@44.begin__best__getint:
 xchg esp,[__best__fake_stack]
 call __best__getint
%line 448+1 test.asm
 pop dword eax
 add esp,4-32/8

 xchg esp,[__best__fake_stack]
 ..@44.end__best__getint:
%line 4+1 test.asm
 call root
%line 421+1 test.asm
 ..@45.begin__best__call_putint_for_udword:
 mov [__best__fake_stack+4],eax

 mov eax,ebx
 xchg esp,[__best__fake_stack]
 call __best__call_putint_for_udword

 push dword 10
 call __best__putchar

 xchg esp,[__best__fake_stack]
 mov eax,[__best__fake_stack+4]
 ..@45.end__best__call_putint_for_udword:
%line 546+1 test.asm
 ..@46.begin_stop:
%line 181+1 test.asm
 mov eax,1
%line 181+0 test.asm
 mov ebx,0
 int 0x80
%line 550+0 test.asm
 ..@46.end_stop:
%line 7+0 test.asm

%line 8+1 test.asm

root:
 mov ebx,0
 mov ecx,1<<(0-2)
 _2:
 lea edx,[ebx+ecx]
 cmp eax,edx
 jb _1
 sub eax,edx
 lea ebx,[ebx+ecx*2]
 _1:
 shr ebx,1
 shr ecx,2
 jnz _2
 mov eax,ebx
ret
