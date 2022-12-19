
./a.out:     file format elf64-x86-64


Disassembly of section .text:

00000000004000b0 <__best__putstr>:
  4000b0:	50                   	push   %rax
  4000b1:	51                   	push   %rcx
  4000b2:	52                   	push   %rdx
  4000b3:	53                   	push   %rbx
  4000b4:	54                   	push   %rsp
  4000b5:	55                   	push   %rbp
  4000b6:	56                   	push   %rsi
  4000b7:	57                   	push   %rdi
  4000b8:	48 8b 4c 24 50       	mov    0x50(%rsp),%rcx
  4000bd:	48 8b 54 24 48       	mov    0x48(%rsp),%rdx
  4000c2:	48 29 ca             	sub    %rcx,%rdx
  4000c5:	b8 01 00 00 00       	mov    $0x1,%eax
  4000ca:	bf 01 00 00 00       	mov    $0x1,%edi
  4000cf:	48 89 ce             	mov    %rcx,%rsi
  4000d2:	0f 05                	syscall 
  4000d4:	5f                   	pop    %rdi
  4000d5:	5e                   	pop    %rsi
  4000d6:	5d                   	pop    %rbp
  4000d7:	58                   	pop    %rax
  4000d8:	5b                   	pop    %rbx
  4000d9:	5a                   	pop    %rdx
  4000da:	59                   	pop    %rcx
  4000db:	58                   	pop    %rax
  4000dc:	8f 04 24             	popq   (%rsp)
  4000df:	8f 04 24             	popq   (%rsp)
  4000e2:	c3                   	retq   

00000000004000e3 <__best__getstr>:
  4000e3:	50                   	push   %rax
  4000e4:	51                   	push   %rcx
  4000e5:	52                   	push   %rdx
  4000e6:	53                   	push   %rbx
  4000e7:	54                   	push   %rsp
  4000e8:	55                   	push   %rbp
  4000e9:	56                   	push   %rsi
  4000ea:	57                   	push   %rdi
  4000eb:	48 8b 4c 24 50       	mov    0x50(%rsp),%rcx
  4000f0:	48 8b 54 24 48       	mov    0x48(%rsp),%rdx
  4000f5:	48 29 ca             	sub    %rcx,%rdx
  4000f8:	b8 00 00 00 00       	mov    $0x0,%eax
  4000fd:	bf 00 00 00 00       	mov    $0x0,%edi
  400102:	48 89 ce             	mov    %rcx,%rsi
  400105:	0f 05                	syscall 
  400107:	5f                   	pop    %rdi
  400108:	5e                   	pop    %rsi
  400109:	5d                   	pop    %rbp
  40010a:	58                   	pop    %rax
  40010b:	5b                   	pop    %rbx
  40010c:	5a                   	pop    %rdx
  40010d:	59                   	pop    %rcx
  40010e:	58                   	pop    %rax
  40010f:	8f 04 24             	popq   (%rsp)
  400112:	8f 04 24             	popq   (%rsp)
  400115:	c3                   	retq   

0000000000400116 <__best__putchar_s>:
  400116:	54                   	push   %rsp
  400117:	48 83 04 24 08       	addq   $0x8,(%rsp)
  40011c:	54                   	push   %rsp
  40011d:	48 83 04 24 11       	addq   $0x11,(%rsp)
  400122:	e8 89 ff ff ff       	callq  4000b0 <__best__putstr>
  400127:	c3                   	retq   

0000000000400128 <__best__getchar_s>:
  400128:	54                   	push   %rsp
  400129:	48 83 04 24 08       	addq   $0x8,(%rsp)
  40012e:	54                   	push   %rsp
  40012f:	48 83 04 24 11       	addq   $0x11,(%rsp)
  400134:	e8 aa ff ff ff       	callq  4000e3 <__best__getstr>
  400139:	c3                   	retq   

