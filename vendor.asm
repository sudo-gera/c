
vendor:	file format elf32-i386

Disassembly of section .init:

080482b4 <_init>:
 80482b4: 53                           	push	ebx
 80482b5: 83 ec 08                     	sub	esp, 8
 80482b8: e8 97 00 00 00               	call	0x8048354 <__x86.get_pc_thunk.bx>
 80482bd: 81 c3 e3 13 00 00            	add	ebx, 5091
 80482c3: 8b 83 fc ff ff ff            	mov	eax, dword ptr [ebx - 4]
 80482c9: 85 c0                        	test	eax, eax
 80482cb: 74 05                        	je	0x80482d2 <_init+0x1e>
 80482cd: e8 3e 00 00 00               	call	0x8048310 <__gmon_start__@plt>
 80482d2: 83 c4 08                     	add	esp, 8
 80482d5: 5b                           	pop	ebx
 80482d6: c3                           	ret

Disassembly of section .plt:

080482e0 <.plt>:
 80482e0: ff 35 a4 96 04 08            	push	dword ptr [134518436]
 80482e6: ff 25 a8 96 04 08            	jmp	dword ptr [134518440]
 80482ec: 00 00                        	add	byte ptr [eax], al
 80482ee: 00 00                        	add	byte ptr [eax], al

080482f0 <printf@plt>:
 80482f0: ff 25 ac 96 04 08            	jmp	dword ptr [134518444]
 80482f6: 68 00 00 00 00               	push	0
 80482fb: e9 e0 ff ff ff               	jmp	0x80482e0 <.plt>

08048300 <scanf@plt>:
 8048300: ff 25 b0 96 04 08            	jmp	dword ptr [134518448]
 8048306: 68 08 00 00 00               	push	8
 804830b: e9 d0 ff ff ff               	jmp	0x80482e0 <.plt>

08048310 <__gmon_start__@plt>:
 8048310: ff 25 b4 96 04 08            	jmp	dword ptr [134518452]
 8048316: 68 10 00 00 00               	push	16
 804831b: e9 c0 ff ff ff               	jmp	0x80482e0 <.plt>

08048320 <__libc_start_main@plt>:
 8048320: ff 25 b8 96 04 08            	jmp	dword ptr [134518456]
 8048326: 68 18 00 00 00               	push	24
 804832b: e9 b0 ff ff ff               	jmp	0x80482e0 <.plt>

Disassembly of section .text:

08048330 <_start>:
 8048330: 31 ed                        	xor	ebp, ebp
 8048332: 5e                           	pop	esi
 8048333: 89 e1                        	mov	ecx, esp
 8048335: 83 e4 f0                     	and	esp, -16
 8048338: 50                           	push	eax
 8048339: 54                           	push	esp
 804833a: 52                           	push	edx
 804833b: 68 d0 84 04 08               	push	134513872
 8048340: 68 60 84 04 08               	push	134513760
 8048345: 51                           	push	ecx
 8048346: 56                           	push	esi
 8048347: 68 20 84 04 08               	push	134513696
 804834c: e8 cf ff ff ff               	call	0x8048320 <__libc_start_main@plt>
 8048351: f4                           	hlt
 8048352: 66 90                        	nop

08048354 <__x86.get_pc_thunk.bx>:
 8048354: 8b 1c 24                     	mov	ebx, dword ptr [esp]
 8048357: c3                           	ret
 8048358: 0f 1f 84 00 00 00 00 00      	nop	dword ptr [eax + eax]

08048360 <deregister_tm_clones>:
 8048360: b8 cf 96 04 08               	mov	eax, 134518479
 8048365: 2d cc 96 04 08               	sub	eax, 134518476
 804836a: 83 f8 06                     	cmp	eax, 6
 804836d: 77 02                        	ja	0x8048371 <deregister_tm_clones+0x11>
 804836f: f3 c3                        	rep		ret
 8048371: b8 00 00 00 00               	mov	eax, 0
 8048376: 85 c0                        	test	eax, eax
 8048378: 74 f5                        	je	0x804836f <deregister_tm_clones+0xf>
 804837a: 55                           	push	ebp
 804837b: 89 e5                        	mov	ebp, esp
 804837d: 83 ec 18                     	sub	esp, 24
 8048380: c7 04 24 cc 96 04 08         	mov	dword ptr [esp], 134518476
 8048387: ff d0                        	call	eax
 8048389: c9                           	leave
 804838a: c3                           	ret
 804838b: 90                           	nop
 804838c: 8d 74 26 00                  	lea	esi, [esi + eiz]

