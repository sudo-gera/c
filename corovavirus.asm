
corovavirus:	file format elf64-x86-64

Disassembly of section .init:

00000000004003c0 <.init>:
  4003c0: 48 83 ec 08                  	sub	rsp, 8
  4003c4: 48 8b 05 2d 0c 20 00         	mov	rax, qword ptr [rip + 2100269] # 0x600ff8
  4003cb: 48 85 c0                     	test	rax, rax
  4003ce: 74 05                        	je	0x4003d5 <.init+0x15>
  4003d0: e8 2b 00 00 00               	call	0x400400 <__gmon_start__@plt>
  4003d5: 48 83 c4 08                  	add	rsp, 8
  4003d9: c3                           	ret

Disassembly of section .plt:

00000000004003e0 <.plt>:
  4003e0: ff 35 22 0c 20 00            	push	qword ptr [rip + 2100258] # 0x601008
  4003e6: ff 25 24 0c 20 00            	jmp	qword ptr [rip + 2100260] # 0x601010
  4003ec: 0f 1f 40 00                  	nop	dword ptr [rax]

00000000004003f0 <__libc_start_main@plt>:
  4003f0: ff 25 22 0c 20 00            	jmp	qword ptr [rip + 2100258] # 0x601018
  4003f6: 68 00 00 00 00               	push	0
  4003fb: e9 e0 ff ff ff               	jmp	0x4003e0 <.plt>

0000000000400400 <__gmon_start__@plt>:
  400400: ff 25 1a 0c 20 00            	jmp	qword ptr [rip + 2100250] # 0x601020
  400406: 68 01 00 00 00               	push	1
  40040b: e9 d0 ff ff ff               	jmp	0x4003e0 <.plt>

Disassembly of section .text:

