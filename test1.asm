
a.out:     file format elf32-i386


Disassembly of section .text:

08048080 <macro_regout>:
 8048080:	e8 1f 0e 00 00       	call   8048ea4 <__best_sput+0x6>

08048085 <..@171._1>:
 8048085:	65 61                	gs popa 
 8048087:	78                   	.byte 0x78

08048088 <..@171._2>:
 8048088:	e8 19 0e 00 00       	call   8048ea6 <__best_sput+0x8>

0804808d <..@172._1>:
 804808d:	20                   	.byte 0x20
 804808e:	3d                   	.byte 0x3d
 804808f:	3d                   	.byte 0x3d
 8048090:	20                   	.byte 0x20

08048091 <..@172._2>:
 8048091:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8048096:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 804809b:	b0 1b                	mov    al,0x1b
 804809d:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80480a1:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 80480a6:	83 ec 02             	sub    esp,0x2
 80480a9:	e8 20 0d 00 00       	call   8048dce <__best_cput+0x2>
 80480ae:	e8 f3 0d 00 00       	call   8048ea6 <__best_sput+0x8>

080480b3 <..@177._1>:
 80480b3:	5b                   	pop    ebx
 80480b4:	33 32                	xor    esi,DWORD PTR [edx]
 80480b6:	6d                   	ins    DWORD PTR es:[edi],dx

080480b7 <..@177._2>:
 80480b7:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 80480bc:	89 c0                	mov    eax,eax
 80480be:	89 44 24 fc          	mov    DWORD PTR [esp-0x4],eax
 80480c2:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 80480c7:	83 ec 04             	sub    esp,0x4
 80480ca:	e8 f1 08 00 00       	call   80489c0 <__best_dsput+0x2>
 80480cf:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80480d4:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 80480d9:	b0 1b                	mov    al,0x1b
 80480db:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80480df:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 80480e4:	83 ec 02             	sub    esp,0x2
 80480e7:	e8 e2 0c 00 00       	call   8048dce <__best_cput+0x2>
 80480ec:	e8 b3 0d 00 00       	call   8048ea4 <__best_sput+0x6>

080480f1 <..@186._1>:
 80480f1:	5b                   	pop    ebx
 80480f2:	30                   	.byte 0x30
 80480f3:	6d                   	ins    DWORD PTR es:[edi],dx

080480f4 <..@186._2>:
 80480f4:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80480f9:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 80480fe:	b0 09                	mov    al,0x9
 8048100:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8048104:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8048109:	83 ec 02             	sub    esp,0x2
 804810c:	e8 bd 0c 00 00       	call   8048dce <__best_cput+0x2>
 8048111:	e8 8a 0d 00 00       	call   8048ea0 <__best_sput+0x2>

08048116 <..@191._1>:
 8048116:	20                   	.byte 0x20

08048117 <..@191._2>:
 8048117:	e8 88 0d 00 00       	call   8048ea4 <__best_sput+0x6>

0804811c <..@193._1>:
 804811c:	65                   	gs
 804811d:	62                   	.byte 0x62
 804811e:	78                   	.byte 0x78

0804811f <..@193._2>:
 804811f:	e8 82 0d 00 00       	call   8048ea6 <__best_sput+0x8>

08048124 <..@194._1>:
 8048124:	20                   	.byte 0x20
 8048125:	3d                   	.byte 0x3d
 8048126:	3d                   	.byte 0x3d
 8048127:	20                   	.byte 0x20

08048128 <..@194._2>:
 8048128:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804812d:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048132:	b0 1b                	mov    al,0x1b
 8048134:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8048138:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 804813d:	83 ec 02             	sub    esp,0x2
 8048140:	e8 89 0c 00 00       	call   8048dce <__best_cput+0x2>
 8048145:	e8 5c 0d 00 00       	call   8048ea6 <__best_sput+0x8>

0804814a <..@199._1>:
 804814a:	5b                   	pop    ebx
 804814b:	33 32                	xor    esi,DWORD PTR [edx]
 804814d:	6d                   	ins    DWORD PTR es:[edi],dx

0804814e <..@199._2>:
 804814e:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048153:	89 d8                	mov    eax,ebx
 8048155:	89 44 24 fc          	mov    DWORD PTR [esp-0x4],eax
 8048159:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 804815e:	83 ec 04             	sub    esp,0x4
 8048161:	e8 5a 08 00 00       	call   80489c0 <__best_dsput+0x2>
 8048166:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804816b:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048170:	b0 1b                	mov    al,0x1b
 8048172:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8048176:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 804817b:	83 ec 02             	sub    esp,0x2
 804817e:	e8 4b 0c 00 00       	call   8048dce <__best_cput+0x2>
 8048183:	e8 1c 0d 00 00       	call   8048ea4 <__best_sput+0x6>

08048188 <..@208._1>:
 8048188:	5b                   	pop    ebx
 8048189:	30                   	.byte 0x30
 804818a:	6d                   	ins    DWORD PTR es:[edi],dx

0804818b <..@208._2>:
 804818b:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8048190:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048195:	b0 09                	mov    al,0x9
 8048197:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804819b:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 80481a0:	83 ec 02             	sub    esp,0x2
 80481a3:	e8 26 0c 00 00       	call   8048dce <__best_cput+0x2>
 80481a8:	e8 f3 0c 00 00       	call   8048ea0 <__best_sput+0x2>

080481ad <..@213._1>:
 80481ad:	20                   	.byte 0x20

080481ae <..@213._2>:
 80481ae:	e8 f1 0c 00 00       	call   8048ea4 <__best_sput+0x6>

080481b3 <..@215._1>:
 80481b3:	65                   	gs
 80481b4:	63                   	.byte 0x63
 80481b5:	78                   	.byte 0x78

080481b6 <..@215._2>:
 80481b6:	e8 eb 0c 00 00       	call   8048ea6 <__best_sput+0x8>

080481bb <..@216._1>:
 80481bb:	20                   	.byte 0x20
 80481bc:	3d                   	.byte 0x3d
 80481bd:	3d                   	.byte 0x3d
 80481be:	20                   	.byte 0x20

080481bf <..@216._2>:
 80481bf:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80481c4:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 80481c9:	b0 1b                	mov    al,0x1b
 80481cb:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80481cf:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 80481d4:	83 ec 02             	sub    esp,0x2
 80481d7:	e8 f2 0b 00 00       	call   8048dce <__best_cput+0x2>
 80481dc:	e8 c5 0c 00 00       	call   8048ea6 <__best_sput+0x8>

080481e1 <..@221._1>:
 80481e1:	5b                   	pop    ebx
 80481e2:	33 32                	xor    esi,DWORD PTR [edx]
 80481e4:	6d                   	ins    DWORD PTR es:[edi],dx

080481e5 <..@221._2>:
 80481e5:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 80481ea:	89 c8                	mov    eax,ecx
 80481ec:	89 44 24 fc          	mov    DWORD PTR [esp-0x4],eax
 80481f0:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 80481f5:	83 ec 04             	sub    esp,0x4
 80481f8:	e8 c3 07 00 00       	call   80489c0 <__best_dsput+0x2>
 80481fd:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8048202:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048207:	b0 1b                	mov    al,0x1b
 8048209:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804820d:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8048212:	83 ec 02             	sub    esp,0x2
 8048215:	e8 b4 0b 00 00       	call   8048dce <__best_cput+0x2>
 804821a:	e8 85 0c 00 00       	call   8048ea4 <__best_sput+0x6>

0804821f <..@230._1>:
 804821f:	5b                   	pop    ebx
 8048220:	30                   	.byte 0x30
 8048221:	6d                   	ins    DWORD PTR es:[edi],dx

08048222 <..@230._2>:
 8048222:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8048227:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 804822c:	b0 09                	mov    al,0x9
 804822e:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8048232:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8048237:	83 ec 02             	sub    esp,0x2
 804823a:	e8 8f 0b 00 00       	call   8048dce <__best_cput+0x2>
 804823f:	e8 5c 0c 00 00       	call   8048ea0 <__best_sput+0x2>

08048244 <..@235._1>:
 8048244:	20                   	.byte 0x20

08048245 <..@235._2>:
 8048245:	e8 5a 0c 00 00       	call   8048ea4 <__best_sput+0x6>

0804824a <..@237._1>:
 804824a:	65                   	gs
 804824b:	64                   	fs
 804824c:	78                   	.byte 0x78

0804824d <..@237._2>:
 804824d:	e8 54 0c 00 00       	call   8048ea6 <__best_sput+0x8>

08048252 <..@238._1>:
 8048252:	20                   	.byte 0x20
 8048253:	3d                   	.byte 0x3d
 8048254:	3d                   	.byte 0x3d
 8048255:	20                   	.byte 0x20

08048256 <..@238._2>:
 8048256:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804825b:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048260:	b0 1b                	mov    al,0x1b
 8048262:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8048266:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 804826b:	83 ec 02             	sub    esp,0x2
 804826e:	e8 5b 0b 00 00       	call   8048dce <__best_cput+0x2>
 8048273:	e8 2e 0c 00 00       	call   8048ea6 <__best_sput+0x8>

08048278 <..@243._1>:
 8048278:	5b                   	pop    ebx
 8048279:	33 32                	xor    esi,DWORD PTR [edx]
 804827b:	6d                   	ins    DWORD PTR es:[edi],dx

0804827c <..@243._2>:
 804827c:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048281:	89 d0                	mov    eax,edx
 8048283:	89 44 24 fc          	mov    DWORD PTR [esp-0x4],eax
 8048287:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 804828c:	83 ec 04             	sub    esp,0x4
 804828f:	e8 2c 07 00 00       	call   80489c0 <__best_dsput+0x2>
 8048294:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8048299:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 804829e:	b0 1b                	mov    al,0x1b
 80482a0:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80482a4:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 80482a9:	83 ec 02             	sub    esp,0x2
 80482ac:	e8 1d 0b 00 00       	call   8048dce <__best_cput+0x2>
 80482b1:	e8 ee 0b 00 00       	call   8048ea4 <__best_sput+0x6>

080482b6 <..@252._1>:
 80482b6:	5b                   	pop    ebx
 80482b7:	30                   	.byte 0x30
 80482b8:	6d                   	ins    DWORD PTR es:[edi],dx

080482b9 <..@252._2>:
 80482b9:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80482be:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 80482c3:	b0 09                	mov    al,0x9
 80482c5:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80482c9:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 80482ce:	83 ec 02             	sub    esp,0x2
 80482d1:	e8 f8 0a 00 00       	call   8048dce <__best_cput+0x2>
 80482d6:	e8 c5 0b 00 00       	call   8048ea0 <__best_sput+0x2>

080482db <..@257._1>:
 80482db:	20                   	.byte 0x20

080482dc <..@257._2>:
 80482dc:	e8 c3 0b 00 00       	call   8048ea4 <__best_sput+0x6>

080482e1 <..@259._1>:
 80482e1:	65 73 69             	gs jae 804834d <..@274._1>

080482e4 <..@259._2>:
 80482e4:	e8 bd 0b 00 00       	call   8048ea6 <__best_sput+0x8>

080482e9 <..@260._1>:
 80482e9:	20                   	.byte 0x20
 80482ea:	3d                   	.byte 0x3d
 80482eb:	3d                   	.byte 0x3d
 80482ec:	20                   	.byte 0x20

080482ed <..@260._2>:
 80482ed:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80482f2:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 80482f7:	b0 1b                	mov    al,0x1b
 80482f9:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80482fd:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8048302:	83 ec 02             	sub    esp,0x2
 8048305:	e8 c4 0a 00 00       	call   8048dce <__best_cput+0x2>
 804830a:	e8 97 0b 00 00       	call   8048ea6 <__best_sput+0x8>

0804830f <..@265._1>:
 804830f:	5b                   	pop    ebx
 8048310:	33 32                	xor    esi,DWORD PTR [edx]
 8048312:	6d                   	ins    DWORD PTR es:[edi],dx

08048313 <..@265._2>:
 8048313:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048318:	89 f0                	mov    eax,esi
 804831a:	89 44 24 fc          	mov    DWORD PTR [esp-0x4],eax
 804831e:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8048323:	83 ec 04             	sub    esp,0x4
 8048326:	e8 95 06 00 00       	call   80489c0 <__best_dsput+0x2>
 804832b:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8048330:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048335:	b0 1b                	mov    al,0x1b
 8048337:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804833b:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8048340:	83 ec 02             	sub    esp,0x2
 8048343:	e8 86 0a 00 00       	call   8048dce <__best_cput+0x2>
 8048348:	e8 57 0b 00 00       	call   8048ea4 <__best_sput+0x6>

0804834d <..@274._1>:
 804834d:	5b                   	pop    ebx
 804834e:	30                   	.byte 0x30
 804834f:	6d                   	ins    DWORD PTR es:[edi],dx

08048350 <..@274._2>:
 8048350:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8048355:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 804835a:	b0 09                	mov    al,0x9
 804835c:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8048360:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8048365:	83 ec 02             	sub    esp,0x2
 8048368:	e8 61 0a 00 00       	call   8048dce <__best_cput+0x2>
 804836d:	e8 2e 0b 00 00       	call   8048ea0 <__best_sput+0x2>

08048372 <..@279._1>:
 8048372:	20                   	.byte 0x20

08048373 <..@279._2>:
 8048373:	e8 2c 0b 00 00       	call   8048ea4 <__best_sput+0x6>

08048378 <..@281._1>:
 8048378:	65                   	gs
 8048379:	64                   	fs
 804837a:	69                   	.byte 0x69

0804837b <..@281._2>:
 804837b:	e8 26 0b 00 00       	call   8048ea6 <__best_sput+0x8>

08048380 <..@282._1>:
 8048380:	20                   	.byte 0x20
 8048381:	3d                   	.byte 0x3d
 8048382:	3d                   	.byte 0x3d
 8048383:	20                   	.byte 0x20

08048384 <..@282._2>:
 8048384:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8048389:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 804838e:	b0 1b                	mov    al,0x1b
 8048390:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8048394:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8048399:	83 ec 02             	sub    esp,0x2
 804839c:	e8 2d 0a 00 00       	call   8048dce <__best_cput+0x2>
 80483a1:	e8 00 0b 00 00       	call   8048ea6 <__best_sput+0x8>

080483a6 <..@287._1>:
 80483a6:	5b                   	pop    ebx
 80483a7:	33 32                	xor    esi,DWORD PTR [edx]
 80483a9:	6d                   	ins    DWORD PTR es:[edi],dx

080483aa <..@287._2>:
 80483aa:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 80483af:	89 f8                	mov    eax,edi
 80483b1:	89 44 24 fc          	mov    DWORD PTR [esp-0x4],eax
 80483b5:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 80483ba:	83 ec 04             	sub    esp,0x4
 80483bd:	e8 fe 05 00 00       	call   80489c0 <__best_dsput+0x2>
 80483c2:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80483c7:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 80483cc:	b0 1b                	mov    al,0x1b
 80483ce:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80483d2:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 80483d7:	83 ec 02             	sub    esp,0x2
 80483da:	e8 ef 09 00 00       	call   8048dce <__best_cput+0x2>
 80483df:	e8 c0 0a 00 00       	call   8048ea4 <__best_sput+0x6>

080483e4 <..@296._1>:
 80483e4:	5b                   	pop    ebx
 80483e5:	30                   	.byte 0x30
 80483e6:	6d                   	ins    DWORD PTR es:[edi],dx

080483e7 <..@296._2>:
 80483e7:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80483ec:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 80483f1:	b0 09                	mov    al,0x9
 80483f3:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80483f7:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 80483fc:	83 ec 02             	sub    esp,0x2
 80483ff:	e8 ca 09 00 00       	call   8048dce <__best_cput+0x2>
 8048404:	e8 97 0a 00 00       	call   8048ea0 <__best_sput+0x2>

08048409 <..@301._1>:
 8048409:	20                   	.byte 0x20

0804840a <..@301._2>:
 804840a:	e8 95 0a 00 00       	call   8048ea4 <__best_sput+0x6>

0804840f <..@303._1>:
 804840f:	65                   	gs
 8048410:	62                   	.byte 0x62
 8048411:	70                   	.byte 0x70

08048412 <..@303._2>:
 8048412:	e8 8f 0a 00 00       	call   8048ea6 <__best_sput+0x8>

08048417 <..@304._1>:
 8048417:	20                   	.byte 0x20
 8048418:	3d                   	.byte 0x3d
 8048419:	3d                   	.byte 0x3d
 804841a:	20                   	.byte 0x20

0804841b <..@304._2>:
 804841b:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8048420:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048425:	b0 1b                	mov    al,0x1b
 8048427:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804842b:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8048430:	83 ec 02             	sub    esp,0x2
 8048433:	e8 96 09 00 00       	call   8048dce <__best_cput+0x2>
 8048438:	e8 69 0a 00 00       	call   8048ea6 <__best_sput+0x8>

0804843d <..@309._1>:
 804843d:	5b                   	pop    ebx
 804843e:	33 32                	xor    esi,DWORD PTR [edx]
 8048440:	6d                   	ins    DWORD PTR es:[edi],dx

08048441 <..@309._2>:
 8048441:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048446:	89 e8                	mov    eax,ebp
 8048448:	89 44 24 fc          	mov    DWORD PTR [esp-0x4],eax
 804844c:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8048451:	83 ec 04             	sub    esp,0x4
 8048454:	e8 67 05 00 00       	call   80489c0 <__best_dsput+0x2>
 8048459:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804845e:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048463:	b0 1b                	mov    al,0x1b
 8048465:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8048469:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 804846e:	83 ec 02             	sub    esp,0x2
 8048471:	e8 58 09 00 00       	call   8048dce <__best_cput+0x2>
 8048476:	e8 29 0a 00 00       	call   8048ea4 <__best_sput+0x6>

0804847b <..@318._1>:
 804847b:	5b                   	pop    ebx
 804847c:	30                   	.byte 0x30
 804847d:	6d                   	ins    DWORD PTR es:[edi],dx

0804847e <..@318._2>:
 804847e:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8048483:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048488:	b0 09                	mov    al,0x9
 804848a:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804848e:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8048493:	83 ec 02             	sub    esp,0x2
 8048496:	e8 33 09 00 00       	call   8048dce <__best_cput+0x2>
 804849b:	e8 00 0a 00 00       	call   8048ea0 <__best_sput+0x2>

080484a0 <..@323._1>:
 80484a0:	20                   	.byte 0x20

080484a1 <..@323._2>:
 80484a1:	e8 fe 09 00 00       	call   8048ea4 <__best_sput+0x6>

080484a6 <..@325._1>:
 80484a6:	65 73 70             	gs jae 8048519 <..@331._2+0x41>

080484a9 <..@325._2>:
 80484a9:	e8 f8 09 00 00       	call   8048ea6 <__best_sput+0x8>

080484ae <..@326._1>:
 80484ae:	20                   	.byte 0x20
 80484af:	3d                   	.byte 0x3d
 80484b0:	3d                   	.byte 0x3d
 80484b1:	20                   	.byte 0x20

080484b2 <..@326._2>:
 80484b2:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80484b7:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 80484bc:	b0 1b                	mov    al,0x1b
 80484be:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80484c2:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 80484c7:	83 ec 02             	sub    esp,0x2
 80484ca:	e8 ff 08 00 00       	call   8048dce <__best_cput+0x2>
 80484cf:	e8 d2 09 00 00       	call   8048ea6 <__best_sput+0x8>

080484d4 <..@331._1>:
 80484d4:	5b                   	pop    ebx
 80484d5:	33 32                	xor    esi,DWORD PTR [edx]
 80484d7:	6d                   	ins    DWORD PTR es:[edi],dx

080484d8 <..@331._2>:
 80484d8:	29 24 24             	sub    DWORD PTR [esp],esp
 80484db:	f7 1c 24             	neg    DWORD PTR [esp]
 80484de:	87 04 24             	xchg   DWORD PTR [esp],eax
 80484e1:	83 c0 0c             	add    eax,0xc
 80484e4:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 80484e9:	89 c0                	mov    eax,eax
 80484eb:	89 44 24 fc          	mov    DWORD PTR [esp-0x4],eax
 80484ef:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 80484f4:	83 ec 04             	sub    esp,0x4
 80484f7:	e8 c4 04 00 00       	call   80489c0 <__best_dsput+0x2>
 80484fc:	83 e8 0c             	sub    eax,0xc
 80484ff:	87 04 24             	xchg   DWORD PTR [esp],eax
 8048502:	f7 1c 24             	neg    DWORD PTR [esp]
 8048505:	01 24 24             	add    DWORD PTR [esp],esp
 8048508:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804850d:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048512:	b0 1b                	mov    al,0x1b
 8048514:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8048518:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 804851d:	83 ec 02             	sub    esp,0x2
 8048520:	e8 a9 08 00 00       	call   8048dce <__best_cput+0x2>
 8048525:	e8 7a 09 00 00       	call   8048ea4 <__best_sput+0x6>

0804852a <..@340._1>:
 804852a:	5b                   	pop    ebx
 804852b:	30                   	.byte 0x30
 804852c:	6d                   	ins    DWORD PTR es:[edi],dx

0804852d <..@340._2>:
 804852d:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8048532:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048537:	b0 09                	mov    al,0x9
 8048539:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804853d:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8048542:	83 ec 02             	sub    esp,0x2
 8048545:	e8 84 08 00 00       	call   8048dce <__best_cput+0x2>
 804854a:	e8 5f 09 00 00       	call   8048eae <__best_sput+0x10>

0804854f <..@345._1>:
 804854f:	20 6c 69 6e          	and    BYTE PTR [ecx+ebp*2+0x6e],ch
 8048553:	65                   	gs
 8048554:	20                   	.byte 0x20
 8048555:	3d                   	.byte 0x3d
 8048556:	20                   	.byte 0x20

08048557 <..@345._2>:
 8048557:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804855c:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048561:	b0 1b                	mov    al,0x1b
 8048563:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8048567:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 804856c:	83 ec 02             	sub    esp,0x2
 804856f:	e8 5a 08 00 00       	call   8048dce <__best_cput+0x2>
 8048574:	e8 2d 09 00 00       	call   8048ea6 <__best_sput+0x8>