000000000040013a <__best__putchar>:
  40013a:	50                   	push   %rax
  40013b:	51                   	push   %rcx
  40013c:	52                   	push   %rdx
  40013d:	53                   	push   %rbx
  40013e:	54                   	push   %rsp
  40013f:	55                   	push   %rbp
  400140:	56                   	push   %rsi
  400141:	57                   	push   %rdi
  400142:	48 8b 44 24 48       	mov    0x48(%rsp),%rax
  400147:	50                   	push   %rax
  400148:	e8 c9 ff ff ff       	callq  400116 <__best__putchar_s>
  40014d:	48 83 c4 08          	add    $0x8,%rsp
  400151:	5f                   	pop    %rdi
  400152:	5e                   	pop    %rsi
  400153:	5d                   	pop    %rbp
  400154:	58                   	pop    %rax
  400155:	5b                   	pop    %rbx
  400156:	5a                   	pop    %rdx
  400157:	59                   	pop    %rcx
  400158:	58                   	pop    %rax
  400159:	8f 04 24             	popq   (%rsp)
  40015c:	c3                   	retq   

000000000040015d <__best__getchar>:
  40015d:	ff 34 24             	pushq  (%rsp)
  400160:	50                   	push   %rax
  400161:	51                   	push   %rcx
  400162:	52                   	push   %rdx
  400163:	53                   	push   %rbx
  400164:	54                   	push   %rsp
  400165:	55                   	push   %rbp
  400166:	56                   	push   %rsi
  400167:	57                   	push   %rdi
  400168:	6a 00                	pushq  $0x0
  40016a:	e8 b9 ff ff ff       	callq  400128 <__best__getchar_s>
  40016f:	58                   	pop    %rax
  400170:	48 89 44 24 48       	mov    %rax,0x48(%rsp)
  400175:	5f                   	pop    %rdi
  400176:	5e                   	pop    %rsi
  400177:	5d                   	pop    %rbp
  400178:	58                   	pop    %rax
  400179:	5b                   	pop    %rbx
  40017a:	5a                   	pop    %rdx
  40017b:	59                   	pop    %rcx
  40017c:	58                   	pop    %rax
  40017d:	c3                   	retq   

000000000040017e <__best__putuint>:
  40017e:	50                   	push   %rax
  40017f:	51                   	push   %rcx
  400180:	52                   	push   %rdx
  400181:	53                   	push   %rbx
  400182:	54                   	push   %rsp
  400183:	55                   	push   %rbp
  400184:	56                   	push   %rsi
  400185:	57                   	push   %rdi
  400186:	48 8b 44 24 48       	mov    0x48(%rsp),%rax
  40018b:	48 89 e3             	mov    %rsp,%rbx
  40018e:	48 89 e5             	mov    %rsp,%rbp
  400191:	48 83 ec 50          	sub    $0x50,%rsp
  400195:	ba 00 00 00 00       	mov    $0x0,%edx
  40019a:	bf 0a 00 00 00       	mov    $0xa,%edi
  40019f:	66 b9 14 00          	mov    $0x14,%cx

00000000004001a3 <__best__20>:
  4001a3:	48 f7 f7             	div    %rdi
  4001a6:	80 c2 30             	add    $0x30,%dl
  4001a9:	48 ff cb             	dec    %rbx
  4001ac:	88 13                	mov    %dl,(%rbx)
  4001ae:	66 ba 00 00          	mov    $0x0,%dx
  4001b2:	48 83 f8 00          	cmp    $0x0,%rax
  4001b6:	e0 eb                	loopne 4001a3 <__best__20>
  4001b8:	53                   	push   %rbx
  4001b9:	55                   	push   %rbp
  4001ba:	e8 f1 fe ff ff       	callq  4000b0 <__best__putstr>
  4001bf:	48 83 c4 50          	add    $0x50,%rsp
  4001c3:	5f                   	pop    %rdi
  4001c4:	5e                   	pop    %rsi
  4001c5:	5d                   	pop    %rbp
  4001c6:	58                   	pop    %rax
  4001c7:	5b                   	pop    %rbx
  4001c8:	5a                   	pop    %rdx
  4001c9:	59                   	pop    %rcx
  4001ca:	58                   	pop    %rax
  4001cb:	8f 04 24             	popq   (%rsp)
  4001ce:	c3                   	retq   