0000000000400410 <.text>:
  400410: 48 8b 46 08                  	mov	rax, qword ptr [rsi + 8]
  400414: 8b 10                        	mov	edx, dword ptr [rax]
  400416: 81 fa 43 47 54 41            	cmp	edx, 1096042307
  40041c: 74 79                        	je	0x400497 <.text+0x87>
  40041e: 7e 23                        	jle	0x400443 <.text+0x33>
  400420: 81 fa 41 47 54 43            	cmp	edx, 1129596737
  400426: 74 63                        	je	0x40048b <.text+0x7b>
  400428: 7e 53                        	jle	0x40047d <.text+0x6d>
  40042a: 81 fa 43 54 41 47            	cmp	edx, 1195463747
  400430: b8 04 00 00 00               	mov	eax, 4
  400435: 74 0a                        	je	0x400441 <.text+0x31>
  400437: 81 fa 43 54 54 54            	cmp	edx, 1414812739
  40043d: b0 08                        	mov	al, 8
  40043f: 75 28                        	jne	0x400469 <.text+0x59>
  400441: f3 c3                        	rep		ret
  400443: 81 fa 47 47 41 41            	cmp	edx, 1094797127
  400449: 74 46                        	je	0x400491 <.text+0x81>
  40044b: 0f 1f 44 00 00               	nop	dword ptr [rax + rax]
  400450: 7e 1d                        	jle	0x40046f <.text+0x5f>
  400452: 81 fa 47 41 43 41            	cmp	edx, 1094926663
  400458: b8 07 00 00 00               	mov	eax, 7
  40045d: 74 e2                        	je	0x400441 <.text+0x31>
  40045f: 81 fa 43 54 47 41            	cmp	edx, 1095193667
  400465: b0 06                        	mov	al, 6
  400467: 74 d8                        	je	0x400441 <.text+0x31>
  400469: b8 0a 00 00 00               	mov	eax, 10
  40046e: c3                           	ret
  40046f: 81 fa 41 41 41 41            	cmp	edx, 1094795585
  400475: b8 01 00 00 00               	mov	eax, 1
  40047a: 75 ed                        	jne	0x400469 <.text+0x59>
  40047c: c3                           	ret
  40047d: 81 fa 41 54 43 43            	cmp	edx, 1128485953
  400483: b8 05 00 00 00               	mov	eax, 5
  400488: 75 df                        	jne	0x400469 <.text+0x59>
  40048a: c3                           	ret
  40048b: b8 03 00 00 00               	mov	eax, 3
  400490: c3                           	ret
  400491: b8 02 00 00 00               	mov	eax, 2
  400496: c3                           	ret
  400497: b8 09 00 00 00               	mov	eax, 9
  40049c: c3                           	ret
  40049d: 31 ed                        	xor	ebp, ebp
  40049f: 49 89 d1                     	mov	r9, rdx
  4004a2: 5e                           	pop	rsi
  4004a3: 48 89 e2                     	mov	rdx, rsp
  4004a6: 48 83 e4 f0                  	and	rsp, -16
  4004aa: 50                           	push	rax
  4004ab: 54                           	push	rsp
  4004ac: 49 c7 c0 00 06 40 00         	mov	r8, 4195840
  4004b3: 48 c7 c1 90 05 40 00         	mov	rcx, 4195728
  4004ba: 48 c7 c7 10 04 40 00         	mov	rdi, 4195344
  4004c1: e8 2a ff ff ff               	call	0x4003f0 <__libc_start_main@plt>
  4004c6: f4                           	hlt
  4004c7: 66 0f 1f 84 00 00 00 00 00   	nop	word ptr [rax + rax]
  4004d0: b8 3f 10 60 00               	mov	eax, 6295615
  4004d5: 55                           	push	rbp
  4004d6: 48 2d 38 10 60 00            	sub	rax, 6295608
  4004dc: 48 83 f8 0e                  	cmp	rax, 14
  4004e0: 48 89 e5                     	mov	rbp, rsp
  4004e3: 77 02                        	ja	0x4004e7 <.text+0xd7>
  4004e5: 5d                           	pop	rbp
  4004e6: c3                           	ret
  4004e7: b8 00 00 00 00               	mov	eax, 0
  4004ec: 48 85 c0                     	test	rax, rax
  4004ef: 74 f4                        	je	0x4004e5 <.text+0xd5>
  4004f1: 5d                           	pop	rbp
  4004f2: bf 38 10 60 00               	mov	edi, 6295608
  4004f7: ff e0                        	jmp	rax
  4004f9: 0f 1f 80 00 00 00 00         	nop	dword ptr [rax]
  400500: b8 38 10 60 00               	mov	eax, 6295608
  400505: 55                           	push	rbp
  400506: 48 2d 38 10 60 00            	sub	rax, 6295608
  40050c: 48 c1 f8 03                  	sar	rax, 3
  400510: 48 89 e5                     	mov	rbp, rsp
  400513: 48 89 c2                     	mov	rdx, rax
  400516: 48 c1 ea 3f                  	shr	rdx, 63
  40051a: 48 01 d0                     	add	rax, rdx
  40051d: 48 d1 f8                     	sar	rax
  400520: 75 02                        	jne	0x400524 <.text+0x114>
  400522: 5d                           	pop	rbp
  400523: c3                           	ret
  400524: ba 00 00 00 00               	mov	edx, 0
  400529: 48 85 d2                     	test	rdx, rdx
  40052c: 74 f4                        	je	0x400522 <.text+0x112>
  40052e: 5d                           	pop	rbp
  40052f: 48 89 c6                     	mov	rsi, rax
  400532: bf 38 10 60 00               	mov	edi, 6295608
  400537: ff e2                        	jmp	rdx
  400539: 0f 1f 80 00 00 00 00         	nop	dword ptr [rax]
  400540: 80 3d f1 0a 20 00 00         	cmp	byte ptr [rip + 2099953], 0 # 0x601038
  400547: 75 11                        	jne	0x40055a <.text+0x14a>
  400549: 55                           	push	rbp
  40054a: 48 89 e5                     	mov	rbp, rsp
  40054d: e8 7e ff ff ff               	call	0x4004d0 <.text+0xc0>
  400552: 5d                           	pop	rbp
  400553: c6 05 de 0a 20 00 01         	mov	byte ptr [rip + 2099934], 1 # 0x601038
  40055a: f3 c3                        	rep		ret
  40055c: 0f 1f 40 00                  	nop	dword ptr [rax]
  400560: 48 83 3d a8 08 20 00 00      	cmp	qword ptr [rip + 2099368], 0 # 0x600e10
  400568: 74 1e                        	je	0x400588 <.text+0x178>
  40056a: b8 00 00 00 00               	mov	eax, 0
  40056f: 48 85 c0                     	test	rax, rax
  400572: 74 14                        	je	0x400588 <.text+0x178>
  400574: 55                           	push	rbp
  400575: bf 10 0e 60 00               	mov	edi, 6295056
  40057a: 48 89 e5                     	mov	rbp, rsp
  40057d: ff d0                        	call	rax
  40057f: 5d                           	pop	rbp
  400580: e9 7b ff ff ff               	jmp	0x400500 <.text+0xf0>
  400585: 0f 1f 00                     	nop	dword ptr [rax]
  400588: e9 73 ff ff ff               	jmp	0x400500 <.text+0xf0>
  40058d: 0f 1f 00                     	nop	dword ptr [rax]
  400590: 41 57                        	push	r15
  400592: 41 89 ff                     	mov	r15d, edi
  400595: 41 56                        	push	r14
  400597: 49 89 f6                     	mov	r14, rsi
  40059a: 41 55                        	push	r13
  40059c: 49 89 d5                     	mov	r13, rdx
  40059f: 41 54                        	push	r12
  4005a1: 4c 8d 25 58 08 20 00         	lea	r12, [rip + 2099288]    # 0x600e00
  4005a8: 55                           	push	rbp
  4005a9: 48 8d 2d 58 08 20 00         	lea	rbp, [rip + 2099288]    # 0x600e08
  4005b0: 53                           	push	rbx
  4005b1: 4c 29 e5                     	sub	rbp, r12
  4005b4: 31 db                        	xor	ebx, ebx
  4005b6: 48 c1 fd 03                  	sar	rbp, 3
  4005ba: 48 83 ec 08                  	sub	rsp, 8
  4005be: e8 fd fd ff ff               	call	0x4003c0 <.init>
  4005c3: 48 85 ed                     	test	rbp, rbp
  4005c6: 74 1e                        	je	0x4005e6 <.text+0x1d6>
  4005c8: 0f 1f 84 00 00 00 00 00      	nop	dword ptr [rax + rax]
  4005d0: 4c 89 ea                     	mov	rdx, r13
  4005d3: 4c 89 f6                     	mov	rsi, r14
  4005d6: 44 89 ff                     	mov	edi, r15d
  4005d9: 41 ff 14 dc                  	call	qword ptr [r12 + 8*rbx]
  4005dd: 48 83 c3 01                  	add	rbx, 1
  4005e1: 48 39 eb                     	cmp	rbx, rbp
  4005e4: 75 ea                        	jne	0x4005d0 <.text+0x1c0>
  4005e6: 48 83 c4 08                  	add	rsp, 8
  4005ea: 5b                           	pop	rbx
  4005eb: 5d                           	pop	rbp
  4005ec: 41 5c                        	pop	r12
  4005ee: 41 5d                        	pop	r13
  4005f0: 41 5e                        	pop	r14
  4005f2: 41 5f                        	pop	r15
  4005f4: c3                           	ret
  4005f5: 66 66 2e 0f 1f 84 00 00 00 00 00     	nop	word ptr cs:[rax + rax]
  400600: f3 c3                        	rep		ret

Disassembly of section .fini:

0000000000400604 <.fini>:
  400604: 48 83 ec 08                  	sub	rsp, 8
  400608: 48 83 c4 08                  	add	rsp, 8
  40060c: c3                           	ret