08048579 <..@350._1>:
 8048579:	5b                   	pop    ebx
 804857a:	33 32                	xor    esi,DWORD PTR [edx]
 804857c:	6d                   	ins    DWORD PTR es:[edi],dx

0804857d <..@350._2>:
 804857d:	87 44 24 04          	xchg   DWORD PTR [esp+0x4],eax
 8048581:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048586:	89 c0                	mov    eax,eax
 8048588:	89 44 24 fc          	mov    DWORD PTR [esp-0x4],eax
 804858c:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8048591:	83 ec 04             	sub    esp,0x4
 8048594:	e8 27 04 00 00       	call   80489c0 <__best_dsput+0x2>
 8048599:	87 44 24 04          	xchg   DWORD PTR [esp+0x4],eax
 804859d:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80485a2:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 80485a7:	b0 1b                	mov    al,0x1b
 80485a9:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80485ad:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 80485b2:	83 ec 02             	sub    esp,0x2
 80485b5:	e8 14 08 00 00       	call   8048dce <__best_cput+0x2>
 80485ba:	e8 e5 08 00 00       	call   8048ea4 <__best_sput+0x6>

080485bf <..@359._1>:
 80485bf:	5b                   	pop    ebx
 80485c0:	30                   	.byte 0x30
 80485c1:	6d                   	ins    DWORD PTR es:[edi],dx

080485c2 <..@359._2>:
 80485c2:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80485c7:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 80485cc:	b0 0a                	mov    al,0xa
 80485ce:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80485d2:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 80485d7:	83 ec 02             	sub    esp,0x2
 80485da:	e8 ef 07 00 00       	call   8048dce <__best_cput+0x2>
 80485df:	83 c4 08             	add    esp,0x8
 80485e2:	c3                   	ret    

080485e3 <__best__uput_one>:
 80485e3:	83 ec 04             	sub    esp,0x4
 80485e6:	60                   	pusha  
 80485e7:	ba 00 00 00 00       	mov    edx,0x0
 80485ec:	b9 00 00 00 00       	mov    ecx,0x0
 80485f1:	be 00 00 00 00       	mov    esi,0x0
 80485f6:	bd 00 00 00 00       	mov    ebp,0x0
 80485fb:	bb 0a 00 00 00       	mov    ebx,0xa
 8048600:	89 c7                	mov    edi,eax

08048602 <__best__uput_one_1>:
 8048602:	41                   	inc    ecx
 8048603:	f7 f3                	div    ebx
 8048605:	ba 00 00 00 00       	mov    edx,0x0
 804860a:	83 f8 00             	cmp    eax,0x0
 804860d:	75 f3                	jne    8048602 <__best__uput_one_1>
 804860f:	89 ce                	mov    esi,ecx
 8048611:	ba 00 00 00 00       	mov    edx,0x0
 8048616:	b8 01 00 00 00       	mov    eax,0x1

0804861b <__best__uput_one_2>:
 804861b:	50                   	push   eax
 804861c:	f7 e3                	mul    ebx
 804861e:	e2 fb                	loop   804861b <__best__uput_one_2>
 8048620:	89 f1                	mov    ecx,esi
 8048622:	89 f8                	mov    eax,edi

08048624 <__best__uput_one_3>:
 8048624:	5b                   	pop    ebx
 8048625:	ba 00 00 00 00       	mov    edx,0x0
 804862a:	f7 f3                	div    ebx
 804862c:	83 c0 30             	add    eax,0x30
 804862f:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8048634:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048639:	88 c0                	mov    al,al
 804863b:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804863f:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8048644:	83 ec 02             	sub    esp,0x2
 8048647:	e8 82 07 00 00       	call   8048dce <__best_cput+0x2>
 804864c:	89 d0                	mov    eax,edx
 804864e:	e2 d4                	loop   8048624 <__best__uput_one_3>
 8048650:	61                   	popa   
 8048651:	83 c4 04             	add    esp,0x4
 8048654:	c3                   	ret    

08048655 <__best_quput_one>:
 8048655:	e8 89 ff ff ff       	call   80485e3 <__best__uput_one>
 804865a:	c3                   	ret    

0804865b <__best_qsput_one>:
 804865b:	83 f8 00             	cmp    eax,0x0
 804865e:	7d 1f                	jge    804867f <..@369._1>
 8048660:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8048665:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 804866a:	b0 2d                	mov    al,0x2d
 804866c:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8048670:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8048675:	83 ec 02             	sub    esp,0x2
 8048678:	e8 51 07 00 00       	call   8048dce <__best_cput+0x2>
 804867d:	f7 d8                	neg    eax

0804867f <..@369._1>:
 804867f:	e8 5f ff ff ff       	call   80485e3 <__best__uput_one>
 8048684:	c3                   	ret    

08048685 <__best_duput_one>:
 8048685:	e8 59 ff ff ff       	call   80485e3 <__best__uput_one>
 804868a:	c3                   	ret    

0804868b <__best_dsput_one>:
 804868b:	83 f8 00             	cmp    eax,0x0
 804868e:	7d 1f                	jge    80486af <..@374._1>
 8048690:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8048695:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 804869a:	b0 2d                	mov    al,0x2d
 804869c:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80486a0:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 80486a5:	83 ec 02             	sub    esp,0x2
 80486a8:	e8 21 07 00 00       	call   8048dce <__best_cput+0x2>
 80486ad:	f7 d8                	neg    eax

080486af <..@374._1>:
 80486af:	e8 2f ff ff ff       	call   80485e3 <__best__uput_one>
 80486b4:	c3                   	ret    

080486b5 <__best_wuput_one>:
 80486b5:	e8 29 ff ff ff       	call   80485e3 <__best__uput_one>
 80486ba:	c3                   	ret    

080486bb <__best_wsput_one>:
 80486bb:	c1 e0 08             	shl    eax,0x8
 80486be:	c1 e0 08             	shl    eax,0x8
 80486c1:	83 f8 00             	cmp    eax,0x0
 80486c4:	7d 1f                	jge    80486e5 <..@379._1>
 80486c6:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80486cb:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 80486d0:	b0 2d                	mov    al,0x2d
 80486d2:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80486d6:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 80486db:	83 ec 02             	sub    esp,0x2
 80486de:	e8 eb 06 00 00       	call   8048dce <__best_cput+0x2>
 80486e3:	f7 d8                	neg    eax

080486e5 <..@379._1>:
 80486e5:	c1 e8 08             	shr    eax,0x8
 80486e8:	c1 e8 08             	shr    eax,0x8
 80486eb:	e8 f3 fe ff ff       	call   80485e3 <__best__uput_one>
 80486f0:	c3                   	ret    

080486f1 <__best_buput_one>:
 80486f1:	e8 ed fe ff ff       	call   80485e3 <__best__uput_one>
 80486f6:	c3                   	ret    

080486f7 <__best_bsput_one>:
 80486f7:	c1 e0 08             	shl    eax,0x8
 80486fa:	c1 e0 08             	shl    eax,0x8
 80486fd:	c1 e0 08             	shl    eax,0x8
 8048700:	83 f8 00             	cmp    eax,0x0
 8048703:	7d 1f                	jge    8048724 <..@384._1>
 8048705:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804870a:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 804870f:	b0 2d                	mov    al,0x2d
 8048711:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8048715:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 804871a:	83 ec 02             	sub    esp,0x2
 804871d:	e8 ac 06 00 00       	call   8048dce <__best_cput+0x2>
 8048722:	f7 d8                	neg    eax

08048724 <..@384._1>:
 8048724:	c1 e8 08             	shr    eax,0x8
 8048727:	c1 e8 08             	shr    eax,0x8
 804872a:	c1 e8 08             	shr    eax,0x8
 804872d:	e8 b1 fe ff ff       	call   80485e3 <__best__uput_one>
 8048732:	c3                   	ret    

08048733 <__best_cput_one>:
 8048733:	60                   	pusha  
 8048734:	66 50                	push   ax
 8048736:	b8 04 00 00 00       	mov    eax,0x4
 804873b:	bb 01 00 00 00       	mov    ebx,0x1
 8048740:	89 e1                	mov    ecx,esp
 8048742:	ba 01 00 00 00       	mov    edx,0x1
 8048747:	cd 80                	int    0x80
 8048749:	83 c4 02             	add    esp,0x2
 804874c:	61                   	popa   
 804874d:	c3                   	ret    

0804874e <__best_sput_one>:
 804874e:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8048753:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048758:	88 c0                	mov    al,al
 804875a:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804875e:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8048763:	83 ec 02             	sub    esp,0x2
 8048766:	e8 63 06 00 00       	call   8048dce <__best_cput+0x2>
 804876b:	c3                   	ret    

0804876c <__best_quput>:
 804876c:	6a 00                	push   0x0
 804876e:	6a 00                	push   0x0
 8048770:	6a 00                	push   0x0
 8048772:	6a 00                	push   0x0
 8048774:	6a 00                	push   0x0
 8048776:	6a 00                	push   0x0
 8048778:	6a 00                	push   0x0
 804877a:	6a 00                	push   0x0
 804877c:	6a 00                	push   0x0
 804877e:	6a 00                	push   0x0
 8048780:	6a 00                	push   0x0
 8048782:	6a 00                	push   0x0
 8048784:	6a 00                	push   0x0
 8048786:	6a 00                	push   0x0
 8048788:	6a 00                	push   0x0
 804878a:	6a 00                	push   0x0
 804878c:	6a 00                	push   0x0
 804878e:	6a 00                	push   0x0
 8048790:	6a 00                	push   0x0
 8048792:	6a 00                	push   0x0
 8048794:	6a 00                	push   0x0
 8048796:	6a 00                	push   0x0
 8048798:	6a 00                	push   0x0
 804879a:	6a 00                	push   0x0
 804879c:	6a 00                	push   0x0
 804879e:	6a 00                	push   0x0
 80487a0:	6a 00                	push   0x0
 80487a2:	6a 00                	push   0x0
 80487a4:	6a 00                	push   0x0
 80487a6:	6a 00                	push   0x0
 80487a8:	6a 00                	push   0x0
 80487aa:	6a 00                	push   0x0
 80487ac:	6a 20                	push   0x20

080487ae <..@394._1>:
 80487ae:	bd 00 00 00 00       	mov    ebp,0x0
 80487b3:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 80487b7:	75 08                	jne    80487c1 <..@394._2>
 80487b9:	ff 0c 24             	dec    DWORD PTR [esp]
 80487bc:	8f 04 24             	pop    DWORD PTR [esp]
 80487bf:	eb ed                	jmp    80487ae <..@394._1>

080487c1 <..@394._2>:
 80487c1:	60                   	pusha  
 80487c2:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 80487c6:	89 e2                	mov    edx,esp
 80487c8:	83 c2 28             	add    edx,0x28
 80487cb:	89 cb                	mov    ebx,ecx
 80487cd:	90                   	nop
 80487ce:	60                   	pusha  
 80487cf:	89 d9                	mov    ecx,ebx

080487d1 <..@393._2>:
 80487d1:	83 f9 01             	cmp    ecx,0x1
 80487d4:	7c 34                	jl     804880a <..@393._1>
 80487d6:	b8 00 00 00 00       	mov    eax,0x0
 80487db:	8b 02                	mov    eax,DWORD PTR [edx]
 80487dd:	e8 73 fe ff ff       	call   8048655 <__best_quput_one>
 80487e2:	83 c2 08             	add    edx,0x8
 80487e5:	49                   	dec    ecx
 80487e6:	83 f9 01             	cmp    ecx,0x1
 80487e9:	7c 1f                	jl     804880a <..@393._1>
 80487eb:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80487f0:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 80487f5:	b0 20                	mov    al,0x20
 80487f7:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80487fb:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8048800:	83 ec 02             	sub    esp,0x2
 8048803:	e8 c6 05 00 00       	call   8048dce <__best_cput+0x2>
 8048808:	eb c7                	jmp    80487d1 <..@393._2>

0804880a <..@393._1>:
 804880a:	61                   	popa   
 804880b:	89 c8                	mov    eax,ecx
 804880d:	bb 08 00 00 00       	mov    ebx,0x8
 8048812:	f7 e3                	mul    ebx
 8048814:	89 e3                	mov    ebx,esp
 8048816:	89 de                	mov    esi,ebx
 8048818:	89 df                	mov    edi,ebx
 804881a:	01 c7                	add    edi,eax
 804881c:	b9 28 00 00 00       	mov    ecx,0x28
 8048821:	01 cf                	add    edi,ecx
 8048823:	01 ce                	add    esi,ecx
 8048825:	4f                   	dec    edi
 8048826:	4e                   	dec    esi
 8048827:	fd                   	std    
 8048828:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 804882a:	fc                   	cld    
 804882b:	01 c4                	add    esp,eax
 804882d:	61                   	popa   
 804882e:	83 c4 04             	add    esp,0x4
 8048831:	c3                   	ret    

08048832 <__best_qsput>:
 8048832:	6a 00                	push   0x0
 8048834:	6a 00                	push   0x0
 8048836:	6a 00                	push   0x0
 8048838:	6a 00                	push   0x0
 804883a:	6a 00                	push   0x0
 804883c:	6a 00                	push   0x0
 804883e:	6a 00                	push   0x0
 8048840:	6a 00                	push   0x0
 8048842:	6a 00                	push   0x0
 8048844:	6a 00                	push   0x0
 8048846:	6a 00                	push   0x0
 8048848:	6a 00                	push   0x0
 804884a:	6a 00                	push   0x0
 804884c:	6a 00                	push   0x0
 804884e:	6a 00                	push   0x0
 8048850:	6a 00                	push   0x0
 8048852:	6a 00                	push   0x0
 8048854:	6a 00                	push   0x0
 8048856:	6a 00                	push   0x0
 8048858:	6a 00                	push   0x0
 804885a:	6a 00                	push   0x0
 804885c:	6a 00                	push   0x0
 804885e:	6a 00                	push   0x0
 8048860:	6a 00                	push   0x0
 8048862:	6a 00                	push   0x0
 8048864:	6a 00                	push   0x0
 8048866:	6a 00                	push   0x0
 8048868:	6a 00                	push   0x0
 804886a:	6a 00                	push   0x0
 804886c:	6a 00                	push   0x0
 804886e:	6a 00                	push   0x0
 8048870:	6a 00                	push   0x0
 8048872:	6a 20                	push   0x20

08048874 <..@400._1>:
 8048874:	bd 00 00 00 00       	mov    ebp,0x0
 8048879:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 804887d:	75 08                	jne    8048887 <..@400._2>
 804887f:	ff 0c 24             	dec    DWORD PTR [esp]
 8048882:	8f 04 24             	pop    DWORD PTR [esp]
 8048885:	eb ed                	jmp    8048874 <..@400._1>

08048887 <..@400._2>:
 8048887:	60                   	pusha  
 8048888:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 804888c:	89 e2                	mov    edx,esp
 804888e:	83 c2 28             	add    edx,0x28
 8048891:	89 cb                	mov    ebx,ecx
 8048893:	90                   	nop
 8048894:	60                   	pusha  
 8048895:	89 d9                	mov    ecx,ebx

08048897 <..@399._2>:
 8048897:	83 f9 01             	cmp    ecx,0x1
 804889a:	7c 34                	jl     80488d0 <..@399._1>
 804889c:	b8 00 00 00 00       	mov    eax,0x0
 80488a1:	8b 02                	mov    eax,DWORD PTR [edx]
 80488a3:	e8 b3 fd ff ff       	call   804865b <__best_qsput_one>
 80488a8:	83 c2 08             	add    edx,0x8
 80488ab:	49                   	dec    ecx
 80488ac:	83 f9 01             	cmp    ecx,0x1
 80488af:	7c 1f                	jl     80488d0 <..@399._1>
 80488b1:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80488b6:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 80488bb:	b0 20                	mov    al,0x20
 80488bd:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80488c1:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 80488c6:	83 ec 02             	sub    esp,0x2
 80488c9:	e8 00 05 00 00       	call   8048dce <__best_cput+0x2>
 80488ce:	eb c7                	jmp    8048897 <..@399._2>

080488d0 <..@399._1>:
 80488d0:	61                   	popa   
 80488d1:	89 c8                	mov    eax,ecx
 80488d3:	bb 08 00 00 00       	mov    ebx,0x8
 80488d8:	f7 e3                	mul    ebx
 80488da:	89 e3                	mov    ebx,esp
 80488dc:	89 de                	mov    esi,ebx
 80488de:	89 df                	mov    edi,ebx
 80488e0:	01 c7                	add    edi,eax
 80488e2:	b9 28 00 00 00       	mov    ecx,0x28
 80488e7:	01 cf                	add    edi,ecx
 80488e9:	01 ce                	add    esi,ecx
 80488eb:	4f                   	dec    edi
 80488ec:	4e                   	dec    esi
 80488ed:	fd                   	std    
 80488ee:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 80488f0:	fc                   	cld    
 80488f1:	01 c4                	add    esp,eax
 80488f3:	61                   	popa   
 80488f4:	83 c4 04             	add    esp,0x4
 80488f7:	c3                   	ret    

080488f8 <__best_duput>:
 80488f8:	6a 00                	push   0x0
 80488fa:	6a 00                	push   0x0
 80488fc:	6a 00                	push   0x0
 80488fe:	6a 00                	push   0x0
 8048900:	6a 00                	push   0x0
 8048902:	6a 00                	push   0x0
 8048904:	6a 00                	push   0x0
 8048906:	6a 00                	push   0x0
 8048908:	6a 00                	push   0x0
 804890a:	6a 00                	push   0x0
 804890c:	6a 00                	push   0x0
 804890e:	6a 00                	push   0x0
 8048910:	6a 00                	push   0x0
 8048912:	6a 00                	push   0x0
 8048914:	6a 00                	push   0x0
 8048916:	6a 00                	push   0x0
 8048918:	6a 00                	push   0x0
 804891a:	6a 00                	push   0x0
 804891c:	6a 00                	push   0x0
 804891e:	6a 00                	push   0x0
 8048920:	6a 00                	push   0x0
 8048922:	6a 00                	push   0x0
 8048924:	6a 00                	push   0x0
 8048926:	6a 00                	push   0x0
 8048928:	6a 00                	push   0x0
 804892a:	6a 00                	push   0x0
 804892c:	6a 00                	push   0x0
 804892e:	6a 00                	push   0x0
 8048930:	6a 00                	push   0x0
 8048932:	6a 00                	push   0x0
 8048934:	6a 00                	push   0x0
 8048936:	6a 00                	push   0x0
 8048938:	6a 20                	push   0x20

0804893a <..@406._1>:
 804893a:	bd 00 00 00 00       	mov    ebp,0x0
 804893f:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 8048943:	75 08                	jne    804894d <..@406._2>
 8048945:	ff 0c 24             	dec    DWORD PTR [esp]
 8048948:	8f 04 24             	pop    DWORD PTR [esp]
 804894b:	eb ed                	jmp    804893a <..@406._1>

0804894d <..@406._2>:
 804894d:	60                   	pusha  
 804894e:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8048952:	89 e2                	mov    edx,esp
 8048954:	83 c2 28             	add    edx,0x28
 8048957:	89 cb                	mov    ebx,ecx
 8048959:	90                   	nop
 804895a:	60                   	pusha  
 804895b:	89 d9                	mov    ecx,ebx

0804895d <..@405._2>:
 804895d:	83 f9 01             	cmp    ecx,0x1
 8048960:	7c 34                	jl     8048996 <..@405._1>
 8048962:	b8 00 00 00 00       	mov    eax,0x0
 8048967:	8b 02                	mov    eax,DWORD PTR [edx]
 8048969:	e8 17 fd ff ff       	call   8048685 <__best_duput_one>
 804896e:	83 c2 04             	add    edx,0x4
 8048971:	49                   	dec    ecx
 8048972:	83 f9 01             	cmp    ecx,0x1
 8048975:	7c 1f                	jl     8048996 <..@405._1>
 8048977:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804897c:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048981:	b0 20                	mov    al,0x20
 8048983:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8048987:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 804898c:	83 ec 02             	sub    esp,0x2
 804898f:	e8 3a 04 00 00       	call   8048dce <__best_cput+0x2>
 8048994:	eb c7                	jmp    804895d <..@405._2>

08048996 <..@405._1>:
 8048996:	61                   	popa   
 8048997:	89 c8                	mov    eax,ecx
 8048999:	bb 04 00 00 00       	mov    ebx,0x4
 804899e:	f7 e3                	mul    ebx
 80489a0:	89 e3                	mov    ebx,esp
 80489a2:	89 de                	mov    esi,ebx
 80489a4:	89 df                	mov    edi,ebx
 80489a6:	01 c7                	add    edi,eax
 80489a8:	b9 28 00 00 00       	mov    ecx,0x28
 80489ad:	01 cf                	add    edi,ecx
 80489af:	01 ce                	add    esi,ecx
 80489b1:	4f                   	dec    edi
 80489b2:	4e                   	dec    esi
 80489b3:	fd                   	std    
 80489b4:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 80489b6:	fc                   	cld    
 80489b7:	01 c4                	add    esp,eax
 80489b9:	61                   	popa   
 80489ba:	83 c4 04             	add    esp,0x4
 80489bd:	c3                   	ret    

080489be <__best_dsput>:
 80489be:	6a 00                	push   0x0
 80489c0:	6a 00                	push   0x0
 80489c2:	6a 00                	push   0x0
 80489c4:	6a 00                	push   0x0
 80489c6:	6a 00                	push   0x0
 80489c8:	6a 00                	push   0x0
 80489ca:	6a 00                	push   0x0
 80489cc:	6a 00                	push   0x0
 80489ce:	6a 00                	push   0x0
 80489d0:	6a 00                	push   0x0
 80489d2:	6a 00                	push   0x0
 80489d4:	6a 00                	push   0x0
 80489d6:	6a 00                	push   0x0
 80489d8:	6a 00                	push   0x0
 80489da:	6a 00                	push   0x0
 80489dc:	6a 00                	push   0x0
 80489de:	6a 00                	push   0x0
 80489e0:	6a 00                	push   0x0
 80489e2:	6a 00                	push   0x0
 80489e4:	6a 00                	push   0x0
 80489e6:	6a 00                	push   0x0
 80489e8:	6a 00                	push   0x0
 80489ea:	6a 00                	push   0x0
 80489ec:	6a 00                	push   0x0
 80489ee:	6a 00                	push   0x0
 80489f0:	6a 00                	push   0x0
 80489f2:	6a 00                	push   0x0
 80489f4:	6a 00                	push   0x0
 80489f6:	6a 00                	push   0x0
 80489f8:	6a 00                	push   0x0
 80489fa:	6a 00                	push   0x0
 80489fc:	6a 00                	push   0x0
 80489fe:	6a 20                	push   0x20