08048390 <register_tm_clones>:
 8048390: b8 cc 96 04 08               	mov	eax, 134518476
 8048395: 2d cc 96 04 08               	sub	eax, 134518476
 804839a: c1 f8 02                     	sar	eax, 2
 804839d: 89 c2                        	mov	edx, eax
 804839f: c1 ea 1f                     	shr	edx, 31
 80483a2: 01 d0                        	add	eax, edx
 80483a4: d1 f8                        	sar	eax
 80483a6: 75 02                        	jne	0x80483aa <register_tm_clones+0x1a>
 80483a8: f3 c3                        	rep		ret
 80483aa: ba 00 00 00 00               	mov	edx, 0
 80483af: 85 d2                        	test	edx, edx
 80483b1: 74 f5                        	je	0x80483a8 <register_tm_clones+0x18>
 80483b3: 55                           	push	ebp
 80483b4: 89 e5                        	mov	ebp, esp
 80483b6: 83 ec 18                     	sub	esp, 24
 80483b9: 89 44 24 04                  	mov	dword ptr [esp + 4], eax
 80483bd: c7 04 24 cc 96 04 08         	mov	dword ptr [esp], 134518476
 80483c4: ff d2                        	call	edx
 80483c6: c9                           	leave
 80483c7: c3                           	ret
 80483c8: 90                           	nop
 80483c9: 8d b4 26 00 00 00 00         	lea	esi, [esi + eiz]

080483d0 <__do_global_dtors_aux>:
 80483d0: 80 3d cc 96 04 08 00         	cmp	byte ptr [134518476], 0
 80483d7: 75 13                        	jne	0x80483ec <__do_global_dtors_aux+0x1c>
 80483d9: 55                           	push	ebp
 80483da: 89 e5                        	mov	ebp, esp
 80483dc: 83 ec 08                     	sub	esp, 8
 80483df: e8 7c ff ff ff               	call	0x8048360 <deregister_tm_clones>
 80483e4: c6 05 cc 96 04 08 01         	mov	byte ptr [134518476], 1
 80483eb: c9                           	leave
 80483ec: f3 c3                        	rep		ret
 80483ee: 66 90                        	nop

080483f0 <frame_dummy>:
 80483f0: a1 b0 95 04 08               	mov	eax, dword ptr [134518192]
 80483f5: 85 c0                        	test	eax, eax
 80483f7: 74 1e                        	je	0x8048417 <frame_dummy+0x27>
 80483f9: b8 00 00 00 00               	mov	eax, 0
 80483fe: 85 c0                        	test	eax, eax
 8048400: 74 15                        	je	0x8048417 <frame_dummy+0x27>
 8048402: 55                           	push	ebp
 8048403: 89 e5                        	mov	ebp, esp
 8048405: 83 ec 18                     	sub	esp, 24
 8048408: c7 04 24 b0 95 04 08         	mov	dword ptr [esp], 134518192
 804840f: ff d0                        	call	eax
 8048411: c9                           	leave
 8048412: e9 79 ff ff ff               	jmp	0x8048390 <register_tm_clones>
 8048417: e9 74 ff ff ff               	jmp	0x8048390 <register_tm_clones>
 804841c: 0f 1f 40 00                  	nop	dword ptr [eax]

