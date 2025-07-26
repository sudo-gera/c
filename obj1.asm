
obj1.o:	file format elf64-x86-64

Disassembly of section .text:

0000000000000000 <calc>:
       0: 55                           	push	rbp
       1: 48 89 e5                     	mov	rbp, rsp
       4: 89 7d ec                     	mov	dword ptr [rbp - 20], edi
       7: 89 75 e8                     	mov	dword ptr [rbp - 24], esi
       a: c7 45 f8 00 00 00 00         	mov	dword ptr [rbp - 8], 0
      11: c7 45 fc 01 00 00 00         	mov	dword ptr [rbp - 4], 1
      18: eb 0e                        	jmp	0x28 <calc+0x28>
      1a: 8b 45 fc                     	mov	eax, dword ptr [rbp - 4]
      1d: 0f af 45 e8                  	imul	eax, dword ptr [rbp - 24]
      21: 89 45 fc                     	mov	dword ptr [rbp - 4], eax
      24: 83 45 f8 01                  	add	dword ptr [rbp - 8], 1
      28: 8b 45 f8                     	mov	eax, dword ptr [rbp - 8]
      2b: 3b 45 ec                     	cmp	eax, dword ptr [rbp - 20]
      2e: 7c ea                        	jl	0x1a <calc+0x1a>
      30: 8b 45 fc                     	mov	eax, dword ptr [rbp - 4]
      33: 5d                           	pop	rbp
      34: c3                           	ret