08048a00 <..@412._1>:
 8048a00:	bd 00 00 00 00       	mov    ebp,0x0
 8048a05:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 8048a09:	75 08                	jne    8048a13 <..@412._2>
 8048a0b:	ff 0c 24             	dec    DWORD PTR [esp]
 8048a0e:	8f 04 24             	pop    DWORD PTR [esp]
 8048a11:	eb ed                	jmp    8048a00 <..@412._1>

08048a13 <..@412._2>:
 8048a13:	60                   	pusha  
 8048a14:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8048a18:	89 e2                	mov    edx,esp
 8048a1a:	83 c2 28             	add    edx,0x28
 8048a1d:	89 cb                	mov    ebx,ecx
 8048a1f:	90                   	nop
 8048a20:	60                   	pusha  
 8048a21:	89 d9                	mov    ecx,ebx

08048a23 <..@411._2>:
 8048a23:	83 f9 01             	cmp    ecx,0x1
 8048a26:	7c 34                	jl     8048a5c <..@411._1>
 8048a28:	b8 00 00 00 00       	mov    eax,0x0
 8048a2d:	8b 02                	mov    eax,DWORD PTR [edx]
 8048a2f:	e8 57 fc ff ff       	call   804868b <__best_dsput_one>
 8048a34:	83 c2 04             	add    edx,0x4
 8048a37:	49                   	dec    ecx
 8048a38:	83 f9 01             	cmp    ecx,0x1
 8048a3b:	7c 1f                	jl     8048a5c <..@411._1>
 8048a3d:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8048a42:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048a47:	b0 20                	mov    al,0x20
 8048a49:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8048a4d:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8048a52:	83 ec 02             	sub    esp,0x2
 8048a55:	e8 74 03 00 00       	call   8048dce <__best_cput+0x2>
 8048a5a:	eb c7                	jmp    8048a23 <..@411._2>

08048a5c <..@411._1>:
 8048a5c:	61                   	popa   
 8048a5d:	89 c8                	mov    eax,ecx
 8048a5f:	bb 04 00 00 00       	mov    ebx,0x4
 8048a64:	f7 e3                	mul    ebx
 8048a66:	89 e3                	mov    ebx,esp
 8048a68:	89 de                	mov    esi,ebx
 8048a6a:	89 df                	mov    edi,ebx
 8048a6c:	01 c7                	add    edi,eax
 8048a6e:	b9 28 00 00 00       	mov    ecx,0x28
 8048a73:	01 cf                	add    edi,ecx
 8048a75:	01 ce                	add    esi,ecx
 8048a77:	4f                   	dec    edi
 8048a78:	4e                   	dec    esi
 8048a79:	fd                   	std    
 8048a7a:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8048a7c:	fc                   	cld    
 8048a7d:	01 c4                	add    esp,eax
 8048a7f:	61                   	popa   
 8048a80:	83 c4 04             	add    esp,0x4
 8048a83:	c3                   	ret    

08048a84 <__best_wuput>:
 8048a84:	6a 00                	push   0x0
 8048a86:	6a 00                	push   0x0
 8048a88:	6a 00                	push   0x0
 8048a8a:	6a 00                	push   0x0
 8048a8c:	6a 00                	push   0x0
 8048a8e:	6a 00                	push   0x0
 8048a90:	6a 00                	push   0x0
 8048a92:	6a 00                	push   0x0
 8048a94:	6a 00                	push   0x0
 8048a96:	6a 00                	push   0x0
 8048a98:	6a 00                	push   0x0
 8048a9a:	6a 00                	push   0x0
 8048a9c:	6a 00                	push   0x0
 8048a9e:	6a 00                	push   0x0
 8048aa0:	6a 00                	push   0x0
 8048aa2:	6a 00                	push   0x0
 8048aa4:	6a 00                	push   0x0
 8048aa6:	6a 00                	push   0x0
 8048aa8:	6a 00                	push   0x0
 8048aaa:	6a 00                	push   0x0
 8048aac:	6a 00                	push   0x0
 8048aae:	6a 00                	push   0x0
 8048ab0:	6a 00                	push   0x0
 8048ab2:	6a 00                	push   0x0
 8048ab4:	6a 00                	push   0x0
 8048ab6:	6a 00                	push   0x0
 8048ab8:	6a 00                	push   0x0
 8048aba:	6a 00                	push   0x0
 8048abc:	6a 00                	push   0x0
 8048abe:	6a 00                	push   0x0
 8048ac0:	6a 00                	push   0x0
 8048ac2:	6a 00                	push   0x0
 8048ac4:	6a 20                	push   0x20

08048ac6 <..@418._1>:
 8048ac6:	bd 00 00 00 00       	mov    ebp,0x0
 8048acb:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 8048acf:	75 08                	jne    8048ad9 <..@418._2>
 8048ad1:	ff 0c 24             	dec    DWORD PTR [esp]
 8048ad4:	8f 04 24             	pop    DWORD PTR [esp]
 8048ad7:	eb ed                	jmp    8048ac6 <..@418._1>

08048ad9 <..@418._2>:
 8048ad9:	60                   	pusha  
 8048ada:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8048ade:	89 e2                	mov    edx,esp
 8048ae0:	83 c2 28             	add    edx,0x28
 8048ae3:	89 cb                	mov    ebx,ecx
 8048ae5:	90                   	nop
 8048ae6:	60                   	pusha  
 8048ae7:	89 d9                	mov    ecx,ebx

08048ae9 <..@417._2>:
 8048ae9:	83 f9 01             	cmp    ecx,0x1
 8048aec:	7c 40                	jl     8048b2e <..@417._1>
 8048aee:	b8 00 00 00 00       	mov    eax,0x0
 8048af3:	8b 02                	mov    eax,DWORD PTR [edx]
 8048af5:	c1 e0 08             	shl    eax,0x8
 8048af8:	c1 e0 08             	shl    eax,0x8
 8048afb:	c1 e8 08             	shr    eax,0x8
 8048afe:	c1 e8 08             	shr    eax,0x8
 8048b01:	e8 af fb ff ff       	call   80486b5 <__best_wuput_one>
 8048b06:	83 c2 02             	add    edx,0x2
 8048b09:	49                   	dec    ecx
 8048b0a:	83 f9 01             	cmp    ecx,0x1
 8048b0d:	7c 1f                	jl     8048b2e <..@417._1>
 8048b0f:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8048b14:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048b19:	b0 20                	mov    al,0x20
 8048b1b:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8048b1f:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8048b24:	83 ec 02             	sub    esp,0x2
 8048b27:	e8 a2 02 00 00       	call   8048dce <__best_cput+0x2>
 8048b2c:	eb bb                	jmp    8048ae9 <..@417._2>

08048b2e <..@417._1>:
 8048b2e:	61                   	popa   
 8048b2f:	89 c8                	mov    eax,ecx
 8048b31:	bb 02 00 00 00       	mov    ebx,0x2
 8048b36:	f7 e3                	mul    ebx
 8048b38:	89 e3                	mov    ebx,esp
 8048b3a:	89 de                	mov    esi,ebx
 8048b3c:	89 df                	mov    edi,ebx
 8048b3e:	01 c7                	add    edi,eax
 8048b40:	b9 28 00 00 00       	mov    ecx,0x28
 8048b45:	01 cf                	add    edi,ecx
 8048b47:	01 ce                	add    esi,ecx
 8048b49:	4f                   	dec    edi
 8048b4a:	4e                   	dec    esi
 8048b4b:	fd                   	std    
 8048b4c:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8048b4e:	fc                   	cld    
 8048b4f:	01 c4                	add    esp,eax
 8048b51:	61                   	popa   
 8048b52:	83 c4 04             	add    esp,0x4
 8048b55:	c3                   	ret    

08048b56 <__best_wsput>:
 8048b56:	6a 00                	push   0x0
 8048b58:	6a 00                	push   0x0
 8048b5a:	6a 00                	push   0x0
 8048b5c:	6a 00                	push   0x0
 8048b5e:	6a 00                	push   0x0
 8048b60:	6a 00                	push   0x0
 8048b62:	6a 00                	push   0x0
 8048b64:	6a 00                	push   0x0
 8048b66:	6a 00                	push   0x0
 8048b68:	6a 00                	push   0x0
 8048b6a:	6a 00                	push   0x0
 8048b6c:	6a 00                	push   0x0
 8048b6e:	6a 00                	push   0x0
 8048b70:	6a 00                	push   0x0
 8048b72:	6a 00                	push   0x0
 8048b74:	6a 00                	push   0x0
 8048b76:	6a 00                	push   0x0
 8048b78:	6a 00                	push   0x0
 8048b7a:	6a 00                	push   0x0
 8048b7c:	6a 00                	push   0x0
 8048b7e:	6a 00                	push   0x0
 8048b80:	6a 00                	push   0x0
 8048b82:	6a 00                	push   0x0
 8048b84:	6a 00                	push   0x0
 8048b86:	6a 00                	push   0x0
 8048b88:	6a 00                	push   0x0
 8048b8a:	6a 00                	push   0x0
 8048b8c:	6a 00                	push   0x0
 8048b8e:	6a 00                	push   0x0
 8048b90:	6a 00                	push   0x0
 8048b92:	6a 00                	push   0x0
 8048b94:	6a 00                	push   0x0
 8048b96:	6a 20                	push   0x20

08048b98 <..@424._1>:
 8048b98:	bd 00 00 00 00       	mov    ebp,0x0
 8048b9d:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 8048ba1:	75 08                	jne    8048bab <..@424._2>
 8048ba3:	ff 0c 24             	dec    DWORD PTR [esp]
 8048ba6:	8f 04 24             	pop    DWORD PTR [esp]
 8048ba9:	eb ed                	jmp    8048b98 <..@424._1>

08048bab <..@424._2>:
 8048bab:	60                   	pusha  
 8048bac:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8048bb0:	89 e2                	mov    edx,esp
 8048bb2:	83 c2 28             	add    edx,0x28
 8048bb5:	89 cb                	mov    ebx,ecx
 8048bb7:	90                   	nop
 8048bb8:	60                   	pusha  
 8048bb9:	89 d9                	mov    ecx,ebx

08048bbb <..@423._2>:
 8048bbb:	83 f9 01             	cmp    ecx,0x1
 8048bbe:	7c 40                	jl     8048c00 <..@423._1>
 8048bc0:	b8 00 00 00 00       	mov    eax,0x0
 8048bc5:	8b 02                	mov    eax,DWORD PTR [edx]
 8048bc7:	c1 e0 08             	shl    eax,0x8
 8048bca:	c1 e0 08             	shl    eax,0x8
 8048bcd:	c1 e8 08             	shr    eax,0x8
 8048bd0:	c1 e8 08             	shr    eax,0x8
 8048bd3:	e8 e3 fa ff ff       	call   80486bb <__best_wsput_one>
 8048bd8:	83 c2 02             	add    edx,0x2
 8048bdb:	49                   	dec    ecx
 8048bdc:	83 f9 01             	cmp    ecx,0x1
 8048bdf:	7c 1f                	jl     8048c00 <..@423._1>
 8048be1:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8048be6:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048beb:	b0 20                	mov    al,0x20
 8048bed:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8048bf1:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8048bf6:	83 ec 02             	sub    esp,0x2
 8048bf9:	e8 d0 01 00 00       	call   8048dce <__best_cput+0x2>
 8048bfe:	eb bb                	jmp    8048bbb <..@423._2>

08048c00 <..@423._1>:
 8048c00:	61                   	popa   
 8048c01:	89 c8                	mov    eax,ecx
 8048c03:	bb 02 00 00 00       	mov    ebx,0x2
 8048c08:	f7 e3                	mul    ebx
 8048c0a:	89 e3                	mov    ebx,esp
 8048c0c:	89 de                	mov    esi,ebx
 8048c0e:	89 df                	mov    edi,ebx
 8048c10:	01 c7                	add    edi,eax
 8048c12:	b9 28 00 00 00       	mov    ecx,0x28
 8048c17:	01 cf                	add    edi,ecx
 8048c19:	01 ce                	add    esi,ecx
 8048c1b:	4f                   	dec    edi
 8048c1c:	4e                   	dec    esi
 8048c1d:	fd                   	std    
 8048c1e:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8048c20:	fc                   	cld    
 8048c21:	01 c4                	add    esp,eax
 8048c23:	61                   	popa   
 8048c24:	83 c4 04             	add    esp,0x4
 8048c27:	c3                   	ret    

08048c28 <__best_buput>:
 8048c28:	6a 00                	push   0x0
 8048c2a:	6a 00                	push   0x0
 8048c2c:	6a 00                	push   0x0
 8048c2e:	6a 00                	push   0x0
 8048c30:	6a 00                	push   0x0
 8048c32:	6a 00                	push   0x0
 8048c34:	6a 00                	push   0x0
 8048c36:	6a 00                	push   0x0
 8048c38:	6a 00                	push   0x0
 8048c3a:	6a 00                	push   0x0
 8048c3c:	6a 00                	push   0x0
 8048c3e:	6a 00                	push   0x0
 8048c40:	6a 00                	push   0x0
 8048c42:	6a 00                	push   0x0
 8048c44:	6a 00                	push   0x0
 8048c46:	6a 00                	push   0x0
 8048c48:	6a 00                	push   0x0
 8048c4a:	6a 00                	push   0x0
 8048c4c:	6a 00                	push   0x0
 8048c4e:	6a 00                	push   0x0
 8048c50:	6a 00                	push   0x0
 8048c52:	6a 00                	push   0x0
 8048c54:	6a 00                	push   0x0
 8048c56:	6a 00                	push   0x0
 8048c58:	6a 00                	push   0x0
 8048c5a:	6a 00                	push   0x0
 8048c5c:	6a 00                	push   0x0
 8048c5e:	6a 00                	push   0x0
 8048c60:	6a 00                	push   0x0
 8048c62:	6a 00                	push   0x0
 8048c64:	6a 00                	push   0x0
 8048c66:	6a 00                	push   0x0
 8048c68:	6a 20                	push   0x20

08048c6a <..@430._1>:
 8048c6a:	bd 00 00 00 00       	mov    ebp,0x0
 8048c6f:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 8048c73:	75 08                	jne    8048c7d <..@430._2>
 8048c75:	ff 0c 24             	dec    DWORD PTR [esp]
 8048c78:	8f 04 24             	pop    DWORD PTR [esp]
 8048c7b:	eb ed                	jmp    8048c6a <..@430._1>

08048c7d <..@430._2>:
 8048c7d:	60                   	pusha  
 8048c7e:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8048c82:	89 e2                	mov    edx,esp
 8048c84:	83 c2 28             	add    edx,0x28
 8048c87:	89 cb                	mov    ebx,ecx
 8048c89:	90                   	nop
 8048c8a:	60                   	pusha  
 8048c8b:	89 d9                	mov    ecx,ebx

08048c8d <..@429._2>:
 8048c8d:	83 f9 01             	cmp    ecx,0x1
 8048c90:	7c 40                	jl     8048cd2 <..@429._1>
 8048c92:	b8 00 00 00 00       	mov    eax,0x0
 8048c97:	8b 02                	mov    eax,DWORD PTR [edx]
 8048c99:	c1 e0 08             	shl    eax,0x8
 8048c9c:	c1 e0 08             	shl    eax,0x8
 8048c9f:	c1 e8 08             	shr    eax,0x8
 8048ca2:	c1 e8 08             	shr    eax,0x8
 8048ca5:	e8 47 fa ff ff       	call   80486f1 <__best_buput_one>
 8048caa:	83 c2 02             	add    edx,0x2
 8048cad:	49                   	dec    ecx
 8048cae:	83 f9 01             	cmp    ecx,0x1
 8048cb1:	7c 1f                	jl     8048cd2 <..@429._1>
 8048cb3:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8048cb8:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048cbd:	b0 20                	mov    al,0x20
 8048cbf:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8048cc3:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8048cc8:	83 ec 02             	sub    esp,0x2
 8048ccb:	e8 fe 00 00 00       	call   8048dce <__best_cput+0x2>
 8048cd0:	eb bb                	jmp    8048c8d <..@429._2>

08048cd2 <..@429._1>:
 8048cd2:	61                   	popa   
 8048cd3:	89 c8                	mov    eax,ecx
 8048cd5:	bb 02 00 00 00       	mov    ebx,0x2
 8048cda:	f7 e3                	mul    ebx
 8048cdc:	89 e3                	mov    ebx,esp
 8048cde:	89 de                	mov    esi,ebx
 8048ce0:	89 df                	mov    edi,ebx
 8048ce2:	01 c7                	add    edi,eax
 8048ce4:	b9 28 00 00 00       	mov    ecx,0x28
 8048ce9:	01 cf                	add    edi,ecx
 8048ceb:	01 ce                	add    esi,ecx
 8048ced:	4f                   	dec    edi
 8048cee:	4e                   	dec    esi
 8048cef:	fd                   	std    
 8048cf0:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8048cf2:	fc                   	cld    
 8048cf3:	01 c4                	add    esp,eax
 8048cf5:	61                   	popa   
 8048cf6:	83 c4 04             	add    esp,0x4
 8048cf9:	c3                   	ret    

08048cfa <__best_bsput>:
 8048cfa:	6a 00                	push   0x0
 8048cfc:	6a 00                	push   0x0
 8048cfe:	6a 00                	push   0x0
 8048d00:	6a 00                	push   0x0
 8048d02:	6a 00                	push   0x0
 8048d04:	6a 00                	push   0x0
 8048d06:	6a 00                	push   0x0
 8048d08:	6a 00                	push   0x0
 8048d0a:	6a 00                	push   0x0
 8048d0c:	6a 00                	push   0x0
 8048d0e:	6a 00                	push   0x0
 8048d10:	6a 00                	push   0x0
 8048d12:	6a 00                	push   0x0
 8048d14:	6a 00                	push   0x0
 8048d16:	6a 00                	push   0x0
 8048d18:	6a 00                	push   0x0
 8048d1a:	6a 00                	push   0x0
 8048d1c:	6a 00                	push   0x0
 8048d1e:	6a 00                	push   0x0
 8048d20:	6a 00                	push   0x0
 8048d22:	6a 00                	push   0x0
 8048d24:	6a 00                	push   0x0
 8048d26:	6a 00                	push   0x0
 8048d28:	6a 00                	push   0x0
 8048d2a:	6a 00                	push   0x0
 8048d2c:	6a 00                	push   0x0
 8048d2e:	6a 00                	push   0x0
 8048d30:	6a 00                	push   0x0
 8048d32:	6a 00                	push   0x0
 8048d34:	6a 00                	push   0x0
 8048d36:	6a 00                	push   0x0
 8048d38:	6a 00                	push   0x0
 8048d3a:	6a 20                	push   0x20

08048d3c <..@436._1>:
 8048d3c:	bd 00 00 00 00       	mov    ebp,0x0
 8048d41:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 8048d45:	75 08                	jne    8048d4f <..@436._2>
 8048d47:	ff 0c 24             	dec    DWORD PTR [esp]
 8048d4a:	8f 04 24             	pop    DWORD PTR [esp]
 8048d4d:	eb ed                	jmp    8048d3c <..@436._1>

08048d4f <..@436._2>:
 8048d4f:	60                   	pusha  
 8048d50:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8048d54:	89 e2                	mov    edx,esp
 8048d56:	83 c2 28             	add    edx,0x28
 8048d59:	89 cb                	mov    ebx,ecx
 8048d5b:	90                   	nop
 8048d5c:	60                   	pusha  
 8048d5d:	89 d9                	mov    ecx,ebx

08048d5f <..@435._2>:
 8048d5f:	83 f9 01             	cmp    ecx,0x1
 8048d62:	7c 40                	jl     8048da4 <..@435._1>
 8048d64:	b8 00 00 00 00       	mov    eax,0x0
 8048d69:	8b 02                	mov    eax,DWORD PTR [edx]
 8048d6b:	c1 e0 08             	shl    eax,0x8
 8048d6e:	c1 e0 08             	shl    eax,0x8
 8048d71:	c1 e8 08             	shr    eax,0x8
 8048d74:	c1 e8 08             	shr    eax,0x8
 8048d77:	e8 7b f9 ff ff       	call   80486f7 <__best_bsput_one>
 8048d7c:	83 c2 02             	add    edx,0x2
 8048d7f:	49                   	dec    ecx
 8048d80:	83 f9 01             	cmp    ecx,0x1
 8048d83:	7c 1f                	jl     8048da4 <..@435._1>
 8048d85:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8048d8a:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048d8f:	b0 20                	mov    al,0x20
 8048d91:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8048d95:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8048d9a:	83 ec 02             	sub    esp,0x2
 8048d9d:	e8 2c 00 00 00       	call   8048dce <__best_cput+0x2>
 8048da2:	eb bb                	jmp    8048d5f <..@435._2>

08048da4 <..@435._1>:
 8048da4:	61                   	popa   
 8048da5:	89 c8                	mov    eax,ecx
 8048da7:	bb 02 00 00 00       	mov    ebx,0x2
 8048dac:	f7 e3                	mul    ebx
 8048dae:	89 e3                	mov    ebx,esp
 8048db0:	89 de                	mov    esi,ebx
 8048db2:	89 df                	mov    edi,ebx
 8048db4:	01 c7                	add    edi,eax
 8048db6:	b9 28 00 00 00       	mov    ecx,0x28
 8048dbb:	01 cf                	add    edi,ecx
 8048dbd:	01 ce                	add    esi,ecx
 8048dbf:	4f                   	dec    edi
 8048dc0:	4e                   	dec    esi
 8048dc1:	fd                   	std    
 8048dc2:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8048dc4:	fc                   	cld    
 8048dc5:	01 c4                	add    esp,eax
 8048dc7:	61                   	popa   
 8048dc8:	83 c4 04             	add    esp,0x4
 8048dcb:	c3                   	ret    