08048420 <main>:
 8048420: 68 d0 96 04 08               	push	134518480
 8048425: 68 c0 96 04 08               	push	134518464
 804842a: e8 d1 fe ff ff               	call	0x8048300 <scanf@plt>
 804842f: 83 c4 08                     	add	esp, 8
 8048432: 31 c0                        	xor	eax, eax
 8048434: 0f a2                        	cpuid
 8048436: a1 d0 96 04 08               	mov	eax, dword ptr [134518480]
 804843b: 33 05 c7 96 04 08            	xor	eax, dword ptr [134518471]
 8048441: 31 d8                        	xor	eax, ebx
 8048443: 31 c8                        	xor	eax, ecx
 8048445: 31 d0                        	xor	eax, edx
 8048447: 50                           	push	eax
 8048448: 68 c3 96 04 08               	push	134518467
 804844d: e8 9e fe ff ff               	call	0x80482f0 <printf@plt>
 8048452: 83 c4 08                     	add	esp, 8
 8048455: 66 2e 0f 1f 84 00 00 00 00 00	nop	word ptr cs:[eax + eax]
 804845f: 90                           	nop

08048460 <__libc_csu_init>:
 8048460: 55                           	push	ebp
 8048461: 57                           	push	edi
 8048462: 31 ff                        	xor	edi, edi
 8048464: 56                           	push	esi
 8048465: 53                           	push	ebx
 8048466: e8 e9 fe ff ff               	call	0x8048354 <__x86.get_pc_thunk.bx>
 804846b: 81 c3 35 12 00 00            	add	ebx, 4661
 8048471: 83 ec 1c                     	sub	esp, 28
 8048474: 8b 6c 24 30                  	mov	ebp, dword ptr [esp + 48]
 8048478: 8d b3 0c ff ff ff            	lea	esi, [ebx - 244]
 804847e: e8 31 fe ff ff               	call	0x80482b4 <_init>
 8048483: 8d 83 08 ff ff ff            	lea	eax, [ebx - 248]
 8048489: 29 c6                        	sub	esi, eax
 804848b: c1 fe 02                     	sar	esi, 2
 804848e: 85 f6                        	test	esi, esi
 8048490: 74 27                        	je	0x80484b9 <__libc_csu_init+0x59>
 8048492: 8d b6 00 00 00 00            	lea	esi, [esi]
 8048498: 8b 44 24 38                  	mov	eax, dword ptr [esp + 56]
 804849c: 89 2c 24                     	mov	dword ptr [esp], ebp
 804849f: 89 44 24 08                  	mov	dword ptr [esp + 8], eax
 80484a3: 8b 44 24 34                  	mov	eax, dword ptr [esp + 52]
 80484a7: 89 44 24 04                  	mov	dword ptr [esp + 4], eax
 80484ab: ff 94 bb 08 ff ff ff         	call	dword ptr [ebx + 4*edi - 248]
 80484b2: 83 c7 01                     	add	edi, 1
 80484b5: 39 f7                        	cmp	edi, esi
 80484b7: 75 df                        	jne	0x8048498 <__libc_csu_init+0x38>
 80484b9: 83 c4 1c                     	add	esp, 28
 80484bc: 5b                           	pop	ebx
 80484bd: 5e                           	pop	esi
 80484be: 5f                           	pop	edi
 80484bf: 5d                           	pop	ebp
 80484c0: c3                           	ret
 80484c1: eb 0d                        	jmp	0x80484d0 <__libc_csu_fini>
 80484c3: 90                           	nop
 80484c4: 90                           	nop
 80484c5: 90                           	nop
 80484c6: 90                           	nop
 80484c7: 90                           	nop
 80484c8: 90                           	nop
 80484c9: 90                           	nop
 80484ca: 90                           	nop
 80484cb: 90                           	nop
 80484cc: 90                           	nop
 80484cd: 90                           	nop
 80484ce: 90                           	nop
 80484cf: 90                           	nop

080484d0 <__libc_csu_fini>:
 80484d0: f3 c3                        	rep		ret
 80484d2: 66 90                        	nop

Disassembly of section .fini:

080484d4 <_fini>:
 80484d4: 53                           	push	ebx
 80484d5: 83 ec 08                     	sub	esp, 8
 80484d8: e8 77 fe ff ff               	call	0x8048354 <__x86.get_pc_thunk.bx>
 80484dd: 81 c3 c3 11 00 00            	add	ebx, 4547
 80484e3: 83 c4 08                     	add	esp, 8
 80484e6: 5b                           	pop	ebx
 80484e7: c3                           	ret