00000000004001cf <__best__putsint>:
  4001cf:	50                   	push   %rax
  4001d0:	51                   	push   %rcx
  4001d1:	52                   	push   %rdx
  4001d2:	53                   	push   %rbx
  4001d3:	54                   	push   %rsp
  4001d4:	55                   	push   %rbp
  4001d5:	56                   	push   %rsi
  4001d6:	57                   	push   %rdi
  4001d7:	48 8b 44 24 48       	mov    0x48(%rsp),%rax
  4001dc:	48 83 f8 00          	cmp    $0x0,%rax
  4001e0:	7d 0a                	jge    4001ec <__best__33>
  4001e2:	6a 2d                	pushq  $0x2d
  4001e4:	e8 51 ff ff ff       	callq  40013a <__best__putchar>
  4001e9:	48 f7 d8             	neg    %rax

00000000004001ec <__best__33>:
  4001ec:	50                   	push   %rax
  4001ed:	e8 8c ff ff ff       	callq  40017e <__best__putuint>
  4001f2:	5f                   	pop    %rdi
  4001f3:	5e                   	pop    %rsi
  4001f4:	5d                   	pop    %rbp
  4001f5:	58                   	pop    %rax
  4001f6:	5b                   	pop    %rbx
  4001f7:	5a                   	pop    %rdx
  4001f8:	59                   	pop    %rcx
  4001f9:	58                   	pop    %rax
  4001fa:	8f 04 24             	popq   (%rsp)
  4001fd:	c3                   	retq   

00000000004001fe <__best__getint>:
  4001fe:	ff 34 24             	pushq  (%rsp)
  400201:	50                   	push   %rax
  400202:	51                   	push   %rcx
  400203:	52                   	push   %rdx
  400204:	53                   	push   %rbx
  400205:	54                   	push   %rsp
  400206:	55                   	push   %rbp
  400207:	56                   	push   %rsi
  400208:	57                   	push   %rdi
  400209:	b8 00 00 00 00       	mov    $0x0,%eax
  40020e:	bb 00 00 00 00       	mov    $0x0,%ebx
  400213:	b9 00 00 00 00       	mov    $0x0,%ecx
  400218:	66 6a 00             	pushw  $0x0
  40021b:	b1 0a                	mov    $0xa,%cl

000000000040021d <__best__70>:
  40021d:	e8 06 ff ff ff       	callq  400128 <__best__getchar_s>
  400222:	8a 1c 24             	mov    (%rsp),%bl
  400225:	80 eb 30             	sub    $0x30,%bl
  400228:	80 fb fd             	cmp    $0xfd,%bl
  40022b:	75 05                	jne    400232 <__best__30>
  40022d:	c6 44 24 01 01       	movb   $0x1,0x1(%rsp)

0000000000400232 <__best__30>:
  400232:	80 fb 09             	cmp    $0x9,%bl
  400235:	77 e6                	ja     40021d <__best__70>
  400237:	eb 0b                	jmp    400244 <__best__71>

0000000000400239 <__best__32>:
  400239:	e8 ea fe ff ff       	callq  400128 <__best__getchar_s>
  40023e:	8a 1c 24             	mov    (%rsp),%bl
  400241:	80 eb 30             	sub    $0x30,%bl

0000000000400244 <__best__71>:
  400244:	80 fb 09             	cmp    $0x9,%bl
  400247:	77 08                	ja     400251 <__best__31>
  400249:	48 f7 e1             	mul    %rcx
  40024c:	48 01 d8             	add    %rbx,%rax
  40024f:	eb e8                	jmp    400239 <__best__32>