08048dcc <__best_cput>:
 8048dcc:	6a 00                	push   0x0
 8048dce:	6a 00                	push   0x0
 8048dd0:	6a 00                	push   0x0
 8048dd2:	6a 00                	push   0x0
 8048dd4:	6a 00                	push   0x0
 8048dd6:	6a 00                	push   0x0
 8048dd8:	6a 00                	push   0x0
 8048dda:	6a 00                	push   0x0
 8048ddc:	6a 00                	push   0x0
 8048dde:	6a 00                	push   0x0
 8048de0:	6a 00                	push   0x0
 8048de2:	6a 00                	push   0x0
 8048de4:	6a 00                	push   0x0
 8048de6:	6a 00                	push   0x0
 8048de8:	6a 00                	push   0x0
 8048dea:	6a 00                	push   0x0
 8048dec:	6a 00                	push   0x0
 8048dee:	6a 00                	push   0x0
 8048df0:	6a 00                	push   0x0
 8048df2:	6a 00                	push   0x0
 8048df4:	6a 00                	push   0x0
 8048df6:	6a 00                	push   0x0
 8048df8:	6a 00                	push   0x0
 8048dfa:	6a 00                	push   0x0
 8048dfc:	6a 00                	push   0x0
 8048dfe:	6a 00                	push   0x0
 8048e00:	6a 00                	push   0x0
 8048e02:	6a 00                	push   0x0
 8048e04:	6a 00                	push   0x0
 8048e06:	6a 00                	push   0x0
 8048e08:	6a 00                	push   0x0
 8048e0a:	6a 00                	push   0x0
 8048e0c:	6a 20                	push   0x20

08048e0e <..@442._1>:
 8048e0e:	bd 00 00 00 00       	mov    ebp,0x0
 8048e13:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 8048e17:	75 08                	jne    8048e21 <..@442._2>
 8048e19:	ff 0c 24             	dec    DWORD PTR [esp]
 8048e1c:	8f 04 24             	pop    DWORD PTR [esp]
 8048e1f:	eb ed                	jmp    8048e0e <..@442._1>

08048e21 <..@442._2>:
 8048e21:	60                   	pusha  
 8048e22:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8048e26:	89 e2                	mov    edx,esp
 8048e28:	83 c2 28             	add    edx,0x28
 8048e2b:	89 cb                	mov    ebx,ecx
 8048e2d:	90                   	nop
 8048e2e:	60                   	pusha  
 8048e2f:	89 d9                	mov    ecx,ebx

08048e31 <..@441._2>:
 8048e31:	83 f9 01             	cmp    ecx,0x1
 8048e34:	7c 40                	jl     8048e76 <..@441._1>
 8048e36:	b8 00 00 00 00       	mov    eax,0x0
 8048e3b:	8b 02                	mov    eax,DWORD PTR [edx]
 8048e3d:	c1 e0 08             	shl    eax,0x8
 8048e40:	c1 e0 08             	shl    eax,0x8
 8048e43:	c1 e8 08             	shr    eax,0x8
 8048e46:	c1 e8 08             	shr    eax,0x8
 8048e49:	e8 e5 f8 ff ff       	call   8048733 <__best_cput_one>
 8048e4e:	83 c2 02             	add    edx,0x2
 8048e51:	49                   	dec    ecx
 8048e52:	83 f9 01             	cmp    ecx,0x1
 8048e55:	7c 1f                	jl     8048e76 <..@441._1>
 8048e57:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8048e5c:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048e61:	b0 20                	mov    al,0x20
 8048e63:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8048e67:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8048e6c:	83 ec 02             	sub    esp,0x2
 8048e6f:	e8 5a ff ff ff       	call   8048dce <__best_cput+0x2>
 8048e74:	eb bb                	jmp    8048e31 <..@441._2>

08048e76 <..@441._1>:
 8048e76:	61                   	popa   
 8048e77:	89 c8                	mov    eax,ecx
 8048e79:	bb 02 00 00 00       	mov    ebx,0x2
 8048e7e:	f7 e3                	mul    ebx
 8048e80:	89 e3                	mov    ebx,esp
 8048e82:	89 de                	mov    esi,ebx
 8048e84:	89 df                	mov    edi,ebx
 8048e86:	01 c7                	add    edi,eax
 8048e88:	b9 28 00 00 00       	mov    ecx,0x28
 8048e8d:	01 cf                	add    edi,ecx
 8048e8f:	01 ce                	add    esi,ecx
 8048e91:	4f                   	dec    edi
 8048e92:	4e                   	dec    esi
 8048e93:	fd                   	std    
 8048e94:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8048e96:	fc                   	cld    
 8048e97:	01 c4                	add    esp,eax
 8048e99:	61                   	popa   
 8048e9a:	83 c4 04             	add    esp,0x4
 8048e9d:	c3                   	ret    

08048e9e <__best_sput>:
 8048e9e:	6a 00                	push   0x0
 8048ea0:	6a 00                	push   0x0
 8048ea2:	6a 00                	push   0x0
 8048ea4:	6a 00                	push   0x0
 8048ea6:	6a 00                	push   0x0
 8048ea8:	6a 00                	push   0x0
 8048eaa:	6a 00                	push   0x0
 8048eac:	6a 00                	push   0x0
 8048eae:	6a 00                	push   0x0
 8048eb0:	6a 00                	push   0x0
 8048eb2:	6a 00                	push   0x0
 8048eb4:	6a 00                	push   0x0
 8048eb6:	6a 00                	push   0x0
 8048eb8:	6a 00                	push   0x0
 8048eba:	6a 00                	push   0x0
 8048ebc:	6a 00                	push   0x0
 8048ebe:	6a 00                	push   0x0
 8048ec0:	6a 00                	push   0x0
 8048ec2:	6a 00                	push   0x0
 8048ec4:	6a 00                	push   0x0
 8048ec6:	6a 00                	push   0x0
 8048ec8:	6a 00                	push   0x0
 8048eca:	6a 00                	push   0x0
 8048ecc:	6a 00                	push   0x0
 8048ece:	6a 00                	push   0x0
 8048ed0:	6a 00                	push   0x0
 8048ed2:	6a 00                	push   0x0
 8048ed4:	6a 00                	push   0x0
 8048ed6:	6a 00                	push   0x0
 8048ed8:	6a 00                	push   0x0
 8048eda:	6a 00                	push   0x0
 8048edc:	6a 00                	push   0x0
 8048ede:	6a 20                	push   0x20

08048ee0 <..@448._1>:
 8048ee0:	bd 00 00 00 00       	mov    ebp,0x0
 8048ee5:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 8048ee9:	75 08                	jne    8048ef3 <..@448._2>
 8048eeb:	ff 0c 24             	dec    DWORD PTR [esp]
 8048eee:	8f 04 24             	pop    DWORD PTR [esp]
 8048ef1:	eb ed                	jmp    8048ee0 <..@448._1>

08048ef3 <..@448._2>:
 8048ef3:	60                   	pusha  
 8048ef4:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8048ef8:	89 e2                	mov    edx,esp
 8048efa:	83 c2 28             	add    edx,0x28
 8048efd:	89 cb                	mov    ebx,ecx
 8048eff:	8b 54 24 24          	mov    edx,DWORD PTR [esp+0x24]
 8048f03:	01 4c 24 24          	add    DWORD PTR [esp+0x24],ecx
 8048f07:	b9 00 00 00 00       	mov    ecx,0x0
 8048f0c:	60                   	pusha  
 8048f0d:	89 d9                	mov    ecx,ebx

08048f0f <..@447._2>:
 8048f0f:	83 f9 01             	cmp    ecx,0x1
 8048f12:	7c 29                	jl     8048f3d <..@447._1>
 8048f14:	b8 00 00 00 00       	mov    eax,0x0
 8048f19:	8b 02                	mov    eax,DWORD PTR [edx]
 8048f1b:	c1 e0 08             	shl    eax,0x8
 8048f1e:	c1 e0 08             	shl    eax,0x8
 8048f21:	c1 e0 08             	shl    eax,0x8
 8048f24:	c1 e8 08             	shr    eax,0x8
 8048f27:	c1 e8 08             	shr    eax,0x8
 8048f2a:	c1 e8 08             	shr    eax,0x8
 8048f2d:	e8 1c f8 ff ff       	call   804874e <__best_sput_one>
 8048f32:	83 c2 01             	add    edx,0x1
 8048f35:	49                   	dec    ecx
 8048f36:	83 f9 01             	cmp    ecx,0x1
 8048f39:	7c 02                	jl     8048f3d <..@447._1>
 8048f3b:	eb d2                	jmp    8048f0f <..@447._2>

08048f3d <..@447._1>:
 8048f3d:	61                   	popa   
 8048f3e:	89 c8                	mov    eax,ecx
 8048f40:	bb 01 00 00 00       	mov    ebx,0x1
 8048f45:	f7 e3                	mul    ebx
 8048f47:	89 e3                	mov    ebx,esp
 8048f49:	89 de                	mov    esi,ebx
 8048f4b:	89 df                	mov    edi,ebx
 8048f4d:	01 c7                	add    edi,eax
 8048f4f:	b9 28 00 00 00       	mov    ecx,0x28
 8048f54:	01 cf                	add    edi,ecx
 8048f56:	01 ce                	add    esi,ecx
 8048f58:	4f                   	dec    edi
 8048f59:	4e                   	dec    esi
 8048f5a:	fd                   	std    
 8048f5b:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8048f5d:	fc                   	cld    
 8048f5e:	01 c4                	add    esp,eax
 8048f60:	61                   	popa   
 8048f61:	83 c4 04             	add    esp,0x4
 8048f64:	c3                   	ret    

08048f65 <__best_quwrite>:
 8048f65:	6a 00                	push   0x0
 8048f67:	6a 00                	push   0x0
 8048f69:	6a 00                	push   0x0
 8048f6b:	6a 00                	push   0x0
 8048f6d:	6a 00                	push   0x0
 8048f6f:	6a 00                	push   0x0
 8048f71:	6a 00                	push   0x0
 8048f73:	6a 00                	push   0x0
 8048f75:	6a 00                	push   0x0
 8048f77:	6a 00                	push   0x0
 8048f79:	6a 00                	push   0x0
 8048f7b:	6a 00                	push   0x0
 8048f7d:	6a 00                	push   0x0
 8048f7f:	6a 00                	push   0x0
 8048f81:	6a 00                	push   0x0
 8048f83:	6a 00                	push   0x0
 8048f85:	6a 00                	push   0x0
 8048f87:	6a 00                	push   0x0
 8048f89:	6a 00                	push   0x0
 8048f8b:	6a 00                	push   0x0
 8048f8d:	6a 00                	push   0x0
 8048f8f:	6a 00                	push   0x0
 8048f91:	6a 00                	push   0x0
 8048f93:	6a 00                	push   0x0
 8048f95:	6a 00                	push   0x0
 8048f97:	6a 00                	push   0x0
 8048f99:	6a 00                	push   0x0
 8048f9b:	6a 00                	push   0x0
 8048f9d:	6a 00                	push   0x0
 8048f9f:	6a 00                	push   0x0
 8048fa1:	6a 00                	push   0x0
 8048fa3:	6a 00                	push   0x0
 8048fa5:	6a 20                	push   0x20

08048fa7 <..@451._1>:
 8048fa7:	bd 00 00 00 00       	mov    ebp,0x0
 8048fac:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 8048fb0:	75 08                	jne    8048fba <..@451._2>
 8048fb2:	ff 0c 24             	dec    DWORD PTR [esp]
 8048fb5:	8f 04 24             	pop    DWORD PTR [esp]
 8048fb8:	eb ed                	jmp    8048fa7 <..@451._1>

08048fba <..@451._2>:
 8048fba:	60                   	pusha  
 8048fbb:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8048fbf:	89 e2                	mov    edx,esp
 8048fc1:	83 c2 28             	add    edx,0x28
 8048fc4:	89 cb                	mov    ebx,ecx
 8048fc6:	90                   	nop
 8048fc7:	60                   	pusha  
 8048fc8:	89 d9                	mov    ecx,ebx

08048fca <..@450._2>:
 8048fca:	83 f9 01             	cmp    ecx,0x1
 8048fcd:	7c 34                	jl     8049003 <..@450._1>
 8048fcf:	b8 00 00 00 00       	mov    eax,0x0
 8048fd4:	8b 02                	mov    eax,DWORD PTR [edx]
 8048fd6:	e8 7a f6 ff ff       	call   8048655 <__best_quput_one>
 8048fdb:	83 c2 08             	add    edx,0x8
 8048fde:	49                   	dec    ecx
 8048fdf:	83 f9 01             	cmp    ecx,0x1
 8048fe2:	7c 1f                	jl     8049003 <..@450._1>
 8048fe4:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8048fe9:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8048fee:	b0 20                	mov    al,0x20
 8048ff0:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8048ff4:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8048ff9:	83 ec 02             	sub    esp,0x2
 8048ffc:	e8 cd fd ff ff       	call   8048dce <__best_cput+0x2>
 8049001:	eb c7                	jmp    8048fca <..@450._2>

08049003 <..@450._1>:
 8049003:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8049008:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 804900d:	b0 20                	mov    al,0x20
 804900f:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8049013:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8049018:	83 ec 02             	sub    esp,0x2
 804901b:	e8 ae fd ff ff       	call   8048dce <__best_cput+0x2>
 8049020:	61                   	popa   
 8049021:	89 c8                	mov    eax,ecx
 8049023:	bb 08 00 00 00       	mov    ebx,0x8
 8049028:	f7 e3                	mul    ebx
 804902a:	89 e3                	mov    ebx,esp
 804902c:	89 de                	mov    esi,ebx
 804902e:	89 df                	mov    edi,ebx
 8049030:	01 c7                	add    edi,eax
 8049032:	b9 28 00 00 00       	mov    ecx,0x28
 8049037:	01 cf                	add    edi,ecx
 8049039:	01 ce                	add    esi,ecx
 804903b:	4f                   	dec    edi
 804903c:	4e                   	dec    esi
 804903d:	fd                   	std    
 804903e:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8049040:	fc                   	cld    
 8049041:	01 c4                	add    esp,eax
 8049043:	61                   	popa   
 8049044:	83 c4 04             	add    esp,0x4
 8049047:	c3                   	ret    

08049048 <__best_qswrite>:
 8049048:	6a 00                	push   0x0
 804904a:	6a 00                	push   0x0
 804904c:	6a 00                	push   0x0
 804904e:	6a 00                	push   0x0
 8049050:	6a 00                	push   0x0
 8049052:	6a 00                	push   0x0
 8049054:	6a 00                	push   0x0
 8049056:	6a 00                	push   0x0
 8049058:	6a 00                	push   0x0
 804905a:	6a 00                	push   0x0
 804905c:	6a 00                	push   0x0
 804905e:	6a 00                	push   0x0
 8049060:	6a 00                	push   0x0
 8049062:	6a 00                	push   0x0
 8049064:	6a 00                	push   0x0
 8049066:	6a 00                	push   0x0
 8049068:	6a 00                	push   0x0
 804906a:	6a 00                	push   0x0
 804906c:	6a 00                	push   0x0
 804906e:	6a 00                	push   0x0
 8049070:	6a 00                	push   0x0
 8049072:	6a 00                	push   0x0
 8049074:	6a 00                	push   0x0
 8049076:	6a 00                	push   0x0
 8049078:	6a 00                	push   0x0
 804907a:	6a 00                	push   0x0
 804907c:	6a 00                	push   0x0
 804907e:	6a 00                	push   0x0
 8049080:	6a 00                	push   0x0
 8049082:	6a 00                	push   0x0
 8049084:	6a 00                	push   0x0
 8049086:	6a 00                	push   0x0
 8049088:	6a 20                	push   0x20

0804908a <..@461._1>:
 804908a:	bd 00 00 00 00       	mov    ebp,0x0
 804908f:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 8049093:	75 08                	jne    804909d <..@461._2>
 8049095:	ff 0c 24             	dec    DWORD PTR [esp]
 8049098:	8f 04 24             	pop    DWORD PTR [esp]
 804909b:	eb ed                	jmp    804908a <..@461._1>

0804909d <..@461._2>:
 804909d:	60                   	pusha  
 804909e:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 80490a2:	89 e2                	mov    edx,esp
 80490a4:	83 c2 28             	add    edx,0x28
 80490a7:	89 cb                	mov    ebx,ecx
 80490a9:	90                   	nop
 80490aa:	60                   	pusha  
 80490ab:	89 d9                	mov    ecx,ebx

080490ad <..@460._2>:
 80490ad:	83 f9 01             	cmp    ecx,0x1
 80490b0:	7c 34                	jl     80490e6 <..@460._1>
 80490b2:	b8 00 00 00 00       	mov    eax,0x0
 80490b7:	8b 02                	mov    eax,DWORD PTR [edx]
 80490b9:	e8 9d f5 ff ff       	call   804865b <__best_qsput_one>
 80490be:	83 c2 08             	add    edx,0x8
 80490c1:	49                   	dec    ecx
 80490c2:	83 f9 01             	cmp    ecx,0x1
 80490c5:	7c 1f                	jl     80490e6 <..@460._1>
 80490c7:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80490cc:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 80490d1:	b0 20                	mov    al,0x20
 80490d3:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80490d7:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 80490dc:	83 ec 02             	sub    esp,0x2
 80490df:	e8 ea fc ff ff       	call   8048dce <__best_cput+0x2>
 80490e4:	eb c7                	jmp    80490ad <..@460._2>

080490e6 <..@460._1>:
 80490e6:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80490eb:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 80490f0:	b0 20                	mov    al,0x20
 80490f2:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80490f6:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 80490fb:	83 ec 02             	sub    esp,0x2
 80490fe:	e8 cb fc ff ff       	call   8048dce <__best_cput+0x2>
 8049103:	61                   	popa   
 8049104:	89 c8                	mov    eax,ecx
 8049106:	bb 08 00 00 00       	mov    ebx,0x8
 804910b:	f7 e3                	mul    ebx
 804910d:	89 e3                	mov    ebx,esp
 804910f:	89 de                	mov    esi,ebx
 8049111:	89 df                	mov    edi,ebx
 8049113:	01 c7                	add    edi,eax
 8049115:	b9 28 00 00 00       	mov    ecx,0x28
 804911a:	01 cf                	add    edi,ecx
 804911c:	01 ce                	add    esi,ecx
 804911e:	4f                   	dec    edi
 804911f:	4e                   	dec    esi
 8049120:	fd                   	std    
 8049121:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8049123:	fc                   	cld    
 8049124:	01 c4                	add    esp,eax
 8049126:	61                   	popa   
 8049127:	83 c4 04             	add    esp,0x4
 804912a:	c3                   	ret    

0804912b <__best_duwrite>:
 804912b:	6a 00                	push   0x0
 804912d:	6a 00                	push   0x0
 804912f:	6a 00                	push   0x0
 8049131:	6a 00                	push   0x0
 8049133:	6a 00                	push   0x0
 8049135:	6a 00                	push   0x0
 8049137:	6a 00                	push   0x0
 8049139:	6a 00                	push   0x0
 804913b:	6a 00                	push   0x0
 804913d:	6a 00                	push   0x0
 804913f:	6a 00                	push   0x0
 8049141:	6a 00                	push   0x0
 8049143:	6a 00                	push   0x0
 8049145:	6a 00                	push   0x0
 8049147:	6a 00                	push   0x0
 8049149:	6a 00                	push   0x0
 804914b:	6a 00                	push   0x0
 804914d:	6a 00                	push   0x0
 804914f:	6a 00                	push   0x0
 8049151:	6a 00                	push   0x0
 8049153:	6a 00                	push   0x0
 8049155:	6a 00                	push   0x0
 8049157:	6a 00                	push   0x0
 8049159:	6a 00                	push   0x0
 804915b:	6a 00                	push   0x0
 804915d:	6a 00                	push   0x0
 804915f:	6a 00                	push   0x0
 8049161:	6a 00                	push   0x0
 8049163:	6a 00                	push   0x0
 8049165:	6a 00                	push   0x0
 8049167:	6a 00                	push   0x0
 8049169:	6a 00                	push   0x0
 804916b:	6a 20                	push   0x20

0804916d <..@471._1>:
 804916d:	bd 00 00 00 00       	mov    ebp,0x0
 8049172:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 8049176:	75 08                	jne    8049180 <..@471._2>
 8049178:	ff 0c 24             	dec    DWORD PTR [esp]
 804917b:	8f 04 24             	pop    DWORD PTR [esp]
 804917e:	eb ed                	jmp    804916d <..@471._1>

08049180 <..@471._2>:
 8049180:	60                   	pusha  
 8049181:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8049185:	89 e2                	mov    edx,esp
 8049187:	83 c2 28             	add    edx,0x28
 804918a:	89 cb                	mov    ebx,ecx
 804918c:	90                   	nop
 804918d:	60                   	pusha  
 804918e:	89 d9                	mov    ecx,ebx

08049190 <..@470._2>:
 8049190:	83 f9 01             	cmp    ecx,0x1
 8049193:	7c 34                	jl     80491c9 <..@470._1>
 8049195:	b8 00 00 00 00       	mov    eax,0x0
 804919a:	8b 02                	mov    eax,DWORD PTR [edx]
 804919c:	e8 e4 f4 ff ff       	call   8048685 <__best_duput_one>
 80491a1:	83 c2 04             	add    edx,0x4
 80491a4:	49                   	dec    ecx
 80491a5:	83 f9 01             	cmp    ecx,0x1
 80491a8:	7c 1f                	jl     80491c9 <..@470._1>
 80491aa:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80491af:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 80491b4:	b0 20                	mov    al,0x20
 80491b6:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80491ba:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 80491bf:	83 ec 02             	sub    esp,0x2
 80491c2:	e8 07 fc ff ff       	call   8048dce <__best_cput+0x2>
 80491c7:	eb c7                	jmp    8049190 <..@470._2>

