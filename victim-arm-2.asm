In archive libleap.a-2:

lib.o:     file format elf32-i386


Disassembly of section .text:

00000000 <leap>:
   0:	55                   	push   ebp
   1:	89 e5                	mov    ebp,esp
   3:	31 c0                	xor    eax,eax
   5:	40                   	inc    eax
   6:	8b 5d 08             	mov    ebx,DWORD PTR [ebp+0x8]
   9:	31 c3                	xor    ebx,eax
   b:	81 fb 06 08 00 00    	cmp    ebx,0x806
  11:	75 07                	jne    1a <leap+0x1a>
  13:	b8 01 00 00 00       	mov    eax,0x1
  18:	eb 05                	jmp    1f <leap+0x1f>
  1a:	b8 00 00 00 00       	mov    eax,0x0
  1f:	5d                   	pop    ebp
  20:	c3                   	ret    