0000000000400251 <__best__31>:
  400251:	b3 00                	mov    $0x0,%bl
  400253:	38 5c 24 01          	cmp    %bl,0x1(%rsp)
  400257:	74 03                	je     40025c <__best__18>
  400259:	48 f7 d8             	neg    %rax

000000000040025c <__best__18>:
  40025c:	48 83 c4 02          	add    $0x2,%rsp
  400260:	48 89 44 24 48       	mov    %rax,0x48(%rsp)
  400265:	5f                   	pop    %rdi
  400266:	5e                   	pop    %rsi
  400267:	5d                   	pop    %rbp
  400268:	58                   	pop    %rax
  400269:	5b                   	pop    %rbx
  40026a:	5a                   	pop    %rdx
  40026b:	59                   	pop    %rcx
  40026c:	58                   	pop    %rax
  40026d:	c3                   	retq   

000000000040026e <__best__put_reg>:
  40026e:	50                   	push   %rax
  40026f:	51                   	push   %rcx
  400270:	52                   	push   %rdx
  400271:	53                   	push   %rbx
  400272:	54                   	push   %rsp
  400273:	55                   	push   %rbp
  400274:	56                   	push   %rsi
  400275:	57                   	push   %rdi
  400276:	b9 09 00 00 00       	mov    $0x9,%ecx
  40027b:	48 ba e0 03 61 00 00 	movabs $0x6103e0,%rdx
  400282:	00 00 00 
  400285:	48 29 e2             	sub    %rsp,%rdx
  400288:	48 81 fa 00 00 01 00 	cmp    $0x10000,%rdx
  40028f:	73 0f                	jae    4002a0 <__best__51>
  400291:	48 8b 04 25 e0 03 61 	mov    0x6103e0,%rax
  400298:	00 
  400299:	48 89 44 24 18       	mov    %rax,0x18(%rsp)
  40029e:	eb 06                	jmp    4002a6 <__best__50>

00000000004002a0 <__best__51>:
  4002a0:	48 83 44 24 18 78    	addq   $0x78,0x18(%rsp)

00000000004002a6 <__best__50>:
  4002a6:	ff 34 cd f0 03 61 00 	pushq  0x6103f0(,%rcx,8)
  4002ad:	48 81 04 24 40 04 61 	addq   $0x610440,(%rsp)
  4002b4:	00 
  4002b5:	ff 34 cd e8 03 61 00 	pushq  0x6103e8(,%rcx,8)
  4002bc:	48 81 04 24 40 04 61 	addq   $0x610440,(%rsp)
  4002c3:	00 
  4002c4:	e8 e7 fd ff ff       	callq  4000b0 <__best__putstr>
  4002c9:	48 8b 04 cd 81 04 61 	mov    0x610481(,%rcx,8),%rax
  4002d0:	00 
  4002d1:	48 8b 04 cd 81 04 61 	mov    0x610481(,%rcx,8),%rax
  4002d8:	00 
  4002d9:	48 01 e0             	add    %rsp,%rax
  4002dc:	ff 30                	pushq  (%rax)
  4002de:	e8 ec fe ff ff       	callq  4001cf <__best__putsint>
  4002e3:	6a 09                	pushq  $0x9
  4002e5:	e8 50 fe ff ff       	callq  40013a <__best__putchar>
  4002ea:	e2 ba                	loop   4002a6 <__best__50>
  4002ec:	5f                   	pop    %rdi
  4002ed:	5e                   	pop    %rsi
  4002ee:	5d                   	pop    %rbp
  4002ef:	58                   	pop    %rax
  4002f0:	5b                   	pop    %rbx
  4002f1:	5a                   	pop    %rdx
  4002f2:	59                   	pop    %rcx
  4002f3:	58                   	pop    %rax
  4002f4:	c3                   	retq   