080491c9 <..@470._1>:
 80491c9:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80491ce:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 80491d3:	b0 20                	mov    al,0x20
 80491d5:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80491d9:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 80491de:	83 ec 02             	sub    esp,0x2
 80491e1:	e8 e8 fb ff ff       	call   8048dce <__best_cput+0x2>
 80491e6:	61                   	popa   
 80491e7:	89 c8                	mov    eax,ecx
 80491e9:	bb 04 00 00 00       	mov    ebx,0x4
 80491ee:	f7 e3                	mul    ebx
 80491f0:	89 e3                	mov    ebx,esp
 80491f2:	89 de                	mov    esi,ebx
 80491f4:	89 df                	mov    edi,ebx
 80491f6:	01 c7                	add    edi,eax
 80491f8:	b9 28 00 00 00       	mov    ecx,0x28
 80491fd:	01 cf                	add    edi,ecx
 80491ff:	01 ce                	add    esi,ecx
 8049201:	4f                   	dec    edi
 8049202:	4e                   	dec    esi
 8049203:	fd                   	std    
 8049204:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8049206:	fc                   	cld    
 8049207:	01 c4                	add    esp,eax
 8049209:	61                   	popa   
 804920a:	83 c4 04             	add    esp,0x4
 804920d:	c3                   	ret    

0804920e <__best_dswrite>:
 804920e:	6a 00                	push   0x0
 8049210:	6a 00                	push   0x0
 8049212:	6a 00                	push   0x0
 8049214:	6a 00                	push   0x0
 8049216:	6a 00                	push   0x0
 8049218:	6a 00                	push   0x0
 804921a:	6a 00                	push   0x0
 804921c:	6a 00                	push   0x0
 804921e:	6a 00                	push   0x0
 8049220:	6a 00                	push   0x0
 8049222:	6a 00                	push   0x0
 8049224:	6a 00                	push   0x0
 8049226:	6a 00                	push   0x0
 8049228:	6a 00                	push   0x0
 804922a:	6a 00                	push   0x0
 804922c:	6a 00                	push   0x0
 804922e:	6a 00                	push   0x0
 8049230:	6a 00                	push   0x0
 8049232:	6a 00                	push   0x0
 8049234:	6a 00                	push   0x0
 8049236:	6a 00                	push   0x0
 8049238:	6a 00                	push   0x0
 804923a:	6a 00                	push   0x0
 804923c:	6a 00                	push   0x0
 804923e:	6a 00                	push   0x0
 8049240:	6a 00                	push   0x0
 8049242:	6a 00                	push   0x0
 8049244:	6a 00                	push   0x0
 8049246:	6a 00                	push   0x0
 8049248:	6a 00                	push   0x0
 804924a:	6a 00                	push   0x0
 804924c:	6a 00                	push   0x0
 804924e:	6a 20                	push   0x20

08049250 <..@481._1>:
 8049250:	bd 00 00 00 00       	mov    ebp,0x0
 8049255:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 8049259:	75 08                	jne    8049263 <..@481._2>
 804925b:	ff 0c 24             	dec    DWORD PTR [esp]
 804925e:	8f 04 24             	pop    DWORD PTR [esp]
 8049261:	eb ed                	jmp    8049250 <..@481._1>

08049263 <..@481._2>:
 8049263:	60                   	pusha  
 8049264:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8049268:	89 e2                	mov    edx,esp
 804926a:	83 c2 28             	add    edx,0x28
 804926d:	89 cb                	mov    ebx,ecx
 804926f:	90                   	nop
 8049270:	60                   	pusha  
 8049271:	89 d9                	mov    ecx,ebx

08049273 <..@480._2>:
 8049273:	83 f9 01             	cmp    ecx,0x1
 8049276:	7c 34                	jl     80492ac <..@480._1>
 8049278:	b8 00 00 00 00       	mov    eax,0x0
 804927d:	8b 02                	mov    eax,DWORD PTR [edx]
 804927f:	e8 07 f4 ff ff       	call   804868b <__best_dsput_one>
 8049284:	83 c2 04             	add    edx,0x4
 8049287:	49                   	dec    ecx
 8049288:	83 f9 01             	cmp    ecx,0x1
 804928b:	7c 1f                	jl     80492ac <..@480._1>
 804928d:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8049292:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8049297:	b0 20                	mov    al,0x20
 8049299:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804929d:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 80492a2:	83 ec 02             	sub    esp,0x2
 80492a5:	e8 24 fb ff ff       	call   8048dce <__best_cput+0x2>
 80492aa:	eb c7                	jmp    8049273 <..@480._2>

080492ac <..@480._1>:
 80492ac:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80492b1:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 80492b6:	b0 20                	mov    al,0x20
 80492b8:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80492bc:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 80492c1:	83 ec 02             	sub    esp,0x2
 80492c4:	e8 05 fb ff ff       	call   8048dce <__best_cput+0x2>
 80492c9:	61                   	popa   
 80492ca:	89 c8                	mov    eax,ecx
 80492cc:	bb 04 00 00 00       	mov    ebx,0x4
 80492d1:	f7 e3                	mul    ebx
 80492d3:	89 e3                	mov    ebx,esp
 80492d5:	89 de                	mov    esi,ebx
 80492d7:	89 df                	mov    edi,ebx
 80492d9:	01 c7                	add    edi,eax
 80492db:	b9 28 00 00 00       	mov    ecx,0x28
 80492e0:	01 cf                	add    edi,ecx
 80492e2:	01 ce                	add    esi,ecx
 80492e4:	4f                   	dec    edi
 80492e5:	4e                   	dec    esi
 80492e6:	fd                   	std    
 80492e7:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 80492e9:	fc                   	cld    
 80492ea:	01 c4                	add    esp,eax
 80492ec:	61                   	popa   
 80492ed:	83 c4 04             	add    esp,0x4
 80492f0:	c3                   	ret    

080492f1 <__best_wuwrite>:
 80492f1:	6a 00                	push   0x0
 80492f3:	6a 00                	push   0x0
 80492f5:	6a 00                	push   0x0
 80492f7:	6a 00                	push   0x0
 80492f9:	6a 00                	push   0x0
 80492fb:	6a 00                	push   0x0
 80492fd:	6a 00                	push   0x0
 80492ff:	6a 00                	push   0x0
 8049301:	6a 00                	push   0x0
 8049303:	6a 00                	push   0x0
 8049305:	6a 00                	push   0x0
 8049307:	6a 00                	push   0x0
 8049309:	6a 00                	push   0x0
 804930b:	6a 00                	push   0x0
 804930d:	6a 00                	push   0x0
 804930f:	6a 00                	push   0x0
 8049311:	6a 00                	push   0x0
 8049313:	6a 00                	push   0x0
 8049315:	6a 00                	push   0x0
 8049317:	6a 00                	push   0x0
 8049319:	6a 00                	push   0x0
 804931b:	6a 00                	push   0x0
 804931d:	6a 00                	push   0x0
 804931f:	6a 00                	push   0x0
 8049321:	6a 00                	push   0x0
 8049323:	6a 00                	push   0x0
 8049325:	6a 00                	push   0x0
 8049327:	6a 00                	push   0x0
 8049329:	6a 00                	push   0x0
 804932b:	6a 00                	push   0x0
 804932d:	6a 00                	push   0x0
 804932f:	6a 00                	push   0x0
 8049331:	6a 20                	push   0x20

08049333 <..@491._1>:
 8049333:	bd 00 00 00 00       	mov    ebp,0x0
 8049338:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 804933c:	75 08                	jne    8049346 <..@491._2>
 804933e:	ff 0c 24             	dec    DWORD PTR [esp]
 8049341:	8f 04 24             	pop    DWORD PTR [esp]
 8049344:	eb ed                	jmp    8049333 <..@491._1>

08049346 <..@491._2>:
 8049346:	60                   	pusha  
 8049347:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 804934b:	89 e2                	mov    edx,esp
 804934d:	83 c2 28             	add    edx,0x28
 8049350:	89 cb                	mov    ebx,ecx
 8049352:	90                   	nop
 8049353:	60                   	pusha  
 8049354:	89 d9                	mov    ecx,ebx

08049356 <..@490._2>:
 8049356:	83 f9 01             	cmp    ecx,0x1
 8049359:	7c 40                	jl     804939b <..@490._1>
 804935b:	b8 00 00 00 00       	mov    eax,0x0
 8049360:	8b 02                	mov    eax,DWORD PTR [edx]
 8049362:	c1 e0 08             	shl    eax,0x8
 8049365:	c1 e0 08             	shl    eax,0x8
 8049368:	c1 e8 08             	shr    eax,0x8
 804936b:	c1 e8 08             	shr    eax,0x8
 804936e:	e8 42 f3 ff ff       	call   80486b5 <__best_wuput_one>
 8049373:	83 c2 02             	add    edx,0x2
 8049376:	49                   	dec    ecx
 8049377:	83 f9 01             	cmp    ecx,0x1
 804937a:	7c 1f                	jl     804939b <..@490._1>
 804937c:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8049381:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8049386:	b0 20                	mov    al,0x20
 8049388:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804938c:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8049391:	83 ec 02             	sub    esp,0x2
 8049394:	e8 35 fa ff ff       	call   8048dce <__best_cput+0x2>
 8049399:	eb bb                	jmp    8049356 <..@490._2>

0804939b <..@490._1>:
 804939b:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80493a0:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 80493a5:	b0 20                	mov    al,0x20
 80493a7:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80493ab:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 80493b0:	83 ec 02             	sub    esp,0x2
 80493b3:	e8 16 fa ff ff       	call   8048dce <__best_cput+0x2>
 80493b8:	61                   	popa   
 80493b9:	89 c8                	mov    eax,ecx
 80493bb:	bb 02 00 00 00       	mov    ebx,0x2
 80493c0:	f7 e3                	mul    ebx
 80493c2:	89 e3                	mov    ebx,esp
 80493c4:	89 de                	mov    esi,ebx
 80493c6:	89 df                	mov    edi,ebx
 80493c8:	01 c7                	add    edi,eax
 80493ca:	b9 28 00 00 00       	mov    ecx,0x28
 80493cf:	01 cf                	add    edi,ecx
 80493d1:	01 ce                	add    esi,ecx
 80493d3:	4f                   	dec    edi
 80493d4:	4e                   	dec    esi
 80493d5:	fd                   	std    
 80493d6:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 80493d8:	fc                   	cld    
 80493d9:	01 c4                	add    esp,eax
 80493db:	61                   	popa   
 80493dc:	83 c4 04             	add    esp,0x4
 80493df:	c3                   	ret    

080493e0 <__best_wswrite>:
 80493e0:	6a 00                	push   0x0
 80493e2:	6a 00                	push   0x0
 80493e4:	6a 00                	push   0x0
 80493e6:	6a 00                	push   0x0
 80493e8:	6a 00                	push   0x0
 80493ea:	6a 00                	push   0x0
 80493ec:	6a 00                	push   0x0
 80493ee:	6a 00                	push   0x0
 80493f0:	6a 00                	push   0x0
 80493f2:	6a 00                	push   0x0
 80493f4:	6a 00                	push   0x0
 80493f6:	6a 00                	push   0x0
 80493f8:	6a 00                	push   0x0
 80493fa:	6a 00                	push   0x0
 80493fc:	6a 00                	push   0x0
 80493fe:	6a 00                	push   0x0
 8049400:	6a 00                	push   0x0
 8049402:	6a 00                	push   0x0
 8049404:	6a 00                	push   0x0
 8049406:	6a 00                	push   0x0
 8049408:	6a 00                	push   0x0
 804940a:	6a 00                	push   0x0
 804940c:	6a 00                	push   0x0
 804940e:	6a 00                	push   0x0
 8049410:	6a 00                	push   0x0
 8049412:	6a 00                	push   0x0
 8049414:	6a 00                	push   0x0
 8049416:	6a 00                	push   0x0
 8049418:	6a 00                	push   0x0
 804941a:	6a 00                	push   0x0
 804941c:	6a 00                	push   0x0
 804941e:	6a 00                	push   0x0
 8049420:	6a 20                	push   0x20

08049422 <..@501._1>:
 8049422:	bd 00 00 00 00       	mov    ebp,0x0
 8049427:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 804942b:	75 08                	jne    8049435 <..@501._2>
 804942d:	ff 0c 24             	dec    DWORD PTR [esp]
 8049430:	8f 04 24             	pop    DWORD PTR [esp]
 8049433:	eb ed                	jmp    8049422 <..@501._1>

08049435 <..@501._2>:
 8049435:	60                   	pusha  
 8049436:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 804943a:	89 e2                	mov    edx,esp
 804943c:	83 c2 28             	add    edx,0x28
 804943f:	89 cb                	mov    ebx,ecx
 8049441:	90                   	nop
 8049442:	60                   	pusha  
 8049443:	89 d9                	mov    ecx,ebx

08049445 <..@500._2>:
 8049445:	83 f9 01             	cmp    ecx,0x1
 8049448:	7c 40                	jl     804948a <..@500._1>
 804944a:	b8 00 00 00 00       	mov    eax,0x0
 804944f:	8b 02                	mov    eax,DWORD PTR [edx]
 8049451:	c1 e0 08             	shl    eax,0x8
 8049454:	c1 e0 08             	shl    eax,0x8
 8049457:	c1 e8 08             	shr    eax,0x8
 804945a:	c1 e8 08             	shr    eax,0x8
 804945d:	e8 59 f2 ff ff       	call   80486bb <__best_wsput_one>
 8049462:	83 c2 02             	add    edx,0x2
 8049465:	49                   	dec    ecx
 8049466:	83 f9 01             	cmp    ecx,0x1
 8049469:	7c 1f                	jl     804948a <..@500._1>
 804946b:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8049470:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8049475:	b0 20                	mov    al,0x20
 8049477:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804947b:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8049480:	83 ec 02             	sub    esp,0x2
 8049483:	e8 46 f9 ff ff       	call   8048dce <__best_cput+0x2>
 8049488:	eb bb                	jmp    8049445 <..@500._2>

0804948a <..@500._1>:
 804948a:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804948f:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8049494:	b0 20                	mov    al,0x20
 8049496:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804949a:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 804949f:	83 ec 02             	sub    esp,0x2
 80494a2:	e8 27 f9 ff ff       	call   8048dce <__best_cput+0x2>
 80494a7:	61                   	popa   
 80494a8:	89 c8                	mov    eax,ecx
 80494aa:	bb 02 00 00 00       	mov    ebx,0x2
 80494af:	f7 e3                	mul    ebx
 80494b1:	89 e3                	mov    ebx,esp
 80494b3:	89 de                	mov    esi,ebx
 80494b5:	89 df                	mov    edi,ebx
 80494b7:	01 c7                	add    edi,eax
 80494b9:	b9 28 00 00 00       	mov    ecx,0x28
 80494be:	01 cf                	add    edi,ecx
 80494c0:	01 ce                	add    esi,ecx
 80494c2:	4f                   	dec    edi
 80494c3:	4e                   	dec    esi
 80494c4:	fd                   	std    
 80494c5:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 80494c7:	fc                   	cld    
 80494c8:	01 c4                	add    esp,eax
 80494ca:	61                   	popa   
 80494cb:	83 c4 04             	add    esp,0x4
 80494ce:	c3                   	ret    

080494cf <__best_buwrite>:
 80494cf:	6a 00                	push   0x0
 80494d1:	6a 00                	push   0x0
 80494d3:	6a 00                	push   0x0
 80494d5:	6a 00                	push   0x0
 80494d7:	6a 00                	push   0x0
 80494d9:	6a 00                	push   0x0
 80494db:	6a 00                	push   0x0
 80494dd:	6a 00                	push   0x0
 80494df:	6a 00                	push   0x0
 80494e1:	6a 00                	push   0x0
 80494e3:	6a 00                	push   0x0
 80494e5:	6a 00                	push   0x0
 80494e7:	6a 00                	push   0x0
 80494e9:	6a 00                	push   0x0
 80494eb:	6a 00                	push   0x0
 80494ed:	6a 00                	push   0x0
 80494ef:	6a 00                	push   0x0
 80494f1:	6a 00                	push   0x0
 80494f3:	6a 00                	push   0x0
 80494f5:	6a 00                	push   0x0
 80494f7:	6a 00                	push   0x0
 80494f9:	6a 00                	push   0x0
 80494fb:	6a 00                	push   0x0
 80494fd:	6a 00                	push   0x0
 80494ff:	6a 00                	push   0x0
 8049501:	6a 00                	push   0x0
 8049503:	6a 00                	push   0x0
 8049505:	6a 00                	push   0x0
 8049507:	6a 00                	push   0x0
 8049509:	6a 00                	push   0x0
 804950b:	6a 00                	push   0x0
 804950d:	6a 00                	push   0x0
 804950f:	6a 20                	push   0x20

08049511 <..@511._1>:
 8049511:	bd 00 00 00 00       	mov    ebp,0x0
 8049516:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 804951a:	75 08                	jne    8049524 <..@511._2>
 804951c:	ff 0c 24             	dec    DWORD PTR [esp]
 804951f:	8f 04 24             	pop    DWORD PTR [esp]
 8049522:	eb ed                	jmp    8049511 <..@511._1>

08049524 <..@511._2>:
 8049524:	60                   	pusha  
 8049525:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8049529:	89 e2                	mov    edx,esp
 804952b:	83 c2 28             	add    edx,0x28
 804952e:	89 cb                	mov    ebx,ecx
 8049530:	90                   	nop
 8049531:	60                   	pusha  
 8049532:	89 d9                	mov    ecx,ebx

08049534 <..@510._2>:
 8049534:	83 f9 01             	cmp    ecx,0x1
 8049537:	7c 40                	jl     8049579 <..@510._1>
 8049539:	b8 00 00 00 00       	mov    eax,0x0
 804953e:	8b 02                	mov    eax,DWORD PTR [edx]
 8049540:	c1 e0 08             	shl    eax,0x8
 8049543:	c1 e0 08             	shl    eax,0x8
 8049546:	c1 e8 08             	shr    eax,0x8
 8049549:	c1 e8 08             	shr    eax,0x8
 804954c:	e8 a0 f1 ff ff       	call   80486f1 <__best_buput_one>
 8049551:	83 c2 02             	add    edx,0x2
 8049554:	49                   	dec    ecx
 8049555:	83 f9 01             	cmp    ecx,0x1
 8049558:	7c 1f                	jl     8049579 <..@510._1>
 804955a:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804955f:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8049564:	b0 20                	mov    al,0x20
 8049566:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804956a:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 804956f:	83 ec 02             	sub    esp,0x2
 8049572:	e8 57 f8 ff ff       	call   8048dce <__best_cput+0x2>
 8049577:	eb bb                	jmp    8049534 <..@510._2>

08049579 <..@510._1>:
 8049579:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804957e:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8049583:	b0 20                	mov    al,0x20
 8049585:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8049589:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 804958e:	83 ec 02             	sub    esp,0x2
 8049591:	e8 38 f8 ff ff       	call   8048dce <__best_cput+0x2>
 8049596:	61                   	popa   
 8049597:	89 c8                	mov    eax,ecx
 8049599:	bb 02 00 00 00       	mov    ebx,0x2
 804959e:	f7 e3                	mul    ebx
 80495a0:	89 e3                	mov    ebx,esp
 80495a2:	89 de                	mov    esi,ebx
 80495a4:	89 df                	mov    edi,ebx
 80495a6:	01 c7                	add    edi,eax
 80495a8:	b9 28 00 00 00       	mov    ecx,0x28
 80495ad:	01 cf                	add    edi,ecx
 80495af:	01 ce                	add    esi,ecx
 80495b1:	4f                   	dec    edi
 80495b2:	4e                   	dec    esi
 80495b3:	fd                   	std    
 80495b4:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 80495b6:	fc                   	cld    
 80495b7:	01 c4                	add    esp,eax
 80495b9:	61                   	popa   
 80495ba:	83 c4 04             	add    esp,0x4
 80495bd:	c3                   	ret    

080495be <__best_bswrite>:
 80495be:	6a 00                	push   0x0
 80495c0:	6a 00                	push   0x0
 80495c2:	6a 00                	push   0x0
 80495c4:	6a 00                	push   0x0
 80495c6:	6a 00                	push   0x0
 80495c8:	6a 00                	push   0x0
 80495ca:	6a 00                	push   0x0
 80495cc:	6a 00                	push   0x0
 80495ce:	6a 00                	push   0x0
 80495d0:	6a 00                	push   0x0
 80495d2:	6a 00                	push   0x0
 80495d4:	6a 00                	push   0x0
 80495d6:	6a 00                	push   0x0
 80495d8:	6a 00                	push   0x0
 80495da:	6a 00                	push   0x0
 80495dc:	6a 00                	push   0x0
 80495de:	6a 00                	push   0x0
 80495e0:	6a 00                	push   0x0
 80495e2:	6a 00                	push   0x0
 80495e4:	6a 00                	push   0x0
 80495e6:	6a 00                	push   0x0
 80495e8:	6a 00                	push   0x0
 80495ea:	6a 00                	push   0x0
 80495ec:	6a 00                	push   0x0
 80495ee:	6a 00                	push   0x0
 80495f0:	6a 00                	push   0x0
 80495f2:	6a 00                	push   0x0
 80495f4:	6a 00                	push   0x0
 80495f6:	6a 00                	push   0x0
 80495f8:	6a 00                	push   0x0
 80495fa:	6a 00                	push   0x0
 80495fc:	6a 00                	push   0x0
 80495fe:	6a 20                	push   0x20

08049600 <..@521._1>:
 8049600:	bd 00 00 00 00       	mov    ebp,0x0
 8049605:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 8049609:	75 08                	jne    8049613 <..@521._2>
 804960b:	ff 0c 24             	dec    DWORD PTR [esp]
 804960e:	8f 04 24             	pop    DWORD PTR [esp]
 8049611:	eb ed                	jmp    8049600 <..@521._1>

08049613 <..@521._2>:
 8049613:	60                   	pusha  
 8049614:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8049618:	89 e2                	mov    edx,esp
 804961a:	83 c2 28             	add    edx,0x28
 804961d:	89 cb                	mov    ebx,ecx
 804961f:	90                   	nop
 8049620:	60                   	pusha  
 8049621:	89 d9                	mov    ecx,ebx

