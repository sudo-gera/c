
antideb:	file format elf64-x86-64

Disassembly of section .init:

0000000000400480 <_init>:
  400480: 48 83 ec 08                  	sub	rsp, 8
  400484: e8 93 00 00 00               	call	0x40051c <call_gmon_start>
  400489: e8 22 01 00 00               	call	0x4005b0 <frame_dummy>
  40048e: e8 3d 02 00 00               	call	0x4006d0 <__do_global_ctors_aux>
  400493: 48 83 c4 08                  	add	rsp, 8
  400497: c3                           	ret

Disassembly of section .plt:

0000000000400498 <.plt>:
  400498: ff 35 52 0b 20 00            	push	qword ptr [rip + 2100050] # 0x600ff0 <_GLOBAL_OFFSET_TABLE_+0x8>
  40049e: ff 25 54 0b 20 00            	jmp	qword ptr [rip + 2100052] # 0x600ff8 <_GLOBAL_OFFSET_TABLE_+0x10>
  4004a4: 0f 1f 40 00                  	nop	dword ptr [rax]

00000000004004a8 <puts@plt>:
  4004a8: ff 25 52 0b 20 00            	jmp	qword ptr [rip + 2100050] # 0x601000 <_GLOBAL_OFFSET_TABLE_+0x18>
  4004ae: 68 00 00 00 00               	push	0
  4004b3: e9 e0 ff ff ff               	jmp	0x400498 <.plt>

00000000004004b8 <__libc_start_main@plt>:
  4004b8: ff 25 4a 0b 20 00            	jmp	qword ptr [rip + 2100042] # 0x601008 <_GLOBAL_OFFSET_TABLE_+0x20>
  4004be: 68 01 00 00 00               	push	1
  4004c3: e9 d0 ff ff ff               	jmp	0x400498 <.plt>

00000000004004c8 <_exit@plt>:
  4004c8: ff 25 42 0b 20 00            	jmp	qword ptr [rip + 2100034] # 0x601010 <_GLOBAL_OFFSET_TABLE_+0x28>
  4004ce: 68 02 00 00 00               	push	2
  4004d3: e9 c0 ff ff ff               	jmp	0x400498 <.plt>

00000000004004d8 <ptrace@plt>:
  4004d8: ff 25 3a 0b 20 00            	jmp	qword ptr [rip + 2100026] # 0x601018 <_GLOBAL_OFFSET_TABLE_+0x30>
  4004de: 68 03 00 00 00               	push	3
  4004e3: e9 b0 ff ff ff               	jmp	0x400498 <.plt>

Disassembly of section .text:

00000000004004f0 <_start>:
  4004f0: 31 ed                        	xor	ebp, ebp
  4004f2: 49 89 d1                     	mov	r9, rdx
  4004f5: 5e                           	pop	rsi
  4004f6: 48 89 e2                     	mov	rdx, rsp
  4004f9: 48 83 e4 f0                  	and	rsp, -16
  4004fd: 50                           	push	rax
  4004fe: 54                           	push	rsp
  4004ff: 49 c7 c0 c0 06 40 00         	mov	r8, 4196032
  400506: 48 c7 c1 30 06 40 00         	mov	rcx, 4195888
  40050d: 48 c7 c7 12 06 40 00         	mov	rdi, 4195858
  400514: e8 9f ff ff ff               	call	0x4004b8 <__libc_start_main@plt>
  400519: f4                           	hlt
  40051a: 90                           	nop
  40051b: 90                           	nop

000000000040051c <call_gmon_start>:
  40051c: 48 83 ec 08                  	sub	rsp, 8
  400520: 48 8b 05 b9 0a 20 00         	mov	rax, qword ptr [rip + 2099897] # 0x600fe0 <puts@@GLIBC_2.2.5+0x600fe0>
  400527: 48 85 c0                     	test	rax, rax
  40052a: 74 02                        	je	0x40052e <call_gmon_start+0x12>
  40052c: ff d0                        	call	rax
  40052e: 48 83 c4 08                  	add	rsp, 8
  400532: c3                           	ret
  400533: 90                           	nop
  400534: 90                           	nop
  400535: 90                           	nop
  400536: 90                           	nop
  400537: 90                           	nop
  400538: 90                           	nop
  400539: 90                           	nop
  40053a: 90                           	nop
  40053b: 90                           	nop
  40053c: 90                           	nop
  40053d: 90                           	nop
  40053e: 90                           	nop
  40053f: 90                           	nop