00000000004002f5 <__best__printreg>:
  4002f5:	50                   	push   %rax
  4002f6:	51                   	push   %rcx
  4002f7:	52                   	push   %rdx
  4002f8:	53                   	push   %rbx
  4002f9:	54                   	push   %rsp
  4002fa:	55                   	push   %rbp
  4002fb:	56                   	push   %rsi
  4002fc:	57                   	push   %rdi
  4002fd:	e8 6c ff ff ff       	callq  40026e <__best__put_reg>
  400302:	6a 0a                	pushq  $0xa
  400304:	e8 31 fe ff ff       	callq  40013a <__best__putchar>
  400309:	5f                   	pop    %rdi
  40030a:	5e                   	pop    %rsi
  40030b:	5d                   	pop    %rbp
  40030c:	58                   	pop    %rax
  40030d:	5b                   	pop    %rbx
  40030e:	5a                   	pop    %rdx
  40030f:	59                   	pop    %rcx
  400310:	58                   	pop    %rax
  400311:	8f 04 24             	popq   (%rsp)
  400314:	c3                   	retq   

0000000000400315 <__best__writereg>:
  400315:	50                   	push   %rax
  400316:	51                   	push   %rcx
  400317:	52                   	push   %rdx
  400318:	53                   	push   %rbx
  400319:	54                   	push   %rsp
  40031a:	55                   	push   %rbp
  40031b:	56                   	push   %rsi
  40031c:	57                   	push   %rdi
  40031d:	e8 4c ff ff ff       	callq  40026e <__best__put_reg>
  400322:	6a 20                	pushq  $0x20
  400324:	e8 11 fe ff ff       	callq  40013a <__best__putchar>
  400329:	5f                   	pop    %rdi
  40032a:	5e                   	pop    %rsi
  40032b:	5d                   	pop    %rbp
  40032c:	58                   	pop    %rax
  40032d:	5b                   	pop    %rbx
  40032e:	5a                   	pop    %rdx
  40032f:	59                   	pop    %rcx
  400330:	58                   	pop    %rax
  400331:	8f 04 24             	popq   (%rsp)
  400334:	c3                   	retq   

0000000000400335 <__best__putreg>:
  400335:	50                   	push   %rax
  400336:	51                   	push   %rcx
  400337:	52                   	push   %rdx
  400338:	53                   	push   %rbx
  400339:	54                   	push   %rsp
  40033a:	55                   	push   %rbp
  40033b:	56                   	push   %rsi
  40033c:	57                   	push   %rdi
  40033d:	e8 2c ff ff ff       	callq  40026e <__best__put_reg>
  400342:	5f                   	pop    %rdi
  400343:	5e                   	pop    %rsi
  400344:	5d                   	pop    %rbp
  400345:	58                   	pop    %rax
  400346:	5b                   	pop    %rbx
  400347:	5a                   	pop    %rdx
  400348:	59                   	pop    %rcx
  400349:	58                   	pop    %rax
  40034a:	8f 04 24             	popq   (%rsp)
  40034d:	c3                   	retq   

000000000040034e <__best__movzx_dword_to_qword>:
  40034e:	48 c1 e0 20          	shl    $0x20,%rax
  400352:	48 c1 e8 20          	shr    $0x20,%rax
  400356:	c3                   	retq   

0000000000400357 <__best__call_putint_for_sbyte>:
  400357:	66 98                	cbtw   

0000000000400359 <__best__call_putint_for_sword>:
  400359:	98                   	cwtl   

000000000040035a <__best__call_putint_for_sdword>:
  40035a:	48 98                	cltq   

000000000040035c <__best__call_putint_for_sqword>:
  40035c:	50                   	push   %rax
  40035d:	e8 6d fe ff ff       	callq  4001cf <__best__putsint>
  400362:	c3                   	retq   

0000000000400363 <__best__call_putint_for_ubyte>:
  400363:	48 c1 e0 38          	shl    $0x38,%rax
  400367:	48 c1 e8 38          	shr    $0x38,%rax