08049623 <..@520._2>:
 8049623:	83 f9 01             	cmp    ecx,0x1
 8049626:	7c 40                	jl     8049668 <..@520._1>
 8049628:	b8 00 00 00 00       	mov    eax,0x0
 804962d:	8b 02                	mov    eax,DWORD PTR [edx]
 804962f:	c1 e0 08             	shl    eax,0x8
 8049632:	c1 e0 08             	shl    eax,0x8
 8049635:	c1 e8 08             	shr    eax,0x8
 8049638:	c1 e8 08             	shr    eax,0x8
 804963b:	e8 b7 f0 ff ff       	call   80486f7 <__best_bsput_one>
 8049640:	83 c2 02             	add    edx,0x2
 8049643:	49                   	dec    ecx
 8049644:	83 f9 01             	cmp    ecx,0x1
 8049647:	7c 1f                	jl     8049668 <..@520._1>
 8049649:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804964e:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8049653:	b0 20                	mov    al,0x20
 8049655:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8049659:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 804965e:	83 ec 02             	sub    esp,0x2
 8049661:	e8 68 f7 ff ff       	call   8048dce <__best_cput+0x2>
 8049666:	eb bb                	jmp    8049623 <..@520._2>

08049668 <..@520._1>:
 8049668:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804966d:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8049672:	b0 20                	mov    al,0x20
 8049674:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8049678:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 804967d:	83 ec 02             	sub    esp,0x2
 8049680:	e8 49 f7 ff ff       	call   8048dce <__best_cput+0x2>
 8049685:	61                   	popa   
 8049686:	89 c8                	mov    eax,ecx
 8049688:	bb 02 00 00 00       	mov    ebx,0x2
 804968d:	f7 e3                	mul    ebx
 804968f:	89 e3                	mov    ebx,esp
 8049691:	89 de                	mov    esi,ebx
 8049693:	89 df                	mov    edi,ebx
 8049695:	01 c7                	add    edi,eax
 8049697:	b9 28 00 00 00       	mov    ecx,0x28
 804969c:	01 cf                	add    edi,ecx
 804969e:	01 ce                	add    esi,ecx
 80496a0:	4f                   	dec    edi
 80496a1:	4e                   	dec    esi
 80496a2:	fd                   	std    
 80496a3:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 80496a5:	fc                   	cld    
 80496a6:	01 c4                	add    esp,eax
 80496a8:	61                   	popa   
 80496a9:	83 c4 04             	add    esp,0x4
 80496ac:	c3                   	ret    

080496ad <__best_cwrite>:
 80496ad:	6a 00                	push   0x0
 80496af:	6a 00                	push   0x0
 80496b1:	6a 00                	push   0x0
 80496b3:	6a 00                	push   0x0
 80496b5:	6a 00                	push   0x0
 80496b7:	6a 00                	push   0x0
 80496b9:	6a 00                	push   0x0
 80496bb:	6a 00                	push   0x0
 80496bd:	6a 00                	push   0x0
 80496bf:	6a 00                	push   0x0
 80496c1:	6a 00                	push   0x0
 80496c3:	6a 00                	push   0x0
 80496c5:	6a 00                	push   0x0
 80496c7:	6a 00                	push   0x0
 80496c9:	6a 00                	push   0x0
 80496cb:	6a 00                	push   0x0
 80496cd:	6a 00                	push   0x0
 80496cf:	6a 00                	push   0x0
 80496d1:	6a 00                	push   0x0
 80496d3:	6a 00                	push   0x0
 80496d5:	6a 00                	push   0x0
 80496d7:	6a 00                	push   0x0
 80496d9:	6a 00                	push   0x0
 80496db:	6a 00                	push   0x0
 80496dd:	6a 00                	push   0x0
 80496df:	6a 00                	push   0x0
 80496e1:	6a 00                	push   0x0
 80496e3:	6a 00                	push   0x0
 80496e5:	6a 00                	push   0x0
 80496e7:	6a 00                	push   0x0
 80496e9:	6a 00                	push   0x0
 80496eb:	6a 00                	push   0x0
 80496ed:	6a 20                	push   0x20

080496ef <..@531._1>:
 80496ef:	bd 00 00 00 00       	mov    ebp,0x0
 80496f4:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 80496f8:	75 08                	jne    8049702 <..@531._2>
 80496fa:	ff 0c 24             	dec    DWORD PTR [esp]
 80496fd:	8f 04 24             	pop    DWORD PTR [esp]
 8049700:	eb ed                	jmp    80496ef <..@531._1>

08049702 <..@531._2>:
 8049702:	60                   	pusha  
 8049703:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8049707:	89 e2                	mov    edx,esp
 8049709:	83 c2 28             	add    edx,0x28
 804970c:	89 cb                	mov    ebx,ecx
 804970e:	90                   	nop
 804970f:	60                   	pusha  
 8049710:	89 d9                	mov    ecx,ebx

08049712 <..@530._2>:
 8049712:	83 f9 01             	cmp    ecx,0x1
 8049715:	7c 40                	jl     8049757 <..@530._1>
 8049717:	b8 00 00 00 00       	mov    eax,0x0
 804971c:	8b 02                	mov    eax,DWORD PTR [edx]
 804971e:	c1 e0 08             	shl    eax,0x8
 8049721:	c1 e0 08             	shl    eax,0x8
 8049724:	c1 e8 08             	shr    eax,0x8
 8049727:	c1 e8 08             	shr    eax,0x8
 804972a:	e8 04 f0 ff ff       	call   8048733 <__best_cput_one>
 804972f:	83 c2 02             	add    edx,0x2
 8049732:	49                   	dec    ecx
 8049733:	83 f9 01             	cmp    ecx,0x1
 8049736:	7c 1f                	jl     8049757 <..@530._1>
 8049738:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804973d:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8049742:	b0 20                	mov    al,0x20
 8049744:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8049748:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 804974d:	83 ec 02             	sub    esp,0x2
 8049750:	e8 79 f6 ff ff       	call   8048dce <__best_cput+0x2>
 8049755:	eb bb                	jmp    8049712 <..@530._2>

08049757 <..@530._1>:
 8049757:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804975c:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8049761:	b0 20                	mov    al,0x20
 8049763:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8049767:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 804976c:	83 ec 02             	sub    esp,0x2
 804976f:	e8 5a f6 ff ff       	call   8048dce <__best_cput+0x2>
 8049774:	61                   	popa   
 8049775:	89 c8                	mov    eax,ecx
 8049777:	bb 02 00 00 00       	mov    ebx,0x2
 804977c:	f7 e3                	mul    ebx
 804977e:	89 e3                	mov    ebx,esp
 8049780:	89 de                	mov    esi,ebx
 8049782:	89 df                	mov    edi,ebx
 8049784:	01 c7                	add    edi,eax
 8049786:	b9 28 00 00 00       	mov    ecx,0x28
 804978b:	01 cf                	add    edi,ecx
 804978d:	01 ce                	add    esi,ecx
 804978f:	4f                   	dec    edi
 8049790:	4e                   	dec    esi
 8049791:	fd                   	std    
 8049792:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8049794:	fc                   	cld    
 8049795:	01 c4                	add    esp,eax
 8049797:	61                   	popa   
 8049798:	83 c4 04             	add    esp,0x4
 804979b:	c3                   	ret    

0804979c <__best_swrite>:
 804979c:	6a 00                	push   0x0
 804979e:	6a 00                	push   0x0
 80497a0:	6a 00                	push   0x0
 80497a2:	6a 00                	push   0x0
 80497a4:	6a 00                	push   0x0
 80497a6:	6a 00                	push   0x0
 80497a8:	6a 00                	push   0x0
 80497aa:	6a 00                	push   0x0
 80497ac:	6a 00                	push   0x0
 80497ae:	6a 00                	push   0x0
 80497b0:	6a 00                	push   0x0
 80497b2:	6a 00                	push   0x0
 80497b4:	6a 00                	push   0x0
 80497b6:	6a 00                	push   0x0
 80497b8:	6a 00                	push   0x0
 80497ba:	6a 00                	push   0x0
 80497bc:	6a 00                	push   0x0
 80497be:	6a 00                	push   0x0
 80497c0:	6a 00                	push   0x0
 80497c2:	6a 00                	push   0x0
 80497c4:	6a 00                	push   0x0
 80497c6:	6a 00                	push   0x0
 80497c8:	6a 00                	push   0x0
 80497ca:	6a 00                	push   0x0
 80497cc:	6a 00                	push   0x0
 80497ce:	6a 00                	push   0x0
 80497d0:	6a 00                	push   0x0
 80497d2:	6a 00                	push   0x0
 80497d4:	6a 00                	push   0x0
 80497d6:	6a 00                	push   0x0
 80497d8:	6a 00                	push   0x0
 80497da:	6a 00                	push   0x0
 80497dc:	6a 20                	push   0x20

080497de <..@541._1>:
 80497de:	bd 00 00 00 00       	mov    ebp,0x0
 80497e3:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 80497e7:	75 08                	jne    80497f1 <..@541._2>
 80497e9:	ff 0c 24             	dec    DWORD PTR [esp]
 80497ec:	8f 04 24             	pop    DWORD PTR [esp]
 80497ef:	eb ed                	jmp    80497de <..@541._1>

080497f1 <..@541._2>:
 80497f1:	60                   	pusha  
 80497f2:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 80497f6:	89 e2                	mov    edx,esp
 80497f8:	83 c2 28             	add    edx,0x28
 80497fb:	89 cb                	mov    ebx,ecx
 80497fd:	8b 54 24 24          	mov    edx,DWORD PTR [esp+0x24]
 8049801:	01 4c 24 24          	add    DWORD PTR [esp+0x24],ecx
 8049805:	b9 00 00 00 00       	mov    ecx,0x0
 804980a:	60                   	pusha  
 804980b:	89 d9                	mov    ecx,ebx

0804980d <..@540._2>:
 804980d:	83 f9 01             	cmp    ecx,0x1
 8049810:	7c 29                	jl     804983b <..@540._1>
 8049812:	b8 00 00 00 00       	mov    eax,0x0
 8049817:	8b 02                	mov    eax,DWORD PTR [edx]
 8049819:	c1 e0 08             	shl    eax,0x8
 804981c:	c1 e0 08             	shl    eax,0x8
 804981f:	c1 e0 08             	shl    eax,0x8
 8049822:	c1 e8 08             	shr    eax,0x8
 8049825:	c1 e8 08             	shr    eax,0x8
 8049828:	c1 e8 08             	shr    eax,0x8
 804982b:	e8 1e ef ff ff       	call   804874e <__best_sput_one>
 8049830:	83 c2 01             	add    edx,0x1
 8049833:	49                   	dec    ecx
 8049834:	83 f9 01             	cmp    ecx,0x1
 8049837:	7c 02                	jl     804983b <..@540._1>
 8049839:	eb d2                	jmp    804980d <..@540._2>

0804983b <..@540._1>:
 804983b:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8049840:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8049845:	b0 20                	mov    al,0x20
 8049847:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804984b:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8049850:	83 ec 02             	sub    esp,0x2
 8049853:	e8 76 f5 ff ff       	call   8048dce <__best_cput+0x2>
 8049858:	61                   	popa   
 8049859:	89 c8                	mov    eax,ecx
 804985b:	bb 01 00 00 00       	mov    ebx,0x1
 8049860:	f7 e3                	mul    ebx
 8049862:	89 e3                	mov    ebx,esp
 8049864:	89 de                	mov    esi,ebx
 8049866:	89 df                	mov    edi,ebx
 8049868:	01 c7                	add    edi,eax
 804986a:	b9 28 00 00 00       	mov    ecx,0x28
 804986f:	01 cf                	add    edi,ecx
 8049871:	01 ce                	add    esi,ecx
 8049873:	4f                   	dec    edi
 8049874:	4e                   	dec    esi
 8049875:	fd                   	std    
 8049876:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8049878:	fc                   	cld    
 8049879:	01 c4                	add    esp,eax
 804987b:	61                   	popa   
 804987c:	83 c4 04             	add    esp,0x4
 804987f:	c3                   	ret    

08049880 <__best_quprint>:
 8049880:	6a 00                	push   0x0
 8049882:	6a 00                	push   0x0
 8049884:	6a 00                	push   0x0
 8049886:	6a 00                	push   0x0
 8049888:	6a 00                	push   0x0
 804988a:	6a 00                	push   0x0
 804988c:	6a 00                	push   0x0
 804988e:	6a 00                	push   0x0
 8049890:	6a 00                	push   0x0
 8049892:	6a 00                	push   0x0
 8049894:	6a 00                	push   0x0
 8049896:	6a 00                	push   0x0
 8049898:	6a 00                	push   0x0
 804989a:	6a 00                	push   0x0
 804989c:	6a 00                	push   0x0
 804989e:	6a 00                	push   0x0
 80498a0:	6a 00                	push   0x0
 80498a2:	6a 00                	push   0x0
 80498a4:	6a 00                	push   0x0
 80498a6:	6a 00                	push   0x0
 80498a8:	6a 00                	push   0x0
 80498aa:	6a 00                	push   0x0
 80498ac:	6a 00                	push   0x0
 80498ae:	6a 00                	push   0x0
 80498b0:	6a 00                	push   0x0
 80498b2:	6a 00                	push   0x0
 80498b4:	6a 00                	push   0x0
 80498b6:	6a 00                	push   0x0
 80498b8:	6a 00                	push   0x0
 80498ba:	6a 00                	push   0x0
 80498bc:	6a 00                	push   0x0
 80498be:	6a 00                	push   0x0
 80498c0:	6a 20                	push   0x20

080498c2 <..@548._1>:
 80498c2:	bd 00 00 00 00       	mov    ebp,0x0
 80498c7:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 80498cb:	75 08                	jne    80498d5 <..@548._2>
 80498cd:	ff 0c 24             	dec    DWORD PTR [esp]
 80498d0:	8f 04 24             	pop    DWORD PTR [esp]
 80498d3:	eb ed                	jmp    80498c2 <..@548._1>

080498d5 <..@548._2>:
 80498d5:	60                   	pusha  
 80498d6:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 80498da:	89 e2                	mov    edx,esp
 80498dc:	83 c2 28             	add    edx,0x28
 80498df:	89 cb                	mov    ebx,ecx
 80498e1:	90                   	nop
 80498e2:	60                   	pusha  
 80498e3:	89 d9                	mov    ecx,ebx

080498e5 <..@547._2>:
 80498e5:	83 f9 01             	cmp    ecx,0x1
 80498e8:	7c 34                	jl     804991e <..@547._1>
 80498ea:	b8 00 00 00 00       	mov    eax,0x0
 80498ef:	8b 02                	mov    eax,DWORD PTR [edx]
 80498f1:	e8 5f ed ff ff       	call   8048655 <__best_quput_one>
 80498f6:	83 c2 08             	add    edx,0x8
 80498f9:	49                   	dec    ecx
 80498fa:	83 f9 01             	cmp    ecx,0x1
 80498fd:	7c 1f                	jl     804991e <..@547._1>
 80498ff:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8049904:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8049909:	b0 20                	mov    al,0x20
 804990b:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804990f:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8049914:	83 ec 02             	sub    esp,0x2
 8049917:	e8 b2 f4 ff ff       	call   8048dce <__best_cput+0x2>
 804991c:	eb c7                	jmp    80498e5 <..@547._2>

0804991e <..@547._1>:
 804991e:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8049923:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8049928:	b0 0a                	mov    al,0xa
 804992a:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804992e:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8049933:	83 ec 02             	sub    esp,0x2
 8049936:	e8 93 f4 ff ff       	call   8048dce <__best_cput+0x2>
 804993b:	61                   	popa   
 804993c:	89 c8                	mov    eax,ecx
 804993e:	bb 08 00 00 00       	mov    ebx,0x8
 8049943:	f7 e3                	mul    ebx
 8049945:	89 e3                	mov    ebx,esp
 8049947:	89 de                	mov    esi,ebx
 8049949:	89 df                	mov    edi,ebx
 804994b:	01 c7                	add    edi,eax
 804994d:	b9 28 00 00 00       	mov    ecx,0x28
 8049952:	01 cf                	add    edi,ecx
 8049954:	01 ce                	add    esi,ecx
 8049956:	4f                   	dec    edi
 8049957:	4e                   	dec    esi
 8049958:	fd                   	std    
 8049959:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 804995b:	fc                   	cld    
 804995c:	01 c4                	add    esp,eax
 804995e:	61                   	popa   
 804995f:	83 c4 04             	add    esp,0x4
 8049962:	c3                   	ret    

08049963 <__best_qsprint>:
 8049963:	6a 00                	push   0x0
 8049965:	6a 00                	push   0x0
 8049967:	6a 00                	push   0x0
 8049969:	6a 00                	push   0x0
 804996b:	6a 00                	push   0x0
 804996d:	6a 00                	push   0x0
 804996f:	6a 00                	push   0x0
 8049971:	6a 00                	push   0x0
 8049973:	6a 00                	push   0x0
 8049975:	6a 00                	push   0x0
 8049977:	6a 00                	push   0x0
 8049979:	6a 00                	push   0x0
 804997b:	6a 00                	push   0x0
 804997d:	6a 00                	push   0x0
 804997f:	6a 00                	push   0x0
 8049981:	6a 00                	push   0x0
 8049983:	6a 00                	push   0x0
 8049985:	6a 00                	push   0x0
 8049987:	6a 00                	push   0x0
 8049989:	6a 00                	push   0x0
 804998b:	6a 00                	push   0x0
 804998d:	6a 00                	push   0x0
 804998f:	6a 00                	push   0x0
 8049991:	6a 00                	push   0x0
 8049993:	6a 00                	push   0x0
 8049995:	6a 00                	push   0x0
 8049997:	6a 00                	push   0x0
 8049999:	6a 00                	push   0x0
 804999b:	6a 00                	push   0x0
 804999d:	6a 00                	push   0x0
 804999f:	6a 00                	push   0x0
 80499a1:	6a 00                	push   0x0
 80499a3:	6a 20                	push   0x20

080499a5 <..@558._1>:
 80499a5:	bd 00 00 00 00       	mov    ebp,0x0
 80499aa:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 80499ae:	75 08                	jne    80499b8 <..@558._2>
 80499b0:	ff 0c 24             	dec    DWORD PTR [esp]
 80499b3:	8f 04 24             	pop    DWORD PTR [esp]
 80499b6:	eb ed                	jmp    80499a5 <..@558._1>

080499b8 <..@558._2>:
 80499b8:	60                   	pusha  
 80499b9:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 80499bd:	89 e2                	mov    edx,esp
 80499bf:	83 c2 28             	add    edx,0x28
 80499c2:	89 cb                	mov    ebx,ecx
 80499c4:	90                   	nop
 80499c5:	60                   	pusha  
 80499c6:	89 d9                	mov    ecx,ebx

080499c8 <..@557._2>:
 80499c8:	83 f9 01             	cmp    ecx,0x1
 80499cb:	7c 34                	jl     8049a01 <..@557._1>
 80499cd:	b8 00 00 00 00       	mov    eax,0x0
 80499d2:	8b 02                	mov    eax,DWORD PTR [edx]
 80499d4:	e8 82 ec ff ff       	call   804865b <__best_qsput_one>
 80499d9:	83 c2 08             	add    edx,0x8
 80499dc:	49                   	dec    ecx
 80499dd:	83 f9 01             	cmp    ecx,0x1
 80499e0:	7c 1f                	jl     8049a01 <..@557._1>
 80499e2:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80499e7:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 80499ec:	b0 20                	mov    al,0x20
 80499ee:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80499f2:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 80499f7:	83 ec 02             	sub    esp,0x2
 80499fa:	e8 cf f3 ff ff       	call   8048dce <__best_cput+0x2>
 80499ff:	eb c7                	jmp    80499c8 <..@557._2>

08049a01 <..@557._1>:
 8049a01:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8049a06:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8049a0b:	b0 0a                	mov    al,0xa
 8049a0d:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8049a11:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8049a16:	83 ec 02             	sub    esp,0x2
 8049a19:	e8 b0 f3 ff ff       	call   8048dce <__best_cput+0x2>
 8049a1e:	61                   	popa   
 8049a1f:	89 c8                	mov    eax,ecx
 8049a21:	bb 08 00 00 00       	mov    ebx,0x8
 8049a26:	f7 e3                	mul    ebx
 8049a28:	89 e3                	mov    ebx,esp
 8049a2a:	89 de                	mov    esi,ebx
 8049a2c:	89 df                	mov    edi,ebx
 8049a2e:	01 c7                	add    edi,eax
 8049a30:	b9 28 00 00 00       	mov    ecx,0x28
 8049a35:	01 cf                	add    edi,ecx
 8049a37:	01 ce                	add    esi,ecx
 8049a39:	4f                   	dec    edi
 8049a3a:	4e                   	dec    esi
 8049a3b:	fd                   	std    
 8049a3c:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8049a3e:	fc                   	cld    
 8049a3f:	01 c4                	add    esp,eax
 8049a41:	61                   	popa   
 8049a42:	83 c4 04             	add    esp,0x4
 8049a45:	c3                   	ret    

08049a46 <__best_duprint>:
 8049a46:	6a 00                	push   0x0
 8049a48:	6a 00                	push   0x0
 8049a4a:	6a 00                	push   0x0
 8049a4c:	6a 00                	push   0x0
 8049a4e:	6a 00                	push   0x0
 8049a50:	6a 00                	push   0x0
 8049a52:	6a 00                	push   0x0
 8049a54:	6a 00                	push   0x0
 8049a56:	6a 00                	push   0x0
 8049a58:	6a 00                	push   0x0
 8049a5a:	6a 00                	push   0x0
 8049a5c:	6a 00                	push   0x0
 8049a5e:	6a 00                	push   0x0
 8049a60:	6a 00                	push   0x0
 8049a62:	6a 00                	push   0x0
 8049a64:	6a 00                	push   0x0
 8049a66:	6a 00                	push   0x0
 8049a68:	6a 00                	push   0x0
 8049a6a:	6a 00                	push   0x0
 8049a6c:	6a 00                	push   0x0
 8049a6e:	6a 00                	push   0x0
 8049a70:	6a 00                	push   0x0
 8049a72:	6a 00                	push   0x0
 8049a74:	6a 00                	push   0x0
 8049a76:	6a 00                	push   0x0
 8049a78:	6a 00                	push   0x0
 8049a7a:	6a 00                	push   0x0
 8049a7c:	6a 00                	push   0x0
 8049a7e:	6a 00                	push   0x0
 8049a80:	6a 00                	push   0x0
 8049a82:	6a 00                	push   0x0
 8049a84:	6a 00                	push   0x0
 8049a86:	6a 20                	push   0x20

