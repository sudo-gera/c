
uran.o:	file format elf32-i386

Disassembly of section .text:

00000000 <accelerate>:
       0: 55                           	push	ebp
       1: 89 e5                        	mov	ebp, esp
       3: 81 ec 14 00 00 00            	sub	esp, 20
       9: d9 45 08                     	fld	dword ptr [ebp + 8]
       c: d9 45 08                     	fld	dword ptr [ebp + 8]
       f: d8 c1                        	fadd	st, st(1)
      11: d9 5d fc                     	fstp	dword ptr [ebp - 4]
      14: 8b 45 fc                     	mov	eax, dword ptr [ebp - 4]
      17: 89 45 ec                     	mov	dword ptr [ebp - 20], eax
      1a: d9 45 ec                     	fld	dword ptr [ebp - 20]
      1d: c9                           	leave
      1e: c3                           	ret