000000000040036b <__best__call_putint_for_uword>:
  40036b:	48 c1 e0 30          	shl    $0x30,%rax
  40036f:	48 c1 e8 30          	shr    $0x30,%rax

0000000000400373 <__best__call_putint_for_udword>:
  400373:	48 c1 e0 20          	shl    $0x20,%rax
  400377:	48 c1 e8 20          	shr    $0x20,%rax

000000000040037b <__best__call_putint_for_uqword>:
  40037b:	50                   	push   %rax
  40037c:	e8 fd fd ff ff       	callq  40017e <__best__putuint>
  400381:	c3                   	retq   

0000000000400382 <__best__call_putchar>:
  400382:	50                   	push   %rax
  400383:	e8 47 fe ff ff       	callq  4001cf <__best__putsint>
  400388:	c3                   	retq   

0000000000400389 <_f_printreg>:
  400389:	48 87 24 25 e0 03 61 	xchg   %rsp,0x6103e0
  400390:	00 
  400391:	6a 04                	pushq  $0x4
  400393:	e8 5d ff ff ff       	callq  4002f5 <__best__printreg>
  400398:	48 87 24 25 e0 03 61 	xchg   %rsp,0x6103e0
  40039f:	00 

00000000004003a0 <..@41.end_putreg>:
  4003a0:	c3                   	retq   

00000000004003a1 <_start>:
  4003a1:	b8 00 00 00 00       	mov    $0x0,%eax
  4003a6:	bb 00 00 00 00       	mov    $0x0,%ebx
  4003ab:	b9 00 00 00 00       	mov    $0x0,%ecx
  4003b0:	ba 00 00 00 00       	mov    $0x0,%edx
  4003b5:	be 00 00 00 00       	mov    $0x0,%esi
  4003ba:	bf 00 00 00 00       	mov    $0x0,%edi
  4003bf:	bd 00 00 00 00       	mov    $0x0,%ebp

00000000004003c4 <..@42.end_start>:
  4003c4:	e8 c0 ff ff ff       	callq  400389 <_f_printreg>

00000000004003c9 <..@45.begin_stop>:
  4003c9:	b8 3c 00 00 00       	mov    $0x3c,%eax
  4003ce:	bf 00 00 00 00       	mov    $0x0,%edi
  4003d3:	0f 05                	syscall 

Disassembly of section .data:

00000000006003e0 <__best__fake_stack-0x10000>:
	...

00000000006103e0 <__best__fake_stack>:
  6103e0:	e0 03                	loopne 6103e5 <__best__fake_stack+0x5>
  6103e2:	61                   	(bad)  
	...

00000000006103f0 <__best__putreg_names_pos>:
  6103f0:	40 00 00             	add    %al,(%rax)
  6103f3:	00 00                	add    %al,(%rax)
  6103f5:	00 00                	add    %al,(%rax)
  6103f7:	00 38                	add    %bh,(%rax)
  6103f9:	00 00                	add    %al,(%rax)
  6103fb:	00 00                	add    %al,(%rax)
  6103fd:	00 00                	add    %al,(%rax)
  6103ff:	00 31                	add    %dh,(%rcx)
  610401:	00 00                	add    %al,(%rax)
  610403:	00 00                	add    %al,(%rax)
  610405:	00 00                	add    %al,(%rax)
  610407:	00 2a                	add    %ch,(%rdx)
  610409:	00 00                	add    %al,(%rax)
  61040b:	00 00                	add    %al,(%rax)
  61040d:	00 00                	add    %al,(%rax)
  61040f:	00 23                	add    %ah,(%rbx)
  610411:	00 00                	add    %al,(%rax)
  610413:	00 00                	add    %al,(%rax)
  610415:	00 00                	add    %al,(%rax)
  610417:	00 1c 00             	add    %bl,(%rax,%rax,1)
  61041a:	00 00                	add    %al,(%rax)
  61041c:	00 00                	add    %al,(%rax)
  61041e:	00 00                	add    %al,(%rax)
  610420:	15 00 00 00 00       	adc    $0x0,%eax
  610425:	00 00                	add    %al,(%rax)
  610427:	00 0e                	add    %cl,(%rsi)
  610429:	00 00                	add    %al,(%rax)
  61042b:	00 00                	add    %al,(%rax)
  61042d:	00 00                	add    %al,(%rax)
  61042f:	00 07                	add    %al,(%rdi)
	...