08049a88 <..@568._1>:
 8049a88:	bd 00 00 00 00       	mov    ebp,0x0
 8049a8d:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 8049a91:	75 08                	jne    8049a9b <..@568._2>
 8049a93:	ff 0c 24             	dec    DWORD PTR [esp]
 8049a96:	8f 04 24             	pop    DWORD PTR [esp]
 8049a99:	eb ed                	jmp    8049a88 <..@568._1>

08049a9b <..@568._2>:
 8049a9b:	60                   	pusha  
 8049a9c:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8049aa0:	89 e2                	mov    edx,esp
 8049aa2:	83 c2 28             	add    edx,0x28
 8049aa5:	89 cb                	mov    ebx,ecx
 8049aa7:	90                   	nop
 8049aa8:	60                   	pusha  
 8049aa9:	89 d9                	mov    ecx,ebx

08049aab <..@567._2>:
 8049aab:	83 f9 01             	cmp    ecx,0x1
 8049aae:	7c 34                	jl     8049ae4 <..@567._1>
 8049ab0:	b8 00 00 00 00       	mov    eax,0x0
 8049ab5:	8b 02                	mov    eax,DWORD PTR [edx]
 8049ab7:	e8 c9 eb ff ff       	call   8048685 <__best_duput_one>
 8049abc:	83 c2 04             	add    edx,0x4
 8049abf:	49                   	dec    ecx
 8049ac0:	83 f9 01             	cmp    ecx,0x1
 8049ac3:	7c 1f                	jl     8049ae4 <..@567._1>
 8049ac5:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8049aca:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8049acf:	b0 20                	mov    al,0x20
 8049ad1:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8049ad5:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8049ada:	83 ec 02             	sub    esp,0x2
 8049add:	e8 ec f2 ff ff       	call   8048dce <__best_cput+0x2>
 8049ae2:	eb c7                	jmp    8049aab <..@567._2>

08049ae4 <..@567._1>:
 8049ae4:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8049ae9:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8049aee:	b0 0a                	mov    al,0xa
 8049af0:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8049af4:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8049af9:	83 ec 02             	sub    esp,0x2
 8049afc:	e8 cd f2 ff ff       	call   8048dce <__best_cput+0x2>
 8049b01:	61                   	popa   
 8049b02:	89 c8                	mov    eax,ecx
 8049b04:	bb 04 00 00 00       	mov    ebx,0x4
 8049b09:	f7 e3                	mul    ebx
 8049b0b:	89 e3                	mov    ebx,esp
 8049b0d:	89 de                	mov    esi,ebx
 8049b0f:	89 df                	mov    edi,ebx
 8049b11:	01 c7                	add    edi,eax
 8049b13:	b9 28 00 00 00       	mov    ecx,0x28
 8049b18:	01 cf                	add    edi,ecx
 8049b1a:	01 ce                	add    esi,ecx
 8049b1c:	4f                   	dec    edi
 8049b1d:	4e                   	dec    esi
 8049b1e:	fd                   	std    
 8049b1f:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8049b21:	fc                   	cld    
 8049b22:	01 c4                	add    esp,eax
 8049b24:	61                   	popa   
 8049b25:	83 c4 04             	add    esp,0x4
 8049b28:	c3                   	ret    

08049b29 <__best_dsprint>:
 8049b29:	6a 00                	push   0x0
 8049b2b:	6a 00                	push   0x0
 8049b2d:	6a 00                	push   0x0
 8049b2f:	6a 00                	push   0x0
 8049b31:	6a 00                	push   0x0
 8049b33:	6a 00                	push   0x0
 8049b35:	6a 00                	push   0x0
 8049b37:	6a 00                	push   0x0
 8049b39:	6a 00                	push   0x0
 8049b3b:	6a 00                	push   0x0
 8049b3d:	6a 00                	push   0x0
 8049b3f:	6a 00                	push   0x0
 8049b41:	6a 00                	push   0x0
 8049b43:	6a 00                	push   0x0
 8049b45:	6a 00                	push   0x0
 8049b47:	6a 00                	push   0x0
 8049b49:	6a 00                	push   0x0
 8049b4b:	6a 00                	push   0x0
 8049b4d:	6a 00                	push   0x0
 8049b4f:	6a 00                	push   0x0
 8049b51:	6a 00                	push   0x0
 8049b53:	6a 00                	push   0x0
 8049b55:	6a 00                	push   0x0
 8049b57:	6a 00                	push   0x0
 8049b59:	6a 00                	push   0x0
 8049b5b:	6a 00                	push   0x0
 8049b5d:	6a 00                	push   0x0
 8049b5f:	6a 00                	push   0x0
 8049b61:	6a 00                	push   0x0
 8049b63:	6a 00                	push   0x0
 8049b65:	6a 00                	push   0x0
 8049b67:	6a 00                	push   0x0
 8049b69:	6a 20                	push   0x20

08049b6b <..@578._1>:
 8049b6b:	bd 00 00 00 00       	mov    ebp,0x0
 8049b70:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 8049b74:	75 08                	jne    8049b7e <..@578._2>
 8049b76:	ff 0c 24             	dec    DWORD PTR [esp]
 8049b79:	8f 04 24             	pop    DWORD PTR [esp]
 8049b7c:	eb ed                	jmp    8049b6b <..@578._1>

08049b7e <..@578._2>:
 8049b7e:	60                   	pusha  
 8049b7f:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8049b83:	89 e2                	mov    edx,esp
 8049b85:	83 c2 28             	add    edx,0x28
 8049b88:	89 cb                	mov    ebx,ecx
 8049b8a:	90                   	nop
 8049b8b:	60                   	pusha  
 8049b8c:	89 d9                	mov    ecx,ebx

08049b8e <..@577._2>:
 8049b8e:	83 f9 01             	cmp    ecx,0x1
 8049b91:	7c 34                	jl     8049bc7 <..@577._1>
 8049b93:	b8 00 00 00 00       	mov    eax,0x0
 8049b98:	8b 02                	mov    eax,DWORD PTR [edx]
 8049b9a:	e8 ec ea ff ff       	call   804868b <__best_dsput_one>
 8049b9f:	83 c2 04             	add    edx,0x4
 8049ba2:	49                   	dec    ecx
 8049ba3:	83 f9 01             	cmp    ecx,0x1
 8049ba6:	7c 1f                	jl     8049bc7 <..@577._1>
 8049ba8:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8049bad:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8049bb2:	b0 20                	mov    al,0x20
 8049bb4:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8049bb8:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8049bbd:	83 ec 02             	sub    esp,0x2
 8049bc0:	e8 09 f2 ff ff       	call   8048dce <__best_cput+0x2>
 8049bc5:	eb c7                	jmp    8049b8e <..@577._2>

08049bc7 <..@577._1>:
 8049bc7:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8049bcc:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8049bd1:	b0 0a                	mov    al,0xa
 8049bd3:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8049bd7:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8049bdc:	83 ec 02             	sub    esp,0x2
 8049bdf:	e8 ea f1 ff ff       	call   8048dce <__best_cput+0x2>
 8049be4:	61                   	popa   
 8049be5:	89 c8                	mov    eax,ecx
 8049be7:	bb 04 00 00 00       	mov    ebx,0x4
 8049bec:	f7 e3                	mul    ebx
 8049bee:	89 e3                	mov    ebx,esp
 8049bf0:	89 de                	mov    esi,ebx
 8049bf2:	89 df                	mov    edi,ebx
 8049bf4:	01 c7                	add    edi,eax
 8049bf6:	b9 28 00 00 00       	mov    ecx,0x28
 8049bfb:	01 cf                	add    edi,ecx
 8049bfd:	01 ce                	add    esi,ecx
 8049bff:	4f                   	dec    edi
 8049c00:	4e                   	dec    esi
 8049c01:	fd                   	std    
 8049c02:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8049c04:	fc                   	cld    
 8049c05:	01 c4                	add    esp,eax
 8049c07:	61                   	popa   
 8049c08:	83 c4 04             	add    esp,0x4
 8049c0b:	c3                   	ret    

08049c0c <__best_wuprint>:
 8049c0c:	6a 00                	push   0x0
 8049c0e:	6a 00                	push   0x0
 8049c10:	6a 00                	push   0x0
 8049c12:	6a 00                	push   0x0
 8049c14:	6a 00                	push   0x0
 8049c16:	6a 00                	push   0x0
 8049c18:	6a 00                	push   0x0
 8049c1a:	6a 00                	push   0x0
 8049c1c:	6a 00                	push   0x0
 8049c1e:	6a 00                	push   0x0
 8049c20:	6a 00                	push   0x0
 8049c22:	6a 00                	push   0x0
 8049c24:	6a 00                	push   0x0
 8049c26:	6a 00                	push   0x0
 8049c28:	6a 00                	push   0x0
 8049c2a:	6a 00                	push   0x0
 8049c2c:	6a 00                	push   0x0
 8049c2e:	6a 00                	push   0x0
 8049c30:	6a 00                	push   0x0
 8049c32:	6a 00                	push   0x0
 8049c34:	6a 00                	push   0x0
 8049c36:	6a 00                	push   0x0
 8049c38:	6a 00                	push   0x0
 8049c3a:	6a 00                	push   0x0
 8049c3c:	6a 00                	push   0x0
 8049c3e:	6a 00                	push   0x0
 8049c40:	6a 00                	push   0x0
 8049c42:	6a 00                	push   0x0
 8049c44:	6a 00                	push   0x0
 8049c46:	6a 00                	push   0x0
 8049c48:	6a 00                	push   0x0
 8049c4a:	6a 00                	push   0x0
 8049c4c:	6a 20                	push   0x20

08049c4e <..@588._1>:
 8049c4e:	bd 00 00 00 00       	mov    ebp,0x0
 8049c53:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 8049c57:	75 08                	jne    8049c61 <..@588._2>
 8049c59:	ff 0c 24             	dec    DWORD PTR [esp]
 8049c5c:	8f 04 24             	pop    DWORD PTR [esp]
 8049c5f:	eb ed                	jmp    8049c4e <..@588._1>

08049c61 <..@588._2>:
 8049c61:	60                   	pusha  
 8049c62:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8049c66:	89 e2                	mov    edx,esp
 8049c68:	83 c2 28             	add    edx,0x28
 8049c6b:	89 cb                	mov    ebx,ecx
 8049c6d:	90                   	nop
 8049c6e:	60                   	pusha  
 8049c6f:	89 d9                	mov    ecx,ebx

08049c71 <..@587._2>:
 8049c71:	83 f9 01             	cmp    ecx,0x1
 8049c74:	7c 40                	jl     8049cb6 <..@587._1>
 8049c76:	b8 00 00 00 00       	mov    eax,0x0
 8049c7b:	8b 02                	mov    eax,DWORD PTR [edx]
 8049c7d:	c1 e0 08             	shl    eax,0x8
 8049c80:	c1 e0 08             	shl    eax,0x8
 8049c83:	c1 e8 08             	shr    eax,0x8
 8049c86:	c1 e8 08             	shr    eax,0x8
 8049c89:	e8 27 ea ff ff       	call   80486b5 <__best_wuput_one>
 8049c8e:	83 c2 02             	add    edx,0x2
 8049c91:	49                   	dec    ecx
 8049c92:	83 f9 01             	cmp    ecx,0x1
 8049c95:	7c 1f                	jl     8049cb6 <..@587._1>
 8049c97:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8049c9c:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8049ca1:	b0 20                	mov    al,0x20
 8049ca3:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8049ca7:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8049cac:	83 ec 02             	sub    esp,0x2
 8049caf:	e8 1a f1 ff ff       	call   8048dce <__best_cput+0x2>
 8049cb4:	eb bb                	jmp    8049c71 <..@587._2>

08049cb6 <..@587._1>:
 8049cb6:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8049cbb:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8049cc0:	b0 0a                	mov    al,0xa
 8049cc2:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8049cc6:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8049ccb:	83 ec 02             	sub    esp,0x2
 8049cce:	e8 fb f0 ff ff       	call   8048dce <__best_cput+0x2>
 8049cd3:	61                   	popa   
 8049cd4:	89 c8                	mov    eax,ecx
 8049cd6:	bb 02 00 00 00       	mov    ebx,0x2
 8049cdb:	f7 e3                	mul    ebx
 8049cdd:	89 e3                	mov    ebx,esp
 8049cdf:	89 de                	mov    esi,ebx
 8049ce1:	89 df                	mov    edi,ebx
 8049ce3:	01 c7                	add    edi,eax
 8049ce5:	b9 28 00 00 00       	mov    ecx,0x28
 8049cea:	01 cf                	add    edi,ecx
 8049cec:	01 ce                	add    esi,ecx
 8049cee:	4f                   	dec    edi
 8049cef:	4e                   	dec    esi
 8049cf0:	fd                   	std    
 8049cf1:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8049cf3:	fc                   	cld    
 8049cf4:	01 c4                	add    esp,eax
 8049cf6:	61                   	popa   
 8049cf7:	83 c4 04             	add    esp,0x4
 8049cfa:	c3                   	ret    

08049cfb <__best_wsprint>:
 8049cfb:	6a 00                	push   0x0
 8049cfd:	6a 00                	push   0x0
 8049cff:	6a 00                	push   0x0
 8049d01:	6a 00                	push   0x0
 8049d03:	6a 00                	push   0x0
 8049d05:	6a 00                	push   0x0
 8049d07:	6a 00                	push   0x0
 8049d09:	6a 00                	push   0x0
 8049d0b:	6a 00                	push   0x0
 8049d0d:	6a 00                	push   0x0
 8049d0f:	6a 00                	push   0x0
 8049d11:	6a 00                	push   0x0
 8049d13:	6a 00                	push   0x0
 8049d15:	6a 00                	push   0x0
 8049d17:	6a 00                	push   0x0
 8049d19:	6a 00                	push   0x0
 8049d1b:	6a 00                	push   0x0
 8049d1d:	6a 00                	push   0x0
 8049d1f:	6a 00                	push   0x0
 8049d21:	6a 00                	push   0x0
 8049d23:	6a 00                	push   0x0
 8049d25:	6a 00                	push   0x0
 8049d27:	6a 00                	push   0x0
 8049d29:	6a 00                	push   0x0
 8049d2b:	6a 00                	push   0x0
 8049d2d:	6a 00                	push   0x0
 8049d2f:	6a 00                	push   0x0
 8049d31:	6a 00                	push   0x0
 8049d33:	6a 00                	push   0x0
 8049d35:	6a 00                	push   0x0
 8049d37:	6a 00                	push   0x0
 8049d39:	6a 00                	push   0x0
 8049d3b:	6a 20                	push   0x20

08049d3d <..@598._1>:
 8049d3d:	bd 00 00 00 00       	mov    ebp,0x0
 8049d42:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 8049d46:	75 08                	jne    8049d50 <..@598._2>
 8049d48:	ff 0c 24             	dec    DWORD PTR [esp]
 8049d4b:	8f 04 24             	pop    DWORD PTR [esp]
 8049d4e:	eb ed                	jmp    8049d3d <..@598._1>

08049d50 <..@598._2>:
 8049d50:	60                   	pusha  
 8049d51:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8049d55:	89 e2                	mov    edx,esp
 8049d57:	83 c2 28             	add    edx,0x28
 8049d5a:	89 cb                	mov    ebx,ecx
 8049d5c:	90                   	nop
 8049d5d:	60                   	pusha  
 8049d5e:	89 d9                	mov    ecx,ebx

08049d60 <..@597._2>:
 8049d60:	83 f9 01             	cmp    ecx,0x1
 8049d63:	7c 40                	jl     8049da5 <..@597._1>
 8049d65:	b8 00 00 00 00       	mov    eax,0x0
 8049d6a:	8b 02                	mov    eax,DWORD PTR [edx]
 8049d6c:	c1 e0 08             	shl    eax,0x8
 8049d6f:	c1 e0 08             	shl    eax,0x8
 8049d72:	c1 e8 08             	shr    eax,0x8
 8049d75:	c1 e8 08             	shr    eax,0x8
 8049d78:	e8 3e e9 ff ff       	call   80486bb <__best_wsput_one>
 8049d7d:	83 c2 02             	add    edx,0x2
 8049d80:	49                   	dec    ecx
 8049d81:	83 f9 01             	cmp    ecx,0x1
 8049d84:	7c 1f                	jl     8049da5 <..@597._1>
 8049d86:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8049d8b:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8049d90:	b0 20                	mov    al,0x20
 8049d92:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8049d96:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8049d9b:	83 ec 02             	sub    esp,0x2
 8049d9e:	e8 2b f0 ff ff       	call   8048dce <__best_cput+0x2>
 8049da3:	eb bb                	jmp    8049d60 <..@597._2>

08049da5 <..@597._1>:
 8049da5:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8049daa:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8049daf:	b0 0a                	mov    al,0xa
 8049db1:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8049db5:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8049dba:	83 ec 02             	sub    esp,0x2
 8049dbd:	e8 0c f0 ff ff       	call   8048dce <__best_cput+0x2>
 8049dc2:	61                   	popa   
 8049dc3:	89 c8                	mov    eax,ecx
 8049dc5:	bb 02 00 00 00       	mov    ebx,0x2
 8049dca:	f7 e3                	mul    ebx
 8049dcc:	89 e3                	mov    ebx,esp
 8049dce:	89 de                	mov    esi,ebx
 8049dd0:	89 df                	mov    edi,ebx
 8049dd2:	01 c7                	add    edi,eax
 8049dd4:	b9 28 00 00 00       	mov    ecx,0x28
 8049dd9:	01 cf                	add    edi,ecx
 8049ddb:	01 ce                	add    esi,ecx
 8049ddd:	4f                   	dec    edi
 8049dde:	4e                   	dec    esi
 8049ddf:	fd                   	std    
 8049de0:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8049de2:	fc                   	cld    
 8049de3:	01 c4                	add    esp,eax
 8049de5:	61                   	popa   
 8049de6:	83 c4 04             	add    esp,0x4
 8049de9:	c3                   	ret    

08049dea <__best_buprint>:
 8049dea:	6a 00                	push   0x0
 8049dec:	6a 00                	push   0x0
 8049dee:	6a 00                	push   0x0
 8049df0:	6a 00                	push   0x0
 8049df2:	6a 00                	push   0x0
 8049df4:	6a 00                	push   0x0
 8049df6:	6a 00                	push   0x0
 8049df8:	6a 00                	push   0x0
 8049dfa:	6a 00                	push   0x0
 8049dfc:	6a 00                	push   0x0
 8049dfe:	6a 00                	push   0x0
 8049e00:	6a 00                	push   0x0
 8049e02:	6a 00                	push   0x0
 8049e04:	6a 00                	push   0x0
 8049e06:	6a 00                	push   0x0
 8049e08:	6a 00                	push   0x0
 8049e0a:	6a 00                	push   0x0
 8049e0c:	6a 00                	push   0x0
 8049e0e:	6a 00                	push   0x0
 8049e10:	6a 00                	push   0x0
 8049e12:	6a 00                	push   0x0
 8049e14:	6a 00                	push   0x0
 8049e16:	6a 00                	push   0x0
 8049e18:	6a 00                	push   0x0
 8049e1a:	6a 00                	push   0x0
 8049e1c:	6a 00                	push   0x0
 8049e1e:	6a 00                	push   0x0
 8049e20:	6a 00                	push   0x0
 8049e22:	6a 00                	push   0x0
 8049e24:	6a 00                	push   0x0
 8049e26:	6a 00                	push   0x0
 8049e28:	6a 00                	push   0x0
 8049e2a:	6a 20                	push   0x20

08049e2c <..@608._1>:
 8049e2c:	bd 00 00 00 00       	mov    ebp,0x0
 8049e31:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 8049e35:	75 08                	jne    8049e3f <..@608._2>
 8049e37:	ff 0c 24             	dec    DWORD PTR [esp]
 8049e3a:	8f 04 24             	pop    DWORD PTR [esp]
 8049e3d:	eb ed                	jmp    8049e2c <..@608._1>

08049e3f <..@608._2>:
 8049e3f:	60                   	pusha  
 8049e40:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8049e44:	89 e2                	mov    edx,esp
 8049e46:	83 c2 28             	add    edx,0x28
 8049e49:	89 cb                	mov    ebx,ecx
 8049e4b:	90                   	nop
 8049e4c:	60                   	pusha  
 8049e4d:	89 d9                	mov    ecx,ebx

08049e4f <..@607._2>:
 8049e4f:	83 f9 01             	cmp    ecx,0x1
 8049e52:	7c 40                	jl     8049e94 <..@607._1>
 8049e54:	b8 00 00 00 00       	mov    eax,0x0
 8049e59:	8b 02                	mov    eax,DWORD PTR [edx]
 8049e5b:	c1 e0 08             	shl    eax,0x8
 8049e5e:	c1 e0 08             	shl    eax,0x8
 8049e61:	c1 e8 08             	shr    eax,0x8
 8049e64:	c1 e8 08             	shr    eax,0x8
 8049e67:	e8 85 e8 ff ff       	call   80486f1 <__best_buput_one>
 8049e6c:	83 c2 02             	add    edx,0x2
 8049e6f:	49                   	dec    ecx
 8049e70:	83 f9 01             	cmp    ecx,0x1
 8049e73:	7c 1f                	jl     8049e94 <..@607._1>
 8049e75:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8049e7a:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8049e7f:	b0 20                	mov    al,0x20
 8049e81:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8049e85:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8049e8a:	83 ec 02             	sub    esp,0x2
 8049e8d:	e8 3c ef ff ff       	call   8048dce <__best_cput+0x2>
 8049e92:	eb bb                	jmp    8049e4f <..@607._2>

08049e94 <..@607._1>:
 8049e94:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8049e99:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8049e9e:	b0 0a                	mov    al,0xa
 8049ea0:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8049ea4:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8049ea9:	83 ec 02             	sub    esp,0x2
 8049eac:	e8 1d ef ff ff       	call   8048dce <__best_cput+0x2>
 8049eb1:	61                   	popa   
 8049eb2:	89 c8                	mov    eax,ecx
 8049eb4:	bb 02 00 00 00       	mov    ebx,0x2
 8049eb9:	f7 e3                	mul    ebx
 8049ebb:	89 e3                	mov    ebx,esp
 8049ebd:	89 de                	mov    esi,ebx
 8049ebf:	89 df                	mov    edi,ebx
 8049ec1:	01 c7                	add    edi,eax
 8049ec3:	b9 28 00 00 00       	mov    ecx,0x28
 8049ec8:	01 cf                	add    edi,ecx
 8049eca:	01 ce                	add    esi,ecx
 8049ecc:	4f                   	dec    edi
 8049ecd:	4e                   	dec    esi
 8049ece:	fd                   	std    
 8049ecf:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8049ed1:	fc                   	cld    
 8049ed2:	01 c4                	add    esp,eax
 8049ed4:	61                   	popa   
 8049ed5:	83 c4 04             	add    esp,0x4
 8049ed8:	c3                   	ret    