0000000000400540 <__do_global_dtors_aux>:
  400540: 55                           	push	rbp
  400541: 48 89 e5                     	mov	rbp, rsp
  400544: 53                           	push	rbx
  400545: 48 83 ec 08                  	sub	rsp, 8
  400549: 80 3d e0 0a 20 00 00         	cmp	byte ptr [rip + 2099936], 0 # 0x601030 <completed.5939>
  400550: 75 4b                        	jne	0x40059d <__do_global_dtors_aux+0x5d>
  400552: bb 30 0e 60 00               	mov	ebx, 6295088
  400557: 48 8b 05 da 0a 20 00         	mov	rax, qword ptr [rip + 2099930] # 0x601038 <dtor_idx.5941>
  40055e: 48 81 eb 28 0e 60 00         	sub	rbx, 6295080
  400565: 48 c1 fb 03                  	sar	rbx, 3
  400569: 48 83 eb 01                  	sub	rbx, 1
  40056d: 48 39 d8                     	cmp	rax, rbx
  400570: 73 24                        	jae	0x400596 <__do_global_dtors_aux+0x56>
  400572: 66 0f 1f 44 00 00            	nop	word ptr [rax + rax]
  400578: 48 83 c0 01                  	add	rax, 1
  40057c: 48 89 05 b5 0a 20 00         	mov	qword ptr [rip + 2099893], rax # 0x601038 <dtor_idx.5941>
  400583: ff 14 c5 28 0e 60 00         	call	qword ptr [8*rax + 6295080]
  40058a: 48 8b 05 a7 0a 20 00         	mov	rax, qword ptr [rip + 2099879] # 0x601038 <dtor_idx.5941>
  400591: 48 39 d8                     	cmp	rax, rbx
  400594: 72 e2                        	jb	0x400578 <__do_global_dtors_aux+0x38>
  400596: c6 05 93 0a 20 00 01         	mov	byte ptr [rip + 2099859], 1 # 0x601030 <completed.5939>
  40059d: 48 83 c4 08                  	add	rsp, 8
  4005a1: 5b                           	pop	rbx
  4005a2: c9                           	leave
  4005a3: c3                           	ret
  4005a4: 66 66 66 2e 0f 1f 84 00 00 00 00 00  	nop	word ptr cs:[rax + rax]

00000000004005b0 <frame_dummy>:
  4005b0: 48 83 3d 80 08 20 00 00      	cmp	qword ptr [rip + 2099328], 0 # 0x600e38 <__JCR_LIST__>
  4005b8: 55                           	push	rbp
  4005b9: 48 89 e5                     	mov	rbp, rsp
  4005bc: 74 12                        	je	0x4005d0 <frame_dummy+0x20>
  4005be: b8 00 00 00 00               	mov	eax, 0
  4005c3: 48 85 c0                     	test	rax, rax
  4005c6: 74 08                        	je	0x4005d0 <frame_dummy+0x20>
  4005c8: bf 38 0e 60 00               	mov	edi, 6295096
  4005cd: c9                           	leave
  4005ce: ff e0                        	jmp	rax
  4005d0: c9                           	leave
  4005d1: c3                           	ret
  4005d2: 90                           	nop
  4005d3: 90                           	nop

00000000004005d4 <check>:
  4005d4: 55                           	push	rbp
  4005d5: 48 89 e5                     	mov	rbp, rsp
  4005d8: b9 00 00 00 00               	mov	ecx, 0
  4005dd: ba 00 00 00 00               	mov	edx, 0
  4005e2: be 00 00 00 00               	mov	esi, 0
  4005e7: bf 00 00 00 00               	mov	edi, 0
  4005ec: b8 00 00 00 00               	mov	eax, 0
  4005f1: e8 e2 fe ff ff               	call	0x4004d8 <ptrace@plt>
  4005f6: 48 83 f8 ff                  	cmp	rax, -1
  4005fa: 75 14                        	jne	0x400610 <check+0x3c>
  4005fc: bf 20 07 40 00               	mov	edi, 4196128
  400601: e8 a2 fe ff ff               	call	0x4004a8 <puts@plt>
  400606: bf ff ff ff ff               	mov	edi, 4294967295
  40060b: e8 b8 fe ff ff               	call	0x4004c8 <_exit@plt>
  400610: c9                           	leave
  400611: c3                           	ret

0000000000400612 <main>:
  400612: 55                           	push	rbp
  400613: 48 89 e5                     	mov	rbp, rsp
  400616: bf 38 07 40 00               	mov	edi, 4196152
  40061b: e8 88 fe ff ff               	call	0x4004a8 <puts@plt>
  400620: b8 00 00 00 00               	mov	eax, 0
  400625: c9                           	leave
  400626: c3                           	ret
  400627: 90                           	nop
  400628: 90                           	nop
  400629: 90                           	nop
  40062a: 90                           	nop
  40062b: 90                           	nop
  40062c: 90                           	nop
  40062d: 90                           	nop
  40062e: 90                           	nop
  40062f: 90                           	nop