0000000000610440 <__best__putreg_names>:
  610440:	72 61                	jb     6104a3 <__best__putreg_stack_pos+0x22>
  610442:	78 20                	js     610464 <__best__putreg_names+0x24>
  610444:	3d 3d 20 72 62       	cmp    $0x6272203d,%eax
  610449:	78 20                	js     61046b <__best__putreg_names+0x2b>
  61044b:	3d 3d 20 72 63       	cmp    $0x6372203d,%eax
  610450:	78 20                	js     610472 <__best__putreg_names+0x32>
  610452:	3d 3d 20 72 64       	cmp    $0x6472203d,%eax
  610457:	78 20                	js     610479 <__best__putreg_names+0x39>
  610459:	3d 3d 20 72 73       	cmp    $0x7372203d,%eax
  61045e:	69 20 3d 3d 20 72    	imul   $0x72203d3d,(%rax),%esp
  610464:	64 69 20 3d 3d 20 72 	imul   $0x72203d3d,%fs:(%rax),%esp
  61046b:	62                   	(bad)  
  61046c:	70 20                	jo     61048e <__best__putreg_stack_pos+0xd>
  61046e:	3d 3d 20 72 73       	cmp    $0x7372203d,%eax
  610473:	70 20                	jo     610495 <__best__putreg_stack_pos+0x14>
  610475:	3d 3d 20 6c 69       	cmp    $0x696c203d,%eax
  61047a:	6e                   	outsb  %ds:(%rsi),(%dx)
  61047b:	65 20 3d 3d 20 30  	and    %bh,%gs:0x30203d(%rip)        # 9124bf <_end+0x301fe7>

0000000000610481 <__best__putreg_stack_pos>:
	...
  610489:	90                   	nop
  61048a:	00 00                	add    %al,(%rax)
  61048c:	00 00                	add    %al,(%rax)
  61048e:	00 00                	add    %al,(%rax)
  610490:	00 18                	add    %bl,(%rax)
  610492:	00 00                	add    %al,(%rax)
  610494:	00 00                	add    %al,(%rax)
  610496:	00 00                	add    %al,(%rax)
  610498:	00 10                	add    %dl,(%rax)
	...
  6104a6:	00 00                	add    %al,(%rax)
  6104a8:	00 08                	add    %cl,(%rax)
  6104aa:	00 00                	add    %al,(%rax)
  6104ac:	00 00                	add    %al,(%rax)
  6104ae:	00 00                	add    %al,(%rax)
  6104b0:	00 28                	add    %ch,(%rax)
  6104b2:	00 00                	add    %al,(%rax)
  6104b4:	00 00                	add    %al,(%rax)
  6104b6:	00 00                	add    %al,(%rax)
  6104b8:	00 30                	add    %dh,(%rax)
  6104ba:	00 00                	add    %al,(%rax)
  6104bc:	00 00                	add    %al,(%rax)
  6104be:	00 00                	add    %al,(%rax)
  6104c0:	00 20                	add    %ah,(%rax)
  6104c2:	00 00                	add    %al,(%rax)
  6104c4:	00 00                	add    %al,(%rax)
  6104c6:	00 00                	add    %al,(%rax)
  6104c8:	00 38                	add    %bh,(%rax)
  6104ca:	00 00                	add    %al,(%rax)
  6104cc:	00 00                	add    %al,(%rax)
  6104ce:	00 00                	add    %al,(%rax)
	...