08049ed9 <__best_bsprint>:
 8049ed9:	6a 00                	push   0x0
 8049edb:	6a 00                	push   0x0
 8049edd:	6a 00                	push   0x0
 8049edf:	6a 00                	push   0x0
 8049ee1:	6a 00                	push   0x0
 8049ee3:	6a 00                	push   0x0
 8049ee5:	6a 00                	push   0x0
 8049ee7:	6a 00                	push   0x0
 8049ee9:	6a 00                	push   0x0
 8049eeb:	6a 00                	push   0x0
 8049eed:	6a 00                	push   0x0
 8049eef:	6a 00                	push   0x0
 8049ef1:	6a 00                	push   0x0
 8049ef3:	6a 00                	push   0x0
 8049ef5:	6a 00                	push   0x0
 8049ef7:	6a 00                	push   0x0
 8049ef9:	6a 00                	push   0x0
 8049efb:	6a 00                	push   0x0
 8049efd:	6a 00                	push   0x0
 8049eff:	6a 00                	push   0x0
 8049f01:	6a 00                	push   0x0
 8049f03:	6a 00                	push   0x0
 8049f05:	6a 00                	push   0x0
 8049f07:	6a 00                	push   0x0
 8049f09:	6a 00                	push   0x0
 8049f0b:	6a 00                	push   0x0
 8049f0d:	6a 00                	push   0x0
 8049f0f:	6a 00                	push   0x0
 8049f11:	6a 00                	push   0x0
 8049f13:	6a 00                	push   0x0
 8049f15:	6a 00                	push   0x0
 8049f17:	6a 00                	push   0x0
 8049f19:	6a 20                	push   0x20

08049f1b <..@618._1>:
 8049f1b:	bd 00 00 00 00       	mov    ebp,0x0
 8049f20:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 8049f24:	75 08                	jne    8049f2e <..@618._2>
 8049f26:	ff 0c 24             	dec    DWORD PTR [esp]
 8049f29:	8f 04 24             	pop    DWORD PTR [esp]
 8049f2c:	eb ed                	jmp    8049f1b <..@618._1>

08049f2e <..@618._2>:
 8049f2e:	60                   	pusha  
 8049f2f:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8049f33:	89 e2                	mov    edx,esp
 8049f35:	83 c2 28             	add    edx,0x28
 8049f38:	89 cb                	mov    ebx,ecx
 8049f3a:	90                   	nop
 8049f3b:	60                   	pusha  
 8049f3c:	89 d9                	mov    ecx,ebx

08049f3e <..@617._2>:
 8049f3e:	83 f9 01             	cmp    ecx,0x1
 8049f41:	7c 40                	jl     8049f83 <..@617._1>
 8049f43:	b8 00 00 00 00       	mov    eax,0x0
 8049f48:	8b 02                	mov    eax,DWORD PTR [edx]
 8049f4a:	c1 e0 08             	shl    eax,0x8
 8049f4d:	c1 e0 08             	shl    eax,0x8
 8049f50:	c1 e8 08             	shr    eax,0x8
 8049f53:	c1 e8 08             	shr    eax,0x8
 8049f56:	e8 9c e7 ff ff       	call   80486f7 <__best_bsput_one>
 8049f5b:	83 c2 02             	add    edx,0x2
 8049f5e:	49                   	dec    ecx
 8049f5f:	83 f9 01             	cmp    ecx,0x1
 8049f62:	7c 1f                	jl     8049f83 <..@617._1>
 8049f64:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8049f69:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8049f6e:	b0 20                	mov    al,0x20
 8049f70:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8049f74:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8049f79:	83 ec 02             	sub    esp,0x2
 8049f7c:	e8 4d ee ff ff       	call   8048dce <__best_cput+0x2>
 8049f81:	eb bb                	jmp    8049f3e <..@617._2>

08049f83 <..@617._1>:
 8049f83:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8049f88:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 8049f8d:	b0 0a                	mov    al,0xa
 8049f8f:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8049f93:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 8049f98:	83 ec 02             	sub    esp,0x2
 8049f9b:	e8 2e ee ff ff       	call   8048dce <__best_cput+0x2>
 8049fa0:	61                   	popa   
 8049fa1:	89 c8                	mov    eax,ecx
 8049fa3:	bb 02 00 00 00       	mov    ebx,0x2
 8049fa8:	f7 e3                	mul    ebx
 8049faa:	89 e3                	mov    ebx,esp
 8049fac:	89 de                	mov    esi,ebx
 8049fae:	89 df                	mov    edi,ebx
 8049fb0:	01 c7                	add    edi,eax
 8049fb2:	b9 28 00 00 00       	mov    ecx,0x28
 8049fb7:	01 cf                	add    edi,ecx
 8049fb9:	01 ce                	add    esi,ecx
 8049fbb:	4f                   	dec    edi
 8049fbc:	4e                   	dec    esi
 8049fbd:	fd                   	std    
 8049fbe:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8049fc0:	fc                   	cld    
 8049fc1:	01 c4                	add    esp,eax
 8049fc3:	61                   	popa   
 8049fc4:	83 c4 04             	add    esp,0x4
 8049fc7:	c3                   	ret    

08049fc8 <__best_cprint>:
 8049fc8:	6a 00                	push   0x0
 8049fca:	6a 00                	push   0x0
 8049fcc:	6a 00                	push   0x0
 8049fce:	6a 00                	push   0x0
 8049fd0:	6a 00                	push   0x0
 8049fd2:	6a 00                	push   0x0
 8049fd4:	6a 00                	push   0x0
 8049fd6:	6a 00                	push   0x0
 8049fd8:	6a 00                	push   0x0
 8049fda:	6a 00                	push   0x0
 8049fdc:	6a 00                	push   0x0
 8049fde:	6a 00                	push   0x0
 8049fe0:	6a 00                	push   0x0
 8049fe2:	6a 00                	push   0x0
 8049fe4:	6a 00                	push   0x0
 8049fe6:	6a 00                	push   0x0
 8049fe8:	6a 00                	push   0x0
 8049fea:	6a 00                	push   0x0
 8049fec:	6a 00                	push   0x0
 8049fee:	6a 00                	push   0x0
 8049ff0:	6a 00                	push   0x0
 8049ff2:	6a 00                	push   0x0
 8049ff4:	6a 00                	push   0x0
 8049ff6:	6a 00                	push   0x0
 8049ff8:	6a 00                	push   0x0
 8049ffa:	6a 00                	push   0x0
 8049ffc:	6a 00                	push   0x0
 8049ffe:	6a 00                	push   0x0
 804a000:	6a 00                	push   0x0
 804a002:	6a 00                	push   0x0
 804a004:	6a 00                	push   0x0
 804a006:	6a 00                	push   0x0
 804a008:	6a 20                	push   0x20

0804a00a <..@628._1>:
 804a00a:	bd 00 00 00 00       	mov    ebp,0x0
 804a00f:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 804a013:	75 08                	jne    804a01d <..@628._2>
 804a015:	ff 0c 24             	dec    DWORD PTR [esp]
 804a018:	8f 04 24             	pop    DWORD PTR [esp]
 804a01b:	eb ed                	jmp    804a00a <..@628._1>

0804a01d <..@628._2>:
 804a01d:	60                   	pusha  
 804a01e:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 804a022:	89 e2                	mov    edx,esp
 804a024:	83 c2 28             	add    edx,0x28
 804a027:	89 cb                	mov    ebx,ecx
 804a029:	90                   	nop
 804a02a:	60                   	pusha  
 804a02b:	89 d9                	mov    ecx,ebx

0804a02d <..@627._2>:
 804a02d:	83 f9 01             	cmp    ecx,0x1
 804a030:	7c 40                	jl     804a072 <..@627._1>
 804a032:	b8 00 00 00 00       	mov    eax,0x0
 804a037:	8b 02                	mov    eax,DWORD PTR [edx]
 804a039:	c1 e0 08             	shl    eax,0x8
 804a03c:	c1 e0 08             	shl    eax,0x8
 804a03f:	c1 e8 08             	shr    eax,0x8
 804a042:	c1 e8 08             	shr    eax,0x8
 804a045:	e8 e9 e6 ff ff       	call   8048733 <__best_cput_one>
 804a04a:	83 c2 02             	add    edx,0x2
 804a04d:	49                   	dec    ecx
 804a04e:	83 f9 01             	cmp    ecx,0x1
 804a051:	7c 1f                	jl     804a072 <..@627._1>
 804a053:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804a058:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 804a05d:	b0 20                	mov    al,0x20
 804a05f:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804a063:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 804a068:	83 ec 02             	sub    esp,0x2
 804a06b:	e8 5e ed ff ff       	call   8048dce <__best_cput+0x2>
 804a070:	eb bb                	jmp    804a02d <..@627._2>

0804a072 <..@627._1>:
 804a072:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804a077:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 804a07c:	b0 0a                	mov    al,0xa
 804a07e:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804a082:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 804a087:	83 ec 02             	sub    esp,0x2
 804a08a:	e8 3f ed ff ff       	call   8048dce <__best_cput+0x2>
 804a08f:	61                   	popa   
 804a090:	89 c8                	mov    eax,ecx
 804a092:	bb 02 00 00 00       	mov    ebx,0x2
 804a097:	f7 e3                	mul    ebx
 804a099:	89 e3                	mov    ebx,esp
 804a09b:	89 de                	mov    esi,ebx
 804a09d:	89 df                	mov    edi,ebx
 804a09f:	01 c7                	add    edi,eax
 804a0a1:	b9 28 00 00 00       	mov    ecx,0x28
 804a0a6:	01 cf                	add    edi,ecx
 804a0a8:	01 ce                	add    esi,ecx
 804a0aa:	4f                   	dec    edi
 804a0ab:	4e                   	dec    esi
 804a0ac:	fd                   	std    
 804a0ad:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 804a0af:	fc                   	cld    
 804a0b0:	01 c4                	add    esp,eax
 804a0b2:	61                   	popa   
 804a0b3:	83 c4 04             	add    esp,0x4
 804a0b6:	c3                   	ret    

0804a0b7 <__best_sprint>:
 804a0b7:	6a 00                	push   0x0
 804a0b9:	6a 00                	push   0x0
 804a0bb:	6a 00                	push   0x0
 804a0bd:	6a 00                	push   0x0
 804a0bf:	6a 00                	push   0x0
 804a0c1:	6a 00                	push   0x0
 804a0c3:	6a 00                	push   0x0
 804a0c5:	6a 00                	push   0x0
 804a0c7:	6a 00                	push   0x0
 804a0c9:	6a 00                	push   0x0
 804a0cb:	6a 00                	push   0x0
 804a0cd:	6a 00                	push   0x0
 804a0cf:	6a 00                	push   0x0
 804a0d1:	6a 00                	push   0x0
 804a0d3:	6a 00                	push   0x0
 804a0d5:	6a 00                	push   0x0
 804a0d7:	6a 00                	push   0x0
 804a0d9:	6a 00                	push   0x0
 804a0db:	6a 00                	push   0x0
 804a0dd:	6a 00                	push   0x0
 804a0df:	6a 00                	push   0x0
 804a0e1:	6a 00                	push   0x0
 804a0e3:	6a 00                	push   0x0
 804a0e5:	6a 00                	push   0x0
 804a0e7:	6a 00                	push   0x0
 804a0e9:	6a 00                	push   0x0
 804a0eb:	6a 00                	push   0x0
 804a0ed:	6a 00                	push   0x0
 804a0ef:	6a 00                	push   0x0
 804a0f1:	6a 00                	push   0x0
 804a0f3:	6a 00                	push   0x0
 804a0f5:	6a 00                	push   0x0
 804a0f7:	6a 20                	push   0x20

0804a0f9 <..@638._1>:
 804a0f9:	bd 00 00 00 00       	mov    ebp,0x0
 804a0fe:	39 6c 24 04          	cmp    DWORD PTR [esp+0x4],ebp
 804a102:	75 08                	jne    804a10c <..@638._2>
 804a104:	ff 0c 24             	dec    DWORD PTR [esp]
 804a107:	8f 04 24             	pop    DWORD PTR [esp]
 804a10a:	eb ed                	jmp    804a0f9 <..@638._1>

0804a10c <..@638._2>:
 804a10c:	60                   	pusha  
 804a10d:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 804a111:	89 e2                	mov    edx,esp
 804a113:	83 c2 28             	add    edx,0x28
 804a116:	89 cb                	mov    ebx,ecx
 804a118:	8b 54 24 24          	mov    edx,DWORD PTR [esp+0x24]
 804a11c:	01 4c 24 24          	add    DWORD PTR [esp+0x24],ecx
 804a120:	b9 00 00 00 00       	mov    ecx,0x0
 804a125:	60                   	pusha  
 804a126:	89 d9                	mov    ecx,ebx

0804a128 <..@637._2>:
 804a128:	83 f9 01             	cmp    ecx,0x1
 804a12b:	7c 29                	jl     804a156 <..@637._1>
 804a12d:	b8 00 00 00 00       	mov    eax,0x0
 804a132:	8b 02                	mov    eax,DWORD PTR [edx]
 804a134:	c1 e0 08             	shl    eax,0x8
 804a137:	c1 e0 08             	shl    eax,0x8
 804a13a:	c1 e0 08             	shl    eax,0x8
 804a13d:	c1 e8 08             	shr    eax,0x8
 804a140:	c1 e8 08             	shr    eax,0x8
 804a143:	c1 e8 08             	shr    eax,0x8
 804a146:	e8 03 e6 ff ff       	call   804874e <__best_sput_one>
 804a14b:	83 c2 01             	add    edx,0x1
 804a14e:	49                   	dec    ecx
 804a14f:	83 f9 01             	cmp    ecx,0x1
 804a152:	7c 02                	jl     804a156 <..@637._1>
 804a154:	eb d2                	jmp    804a128 <..@637._2>

0804a156 <..@637._1>:
 804a156:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804a15b:	a3 02 b3 04 08       	mov    ds:0x804b302,eax
 804a160:	b0 0a                	mov    al,0xa
 804a162:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804a166:	a1 02 b3 04 08       	mov    eax,ds:0x804b302
 804a16b:	83 ec 02             	sub    esp,0x2
 804a16e:	e8 5b ec ff ff       	call   8048dce <__best_cput+0x2>
 804a173:	61                   	popa   
 804a174:	89 c8                	mov    eax,ecx
 804a176:	bb 01 00 00 00       	mov    ebx,0x1
 804a17b:	f7 e3                	mul    ebx
 804a17d:	89 e3                	mov    ebx,esp
 804a17f:	89 de                	mov    esi,ebx
 804a181:	89 df                	mov    edi,ebx
 804a183:	01 c7                	add    edi,eax
 804a185:	b9 28 00 00 00       	mov    ecx,0x28
 804a18a:	01 cf                	add    edi,ecx
 804a18c:	01 ce                	add    esi,ecx
 804a18e:	4f                   	dec    edi
 804a18f:	4e                   	dec    esi
 804a190:	fd                   	std    
 804a191:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 804a193:	fc                   	cld    
 804a194:	01 c4                	add    esp,eax
 804a196:	61                   	popa   
 804a197:	83 c4 04             	add    esp,0x4
 804a19a:	c3                   	ret    
 804a19b:	66 90                	xchg   ax,ax
 804a19d:	66 90                	xchg   ax,ax
 804a19f:	90                   	nop

0804a1a0 <_start>:
 804a1a0:	89 25 2e 0e 0e 08    	mov    DWORD PTR ds:0x80e0e2e,esp
 804a1a6:	eb 19                	jmp    804a1c1 <..@126._1>

0804a1a8 <..@127.__jup>:
 804a1a8:	39 25 2e 0e 0e 08    	cmp    DWORD PTR ds:0x80e0e2e,esp
 804a1ae:	74 00                	je     804a1b0 <..@126._2>

0804a1b0 <..@126._2>:
 804a1b0:	b8 01 00 00 00       	mov    eax,0x1
 804a1b5:	bb 00 00 00 00       	mov    ebx,0x0
 804a1ba:	cd 80                	int    0x80
 804a1bc:	e9 15 01 00 00       	jmp    804a2d6 <..@127.__jdown>

0804a1c1 <..@126._1>:
 804a1c1:	e9 e0 00 00 00       	jmp    804a2a6 <..@133.__jdown>

0804a1c6 <fact>:
 804a1c6:	68 d8 a1 04 08       	push   0x804a1d8
 804a1cb:	6a 07                	push   0x7
 804a1cd:	ff 35 2e 0e 0e 08    	push   DWORD PTR ds:0x80e0e2e
 804a1d3:	e9 a8 de ff ff       	jmp    8048080 <macro_regout>

0804a1d8 <..@134._1>:
 804a1d8:	c7 05 16 6e 0c 08 00 	mov    DWORD PTR ds:0x80c6e16,0x0
 804a1df:	00 00 00 
 804a1e2:	c7 05 1a 6e 0c 08 00 	mov    DWORD PTR ds:0x80c6e1a,0x0
 804a1e9:	00 00 00 
 804a1ec:	c7 05 1e 6e 0c 08 00 	mov    DWORD PTR ds:0x80c6e1e,0x0
 804a1f3:	00 00 00 
 804a1f6:	c7 05 22 6e 0c 08 00 	mov    DWORD PTR ds:0x80c6e22,0x0
 804a1fd:	00 00 00 
 804a200:	ff 74 24 10          	push   DWORD PTR [esp+0x10]
 804a204:	8f 05 16 6e 0c 08    	pop    DWORD PTR ds:0x80c6e16
 804a20a:	ff 74 24 0c          	push   DWORD PTR [esp+0xc]
 804a20e:	8f 05 1a 6e 0c 08    	pop    DWORD PTR ds:0x80c6e1a
 804a214:	ff 74 24 08          	push   DWORD PTR [esp+0x8]
 804a218:	8f 05 1e 6e 0c 08    	pop    DWORD PTR ds:0x80c6e1e
 804a21e:	ff 74 24 04          	push   DWORD PTR [esp+0x4]
 804a222:	8f 05 22 6e 0c 08    	pop    DWORD PTR ds:0x80c6e22
 804a228:	60                   	pusha  
 804a229:	a1 16 6e 0c 08       	mov    eax,ds:0x80c6e16
 804a22e:	8b 1d 1a 6e 0c 08    	mov    ebx,DWORD PTR ds:0x80c6e1a
 804a234:	8b 0d 1e 6e 0c 08    	mov    ecx,DWORD PTR ds:0x80c6e1e
 804a23a:	8b 15 22 6e 0c 08    	mov    edx,DWORD PTR ds:0x80c6e22
 804a240:	be 00 00 00 00       	mov    esi,0x0
 804a245:	bf 00 00 00 00       	mov    edi,0x0
 804a24a:	bd 00 00 00 00       	mov    ebp,0x0
 804a24f:	eb 41                	jmp    804a292 <..@131._2>

0804a251 <..@133.__jup>:
 804a251:	a3 16 6e 0c 08       	mov    ds:0x80c6e16,eax
 804a256:	89 1d 1a 6e 0c 08    	mov    DWORD PTR ds:0x80c6e1a,ebx
 804a25c:	89 0d 1e 6e 0c 08    	mov    DWORD PTR ds:0x80c6e1e,ecx
 804a262:	89 15 22 6e 0c 08    	mov    DWORD PTR ds:0x80c6e22,edx
 804a268:	61                   	popa   
 804a269:	ff 35 16 6e 0c 08    	push   DWORD PTR ds:0x80c6e16
 804a26f:	8f 44 24 04          	pop    DWORD PTR [esp+0x4]
 804a273:	ff 35 1a 6e 0c 08    	push   DWORD PTR ds:0x80c6e1a
 804a279:	8f 44 24 08          	pop    DWORD PTR [esp+0x8]
 804a27d:	ff 35 1e 6e 0c 08    	push   DWORD PTR ds:0x80c6e1e
 804a283:	8f 44 24 0c          	pop    DWORD PTR [esp+0xc]
 804a287:	ff 35 22 6e 0c 08    	push   DWORD PTR ds:0x80c6e22
 804a28d:	8f 44 24 10          	pop    DWORD PTR [esp+0x10]
 804a291:	c3                   	ret    

0804a292 <..@131._2>:
 804a292:	68 a4 a2 04 08       	push   0x804a2a4
 804a297:	6a 08                	push   0x8
 804a299:	ff 35 2e 0e 0e 08    	push   DWORD PTR ds:0x80e0e2e
 804a29f:	e9 dc dd ff ff       	jmp    8048080 <macro_regout>

0804a2a4 <..@165._1>:
 804a2a4:	eb ab                	jmp    804a251 <..@133.__jup>

0804a2a6 <..@133.__jdown>:
 804a2a6:	68 b8 a2 04 08       	push   0x804a2b8
 804a2ab:	6a 14                	push   0x14
 804a2ad:	ff 35 2e 0e 0e 08    	push   DWORD PTR ds:0x80e0e2e
 804a2b3:	e9 c8 dd ff ff       	jmp    8048080 <macro_regout>

0804a2b8 <..@167._1>:
 804a2b8:	68 c6 a1 04 08       	push   0x804a1c6
 804a2bd:	6a 00                	push   0x0
 804a2bf:	6a 00                	push   0x0
 804a2c1:	6a 00                	push   0x0
 804a2c3:	e8 fe fe ff ff       	call   804a1c6 <fact>
 804a2c8:	83 c4 10             	add    esp,0x10
 804a2cb:	50                   	push   eax
 804a2cc:	e8 77 f7 ff ff       	call   8049a48 <__best_duprint+0x2>
 804a2d1:	e9 d2 fe ff ff       	jmp    804a1a8 <..@127.__jup>