0000000000400630 <__libc_csu_init>:
  400630: 48 89 6c 24 d8               	mov	qword ptr [rsp - 40], rbp
  400635: 4c 89 64 24 e0               	mov	qword ptr [rsp - 32], r12
  40063a: 48 8d 2d cb 07 20 00         	lea	rbp, [rip + 2099147]    # 0x600e0c <__FRAME_END__+0x2005ec>
  400641: 4c 8d 25 c4 07 20 00         	lea	r12, [rip + 2099140]    # 0x600e0c <__FRAME_END__+0x2005ec>
  400648: 4c 89 6c 24 e8               	mov	qword ptr [rsp - 24], r13
  40064d: 4c 89 74 24 f0               	mov	qword ptr [rsp - 16], r14
  400652: 4c 89 7c 24 f8               	mov	qword ptr [rsp - 8], r15
  400657: 48 89 5c 24 d0               	mov	qword ptr [rsp - 48], rbx
  40065c: 48 83 ec 38                  	sub	rsp, 56
  400660: 4c 29 e5                     	sub	rbp, r12
  400663: 41 89 fd                     	mov	r13d, edi
  400666: 49 89 f6                     	mov	r14, rsi
  400669: 48 c1 fd 03                  	sar	rbp, 3
  40066d: 49 89 d7                     	mov	r15, rdx
  400670: e8 0b fe ff ff               	call	0x400480 <_init>
  400675: 48 85 ed                     	test	rbp, rbp
  400678: 74 1c                        	je	0x400696 <__libc_csu_init+0x66>
  40067a: 31 db                        	xor	ebx, ebx
  40067c: 0f 1f 40 00                  	nop	dword ptr [rax]
  400680: 4c 89 fa                     	mov	rdx, r15
  400683: 4c 89 f6                     	mov	rsi, r14
  400686: 44 89 ef                     	mov	edi, r13d
  400689: 41 ff 14 dc                  	call	qword ptr [r12 + 8*rbx]
  40068d: 48 83 c3 01                  	add	rbx, 1
  400691: 48 39 eb                     	cmp	rbx, rbp
  400694: 72 ea                        	jb	0x400680 <__libc_csu_init+0x50>
  400696: 48 8b 5c 24 08               	mov	rbx, qword ptr [rsp + 8]
  40069b: 48 8b 6c 24 10               	mov	rbp, qword ptr [rsp + 16]
  4006a0: 4c 8b 64 24 18               	mov	r12, qword ptr [rsp + 24]
  4006a5: 4c 8b 6c 24 20               	mov	r13, qword ptr [rsp + 32]
  4006aa: 4c 8b 74 24 28               	mov	r14, qword ptr [rsp + 40]
  4006af: 4c 8b 7c 24 30               	mov	r15, qword ptr [rsp + 48]
  4006b4: 48 83 c4 38                  	add	rsp, 56
  4006b8: c3                           	ret
  4006b9: 0f 1f 80 00 00 00 00         	nop	dword ptr [rax]

00000000004006c0 <__libc_csu_fini>:
  4006c0: f3 c3                        	rep		ret
  4006c2: 90                           	nop
  4006c3: 90                           	nop
  4006c4: 90                           	nop
  4006c5: 90                           	nop
  4006c6: 90                           	nop
  4006c7: 90                           	nop
  4006c8: 90                           	nop
  4006c9: 90                           	nop
  4006ca: 90                           	nop
  4006cb: 90                           	nop
  4006cc: 90                           	nop
  4006cd: 90                           	nop
  4006ce: 90                           	nop
  4006cf: 90                           	nop

00000000004006d0 <__do_global_ctors_aux>:
  4006d0: 55                           	push	rbp
  4006d1: 48 89 e5                     	mov	rbp, rsp
  4006d4: 53                           	push	rbx
  4006d5: 48 83 ec 08                  	sub	rsp, 8
  4006d9: 48 8b 05 38 07 20 00         	mov	rax, qword ptr [rip + 2099000] # 0x600e18 <__CTOR_LIST__+0x8>
  4006e0: 48 83 f8 ff                  	cmp	rax, -1
  4006e4: 74 19                        	je	0x4006ff <__do_global_ctors_aux+0x2f>
  4006e6: bb 18 0e 60 00               	mov	ebx, 6295064
  4006eb: 0f 1f 44 00 00               	nop	dword ptr [rax + rax]
  4006f0: 48 83 eb 08                  	sub	rbx, 8
  4006f4: ff d0                        	call	rax
  4006f6: 48 8b 03                     	mov	rax, qword ptr [rbx]
  4006f9: 48 83 f8 ff                  	cmp	rax, -1
  4006fd: 75 f1                        	jne	0x4006f0 <__do_global_ctors_aux+0x20>
  4006ff: 48 83 c4 08                  	add	rsp, 8
  400703: 5b                           	pop	rbx
  400704: c9                           	leave
  400705: c3                           	ret
  400706: 90                           	nop
  400707: 90                           	nop

Disassembly of section .fini:

0000000000400708 <_fini>:
  400708: 48 83 ec 08                  	sub	rsp, 8
  40070c: e8 2f fe ff ff               	call	0x400540 <__do_global_dtors_aux>
  400711: 48 83 c4 08                  	add	rsp, 8
  400715: c3                           	ret
