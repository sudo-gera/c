
a.out:     file format elf32-i386


Disassembly of section .text:

08048080 <macro_pr_jmp>:
 8048080:	83 c4 08             	add    esp,0x8
 8048083:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]
 8048087:	e9 04 5e 00 00       	jmp    804de90 <..@188.__jdown>

0804808c <macro_ops>:
 804808c:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8048093:	00 00 00 
 8048096:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804809d:	00 00 00 
 80480a0:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 80480a7:	00 00 00 
 80480aa:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 80480b1:	00 00 00 
 80480b4:	ff 74 24 10          	push   DWORD PTR [esp+0x10]
 80480b8:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 80480be:	ff 74 24 0c          	push   DWORD PTR [esp+0xc]
 80480c2:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 80480c8:	ff 74 24 08          	push   DWORD PTR [esp+0x8]
 80480cc:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 80480d2:	ff 74 24 04          	push   DWORD PTR [esp+0x4]
 80480d6:	8f 05 0e 29 05 08    	pop    DWORD PTR ds:0x805290e
 80480dc:	60                   	pusha  
 80480dd:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 80480e2:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 80480e8:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 80480ee:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 80480f4:	be 00 00 00 00       	mov    esi,0x0
 80480f9:	bf 00 00 00 00       	mov    edi,0x0
 80480fe:	bd 00 00 00 00       	mov    ebp,0x0
 8048103:	eb 41                	jmp    8048146 <..@186._2>

08048105 <..@188.__jup>:
 8048105:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804810a:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8048110:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048116:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804811c:	61                   	popa   
 804811d:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 8048123:	8f 44 24 04          	pop    DWORD PTR [esp+0x4]
 8048127:	ff 35 06 29 05 08    	push   DWORD PTR ds:0x8052906
 804812d:	8f 44 24 08          	pop    DWORD PTR [esp+0x8]
 8048131:	ff 35 0a 29 05 08    	push   DWORD PTR ds:0x805290a
 8048137:	8f 44 24 0c          	pop    DWORD PTR [esp+0xc]
 804813b:	ff 35 0e 29 05 08    	push   DWORD PTR ds:0x805290e
 8048141:	8f 44 24 10          	pop    DWORD PTR [esp+0x10]
 8048145:	c3                   	ret    

08048146 <..@186._2>:
 8048146:	89 da                	mov    edx,ebx

08048148 <_________macro_ops_for_begin8>:
 8048148:	39 c2                	cmp    edx,eax
 804814a:	0f 86 7a 0b 00 00    	jbe    8048cca <_________macro_ops_for_end8>
 8048150:	83 ea 0c             	sub    edx,0xc
 8048153:	68 62 81 04 08       	push   0x8048162
 8048158:	68 8f 00 00 00       	push   0x8f
 804815d:	e9 1e ff ff ff       	jmp    8048080 <macro_pr_jmp>

08048162 <..@219._1>:
 8048162:	83 3a 02             	cmp    DWORD PTR [edx],0x2
 8048165:	0f 85 5a 0b 00 00    	jne    8048cc5 <_________macro_ops_end8>
 804816b:	8b 6a 04             	mov    ebp,DWORD PTR [edx+0x4]
 804816e:	83 fd 2a             	cmp    ebp,0x2a
 8048171:	0f 85 cc 03 00 00    	jne    8048543 <_________macro_ops_not8_1>
 8048177:	89 d5                	mov    ebp,edx
 8048179:	83 ed 0c             	sub    ebp,0xc
 804817c:	39 e8                	cmp    eax,ebp
 804817e:	77 0a                	ja     804818a <_________macro_ops_un8_1>
 8048180:	83 7a f4 02          	cmp    DWORD PTR [edx-0xc],0x2
 8048184:	0f 85 b4 03 00 00    	jne    804853e <_________macro_ops_bin8_1>

0804818a <_________macro_ops_un8_1>:
 804818a:	60                   	pusha  
 804818b:	8b 42 10             	mov    eax,DWORD PTR [edx+0x10]
 804818e:	8b 18                	mov    ebx,DWORD PTR [eax]
 8048190:	89 5a 10             	mov    DWORD PTR [edx+0x10],ebx
 8048193:	89 42 0c             	mov    DWORD PTR [edx+0xc],eax
 8048196:	c7 42 14 04 00 00 00 	mov    DWORD PTR [edx+0x14],0x4
 804819d:	61                   	popa   
 804819e:	6a 00                	push   0x0
 80481a0:	5e                   	pop    esi
 80481a1:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 80481a8:	00 00 00 
 80481ab:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 80481b2:	00 00 00 
 80481b5:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 80481bc:	00 00 00 
 80481bf:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 80481c6:	00 00 00 
 80481c9:	56                   	push   esi
 80481ca:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 80481d0:	6a 01                	push   0x1
 80481d2:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 80481d8:	60                   	pusha  
 80481d9:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 80481de:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 80481e4:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 80481ea:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 80481f0:	be 00 00 00 00       	mov    esi,0x0
 80481f5:	bf 00 00 00 00       	mov    edi,0x0
 80481fa:	bd 00 00 00 00       	mov    ebp,0x0
 80481ff:	29 d8                	sub    eax,ebx
 8048201:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8048206:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804820c:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048212:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8048218:	61                   	popa   
 8048219:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804821f:	5e                   	pop    esi

08048220 <..@225.__jup>:
 8048220:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8048227:	00 00 00 
 804822a:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8048231:	00 00 00 
 8048234:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804823b:	00 00 00 
 804823e:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8048245:	00 00 00 
 8048248:	56                   	push   esi
 8048249:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804824f:	6a 01                	push   0x1
 8048251:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8048257:	60                   	pusha  
 8048258:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804825d:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8048263:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8048269:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804826f:	be 00 00 00 00       	mov    esi,0x0
 8048274:	bf 00 00 00 00       	mov    edi,0x0
 8048279:	bd 00 00 00 00       	mov    ebp,0x0
 804827e:	01 d8                	add    eax,ebx
 8048280:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8048285:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804828b:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048291:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8048297:	61                   	popa   
 8048298:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804829e:	5e                   	pop    esi
 804829f:	68 eb 83 04 08       	push   0x80483eb
 80482a4:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 80482ab:	00 00 00 
 80482ae:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 80482b5:	00 00 00 
 80482b8:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 80482bf:	00 00 00 
 80482c2:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 80482c9:	00 00 00 
 80482cc:	6a 01                	push   0x1
 80482ce:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 80482d4:	6a 00                	push   0x0
 80482d6:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 80482dc:	60                   	pusha  
 80482dd:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 80482e2:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 80482e8:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 80482ee:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 80482f4:	be 00 00 00 00       	mov    esi,0x0
 80482f9:	bf 00 00 00 00       	mov    edi,0x0
 80482fe:	bd 00 00 00 00       	mov    ebp,0x0
 8048303:	39 d8                	cmp    eax,ebx
 8048305:	7c 1d                	jl     8048324 <..@262._jmp>
 8048307:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804830c:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8048312:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048318:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804831e:	61                   	popa   
 804831f:	83 c4 04             	add    esp,0x4
 8048322:	eb 1f                	jmp    8048343 <..@262._end>

08048324 <..@262._jmp>:
 8048324:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8048329:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804832f:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048335:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804833b:	61                   	popa   
 804833c:	83 c4 04             	add    esp,0x4
 804833f:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

08048343 <..@262._end>:
 8048343:	68 3b 85 04 08       	push   0x804853b
 8048348:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804834f:	00 00 00 
 8048352:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8048359:	00 00 00 
 804835c:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8048363:	00 00 00 
 8048366:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804836d:	00 00 00 
 8048370:	56                   	push   esi
 8048371:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8048377:	6a 01                	push   0x1
 8048379:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804837f:	60                   	pusha  
 8048380:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8048385:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804838b:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8048391:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8048397:	be 00 00 00 00       	mov    esi,0x0
 804839c:	bf 00 00 00 00       	mov    edi,0x0
 80483a1:	bd 00 00 00 00       	mov    ebp,0x0
 80483a6:	39 d8                	cmp    eax,ebx
 80483a8:	73 1d                	jae    80483c7 <..@279._jmp>
 80483aa:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 80483af:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 80483b5:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 80483bb:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 80483c1:	61                   	popa   
 80483c2:	83 c4 04             	add    esp,0x4
 80483c5:	eb 1f                	jmp    80483e6 <..@279._end>

080483c7 <..@279._jmp>:
 80483c7:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 80483cc:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 80483d2:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 80483d8:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 80483de:	61                   	popa   
 80483df:	83 c4 04             	add    esp,0x4
 80483e2:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

080483e6 <..@279._end>:
 80483e6:	e9 a3 00 00 00       	jmp    804848e <..@224._end>

080483eb <..@224._less>:
 80483eb:	68 3b 85 04 08       	push   0x804853b
 80483f0:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 80483f7:	00 00 00 
 80483fa:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8048401:	00 00 00 
 8048404:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804840b:	00 00 00 
 804840e:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8048415:	00 00 00 
 8048418:	56                   	push   esi
 8048419:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804841f:	6a 01                	push   0x1
 8048421:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8048427:	60                   	pusha  
 8048428:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804842d:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8048433:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8048439:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804843f:	be 00 00 00 00       	mov    esi,0x0
 8048444:	bf 00 00 00 00       	mov    edi,0x0
 8048449:	bd 00 00 00 00       	mov    ebp,0x0
 804844e:	39 d8                	cmp    eax,ebx
 8048450:	76 1d                	jbe    804846f <..@296._jmp>
 8048452:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8048457:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804845d:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048463:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8048469:	61                   	popa   
 804846a:	83 c4 04             	add    esp,0x4
 804846d:	eb 1f                	jmp    804848e <..@224._end>

0804846f <..@296._jmp>:
 804846f:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8048474:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804847a:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048480:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8048486:	61                   	popa   
 8048487:	83 c4 04             	add    esp,0x4
 804848a:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804848e <..@224._end>:
 804848e:	89 d7                	mov    edi,edx
 8048490:	83 c7 0c             	add    edi,0xc
 8048493:	89 cd                	mov    ebp,ecx
 8048495:	29 fd                	sub    ebp,edi
 8048497:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804849e:	00 00 00 
 80484a1:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 80484a8:	00 00 00 
 80484ab:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 80484b2:	00 00 00 
 80484b5:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 80484bc:	00 00 00 
 80484bf:	52                   	push   edx
 80484c0:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 80484c6:	57                   	push   edi
 80484c7:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 80484cd:	55                   	push   ebp
 80484ce:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 80484d4:	60                   	pusha  
 80484d5:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 80484da:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 80484e0:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 80484e6:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 80484ec:	be 00 00 00 00       	mov    esi,0x0
 80484f1:	bf 00 00 00 00       	mov    edi,0x0
 80484f6:	bd 00 00 00 00       	mov    ebp,0x0
 80484fb:	39 d8                	cmp    eax,ebx
 80484fd:	72 0e                	jb     804850d <..@312.left>
 80484ff:	01 c8                	add    eax,ecx
 8048501:	01 cb                	add    ebx,ecx

08048503 <..@312.right>:
 8048503:	48                   	dec    eax
 8048504:	4b                   	dec    ebx
 8048505:	8b 13                	mov    edx,DWORD PTR [ebx]
 8048507:	89 10                	mov    DWORD PTR [eax],edx
 8048509:	e2 f8                	loop   8048503 <..@312.right>
 804850b:	eb 08                	jmp    8048515 <..@312.end>

0804850d <..@312.left>:
 804850d:	8b 13                	mov    edx,DWORD PTR [ebx]
 804850f:	89 10                	mov    DWORD PTR [eax],edx
 8048511:	40                   	inc    eax
 8048512:	43                   	inc    ebx
 8048513:	e2 f8                	loop   804850d <..@312.left>

08048515 <..@312.end>:
 8048515:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804851a:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8048520:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048526:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804852c:	61                   	popa   
 804852d:	83 e9 0c             	sub    ecx,0xc
 8048530:	83 eb 0c             	sub    ebx,0xc
 8048533:	83 ea 0c             	sub    edx,0xc
 8048536:	e9 e5 fc ff ff       	jmp    8048220 <..@225.__jup>

0804853b <..@225.__jdown>:
 804853b:	83 c2 0c             	add    edx,0xc

0804853e <_________macro_ops_bin8_1>:
 804853e:	e9 82 07 00 00       	jmp    8048cc5 <_________macro_ops_end8>

08048543 <_________macro_ops_not8_1>:
 8048543:	83 fd 2d             	cmp    ebp,0x2d
 8048546:	0f 85 bb 03 00 00    	jne    8048907 <_________macro_ops_not8_2>
 804854c:	89 d5                	mov    ebp,edx
 804854e:	83 ed 0c             	sub    ebp,0xc
 8048551:	39 e8                	cmp    eax,ebp
 8048553:	77 0a                	ja     804855f <_________macro_ops_un8_2>
 8048555:	83 7a f4 02          	cmp    DWORD PTR [edx-0xc],0x2
 8048559:	0f 85 a3 03 00 00    	jne    8048902 <_________macro_ops_bin8_2>

0804855f <_________macro_ops_un8_2>:
 804855f:	f7 5a 10             	neg    DWORD PTR [edx+0x10]
 8048562:	6a 00                	push   0x0
 8048564:	5e                   	pop    esi
 8048565:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804856c:	00 00 00 
 804856f:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8048576:	00 00 00 
 8048579:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8048580:	00 00 00 
 8048583:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804858a:	00 00 00 
 804858d:	56                   	push   esi
 804858e:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8048594:	6a 01                	push   0x1
 8048596:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804859c:	60                   	pusha  
 804859d:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 80485a2:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 80485a8:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 80485ae:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 80485b4:	be 00 00 00 00       	mov    esi,0x0
 80485b9:	bf 00 00 00 00       	mov    edi,0x0
 80485be:	bd 00 00 00 00       	mov    ebp,0x0
 80485c3:	29 d8                	sub    eax,ebx
 80485c5:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 80485ca:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 80485d0:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 80485d6:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 80485dc:	61                   	popa   
 80485dd:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 80485e3:	5e                   	pop    esi

080485e4 <..@332.__jup>:
 80485e4:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 80485eb:	00 00 00 
 80485ee:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 80485f5:	00 00 00 
 80485f8:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 80485ff:	00 00 00 
 8048602:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8048609:	00 00 00 
 804860c:	56                   	push   esi
 804860d:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8048613:	6a 01                	push   0x1
 8048615:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804861b:	60                   	pusha  
 804861c:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8048621:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8048627:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804862d:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8048633:	be 00 00 00 00       	mov    esi,0x0
 8048638:	bf 00 00 00 00       	mov    edi,0x0
 804863d:	bd 00 00 00 00       	mov    ebp,0x0
 8048642:	01 d8                	add    eax,ebx
 8048644:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8048649:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804864f:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048655:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804865b:	61                   	popa   
 804865c:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 8048662:	5e                   	pop    esi
 8048663:	68 af 87 04 08       	push   0x80487af
 8048668:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804866f:	00 00 00 
 8048672:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8048679:	00 00 00 
 804867c:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8048683:	00 00 00 
 8048686:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804868d:	00 00 00 
 8048690:	6a 01                	push   0x1
 8048692:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8048698:	6a 00                	push   0x0
 804869a:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 80486a0:	60                   	pusha  
 80486a1:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 80486a6:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 80486ac:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 80486b2:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 80486b8:	be 00 00 00 00       	mov    esi,0x0
 80486bd:	bf 00 00 00 00       	mov    edi,0x0
 80486c2:	bd 00 00 00 00       	mov    ebp,0x0
 80486c7:	39 d8                	cmp    eax,ebx
 80486c9:	7c 1d                	jl     80486e8 <..@369._jmp>
 80486cb:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 80486d0:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 80486d6:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 80486dc:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 80486e2:	61                   	popa   
 80486e3:	83 c4 04             	add    esp,0x4
 80486e6:	eb 1f                	jmp    8048707 <..@369._end>

080486e8 <..@369._jmp>:
 80486e8:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 80486ed:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 80486f3:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 80486f9:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 80486ff:	61                   	popa   
 8048700:	83 c4 04             	add    esp,0x4
 8048703:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

08048707 <..@369._end>:
 8048707:	68 ff 88 04 08       	push   0x80488ff
 804870c:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8048713:	00 00 00 
 8048716:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804871d:	00 00 00 
 8048720:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8048727:	00 00 00 
 804872a:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8048731:	00 00 00 
 8048734:	56                   	push   esi
 8048735:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804873b:	6a 01                	push   0x1
 804873d:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8048743:	60                   	pusha  
 8048744:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8048749:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804874f:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8048755:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804875b:	be 00 00 00 00       	mov    esi,0x0
 8048760:	bf 00 00 00 00       	mov    edi,0x0
 8048765:	bd 00 00 00 00       	mov    ebp,0x0
 804876a:	39 d8                	cmp    eax,ebx
 804876c:	73 1d                	jae    804878b <..@386._jmp>
 804876e:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8048773:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8048779:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804877f:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8048785:	61                   	popa   
 8048786:	83 c4 04             	add    esp,0x4
 8048789:	eb 1f                	jmp    80487aa <..@386._end>

0804878b <..@386._jmp>:
 804878b:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8048790:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8048796:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804879c:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 80487a2:	61                   	popa   
 80487a3:	83 c4 04             	add    esp,0x4
 80487a6:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

080487aa <..@386._end>:
 80487aa:	e9 a3 00 00 00       	jmp    8048852 <..@331._end>

080487af <..@331._less>:
 80487af:	68 ff 88 04 08       	push   0x80488ff
 80487b4:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 80487bb:	00 00 00 
 80487be:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 80487c5:	00 00 00 
 80487c8:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 80487cf:	00 00 00 
 80487d2:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 80487d9:	00 00 00 
 80487dc:	56                   	push   esi
 80487dd:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 80487e3:	6a 01                	push   0x1
 80487e5:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 80487eb:	60                   	pusha  
 80487ec:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 80487f1:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 80487f7:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 80487fd:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8048803:	be 00 00 00 00       	mov    esi,0x0
 8048808:	bf 00 00 00 00       	mov    edi,0x0
 804880d:	bd 00 00 00 00       	mov    ebp,0x0
 8048812:	39 d8                	cmp    eax,ebx
 8048814:	76 1d                	jbe    8048833 <..@403._jmp>
 8048816:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804881b:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8048821:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048827:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804882d:	61                   	popa   
 804882e:	83 c4 04             	add    esp,0x4
 8048831:	eb 1f                	jmp    8048852 <..@331._end>

08048833 <..@403._jmp>:
 8048833:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8048838:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804883e:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048844:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804884a:	61                   	popa   
 804884b:	83 c4 04             	add    esp,0x4
 804884e:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

08048852 <..@331._end>:
 8048852:	89 d7                	mov    edi,edx
 8048854:	83 c7 0c             	add    edi,0xc
 8048857:	89 cd                	mov    ebp,ecx
 8048859:	29 fd                	sub    ebp,edi
 804885b:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8048862:	00 00 00 
 8048865:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804886c:	00 00 00 
 804886f:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8048876:	00 00 00 
 8048879:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8048880:	00 00 00 
 8048883:	52                   	push   edx
 8048884:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804888a:	57                   	push   edi
 804888b:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8048891:	55                   	push   ebp
 8048892:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 8048898:	60                   	pusha  
 8048899:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804889e:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 80488a4:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 80488aa:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 80488b0:	be 00 00 00 00       	mov    esi,0x0
 80488b5:	bf 00 00 00 00       	mov    edi,0x0
 80488ba:	bd 00 00 00 00       	mov    ebp,0x0
 80488bf:	39 d8                	cmp    eax,ebx
 80488c1:	72 0e                	jb     80488d1 <..@419.left>
 80488c3:	01 c8                	add    eax,ecx
 80488c5:	01 cb                	add    ebx,ecx

080488c7 <..@419.right>:
 80488c7:	48                   	dec    eax
 80488c8:	4b                   	dec    ebx
 80488c9:	8b 13                	mov    edx,DWORD PTR [ebx]
 80488cb:	89 10                	mov    DWORD PTR [eax],edx
 80488cd:	e2 f8                	loop   80488c7 <..@419.right>
 80488cf:	eb 08                	jmp    80488d9 <..@419.end>

080488d1 <..@419.left>:
 80488d1:	8b 13                	mov    edx,DWORD PTR [ebx]
 80488d3:	89 10                	mov    DWORD PTR [eax],edx
 80488d5:	40                   	inc    eax
 80488d6:	43                   	inc    ebx
 80488d7:	e2 f8                	loop   80488d1 <..@419.left>

080488d9 <..@419.end>:
 80488d9:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 80488de:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 80488e4:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 80488ea:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 80488f0:	61                   	popa   
 80488f1:	83 e9 0c             	sub    ecx,0xc
 80488f4:	83 eb 0c             	sub    ebx,0xc
 80488f7:	83 ea 0c             	sub    edx,0xc
 80488fa:	e9 e5 fc ff ff       	jmp    80485e4 <..@332.__jup>

080488ff <..@332.__jdown>:
 80488ff:	83 c2 0c             	add    edx,0xc

08048902 <_________macro_ops_bin8_2>:
 8048902:	e9 be 03 00 00       	jmp    8048cc5 <_________macro_ops_end8>

08048907 <_________macro_ops_not8_2>:
 8048907:	83 fd 2b             	cmp    ebp,0x2b
 804890a:	0f 85 b5 03 00 00    	jne    8048cc5 <_________macro_ops_end8>
 8048910:	89 d5                	mov    ebp,edx
 8048912:	83 ed 0c             	sub    ebp,0xc
 8048915:	39 e8                	cmp    eax,ebp
 8048917:	77 0a                	ja     8048923 <_________macro_ops_un8_3>
 8048919:	83 7a f4 02          	cmp    DWORD PTR [edx-0xc],0x2
 804891d:	0f 85 a0 03 00 00    	jne    8048cc3 <_________macro_ops_bin8_3>

08048923 <_________macro_ops_un8_3>:
 8048923:	6a 00                	push   0x0
 8048925:	5e                   	pop    esi
 8048926:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804892d:	00 00 00 
 8048930:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8048937:	00 00 00 
 804893a:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8048941:	00 00 00 
 8048944:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804894b:	00 00 00 
 804894e:	56                   	push   esi
 804894f:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8048955:	6a 01                	push   0x1
 8048957:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804895d:	60                   	pusha  
 804895e:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8048963:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8048969:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804896f:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8048975:	be 00 00 00 00       	mov    esi,0x0
 804897a:	bf 00 00 00 00       	mov    edi,0x0
 804897f:	bd 00 00 00 00       	mov    ebp,0x0
 8048984:	29 d8                	sub    eax,ebx
 8048986:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804898b:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8048991:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048997:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804899d:	61                   	popa   
 804899e:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 80489a4:	5e                   	pop    esi

080489a5 <..@439.__jup>:
 80489a5:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 80489ac:	00 00 00 
 80489af:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 80489b6:	00 00 00 
 80489b9:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 80489c0:	00 00 00 
 80489c3:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 80489ca:	00 00 00 
 80489cd:	56                   	push   esi
 80489ce:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 80489d4:	6a 01                	push   0x1
 80489d6:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 80489dc:	60                   	pusha  
 80489dd:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 80489e2:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 80489e8:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 80489ee:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 80489f4:	be 00 00 00 00       	mov    esi,0x0
 80489f9:	bf 00 00 00 00       	mov    edi,0x0
 80489fe:	bd 00 00 00 00       	mov    ebp,0x0
 8048a03:	01 d8                	add    eax,ebx
 8048a05:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8048a0a:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8048a10:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048a16:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8048a1c:	61                   	popa   
 8048a1d:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 8048a23:	5e                   	pop    esi
 8048a24:	68 70 8b 04 08       	push   0x8048b70
 8048a29:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8048a30:	00 00 00 
 8048a33:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8048a3a:	00 00 00 
 8048a3d:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8048a44:	00 00 00 
 8048a47:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8048a4e:	00 00 00 
 8048a51:	6a 01                	push   0x1
 8048a53:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8048a59:	6a 00                	push   0x0
 8048a5b:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8048a61:	60                   	pusha  
 8048a62:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8048a67:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8048a6d:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8048a73:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8048a79:	be 00 00 00 00       	mov    esi,0x0
 8048a7e:	bf 00 00 00 00       	mov    edi,0x0
 8048a83:	bd 00 00 00 00       	mov    ebp,0x0
 8048a88:	39 d8                	cmp    eax,ebx
 8048a8a:	7c 1d                	jl     8048aa9 <..@476._jmp>
 8048a8c:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8048a91:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8048a97:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048a9d:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8048aa3:	61                   	popa   
 8048aa4:	83 c4 04             	add    esp,0x4
 8048aa7:	eb 1f                	jmp    8048ac8 <..@476._end>

08048aa9 <..@476._jmp>:
 8048aa9:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8048aae:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8048ab4:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048aba:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8048ac0:	61                   	popa   
 8048ac1:	83 c4 04             	add    esp,0x4
 8048ac4:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

08048ac8 <..@476._end>:
 8048ac8:	68 c0 8c 04 08       	push   0x8048cc0
 8048acd:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8048ad4:	00 00 00 
 8048ad7:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8048ade:	00 00 00 
 8048ae1:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8048ae8:	00 00 00 
 8048aeb:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8048af2:	00 00 00 
 8048af5:	56                   	push   esi
 8048af6:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8048afc:	6a 01                	push   0x1
 8048afe:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8048b04:	60                   	pusha  
 8048b05:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8048b0a:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8048b10:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8048b16:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8048b1c:	be 00 00 00 00       	mov    esi,0x0
 8048b21:	bf 00 00 00 00       	mov    edi,0x0
 8048b26:	bd 00 00 00 00       	mov    ebp,0x0
 8048b2b:	39 d8                	cmp    eax,ebx
 8048b2d:	73 1d                	jae    8048b4c <..@493._jmp>
 8048b2f:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8048b34:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8048b3a:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048b40:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8048b46:	61                   	popa   
 8048b47:	83 c4 04             	add    esp,0x4
 8048b4a:	eb 1f                	jmp    8048b6b <..@493._end>

08048b4c <..@493._jmp>:
 8048b4c:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8048b51:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8048b57:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048b5d:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8048b63:	61                   	popa   
 8048b64:	83 c4 04             	add    esp,0x4
 8048b67:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

08048b6b <..@493._end>:
 8048b6b:	e9 a3 00 00 00       	jmp    8048c13 <..@438._end>

08048b70 <..@438._less>:
 8048b70:	68 c0 8c 04 08       	push   0x8048cc0
 8048b75:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8048b7c:	00 00 00 
 8048b7f:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8048b86:	00 00 00 
 8048b89:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8048b90:	00 00 00 
 8048b93:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8048b9a:	00 00 00 
 8048b9d:	56                   	push   esi
 8048b9e:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8048ba4:	6a 01                	push   0x1
 8048ba6:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8048bac:	60                   	pusha  
 8048bad:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8048bb2:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8048bb8:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8048bbe:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8048bc4:	be 00 00 00 00       	mov    esi,0x0
 8048bc9:	bf 00 00 00 00       	mov    edi,0x0
 8048bce:	bd 00 00 00 00       	mov    ebp,0x0
 8048bd3:	39 d8                	cmp    eax,ebx
 8048bd5:	76 1d                	jbe    8048bf4 <..@510._jmp>
 8048bd7:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8048bdc:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8048be2:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048be8:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8048bee:	61                   	popa   
 8048bef:	83 c4 04             	add    esp,0x4
 8048bf2:	eb 1f                	jmp    8048c13 <..@438._end>

08048bf4 <..@510._jmp>:
 8048bf4:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8048bf9:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8048bff:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048c05:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8048c0b:	61                   	popa   
 8048c0c:	83 c4 04             	add    esp,0x4
 8048c0f:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

08048c13 <..@438._end>:
 8048c13:	89 d7                	mov    edi,edx
 8048c15:	83 c7 0c             	add    edi,0xc
 8048c18:	89 cd                	mov    ebp,ecx
 8048c1a:	29 fd                	sub    ebp,edi
 8048c1c:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8048c23:	00 00 00 
 8048c26:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8048c2d:	00 00 00 
 8048c30:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8048c37:	00 00 00 
 8048c3a:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8048c41:	00 00 00 
 8048c44:	52                   	push   edx
 8048c45:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8048c4b:	57                   	push   edi
 8048c4c:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8048c52:	55                   	push   ebp
 8048c53:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 8048c59:	60                   	pusha  
 8048c5a:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8048c5f:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8048c65:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8048c6b:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8048c71:	be 00 00 00 00       	mov    esi,0x0
 8048c76:	bf 00 00 00 00       	mov    edi,0x0
 8048c7b:	bd 00 00 00 00       	mov    ebp,0x0
 8048c80:	39 d8                	cmp    eax,ebx
 8048c82:	72 0e                	jb     8048c92 <..@526.left>
 8048c84:	01 c8                	add    eax,ecx
 8048c86:	01 cb                	add    ebx,ecx

08048c88 <..@526.right>:
 8048c88:	48                   	dec    eax
 8048c89:	4b                   	dec    ebx
 8048c8a:	8b 13                	mov    edx,DWORD PTR [ebx]
 8048c8c:	89 10                	mov    DWORD PTR [eax],edx
 8048c8e:	e2 f8                	loop   8048c88 <..@526.right>
 8048c90:	eb 08                	jmp    8048c9a <..@526.end>

08048c92 <..@526.left>:
 8048c92:	8b 13                	mov    edx,DWORD PTR [ebx]
 8048c94:	89 10                	mov    DWORD PTR [eax],edx
 8048c96:	40                   	inc    eax
 8048c97:	43                   	inc    ebx
 8048c98:	e2 f8                	loop   8048c92 <..@526.left>

08048c9a <..@526.end>:
 8048c9a:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8048c9f:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8048ca5:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048cab:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8048cb1:	61                   	popa   
 8048cb2:	83 e9 0c             	sub    ecx,0xc
 8048cb5:	83 eb 0c             	sub    ebx,0xc
 8048cb8:	83 ea 0c             	sub    edx,0xc
 8048cbb:	e9 e5 fc ff ff       	jmp    80489a5 <..@439.__jup>

08048cc0 <..@439.__jdown>:
 8048cc0:	83 c2 0c             	add    edx,0xc

08048cc3 <_________macro_ops_bin8_3>:
 8048cc3:	eb 00                	jmp    8048cc5 <_________macro_ops_end8>

08048cc5 <_________macro_ops_end8>:
 8048cc5:	e9 7e f4 ff ff       	jmp    8048148 <_________macro_ops_for_begin8>

08048cca <_________macro_ops_for_end8>:
 8048cca:	89 c2                	mov    edx,eax

08048ccc <_________macro_ops_for_begin1>:
 8048ccc:	39 da                	cmp    edx,ebx
 8048cce:	0f 83 3c 0c 00 00    	jae    8049910 <_________macro_ops_for_end1>
 8048cd4:	68 e3 8c 04 08       	push   0x8048ce3
 8048cd9:	68 ce 00 00 00       	push   0xce
 8048cde:	e9 9d f3 ff ff       	jmp    8048080 <macro_pr_jmp>

08048ce3 <..@543._1>:
 8048ce3:	83 3a 02             	cmp    DWORD PTR [edx],0x2
 8048ce6:	0f 85 1c 0c 00 00    	jne    8049908 <_________macro_ops_end1>
 8048cec:	8b 6a 04             	mov    ebp,DWORD PTR [edx+0x4]
 8048cef:	83 fd 2a             	cmp    ebp,0x2a
 8048cf2:	0f 85 b1 03 00 00    	jne    80490a9 <_________macro_ops_not1_1>
 8048cf8:	60                   	pusha  
 8048cf9:	8b 42 10             	mov    eax,DWORD PTR [edx+0x10]
 8048cfc:	8b 5a f8             	mov    ebx,DWORD PTR [edx-0x8]
 8048cff:	89 d1                	mov    ecx,edx
 8048d01:	f7 e3                	mul    ebx
 8048d03:	89 41 10             	mov    DWORD PTR [ecx+0x10],eax
 8048d06:	61                   	popa   
 8048d07:	6a 00                	push   0x0
 8048d09:	5e                   	pop    esi
 8048d0a:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8048d11:	00 00 00 
 8048d14:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8048d1b:	00 00 00 
 8048d1e:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8048d25:	00 00 00 
 8048d28:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8048d2f:	00 00 00 
 8048d32:	56                   	push   esi
 8048d33:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8048d39:	6a 01                	push   0x1
 8048d3b:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8048d41:	60                   	pusha  
 8048d42:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8048d47:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8048d4d:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8048d53:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8048d59:	be 00 00 00 00       	mov    esi,0x0
 8048d5e:	bf 00 00 00 00       	mov    edi,0x0
 8048d63:	bd 00 00 00 00       	mov    ebp,0x0
 8048d68:	29 d8                	sub    eax,ebx
 8048d6a:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8048d6f:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8048d75:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048d7b:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8048d81:	61                   	popa   
 8048d82:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 8048d88:	5e                   	pop    esi

08048d89 <..@549.__jup>:
 8048d89:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8048d90:	00 00 00 
 8048d93:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8048d9a:	00 00 00 
 8048d9d:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8048da4:	00 00 00 
 8048da7:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8048dae:	00 00 00 
 8048db1:	56                   	push   esi
 8048db2:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8048db8:	6a 01                	push   0x1
 8048dba:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8048dc0:	60                   	pusha  
 8048dc1:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8048dc6:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8048dcc:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8048dd2:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8048dd8:	be 00 00 00 00       	mov    esi,0x0
 8048ddd:	bf 00 00 00 00       	mov    edi,0x0
 8048de2:	bd 00 00 00 00       	mov    ebp,0x0
 8048de7:	01 d8                	add    eax,ebx
 8048de9:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8048dee:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8048df4:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048dfa:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8048e00:	61                   	popa   
 8048e01:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 8048e07:	5e                   	pop    esi
 8048e08:	68 54 8f 04 08       	push   0x8048f54
 8048e0d:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8048e14:	00 00 00 
 8048e17:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8048e1e:	00 00 00 
 8048e21:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8048e28:	00 00 00 
 8048e2b:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8048e32:	00 00 00 
 8048e35:	6a 01                	push   0x1
 8048e37:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8048e3d:	6a 00                	push   0x0
 8048e3f:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8048e45:	60                   	pusha  
 8048e46:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8048e4b:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8048e51:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8048e57:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8048e5d:	be 00 00 00 00       	mov    esi,0x0
 8048e62:	bf 00 00 00 00       	mov    edi,0x0
 8048e67:	bd 00 00 00 00       	mov    ebp,0x0
 8048e6c:	39 d8                	cmp    eax,ebx
 8048e6e:	7c 1d                	jl     8048e8d <..@586._jmp>
 8048e70:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8048e75:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8048e7b:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048e81:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8048e87:	61                   	popa   
 8048e88:	83 c4 04             	add    esp,0x4
 8048e8b:	eb 1f                	jmp    8048eac <..@586._end>

08048e8d <..@586._jmp>:
 8048e8d:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8048e92:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8048e98:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048e9e:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8048ea4:	61                   	popa   
 8048ea5:	83 c4 04             	add    esp,0x4
 8048ea8:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

08048eac <..@586._end>:
 8048eac:	68 a4 90 04 08       	push   0x80490a4
 8048eb1:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8048eb8:	00 00 00 
 8048ebb:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8048ec2:	00 00 00 
 8048ec5:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8048ecc:	00 00 00 
 8048ecf:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8048ed6:	00 00 00 
 8048ed9:	56                   	push   esi
 8048eda:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8048ee0:	6a 02                	push   0x2
 8048ee2:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8048ee8:	60                   	pusha  
 8048ee9:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8048eee:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8048ef4:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8048efa:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8048f00:	be 00 00 00 00       	mov    esi,0x0
 8048f05:	bf 00 00 00 00       	mov    edi,0x0
 8048f0a:	bd 00 00 00 00       	mov    ebp,0x0
 8048f0f:	39 d8                	cmp    eax,ebx
 8048f11:	73 1d                	jae    8048f30 <..@603._jmp>
 8048f13:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8048f18:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8048f1e:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048f24:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8048f2a:	61                   	popa   
 8048f2b:	83 c4 04             	add    esp,0x4
 8048f2e:	eb 1f                	jmp    8048f4f <..@603._end>

08048f30 <..@603._jmp>:
 8048f30:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8048f35:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8048f3b:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048f41:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8048f47:	61                   	popa   
 8048f48:	83 c4 04             	add    esp,0x4
 8048f4b:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

08048f4f <..@603._end>:
 8048f4f:	e9 a3 00 00 00       	jmp    8048ff7 <..@548._end>

08048f54 <..@548._less>:
 8048f54:	68 a4 90 04 08       	push   0x80490a4
 8048f59:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8048f60:	00 00 00 
 8048f63:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8048f6a:	00 00 00 
 8048f6d:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8048f74:	00 00 00 
 8048f77:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8048f7e:	00 00 00 
 8048f81:	56                   	push   esi
 8048f82:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8048f88:	6a 02                	push   0x2
 8048f8a:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8048f90:	60                   	pusha  
 8048f91:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8048f96:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8048f9c:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8048fa2:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8048fa8:	be 00 00 00 00       	mov    esi,0x0
 8048fad:	bf 00 00 00 00       	mov    edi,0x0
 8048fb2:	bd 00 00 00 00       	mov    ebp,0x0
 8048fb7:	39 d8                	cmp    eax,ebx
 8048fb9:	76 1d                	jbe    8048fd8 <..@620._jmp>
 8048fbb:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8048fc0:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8048fc6:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048fcc:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8048fd2:	61                   	popa   
 8048fd3:	83 c4 04             	add    esp,0x4
 8048fd6:	eb 1f                	jmp    8048ff7 <..@548._end>

08048fd8 <..@620._jmp>:
 8048fd8:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8048fdd:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8048fe3:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8048fe9:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8048fef:	61                   	popa   
 8048ff0:	83 c4 04             	add    esp,0x4
 8048ff3:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

08048ff7 <..@548._end>:
 8048ff7:	89 d7                	mov    edi,edx
 8048ff9:	83 c7 0c             	add    edi,0xc
 8048ffc:	89 cd                	mov    ebp,ecx
 8048ffe:	29 fd                	sub    ebp,edi
 8049000:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8049007:	00 00 00 
 804900a:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8049011:	00 00 00 
 8049014:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804901b:	00 00 00 
 804901e:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8049025:	00 00 00 
 8049028:	52                   	push   edx
 8049029:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804902f:	57                   	push   edi
 8049030:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8049036:	55                   	push   ebp
 8049037:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 804903d:	60                   	pusha  
 804903e:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8049043:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8049049:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804904f:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8049055:	be 00 00 00 00       	mov    esi,0x0
 804905a:	bf 00 00 00 00       	mov    edi,0x0
 804905f:	bd 00 00 00 00       	mov    ebp,0x0
 8049064:	39 d8                	cmp    eax,ebx
 8049066:	72 0e                	jb     8049076 <..@636.left>
 8049068:	01 c8                	add    eax,ecx
 804906a:	01 cb                	add    ebx,ecx

0804906c <..@636.right>:
 804906c:	48                   	dec    eax
 804906d:	4b                   	dec    ebx
 804906e:	8b 13                	mov    edx,DWORD PTR [ebx]
 8049070:	89 10                	mov    DWORD PTR [eax],edx
 8049072:	e2 f8                	loop   804906c <..@636.right>
 8049074:	eb 08                	jmp    804907e <..@636.end>

08049076 <..@636.left>:
 8049076:	8b 13                	mov    edx,DWORD PTR [ebx]
 8049078:	89 10                	mov    DWORD PTR [eax],edx
 804907a:	40                   	inc    eax
 804907b:	43                   	inc    ebx
 804907c:	e2 f8                	loop   8049076 <..@636.left>

0804907e <..@636.end>:
 804907e:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8049083:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8049089:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804908f:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8049095:	61                   	popa   
 8049096:	83 e9 0c             	sub    ecx,0xc
 8049099:	83 eb 0c             	sub    ebx,0xc
 804909c:	83 ea 0c             	sub    edx,0xc
 804909f:	e9 e5 fc ff ff       	jmp    8048d89 <..@549.__jup>

080490a4 <..@549.__jdown>:
 80490a4:	e9 5f 08 00 00       	jmp    8049908 <_________macro_ops_end1>

080490a9 <_________macro_ops_not1_1>:
 80490a9:	83 fd 2f             	cmp    ebp,0x2f
 80490ac:	0f 85 27 04 00 00    	jne    80494d9 <_________macro_ops_not1_2>
 80490b2:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 80490b9:	00 00 00 
 80490bc:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 80490c3:	00 00 00 
 80490c6:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 80490cd:	00 00 00 
 80490d0:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 80490d7:	00 00 00 
 80490da:	ff 72 f8             	push   DWORD PTR [edx-0x8]
 80490dd:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 80490e3:	ff 72 10             	push   DWORD PTR [edx+0x10]
 80490e6:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 80490ec:	60                   	pusha  
 80490ed:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 80490f2:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 80490f8:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 80490fe:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8049104:	be 00 00 00 00       	mov    esi,0x0
 8049109:	bf 00 00 00 00       	mov    edi,0x0
 804910e:	bd 00 00 00 00       	mov    ebp,0x0
 8049113:	99                   	cdq    
 8049114:	f7 fb                	idiv   ebx
 8049116:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804911b:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8049121:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8049127:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804912d:	61                   	popa   
 804912e:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 8049134:	8f 42 10             	pop    DWORD PTR [edx+0x10]
 8049137:	6a 00                	push   0x0
 8049139:	5e                   	pop    esi
 804913a:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8049141:	00 00 00 
 8049144:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804914b:	00 00 00 
 804914e:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8049155:	00 00 00 
 8049158:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804915f:	00 00 00 
 8049162:	56                   	push   esi
 8049163:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8049169:	6a 01                	push   0x1
 804916b:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8049171:	60                   	pusha  
 8049172:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8049177:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804917d:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8049183:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8049189:	be 00 00 00 00       	mov    esi,0x0
 804918e:	bf 00 00 00 00       	mov    edi,0x0
 8049193:	bd 00 00 00 00       	mov    ebp,0x0
 8049198:	29 d8                	sub    eax,ebx
 804919a:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804919f:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 80491a5:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 80491ab:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 80491b1:	61                   	popa   
 80491b2:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 80491b8:	5e                   	pop    esi

080491b9 <..@672.__jup>:
 80491b9:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 80491c0:	00 00 00 
 80491c3:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 80491ca:	00 00 00 
 80491cd:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 80491d4:	00 00 00 
 80491d7:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 80491de:	00 00 00 
 80491e1:	56                   	push   esi
 80491e2:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 80491e8:	6a 01                	push   0x1
 80491ea:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 80491f0:	60                   	pusha  
 80491f1:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 80491f6:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 80491fc:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8049202:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8049208:	be 00 00 00 00       	mov    esi,0x0
 804920d:	bf 00 00 00 00       	mov    edi,0x0
 8049212:	bd 00 00 00 00       	mov    ebp,0x0
 8049217:	01 d8                	add    eax,ebx
 8049219:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804921e:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8049224:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804922a:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8049230:	61                   	popa   
 8049231:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 8049237:	5e                   	pop    esi
 8049238:	68 84 93 04 08       	push   0x8049384
 804923d:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8049244:	00 00 00 
 8049247:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804924e:	00 00 00 
 8049251:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8049258:	00 00 00 
 804925b:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8049262:	00 00 00 
 8049265:	6a 01                	push   0x1
 8049267:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804926d:	6a 00                	push   0x0
 804926f:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8049275:	60                   	pusha  
 8049276:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804927b:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8049281:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8049287:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804928d:	be 00 00 00 00       	mov    esi,0x0
 8049292:	bf 00 00 00 00       	mov    edi,0x0
 8049297:	bd 00 00 00 00       	mov    ebp,0x0
 804929c:	39 d8                	cmp    eax,ebx
 804929e:	7c 1d                	jl     80492bd <..@709._jmp>
 80492a0:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 80492a5:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 80492ab:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 80492b1:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 80492b7:	61                   	popa   
 80492b8:	83 c4 04             	add    esp,0x4
 80492bb:	eb 1f                	jmp    80492dc <..@709._end>

080492bd <..@709._jmp>:
 80492bd:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 80492c2:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 80492c8:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 80492ce:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 80492d4:	61                   	popa   
 80492d5:	83 c4 04             	add    esp,0x4
 80492d8:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

080492dc <..@709._end>:
 80492dc:	68 d4 94 04 08       	push   0x80494d4
 80492e1:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 80492e8:	00 00 00 
 80492eb:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 80492f2:	00 00 00 
 80492f5:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 80492fc:	00 00 00 
 80492ff:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8049306:	00 00 00 
 8049309:	56                   	push   esi
 804930a:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8049310:	6a 02                	push   0x2
 8049312:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8049318:	60                   	pusha  
 8049319:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804931e:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8049324:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804932a:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8049330:	be 00 00 00 00       	mov    esi,0x0
 8049335:	bf 00 00 00 00       	mov    edi,0x0
 804933a:	bd 00 00 00 00       	mov    ebp,0x0
 804933f:	39 d8                	cmp    eax,ebx
 8049341:	73 1d                	jae    8049360 <..@726._jmp>
 8049343:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8049348:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804934e:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8049354:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804935a:	61                   	popa   
 804935b:	83 c4 04             	add    esp,0x4
 804935e:	eb 1f                	jmp    804937f <..@726._end>

08049360 <..@726._jmp>:
 8049360:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8049365:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804936b:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8049371:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8049377:	61                   	popa   
 8049378:	83 c4 04             	add    esp,0x4
 804937b:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804937f <..@726._end>:
 804937f:	e9 a3 00 00 00       	jmp    8049427 <..@671._end>

08049384 <..@671._less>:
 8049384:	68 d4 94 04 08       	push   0x80494d4
 8049389:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8049390:	00 00 00 
 8049393:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804939a:	00 00 00 
 804939d:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 80493a4:	00 00 00 
 80493a7:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 80493ae:	00 00 00 
 80493b1:	56                   	push   esi
 80493b2:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 80493b8:	6a 02                	push   0x2
 80493ba:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 80493c0:	60                   	pusha  
 80493c1:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 80493c6:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 80493cc:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 80493d2:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 80493d8:	be 00 00 00 00       	mov    esi,0x0
 80493dd:	bf 00 00 00 00       	mov    edi,0x0
 80493e2:	bd 00 00 00 00       	mov    ebp,0x0
 80493e7:	39 d8                	cmp    eax,ebx
 80493e9:	76 1d                	jbe    8049408 <..@743._jmp>
 80493eb:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 80493f0:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 80493f6:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 80493fc:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8049402:	61                   	popa   
 8049403:	83 c4 04             	add    esp,0x4
 8049406:	eb 1f                	jmp    8049427 <..@671._end>

08049408 <..@743._jmp>:
 8049408:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804940d:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8049413:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8049419:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804941f:	61                   	popa   
 8049420:	83 c4 04             	add    esp,0x4
 8049423:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

08049427 <..@671._end>:
 8049427:	89 d7                	mov    edi,edx
 8049429:	83 c7 0c             	add    edi,0xc
 804942c:	89 cd                	mov    ebp,ecx
 804942e:	29 fd                	sub    ebp,edi
 8049430:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8049437:	00 00 00 
 804943a:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8049441:	00 00 00 
 8049444:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804944b:	00 00 00 
 804944e:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8049455:	00 00 00 
 8049458:	52                   	push   edx
 8049459:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804945f:	57                   	push   edi
 8049460:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8049466:	55                   	push   ebp
 8049467:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 804946d:	60                   	pusha  
 804946e:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8049473:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8049479:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804947f:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8049485:	be 00 00 00 00       	mov    esi,0x0
 804948a:	bf 00 00 00 00       	mov    edi,0x0
 804948f:	bd 00 00 00 00       	mov    ebp,0x0
 8049494:	39 d8                	cmp    eax,ebx
 8049496:	72 0e                	jb     80494a6 <..@759.left>
 8049498:	01 c8                	add    eax,ecx
 804949a:	01 cb                	add    ebx,ecx

0804949c <..@759.right>:
 804949c:	48                   	dec    eax
 804949d:	4b                   	dec    ebx
 804949e:	8b 13                	mov    edx,DWORD PTR [ebx]
 80494a0:	89 10                	mov    DWORD PTR [eax],edx
 80494a2:	e2 f8                	loop   804949c <..@759.right>
 80494a4:	eb 08                	jmp    80494ae <..@759.end>

080494a6 <..@759.left>:
 80494a6:	8b 13                	mov    edx,DWORD PTR [ebx]
 80494a8:	89 10                	mov    DWORD PTR [eax],edx
 80494aa:	40                   	inc    eax
 80494ab:	43                   	inc    ebx
 80494ac:	e2 f8                	loop   80494a6 <..@759.left>

080494ae <..@759.end>:
 80494ae:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 80494b3:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 80494b9:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 80494bf:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 80494c5:	61                   	popa   
 80494c6:	83 e9 0c             	sub    ecx,0xc
 80494c9:	83 eb 0c             	sub    ebx,0xc
 80494cc:	83 ea 0c             	sub    edx,0xc
 80494cf:	e9 e5 fc ff ff       	jmp    80491b9 <..@672.__jup>

080494d4 <..@672.__jdown>:
 80494d4:	e9 2f 04 00 00       	jmp    8049908 <_________macro_ops_end1>

080494d9 <_________macro_ops_not1_2>:
 80494d9:	83 fd 25             	cmp    ebp,0x25
 80494dc:	0f 85 26 04 00 00    	jne    8049908 <_________macro_ops_end1>
 80494e2:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 80494e9:	00 00 00 
 80494ec:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 80494f3:	00 00 00 
 80494f6:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 80494fd:	00 00 00 
 8049500:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8049507:	00 00 00 
 804950a:	ff 72 f8             	push   DWORD PTR [edx-0x8]
 804950d:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8049513:	ff 72 10             	push   DWORD PTR [edx+0x10]
 8049516:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804951c:	60                   	pusha  
 804951d:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8049522:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8049528:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804952e:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8049534:	be 00 00 00 00       	mov    esi,0x0
 8049539:	bf 00 00 00 00       	mov    edi,0x0
 804953e:	bd 00 00 00 00       	mov    ebp,0x0
 8049543:	99                   	cdq    
 8049544:	f7 fb                	idiv   ebx
 8049546:	89 d0                	mov    eax,edx
 8049548:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804954d:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8049553:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8049559:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804955f:	61                   	popa   
 8049560:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 8049566:	8f 42 10             	pop    DWORD PTR [edx+0x10]
 8049569:	6a 00                	push   0x0
 804956b:	5e                   	pop    esi
 804956c:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8049573:	00 00 00 
 8049576:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804957d:	00 00 00 
 8049580:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8049587:	00 00 00 
 804958a:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8049591:	00 00 00 
 8049594:	56                   	push   esi
 8049595:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804959b:	6a 01                	push   0x1
 804959d:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 80495a3:	60                   	pusha  
 80495a4:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 80495a9:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 80495af:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 80495b5:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 80495bb:	be 00 00 00 00       	mov    esi,0x0
 80495c0:	bf 00 00 00 00       	mov    edi,0x0
 80495c5:	bd 00 00 00 00       	mov    ebp,0x0
 80495ca:	29 d8                	sub    eax,ebx
 80495cc:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 80495d1:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 80495d7:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 80495dd:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 80495e3:	61                   	popa   
 80495e4:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 80495ea:	5e                   	pop    esi

080495eb <..@795.__jup>:
 80495eb:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 80495f2:	00 00 00 
 80495f5:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 80495fc:	00 00 00 
 80495ff:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8049606:	00 00 00 
 8049609:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8049610:	00 00 00 
 8049613:	56                   	push   esi
 8049614:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804961a:	6a 01                	push   0x1
 804961c:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8049622:	60                   	pusha  
 8049623:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8049628:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804962e:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8049634:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804963a:	be 00 00 00 00       	mov    esi,0x0
 804963f:	bf 00 00 00 00       	mov    edi,0x0
 8049644:	bd 00 00 00 00       	mov    ebp,0x0
 8049649:	01 d8                	add    eax,ebx
 804964b:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8049650:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8049656:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804965c:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8049662:	61                   	popa   
 8049663:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 8049669:	5e                   	pop    esi
 804966a:	68 b6 97 04 08       	push   0x80497b6
 804966f:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8049676:	00 00 00 
 8049679:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8049680:	00 00 00 
 8049683:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804968a:	00 00 00 
 804968d:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8049694:	00 00 00 
 8049697:	6a 01                	push   0x1
 8049699:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804969f:	6a 00                	push   0x0
 80496a1:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 80496a7:	60                   	pusha  
 80496a8:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 80496ad:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 80496b3:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 80496b9:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 80496bf:	be 00 00 00 00       	mov    esi,0x0
 80496c4:	bf 00 00 00 00       	mov    edi,0x0
 80496c9:	bd 00 00 00 00       	mov    ebp,0x0
 80496ce:	39 d8                	cmp    eax,ebx
 80496d0:	7c 1d                	jl     80496ef <..@832._jmp>
 80496d2:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 80496d7:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 80496dd:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 80496e3:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 80496e9:	61                   	popa   
 80496ea:	83 c4 04             	add    esp,0x4
 80496ed:	eb 1f                	jmp    804970e <..@832._end>

080496ef <..@832._jmp>:
 80496ef:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 80496f4:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 80496fa:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8049700:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8049706:	61                   	popa   
 8049707:	83 c4 04             	add    esp,0x4
 804970a:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804970e <..@832._end>:
 804970e:	68 06 99 04 08       	push   0x8049906
 8049713:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804971a:	00 00 00 
 804971d:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8049724:	00 00 00 
 8049727:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804972e:	00 00 00 
 8049731:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8049738:	00 00 00 
 804973b:	56                   	push   esi
 804973c:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8049742:	6a 02                	push   0x2
 8049744:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804974a:	60                   	pusha  
 804974b:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8049750:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8049756:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804975c:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8049762:	be 00 00 00 00       	mov    esi,0x0
 8049767:	bf 00 00 00 00       	mov    edi,0x0
 804976c:	bd 00 00 00 00       	mov    ebp,0x0
 8049771:	39 d8                	cmp    eax,ebx
 8049773:	73 1d                	jae    8049792 <..@849._jmp>
 8049775:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804977a:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8049780:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8049786:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804978c:	61                   	popa   
 804978d:	83 c4 04             	add    esp,0x4
 8049790:	eb 1f                	jmp    80497b1 <..@849._end>

08049792 <..@849._jmp>:
 8049792:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8049797:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804979d:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 80497a3:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 80497a9:	61                   	popa   
 80497aa:	83 c4 04             	add    esp,0x4
 80497ad:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

080497b1 <..@849._end>:
 80497b1:	e9 a3 00 00 00       	jmp    8049859 <..@794._end>

080497b6 <..@794._less>:
 80497b6:	68 06 99 04 08       	push   0x8049906
 80497bb:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 80497c2:	00 00 00 
 80497c5:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 80497cc:	00 00 00 
 80497cf:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 80497d6:	00 00 00 
 80497d9:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 80497e0:	00 00 00 
 80497e3:	56                   	push   esi
 80497e4:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 80497ea:	6a 02                	push   0x2
 80497ec:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 80497f2:	60                   	pusha  
 80497f3:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 80497f8:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 80497fe:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8049804:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804980a:	be 00 00 00 00       	mov    esi,0x0
 804980f:	bf 00 00 00 00       	mov    edi,0x0
 8049814:	bd 00 00 00 00       	mov    ebp,0x0
 8049819:	39 d8                	cmp    eax,ebx
 804981b:	76 1d                	jbe    804983a <..@866._jmp>
 804981d:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8049822:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8049828:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804982e:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8049834:	61                   	popa   
 8049835:	83 c4 04             	add    esp,0x4
 8049838:	eb 1f                	jmp    8049859 <..@794._end>

0804983a <..@866._jmp>:
 804983a:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804983f:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8049845:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804984b:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8049851:	61                   	popa   
 8049852:	83 c4 04             	add    esp,0x4
 8049855:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

08049859 <..@794._end>:
 8049859:	89 d7                	mov    edi,edx
 804985b:	83 c7 0c             	add    edi,0xc
 804985e:	89 cd                	mov    ebp,ecx
 8049860:	29 fd                	sub    ebp,edi
 8049862:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8049869:	00 00 00 
 804986c:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8049873:	00 00 00 
 8049876:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804987d:	00 00 00 
 8049880:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8049887:	00 00 00 
 804988a:	52                   	push   edx
 804988b:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8049891:	57                   	push   edi
 8049892:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8049898:	55                   	push   ebp
 8049899:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 804989f:	60                   	pusha  
 80498a0:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 80498a5:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 80498ab:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 80498b1:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 80498b7:	be 00 00 00 00       	mov    esi,0x0
 80498bc:	bf 00 00 00 00       	mov    edi,0x0
 80498c1:	bd 00 00 00 00       	mov    ebp,0x0
 80498c6:	39 d8                	cmp    eax,ebx
 80498c8:	72 0e                	jb     80498d8 <..@882.left>
 80498ca:	01 c8                	add    eax,ecx
 80498cc:	01 cb                	add    ebx,ecx

080498ce <..@882.right>:
 80498ce:	48                   	dec    eax
 80498cf:	4b                   	dec    ebx
 80498d0:	8b 13                	mov    edx,DWORD PTR [ebx]
 80498d2:	89 10                	mov    DWORD PTR [eax],edx
 80498d4:	e2 f8                	loop   80498ce <..@882.right>
 80498d6:	eb 08                	jmp    80498e0 <..@882.end>

080498d8 <..@882.left>:
 80498d8:	8b 13                	mov    edx,DWORD PTR [ebx]
 80498da:	89 10                	mov    DWORD PTR [eax],edx
 80498dc:	40                   	inc    eax
 80498dd:	43                   	inc    ebx
 80498de:	e2 f8                	loop   80498d8 <..@882.left>

080498e0 <..@882.end>:
 80498e0:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 80498e5:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 80498eb:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 80498f1:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 80498f7:	61                   	popa   
 80498f8:	83 e9 0c             	sub    ecx,0xc
 80498fb:	83 eb 0c             	sub    ebx,0xc
 80498fe:	83 ea 0c             	sub    edx,0xc
 8049901:	e9 e5 fc ff ff       	jmp    80495eb <..@795.__jup>

08049906 <..@795.__jdown>:
 8049906:	eb 00                	jmp    8049908 <_________macro_ops_end1>

08049908 <_________macro_ops_end1>:
 8049908:	83 c2 0c             	add    edx,0xc
 804990b:	e9 bc f3 ff ff       	jmp    8048ccc <_________macro_ops_for_begin1>

08049910 <_________macro_ops_for_end1>:
 8049910:	89 c2                	mov    edx,eax

08049912 <_________macro_ops_for_begin2>:
 8049912:	39 da                	cmp    edx,ebx
 8049914:	0f 83 8c 07 00 00    	jae    804a0a6 <_________macro_ops_for_end2>
 804991a:	68 29 99 04 08       	push   0x8049929
 804991f:	68 f4 00 00 00       	push   0xf4
 8049924:	e9 57 e7 ff ff       	jmp    8048080 <macro_pr_jmp>

08049929 <..@899._1>:
 8049929:	83 3a 02             	cmp    DWORD PTR [edx],0x2
 804992c:	0f 85 6c 07 00 00    	jne    804a09e <_________macro_ops_end2>
 8049932:	8b 6a 04             	mov    ebp,DWORD PTR [edx+0x4]
 8049935:	83 fd 2b             	cmp    ebp,0x2b
 8049938:	0f 85 ad 03 00 00    	jne    8049ceb <_________macro_ops_not2_1>
 804993e:	60                   	pusha  
 804993f:	8b 42 f8             	mov    eax,DWORD PTR [edx-0x8]
 8049942:	03 42 10             	add    eax,DWORD PTR [edx+0x10]
 8049945:	89 42 10             	mov    DWORD PTR [edx+0x10],eax
 8049948:	61                   	popa   
 8049949:	6a 00                	push   0x0
 804994b:	5e                   	pop    esi
 804994c:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8049953:	00 00 00 
 8049956:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804995d:	00 00 00 
 8049960:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8049967:	00 00 00 
 804996a:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8049971:	00 00 00 
 8049974:	56                   	push   esi
 8049975:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804997b:	6a 01                	push   0x1
 804997d:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8049983:	60                   	pusha  
 8049984:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8049989:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804998f:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8049995:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804999b:	be 00 00 00 00       	mov    esi,0x0
 80499a0:	bf 00 00 00 00       	mov    edi,0x0
 80499a5:	bd 00 00 00 00       	mov    ebp,0x0
 80499aa:	29 d8                	sub    eax,ebx
 80499ac:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 80499b1:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 80499b7:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 80499bd:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 80499c3:	61                   	popa   
 80499c4:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 80499ca:	5e                   	pop    esi

080499cb <..@905.__jup>:
 80499cb:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 80499d2:	00 00 00 
 80499d5:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 80499dc:	00 00 00 
 80499df:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 80499e6:	00 00 00 
 80499e9:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 80499f0:	00 00 00 
 80499f3:	56                   	push   esi
 80499f4:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 80499fa:	6a 01                	push   0x1
 80499fc:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8049a02:	60                   	pusha  
 8049a03:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8049a08:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8049a0e:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8049a14:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8049a1a:	be 00 00 00 00       	mov    esi,0x0
 8049a1f:	bf 00 00 00 00       	mov    edi,0x0
 8049a24:	bd 00 00 00 00       	mov    ebp,0x0
 8049a29:	01 d8                	add    eax,ebx
 8049a2b:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8049a30:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8049a36:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8049a3c:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8049a42:	61                   	popa   
 8049a43:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 8049a49:	5e                   	pop    esi
 8049a4a:	68 96 9b 04 08       	push   0x8049b96
 8049a4f:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8049a56:	00 00 00 
 8049a59:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8049a60:	00 00 00 
 8049a63:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8049a6a:	00 00 00 
 8049a6d:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8049a74:	00 00 00 
 8049a77:	6a 01                	push   0x1
 8049a79:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8049a7f:	6a 00                	push   0x0
 8049a81:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8049a87:	60                   	pusha  
 8049a88:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8049a8d:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8049a93:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8049a99:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8049a9f:	be 00 00 00 00       	mov    esi,0x0
 8049aa4:	bf 00 00 00 00       	mov    edi,0x0
 8049aa9:	bd 00 00 00 00       	mov    ebp,0x0
 8049aae:	39 d8                	cmp    eax,ebx
 8049ab0:	7c 1d                	jl     8049acf <..@942._jmp>
 8049ab2:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8049ab7:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8049abd:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8049ac3:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8049ac9:	61                   	popa   
 8049aca:	83 c4 04             	add    esp,0x4
 8049acd:	eb 1f                	jmp    8049aee <..@942._end>

08049acf <..@942._jmp>:
 8049acf:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8049ad4:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8049ada:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8049ae0:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8049ae6:	61                   	popa   
 8049ae7:	83 c4 04             	add    esp,0x4
 8049aea:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

08049aee <..@942._end>:
 8049aee:	68 e6 9c 04 08       	push   0x8049ce6
 8049af3:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8049afa:	00 00 00 
 8049afd:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8049b04:	00 00 00 
 8049b07:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8049b0e:	00 00 00 
 8049b11:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8049b18:	00 00 00 
 8049b1b:	56                   	push   esi
 8049b1c:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8049b22:	6a 02                	push   0x2
 8049b24:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8049b2a:	60                   	pusha  
 8049b2b:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8049b30:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8049b36:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8049b3c:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8049b42:	be 00 00 00 00       	mov    esi,0x0
 8049b47:	bf 00 00 00 00       	mov    edi,0x0
 8049b4c:	bd 00 00 00 00       	mov    ebp,0x0
 8049b51:	39 d8                	cmp    eax,ebx
 8049b53:	73 1d                	jae    8049b72 <..@959._jmp>
 8049b55:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8049b5a:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8049b60:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8049b66:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8049b6c:	61                   	popa   
 8049b6d:	83 c4 04             	add    esp,0x4
 8049b70:	eb 1f                	jmp    8049b91 <..@959._end>

08049b72 <..@959._jmp>:
 8049b72:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8049b77:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8049b7d:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8049b83:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8049b89:	61                   	popa   
 8049b8a:	83 c4 04             	add    esp,0x4
 8049b8d:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

08049b91 <..@959._end>:
 8049b91:	e9 a3 00 00 00       	jmp    8049c39 <..@904._end>

08049b96 <..@904._less>:
 8049b96:	68 e6 9c 04 08       	push   0x8049ce6
 8049b9b:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8049ba2:	00 00 00 
 8049ba5:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8049bac:	00 00 00 
 8049baf:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8049bb6:	00 00 00 
 8049bb9:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8049bc0:	00 00 00 
 8049bc3:	56                   	push   esi
 8049bc4:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8049bca:	6a 02                	push   0x2
 8049bcc:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8049bd2:	60                   	pusha  
 8049bd3:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8049bd8:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8049bde:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8049be4:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8049bea:	be 00 00 00 00       	mov    esi,0x0
 8049bef:	bf 00 00 00 00       	mov    edi,0x0
 8049bf4:	bd 00 00 00 00       	mov    ebp,0x0
 8049bf9:	39 d8                	cmp    eax,ebx
 8049bfb:	76 1d                	jbe    8049c1a <..@976._jmp>
 8049bfd:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8049c02:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8049c08:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8049c0e:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8049c14:	61                   	popa   
 8049c15:	83 c4 04             	add    esp,0x4
 8049c18:	eb 1f                	jmp    8049c39 <..@904._end>

08049c1a <..@976._jmp>:
 8049c1a:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8049c1f:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8049c25:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8049c2b:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8049c31:	61                   	popa   
 8049c32:	83 c4 04             	add    esp,0x4
 8049c35:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

08049c39 <..@904._end>:
 8049c39:	89 d7                	mov    edi,edx
 8049c3b:	83 c7 0c             	add    edi,0xc
 8049c3e:	89 cd                	mov    ebp,ecx
 8049c40:	29 fd                	sub    ebp,edi
 8049c42:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8049c49:	00 00 00 
 8049c4c:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8049c53:	00 00 00 
 8049c56:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8049c5d:	00 00 00 
 8049c60:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8049c67:	00 00 00 
 8049c6a:	52                   	push   edx
 8049c6b:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8049c71:	57                   	push   edi
 8049c72:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8049c78:	55                   	push   ebp
 8049c79:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 8049c7f:	60                   	pusha  
 8049c80:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8049c85:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8049c8b:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8049c91:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8049c97:	be 00 00 00 00       	mov    esi,0x0
 8049c9c:	bf 00 00 00 00       	mov    edi,0x0
 8049ca1:	bd 00 00 00 00       	mov    ebp,0x0
 8049ca6:	39 d8                	cmp    eax,ebx
 8049ca8:	72 0e                	jb     8049cb8 <..@992.left>
 8049caa:	01 c8                	add    eax,ecx
 8049cac:	01 cb                	add    ebx,ecx

08049cae <..@992.right>:
 8049cae:	48                   	dec    eax
 8049caf:	4b                   	dec    ebx
 8049cb0:	8b 13                	mov    edx,DWORD PTR [ebx]
 8049cb2:	89 10                	mov    DWORD PTR [eax],edx
 8049cb4:	e2 f8                	loop   8049cae <..@992.right>
 8049cb6:	eb 08                	jmp    8049cc0 <..@992.end>

08049cb8 <..@992.left>:
 8049cb8:	8b 13                	mov    edx,DWORD PTR [ebx]
 8049cba:	89 10                	mov    DWORD PTR [eax],edx
 8049cbc:	40                   	inc    eax
 8049cbd:	43                   	inc    ebx
 8049cbe:	e2 f8                	loop   8049cb8 <..@992.left>

08049cc0 <..@992.end>:
 8049cc0:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8049cc5:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8049ccb:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8049cd1:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8049cd7:	61                   	popa   
 8049cd8:	83 e9 0c             	sub    ecx,0xc
 8049cdb:	83 eb 0c             	sub    ebx,0xc
 8049cde:	83 ea 0c             	sub    edx,0xc
 8049ce1:	e9 e5 fc ff ff       	jmp    80499cb <..@905.__jup>

08049ce6 <..@905.__jdown>:
 8049ce6:	e9 b3 03 00 00       	jmp    804a09e <_________macro_ops_end2>

08049ceb <_________macro_ops_not2_1>:
 8049ceb:	83 fd 2d             	cmp    ebp,0x2d
 8049cee:	0f 85 aa 03 00 00    	jne    804a09e <_________macro_ops_end2>
 8049cf4:	60                   	pusha  
 8049cf5:	8b 42 f8             	mov    eax,DWORD PTR [edx-0x8]
 8049cf8:	2b 42 10             	sub    eax,DWORD PTR [edx+0x10]
 8049cfb:	89 42 10             	mov    DWORD PTR [edx+0x10],eax
 8049cfe:	61                   	popa   
 8049cff:	6a 00                	push   0x0
 8049d01:	5e                   	pop    esi
 8049d02:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8049d09:	00 00 00 
 8049d0c:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8049d13:	00 00 00 
 8049d16:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8049d1d:	00 00 00 
 8049d20:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8049d27:	00 00 00 
 8049d2a:	56                   	push   esi
 8049d2b:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8049d31:	6a 01                	push   0x1
 8049d33:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8049d39:	60                   	pusha  
 8049d3a:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8049d3f:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8049d45:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8049d4b:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8049d51:	be 00 00 00 00       	mov    esi,0x0
 8049d56:	bf 00 00 00 00       	mov    edi,0x0
 8049d5b:	bd 00 00 00 00       	mov    ebp,0x0
 8049d60:	29 d8                	sub    eax,ebx
 8049d62:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8049d67:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8049d6d:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8049d73:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8049d79:	61                   	popa   
 8049d7a:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 8049d80:	5e                   	pop    esi

08049d81 <..@1012.__jup>:
 8049d81:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8049d88:	00 00 00 
 8049d8b:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8049d92:	00 00 00 
 8049d95:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8049d9c:	00 00 00 
 8049d9f:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8049da6:	00 00 00 
 8049da9:	56                   	push   esi
 8049daa:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8049db0:	6a 01                	push   0x1
 8049db2:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8049db8:	60                   	pusha  
 8049db9:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8049dbe:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8049dc4:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8049dca:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8049dd0:	be 00 00 00 00       	mov    esi,0x0
 8049dd5:	bf 00 00 00 00       	mov    edi,0x0
 8049dda:	bd 00 00 00 00       	mov    ebp,0x0
 8049ddf:	01 d8                	add    eax,ebx
 8049de1:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8049de6:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8049dec:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8049df2:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8049df8:	61                   	popa   
 8049df9:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 8049dff:	5e                   	pop    esi
 8049e00:	68 4c 9f 04 08       	push   0x8049f4c
 8049e05:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8049e0c:	00 00 00 
 8049e0f:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8049e16:	00 00 00 
 8049e19:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8049e20:	00 00 00 
 8049e23:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8049e2a:	00 00 00 
 8049e2d:	6a 01                	push   0x1
 8049e2f:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8049e35:	6a 00                	push   0x0
 8049e37:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8049e3d:	60                   	pusha  
 8049e3e:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8049e43:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8049e49:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8049e4f:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8049e55:	be 00 00 00 00       	mov    esi,0x0
 8049e5a:	bf 00 00 00 00       	mov    edi,0x0
 8049e5f:	bd 00 00 00 00       	mov    ebp,0x0
 8049e64:	39 d8                	cmp    eax,ebx
 8049e66:	7c 1d                	jl     8049e85 <..@1049._jmp>
 8049e68:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8049e6d:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8049e73:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8049e79:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8049e7f:	61                   	popa   
 8049e80:	83 c4 04             	add    esp,0x4
 8049e83:	eb 1f                	jmp    8049ea4 <..@1049._end>

08049e85 <..@1049._jmp>:
 8049e85:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8049e8a:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8049e90:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8049e96:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8049e9c:	61                   	popa   
 8049e9d:	83 c4 04             	add    esp,0x4
 8049ea0:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

08049ea4 <..@1049._end>:
 8049ea4:	68 9c a0 04 08       	push   0x804a09c
 8049ea9:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8049eb0:	00 00 00 
 8049eb3:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8049eba:	00 00 00 
 8049ebd:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8049ec4:	00 00 00 
 8049ec7:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8049ece:	00 00 00 
 8049ed1:	56                   	push   esi
 8049ed2:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8049ed8:	6a 02                	push   0x2
 8049eda:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8049ee0:	60                   	pusha  
 8049ee1:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8049ee6:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8049eec:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8049ef2:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8049ef8:	be 00 00 00 00       	mov    esi,0x0
 8049efd:	bf 00 00 00 00       	mov    edi,0x0
 8049f02:	bd 00 00 00 00       	mov    ebp,0x0
 8049f07:	39 d8                	cmp    eax,ebx
 8049f09:	73 1d                	jae    8049f28 <..@1066._jmp>
 8049f0b:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8049f10:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8049f16:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8049f1c:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8049f22:	61                   	popa   
 8049f23:	83 c4 04             	add    esp,0x4
 8049f26:	eb 1f                	jmp    8049f47 <..@1066._end>

08049f28 <..@1066._jmp>:
 8049f28:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8049f2d:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8049f33:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8049f39:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8049f3f:	61                   	popa   
 8049f40:	83 c4 04             	add    esp,0x4
 8049f43:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

08049f47 <..@1066._end>:
 8049f47:	e9 a3 00 00 00       	jmp    8049fef <..@1011._end>

08049f4c <..@1011._less>:
 8049f4c:	68 9c a0 04 08       	push   0x804a09c
 8049f51:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8049f58:	00 00 00 
 8049f5b:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 8049f62:	00 00 00 
 8049f65:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 8049f6c:	00 00 00 
 8049f6f:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 8049f76:	00 00 00 
 8049f79:	56                   	push   esi
 8049f7a:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 8049f80:	6a 02                	push   0x2
 8049f82:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 8049f88:	60                   	pusha  
 8049f89:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 8049f8e:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 8049f94:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 8049f9a:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 8049fa0:	be 00 00 00 00       	mov    esi,0x0
 8049fa5:	bf 00 00 00 00       	mov    edi,0x0
 8049faa:	bd 00 00 00 00       	mov    ebp,0x0
 8049faf:	39 d8                	cmp    eax,ebx
 8049fb1:	76 1d                	jbe    8049fd0 <..@1083._jmp>
 8049fb3:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8049fb8:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8049fbe:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8049fc4:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8049fca:	61                   	popa   
 8049fcb:	83 c4 04             	add    esp,0x4
 8049fce:	eb 1f                	jmp    8049fef <..@1011._end>

08049fd0 <..@1083._jmp>:
 8049fd0:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 8049fd5:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 8049fdb:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 8049fe1:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 8049fe7:	61                   	popa   
 8049fe8:	83 c4 04             	add    esp,0x4
 8049feb:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

08049fef <..@1011._end>:
 8049fef:	89 d7                	mov    edi,edx
 8049ff1:	83 c7 0c             	add    edi,0xc
 8049ff4:	89 cd                	mov    ebp,ecx
 8049ff6:	29 fd                	sub    ebp,edi
 8049ff8:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 8049fff:	00 00 00 
 804a002:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804a009:	00 00 00 
 804a00c:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804a013:	00 00 00 
 804a016:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804a01d:	00 00 00 
 804a020:	52                   	push   edx
 804a021:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804a027:	57                   	push   edi
 804a028:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804a02e:	55                   	push   ebp
 804a02f:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 804a035:	60                   	pusha  
 804a036:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804a03b:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804a041:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804a047:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804a04d:	be 00 00 00 00       	mov    esi,0x0
 804a052:	bf 00 00 00 00       	mov    edi,0x0
 804a057:	bd 00 00 00 00       	mov    ebp,0x0
 804a05c:	39 d8                	cmp    eax,ebx
 804a05e:	72 0e                	jb     804a06e <..@1099.left>
 804a060:	01 c8                	add    eax,ecx
 804a062:	01 cb                	add    ebx,ecx

0804a064 <..@1099.right>:
 804a064:	48                   	dec    eax
 804a065:	4b                   	dec    ebx
 804a066:	8b 13                	mov    edx,DWORD PTR [ebx]
 804a068:	89 10                	mov    DWORD PTR [eax],edx
 804a06a:	e2 f8                	loop   804a064 <..@1099.right>
 804a06c:	eb 08                	jmp    804a076 <..@1099.end>

0804a06e <..@1099.left>:
 804a06e:	8b 13                	mov    edx,DWORD PTR [ebx]
 804a070:	89 10                	mov    DWORD PTR [eax],edx
 804a072:	40                   	inc    eax
 804a073:	43                   	inc    ebx
 804a074:	e2 f8                	loop   804a06e <..@1099.left>

0804a076 <..@1099.end>:
 804a076:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804a07b:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804a081:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804a087:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804a08d:	61                   	popa   
 804a08e:	83 e9 0c             	sub    ecx,0xc
 804a091:	83 eb 0c             	sub    ebx,0xc
 804a094:	83 ea 0c             	sub    edx,0xc
 804a097:	e9 e5 fc ff ff       	jmp    8049d81 <..@1012.__jup>

0804a09c <..@1012.__jdown>:
 804a09c:	eb 00                	jmp    804a09e <_________macro_ops_end2>

0804a09e <_________macro_ops_end2>:
 804a09e:	83 c2 0c             	add    edx,0xc
 804a0a1:	e9 6c f8 ff ff       	jmp    8049912 <_________macro_ops_for_begin2>

0804a0a6 <_________macro_ops_for_end2>:
 804a0a6:	89 c2                	mov    edx,eax

0804a0a8 <_________macro_ops_for_begin3>:
 804a0a8:	39 da                	cmp    edx,ebx
 804a0aa:	0f 83 be 16 00 00    	jae    804b76e <_________macro_ops_for_end3>
 804a0b0:	68 bf a0 04 08       	push   0x804a0bf
 804a0b5:	68 16 01 00 00       	push   0x116
 804a0ba:	e9 c1 df ff ff       	jmp    8048080 <macro_pr_jmp>

0804a0bf <..@1116._1>:
 804a0bf:	83 3a 02             	cmp    DWORD PTR [edx],0x2
 804a0c2:	0f 85 9e 16 00 00    	jne    804b766 <_________macro_ops_end3>
 804a0c8:	8b 6a 04             	mov    ebp,DWORD PTR [edx+0x4]
 804a0cb:	83 fd 3c             	cmp    ebp,0x3c
 804a0ce:	0f 85 ba 03 00 00    	jne    804a48e <_________macro_ops_not3_1>
 804a0d4:	8b 72 f8             	mov    esi,DWORD PTR [edx-0x8]
 804a0d7:	3b 72 10             	cmp    esi,DWORD PTR [edx+0x10]
 804a0da:	7d 09                	jge    804a0e5 <_________macro_ops_cmp_begin1>
 804a0dc:	c7 42 10 01 00 00 00 	mov    DWORD PTR [edx+0x10],0x1
 804a0e3:	eb 07                	jmp    804a0ec <_________macro_ops_cmp_end1>

0804a0e5 <_________macro_ops_cmp_begin1>:
 804a0e5:	c7 42 10 00 00 00 00 	mov    DWORD PTR [edx+0x10],0x0

0804a0ec <_________macro_ops_cmp_end1>:
 804a0ec:	6a 00                	push   0x0
 804a0ee:	5e                   	pop    esi
 804a0ef:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804a0f6:	00 00 00 
 804a0f9:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804a100:	00 00 00 
 804a103:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804a10a:	00 00 00 
 804a10d:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804a114:	00 00 00 
 804a117:	56                   	push   esi
 804a118:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804a11e:	6a 01                	push   0x1
 804a120:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804a126:	60                   	pusha  
 804a127:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804a12c:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804a132:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804a138:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804a13e:	be 00 00 00 00       	mov    esi,0x0
 804a143:	bf 00 00 00 00       	mov    edi,0x0
 804a148:	bd 00 00 00 00       	mov    ebp,0x0
 804a14d:	29 d8                	sub    eax,ebx
 804a14f:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804a154:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804a15a:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804a160:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804a166:	61                   	popa   
 804a167:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804a16d:	5e                   	pop    esi

0804a16e <..@1122.__jup>:
 804a16e:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804a175:	00 00 00 
 804a178:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804a17f:	00 00 00 
 804a182:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804a189:	00 00 00 
 804a18c:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804a193:	00 00 00 
 804a196:	56                   	push   esi
 804a197:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804a19d:	6a 01                	push   0x1
 804a19f:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804a1a5:	60                   	pusha  
 804a1a6:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804a1ab:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804a1b1:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804a1b7:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804a1bd:	be 00 00 00 00       	mov    esi,0x0
 804a1c2:	bf 00 00 00 00       	mov    edi,0x0
 804a1c7:	bd 00 00 00 00       	mov    ebp,0x0
 804a1cc:	01 d8                	add    eax,ebx
 804a1ce:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804a1d3:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804a1d9:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804a1df:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804a1e5:	61                   	popa   
 804a1e6:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804a1ec:	5e                   	pop    esi
 804a1ed:	68 39 a3 04 08       	push   0x804a339
 804a1f2:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804a1f9:	00 00 00 
 804a1fc:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804a203:	00 00 00 
 804a206:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804a20d:	00 00 00 
 804a210:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804a217:	00 00 00 
 804a21a:	6a 01                	push   0x1
 804a21c:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804a222:	6a 00                	push   0x0
 804a224:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804a22a:	60                   	pusha  
 804a22b:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804a230:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804a236:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804a23c:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804a242:	be 00 00 00 00       	mov    esi,0x0
 804a247:	bf 00 00 00 00       	mov    edi,0x0
 804a24c:	bd 00 00 00 00       	mov    ebp,0x0
 804a251:	39 d8                	cmp    eax,ebx
 804a253:	7c 1d                	jl     804a272 <..@1159._jmp>
 804a255:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804a25a:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804a260:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804a266:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804a26c:	61                   	popa   
 804a26d:	83 c4 04             	add    esp,0x4
 804a270:	eb 1f                	jmp    804a291 <..@1159._end>

0804a272 <..@1159._jmp>:
 804a272:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804a277:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804a27d:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804a283:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804a289:	61                   	popa   
 804a28a:	83 c4 04             	add    esp,0x4
 804a28d:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804a291 <..@1159._end>:
 804a291:	68 89 a4 04 08       	push   0x804a489
 804a296:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804a29d:	00 00 00 
 804a2a0:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804a2a7:	00 00 00 
 804a2aa:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804a2b1:	00 00 00 
 804a2b4:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804a2bb:	00 00 00 
 804a2be:	56                   	push   esi
 804a2bf:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804a2c5:	6a 02                	push   0x2
 804a2c7:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804a2cd:	60                   	pusha  
 804a2ce:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804a2d3:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804a2d9:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804a2df:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804a2e5:	be 00 00 00 00       	mov    esi,0x0
 804a2ea:	bf 00 00 00 00       	mov    edi,0x0
 804a2ef:	bd 00 00 00 00       	mov    ebp,0x0
 804a2f4:	39 d8                	cmp    eax,ebx
 804a2f6:	73 1d                	jae    804a315 <..@1176._jmp>
 804a2f8:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804a2fd:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804a303:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804a309:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804a30f:	61                   	popa   
 804a310:	83 c4 04             	add    esp,0x4
 804a313:	eb 1f                	jmp    804a334 <..@1176._end>

0804a315 <..@1176._jmp>:
 804a315:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804a31a:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804a320:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804a326:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804a32c:	61                   	popa   
 804a32d:	83 c4 04             	add    esp,0x4
 804a330:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804a334 <..@1176._end>:
 804a334:	e9 a3 00 00 00       	jmp    804a3dc <..@1121._end>

0804a339 <..@1121._less>:
 804a339:	68 89 a4 04 08       	push   0x804a489
 804a33e:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804a345:	00 00 00 
 804a348:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804a34f:	00 00 00 
 804a352:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804a359:	00 00 00 
 804a35c:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804a363:	00 00 00 
 804a366:	56                   	push   esi
 804a367:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804a36d:	6a 02                	push   0x2
 804a36f:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804a375:	60                   	pusha  
 804a376:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804a37b:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804a381:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804a387:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804a38d:	be 00 00 00 00       	mov    esi,0x0
 804a392:	bf 00 00 00 00       	mov    edi,0x0
 804a397:	bd 00 00 00 00       	mov    ebp,0x0
 804a39c:	39 d8                	cmp    eax,ebx
 804a39e:	76 1d                	jbe    804a3bd <..@1193._jmp>
 804a3a0:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804a3a5:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804a3ab:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804a3b1:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804a3b7:	61                   	popa   
 804a3b8:	83 c4 04             	add    esp,0x4
 804a3bb:	eb 1f                	jmp    804a3dc <..@1121._end>

0804a3bd <..@1193._jmp>:
 804a3bd:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804a3c2:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804a3c8:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804a3ce:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804a3d4:	61                   	popa   
 804a3d5:	83 c4 04             	add    esp,0x4
 804a3d8:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804a3dc <..@1121._end>:
 804a3dc:	89 d7                	mov    edi,edx
 804a3de:	83 c7 0c             	add    edi,0xc
 804a3e1:	89 cd                	mov    ebp,ecx
 804a3e3:	29 fd                	sub    ebp,edi
 804a3e5:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804a3ec:	00 00 00 
 804a3ef:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804a3f6:	00 00 00 
 804a3f9:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804a400:	00 00 00 
 804a403:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804a40a:	00 00 00 
 804a40d:	52                   	push   edx
 804a40e:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804a414:	57                   	push   edi
 804a415:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804a41b:	55                   	push   ebp
 804a41c:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 804a422:	60                   	pusha  
 804a423:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804a428:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804a42e:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804a434:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804a43a:	be 00 00 00 00       	mov    esi,0x0
 804a43f:	bf 00 00 00 00       	mov    edi,0x0
 804a444:	bd 00 00 00 00       	mov    ebp,0x0
 804a449:	39 d8                	cmp    eax,ebx
 804a44b:	72 0e                	jb     804a45b <..@1209.left>
 804a44d:	01 c8                	add    eax,ecx
 804a44f:	01 cb                	add    ebx,ecx

0804a451 <..@1209.right>:
 804a451:	48                   	dec    eax
 804a452:	4b                   	dec    ebx
 804a453:	8b 13                	mov    edx,DWORD PTR [ebx]
 804a455:	89 10                	mov    DWORD PTR [eax],edx
 804a457:	e2 f8                	loop   804a451 <..@1209.right>
 804a459:	eb 08                	jmp    804a463 <..@1209.end>

0804a45b <..@1209.left>:
 804a45b:	8b 13                	mov    edx,DWORD PTR [ebx]
 804a45d:	89 10                	mov    DWORD PTR [eax],edx
 804a45f:	40                   	inc    eax
 804a460:	43                   	inc    ebx
 804a461:	e2 f8                	loop   804a45b <..@1209.left>

0804a463 <..@1209.end>:
 804a463:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804a468:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804a46e:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804a474:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804a47a:	61                   	popa   
 804a47b:	83 e9 0c             	sub    ecx,0xc
 804a47e:	83 eb 0c             	sub    ebx,0xc
 804a481:	83 ea 0c             	sub    edx,0xc
 804a484:	e9 e5 fc ff ff       	jmp    804a16e <..@1122.__jup>

0804a489 <..@1122.__jdown>:
 804a489:	e9 d8 12 00 00       	jmp    804b766 <_________macro_ops_end3>

0804a48e <_________macro_ops_not3_1>:
 804a48e:	83 fd 3e             	cmp    ebp,0x3e
 804a491:	0f 85 ba 03 00 00    	jne    804a851 <_________macro_ops_not3_2>
 804a497:	8b 72 f8             	mov    esi,DWORD PTR [edx-0x8]
 804a49a:	3b 72 10             	cmp    esi,DWORD PTR [edx+0x10]
 804a49d:	7e 09                	jle    804a4a8 <_________macro_ops_cmp_begin2>
 804a49f:	c7 42 10 01 00 00 00 	mov    DWORD PTR [edx+0x10],0x1
 804a4a6:	eb 07                	jmp    804a4af <_________macro_ops_cmp_end2>

0804a4a8 <_________macro_ops_cmp_begin2>:
 804a4a8:	c7 42 10 00 00 00 00 	mov    DWORD PTR [edx+0x10],0x0

0804a4af <_________macro_ops_cmp_end2>:
 804a4af:	6a 00                	push   0x0
 804a4b1:	5e                   	pop    esi
 804a4b2:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804a4b9:	00 00 00 
 804a4bc:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804a4c3:	00 00 00 
 804a4c6:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804a4cd:	00 00 00 
 804a4d0:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804a4d7:	00 00 00 
 804a4da:	56                   	push   esi
 804a4db:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804a4e1:	6a 01                	push   0x1
 804a4e3:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804a4e9:	60                   	pusha  
 804a4ea:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804a4ef:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804a4f5:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804a4fb:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804a501:	be 00 00 00 00       	mov    esi,0x0
 804a506:	bf 00 00 00 00       	mov    edi,0x0
 804a50b:	bd 00 00 00 00       	mov    ebp,0x0
 804a510:	29 d8                	sub    eax,ebx
 804a512:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804a517:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804a51d:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804a523:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804a529:	61                   	popa   
 804a52a:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804a530:	5e                   	pop    esi

0804a531 <..@1229.__jup>:
 804a531:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804a538:	00 00 00 
 804a53b:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804a542:	00 00 00 
 804a545:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804a54c:	00 00 00 
 804a54f:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804a556:	00 00 00 
 804a559:	56                   	push   esi
 804a55a:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804a560:	6a 01                	push   0x1
 804a562:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804a568:	60                   	pusha  
 804a569:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804a56e:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804a574:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804a57a:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804a580:	be 00 00 00 00       	mov    esi,0x0
 804a585:	bf 00 00 00 00       	mov    edi,0x0
 804a58a:	bd 00 00 00 00       	mov    ebp,0x0
 804a58f:	01 d8                	add    eax,ebx
 804a591:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804a596:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804a59c:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804a5a2:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804a5a8:	61                   	popa   
 804a5a9:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804a5af:	5e                   	pop    esi
 804a5b0:	68 fc a6 04 08       	push   0x804a6fc
 804a5b5:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804a5bc:	00 00 00 
 804a5bf:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804a5c6:	00 00 00 
 804a5c9:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804a5d0:	00 00 00 
 804a5d3:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804a5da:	00 00 00 
 804a5dd:	6a 01                	push   0x1
 804a5df:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804a5e5:	6a 00                	push   0x0
 804a5e7:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804a5ed:	60                   	pusha  
 804a5ee:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804a5f3:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804a5f9:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804a5ff:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804a605:	be 00 00 00 00       	mov    esi,0x0
 804a60a:	bf 00 00 00 00       	mov    edi,0x0
 804a60f:	bd 00 00 00 00       	mov    ebp,0x0
 804a614:	39 d8                	cmp    eax,ebx
 804a616:	7c 1d                	jl     804a635 <..@1266._jmp>
 804a618:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804a61d:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804a623:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804a629:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804a62f:	61                   	popa   
 804a630:	83 c4 04             	add    esp,0x4
 804a633:	eb 1f                	jmp    804a654 <..@1266._end>

0804a635 <..@1266._jmp>:
 804a635:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804a63a:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804a640:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804a646:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804a64c:	61                   	popa   
 804a64d:	83 c4 04             	add    esp,0x4
 804a650:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804a654 <..@1266._end>:
 804a654:	68 4c a8 04 08       	push   0x804a84c
 804a659:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804a660:	00 00 00 
 804a663:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804a66a:	00 00 00 
 804a66d:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804a674:	00 00 00 
 804a677:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804a67e:	00 00 00 
 804a681:	56                   	push   esi
 804a682:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804a688:	6a 02                	push   0x2
 804a68a:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804a690:	60                   	pusha  
 804a691:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804a696:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804a69c:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804a6a2:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804a6a8:	be 00 00 00 00       	mov    esi,0x0
 804a6ad:	bf 00 00 00 00       	mov    edi,0x0
 804a6b2:	bd 00 00 00 00       	mov    ebp,0x0
 804a6b7:	39 d8                	cmp    eax,ebx
 804a6b9:	73 1d                	jae    804a6d8 <..@1283._jmp>
 804a6bb:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804a6c0:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804a6c6:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804a6cc:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804a6d2:	61                   	popa   
 804a6d3:	83 c4 04             	add    esp,0x4
 804a6d6:	eb 1f                	jmp    804a6f7 <..@1283._end>

0804a6d8 <..@1283._jmp>:
 804a6d8:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804a6dd:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804a6e3:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804a6e9:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804a6ef:	61                   	popa   
 804a6f0:	83 c4 04             	add    esp,0x4
 804a6f3:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804a6f7 <..@1283._end>:
 804a6f7:	e9 a3 00 00 00       	jmp    804a79f <..@1228._end>

0804a6fc <..@1228._less>:
 804a6fc:	68 4c a8 04 08       	push   0x804a84c
 804a701:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804a708:	00 00 00 
 804a70b:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804a712:	00 00 00 
 804a715:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804a71c:	00 00 00 
 804a71f:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804a726:	00 00 00 
 804a729:	56                   	push   esi
 804a72a:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804a730:	6a 02                	push   0x2
 804a732:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804a738:	60                   	pusha  
 804a739:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804a73e:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804a744:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804a74a:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804a750:	be 00 00 00 00       	mov    esi,0x0
 804a755:	bf 00 00 00 00       	mov    edi,0x0
 804a75a:	bd 00 00 00 00       	mov    ebp,0x0
 804a75f:	39 d8                	cmp    eax,ebx
 804a761:	76 1d                	jbe    804a780 <..@1300._jmp>
 804a763:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804a768:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804a76e:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804a774:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804a77a:	61                   	popa   
 804a77b:	83 c4 04             	add    esp,0x4
 804a77e:	eb 1f                	jmp    804a79f <..@1228._end>

0804a780 <..@1300._jmp>:
 804a780:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804a785:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804a78b:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804a791:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804a797:	61                   	popa   
 804a798:	83 c4 04             	add    esp,0x4
 804a79b:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804a79f <..@1228._end>:
 804a79f:	89 d7                	mov    edi,edx
 804a7a1:	83 c7 0c             	add    edi,0xc
 804a7a4:	89 cd                	mov    ebp,ecx
 804a7a6:	29 fd                	sub    ebp,edi
 804a7a8:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804a7af:	00 00 00 
 804a7b2:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804a7b9:	00 00 00 
 804a7bc:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804a7c3:	00 00 00 
 804a7c6:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804a7cd:	00 00 00 
 804a7d0:	52                   	push   edx
 804a7d1:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804a7d7:	57                   	push   edi
 804a7d8:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804a7de:	55                   	push   ebp
 804a7df:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 804a7e5:	60                   	pusha  
 804a7e6:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804a7eb:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804a7f1:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804a7f7:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804a7fd:	be 00 00 00 00       	mov    esi,0x0
 804a802:	bf 00 00 00 00       	mov    edi,0x0
 804a807:	bd 00 00 00 00       	mov    ebp,0x0
 804a80c:	39 d8                	cmp    eax,ebx
 804a80e:	72 0e                	jb     804a81e <..@1316.left>
 804a810:	01 c8                	add    eax,ecx
 804a812:	01 cb                	add    ebx,ecx

0804a814 <..@1316.right>:
 804a814:	48                   	dec    eax
 804a815:	4b                   	dec    ebx
 804a816:	8b 13                	mov    edx,DWORD PTR [ebx]
 804a818:	89 10                	mov    DWORD PTR [eax],edx
 804a81a:	e2 f8                	loop   804a814 <..@1316.right>
 804a81c:	eb 08                	jmp    804a826 <..@1316.end>

0804a81e <..@1316.left>:
 804a81e:	8b 13                	mov    edx,DWORD PTR [ebx]
 804a820:	89 10                	mov    DWORD PTR [eax],edx
 804a822:	40                   	inc    eax
 804a823:	43                   	inc    ebx
 804a824:	e2 f8                	loop   804a81e <..@1316.left>

0804a826 <..@1316.end>:
 804a826:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804a82b:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804a831:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804a837:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804a83d:	61                   	popa   
 804a83e:	83 e9 0c             	sub    ecx,0xc
 804a841:	83 eb 0c             	sub    ebx,0xc
 804a844:	83 ea 0c             	sub    edx,0xc
 804a847:	e9 e5 fc ff ff       	jmp    804a531 <..@1229.__jup>

0804a84c <..@1229.__jdown>:
 804a84c:	e9 15 0f 00 00       	jmp    804b766 <_________macro_ops_end3>

0804a851 <_________macro_ops_not3_2>:
 804a851:	81 fd 3e 3d 00 00    	cmp    ebp,0x3d3e
 804a857:	0f 85 ba 03 00 00    	jne    804ac17 <_________macro_ops_not3_3>
 804a85d:	8b 72 f8             	mov    esi,DWORD PTR [edx-0x8]
 804a860:	3b 72 10             	cmp    esi,DWORD PTR [edx+0x10]
 804a863:	7c 09                	jl     804a86e <_________macro_ops_cmp_begin3>
 804a865:	c7 42 10 01 00 00 00 	mov    DWORD PTR [edx+0x10],0x1
 804a86c:	eb 07                	jmp    804a875 <_________macro_ops_cmp_end3>

0804a86e <_________macro_ops_cmp_begin3>:
 804a86e:	c7 42 10 00 00 00 00 	mov    DWORD PTR [edx+0x10],0x0

0804a875 <_________macro_ops_cmp_end3>:
 804a875:	6a 00                	push   0x0
 804a877:	5e                   	pop    esi
 804a878:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804a87f:	00 00 00 
 804a882:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804a889:	00 00 00 
 804a88c:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804a893:	00 00 00 
 804a896:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804a89d:	00 00 00 
 804a8a0:	56                   	push   esi
 804a8a1:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804a8a7:	6a 01                	push   0x1
 804a8a9:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804a8af:	60                   	pusha  
 804a8b0:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804a8b5:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804a8bb:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804a8c1:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804a8c7:	be 00 00 00 00       	mov    esi,0x0
 804a8cc:	bf 00 00 00 00       	mov    edi,0x0
 804a8d1:	bd 00 00 00 00       	mov    ebp,0x0
 804a8d6:	29 d8                	sub    eax,ebx
 804a8d8:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804a8dd:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804a8e3:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804a8e9:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804a8ef:	61                   	popa   
 804a8f0:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804a8f6:	5e                   	pop    esi

0804a8f7 <..@1336.__jup>:
 804a8f7:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804a8fe:	00 00 00 
 804a901:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804a908:	00 00 00 
 804a90b:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804a912:	00 00 00 
 804a915:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804a91c:	00 00 00 
 804a91f:	56                   	push   esi
 804a920:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804a926:	6a 01                	push   0x1
 804a928:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804a92e:	60                   	pusha  
 804a92f:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804a934:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804a93a:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804a940:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804a946:	be 00 00 00 00       	mov    esi,0x0
 804a94b:	bf 00 00 00 00       	mov    edi,0x0
 804a950:	bd 00 00 00 00       	mov    ebp,0x0
 804a955:	01 d8                	add    eax,ebx
 804a957:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804a95c:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804a962:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804a968:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804a96e:	61                   	popa   
 804a96f:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804a975:	5e                   	pop    esi
 804a976:	68 c2 aa 04 08       	push   0x804aac2
 804a97b:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804a982:	00 00 00 
 804a985:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804a98c:	00 00 00 
 804a98f:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804a996:	00 00 00 
 804a999:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804a9a0:	00 00 00 
 804a9a3:	6a 01                	push   0x1
 804a9a5:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804a9ab:	6a 00                	push   0x0
 804a9ad:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804a9b3:	60                   	pusha  
 804a9b4:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804a9b9:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804a9bf:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804a9c5:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804a9cb:	be 00 00 00 00       	mov    esi,0x0
 804a9d0:	bf 00 00 00 00       	mov    edi,0x0
 804a9d5:	bd 00 00 00 00       	mov    ebp,0x0
 804a9da:	39 d8                	cmp    eax,ebx
 804a9dc:	7c 1d                	jl     804a9fb <..@1373._jmp>
 804a9de:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804a9e3:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804a9e9:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804a9ef:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804a9f5:	61                   	popa   
 804a9f6:	83 c4 04             	add    esp,0x4
 804a9f9:	eb 1f                	jmp    804aa1a <..@1373._end>

0804a9fb <..@1373._jmp>:
 804a9fb:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804aa00:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804aa06:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804aa0c:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804aa12:	61                   	popa   
 804aa13:	83 c4 04             	add    esp,0x4
 804aa16:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804aa1a <..@1373._end>:
 804aa1a:	68 12 ac 04 08       	push   0x804ac12
 804aa1f:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804aa26:	00 00 00 
 804aa29:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804aa30:	00 00 00 
 804aa33:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804aa3a:	00 00 00 
 804aa3d:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804aa44:	00 00 00 
 804aa47:	56                   	push   esi
 804aa48:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804aa4e:	6a 02                	push   0x2
 804aa50:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804aa56:	60                   	pusha  
 804aa57:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804aa5c:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804aa62:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804aa68:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804aa6e:	be 00 00 00 00       	mov    esi,0x0
 804aa73:	bf 00 00 00 00       	mov    edi,0x0
 804aa78:	bd 00 00 00 00       	mov    ebp,0x0
 804aa7d:	39 d8                	cmp    eax,ebx
 804aa7f:	73 1d                	jae    804aa9e <..@1390._jmp>
 804aa81:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804aa86:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804aa8c:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804aa92:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804aa98:	61                   	popa   
 804aa99:	83 c4 04             	add    esp,0x4
 804aa9c:	eb 1f                	jmp    804aabd <..@1390._end>

0804aa9e <..@1390._jmp>:
 804aa9e:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804aaa3:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804aaa9:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804aaaf:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804aab5:	61                   	popa   
 804aab6:	83 c4 04             	add    esp,0x4
 804aab9:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804aabd <..@1390._end>:
 804aabd:	e9 a3 00 00 00       	jmp    804ab65 <..@1335._end>

0804aac2 <..@1335._less>:
 804aac2:	68 12 ac 04 08       	push   0x804ac12
 804aac7:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804aace:	00 00 00 
 804aad1:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804aad8:	00 00 00 
 804aadb:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804aae2:	00 00 00 
 804aae5:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804aaec:	00 00 00 
 804aaef:	56                   	push   esi
 804aaf0:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804aaf6:	6a 02                	push   0x2
 804aaf8:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804aafe:	60                   	pusha  
 804aaff:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804ab04:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804ab0a:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804ab10:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804ab16:	be 00 00 00 00       	mov    esi,0x0
 804ab1b:	bf 00 00 00 00       	mov    edi,0x0
 804ab20:	bd 00 00 00 00       	mov    ebp,0x0
 804ab25:	39 d8                	cmp    eax,ebx
 804ab27:	76 1d                	jbe    804ab46 <..@1407._jmp>
 804ab29:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804ab2e:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804ab34:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804ab3a:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804ab40:	61                   	popa   
 804ab41:	83 c4 04             	add    esp,0x4
 804ab44:	eb 1f                	jmp    804ab65 <..@1335._end>

0804ab46 <..@1407._jmp>:
 804ab46:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804ab4b:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804ab51:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804ab57:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804ab5d:	61                   	popa   
 804ab5e:	83 c4 04             	add    esp,0x4
 804ab61:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804ab65 <..@1335._end>:
 804ab65:	89 d7                	mov    edi,edx
 804ab67:	83 c7 0c             	add    edi,0xc
 804ab6a:	89 cd                	mov    ebp,ecx
 804ab6c:	29 fd                	sub    ebp,edi
 804ab6e:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804ab75:	00 00 00 
 804ab78:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804ab7f:	00 00 00 
 804ab82:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804ab89:	00 00 00 
 804ab8c:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804ab93:	00 00 00 
 804ab96:	52                   	push   edx
 804ab97:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804ab9d:	57                   	push   edi
 804ab9e:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804aba4:	55                   	push   ebp
 804aba5:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 804abab:	60                   	pusha  
 804abac:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804abb1:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804abb7:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804abbd:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804abc3:	be 00 00 00 00       	mov    esi,0x0
 804abc8:	bf 00 00 00 00       	mov    edi,0x0
 804abcd:	bd 00 00 00 00       	mov    ebp,0x0
 804abd2:	39 d8                	cmp    eax,ebx
 804abd4:	72 0e                	jb     804abe4 <..@1423.left>
 804abd6:	01 c8                	add    eax,ecx
 804abd8:	01 cb                	add    ebx,ecx

0804abda <..@1423.right>:
 804abda:	48                   	dec    eax
 804abdb:	4b                   	dec    ebx
 804abdc:	8b 13                	mov    edx,DWORD PTR [ebx]
 804abde:	89 10                	mov    DWORD PTR [eax],edx
 804abe0:	e2 f8                	loop   804abda <..@1423.right>
 804abe2:	eb 08                	jmp    804abec <..@1423.end>

0804abe4 <..@1423.left>:
 804abe4:	8b 13                	mov    edx,DWORD PTR [ebx]
 804abe6:	89 10                	mov    DWORD PTR [eax],edx
 804abe8:	40                   	inc    eax
 804abe9:	43                   	inc    ebx
 804abea:	e2 f8                	loop   804abe4 <..@1423.left>

0804abec <..@1423.end>:
 804abec:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804abf1:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804abf7:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804abfd:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804ac03:	61                   	popa   
 804ac04:	83 e9 0c             	sub    ecx,0xc
 804ac07:	83 eb 0c             	sub    ebx,0xc
 804ac0a:	83 ea 0c             	sub    edx,0xc
 804ac0d:	e9 e5 fc ff ff       	jmp    804a8f7 <..@1336.__jup>

0804ac12 <..@1336.__jdown>:
 804ac12:	e9 4f 0b 00 00       	jmp    804b766 <_________macro_ops_end3>

0804ac17 <_________macro_ops_not3_3>:
 804ac17:	81 fd 3c 3d 00 00    	cmp    ebp,0x3d3c
 804ac1d:	0f 85 ba 03 00 00    	jne    804afdd <_________macro_ops_not3_4>
 804ac23:	8b 72 f8             	mov    esi,DWORD PTR [edx-0x8]
 804ac26:	3b 72 10             	cmp    esi,DWORD PTR [edx+0x10]
 804ac29:	7f 09                	jg     804ac34 <_________macro_ops_cmp_begin4>
 804ac2b:	c7 42 10 01 00 00 00 	mov    DWORD PTR [edx+0x10],0x1
 804ac32:	eb 07                	jmp    804ac3b <_________macro_ops_cmp_end4>

0804ac34 <_________macro_ops_cmp_begin4>:
 804ac34:	c7 42 10 00 00 00 00 	mov    DWORD PTR [edx+0x10],0x0

0804ac3b <_________macro_ops_cmp_end4>:
 804ac3b:	6a 00                	push   0x0
 804ac3d:	5e                   	pop    esi
 804ac3e:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804ac45:	00 00 00 
 804ac48:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804ac4f:	00 00 00 
 804ac52:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804ac59:	00 00 00 
 804ac5c:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804ac63:	00 00 00 
 804ac66:	56                   	push   esi
 804ac67:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804ac6d:	6a 01                	push   0x1
 804ac6f:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804ac75:	60                   	pusha  
 804ac76:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804ac7b:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804ac81:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804ac87:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804ac8d:	be 00 00 00 00       	mov    esi,0x0
 804ac92:	bf 00 00 00 00       	mov    edi,0x0
 804ac97:	bd 00 00 00 00       	mov    ebp,0x0
 804ac9c:	29 d8                	sub    eax,ebx
 804ac9e:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804aca3:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804aca9:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804acaf:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804acb5:	61                   	popa   
 804acb6:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804acbc:	5e                   	pop    esi

0804acbd <..@1443.__jup>:
 804acbd:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804acc4:	00 00 00 
 804acc7:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804acce:	00 00 00 
 804acd1:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804acd8:	00 00 00 
 804acdb:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804ace2:	00 00 00 
 804ace5:	56                   	push   esi
 804ace6:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804acec:	6a 01                	push   0x1
 804acee:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804acf4:	60                   	pusha  
 804acf5:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804acfa:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804ad00:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804ad06:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804ad0c:	be 00 00 00 00       	mov    esi,0x0
 804ad11:	bf 00 00 00 00       	mov    edi,0x0
 804ad16:	bd 00 00 00 00       	mov    ebp,0x0
 804ad1b:	01 d8                	add    eax,ebx
 804ad1d:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804ad22:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804ad28:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804ad2e:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804ad34:	61                   	popa   
 804ad35:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804ad3b:	5e                   	pop    esi
 804ad3c:	68 88 ae 04 08       	push   0x804ae88
 804ad41:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804ad48:	00 00 00 
 804ad4b:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804ad52:	00 00 00 
 804ad55:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804ad5c:	00 00 00 
 804ad5f:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804ad66:	00 00 00 
 804ad69:	6a 01                	push   0x1
 804ad6b:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804ad71:	6a 00                	push   0x0
 804ad73:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804ad79:	60                   	pusha  
 804ad7a:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804ad7f:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804ad85:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804ad8b:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804ad91:	be 00 00 00 00       	mov    esi,0x0
 804ad96:	bf 00 00 00 00       	mov    edi,0x0
 804ad9b:	bd 00 00 00 00       	mov    ebp,0x0
 804ada0:	39 d8                	cmp    eax,ebx
 804ada2:	7c 1d                	jl     804adc1 <..@1480._jmp>
 804ada4:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804ada9:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804adaf:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804adb5:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804adbb:	61                   	popa   
 804adbc:	83 c4 04             	add    esp,0x4
 804adbf:	eb 1f                	jmp    804ade0 <..@1480._end>

0804adc1 <..@1480._jmp>:
 804adc1:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804adc6:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804adcc:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804add2:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804add8:	61                   	popa   
 804add9:	83 c4 04             	add    esp,0x4
 804addc:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804ade0 <..@1480._end>:
 804ade0:	68 d8 af 04 08       	push   0x804afd8
 804ade5:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804adec:	00 00 00 
 804adef:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804adf6:	00 00 00 
 804adf9:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804ae00:	00 00 00 
 804ae03:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804ae0a:	00 00 00 
 804ae0d:	56                   	push   esi
 804ae0e:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804ae14:	6a 02                	push   0x2
 804ae16:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804ae1c:	60                   	pusha  
 804ae1d:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804ae22:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804ae28:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804ae2e:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804ae34:	be 00 00 00 00       	mov    esi,0x0
 804ae39:	bf 00 00 00 00       	mov    edi,0x0
 804ae3e:	bd 00 00 00 00       	mov    ebp,0x0
 804ae43:	39 d8                	cmp    eax,ebx
 804ae45:	73 1d                	jae    804ae64 <..@1497._jmp>
 804ae47:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804ae4c:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804ae52:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804ae58:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804ae5e:	61                   	popa   
 804ae5f:	83 c4 04             	add    esp,0x4
 804ae62:	eb 1f                	jmp    804ae83 <..@1497._end>

0804ae64 <..@1497._jmp>:
 804ae64:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804ae69:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804ae6f:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804ae75:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804ae7b:	61                   	popa   
 804ae7c:	83 c4 04             	add    esp,0x4
 804ae7f:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804ae83 <..@1497._end>:
 804ae83:	e9 a3 00 00 00       	jmp    804af2b <..@1442._end>

0804ae88 <..@1442._less>:
 804ae88:	68 d8 af 04 08       	push   0x804afd8
 804ae8d:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804ae94:	00 00 00 
 804ae97:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804ae9e:	00 00 00 
 804aea1:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804aea8:	00 00 00 
 804aeab:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804aeb2:	00 00 00 
 804aeb5:	56                   	push   esi
 804aeb6:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804aebc:	6a 02                	push   0x2
 804aebe:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804aec4:	60                   	pusha  
 804aec5:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804aeca:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804aed0:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804aed6:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804aedc:	be 00 00 00 00       	mov    esi,0x0
 804aee1:	bf 00 00 00 00       	mov    edi,0x0
 804aee6:	bd 00 00 00 00       	mov    ebp,0x0
 804aeeb:	39 d8                	cmp    eax,ebx
 804aeed:	76 1d                	jbe    804af0c <..@1514._jmp>
 804aeef:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804aef4:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804aefa:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804af00:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804af06:	61                   	popa   
 804af07:	83 c4 04             	add    esp,0x4
 804af0a:	eb 1f                	jmp    804af2b <..@1442._end>

0804af0c <..@1514._jmp>:
 804af0c:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804af11:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804af17:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804af1d:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804af23:	61                   	popa   
 804af24:	83 c4 04             	add    esp,0x4
 804af27:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804af2b <..@1442._end>:
 804af2b:	89 d7                	mov    edi,edx
 804af2d:	83 c7 0c             	add    edi,0xc
 804af30:	89 cd                	mov    ebp,ecx
 804af32:	29 fd                	sub    ebp,edi
 804af34:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804af3b:	00 00 00 
 804af3e:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804af45:	00 00 00 
 804af48:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804af4f:	00 00 00 
 804af52:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804af59:	00 00 00 
 804af5c:	52                   	push   edx
 804af5d:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804af63:	57                   	push   edi
 804af64:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804af6a:	55                   	push   ebp
 804af6b:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 804af71:	60                   	pusha  
 804af72:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804af77:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804af7d:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804af83:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804af89:	be 00 00 00 00       	mov    esi,0x0
 804af8e:	bf 00 00 00 00       	mov    edi,0x0
 804af93:	bd 00 00 00 00       	mov    ebp,0x0
 804af98:	39 d8                	cmp    eax,ebx
 804af9a:	72 0e                	jb     804afaa <..@1530.left>
 804af9c:	01 c8                	add    eax,ecx
 804af9e:	01 cb                	add    ebx,ecx

0804afa0 <..@1530.right>:
 804afa0:	48                   	dec    eax
 804afa1:	4b                   	dec    ebx
 804afa2:	8b 13                	mov    edx,DWORD PTR [ebx]
 804afa4:	89 10                	mov    DWORD PTR [eax],edx
 804afa6:	e2 f8                	loop   804afa0 <..@1530.right>
 804afa8:	eb 08                	jmp    804afb2 <..@1530.end>

0804afaa <..@1530.left>:
 804afaa:	8b 13                	mov    edx,DWORD PTR [ebx]
 804afac:	89 10                	mov    DWORD PTR [eax],edx
 804afae:	40                   	inc    eax
 804afaf:	43                   	inc    ebx
 804afb0:	e2 f8                	loop   804afaa <..@1530.left>

0804afb2 <..@1530.end>:
 804afb2:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804afb7:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804afbd:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804afc3:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804afc9:	61                   	popa   
 804afca:	83 e9 0c             	sub    ecx,0xc
 804afcd:	83 eb 0c             	sub    ebx,0xc
 804afd0:	83 ea 0c             	sub    edx,0xc
 804afd3:	e9 e5 fc ff ff       	jmp    804acbd <..@1443.__jup>

0804afd8 <..@1443.__jdown>:
 804afd8:	e9 89 07 00 00       	jmp    804b766 <_________macro_ops_end3>

0804afdd <_________macro_ops_not3_4>:
 804afdd:	81 fd 3d 3d 00 00    	cmp    ebp,0x3d3d
 804afe3:	0f 85 ba 03 00 00    	jne    804b3a3 <_________macro_ops_not3_5>
 804afe9:	8b 72 f8             	mov    esi,DWORD PTR [edx-0x8]
 804afec:	3b 72 10             	cmp    esi,DWORD PTR [edx+0x10]
 804afef:	75 09                	jne    804affa <_________macro_ops_cmp_begin5>
 804aff1:	c7 42 10 01 00 00 00 	mov    DWORD PTR [edx+0x10],0x1
 804aff8:	eb 07                	jmp    804b001 <_________macro_ops_cmp_end5>

0804affa <_________macro_ops_cmp_begin5>:
 804affa:	c7 42 10 00 00 00 00 	mov    DWORD PTR [edx+0x10],0x0

0804b001 <_________macro_ops_cmp_end5>:
 804b001:	6a 00                	push   0x0
 804b003:	5e                   	pop    esi
 804b004:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804b00b:	00 00 00 
 804b00e:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804b015:	00 00 00 
 804b018:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804b01f:	00 00 00 
 804b022:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804b029:	00 00 00 
 804b02c:	56                   	push   esi
 804b02d:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804b033:	6a 01                	push   0x1
 804b035:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804b03b:	60                   	pusha  
 804b03c:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804b041:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804b047:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804b04d:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804b053:	be 00 00 00 00       	mov    esi,0x0
 804b058:	bf 00 00 00 00       	mov    edi,0x0
 804b05d:	bd 00 00 00 00       	mov    ebp,0x0
 804b062:	29 d8                	sub    eax,ebx
 804b064:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804b069:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804b06f:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804b075:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804b07b:	61                   	popa   
 804b07c:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804b082:	5e                   	pop    esi

0804b083 <..@1550.__jup>:
 804b083:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804b08a:	00 00 00 
 804b08d:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804b094:	00 00 00 
 804b097:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804b09e:	00 00 00 
 804b0a1:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804b0a8:	00 00 00 
 804b0ab:	56                   	push   esi
 804b0ac:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804b0b2:	6a 01                	push   0x1
 804b0b4:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804b0ba:	60                   	pusha  
 804b0bb:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804b0c0:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804b0c6:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804b0cc:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804b0d2:	be 00 00 00 00       	mov    esi,0x0
 804b0d7:	bf 00 00 00 00       	mov    edi,0x0
 804b0dc:	bd 00 00 00 00       	mov    ebp,0x0
 804b0e1:	01 d8                	add    eax,ebx
 804b0e3:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804b0e8:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804b0ee:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804b0f4:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804b0fa:	61                   	popa   
 804b0fb:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804b101:	5e                   	pop    esi
 804b102:	68 4e b2 04 08       	push   0x804b24e
 804b107:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804b10e:	00 00 00 
 804b111:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804b118:	00 00 00 
 804b11b:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804b122:	00 00 00 
 804b125:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804b12c:	00 00 00 
 804b12f:	6a 01                	push   0x1
 804b131:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804b137:	6a 00                	push   0x0
 804b139:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804b13f:	60                   	pusha  
 804b140:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804b145:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804b14b:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804b151:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804b157:	be 00 00 00 00       	mov    esi,0x0
 804b15c:	bf 00 00 00 00       	mov    edi,0x0
 804b161:	bd 00 00 00 00       	mov    ebp,0x0
 804b166:	39 d8                	cmp    eax,ebx
 804b168:	7c 1d                	jl     804b187 <..@1587._jmp>
 804b16a:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804b16f:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804b175:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804b17b:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804b181:	61                   	popa   
 804b182:	83 c4 04             	add    esp,0x4
 804b185:	eb 1f                	jmp    804b1a6 <..@1587._end>

0804b187 <..@1587._jmp>:
 804b187:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804b18c:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804b192:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804b198:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804b19e:	61                   	popa   
 804b19f:	83 c4 04             	add    esp,0x4
 804b1a2:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804b1a6 <..@1587._end>:
 804b1a6:	68 9e b3 04 08       	push   0x804b39e
 804b1ab:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804b1b2:	00 00 00 
 804b1b5:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804b1bc:	00 00 00 
 804b1bf:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804b1c6:	00 00 00 
 804b1c9:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804b1d0:	00 00 00 
 804b1d3:	56                   	push   esi
 804b1d4:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804b1da:	6a 02                	push   0x2
 804b1dc:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804b1e2:	60                   	pusha  
 804b1e3:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804b1e8:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804b1ee:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804b1f4:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804b1fa:	be 00 00 00 00       	mov    esi,0x0
 804b1ff:	bf 00 00 00 00       	mov    edi,0x0
 804b204:	bd 00 00 00 00       	mov    ebp,0x0
 804b209:	39 d8                	cmp    eax,ebx
 804b20b:	73 1d                	jae    804b22a <..@1604._jmp>
 804b20d:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804b212:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804b218:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804b21e:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804b224:	61                   	popa   
 804b225:	83 c4 04             	add    esp,0x4
 804b228:	eb 1f                	jmp    804b249 <..@1604._end>

0804b22a <..@1604._jmp>:
 804b22a:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804b22f:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804b235:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804b23b:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804b241:	61                   	popa   
 804b242:	83 c4 04             	add    esp,0x4
 804b245:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804b249 <..@1604._end>:
 804b249:	e9 a3 00 00 00       	jmp    804b2f1 <..@1549._end>

0804b24e <..@1549._less>:
 804b24e:	68 9e b3 04 08       	push   0x804b39e
 804b253:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804b25a:	00 00 00 
 804b25d:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804b264:	00 00 00 
 804b267:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804b26e:	00 00 00 
 804b271:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804b278:	00 00 00 
 804b27b:	56                   	push   esi
 804b27c:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804b282:	6a 02                	push   0x2
 804b284:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804b28a:	60                   	pusha  
 804b28b:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804b290:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804b296:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804b29c:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804b2a2:	be 00 00 00 00       	mov    esi,0x0
 804b2a7:	bf 00 00 00 00       	mov    edi,0x0
 804b2ac:	bd 00 00 00 00       	mov    ebp,0x0
 804b2b1:	39 d8                	cmp    eax,ebx
 804b2b3:	76 1d                	jbe    804b2d2 <..@1621._jmp>
 804b2b5:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804b2ba:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804b2c0:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804b2c6:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804b2cc:	61                   	popa   
 804b2cd:	83 c4 04             	add    esp,0x4
 804b2d0:	eb 1f                	jmp    804b2f1 <..@1549._end>

0804b2d2 <..@1621._jmp>:
 804b2d2:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804b2d7:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804b2dd:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804b2e3:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804b2e9:	61                   	popa   
 804b2ea:	83 c4 04             	add    esp,0x4
 804b2ed:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804b2f1 <..@1549._end>:
 804b2f1:	89 d7                	mov    edi,edx
 804b2f3:	83 c7 0c             	add    edi,0xc
 804b2f6:	89 cd                	mov    ebp,ecx
 804b2f8:	29 fd                	sub    ebp,edi
 804b2fa:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804b301:	00 00 00 
 804b304:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804b30b:	00 00 00 
 804b30e:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804b315:	00 00 00 
 804b318:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804b31f:	00 00 00 
 804b322:	52                   	push   edx
 804b323:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804b329:	57                   	push   edi
 804b32a:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804b330:	55                   	push   ebp
 804b331:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 804b337:	60                   	pusha  
 804b338:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804b33d:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804b343:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804b349:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804b34f:	be 00 00 00 00       	mov    esi,0x0
 804b354:	bf 00 00 00 00       	mov    edi,0x0
 804b359:	bd 00 00 00 00       	mov    ebp,0x0
 804b35e:	39 d8                	cmp    eax,ebx
 804b360:	72 0e                	jb     804b370 <..@1637.left>
 804b362:	01 c8                	add    eax,ecx
 804b364:	01 cb                	add    ebx,ecx

0804b366 <..@1637.right>:
 804b366:	48                   	dec    eax
 804b367:	4b                   	dec    ebx
 804b368:	8b 13                	mov    edx,DWORD PTR [ebx]
 804b36a:	89 10                	mov    DWORD PTR [eax],edx
 804b36c:	e2 f8                	loop   804b366 <..@1637.right>
 804b36e:	eb 08                	jmp    804b378 <..@1637.end>

0804b370 <..@1637.left>:
 804b370:	8b 13                	mov    edx,DWORD PTR [ebx]
 804b372:	89 10                	mov    DWORD PTR [eax],edx
 804b374:	40                   	inc    eax
 804b375:	43                   	inc    ebx
 804b376:	e2 f8                	loop   804b370 <..@1637.left>

0804b378 <..@1637.end>:
 804b378:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804b37d:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804b383:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804b389:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804b38f:	61                   	popa   
 804b390:	83 e9 0c             	sub    ecx,0xc
 804b393:	83 eb 0c             	sub    ebx,0xc
 804b396:	83 ea 0c             	sub    edx,0xc
 804b399:	e9 e5 fc ff ff       	jmp    804b083 <..@1550.__jup>

0804b39e <..@1550.__jdown>:
 804b39e:	e9 c3 03 00 00       	jmp    804b766 <_________macro_ops_end3>

0804b3a3 <_________macro_ops_not3_5>:
 804b3a3:	81 fd 21 3d 00 00    	cmp    ebp,0x3d21
 804b3a9:	0f 85 b7 03 00 00    	jne    804b766 <_________macro_ops_end3>
 804b3af:	8b 72 f8             	mov    esi,DWORD PTR [edx-0x8]
 804b3b2:	3b 72 10             	cmp    esi,DWORD PTR [edx+0x10]
 804b3b5:	74 09                	je     804b3c0 <_________macro_ops_cmp_begin6>
 804b3b7:	c7 42 10 01 00 00 00 	mov    DWORD PTR [edx+0x10],0x1
 804b3be:	eb 07                	jmp    804b3c7 <_________macro_ops_cmp_end6>

0804b3c0 <_________macro_ops_cmp_begin6>:
 804b3c0:	c7 42 10 00 00 00 00 	mov    DWORD PTR [edx+0x10],0x0

0804b3c7 <_________macro_ops_cmp_end6>:
 804b3c7:	6a 00                	push   0x0
 804b3c9:	5e                   	pop    esi
 804b3ca:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804b3d1:	00 00 00 
 804b3d4:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804b3db:	00 00 00 
 804b3de:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804b3e5:	00 00 00 
 804b3e8:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804b3ef:	00 00 00 
 804b3f2:	56                   	push   esi
 804b3f3:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804b3f9:	6a 01                	push   0x1
 804b3fb:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804b401:	60                   	pusha  
 804b402:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804b407:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804b40d:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804b413:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804b419:	be 00 00 00 00       	mov    esi,0x0
 804b41e:	bf 00 00 00 00       	mov    edi,0x0
 804b423:	bd 00 00 00 00       	mov    ebp,0x0
 804b428:	29 d8                	sub    eax,ebx
 804b42a:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804b42f:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804b435:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804b43b:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804b441:	61                   	popa   
 804b442:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804b448:	5e                   	pop    esi

0804b449 <..@1657.__jup>:
 804b449:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804b450:	00 00 00 
 804b453:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804b45a:	00 00 00 
 804b45d:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804b464:	00 00 00 
 804b467:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804b46e:	00 00 00 
 804b471:	56                   	push   esi
 804b472:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804b478:	6a 01                	push   0x1
 804b47a:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804b480:	60                   	pusha  
 804b481:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804b486:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804b48c:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804b492:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804b498:	be 00 00 00 00       	mov    esi,0x0
 804b49d:	bf 00 00 00 00       	mov    edi,0x0
 804b4a2:	bd 00 00 00 00       	mov    ebp,0x0
 804b4a7:	01 d8                	add    eax,ebx
 804b4a9:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804b4ae:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804b4b4:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804b4ba:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804b4c0:	61                   	popa   
 804b4c1:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804b4c7:	5e                   	pop    esi
 804b4c8:	68 14 b6 04 08       	push   0x804b614
 804b4cd:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804b4d4:	00 00 00 
 804b4d7:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804b4de:	00 00 00 
 804b4e1:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804b4e8:	00 00 00 
 804b4eb:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804b4f2:	00 00 00 
 804b4f5:	6a 01                	push   0x1
 804b4f7:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804b4fd:	6a 00                	push   0x0
 804b4ff:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804b505:	60                   	pusha  
 804b506:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804b50b:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804b511:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804b517:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804b51d:	be 00 00 00 00       	mov    esi,0x0
 804b522:	bf 00 00 00 00       	mov    edi,0x0
 804b527:	bd 00 00 00 00       	mov    ebp,0x0
 804b52c:	39 d8                	cmp    eax,ebx
 804b52e:	7c 1d                	jl     804b54d <..@1694._jmp>
 804b530:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804b535:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804b53b:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804b541:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804b547:	61                   	popa   
 804b548:	83 c4 04             	add    esp,0x4
 804b54b:	eb 1f                	jmp    804b56c <..@1694._end>

0804b54d <..@1694._jmp>:
 804b54d:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804b552:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804b558:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804b55e:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804b564:	61                   	popa   
 804b565:	83 c4 04             	add    esp,0x4
 804b568:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804b56c <..@1694._end>:
 804b56c:	68 64 b7 04 08       	push   0x804b764
 804b571:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804b578:	00 00 00 
 804b57b:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804b582:	00 00 00 
 804b585:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804b58c:	00 00 00 
 804b58f:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804b596:	00 00 00 
 804b599:	56                   	push   esi
 804b59a:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804b5a0:	6a 02                	push   0x2
 804b5a2:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804b5a8:	60                   	pusha  
 804b5a9:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804b5ae:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804b5b4:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804b5ba:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804b5c0:	be 00 00 00 00       	mov    esi,0x0
 804b5c5:	bf 00 00 00 00       	mov    edi,0x0
 804b5ca:	bd 00 00 00 00       	mov    ebp,0x0
 804b5cf:	39 d8                	cmp    eax,ebx
 804b5d1:	73 1d                	jae    804b5f0 <..@1711._jmp>
 804b5d3:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804b5d8:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804b5de:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804b5e4:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804b5ea:	61                   	popa   
 804b5eb:	83 c4 04             	add    esp,0x4
 804b5ee:	eb 1f                	jmp    804b60f <..@1711._end>

0804b5f0 <..@1711._jmp>:
 804b5f0:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804b5f5:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804b5fb:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804b601:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804b607:	61                   	popa   
 804b608:	83 c4 04             	add    esp,0x4
 804b60b:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804b60f <..@1711._end>:
 804b60f:	e9 a3 00 00 00       	jmp    804b6b7 <..@1656._end>

0804b614 <..@1656._less>:
 804b614:	68 64 b7 04 08       	push   0x804b764
 804b619:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804b620:	00 00 00 
 804b623:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804b62a:	00 00 00 
 804b62d:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804b634:	00 00 00 
 804b637:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804b63e:	00 00 00 
 804b641:	56                   	push   esi
 804b642:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804b648:	6a 02                	push   0x2
 804b64a:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804b650:	60                   	pusha  
 804b651:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804b656:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804b65c:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804b662:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804b668:	be 00 00 00 00       	mov    esi,0x0
 804b66d:	bf 00 00 00 00       	mov    edi,0x0
 804b672:	bd 00 00 00 00       	mov    ebp,0x0
 804b677:	39 d8                	cmp    eax,ebx
 804b679:	76 1d                	jbe    804b698 <..@1728._jmp>
 804b67b:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804b680:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804b686:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804b68c:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804b692:	61                   	popa   
 804b693:	83 c4 04             	add    esp,0x4
 804b696:	eb 1f                	jmp    804b6b7 <..@1656._end>

0804b698 <..@1728._jmp>:
 804b698:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804b69d:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804b6a3:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804b6a9:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804b6af:	61                   	popa   
 804b6b0:	83 c4 04             	add    esp,0x4
 804b6b3:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804b6b7 <..@1656._end>:
 804b6b7:	89 d7                	mov    edi,edx
 804b6b9:	83 c7 0c             	add    edi,0xc
 804b6bc:	89 cd                	mov    ebp,ecx
 804b6be:	29 fd                	sub    ebp,edi
 804b6c0:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804b6c7:	00 00 00 
 804b6ca:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804b6d1:	00 00 00 
 804b6d4:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804b6db:	00 00 00 
 804b6de:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804b6e5:	00 00 00 
 804b6e8:	52                   	push   edx
 804b6e9:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804b6ef:	57                   	push   edi
 804b6f0:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804b6f6:	55                   	push   ebp
 804b6f7:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 804b6fd:	60                   	pusha  
 804b6fe:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804b703:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804b709:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804b70f:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804b715:	be 00 00 00 00       	mov    esi,0x0
 804b71a:	bf 00 00 00 00       	mov    edi,0x0
 804b71f:	bd 00 00 00 00       	mov    ebp,0x0
 804b724:	39 d8                	cmp    eax,ebx
 804b726:	72 0e                	jb     804b736 <..@1744.left>
 804b728:	01 c8                	add    eax,ecx
 804b72a:	01 cb                	add    ebx,ecx

0804b72c <..@1744.right>:
 804b72c:	48                   	dec    eax
 804b72d:	4b                   	dec    ebx
 804b72e:	8b 13                	mov    edx,DWORD PTR [ebx]
 804b730:	89 10                	mov    DWORD PTR [eax],edx
 804b732:	e2 f8                	loop   804b72c <..@1744.right>
 804b734:	eb 08                	jmp    804b73e <..@1744.end>

0804b736 <..@1744.left>:
 804b736:	8b 13                	mov    edx,DWORD PTR [ebx]
 804b738:	89 10                	mov    DWORD PTR [eax],edx
 804b73a:	40                   	inc    eax
 804b73b:	43                   	inc    ebx
 804b73c:	e2 f8                	loop   804b736 <..@1744.left>

0804b73e <..@1744.end>:
 804b73e:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804b743:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804b749:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804b74f:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804b755:	61                   	popa   
 804b756:	83 e9 0c             	sub    ecx,0xc
 804b759:	83 eb 0c             	sub    ebx,0xc
 804b75c:	83 ea 0c             	sub    edx,0xc
 804b75f:	e9 e5 fc ff ff       	jmp    804b449 <..@1657.__jup>

0804b764 <..@1657.__jdown>:
 804b764:	eb 00                	jmp    804b766 <_________macro_ops_end3>

0804b766 <_________macro_ops_end3>:
 804b766:	83 c2 0c             	add    edx,0xc
 804b769:	e9 3a e9 ff ff       	jmp    804a0a8 <_________macro_ops_for_begin3>

0804b76e <_________macro_ops_for_end3>:
 804b76e:	89 c2                	mov    edx,eax

0804b770 <_________macro_ops_for_begin4>:
 804b770:	39 da                	cmp    edx,ebx
 804b772:	0f 83 ce 07 00 00    	jae    804bf46 <_________macro_ops_for_end4>
 804b778:	68 87 b7 04 08       	push   0x804b787
 804b77d:	68 72 01 00 00       	push   0x172
 804b782:	e9 f9 c8 ff ff       	jmp    8048080 <macro_pr_jmp>

0804b787 <..@1761._1>:
 804b787:	83 3a 02             	cmp    DWORD PTR [edx],0x2
 804b78a:	0f 85 ae 07 00 00    	jne    804bf3e <_________macro_ops_end4>
 804b790:	8b 6a 04             	mov    ebp,DWORD PTR [edx+0x4]
 804b793:	81 fd 61 6e 64 00    	cmp    ebp,0x646e61
 804b799:	0f 85 cb 03 00 00    	jne    804bb6a <_________macro_ops_not4_1>
 804b79f:	8b 72 f8             	mov    esi,DWORD PTR [edx-0x8]
 804b7a2:	83 fe 00             	cmp    esi,0x0
 804b7a5:	74 1a                	je     804b7c1 <_________macro_ops_cmp_begin7>
 804b7a7:	8b 72 10             	mov    esi,DWORD PTR [edx+0x10]
 804b7aa:	83 fe 00             	cmp    esi,0x0
 804b7ad:	74 09                	je     804b7b8 <_________macro_ops_cmp_begin8>
 804b7af:	c7 42 10 01 00 00 00 	mov    DWORD PTR [edx+0x10],0x1
 804b7b6:	eb 07                	jmp    804b7bf <_________macro_ops_cmp_end8>

0804b7b8 <_________macro_ops_cmp_begin8>:
 804b7b8:	c7 42 10 00 00 00 00 	mov    DWORD PTR [edx+0x10],0x0

0804b7bf <_________macro_ops_cmp_end8>:
 804b7bf:	eb 07                	jmp    804b7c8 <_________macro_ops_cmp_end7>

0804b7c1 <_________macro_ops_cmp_begin7>:
 804b7c1:	c7 42 10 00 00 00 00 	mov    DWORD PTR [edx+0x10],0x0

0804b7c8 <_________macro_ops_cmp_end7>:
 804b7c8:	6a 00                	push   0x0
 804b7ca:	5e                   	pop    esi
 804b7cb:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804b7d2:	00 00 00 
 804b7d5:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804b7dc:	00 00 00 
 804b7df:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804b7e6:	00 00 00 
 804b7e9:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804b7f0:	00 00 00 
 804b7f3:	56                   	push   esi
 804b7f4:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804b7fa:	6a 01                	push   0x1
 804b7fc:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804b802:	60                   	pusha  
 804b803:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804b808:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804b80e:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804b814:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804b81a:	be 00 00 00 00       	mov    esi,0x0
 804b81f:	bf 00 00 00 00       	mov    edi,0x0
 804b824:	bd 00 00 00 00       	mov    ebp,0x0
 804b829:	29 d8                	sub    eax,ebx
 804b82b:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804b830:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804b836:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804b83c:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804b842:	61                   	popa   
 804b843:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804b849:	5e                   	pop    esi

0804b84a <..@1767.__jup>:
 804b84a:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804b851:	00 00 00 
 804b854:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804b85b:	00 00 00 
 804b85e:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804b865:	00 00 00 
 804b868:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804b86f:	00 00 00 
 804b872:	56                   	push   esi
 804b873:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804b879:	6a 01                	push   0x1
 804b87b:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804b881:	60                   	pusha  
 804b882:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804b887:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804b88d:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804b893:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804b899:	be 00 00 00 00       	mov    esi,0x0
 804b89e:	bf 00 00 00 00       	mov    edi,0x0
 804b8a3:	bd 00 00 00 00       	mov    ebp,0x0
 804b8a8:	01 d8                	add    eax,ebx
 804b8aa:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804b8af:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804b8b5:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804b8bb:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804b8c1:	61                   	popa   
 804b8c2:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804b8c8:	5e                   	pop    esi
 804b8c9:	68 15 ba 04 08       	push   0x804ba15
 804b8ce:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804b8d5:	00 00 00 
 804b8d8:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804b8df:	00 00 00 
 804b8e2:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804b8e9:	00 00 00 
 804b8ec:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804b8f3:	00 00 00 
 804b8f6:	6a 01                	push   0x1
 804b8f8:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804b8fe:	6a 00                	push   0x0
 804b900:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804b906:	60                   	pusha  
 804b907:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804b90c:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804b912:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804b918:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804b91e:	be 00 00 00 00       	mov    esi,0x0
 804b923:	bf 00 00 00 00       	mov    edi,0x0
 804b928:	bd 00 00 00 00       	mov    ebp,0x0
 804b92d:	39 d8                	cmp    eax,ebx
 804b92f:	7c 1d                	jl     804b94e <..@1804._jmp>
 804b931:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804b936:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804b93c:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804b942:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804b948:	61                   	popa   
 804b949:	83 c4 04             	add    esp,0x4
 804b94c:	eb 1f                	jmp    804b96d <..@1804._end>

0804b94e <..@1804._jmp>:
 804b94e:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804b953:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804b959:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804b95f:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804b965:	61                   	popa   
 804b966:	83 c4 04             	add    esp,0x4
 804b969:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804b96d <..@1804._end>:
 804b96d:	68 65 bb 04 08       	push   0x804bb65
 804b972:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804b979:	00 00 00 
 804b97c:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804b983:	00 00 00 
 804b986:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804b98d:	00 00 00 
 804b990:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804b997:	00 00 00 
 804b99a:	56                   	push   esi
 804b99b:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804b9a1:	6a 02                	push   0x2
 804b9a3:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804b9a9:	60                   	pusha  
 804b9aa:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804b9af:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804b9b5:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804b9bb:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804b9c1:	be 00 00 00 00       	mov    esi,0x0
 804b9c6:	bf 00 00 00 00       	mov    edi,0x0
 804b9cb:	bd 00 00 00 00       	mov    ebp,0x0
 804b9d0:	39 d8                	cmp    eax,ebx
 804b9d2:	73 1d                	jae    804b9f1 <..@1821._jmp>
 804b9d4:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804b9d9:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804b9df:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804b9e5:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804b9eb:	61                   	popa   
 804b9ec:	83 c4 04             	add    esp,0x4
 804b9ef:	eb 1f                	jmp    804ba10 <..@1821._end>

0804b9f1 <..@1821._jmp>:
 804b9f1:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804b9f6:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804b9fc:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804ba02:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804ba08:	61                   	popa   
 804ba09:	83 c4 04             	add    esp,0x4
 804ba0c:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804ba10 <..@1821._end>:
 804ba10:	e9 a3 00 00 00       	jmp    804bab8 <..@1766._end>

0804ba15 <..@1766._less>:
 804ba15:	68 65 bb 04 08       	push   0x804bb65
 804ba1a:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804ba21:	00 00 00 
 804ba24:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804ba2b:	00 00 00 
 804ba2e:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804ba35:	00 00 00 
 804ba38:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804ba3f:	00 00 00 
 804ba42:	56                   	push   esi
 804ba43:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804ba49:	6a 02                	push   0x2
 804ba4b:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804ba51:	60                   	pusha  
 804ba52:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804ba57:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804ba5d:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804ba63:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804ba69:	be 00 00 00 00       	mov    esi,0x0
 804ba6e:	bf 00 00 00 00       	mov    edi,0x0
 804ba73:	bd 00 00 00 00       	mov    ebp,0x0
 804ba78:	39 d8                	cmp    eax,ebx
 804ba7a:	76 1d                	jbe    804ba99 <..@1838._jmp>
 804ba7c:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804ba81:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804ba87:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804ba8d:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804ba93:	61                   	popa   
 804ba94:	83 c4 04             	add    esp,0x4
 804ba97:	eb 1f                	jmp    804bab8 <..@1766._end>

0804ba99 <..@1838._jmp>:
 804ba99:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804ba9e:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804baa4:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804baaa:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804bab0:	61                   	popa   
 804bab1:	83 c4 04             	add    esp,0x4
 804bab4:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804bab8 <..@1766._end>:
 804bab8:	89 d7                	mov    edi,edx
 804baba:	83 c7 0c             	add    edi,0xc
 804babd:	89 cd                	mov    ebp,ecx
 804babf:	29 fd                	sub    ebp,edi
 804bac1:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804bac8:	00 00 00 
 804bacb:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804bad2:	00 00 00 
 804bad5:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804badc:	00 00 00 
 804badf:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804bae6:	00 00 00 
 804bae9:	52                   	push   edx
 804baea:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804baf0:	57                   	push   edi
 804baf1:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804baf7:	55                   	push   ebp
 804baf8:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 804bafe:	60                   	pusha  
 804baff:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804bb04:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804bb0a:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804bb10:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804bb16:	be 00 00 00 00       	mov    esi,0x0
 804bb1b:	bf 00 00 00 00       	mov    edi,0x0
 804bb20:	bd 00 00 00 00       	mov    ebp,0x0
 804bb25:	39 d8                	cmp    eax,ebx
 804bb27:	72 0e                	jb     804bb37 <..@1854.left>
 804bb29:	01 c8                	add    eax,ecx
 804bb2b:	01 cb                	add    ebx,ecx

0804bb2d <..@1854.right>:
 804bb2d:	48                   	dec    eax
 804bb2e:	4b                   	dec    ebx
 804bb2f:	8b 13                	mov    edx,DWORD PTR [ebx]
 804bb31:	89 10                	mov    DWORD PTR [eax],edx
 804bb33:	e2 f8                	loop   804bb2d <..@1854.right>
 804bb35:	eb 08                	jmp    804bb3f <..@1854.end>

0804bb37 <..@1854.left>:
 804bb37:	8b 13                	mov    edx,DWORD PTR [ebx]
 804bb39:	89 10                	mov    DWORD PTR [eax],edx
 804bb3b:	40                   	inc    eax
 804bb3c:	43                   	inc    ebx
 804bb3d:	e2 f8                	loop   804bb37 <..@1854.left>

0804bb3f <..@1854.end>:
 804bb3f:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804bb44:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804bb4a:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804bb50:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804bb56:	61                   	popa   
 804bb57:	83 e9 0c             	sub    ecx,0xc
 804bb5a:	83 eb 0c             	sub    ebx,0xc
 804bb5d:	83 ea 0c             	sub    edx,0xc
 804bb60:	e9 e5 fc ff ff       	jmp    804b84a <..@1767.__jup>

0804bb65 <..@1767.__jdown>:
 804bb65:	e9 d4 03 00 00       	jmp    804bf3e <_________macro_ops_end4>

0804bb6a <_________macro_ops_not4_1>:
 804bb6a:	81 fd 26 26 00 00    	cmp    ebp,0x2626
 804bb70:	0f 85 c8 03 00 00    	jne    804bf3e <_________macro_ops_end4>
 804bb76:	8b 72 f8             	mov    esi,DWORD PTR [edx-0x8]
 804bb79:	83 fe 00             	cmp    esi,0x0
 804bb7c:	74 1a                	je     804bb98 <_________macro_ops_cmp_begin11>
 804bb7e:	8b 72 10             	mov    esi,DWORD PTR [edx+0x10]
 804bb81:	83 fe 00             	cmp    esi,0x0
 804bb84:	74 09                	je     804bb8f <_________macro_ops_cmp_begin12>
 804bb86:	c7 42 10 01 00 00 00 	mov    DWORD PTR [edx+0x10],0x1
 804bb8d:	eb 07                	jmp    804bb96 <_________macro_ops_cmp_end12>

0804bb8f <_________macro_ops_cmp_begin12>:
 804bb8f:	c7 42 10 00 00 00 00 	mov    DWORD PTR [edx+0x10],0x0

0804bb96 <_________macro_ops_cmp_end12>:
 804bb96:	eb 07                	jmp    804bb9f <_________macro_ops_cmp_end11>

0804bb98 <_________macro_ops_cmp_begin11>:
 804bb98:	c7 42 10 00 00 00 00 	mov    DWORD PTR [edx+0x10],0x0

0804bb9f <_________macro_ops_cmp_end11>:
 804bb9f:	6a 00                	push   0x0
 804bba1:	5e                   	pop    esi
 804bba2:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804bba9:	00 00 00 
 804bbac:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804bbb3:	00 00 00 
 804bbb6:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804bbbd:	00 00 00 
 804bbc0:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804bbc7:	00 00 00 
 804bbca:	56                   	push   esi
 804bbcb:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804bbd1:	6a 01                	push   0x1
 804bbd3:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804bbd9:	60                   	pusha  
 804bbda:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804bbdf:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804bbe5:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804bbeb:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804bbf1:	be 00 00 00 00       	mov    esi,0x0
 804bbf6:	bf 00 00 00 00       	mov    edi,0x0
 804bbfb:	bd 00 00 00 00       	mov    ebp,0x0
 804bc00:	29 d8                	sub    eax,ebx
 804bc02:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804bc07:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804bc0d:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804bc13:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804bc19:	61                   	popa   
 804bc1a:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804bc20:	5e                   	pop    esi

0804bc21 <..@1874.__jup>:
 804bc21:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804bc28:	00 00 00 
 804bc2b:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804bc32:	00 00 00 
 804bc35:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804bc3c:	00 00 00 
 804bc3f:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804bc46:	00 00 00 
 804bc49:	56                   	push   esi
 804bc4a:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804bc50:	6a 01                	push   0x1
 804bc52:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804bc58:	60                   	pusha  
 804bc59:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804bc5e:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804bc64:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804bc6a:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804bc70:	be 00 00 00 00       	mov    esi,0x0
 804bc75:	bf 00 00 00 00       	mov    edi,0x0
 804bc7a:	bd 00 00 00 00       	mov    ebp,0x0
 804bc7f:	01 d8                	add    eax,ebx
 804bc81:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804bc86:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804bc8c:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804bc92:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804bc98:	61                   	popa   
 804bc99:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804bc9f:	5e                   	pop    esi
 804bca0:	68 ec bd 04 08       	push   0x804bdec
 804bca5:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804bcac:	00 00 00 
 804bcaf:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804bcb6:	00 00 00 
 804bcb9:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804bcc0:	00 00 00 
 804bcc3:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804bcca:	00 00 00 
 804bccd:	6a 01                	push   0x1
 804bccf:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804bcd5:	6a 00                	push   0x0
 804bcd7:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804bcdd:	60                   	pusha  
 804bcde:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804bce3:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804bce9:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804bcef:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804bcf5:	be 00 00 00 00       	mov    esi,0x0
 804bcfa:	bf 00 00 00 00       	mov    edi,0x0
 804bcff:	bd 00 00 00 00       	mov    ebp,0x0
 804bd04:	39 d8                	cmp    eax,ebx
 804bd06:	7c 1d                	jl     804bd25 <..@1911._jmp>
 804bd08:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804bd0d:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804bd13:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804bd19:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804bd1f:	61                   	popa   
 804bd20:	83 c4 04             	add    esp,0x4
 804bd23:	eb 1f                	jmp    804bd44 <..@1911._end>

0804bd25 <..@1911._jmp>:
 804bd25:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804bd2a:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804bd30:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804bd36:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804bd3c:	61                   	popa   
 804bd3d:	83 c4 04             	add    esp,0x4
 804bd40:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804bd44 <..@1911._end>:
 804bd44:	68 3c bf 04 08       	push   0x804bf3c
 804bd49:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804bd50:	00 00 00 
 804bd53:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804bd5a:	00 00 00 
 804bd5d:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804bd64:	00 00 00 
 804bd67:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804bd6e:	00 00 00 
 804bd71:	56                   	push   esi
 804bd72:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804bd78:	6a 02                	push   0x2
 804bd7a:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804bd80:	60                   	pusha  
 804bd81:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804bd86:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804bd8c:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804bd92:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804bd98:	be 00 00 00 00       	mov    esi,0x0
 804bd9d:	bf 00 00 00 00       	mov    edi,0x0
 804bda2:	bd 00 00 00 00       	mov    ebp,0x0
 804bda7:	39 d8                	cmp    eax,ebx
 804bda9:	73 1d                	jae    804bdc8 <..@1928._jmp>
 804bdab:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804bdb0:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804bdb6:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804bdbc:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804bdc2:	61                   	popa   
 804bdc3:	83 c4 04             	add    esp,0x4
 804bdc6:	eb 1f                	jmp    804bde7 <..@1928._end>

0804bdc8 <..@1928._jmp>:
 804bdc8:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804bdcd:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804bdd3:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804bdd9:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804bddf:	61                   	popa   
 804bde0:	83 c4 04             	add    esp,0x4
 804bde3:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804bde7 <..@1928._end>:
 804bde7:	e9 a3 00 00 00       	jmp    804be8f <..@1873._end>

0804bdec <..@1873._less>:
 804bdec:	68 3c bf 04 08       	push   0x804bf3c
 804bdf1:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804bdf8:	00 00 00 
 804bdfb:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804be02:	00 00 00 
 804be05:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804be0c:	00 00 00 
 804be0f:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804be16:	00 00 00 
 804be19:	56                   	push   esi
 804be1a:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804be20:	6a 02                	push   0x2
 804be22:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804be28:	60                   	pusha  
 804be29:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804be2e:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804be34:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804be3a:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804be40:	be 00 00 00 00       	mov    esi,0x0
 804be45:	bf 00 00 00 00       	mov    edi,0x0
 804be4a:	bd 00 00 00 00       	mov    ebp,0x0
 804be4f:	39 d8                	cmp    eax,ebx
 804be51:	76 1d                	jbe    804be70 <..@1945._jmp>
 804be53:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804be58:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804be5e:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804be64:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804be6a:	61                   	popa   
 804be6b:	83 c4 04             	add    esp,0x4
 804be6e:	eb 1f                	jmp    804be8f <..@1873._end>

0804be70 <..@1945._jmp>:
 804be70:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804be75:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804be7b:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804be81:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804be87:	61                   	popa   
 804be88:	83 c4 04             	add    esp,0x4
 804be8b:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804be8f <..@1873._end>:
 804be8f:	89 d7                	mov    edi,edx
 804be91:	83 c7 0c             	add    edi,0xc
 804be94:	89 cd                	mov    ebp,ecx
 804be96:	29 fd                	sub    ebp,edi
 804be98:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804be9f:	00 00 00 
 804bea2:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804bea9:	00 00 00 
 804beac:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804beb3:	00 00 00 
 804beb6:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804bebd:	00 00 00 
 804bec0:	52                   	push   edx
 804bec1:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804bec7:	57                   	push   edi
 804bec8:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804bece:	55                   	push   ebp
 804becf:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 804bed5:	60                   	pusha  
 804bed6:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804bedb:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804bee1:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804bee7:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804beed:	be 00 00 00 00       	mov    esi,0x0
 804bef2:	bf 00 00 00 00       	mov    edi,0x0
 804bef7:	bd 00 00 00 00       	mov    ebp,0x0
 804befc:	39 d8                	cmp    eax,ebx
 804befe:	72 0e                	jb     804bf0e <..@1961.left>
 804bf00:	01 c8                	add    eax,ecx
 804bf02:	01 cb                	add    ebx,ecx

0804bf04 <..@1961.right>:
 804bf04:	48                   	dec    eax
 804bf05:	4b                   	dec    ebx
 804bf06:	8b 13                	mov    edx,DWORD PTR [ebx]
 804bf08:	89 10                	mov    DWORD PTR [eax],edx
 804bf0a:	e2 f8                	loop   804bf04 <..@1961.right>
 804bf0c:	eb 08                	jmp    804bf16 <..@1961.end>

0804bf0e <..@1961.left>:
 804bf0e:	8b 13                	mov    edx,DWORD PTR [ebx]
 804bf10:	89 10                	mov    DWORD PTR [eax],edx
 804bf12:	40                   	inc    eax
 804bf13:	43                   	inc    ebx
 804bf14:	e2 f8                	loop   804bf0e <..@1961.left>

0804bf16 <..@1961.end>:
 804bf16:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804bf1b:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804bf21:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804bf27:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804bf2d:	61                   	popa   
 804bf2e:	83 e9 0c             	sub    ecx,0xc
 804bf31:	83 eb 0c             	sub    ebx,0xc
 804bf34:	83 ea 0c             	sub    edx,0xc
 804bf37:	e9 e5 fc ff ff       	jmp    804bc21 <..@1874.__jup>

0804bf3c <..@1874.__jdown>:
 804bf3c:	eb 00                	jmp    804bf3e <_________macro_ops_end4>

0804bf3e <_________macro_ops_end4>:
 804bf3e:	83 c2 0c             	add    edx,0xc
 804bf41:	e9 2a f8 ff ff       	jmp    804b770 <_________macro_ops_for_begin4>

0804bf46 <_________macro_ops_for_end4>:
 804bf46:	89 c2                	mov    edx,eax

0804bf48 <_________macro_ops_for_begin5>:
 804bf48:	39 da                	cmp    edx,ebx
 804bf4a:	0f 83 ce 07 00 00    	jae    804c71e <_________macro_ops_for_end5>
 804bf50:	68 5f bf 04 08       	push   0x804bf5f
 804bf55:	68 a8 01 00 00       	push   0x1a8
 804bf5a:	e9 21 c1 ff ff       	jmp    8048080 <macro_pr_jmp>

0804bf5f <..@1978._1>:
 804bf5f:	83 3a 02             	cmp    DWORD PTR [edx],0x2
 804bf62:	0f 85 ae 07 00 00    	jne    804c716 <_________macro_ops_end5>
 804bf68:	8b 6a 04             	mov    ebp,DWORD PTR [edx+0x4]
 804bf6b:	81 fd 6f 72 00 00    	cmp    ebp,0x726f
 804bf71:	0f 85 cb 03 00 00    	jne    804c342 <_________macro_ops_not5_1>
 804bf77:	8b 72 f8             	mov    esi,DWORD PTR [edx-0x8]
 804bf7a:	83 fe 00             	cmp    esi,0x0
 804bf7d:	74 09                	je     804bf88 <_________macro_ops_cmp_begin9>
 804bf7f:	c7 42 10 01 00 00 00 	mov    DWORD PTR [edx+0x10],0x1
 804bf86:	eb 18                	jmp    804bfa0 <_________macro_ops_cmp_end10>

0804bf88 <_________macro_ops_cmp_begin9>:
 804bf88:	8b 72 10             	mov    esi,DWORD PTR [edx+0x10]
 804bf8b:	83 fe 00             	cmp    esi,0x0
 804bf8e:	74 09                	je     804bf99 <_________macro_ops_cmp_begin10>
 804bf90:	c7 42 10 01 00 00 00 	mov    DWORD PTR [edx+0x10],0x1
 804bf97:	eb 07                	jmp    804bfa0 <_________macro_ops_cmp_end10>

0804bf99 <_________macro_ops_cmp_begin10>:
 804bf99:	c7 42 10 00 00 00 00 	mov    DWORD PTR [edx+0x10],0x0

0804bfa0 <_________macro_ops_cmp_end10>:
 804bfa0:	6a 00                	push   0x0
 804bfa2:	5e                   	pop    esi
 804bfa3:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804bfaa:	00 00 00 
 804bfad:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804bfb4:	00 00 00 
 804bfb7:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804bfbe:	00 00 00 
 804bfc1:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804bfc8:	00 00 00 
 804bfcb:	56                   	push   esi
 804bfcc:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804bfd2:	6a 01                	push   0x1
 804bfd4:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804bfda:	60                   	pusha  
 804bfdb:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804bfe0:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804bfe6:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804bfec:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804bff2:	be 00 00 00 00       	mov    esi,0x0
 804bff7:	bf 00 00 00 00       	mov    edi,0x0
 804bffc:	bd 00 00 00 00       	mov    ebp,0x0
 804c001:	29 d8                	sub    eax,ebx
 804c003:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804c008:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804c00e:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804c014:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804c01a:	61                   	popa   
 804c01b:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804c021:	5e                   	pop    esi

0804c022 <..@1984.__jup>:
 804c022:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804c029:	00 00 00 
 804c02c:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804c033:	00 00 00 
 804c036:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804c03d:	00 00 00 
 804c040:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804c047:	00 00 00 
 804c04a:	56                   	push   esi
 804c04b:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804c051:	6a 01                	push   0x1
 804c053:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804c059:	60                   	pusha  
 804c05a:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804c05f:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804c065:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804c06b:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804c071:	be 00 00 00 00       	mov    esi,0x0
 804c076:	bf 00 00 00 00       	mov    edi,0x0
 804c07b:	bd 00 00 00 00       	mov    ebp,0x0
 804c080:	01 d8                	add    eax,ebx
 804c082:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804c087:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804c08d:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804c093:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804c099:	61                   	popa   
 804c09a:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804c0a0:	5e                   	pop    esi
 804c0a1:	68 ed c1 04 08       	push   0x804c1ed
 804c0a6:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804c0ad:	00 00 00 
 804c0b0:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804c0b7:	00 00 00 
 804c0ba:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804c0c1:	00 00 00 
 804c0c4:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804c0cb:	00 00 00 
 804c0ce:	6a 01                	push   0x1
 804c0d0:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804c0d6:	6a 00                	push   0x0
 804c0d8:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804c0de:	60                   	pusha  
 804c0df:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804c0e4:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804c0ea:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804c0f0:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804c0f6:	be 00 00 00 00       	mov    esi,0x0
 804c0fb:	bf 00 00 00 00       	mov    edi,0x0
 804c100:	bd 00 00 00 00       	mov    ebp,0x0
 804c105:	39 d8                	cmp    eax,ebx
 804c107:	7c 1d                	jl     804c126 <..@2021._jmp>
 804c109:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804c10e:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804c114:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804c11a:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804c120:	61                   	popa   
 804c121:	83 c4 04             	add    esp,0x4
 804c124:	eb 1f                	jmp    804c145 <..@2021._end>

0804c126 <..@2021._jmp>:
 804c126:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804c12b:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804c131:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804c137:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804c13d:	61                   	popa   
 804c13e:	83 c4 04             	add    esp,0x4
 804c141:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804c145 <..@2021._end>:
 804c145:	68 3d c3 04 08       	push   0x804c33d
 804c14a:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804c151:	00 00 00 
 804c154:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804c15b:	00 00 00 
 804c15e:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804c165:	00 00 00 
 804c168:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804c16f:	00 00 00 
 804c172:	56                   	push   esi
 804c173:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804c179:	6a 02                	push   0x2
 804c17b:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804c181:	60                   	pusha  
 804c182:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804c187:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804c18d:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804c193:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804c199:	be 00 00 00 00       	mov    esi,0x0
 804c19e:	bf 00 00 00 00       	mov    edi,0x0
 804c1a3:	bd 00 00 00 00       	mov    ebp,0x0
 804c1a8:	39 d8                	cmp    eax,ebx
 804c1aa:	73 1d                	jae    804c1c9 <..@2038._jmp>
 804c1ac:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804c1b1:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804c1b7:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804c1bd:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804c1c3:	61                   	popa   
 804c1c4:	83 c4 04             	add    esp,0x4
 804c1c7:	eb 1f                	jmp    804c1e8 <..@2038._end>

0804c1c9 <..@2038._jmp>:
 804c1c9:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804c1ce:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804c1d4:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804c1da:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804c1e0:	61                   	popa   
 804c1e1:	83 c4 04             	add    esp,0x4
 804c1e4:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804c1e8 <..@2038._end>:
 804c1e8:	e9 a3 00 00 00       	jmp    804c290 <..@1983._end>

0804c1ed <..@1983._less>:
 804c1ed:	68 3d c3 04 08       	push   0x804c33d
 804c1f2:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804c1f9:	00 00 00 
 804c1fc:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804c203:	00 00 00 
 804c206:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804c20d:	00 00 00 
 804c210:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804c217:	00 00 00 
 804c21a:	56                   	push   esi
 804c21b:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804c221:	6a 02                	push   0x2
 804c223:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804c229:	60                   	pusha  
 804c22a:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804c22f:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804c235:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804c23b:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804c241:	be 00 00 00 00       	mov    esi,0x0
 804c246:	bf 00 00 00 00       	mov    edi,0x0
 804c24b:	bd 00 00 00 00       	mov    ebp,0x0
 804c250:	39 d8                	cmp    eax,ebx
 804c252:	76 1d                	jbe    804c271 <..@2055._jmp>
 804c254:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804c259:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804c25f:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804c265:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804c26b:	61                   	popa   
 804c26c:	83 c4 04             	add    esp,0x4
 804c26f:	eb 1f                	jmp    804c290 <..@1983._end>

0804c271 <..@2055._jmp>:
 804c271:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804c276:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804c27c:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804c282:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804c288:	61                   	popa   
 804c289:	83 c4 04             	add    esp,0x4
 804c28c:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804c290 <..@1983._end>:
 804c290:	89 d7                	mov    edi,edx
 804c292:	83 c7 0c             	add    edi,0xc
 804c295:	89 cd                	mov    ebp,ecx
 804c297:	29 fd                	sub    ebp,edi
 804c299:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804c2a0:	00 00 00 
 804c2a3:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804c2aa:	00 00 00 
 804c2ad:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804c2b4:	00 00 00 
 804c2b7:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804c2be:	00 00 00 
 804c2c1:	52                   	push   edx
 804c2c2:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804c2c8:	57                   	push   edi
 804c2c9:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804c2cf:	55                   	push   ebp
 804c2d0:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 804c2d6:	60                   	pusha  
 804c2d7:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804c2dc:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804c2e2:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804c2e8:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804c2ee:	be 00 00 00 00       	mov    esi,0x0
 804c2f3:	bf 00 00 00 00       	mov    edi,0x0
 804c2f8:	bd 00 00 00 00       	mov    ebp,0x0
 804c2fd:	39 d8                	cmp    eax,ebx
 804c2ff:	72 0e                	jb     804c30f <..@2071.left>
 804c301:	01 c8                	add    eax,ecx
 804c303:	01 cb                	add    ebx,ecx

0804c305 <..@2071.right>:
 804c305:	48                   	dec    eax
 804c306:	4b                   	dec    ebx
 804c307:	8b 13                	mov    edx,DWORD PTR [ebx]
 804c309:	89 10                	mov    DWORD PTR [eax],edx
 804c30b:	e2 f8                	loop   804c305 <..@2071.right>
 804c30d:	eb 08                	jmp    804c317 <..@2071.end>

0804c30f <..@2071.left>:
 804c30f:	8b 13                	mov    edx,DWORD PTR [ebx]
 804c311:	89 10                	mov    DWORD PTR [eax],edx
 804c313:	40                   	inc    eax
 804c314:	43                   	inc    ebx
 804c315:	e2 f8                	loop   804c30f <..@2071.left>

0804c317 <..@2071.end>:
 804c317:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804c31c:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804c322:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804c328:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804c32e:	61                   	popa   
 804c32f:	83 e9 0c             	sub    ecx,0xc
 804c332:	83 eb 0c             	sub    ebx,0xc
 804c335:	83 ea 0c             	sub    edx,0xc
 804c338:	e9 e5 fc ff ff       	jmp    804c022 <..@1984.__jup>

0804c33d <..@1984.__jdown>:
 804c33d:	e9 d4 03 00 00       	jmp    804c716 <_________macro_ops_end5>

0804c342 <_________macro_ops_not5_1>:
 804c342:	81 fd 7c 7c 00 00    	cmp    ebp,0x7c7c
 804c348:	0f 85 c8 03 00 00    	jne    804c716 <_________macro_ops_end5>
 804c34e:	8b 72 f8             	mov    esi,DWORD PTR [edx-0x8]
 804c351:	83 fe 00             	cmp    esi,0x0
 804c354:	74 09                	je     804c35f <_________macro_ops_cmp_begin13>
 804c356:	c7 42 10 01 00 00 00 	mov    DWORD PTR [edx+0x10],0x1
 804c35d:	eb 18                	jmp    804c377 <_________macro_ops_cmp_end13>

0804c35f <_________macro_ops_cmp_begin13>:
 804c35f:	8b 72 10             	mov    esi,DWORD PTR [edx+0x10]
 804c362:	83 fe 00             	cmp    esi,0x0
 804c365:	74 09                	je     804c370 <_________macro_ops_cmp_begin14>
 804c367:	c7 42 10 01 00 00 00 	mov    DWORD PTR [edx+0x10],0x1
 804c36e:	eb 07                	jmp    804c377 <_________macro_ops_cmp_end13>

0804c370 <_________macro_ops_cmp_begin14>:
 804c370:	c7 42 10 00 00 00 00 	mov    DWORD PTR [edx+0x10],0x0

0804c377 <_________macro_ops_cmp_end13>:
 804c377:	6a 00                	push   0x0
 804c379:	5e                   	pop    esi
 804c37a:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804c381:	00 00 00 
 804c384:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804c38b:	00 00 00 
 804c38e:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804c395:	00 00 00 
 804c398:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804c39f:	00 00 00 
 804c3a2:	56                   	push   esi
 804c3a3:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804c3a9:	6a 01                	push   0x1
 804c3ab:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804c3b1:	60                   	pusha  
 804c3b2:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804c3b7:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804c3bd:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804c3c3:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804c3c9:	be 00 00 00 00       	mov    esi,0x0
 804c3ce:	bf 00 00 00 00       	mov    edi,0x0
 804c3d3:	bd 00 00 00 00       	mov    ebp,0x0
 804c3d8:	29 d8                	sub    eax,ebx
 804c3da:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804c3df:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804c3e5:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804c3eb:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804c3f1:	61                   	popa   
 804c3f2:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804c3f8:	5e                   	pop    esi

0804c3f9 <..@2091.__jup>:
 804c3f9:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804c400:	00 00 00 
 804c403:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804c40a:	00 00 00 
 804c40d:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804c414:	00 00 00 
 804c417:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804c41e:	00 00 00 
 804c421:	56                   	push   esi
 804c422:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804c428:	6a 01                	push   0x1
 804c42a:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804c430:	60                   	pusha  
 804c431:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804c436:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804c43c:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804c442:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804c448:	be 00 00 00 00       	mov    esi,0x0
 804c44d:	bf 00 00 00 00       	mov    edi,0x0
 804c452:	bd 00 00 00 00       	mov    ebp,0x0
 804c457:	01 d8                	add    eax,ebx
 804c459:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804c45e:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804c464:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804c46a:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804c470:	61                   	popa   
 804c471:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804c477:	5e                   	pop    esi
 804c478:	68 c4 c5 04 08       	push   0x804c5c4
 804c47d:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804c484:	00 00 00 
 804c487:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804c48e:	00 00 00 
 804c491:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804c498:	00 00 00 
 804c49b:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804c4a2:	00 00 00 
 804c4a5:	6a 01                	push   0x1
 804c4a7:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804c4ad:	6a 00                	push   0x0
 804c4af:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804c4b5:	60                   	pusha  
 804c4b6:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804c4bb:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804c4c1:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804c4c7:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804c4cd:	be 00 00 00 00       	mov    esi,0x0
 804c4d2:	bf 00 00 00 00       	mov    edi,0x0
 804c4d7:	bd 00 00 00 00       	mov    ebp,0x0
 804c4dc:	39 d8                	cmp    eax,ebx
 804c4de:	7c 1d                	jl     804c4fd <..@2128._jmp>
 804c4e0:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804c4e5:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804c4eb:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804c4f1:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804c4f7:	61                   	popa   
 804c4f8:	83 c4 04             	add    esp,0x4
 804c4fb:	eb 1f                	jmp    804c51c <..@2128._end>

0804c4fd <..@2128._jmp>:
 804c4fd:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804c502:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804c508:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804c50e:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804c514:	61                   	popa   
 804c515:	83 c4 04             	add    esp,0x4
 804c518:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804c51c <..@2128._end>:
 804c51c:	68 14 c7 04 08       	push   0x804c714
 804c521:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804c528:	00 00 00 
 804c52b:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804c532:	00 00 00 
 804c535:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804c53c:	00 00 00 
 804c53f:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804c546:	00 00 00 
 804c549:	56                   	push   esi
 804c54a:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804c550:	6a 02                	push   0x2
 804c552:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804c558:	60                   	pusha  
 804c559:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804c55e:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804c564:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804c56a:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804c570:	be 00 00 00 00       	mov    esi,0x0
 804c575:	bf 00 00 00 00       	mov    edi,0x0
 804c57a:	bd 00 00 00 00       	mov    ebp,0x0
 804c57f:	39 d8                	cmp    eax,ebx
 804c581:	73 1d                	jae    804c5a0 <..@2145._jmp>
 804c583:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804c588:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804c58e:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804c594:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804c59a:	61                   	popa   
 804c59b:	83 c4 04             	add    esp,0x4
 804c59e:	eb 1f                	jmp    804c5bf <..@2145._end>

0804c5a0 <..@2145._jmp>:
 804c5a0:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804c5a5:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804c5ab:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804c5b1:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804c5b7:	61                   	popa   
 804c5b8:	83 c4 04             	add    esp,0x4
 804c5bb:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804c5bf <..@2145._end>:
 804c5bf:	e9 a3 00 00 00       	jmp    804c667 <..@2090._end>

0804c5c4 <..@2090._less>:
 804c5c4:	68 14 c7 04 08       	push   0x804c714
 804c5c9:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804c5d0:	00 00 00 
 804c5d3:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804c5da:	00 00 00 
 804c5dd:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804c5e4:	00 00 00 
 804c5e7:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804c5ee:	00 00 00 
 804c5f1:	56                   	push   esi
 804c5f2:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804c5f8:	6a 02                	push   0x2
 804c5fa:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804c600:	60                   	pusha  
 804c601:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804c606:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804c60c:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804c612:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804c618:	be 00 00 00 00       	mov    esi,0x0
 804c61d:	bf 00 00 00 00       	mov    edi,0x0
 804c622:	bd 00 00 00 00       	mov    ebp,0x0
 804c627:	39 d8                	cmp    eax,ebx
 804c629:	76 1d                	jbe    804c648 <..@2162._jmp>
 804c62b:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804c630:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804c636:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804c63c:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804c642:	61                   	popa   
 804c643:	83 c4 04             	add    esp,0x4
 804c646:	eb 1f                	jmp    804c667 <..@2090._end>

0804c648 <..@2162._jmp>:
 804c648:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804c64d:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804c653:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804c659:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804c65f:	61                   	popa   
 804c660:	83 c4 04             	add    esp,0x4
 804c663:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804c667 <..@2090._end>:
 804c667:	89 d7                	mov    edi,edx
 804c669:	83 c7 0c             	add    edi,0xc
 804c66c:	89 cd                	mov    ebp,ecx
 804c66e:	29 fd                	sub    ebp,edi
 804c670:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804c677:	00 00 00 
 804c67a:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804c681:	00 00 00 
 804c684:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804c68b:	00 00 00 
 804c68e:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804c695:	00 00 00 
 804c698:	52                   	push   edx
 804c699:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804c69f:	57                   	push   edi
 804c6a0:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804c6a6:	55                   	push   ebp
 804c6a7:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 804c6ad:	60                   	pusha  
 804c6ae:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804c6b3:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804c6b9:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804c6bf:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804c6c5:	be 00 00 00 00       	mov    esi,0x0
 804c6ca:	bf 00 00 00 00       	mov    edi,0x0
 804c6cf:	bd 00 00 00 00       	mov    ebp,0x0
 804c6d4:	39 d8                	cmp    eax,ebx
 804c6d6:	72 0e                	jb     804c6e6 <..@2178.left>
 804c6d8:	01 c8                	add    eax,ecx
 804c6da:	01 cb                	add    ebx,ecx

0804c6dc <..@2178.right>:
 804c6dc:	48                   	dec    eax
 804c6dd:	4b                   	dec    ebx
 804c6de:	8b 13                	mov    edx,DWORD PTR [ebx]
 804c6e0:	89 10                	mov    DWORD PTR [eax],edx
 804c6e2:	e2 f8                	loop   804c6dc <..@2178.right>
 804c6e4:	eb 08                	jmp    804c6ee <..@2178.end>

0804c6e6 <..@2178.left>:
 804c6e6:	8b 13                	mov    edx,DWORD PTR [ebx]
 804c6e8:	89 10                	mov    DWORD PTR [eax],edx
 804c6ea:	40                   	inc    eax
 804c6eb:	43                   	inc    ebx
 804c6ec:	e2 f8                	loop   804c6e6 <..@2178.left>

0804c6ee <..@2178.end>:
 804c6ee:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804c6f3:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804c6f9:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804c6ff:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804c705:	61                   	popa   
 804c706:	83 e9 0c             	sub    ecx,0xc
 804c709:	83 eb 0c             	sub    ebx,0xc
 804c70c:	83 ea 0c             	sub    edx,0xc
 804c70f:	e9 e5 fc ff ff       	jmp    804c3f9 <..@2091.__jup>

0804c714 <..@2091.__jdown>:
 804c714:	eb 00                	jmp    804c716 <_________macro_ops_end5>

0804c716 <_________macro_ops_end5>:
 804c716:	83 c2 0c             	add    edx,0xc
 804c719:	e9 2a f8 ff ff       	jmp    804bf48 <_________macro_ops_for_begin5>

0804c71e <_________macro_ops_for_end5>:
 804c71e:	89 da                	mov    edx,ebx

0804c720 <_________macro_ops_for_begin7>:
 804c720:	39 c2                	cmp    edx,eax
 804c722:	0f 86 61 17 00 00    	jbe    804de89 <_________macro_ops_for_end7>
 804c728:	83 ea 0c             	sub    edx,0xc
 804c72b:	68 3a c7 04 08       	push   0x804c73a
 804c730:	68 e0 01 00 00       	push   0x1e0
 804c735:	e9 46 b9 ff ff       	jmp    8048080 <macro_pr_jmp>

0804c73a <..@2195._1>:
 804c73a:	83 3a 02             	cmp    DWORD PTR [edx],0x2
 804c73d:	0f 85 41 17 00 00    	jne    804de84 <_________macro_ops_end7>
 804c743:	8b 6a 04             	mov    ebp,DWORD PTR [edx+0x4]
 804c746:	83 fd 3d             	cmp    ebp,0x3d
 804c749:	0f 85 cc 03 00 00    	jne    804cb1b <_________macro_ops_not7_1>
 804c74f:	60                   	pusha  
 804c750:	8b 42 10             	mov    eax,DWORD PTR [edx+0x10]
 804c753:	8b 5a f4             	mov    ebx,DWORD PTR [edx-0xc]
 804c756:	89 5a 0c             	mov    DWORD PTR [edx+0xc],ebx
 804c759:	8b 72 fc             	mov    esi,DWORD PTR [edx-0x4]
 804c75c:	89 72 14             	mov    DWORD PTR [edx+0x14],esi
 804c75f:	83 fe 04             	cmp    esi,0x4
 804c762:	75 02                	jne    804c766 <_________macro_ops_assign7_1_n4>
 804c764:	89 03                	mov    DWORD PTR [ebx],eax

0804c766 <_________macro_ops_assign7_1_n4>:
 804c766:	83 fe 02             	cmp    esi,0x2
 804c769:	75 03                	jne    804c76e <_________macro_ops_assign7_1_n2>
 804c76b:	66 89 03             	mov    WORD PTR [ebx],ax

0804c76e <_________macro_ops_assign7_1_n2>:
 804c76e:	83 fe 01             	cmp    esi,0x1
 804c771:	75 02                	jne    804c775 <_________macro_ops_assign7_1_n1>
 804c773:	88 03                	mov    BYTE PTR [ebx],al

0804c775 <_________macro_ops_assign7_1_n1>:
 804c775:	61                   	popa   
 804c776:	6a 00                	push   0x0
 804c778:	5e                   	pop    esi
 804c779:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804c780:	00 00 00 
 804c783:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804c78a:	00 00 00 
 804c78d:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804c794:	00 00 00 
 804c797:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804c79e:	00 00 00 
 804c7a1:	56                   	push   esi
 804c7a2:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804c7a8:	6a 01                	push   0x1
 804c7aa:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804c7b0:	60                   	pusha  
 804c7b1:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804c7b6:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804c7bc:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804c7c2:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804c7c8:	be 00 00 00 00       	mov    esi,0x0
 804c7cd:	bf 00 00 00 00       	mov    edi,0x0
 804c7d2:	bd 00 00 00 00       	mov    ebp,0x0
 804c7d7:	29 d8                	sub    eax,ebx
 804c7d9:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804c7de:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804c7e4:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804c7ea:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804c7f0:	61                   	popa   
 804c7f1:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804c7f7:	5e                   	pop    esi

0804c7f8 <..@2201.__jup>:
 804c7f8:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804c7ff:	00 00 00 
 804c802:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804c809:	00 00 00 
 804c80c:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804c813:	00 00 00 
 804c816:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804c81d:	00 00 00 
 804c820:	56                   	push   esi
 804c821:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804c827:	6a 01                	push   0x1
 804c829:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804c82f:	60                   	pusha  
 804c830:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804c835:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804c83b:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804c841:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804c847:	be 00 00 00 00       	mov    esi,0x0
 804c84c:	bf 00 00 00 00       	mov    edi,0x0
 804c851:	bd 00 00 00 00       	mov    ebp,0x0
 804c856:	01 d8                	add    eax,ebx
 804c858:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804c85d:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804c863:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804c869:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804c86f:	61                   	popa   
 804c870:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804c876:	5e                   	pop    esi
 804c877:	68 c3 c9 04 08       	push   0x804c9c3
 804c87c:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804c883:	00 00 00 
 804c886:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804c88d:	00 00 00 
 804c890:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804c897:	00 00 00 
 804c89a:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804c8a1:	00 00 00 
 804c8a4:	6a 01                	push   0x1
 804c8a6:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804c8ac:	6a 00                	push   0x0
 804c8ae:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804c8b4:	60                   	pusha  
 804c8b5:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804c8ba:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804c8c0:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804c8c6:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804c8cc:	be 00 00 00 00       	mov    esi,0x0
 804c8d1:	bf 00 00 00 00       	mov    edi,0x0
 804c8d6:	bd 00 00 00 00       	mov    ebp,0x0
 804c8db:	39 d8                	cmp    eax,ebx
 804c8dd:	7c 1d                	jl     804c8fc <..@2238._jmp>
 804c8df:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804c8e4:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804c8ea:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804c8f0:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804c8f6:	61                   	popa   
 804c8f7:	83 c4 04             	add    esp,0x4
 804c8fa:	eb 1f                	jmp    804c91b <..@2238._end>

0804c8fc <..@2238._jmp>:
 804c8fc:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804c901:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804c907:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804c90d:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804c913:	61                   	popa   
 804c914:	83 c4 04             	add    esp,0x4
 804c917:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804c91b <..@2238._end>:
 804c91b:	68 13 cb 04 08       	push   0x804cb13
 804c920:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804c927:	00 00 00 
 804c92a:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804c931:	00 00 00 
 804c934:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804c93b:	00 00 00 
 804c93e:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804c945:	00 00 00 
 804c948:	56                   	push   esi
 804c949:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804c94f:	6a 02                	push   0x2
 804c951:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804c957:	60                   	pusha  
 804c958:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804c95d:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804c963:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804c969:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804c96f:	be 00 00 00 00       	mov    esi,0x0
 804c974:	bf 00 00 00 00       	mov    edi,0x0
 804c979:	bd 00 00 00 00       	mov    ebp,0x0
 804c97e:	39 d8                	cmp    eax,ebx
 804c980:	73 1d                	jae    804c99f <..@2255._jmp>
 804c982:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804c987:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804c98d:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804c993:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804c999:	61                   	popa   
 804c99a:	83 c4 04             	add    esp,0x4
 804c99d:	eb 1f                	jmp    804c9be <..@2255._end>

0804c99f <..@2255._jmp>:
 804c99f:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804c9a4:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804c9aa:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804c9b0:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804c9b6:	61                   	popa   
 804c9b7:	83 c4 04             	add    esp,0x4
 804c9ba:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804c9be <..@2255._end>:
 804c9be:	e9 a3 00 00 00       	jmp    804ca66 <..@2200._end>

0804c9c3 <..@2200._less>:
 804c9c3:	68 13 cb 04 08       	push   0x804cb13
 804c9c8:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804c9cf:	00 00 00 
 804c9d2:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804c9d9:	00 00 00 
 804c9dc:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804c9e3:	00 00 00 
 804c9e6:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804c9ed:	00 00 00 
 804c9f0:	56                   	push   esi
 804c9f1:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804c9f7:	6a 02                	push   0x2
 804c9f9:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804c9ff:	60                   	pusha  
 804ca00:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804ca05:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804ca0b:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804ca11:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804ca17:	be 00 00 00 00       	mov    esi,0x0
 804ca1c:	bf 00 00 00 00       	mov    edi,0x0
 804ca21:	bd 00 00 00 00       	mov    ebp,0x0
 804ca26:	39 d8                	cmp    eax,ebx
 804ca28:	76 1d                	jbe    804ca47 <..@2272._jmp>
 804ca2a:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804ca2f:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804ca35:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804ca3b:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804ca41:	61                   	popa   
 804ca42:	83 c4 04             	add    esp,0x4
 804ca45:	eb 1f                	jmp    804ca66 <..@2200._end>

0804ca47 <..@2272._jmp>:
 804ca47:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804ca4c:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804ca52:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804ca58:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804ca5e:	61                   	popa   
 804ca5f:	83 c4 04             	add    esp,0x4
 804ca62:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804ca66 <..@2200._end>:
 804ca66:	89 d7                	mov    edi,edx
 804ca68:	83 c7 0c             	add    edi,0xc
 804ca6b:	89 cd                	mov    ebp,ecx
 804ca6d:	29 fd                	sub    ebp,edi
 804ca6f:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804ca76:	00 00 00 
 804ca79:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804ca80:	00 00 00 
 804ca83:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804ca8a:	00 00 00 
 804ca8d:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804ca94:	00 00 00 
 804ca97:	52                   	push   edx
 804ca98:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804ca9e:	57                   	push   edi
 804ca9f:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804caa5:	55                   	push   ebp
 804caa6:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 804caac:	60                   	pusha  
 804caad:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804cab2:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804cab8:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804cabe:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804cac4:	be 00 00 00 00       	mov    esi,0x0
 804cac9:	bf 00 00 00 00       	mov    edi,0x0
 804cace:	bd 00 00 00 00       	mov    ebp,0x0
 804cad3:	39 d8                	cmp    eax,ebx
 804cad5:	72 0e                	jb     804cae5 <..@2288.left>
 804cad7:	01 c8                	add    eax,ecx
 804cad9:	01 cb                	add    ebx,ecx

0804cadb <..@2288.right>:
 804cadb:	48                   	dec    eax
 804cadc:	4b                   	dec    ebx
 804cadd:	8b 13                	mov    edx,DWORD PTR [ebx]
 804cadf:	89 10                	mov    DWORD PTR [eax],edx
 804cae1:	e2 f8                	loop   804cadb <..@2288.right>
 804cae3:	eb 08                	jmp    804caed <..@2288.end>

0804cae5 <..@2288.left>:
 804cae5:	8b 13                	mov    edx,DWORD PTR [ebx]
 804cae7:	89 10                	mov    DWORD PTR [eax],edx
 804cae9:	40                   	inc    eax
 804caea:	43                   	inc    ebx
 804caeb:	e2 f8                	loop   804cae5 <..@2288.left>

0804caed <..@2288.end>:
 804caed:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804caf2:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804caf8:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804cafe:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804cb04:	61                   	popa   
 804cb05:	83 e9 0c             	sub    ecx,0xc
 804cb08:	83 eb 0c             	sub    ebx,0xc
 804cb0b:	83 ea 0c             	sub    edx,0xc
 804cb0e:	e9 e5 fc ff ff       	jmp    804c7f8 <..@2201.__jup>

0804cb13 <..@2201.__jdown>:
 804cb13:	83 c2 18             	add    edx,0x18
 804cb16:	e9 69 13 00 00       	jmp    804de84 <_________macro_ops_end7>

0804cb1b <_________macro_ops_not7_1>:
 804cb1b:	81 fd 2b 3d 00 00    	cmp    ebp,0x3d2b
 804cb21:	0f 85 d2 03 00 00    	jne    804cef9 <_________macro_ops_not7_2>
 804cb27:	60                   	pusha  
 804cb28:	8b 42 f8             	mov    eax,DWORD PTR [edx-0x8]
 804cb2b:	03 42 10             	add    eax,DWORD PTR [edx+0x10]
 804cb2e:	89 42 10             	mov    DWORD PTR [edx+0x10],eax
 804cb31:	8b 5a f4             	mov    ebx,DWORD PTR [edx-0xc]
 804cb34:	89 5a 0c             	mov    DWORD PTR [edx+0xc],ebx
 804cb37:	8b 72 fc             	mov    esi,DWORD PTR [edx-0x4]
 804cb3a:	89 72 14             	mov    DWORD PTR [edx+0x14],esi
 804cb3d:	83 fe 04             	cmp    esi,0x4
 804cb40:	75 02                	jne    804cb44 <_________macro_ops_assign7_2_n4>
 804cb42:	89 03                	mov    DWORD PTR [ebx],eax

0804cb44 <_________macro_ops_assign7_2_n4>:
 804cb44:	83 fe 02             	cmp    esi,0x2
 804cb47:	75 03                	jne    804cb4c <_________macro_ops_assign7_2_n2>
 804cb49:	66 89 03             	mov    WORD PTR [ebx],ax

0804cb4c <_________macro_ops_assign7_2_n2>:
 804cb4c:	83 fe 01             	cmp    esi,0x1
 804cb4f:	75 02                	jne    804cb53 <_________macro_ops_assign7_2_n1>
 804cb51:	88 03                	mov    BYTE PTR [ebx],al

0804cb53 <_________macro_ops_assign7_2_n1>:
 804cb53:	61                   	popa   
 804cb54:	6a 00                	push   0x0
 804cb56:	5e                   	pop    esi
 804cb57:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804cb5e:	00 00 00 
 804cb61:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804cb68:	00 00 00 
 804cb6b:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804cb72:	00 00 00 
 804cb75:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804cb7c:	00 00 00 
 804cb7f:	56                   	push   esi
 804cb80:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804cb86:	6a 01                	push   0x1
 804cb88:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804cb8e:	60                   	pusha  
 804cb8f:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804cb94:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804cb9a:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804cba0:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804cba6:	be 00 00 00 00       	mov    esi,0x0
 804cbab:	bf 00 00 00 00       	mov    edi,0x0
 804cbb0:	bd 00 00 00 00       	mov    ebp,0x0
 804cbb5:	29 d8                	sub    eax,ebx
 804cbb7:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804cbbc:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804cbc2:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804cbc8:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804cbce:	61                   	popa   
 804cbcf:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804cbd5:	5e                   	pop    esi

0804cbd6 <..@2308.__jup>:
 804cbd6:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804cbdd:	00 00 00 
 804cbe0:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804cbe7:	00 00 00 
 804cbea:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804cbf1:	00 00 00 
 804cbf4:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804cbfb:	00 00 00 
 804cbfe:	56                   	push   esi
 804cbff:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804cc05:	6a 01                	push   0x1
 804cc07:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804cc0d:	60                   	pusha  
 804cc0e:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804cc13:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804cc19:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804cc1f:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804cc25:	be 00 00 00 00       	mov    esi,0x0
 804cc2a:	bf 00 00 00 00       	mov    edi,0x0
 804cc2f:	bd 00 00 00 00       	mov    ebp,0x0
 804cc34:	01 d8                	add    eax,ebx
 804cc36:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804cc3b:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804cc41:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804cc47:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804cc4d:	61                   	popa   
 804cc4e:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804cc54:	5e                   	pop    esi
 804cc55:	68 a1 cd 04 08       	push   0x804cda1
 804cc5a:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804cc61:	00 00 00 
 804cc64:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804cc6b:	00 00 00 
 804cc6e:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804cc75:	00 00 00 
 804cc78:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804cc7f:	00 00 00 
 804cc82:	6a 01                	push   0x1
 804cc84:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804cc8a:	6a 00                	push   0x0
 804cc8c:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804cc92:	60                   	pusha  
 804cc93:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804cc98:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804cc9e:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804cca4:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804ccaa:	be 00 00 00 00       	mov    esi,0x0
 804ccaf:	bf 00 00 00 00       	mov    edi,0x0
 804ccb4:	bd 00 00 00 00       	mov    ebp,0x0
 804ccb9:	39 d8                	cmp    eax,ebx
 804ccbb:	7c 1d                	jl     804ccda <..@2345._jmp>
 804ccbd:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804ccc2:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804ccc8:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804ccce:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804ccd4:	61                   	popa   
 804ccd5:	83 c4 04             	add    esp,0x4
 804ccd8:	eb 1f                	jmp    804ccf9 <..@2345._end>

0804ccda <..@2345._jmp>:
 804ccda:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804ccdf:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804cce5:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804cceb:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804ccf1:	61                   	popa   
 804ccf2:	83 c4 04             	add    esp,0x4
 804ccf5:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804ccf9 <..@2345._end>:
 804ccf9:	68 f1 ce 04 08       	push   0x804cef1
 804ccfe:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804cd05:	00 00 00 
 804cd08:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804cd0f:	00 00 00 
 804cd12:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804cd19:	00 00 00 
 804cd1c:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804cd23:	00 00 00 
 804cd26:	56                   	push   esi
 804cd27:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804cd2d:	6a 02                	push   0x2
 804cd2f:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804cd35:	60                   	pusha  
 804cd36:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804cd3b:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804cd41:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804cd47:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804cd4d:	be 00 00 00 00       	mov    esi,0x0
 804cd52:	bf 00 00 00 00       	mov    edi,0x0
 804cd57:	bd 00 00 00 00       	mov    ebp,0x0
 804cd5c:	39 d8                	cmp    eax,ebx
 804cd5e:	73 1d                	jae    804cd7d <..@2362._jmp>
 804cd60:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804cd65:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804cd6b:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804cd71:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804cd77:	61                   	popa   
 804cd78:	83 c4 04             	add    esp,0x4
 804cd7b:	eb 1f                	jmp    804cd9c <..@2362._end>

0804cd7d <..@2362._jmp>:
 804cd7d:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804cd82:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804cd88:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804cd8e:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804cd94:	61                   	popa   
 804cd95:	83 c4 04             	add    esp,0x4
 804cd98:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804cd9c <..@2362._end>:
 804cd9c:	e9 a3 00 00 00       	jmp    804ce44 <..@2307._end>

0804cda1 <..@2307._less>:
 804cda1:	68 f1 ce 04 08       	push   0x804cef1
 804cda6:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804cdad:	00 00 00 
 804cdb0:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804cdb7:	00 00 00 
 804cdba:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804cdc1:	00 00 00 
 804cdc4:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804cdcb:	00 00 00 
 804cdce:	56                   	push   esi
 804cdcf:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804cdd5:	6a 02                	push   0x2
 804cdd7:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804cddd:	60                   	pusha  
 804cdde:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804cde3:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804cde9:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804cdef:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804cdf5:	be 00 00 00 00       	mov    esi,0x0
 804cdfa:	bf 00 00 00 00       	mov    edi,0x0
 804cdff:	bd 00 00 00 00       	mov    ebp,0x0
 804ce04:	39 d8                	cmp    eax,ebx
 804ce06:	76 1d                	jbe    804ce25 <..@2379._jmp>
 804ce08:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804ce0d:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804ce13:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804ce19:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804ce1f:	61                   	popa   
 804ce20:	83 c4 04             	add    esp,0x4
 804ce23:	eb 1f                	jmp    804ce44 <..@2307._end>

0804ce25 <..@2379._jmp>:
 804ce25:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804ce2a:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804ce30:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804ce36:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804ce3c:	61                   	popa   
 804ce3d:	83 c4 04             	add    esp,0x4
 804ce40:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804ce44 <..@2307._end>:
 804ce44:	89 d7                	mov    edi,edx
 804ce46:	83 c7 0c             	add    edi,0xc
 804ce49:	89 cd                	mov    ebp,ecx
 804ce4b:	29 fd                	sub    ebp,edi
 804ce4d:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804ce54:	00 00 00 
 804ce57:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804ce5e:	00 00 00 
 804ce61:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804ce68:	00 00 00 
 804ce6b:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804ce72:	00 00 00 
 804ce75:	52                   	push   edx
 804ce76:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804ce7c:	57                   	push   edi
 804ce7d:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804ce83:	55                   	push   ebp
 804ce84:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 804ce8a:	60                   	pusha  
 804ce8b:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804ce90:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804ce96:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804ce9c:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804cea2:	be 00 00 00 00       	mov    esi,0x0
 804cea7:	bf 00 00 00 00       	mov    edi,0x0
 804ceac:	bd 00 00 00 00       	mov    ebp,0x0
 804ceb1:	39 d8                	cmp    eax,ebx
 804ceb3:	72 0e                	jb     804cec3 <..@2395.left>
 804ceb5:	01 c8                	add    eax,ecx
 804ceb7:	01 cb                	add    ebx,ecx

0804ceb9 <..@2395.right>:
 804ceb9:	48                   	dec    eax
 804ceba:	4b                   	dec    ebx
 804cebb:	8b 13                	mov    edx,DWORD PTR [ebx]
 804cebd:	89 10                	mov    DWORD PTR [eax],edx
 804cebf:	e2 f8                	loop   804ceb9 <..@2395.right>
 804cec1:	eb 08                	jmp    804cecb <..@2395.end>

0804cec3 <..@2395.left>:
 804cec3:	8b 13                	mov    edx,DWORD PTR [ebx]
 804cec5:	89 10                	mov    DWORD PTR [eax],edx
 804cec7:	40                   	inc    eax
 804cec8:	43                   	inc    ebx
 804cec9:	e2 f8                	loop   804cec3 <..@2395.left>

0804cecb <..@2395.end>:
 804cecb:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804ced0:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804ced6:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804cedc:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804cee2:	61                   	popa   
 804cee3:	83 e9 0c             	sub    ecx,0xc
 804cee6:	83 eb 0c             	sub    ebx,0xc
 804cee9:	83 ea 0c             	sub    edx,0xc
 804ceec:	e9 e5 fc ff ff       	jmp    804cbd6 <..@2308.__jup>

0804cef1 <..@2308.__jdown>:
 804cef1:	83 c2 18             	add    edx,0x18
 804cef4:	e9 8b 0f 00 00       	jmp    804de84 <_________macro_ops_end7>

0804cef9 <_________macro_ops_not7_2>:
 804cef9:	81 fd 2d 3d 00 00    	cmp    ebp,0x3d2d
 804ceff:	0f 85 d2 03 00 00    	jne    804d2d7 <_________macro_ops_not7_3>
 804cf05:	60                   	pusha  
 804cf06:	8b 42 f8             	mov    eax,DWORD PTR [edx-0x8]
 804cf09:	2b 42 10             	sub    eax,DWORD PTR [edx+0x10]
 804cf0c:	89 42 10             	mov    DWORD PTR [edx+0x10],eax
 804cf0f:	8b 5a f4             	mov    ebx,DWORD PTR [edx-0xc]
 804cf12:	89 5a 0c             	mov    DWORD PTR [edx+0xc],ebx
 804cf15:	8b 72 fc             	mov    esi,DWORD PTR [edx-0x4]
 804cf18:	89 72 14             	mov    DWORD PTR [edx+0x14],esi
 804cf1b:	83 fe 04             	cmp    esi,0x4
 804cf1e:	75 02                	jne    804cf22 <_________macro_ops_assign7_3_n4>
 804cf20:	89 03                	mov    DWORD PTR [ebx],eax

0804cf22 <_________macro_ops_assign7_3_n4>:
 804cf22:	83 fe 02             	cmp    esi,0x2
 804cf25:	75 03                	jne    804cf2a <_________macro_ops_assign7_3_n2>
 804cf27:	66 89 03             	mov    WORD PTR [ebx],ax

0804cf2a <_________macro_ops_assign7_3_n2>:
 804cf2a:	83 fe 01             	cmp    esi,0x1
 804cf2d:	75 02                	jne    804cf31 <_________macro_ops_assign7_3_n1>
 804cf2f:	88 03                	mov    BYTE PTR [ebx],al

0804cf31 <_________macro_ops_assign7_3_n1>:
 804cf31:	61                   	popa   
 804cf32:	6a 00                	push   0x0
 804cf34:	5e                   	pop    esi
 804cf35:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804cf3c:	00 00 00 
 804cf3f:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804cf46:	00 00 00 
 804cf49:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804cf50:	00 00 00 
 804cf53:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804cf5a:	00 00 00 
 804cf5d:	56                   	push   esi
 804cf5e:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804cf64:	6a 01                	push   0x1
 804cf66:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804cf6c:	60                   	pusha  
 804cf6d:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804cf72:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804cf78:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804cf7e:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804cf84:	be 00 00 00 00       	mov    esi,0x0
 804cf89:	bf 00 00 00 00       	mov    edi,0x0
 804cf8e:	bd 00 00 00 00       	mov    ebp,0x0
 804cf93:	29 d8                	sub    eax,ebx
 804cf95:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804cf9a:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804cfa0:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804cfa6:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804cfac:	61                   	popa   
 804cfad:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804cfb3:	5e                   	pop    esi

0804cfb4 <..@2415.__jup>:
 804cfb4:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804cfbb:	00 00 00 
 804cfbe:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804cfc5:	00 00 00 
 804cfc8:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804cfcf:	00 00 00 
 804cfd2:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804cfd9:	00 00 00 
 804cfdc:	56                   	push   esi
 804cfdd:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804cfe3:	6a 01                	push   0x1
 804cfe5:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804cfeb:	60                   	pusha  
 804cfec:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804cff1:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804cff7:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804cffd:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804d003:	be 00 00 00 00       	mov    esi,0x0
 804d008:	bf 00 00 00 00       	mov    edi,0x0
 804d00d:	bd 00 00 00 00       	mov    ebp,0x0
 804d012:	01 d8                	add    eax,ebx
 804d014:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804d019:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804d01f:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804d025:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804d02b:	61                   	popa   
 804d02c:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804d032:	5e                   	pop    esi
 804d033:	68 7f d1 04 08       	push   0x804d17f
 804d038:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804d03f:	00 00 00 
 804d042:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804d049:	00 00 00 
 804d04c:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804d053:	00 00 00 
 804d056:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804d05d:	00 00 00 
 804d060:	6a 01                	push   0x1
 804d062:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804d068:	6a 00                	push   0x0
 804d06a:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804d070:	60                   	pusha  
 804d071:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804d076:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804d07c:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804d082:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804d088:	be 00 00 00 00       	mov    esi,0x0
 804d08d:	bf 00 00 00 00       	mov    edi,0x0
 804d092:	bd 00 00 00 00       	mov    ebp,0x0
 804d097:	39 d8                	cmp    eax,ebx
 804d099:	7c 1d                	jl     804d0b8 <..@2452._jmp>
 804d09b:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804d0a0:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804d0a6:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804d0ac:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804d0b2:	61                   	popa   
 804d0b3:	83 c4 04             	add    esp,0x4
 804d0b6:	eb 1f                	jmp    804d0d7 <..@2452._end>

0804d0b8 <..@2452._jmp>:
 804d0b8:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804d0bd:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804d0c3:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804d0c9:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804d0cf:	61                   	popa   
 804d0d0:	83 c4 04             	add    esp,0x4
 804d0d3:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804d0d7 <..@2452._end>:
 804d0d7:	68 cf d2 04 08       	push   0x804d2cf
 804d0dc:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804d0e3:	00 00 00 
 804d0e6:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804d0ed:	00 00 00 
 804d0f0:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804d0f7:	00 00 00 
 804d0fa:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804d101:	00 00 00 
 804d104:	56                   	push   esi
 804d105:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804d10b:	6a 02                	push   0x2
 804d10d:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804d113:	60                   	pusha  
 804d114:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804d119:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804d11f:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804d125:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804d12b:	be 00 00 00 00       	mov    esi,0x0
 804d130:	bf 00 00 00 00       	mov    edi,0x0
 804d135:	bd 00 00 00 00       	mov    ebp,0x0
 804d13a:	39 d8                	cmp    eax,ebx
 804d13c:	73 1d                	jae    804d15b <..@2469._jmp>
 804d13e:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804d143:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804d149:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804d14f:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804d155:	61                   	popa   
 804d156:	83 c4 04             	add    esp,0x4
 804d159:	eb 1f                	jmp    804d17a <..@2469._end>

0804d15b <..@2469._jmp>:
 804d15b:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804d160:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804d166:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804d16c:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804d172:	61                   	popa   
 804d173:	83 c4 04             	add    esp,0x4
 804d176:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804d17a <..@2469._end>:
 804d17a:	e9 a3 00 00 00       	jmp    804d222 <..@2414._end>

0804d17f <..@2414._less>:
 804d17f:	68 cf d2 04 08       	push   0x804d2cf
 804d184:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804d18b:	00 00 00 
 804d18e:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804d195:	00 00 00 
 804d198:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804d19f:	00 00 00 
 804d1a2:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804d1a9:	00 00 00 
 804d1ac:	56                   	push   esi
 804d1ad:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804d1b3:	6a 02                	push   0x2
 804d1b5:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804d1bb:	60                   	pusha  
 804d1bc:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804d1c1:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804d1c7:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804d1cd:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804d1d3:	be 00 00 00 00       	mov    esi,0x0
 804d1d8:	bf 00 00 00 00       	mov    edi,0x0
 804d1dd:	bd 00 00 00 00       	mov    ebp,0x0
 804d1e2:	39 d8                	cmp    eax,ebx
 804d1e4:	76 1d                	jbe    804d203 <..@2486._jmp>
 804d1e6:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804d1eb:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804d1f1:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804d1f7:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804d1fd:	61                   	popa   
 804d1fe:	83 c4 04             	add    esp,0x4
 804d201:	eb 1f                	jmp    804d222 <..@2414._end>

0804d203 <..@2486._jmp>:
 804d203:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804d208:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804d20e:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804d214:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804d21a:	61                   	popa   
 804d21b:	83 c4 04             	add    esp,0x4
 804d21e:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804d222 <..@2414._end>:
 804d222:	89 d7                	mov    edi,edx
 804d224:	83 c7 0c             	add    edi,0xc
 804d227:	89 cd                	mov    ebp,ecx
 804d229:	29 fd                	sub    ebp,edi
 804d22b:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804d232:	00 00 00 
 804d235:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804d23c:	00 00 00 
 804d23f:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804d246:	00 00 00 
 804d249:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804d250:	00 00 00 
 804d253:	52                   	push   edx
 804d254:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804d25a:	57                   	push   edi
 804d25b:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804d261:	55                   	push   ebp
 804d262:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 804d268:	60                   	pusha  
 804d269:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804d26e:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804d274:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804d27a:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804d280:	be 00 00 00 00       	mov    esi,0x0
 804d285:	bf 00 00 00 00       	mov    edi,0x0
 804d28a:	bd 00 00 00 00       	mov    ebp,0x0
 804d28f:	39 d8                	cmp    eax,ebx
 804d291:	72 0e                	jb     804d2a1 <..@2502.left>
 804d293:	01 c8                	add    eax,ecx
 804d295:	01 cb                	add    ebx,ecx

0804d297 <..@2502.right>:
 804d297:	48                   	dec    eax
 804d298:	4b                   	dec    ebx
 804d299:	8b 13                	mov    edx,DWORD PTR [ebx]
 804d29b:	89 10                	mov    DWORD PTR [eax],edx
 804d29d:	e2 f8                	loop   804d297 <..@2502.right>
 804d29f:	eb 08                	jmp    804d2a9 <..@2502.end>

0804d2a1 <..@2502.left>:
 804d2a1:	8b 13                	mov    edx,DWORD PTR [ebx]
 804d2a3:	89 10                	mov    DWORD PTR [eax],edx
 804d2a5:	40                   	inc    eax
 804d2a6:	43                   	inc    ebx
 804d2a7:	e2 f8                	loop   804d2a1 <..@2502.left>

0804d2a9 <..@2502.end>:
 804d2a9:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804d2ae:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804d2b4:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804d2ba:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804d2c0:	61                   	popa   
 804d2c1:	83 e9 0c             	sub    ecx,0xc
 804d2c4:	83 eb 0c             	sub    ebx,0xc
 804d2c7:	83 ea 0c             	sub    edx,0xc
 804d2ca:	e9 e5 fc ff ff       	jmp    804cfb4 <..@2415.__jup>

0804d2cf <..@2415.__jdown>:
 804d2cf:	83 c2 18             	add    edx,0x18
 804d2d2:	e9 ad 0b 00 00       	jmp    804de84 <_________macro_ops_end7>

0804d2d7 <_________macro_ops_not7_3>:
 804d2d7:	81 fd 2a 3d 00 00    	cmp    ebp,0x3d2a
 804d2dd:	0f 85 d8 03 00 00    	jne    804d6bb <_________macro_ops_not7_4>
 804d2e3:	60                   	pusha  
 804d2e4:	89 d1                	mov    ecx,edx
 804d2e6:	8b 41 f8             	mov    eax,DWORD PTR [ecx-0x8]
 804d2e9:	8b 59 10             	mov    ebx,DWORD PTR [ecx+0x10]
 804d2ec:	f7 e3                	mul    ebx
 804d2ee:	89 ca                	mov    edx,ecx
 804d2f0:	89 41 10             	mov    DWORD PTR [ecx+0x10],eax
 804d2f3:	8b 5a f4             	mov    ebx,DWORD PTR [edx-0xc]
 804d2f6:	89 5a 0c             	mov    DWORD PTR [edx+0xc],ebx
 804d2f9:	8b 72 fc             	mov    esi,DWORD PTR [edx-0x4]
 804d2fc:	89 72 14             	mov    DWORD PTR [edx+0x14],esi
 804d2ff:	83 fe 04             	cmp    esi,0x4
 804d302:	75 02                	jne    804d306 <_________macro_ops_assign7_4_n4>
 804d304:	89 03                	mov    DWORD PTR [ebx],eax

0804d306 <_________macro_ops_assign7_4_n4>:
 804d306:	83 fe 02             	cmp    esi,0x2
 804d309:	75 03                	jne    804d30e <_________macro_ops_assign7_4_n2>
 804d30b:	66 89 03             	mov    WORD PTR [ebx],ax

0804d30e <_________macro_ops_assign7_4_n2>:
 804d30e:	83 fe 01             	cmp    esi,0x1
 804d311:	75 02                	jne    804d315 <_________macro_ops_assign7_4_n1>
 804d313:	88 03                	mov    BYTE PTR [ebx],al

0804d315 <_________macro_ops_assign7_4_n1>:
 804d315:	61                   	popa   
 804d316:	6a 00                	push   0x0
 804d318:	5e                   	pop    esi
 804d319:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804d320:	00 00 00 
 804d323:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804d32a:	00 00 00 
 804d32d:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804d334:	00 00 00 
 804d337:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804d33e:	00 00 00 
 804d341:	56                   	push   esi
 804d342:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804d348:	6a 01                	push   0x1
 804d34a:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804d350:	60                   	pusha  
 804d351:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804d356:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804d35c:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804d362:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804d368:	be 00 00 00 00       	mov    esi,0x0
 804d36d:	bf 00 00 00 00       	mov    edi,0x0
 804d372:	bd 00 00 00 00       	mov    ebp,0x0
 804d377:	29 d8                	sub    eax,ebx
 804d379:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804d37e:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804d384:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804d38a:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804d390:	61                   	popa   
 804d391:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804d397:	5e                   	pop    esi

0804d398 <..@2522.__jup>:
 804d398:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804d39f:	00 00 00 
 804d3a2:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804d3a9:	00 00 00 
 804d3ac:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804d3b3:	00 00 00 
 804d3b6:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804d3bd:	00 00 00 
 804d3c0:	56                   	push   esi
 804d3c1:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804d3c7:	6a 01                	push   0x1
 804d3c9:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804d3cf:	60                   	pusha  
 804d3d0:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804d3d5:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804d3db:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804d3e1:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804d3e7:	be 00 00 00 00       	mov    esi,0x0
 804d3ec:	bf 00 00 00 00       	mov    edi,0x0
 804d3f1:	bd 00 00 00 00       	mov    ebp,0x0
 804d3f6:	01 d8                	add    eax,ebx
 804d3f8:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804d3fd:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804d403:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804d409:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804d40f:	61                   	popa   
 804d410:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804d416:	5e                   	pop    esi
 804d417:	68 63 d5 04 08       	push   0x804d563
 804d41c:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804d423:	00 00 00 
 804d426:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804d42d:	00 00 00 
 804d430:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804d437:	00 00 00 
 804d43a:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804d441:	00 00 00 
 804d444:	6a 01                	push   0x1
 804d446:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804d44c:	6a 00                	push   0x0
 804d44e:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804d454:	60                   	pusha  
 804d455:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804d45a:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804d460:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804d466:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804d46c:	be 00 00 00 00       	mov    esi,0x0
 804d471:	bf 00 00 00 00       	mov    edi,0x0
 804d476:	bd 00 00 00 00       	mov    ebp,0x0
 804d47b:	39 d8                	cmp    eax,ebx
 804d47d:	7c 1d                	jl     804d49c <..@2559._jmp>
 804d47f:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804d484:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804d48a:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804d490:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804d496:	61                   	popa   
 804d497:	83 c4 04             	add    esp,0x4
 804d49a:	eb 1f                	jmp    804d4bb <..@2559._end>

0804d49c <..@2559._jmp>:
 804d49c:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804d4a1:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804d4a7:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804d4ad:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804d4b3:	61                   	popa   
 804d4b4:	83 c4 04             	add    esp,0x4
 804d4b7:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804d4bb <..@2559._end>:
 804d4bb:	68 b3 d6 04 08       	push   0x804d6b3
 804d4c0:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804d4c7:	00 00 00 
 804d4ca:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804d4d1:	00 00 00 
 804d4d4:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804d4db:	00 00 00 
 804d4de:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804d4e5:	00 00 00 
 804d4e8:	56                   	push   esi
 804d4e9:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804d4ef:	6a 02                	push   0x2
 804d4f1:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804d4f7:	60                   	pusha  
 804d4f8:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804d4fd:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804d503:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804d509:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804d50f:	be 00 00 00 00       	mov    esi,0x0
 804d514:	bf 00 00 00 00       	mov    edi,0x0
 804d519:	bd 00 00 00 00       	mov    ebp,0x0
 804d51e:	39 d8                	cmp    eax,ebx
 804d520:	73 1d                	jae    804d53f <..@2576._jmp>
 804d522:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804d527:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804d52d:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804d533:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804d539:	61                   	popa   
 804d53a:	83 c4 04             	add    esp,0x4
 804d53d:	eb 1f                	jmp    804d55e <..@2576._end>

0804d53f <..@2576._jmp>:
 804d53f:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804d544:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804d54a:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804d550:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804d556:	61                   	popa   
 804d557:	83 c4 04             	add    esp,0x4
 804d55a:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804d55e <..@2576._end>:
 804d55e:	e9 a3 00 00 00       	jmp    804d606 <..@2521._end>

0804d563 <..@2521._less>:
 804d563:	68 b3 d6 04 08       	push   0x804d6b3
 804d568:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804d56f:	00 00 00 
 804d572:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804d579:	00 00 00 
 804d57c:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804d583:	00 00 00 
 804d586:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804d58d:	00 00 00 
 804d590:	56                   	push   esi
 804d591:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804d597:	6a 02                	push   0x2
 804d599:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804d59f:	60                   	pusha  
 804d5a0:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804d5a5:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804d5ab:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804d5b1:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804d5b7:	be 00 00 00 00       	mov    esi,0x0
 804d5bc:	bf 00 00 00 00       	mov    edi,0x0
 804d5c1:	bd 00 00 00 00       	mov    ebp,0x0
 804d5c6:	39 d8                	cmp    eax,ebx
 804d5c8:	76 1d                	jbe    804d5e7 <..@2593._jmp>
 804d5ca:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804d5cf:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804d5d5:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804d5db:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804d5e1:	61                   	popa   
 804d5e2:	83 c4 04             	add    esp,0x4
 804d5e5:	eb 1f                	jmp    804d606 <..@2521._end>

0804d5e7 <..@2593._jmp>:
 804d5e7:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804d5ec:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804d5f2:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804d5f8:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804d5fe:	61                   	popa   
 804d5ff:	83 c4 04             	add    esp,0x4
 804d602:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804d606 <..@2521._end>:
 804d606:	89 d7                	mov    edi,edx
 804d608:	83 c7 0c             	add    edi,0xc
 804d60b:	89 cd                	mov    ebp,ecx
 804d60d:	29 fd                	sub    ebp,edi
 804d60f:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804d616:	00 00 00 
 804d619:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804d620:	00 00 00 
 804d623:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804d62a:	00 00 00 
 804d62d:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804d634:	00 00 00 
 804d637:	52                   	push   edx
 804d638:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804d63e:	57                   	push   edi
 804d63f:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804d645:	55                   	push   ebp
 804d646:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 804d64c:	60                   	pusha  
 804d64d:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804d652:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804d658:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804d65e:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804d664:	be 00 00 00 00       	mov    esi,0x0
 804d669:	bf 00 00 00 00       	mov    edi,0x0
 804d66e:	bd 00 00 00 00       	mov    ebp,0x0
 804d673:	39 d8                	cmp    eax,ebx
 804d675:	72 0e                	jb     804d685 <..@2609.left>
 804d677:	01 c8                	add    eax,ecx
 804d679:	01 cb                	add    ebx,ecx

0804d67b <..@2609.right>:
 804d67b:	48                   	dec    eax
 804d67c:	4b                   	dec    ebx
 804d67d:	8b 13                	mov    edx,DWORD PTR [ebx]
 804d67f:	89 10                	mov    DWORD PTR [eax],edx
 804d681:	e2 f8                	loop   804d67b <..@2609.right>
 804d683:	eb 08                	jmp    804d68d <..@2609.end>

0804d685 <..@2609.left>:
 804d685:	8b 13                	mov    edx,DWORD PTR [ebx]
 804d687:	89 10                	mov    DWORD PTR [eax],edx
 804d689:	40                   	inc    eax
 804d68a:	43                   	inc    ebx
 804d68b:	e2 f8                	loop   804d685 <..@2609.left>

0804d68d <..@2609.end>:
 804d68d:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804d692:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804d698:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804d69e:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804d6a4:	61                   	popa   
 804d6a5:	83 e9 0c             	sub    ecx,0xc
 804d6a8:	83 eb 0c             	sub    ebx,0xc
 804d6ab:	83 ea 0c             	sub    edx,0xc
 804d6ae:	e9 e5 fc ff ff       	jmp    804d398 <..@2522.__jup>

0804d6b3 <..@2522.__jdown>:
 804d6b3:	83 c2 18             	add    edx,0x18
 804d6b6:	e9 c9 07 00 00       	jmp    804de84 <_________macro_ops_end7>

0804d6bb <_________macro_ops_not7_4>:
 804d6bb:	81 fd 2f 3d 00 00    	cmp    ebp,0x3d2f
 804d6c1:	0f 85 d9 03 00 00    	jne    804daa0 <_________macro_ops_not7_5>
 804d6c7:	60                   	pusha  
 804d6c8:	89 d1                	mov    ecx,edx
 804d6ca:	8b 41 f8             	mov    eax,DWORD PTR [ecx-0x8]
 804d6cd:	8b 59 10             	mov    ebx,DWORD PTR [ecx+0x10]
 804d6d0:	99                   	cdq    
 804d6d1:	f7 fb                	idiv   ebx
 804d6d3:	89 ca                	mov    edx,ecx
 804d6d5:	89 41 10             	mov    DWORD PTR [ecx+0x10],eax
 804d6d8:	8b 5a f4             	mov    ebx,DWORD PTR [edx-0xc]
 804d6db:	89 5a 0c             	mov    DWORD PTR [edx+0xc],ebx
 804d6de:	8b 72 fc             	mov    esi,DWORD PTR [edx-0x4]
 804d6e1:	89 72 14             	mov    DWORD PTR [edx+0x14],esi
 804d6e4:	83 fe 04             	cmp    esi,0x4
 804d6e7:	75 02                	jne    804d6eb <_________macro_ops_assign7_5_n4>
 804d6e9:	89 03                	mov    DWORD PTR [ebx],eax

0804d6eb <_________macro_ops_assign7_5_n4>:
 804d6eb:	83 fe 02             	cmp    esi,0x2
 804d6ee:	75 03                	jne    804d6f3 <_________macro_ops_assign7_5_n2>
 804d6f0:	66 89 03             	mov    WORD PTR [ebx],ax

0804d6f3 <_________macro_ops_assign7_5_n2>:
 804d6f3:	83 fe 01             	cmp    esi,0x1
 804d6f6:	75 02                	jne    804d6fa <_________macro_ops_assign7_5_n1>
 804d6f8:	88 03                	mov    BYTE PTR [ebx],al

0804d6fa <_________macro_ops_assign7_5_n1>:
 804d6fa:	61                   	popa   
 804d6fb:	6a 00                	push   0x0
 804d6fd:	5e                   	pop    esi
 804d6fe:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804d705:	00 00 00 
 804d708:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804d70f:	00 00 00 
 804d712:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804d719:	00 00 00 
 804d71c:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804d723:	00 00 00 
 804d726:	56                   	push   esi
 804d727:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804d72d:	6a 01                	push   0x1
 804d72f:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804d735:	60                   	pusha  
 804d736:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804d73b:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804d741:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804d747:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804d74d:	be 00 00 00 00       	mov    esi,0x0
 804d752:	bf 00 00 00 00       	mov    edi,0x0
 804d757:	bd 00 00 00 00       	mov    ebp,0x0
 804d75c:	29 d8                	sub    eax,ebx
 804d75e:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804d763:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804d769:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804d76f:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804d775:	61                   	popa   
 804d776:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804d77c:	5e                   	pop    esi

0804d77d <..@2629.__jup>:
 804d77d:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804d784:	00 00 00 
 804d787:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804d78e:	00 00 00 
 804d791:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804d798:	00 00 00 
 804d79b:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804d7a2:	00 00 00 
 804d7a5:	56                   	push   esi
 804d7a6:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804d7ac:	6a 01                	push   0x1
 804d7ae:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804d7b4:	60                   	pusha  
 804d7b5:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804d7ba:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804d7c0:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804d7c6:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804d7cc:	be 00 00 00 00       	mov    esi,0x0
 804d7d1:	bf 00 00 00 00       	mov    edi,0x0
 804d7d6:	bd 00 00 00 00       	mov    ebp,0x0
 804d7db:	01 d8                	add    eax,ebx
 804d7dd:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804d7e2:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804d7e8:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804d7ee:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804d7f4:	61                   	popa   
 804d7f5:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804d7fb:	5e                   	pop    esi
 804d7fc:	68 48 d9 04 08       	push   0x804d948
 804d801:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804d808:	00 00 00 
 804d80b:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804d812:	00 00 00 
 804d815:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804d81c:	00 00 00 
 804d81f:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804d826:	00 00 00 
 804d829:	6a 01                	push   0x1
 804d82b:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804d831:	6a 00                	push   0x0
 804d833:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804d839:	60                   	pusha  
 804d83a:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804d83f:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804d845:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804d84b:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804d851:	be 00 00 00 00       	mov    esi,0x0
 804d856:	bf 00 00 00 00       	mov    edi,0x0
 804d85b:	bd 00 00 00 00       	mov    ebp,0x0
 804d860:	39 d8                	cmp    eax,ebx
 804d862:	7c 1d                	jl     804d881 <..@2666._jmp>
 804d864:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804d869:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804d86f:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804d875:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804d87b:	61                   	popa   
 804d87c:	83 c4 04             	add    esp,0x4
 804d87f:	eb 1f                	jmp    804d8a0 <..@2666._end>

0804d881 <..@2666._jmp>:
 804d881:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804d886:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804d88c:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804d892:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804d898:	61                   	popa   
 804d899:	83 c4 04             	add    esp,0x4
 804d89c:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804d8a0 <..@2666._end>:
 804d8a0:	68 98 da 04 08       	push   0x804da98
 804d8a5:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804d8ac:	00 00 00 
 804d8af:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804d8b6:	00 00 00 
 804d8b9:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804d8c0:	00 00 00 
 804d8c3:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804d8ca:	00 00 00 
 804d8cd:	56                   	push   esi
 804d8ce:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804d8d4:	6a 02                	push   0x2
 804d8d6:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804d8dc:	60                   	pusha  
 804d8dd:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804d8e2:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804d8e8:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804d8ee:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804d8f4:	be 00 00 00 00       	mov    esi,0x0
 804d8f9:	bf 00 00 00 00       	mov    edi,0x0
 804d8fe:	bd 00 00 00 00       	mov    ebp,0x0
 804d903:	39 d8                	cmp    eax,ebx
 804d905:	73 1d                	jae    804d924 <..@2683._jmp>
 804d907:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804d90c:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804d912:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804d918:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804d91e:	61                   	popa   
 804d91f:	83 c4 04             	add    esp,0x4
 804d922:	eb 1f                	jmp    804d943 <..@2683._end>

0804d924 <..@2683._jmp>:
 804d924:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804d929:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804d92f:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804d935:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804d93b:	61                   	popa   
 804d93c:	83 c4 04             	add    esp,0x4
 804d93f:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804d943 <..@2683._end>:
 804d943:	e9 a3 00 00 00       	jmp    804d9eb <..@2628._end>

0804d948 <..@2628._less>:
 804d948:	68 98 da 04 08       	push   0x804da98
 804d94d:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804d954:	00 00 00 
 804d957:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804d95e:	00 00 00 
 804d961:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804d968:	00 00 00 
 804d96b:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804d972:	00 00 00 
 804d975:	56                   	push   esi
 804d976:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804d97c:	6a 02                	push   0x2
 804d97e:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804d984:	60                   	pusha  
 804d985:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804d98a:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804d990:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804d996:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804d99c:	be 00 00 00 00       	mov    esi,0x0
 804d9a1:	bf 00 00 00 00       	mov    edi,0x0
 804d9a6:	bd 00 00 00 00       	mov    ebp,0x0
 804d9ab:	39 d8                	cmp    eax,ebx
 804d9ad:	76 1d                	jbe    804d9cc <..@2700._jmp>
 804d9af:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804d9b4:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804d9ba:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804d9c0:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804d9c6:	61                   	popa   
 804d9c7:	83 c4 04             	add    esp,0x4
 804d9ca:	eb 1f                	jmp    804d9eb <..@2628._end>

0804d9cc <..@2700._jmp>:
 804d9cc:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804d9d1:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804d9d7:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804d9dd:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804d9e3:	61                   	popa   
 804d9e4:	83 c4 04             	add    esp,0x4
 804d9e7:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804d9eb <..@2628._end>:
 804d9eb:	89 d7                	mov    edi,edx
 804d9ed:	83 c7 0c             	add    edi,0xc
 804d9f0:	89 cd                	mov    ebp,ecx
 804d9f2:	29 fd                	sub    ebp,edi
 804d9f4:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804d9fb:	00 00 00 
 804d9fe:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804da05:	00 00 00 
 804da08:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804da0f:	00 00 00 
 804da12:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804da19:	00 00 00 
 804da1c:	52                   	push   edx
 804da1d:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804da23:	57                   	push   edi
 804da24:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804da2a:	55                   	push   ebp
 804da2b:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 804da31:	60                   	pusha  
 804da32:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804da37:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804da3d:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804da43:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804da49:	be 00 00 00 00       	mov    esi,0x0
 804da4e:	bf 00 00 00 00       	mov    edi,0x0
 804da53:	bd 00 00 00 00       	mov    ebp,0x0
 804da58:	39 d8                	cmp    eax,ebx
 804da5a:	72 0e                	jb     804da6a <..@2716.left>
 804da5c:	01 c8                	add    eax,ecx
 804da5e:	01 cb                	add    ebx,ecx

0804da60 <..@2716.right>:
 804da60:	48                   	dec    eax
 804da61:	4b                   	dec    ebx
 804da62:	8b 13                	mov    edx,DWORD PTR [ebx]
 804da64:	89 10                	mov    DWORD PTR [eax],edx
 804da66:	e2 f8                	loop   804da60 <..@2716.right>
 804da68:	eb 08                	jmp    804da72 <..@2716.end>

0804da6a <..@2716.left>:
 804da6a:	8b 13                	mov    edx,DWORD PTR [ebx]
 804da6c:	89 10                	mov    DWORD PTR [eax],edx
 804da6e:	40                   	inc    eax
 804da6f:	43                   	inc    ebx
 804da70:	e2 f8                	loop   804da6a <..@2716.left>

0804da72 <..@2716.end>:
 804da72:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804da77:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804da7d:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804da83:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804da89:	61                   	popa   
 804da8a:	83 e9 0c             	sub    ecx,0xc
 804da8d:	83 eb 0c             	sub    ebx,0xc
 804da90:	83 ea 0c             	sub    edx,0xc
 804da93:	e9 e5 fc ff ff       	jmp    804d77d <..@2629.__jup>

0804da98 <..@2629.__jdown>:
 804da98:	83 c2 18             	add    edx,0x18
 804da9b:	e9 e4 03 00 00       	jmp    804de84 <_________macro_ops_end7>

0804daa0 <_________macro_ops_not7_5>:
 804daa0:	81 fd 25 3d 00 00    	cmp    ebp,0x3d25
 804daa6:	0f 85 d8 03 00 00    	jne    804de84 <_________macro_ops_end7>
 804daac:	60                   	pusha  
 804daad:	89 d1                	mov    ecx,edx
 804daaf:	8b 41 f8             	mov    eax,DWORD PTR [ecx-0x8]
 804dab2:	8b 59 10             	mov    ebx,DWORD PTR [ecx+0x10]
 804dab5:	99                   	cdq    
 804dab6:	f7 fb                	idiv   ebx
 804dab8:	89 d0                	mov    eax,edx
 804daba:	89 ca                	mov    edx,ecx
 804dabc:	89 41 10             	mov    DWORD PTR [ecx+0x10],eax
 804dabf:	8b 5a f4             	mov    ebx,DWORD PTR [edx-0xc]
 804dac2:	89 5a 0c             	mov    DWORD PTR [edx+0xc],ebx
 804dac5:	8b 72 fc             	mov    esi,DWORD PTR [edx-0x4]
 804dac8:	89 72 14             	mov    DWORD PTR [edx+0x14],esi
 804dacb:	83 fe 04             	cmp    esi,0x4
 804dace:	75 02                	jne    804dad2 <_________macro_ops_assign7_6_n4>
 804dad0:	89 03                	mov    DWORD PTR [ebx],eax

0804dad2 <_________macro_ops_assign7_6_n4>:
 804dad2:	83 fe 02             	cmp    esi,0x2
 804dad5:	75 03                	jne    804dada <_________macro_ops_assign7_6_n2>
 804dad7:	66 89 03             	mov    WORD PTR [ebx],ax

0804dada <_________macro_ops_assign7_6_n2>:
 804dada:	83 fe 01             	cmp    esi,0x1
 804dadd:	75 02                	jne    804dae1 <_________macro_ops_assign7_6_n1>
 804dadf:	88 03                	mov    BYTE PTR [ebx],al

0804dae1 <_________macro_ops_assign7_6_n1>:
 804dae1:	61                   	popa   
 804dae2:	6a 00                	push   0x0
 804dae4:	5e                   	pop    esi
 804dae5:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804daec:	00 00 00 
 804daef:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804daf6:	00 00 00 
 804daf9:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804db00:	00 00 00 
 804db03:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804db0a:	00 00 00 
 804db0d:	56                   	push   esi
 804db0e:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804db14:	6a 01                	push   0x1
 804db16:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804db1c:	60                   	pusha  
 804db1d:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804db22:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804db28:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804db2e:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804db34:	be 00 00 00 00       	mov    esi,0x0
 804db39:	bf 00 00 00 00       	mov    edi,0x0
 804db3e:	bd 00 00 00 00       	mov    ebp,0x0
 804db43:	29 d8                	sub    eax,ebx
 804db45:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804db4a:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804db50:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804db56:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804db5c:	61                   	popa   
 804db5d:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804db63:	5e                   	pop    esi

0804db64 <..@2736.__jup>:
 804db64:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804db6b:	00 00 00 
 804db6e:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804db75:	00 00 00 
 804db78:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804db7f:	00 00 00 
 804db82:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804db89:	00 00 00 
 804db8c:	56                   	push   esi
 804db8d:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804db93:	6a 01                	push   0x1
 804db95:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804db9b:	60                   	pusha  
 804db9c:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804dba1:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804dba7:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804dbad:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804dbb3:	be 00 00 00 00       	mov    esi,0x0
 804dbb8:	bf 00 00 00 00       	mov    edi,0x0
 804dbbd:	bd 00 00 00 00       	mov    ebp,0x0
 804dbc2:	01 d8                	add    eax,ebx
 804dbc4:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804dbc9:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804dbcf:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804dbd5:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804dbdb:	61                   	popa   
 804dbdc:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804dbe2:	5e                   	pop    esi
 804dbe3:	68 2f dd 04 08       	push   0x804dd2f
 804dbe8:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804dbef:	00 00 00 
 804dbf2:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804dbf9:	00 00 00 
 804dbfc:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804dc03:	00 00 00 
 804dc06:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804dc0d:	00 00 00 
 804dc10:	6a 01                	push   0x1
 804dc12:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804dc18:	6a 00                	push   0x0
 804dc1a:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804dc20:	60                   	pusha  
 804dc21:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804dc26:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804dc2c:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804dc32:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804dc38:	be 00 00 00 00       	mov    esi,0x0
 804dc3d:	bf 00 00 00 00       	mov    edi,0x0
 804dc42:	bd 00 00 00 00       	mov    ebp,0x0
 804dc47:	39 d8                	cmp    eax,ebx
 804dc49:	7c 1d                	jl     804dc68 <..@2773._jmp>
 804dc4b:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804dc50:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804dc56:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804dc5c:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804dc62:	61                   	popa   
 804dc63:	83 c4 04             	add    esp,0x4
 804dc66:	eb 1f                	jmp    804dc87 <..@2773._end>

0804dc68 <..@2773._jmp>:
 804dc68:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804dc6d:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804dc73:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804dc79:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804dc7f:	61                   	popa   
 804dc80:	83 c4 04             	add    esp,0x4
 804dc83:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804dc87 <..@2773._end>:
 804dc87:	68 7f de 04 08       	push   0x804de7f
 804dc8c:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804dc93:	00 00 00 
 804dc96:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804dc9d:	00 00 00 
 804dca0:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804dca7:	00 00 00 
 804dcaa:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804dcb1:	00 00 00 
 804dcb4:	56                   	push   esi
 804dcb5:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804dcbb:	6a 02                	push   0x2
 804dcbd:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804dcc3:	60                   	pusha  
 804dcc4:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804dcc9:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804dccf:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804dcd5:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804dcdb:	be 00 00 00 00       	mov    esi,0x0
 804dce0:	bf 00 00 00 00       	mov    edi,0x0
 804dce5:	bd 00 00 00 00       	mov    ebp,0x0
 804dcea:	39 d8                	cmp    eax,ebx
 804dcec:	73 1d                	jae    804dd0b <..@2790._jmp>
 804dcee:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804dcf3:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804dcf9:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804dcff:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804dd05:	61                   	popa   
 804dd06:	83 c4 04             	add    esp,0x4
 804dd09:	eb 1f                	jmp    804dd2a <..@2790._end>

0804dd0b <..@2790._jmp>:
 804dd0b:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804dd10:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804dd16:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804dd1c:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804dd22:	61                   	popa   
 804dd23:	83 c4 04             	add    esp,0x4
 804dd26:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804dd2a <..@2790._end>:
 804dd2a:	e9 a3 00 00 00       	jmp    804ddd2 <..@2735._end>

0804dd2f <..@2735._less>:
 804dd2f:	68 7f de 04 08       	push   0x804de7f
 804dd34:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804dd3b:	00 00 00 
 804dd3e:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804dd45:	00 00 00 
 804dd48:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804dd4f:	00 00 00 
 804dd52:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804dd59:	00 00 00 
 804dd5c:	56                   	push   esi
 804dd5d:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804dd63:	6a 02                	push   0x2
 804dd65:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804dd6b:	60                   	pusha  
 804dd6c:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804dd71:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804dd77:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804dd7d:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804dd83:	be 00 00 00 00       	mov    esi,0x0
 804dd88:	bf 00 00 00 00       	mov    edi,0x0
 804dd8d:	bd 00 00 00 00       	mov    ebp,0x0
 804dd92:	39 d8                	cmp    eax,ebx
 804dd94:	76 1d                	jbe    804ddb3 <..@2807._jmp>
 804dd96:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804dd9b:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804dda1:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804dda7:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804ddad:	61                   	popa   
 804ddae:	83 c4 04             	add    esp,0x4
 804ddb1:	eb 1f                	jmp    804ddd2 <..@2735._end>

0804ddb3 <..@2807._jmp>:
 804ddb3:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804ddb8:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804ddbe:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804ddc4:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804ddca:	61                   	popa   
 804ddcb:	83 c4 04             	add    esp,0x4
 804ddce:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804ddd2 <..@2735._end>:
 804ddd2:	89 d7                	mov    edi,edx
 804ddd4:	83 c7 0c             	add    edi,0xc
 804ddd7:	89 cd                	mov    ebp,ecx
 804ddd9:	29 fd                	sub    ebp,edi
 804dddb:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804dde2:	00 00 00 
 804dde5:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804ddec:	00 00 00 
 804ddef:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804ddf6:	00 00 00 
 804ddf9:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804de00:	00 00 00 
 804de03:	52                   	push   edx
 804de04:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804de0a:	57                   	push   edi
 804de0b:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804de11:	55                   	push   ebp
 804de12:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 804de18:	60                   	pusha  
 804de19:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804de1e:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804de24:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804de2a:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804de30:	be 00 00 00 00       	mov    esi,0x0
 804de35:	bf 00 00 00 00       	mov    edi,0x0
 804de3a:	bd 00 00 00 00       	mov    ebp,0x0
 804de3f:	39 d8                	cmp    eax,ebx
 804de41:	72 0e                	jb     804de51 <..@2823.left>
 804de43:	01 c8                	add    eax,ecx
 804de45:	01 cb                	add    ebx,ecx

0804de47 <..@2823.right>:
 804de47:	48                   	dec    eax
 804de48:	4b                   	dec    ebx
 804de49:	8b 13                	mov    edx,DWORD PTR [ebx]
 804de4b:	89 10                	mov    DWORD PTR [eax],edx
 804de4d:	e2 f8                	loop   804de47 <..@2823.right>
 804de4f:	eb 08                	jmp    804de59 <..@2823.end>

0804de51 <..@2823.left>:
 804de51:	8b 13                	mov    edx,DWORD PTR [ebx]
 804de53:	89 10                	mov    DWORD PTR [eax],edx
 804de55:	40                   	inc    eax
 804de56:	43                   	inc    ebx
 804de57:	e2 f8                	loop   804de51 <..@2823.left>

0804de59 <..@2823.end>:
 804de59:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804de5e:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804de64:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804de6a:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804de70:	61                   	popa   
 804de71:	83 e9 0c             	sub    ecx,0xc
 804de74:	83 eb 0c             	sub    ebx,0xc
 804de77:	83 ea 0c             	sub    edx,0xc
 804de7a:	e9 e5 fc ff ff       	jmp    804db64 <..@2736.__jup>

0804de7f <..@2736.__jdown>:
 804de7f:	83 c2 18             	add    edx,0x18
 804de82:	eb 00                	jmp    804de84 <_________macro_ops_end7>

0804de84 <_________macro_ops_end7>:
 804de84:	e9 97 e8 ff ff       	jmp    804c720 <_________macro_ops_for_begin7>

0804de89 <_________macro_ops_for_end7>:
 804de89:	89 c8                	mov    eax,ecx
 804de8b:	e9 75 a2 ff ff       	jmp    8048105 <..@188.__jup>

0804de90 <..@188.__jdown>:
 804de90:	e9 bd 0b 00 00       	jmp    804ea52 <macro_expr_hash_jmp>

0804de95 <macro_bops>:
 804de95:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804de9c:	00 00 00 
 804de9f:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804dea6:	00 00 00 
 804dea9:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804deb0:	00 00 00 
 804deb3:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804deba:	00 00 00 
 804debd:	ff 74 24 10          	push   DWORD PTR [esp+0x10]
 804dec1:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804dec7:	ff 74 24 0c          	push   DWORD PTR [esp+0xc]
 804decb:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804ded1:	ff 74 24 08          	push   DWORD PTR [esp+0x8]
 804ded5:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 804dedb:	ff 74 24 04          	push   DWORD PTR [esp+0x4]
 804dedf:	8f 05 0e 29 05 08    	pop    DWORD PTR ds:0x805290e
 804dee5:	60                   	pusha  
 804dee6:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804deeb:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804def1:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804def7:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804defd:	be 00 00 00 00       	mov    esi,0x0
 804df02:	bf 00 00 00 00       	mov    edi,0x0
 804df07:	bd 00 00 00 00       	mov    ebp,0x0
 804df0c:	eb 41                	jmp    804df4f <..@2841._2>

0804df0e <..@2843.__jup>:
 804df0e:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804df13:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804df19:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804df1f:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804df25:	61                   	popa   
 804df26:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804df2c:	8f 44 24 04          	pop    DWORD PTR [esp+0x4]
 804df30:	ff 35 06 29 05 08    	push   DWORD PTR ds:0x8052906
 804df36:	8f 44 24 08          	pop    DWORD PTR [esp+0x8]
 804df3a:	ff 35 0a 29 05 08    	push   DWORD PTR ds:0x805290a
 804df40:	8f 44 24 0c          	pop    DWORD PTR [esp+0xc]
 804df44:	ff 35 0e 29 05 08    	push   DWORD PTR ds:0x805290e
 804df4a:	8f 44 24 10          	pop    DWORD PTR [esp+0x10]
 804df4e:	c3                   	ret    

0804df4f <..@2841._2>:
 804df4f:	89 c2                	mov    edx,eax

0804df51 <_________macro_ops_for_begin6>:
 804df51:	39 da                	cmp    edx,ebx
 804df53:	0f 83 e3 0a 00 00    	jae    804ea3c <_________macro_ops_for_end6>
 804df59:	68 68 df 04 08       	push   0x804df68
 804df5e:	68 c1 02 00 00       	push   0x2c1
 804df63:	e9 18 a1 ff ff       	jmp    8048080 <macro_pr_jmp>

0804df68 <..@2874._1>:
 804df68:	83 3a 02             	cmp    DWORD PTR [edx],0x2
 804df6b:	0f 85 c3 0a 00 00    	jne    804ea34 <_________macro_ops_end6>
 804df71:	8b 6a 04             	mov    ebp,DWORD PTR [edx+0x4]
 804df74:	83 fd 28             	cmp    ebp,0x28
 804df77:	75 0e                	jne    804df87 <_________macro_ops_not6_1>
 804df79:	83 c2 0c             	add    edx,0xc
 804df7c:	52                   	push   edx
 804df7d:	6a 00                	push   0x0
 804df7f:	83 ea 0c             	sub    edx,0xc
 804df82:	e9 ad 0a 00 00       	jmp    804ea34 <_________macro_ops_end6>

0804df87 <_________macro_ops_not6_1>:
 804df87:	83 fd 29             	cmp    ebp,0x29
 804df8a:	0f 85 0d 06 00 00    	jne    804e59d <_________macro_ops_not6_2>
 804df90:	89 d7                	mov    edi,edx
 804df92:	5d                   	pop    ebp
 804df93:	5e                   	pop    esi
 804df94:	56                   	push   esi
 804df95:	52                   	push   edx
 804df96:	51                   	push   ecx
 804df97:	6a 00                	push   0x0
 804df99:	e8 ee a0 ff ff       	call   804808c <macro_ops>
 804df9e:	59                   	pop    ecx
 804df9f:	5a                   	pop    edx
 804dfa0:	83 c4 08             	add    esp,0x8
 804dfa3:	29 d7                	sub    edi,edx
 804dfa5:	29 fb                	sub    ebx,edi
 804dfa7:	89 f5                	mov    ebp,esi
 804dfa9:	83 ed 18             	sub    ebp,0x18
 804dfac:	39 e8                	cmp    eax,ebp
 804dfae:	77 14                	ja     804dfc4 <_________macro_ops_ncall>
 804dfb0:	83 7d 00 01          	cmp    DWORD PTR [ebp+0x0],0x1
 804dfb4:	75 07                	jne    804dfbd <_________macro_ops_nfunc>
 804dfb6:	bd 01 00 00 00       	mov    ebp,0x1
 804dfbb:	eb 05                	jmp    804dfc2 <_________macro_ops_func>

0804dfbd <_________macro_ops_nfunc>:
 804dfbd:	bd 00 00 00 00       	mov    ebp,0x0

0804dfc2 <_________macro_ops_func>:
 804dfc2:	eb 05                	jmp    804dfc9 <_________macro_ops_call>

0804dfc4 <_________macro_ops_ncall>:
 804dfc4:	bd 00 00 00 00       	mov    ebp,0x0

0804dfc9 <_________macro_ops_call>:
 804dfc9:	83 fd 00             	cmp    ebp,0x0
 804dfcc:	0f 84 8b 01 00 00    	je     804e15d <_________macro_ops_par>
 804dfd2:	89 f5                	mov    ebp,esi
 804dfd4:	83 ed 18             	sub    ebp,0x18
 804dfd7:	89 d7                	mov    edi,edx
 804dfd9:	29 f7                	sub    edi,esi
 804dfdb:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804dfe2:	00 00 00 
 804dfe5:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804dfec:	00 00 00 
 804dfef:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804dff6:	00 00 00 
 804dff9:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804e000:	00 00 00 
 804e003:	57                   	push   edi
 804e004:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804e00a:	6a 0c                	push   0xc
 804e00c:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804e012:	60                   	pusha  
 804e013:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804e018:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804e01e:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804e024:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804e02a:	be 00 00 00 00       	mov    esi,0x0
 804e02f:	bf 00 00 00 00       	mov    edi,0x0
 804e034:	bd 00 00 00 00       	mov    ebp,0x0
 804e039:	99                   	cdq    
 804e03a:	f7 fb                	idiv   ebx
 804e03c:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804e041:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804e047:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804e04d:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804e053:	61                   	popa   
 804e054:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804e05a:	5f                   	pop    edi
 804e05b:	c7 02 01 00 00 00    	mov    DWORD PTR [edx],0x1
 804e061:	83 ff 00             	cmp    edi,0x0
 804e064:	75 13                	jne    804e079 <_________macro_ops_call_args_0>
 804e066:	6a 00                	push   0x0
 804e068:	6a 00                	push   0x0
 804e06a:	6a 00                	push   0x0
 804e06c:	6a 00                	push   0x0
 804e06e:	ff 55 04             	call   DWORD PTR [ebp+0x4]
 804e071:	8f 42 04             	pop    DWORD PTR [edx+0x4]
 804e074:	83 c4 0c             	add    esp,0xc
 804e077:	eb 63                	jmp    804e0dc <_________macro_ops_call_args_end>

0804e079 <_________macro_ops_call_args_0>:
 804e079:	83 ff 01             	cmp    edi,0x1
 804e07c:	75 14                	jne    804e092 <_________macro_ops_call_args_1>
 804e07e:	ff 76 04             	push   DWORD PTR [esi+0x4]
 804e081:	6a 00                	push   0x0
 804e083:	6a 00                	push   0x0
 804e085:	6a 00                	push   0x0
 804e087:	ff 55 04             	call   DWORD PTR [ebp+0x4]
 804e08a:	8f 42 04             	pop    DWORD PTR [edx+0x4]
 804e08d:	83 c4 0c             	add    esp,0xc
 804e090:	eb 4a                	jmp    804e0dc <_________macro_ops_call_args_end>

0804e092 <_________macro_ops_call_args_1>:
 804e092:	83 ff 02             	cmp    edi,0x2
 804e095:	75 15                	jne    804e0ac <_________macro_ops_call_args_2>
 804e097:	ff 76 04             	push   DWORD PTR [esi+0x4]
 804e09a:	ff 76 10             	push   DWORD PTR [esi+0x10]
 804e09d:	6a 00                	push   0x0
 804e09f:	6a 00                	push   0x0
 804e0a1:	ff 55 04             	call   DWORD PTR [ebp+0x4]
 804e0a4:	8f 42 04             	pop    DWORD PTR [edx+0x4]
 804e0a7:	83 c4 0c             	add    esp,0xc
 804e0aa:	eb 30                	jmp    804e0dc <_________macro_ops_call_args_end>

0804e0ac <_________macro_ops_call_args_2>:
 804e0ac:	83 ff 03             	cmp    edi,0x3
 804e0af:	75 16                	jne    804e0c7 <_________macro_ops_call_args_3>
 804e0b1:	ff 76 04             	push   DWORD PTR [esi+0x4]
 804e0b4:	ff 76 10             	push   DWORD PTR [esi+0x10]
 804e0b7:	ff 76 1c             	push   DWORD PTR [esi+0x1c]
 804e0ba:	6a 00                	push   0x0
 804e0bc:	ff 55 04             	call   DWORD PTR [ebp+0x4]
 804e0bf:	8f 42 04             	pop    DWORD PTR [edx+0x4]
 804e0c2:	83 c4 0c             	add    esp,0xc
 804e0c5:	eb 15                	jmp    804e0dc <_________macro_ops_call_args_end>

0804e0c7 <_________macro_ops_call_args_3>:
 804e0c7:	ff 76 04             	push   DWORD PTR [esi+0x4]
 804e0ca:	ff 76 10             	push   DWORD PTR [esi+0x10]
 804e0cd:	ff 76 1c             	push   DWORD PTR [esi+0x1c]
 804e0d0:	ff 76 28             	push   DWORD PTR [esi+0x28]
 804e0d3:	ff 55 04             	call   DWORD PTR [ebp+0x4]
 804e0d6:	8f 42 04             	pop    DWORD PTR [edx+0x4]
 804e0d9:	83 c4 0c             	add    esp,0xc

0804e0dc <_________macro_ops_call_args_end>:
 804e0dc:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804e0e3:	00 00 00 
 804e0e6:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804e0ed:	00 00 00 
 804e0f0:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804e0f7:	00 00 00 
 804e0fa:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804e101:	00 00 00 
 804e104:	56                   	push   esi
 804e105:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804e10b:	6a 0c                	push   0xc
 804e10d:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804e113:	60                   	pusha  
 804e114:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804e119:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804e11f:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804e125:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804e12b:	be 00 00 00 00       	mov    esi,0x0
 804e130:	bf 00 00 00 00       	mov    edi,0x0
 804e135:	bd 00 00 00 00       	mov    ebp,0x0
 804e13a:	29 d8                	sub    eax,ebx
 804e13c:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804e141:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804e147:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804e14d:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804e153:	61                   	popa   
 804e154:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804e15a:	5e                   	pop    esi
 804e15b:	eb 11                	jmp    804e16e <_________macro_ops_par_end>

0804e15d <_________macro_ops_par>:
 804e15d:	ff 72 f4             	push   DWORD PTR [edx-0xc]
 804e160:	8f 02                	pop    DWORD PTR [edx]
 804e162:	ff 72 f8             	push   DWORD PTR [edx-0x8]
 804e165:	8f 42 04             	pop    DWORD PTR [edx+0x4]
 804e168:	ff 72 fc             	push   DWORD PTR [edx-0x4]
 804e16b:	8f 42 08             	pop    DWORD PTR [edx+0x8]

0804e16e <_________macro_ops_par_end>:
 804e16e:	50                   	push   eax
 804e16f:	89 d0                	mov    eax,edx
 804e171:	29 f0                	sub    eax,esi
 804e173:	83 c0 0c             	add    eax,0xc
 804e176:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804e17d:	00 00 00 
 804e180:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804e187:	00 00 00 
 804e18a:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804e191:	00 00 00 
 804e194:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804e19b:	00 00 00 
 804e19e:	50                   	push   eax
 804e19f:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804e1a5:	6a 0c                	push   0xc
 804e1a7:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804e1ad:	60                   	pusha  
 804e1ae:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804e1b3:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804e1b9:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804e1bf:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804e1c5:	be 00 00 00 00       	mov    esi,0x0
 804e1ca:	bf 00 00 00 00       	mov    edi,0x0
 804e1cf:	bd 00 00 00 00       	mov    ebp,0x0
 804e1d4:	99                   	cdq    
 804e1d5:	f7 fb                	idiv   ebx
 804e1d7:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804e1dc:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804e1e2:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804e1e8:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804e1ee:	61                   	popa   
 804e1ef:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804e1f5:	58                   	pop    eax
 804e1f6:	83 ea 0c             	sub    edx,0xc
 804e1f9:	6a 00                	push   0x0
 804e1fb:	5e                   	pop    esi
 804e1fc:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804e203:	00 00 00 
 804e206:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804e20d:	00 00 00 
 804e210:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804e217:	00 00 00 
 804e21a:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804e221:	00 00 00 
 804e224:	56                   	push   esi
 804e225:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804e22b:	6a 01                	push   0x1
 804e22d:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804e233:	60                   	pusha  
 804e234:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804e239:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804e23f:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804e245:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804e24b:	be 00 00 00 00       	mov    esi,0x0
 804e250:	bf 00 00 00 00       	mov    edi,0x0
 804e255:	bd 00 00 00 00       	mov    ebp,0x0
 804e25a:	29 d8                	sub    eax,ebx
 804e25c:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804e261:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804e267:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804e26d:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804e273:	61                   	popa   
 804e274:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804e27a:	5e                   	pop    esi

0804e27b <..@2974.__jup>:
 804e27b:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804e282:	00 00 00 
 804e285:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804e28c:	00 00 00 
 804e28f:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804e296:	00 00 00 
 804e299:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804e2a0:	00 00 00 
 804e2a3:	56                   	push   esi
 804e2a4:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804e2aa:	6a 01                	push   0x1
 804e2ac:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804e2b2:	60                   	pusha  
 804e2b3:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804e2b8:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804e2be:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804e2c4:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804e2ca:	be 00 00 00 00       	mov    esi,0x0
 804e2cf:	bf 00 00 00 00       	mov    edi,0x0
 804e2d4:	bd 00 00 00 00       	mov    ebp,0x0
 804e2d9:	01 d8                	add    eax,ebx
 804e2db:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804e2e0:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804e2e6:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804e2ec:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804e2f2:	61                   	popa   
 804e2f3:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804e2f9:	5e                   	pop    esi
 804e2fa:	68 45 e4 04 08       	push   0x804e445
 804e2ff:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804e306:	00 00 00 
 804e309:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804e310:	00 00 00 
 804e313:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804e31a:	00 00 00 
 804e31d:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804e324:	00 00 00 
 804e327:	6a 01                	push   0x1
 804e329:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804e32f:	6a 00                	push   0x0
 804e331:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804e337:	60                   	pusha  
 804e338:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804e33d:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804e343:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804e349:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804e34f:	be 00 00 00 00       	mov    esi,0x0
 804e354:	bf 00 00 00 00       	mov    edi,0x0
 804e359:	bd 00 00 00 00       	mov    ebp,0x0
 804e35e:	39 d8                	cmp    eax,ebx
 804e360:	7c 1d                	jl     804e37f <..@3011._jmp>
 804e362:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804e367:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804e36d:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804e373:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804e379:	61                   	popa   
 804e37a:	83 c4 04             	add    esp,0x4
 804e37d:	eb 1f                	jmp    804e39e <..@3011._end>

0804e37f <..@3011._jmp>:
 804e37f:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804e384:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804e38a:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804e390:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804e396:	61                   	popa   
 804e397:	83 c4 04             	add    esp,0x4
 804e39a:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804e39e <..@3011._end>:
 804e39e:	68 94 e5 04 08       	push   0x804e594
 804e3a3:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804e3aa:	00 00 00 
 804e3ad:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804e3b4:	00 00 00 
 804e3b7:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804e3be:	00 00 00 
 804e3c1:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804e3c8:	00 00 00 
 804e3cb:	56                   	push   esi
 804e3cc:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804e3d2:	50                   	push   eax
 804e3d3:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804e3d9:	60                   	pusha  
 804e3da:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804e3df:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804e3e5:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804e3eb:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804e3f1:	be 00 00 00 00       	mov    esi,0x0
 804e3f6:	bf 00 00 00 00       	mov    edi,0x0
 804e3fb:	bd 00 00 00 00       	mov    ebp,0x0
 804e400:	39 d8                	cmp    eax,ebx
 804e402:	73 1d                	jae    804e421 <..@3028._jmp>
 804e404:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804e409:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804e40f:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804e415:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804e41b:	61                   	popa   
 804e41c:	83 c4 04             	add    esp,0x4
 804e41f:	eb 1f                	jmp    804e440 <..@3028._end>

0804e421 <..@3028._jmp>:
 804e421:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804e426:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804e42c:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804e432:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804e438:	61                   	popa   
 804e439:	83 c4 04             	add    esp,0x4
 804e43c:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804e440 <..@3028._end>:
 804e440:	e9 a2 00 00 00       	jmp    804e4e7 <..@2973._end>

0804e445 <..@2973._less>:
 804e445:	68 94 e5 04 08       	push   0x804e594
 804e44a:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804e451:	00 00 00 
 804e454:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804e45b:	00 00 00 
 804e45e:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804e465:	00 00 00 
 804e468:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804e46f:	00 00 00 
 804e472:	56                   	push   esi
 804e473:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804e479:	50                   	push   eax
 804e47a:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804e480:	60                   	pusha  
 804e481:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804e486:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804e48c:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804e492:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804e498:	be 00 00 00 00       	mov    esi,0x0
 804e49d:	bf 00 00 00 00       	mov    edi,0x0
 804e4a2:	bd 00 00 00 00       	mov    ebp,0x0
 804e4a7:	39 d8                	cmp    eax,ebx
 804e4a9:	76 1d                	jbe    804e4c8 <..@3045._jmp>
 804e4ab:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804e4b0:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804e4b6:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804e4bc:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804e4c2:	61                   	popa   
 804e4c3:	83 c4 04             	add    esp,0x4
 804e4c6:	eb 1f                	jmp    804e4e7 <..@2973._end>

0804e4c8 <..@3045._jmp>:
 804e4c8:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804e4cd:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804e4d3:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804e4d9:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804e4df:	61                   	popa   
 804e4e0:	83 c4 04             	add    esp,0x4
 804e4e3:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804e4e7 <..@2973._end>:
 804e4e7:	89 d7                	mov    edi,edx
 804e4e9:	83 c7 0c             	add    edi,0xc
 804e4ec:	89 cd                	mov    ebp,ecx
 804e4ee:	29 fd                	sub    ebp,edi
 804e4f0:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804e4f7:	00 00 00 
 804e4fa:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804e501:	00 00 00 
 804e504:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804e50b:	00 00 00 
 804e50e:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804e515:	00 00 00 
 804e518:	52                   	push   edx
 804e519:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804e51f:	57                   	push   edi
 804e520:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804e526:	55                   	push   ebp
 804e527:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 804e52d:	60                   	pusha  
 804e52e:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804e533:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804e539:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804e53f:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804e545:	be 00 00 00 00       	mov    esi,0x0
 804e54a:	bf 00 00 00 00       	mov    edi,0x0
 804e54f:	bd 00 00 00 00       	mov    ebp,0x0
 804e554:	39 d8                	cmp    eax,ebx
 804e556:	72 0e                	jb     804e566 <..@3061.left>
 804e558:	01 c8                	add    eax,ecx
 804e55a:	01 cb                	add    ebx,ecx

0804e55c <..@3061.right>:
 804e55c:	48                   	dec    eax
 804e55d:	4b                   	dec    ebx
 804e55e:	8b 13                	mov    edx,DWORD PTR [ebx]
 804e560:	89 10                	mov    DWORD PTR [eax],edx
 804e562:	e2 f8                	loop   804e55c <..@3061.right>
 804e564:	eb 08                	jmp    804e56e <..@3061.end>

0804e566 <..@3061.left>:
 804e566:	8b 13                	mov    edx,DWORD PTR [ebx]
 804e568:	89 10                	mov    DWORD PTR [eax],edx
 804e56a:	40                   	inc    eax
 804e56b:	43                   	inc    ebx
 804e56c:	e2 f8                	loop   804e566 <..@3061.left>

0804e56e <..@3061.end>:
 804e56e:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804e573:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804e579:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804e57f:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804e585:	61                   	popa   
 804e586:	83 e9 0c             	sub    ecx,0xc
 804e589:	83 eb 0c             	sub    ebx,0xc
 804e58c:	83 ea 0c             	sub    edx,0xc
 804e58f:	e9 e7 fc ff ff       	jmp    804e27b <..@2974.__jup>

0804e594 <..@2974.__jdown>:
 804e594:	83 c2 0c             	add    edx,0xc
 804e597:	58                   	pop    eax
 804e598:	e9 97 04 00 00       	jmp    804ea34 <_________macro_ops_end6>

0804e59d <_________macro_ops_not6_2>:
 804e59d:	81 fd 62 5b 00 00    	cmp    ebp,0x5b62
 804e5a3:	75 0e                	jne    804e5b3 <_________macro_ops_not6_3>
 804e5a5:	83 c2 0c             	add    edx,0xc
 804e5a8:	52                   	push   edx
 804e5a9:	6a 01                	push   0x1
 804e5ab:	83 ea 0c             	sub    edx,0xc
 804e5ae:	e9 81 04 00 00       	jmp    804ea34 <_________macro_ops_end6>

0804e5b3 <_________macro_ops_not6_3>:
 804e5b3:	81 fd 77 5b 00 00    	cmp    ebp,0x5b77
 804e5b9:	75 0e                	jne    804e5c9 <_________macro_ops_not6_4>
 804e5bb:	83 c2 0c             	add    edx,0xc
 804e5be:	52                   	push   edx
 804e5bf:	6a 02                	push   0x2
 804e5c1:	83 ea 0c             	sub    edx,0xc
 804e5c4:	e9 6b 04 00 00       	jmp    804ea34 <_________macro_ops_end6>

0804e5c9 <_________macro_ops_not6_4>:
 804e5c9:	81 fd 64 5b 00 00    	cmp    ebp,0x5b64
 804e5cf:	75 0e                	jne    804e5df <_________macro_ops_not6_5>
 804e5d1:	83 c2 0c             	add    edx,0xc
 804e5d4:	52                   	push   edx
 804e5d5:	6a 04                	push   0x4
 804e5d7:	83 ea 0c             	sub    edx,0xc
 804e5da:	e9 55 04 00 00       	jmp    804ea34 <_________macro_ops_end6>

0804e5df <_________macro_ops_not6_5>:
 804e5df:	81 fd 71 5b 00 00    	cmp    ebp,0x5b71
 804e5e5:	75 0e                	jne    804e5f5 <_________macro_ops_not6_7>
 804e5e7:	83 c2 0c             	add    edx,0xc
 804e5ea:	52                   	push   edx
 804e5eb:	6a 08                	push   0x8
 804e5ed:	83 ea 0c             	sub    edx,0xc
 804e5f0:	e9 3f 04 00 00       	jmp    804ea34 <_________macro_ops_end6>

0804e5f5 <_________macro_ops_not6_7>:
 804e5f5:	83 fd 5b             	cmp    ebp,0x5b
 804e5f8:	75 0e                	jne    804e608 <_________macro_ops_not6_6>
 804e5fa:	83 c2 0c             	add    edx,0xc
 804e5fd:	52                   	push   edx
 804e5fe:	6a 04                	push   0x4
 804e600:	83 ea 0c             	sub    edx,0xc
 804e603:	e9 2c 04 00 00       	jmp    804ea34 <_________macro_ops_end6>

0804e608 <_________macro_ops_not6_6>:
 804e608:	83 fd 5d             	cmp    ebp,0x5d
 804e60b:	0f 85 23 04 00 00    	jne    804ea34 <_________macro_ops_end6>
 804e611:	89 d7                	mov    edi,edx
 804e613:	5d                   	pop    ebp
 804e614:	5e                   	pop    esi
 804e615:	56                   	push   esi
 804e616:	52                   	push   edx
 804e617:	51                   	push   ecx
 804e618:	6a 00                	push   0x0
 804e61a:	e8 6d 9a ff ff       	call   804808c <macro_ops>
 804e61f:	59                   	pop    ecx
 804e620:	5a                   	pop    edx
 804e621:	83 c4 08             	add    esp,0x8
 804e624:	29 d7                	sub    edi,edx
 804e626:	29 fb                	sub    ebx,edi
 804e628:	83 fd 01             	cmp    ebp,0x1
 804e62b:	75 1e                	jne    804e64b <_________macro_ops_get_n1>
 804e62d:	60                   	pusha  
 804e62e:	8b 5a f8             	mov    ebx,DWORD PTR [edx-0x8]
 804e631:	8b 4a e0             	mov    ecx,DWORD PTR [edx-0x20]
 804e634:	8d 1c 19             	lea    ebx,[ecx+ebx*1]
 804e637:	8a 03                	mov    al,BYTE PTR [ebx]
 804e639:	0f be c0             	movsx  eax,al
 804e63c:	89 42 04             	mov    DWORD PTR [edx+0x4],eax
 804e63f:	89 1a                	mov    DWORD PTR [edx],ebx
 804e641:	c7 42 08 01 00 00 00 	mov    DWORD PTR [edx+0x8],0x1
 804e648:	61                   	popa   
 804e649:	eb 44                	jmp    804e68f <_________macro_ops_get_end>

0804e64b <_________macro_ops_get_n1>:
 804e64b:	83 fd 02             	cmp    ebp,0x2
 804e64e:	75 1f                	jne    804e66f <_________macro_ops_get_n2>
 804e650:	60                   	pusha  
 804e651:	8b 5a f8             	mov    ebx,DWORD PTR [edx-0x8]
 804e654:	8b 4a e0             	mov    ecx,DWORD PTR [edx-0x20]
 804e657:	8d 1c 59             	lea    ebx,[ecx+ebx*2]
 804e65a:	66 8b 03             	mov    ax,WORD PTR [ebx]
 804e65d:	0f bf c0             	movsx  eax,ax
 804e660:	89 42 04             	mov    DWORD PTR [edx+0x4],eax
 804e663:	89 1a                	mov    DWORD PTR [edx],ebx
 804e665:	c7 42 08 02 00 00 00 	mov    DWORD PTR [edx+0x8],0x2
 804e66c:	61                   	popa   
 804e66d:	eb 20                	jmp    804e68f <_________macro_ops_get_end>

0804e66f <_________macro_ops_get_n2>:
 804e66f:	83 fd 04             	cmp    ebp,0x4
 804e672:	75 1b                	jne    804e68f <_________macro_ops_get_end>
 804e674:	60                   	pusha  
 804e675:	8b 5a f8             	mov    ebx,DWORD PTR [edx-0x8]
 804e678:	8b 4a e0             	mov    ecx,DWORD PTR [edx-0x20]
 804e67b:	8d 1c 99             	lea    ebx,[ecx+ebx*4]
 804e67e:	8b 03                	mov    eax,DWORD PTR [ebx]
 804e680:	89 42 04             	mov    DWORD PTR [edx+0x4],eax
 804e683:	89 1a                	mov    DWORD PTR [edx],ebx
 804e685:	c7 42 08 04 00 00 00 	mov    DWORD PTR [edx+0x8],0x4
 804e68c:	61                   	popa   
 804e68d:	eb 00                	jmp    804e68f <_________macro_ops_get_end>

0804e68f <_________macro_ops_get_end>:
 804e68f:	83 ea 0c             	sub    edx,0xc
 804e692:	6a 00                	push   0x0
 804e694:	5e                   	pop    esi
 804e695:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804e69c:	00 00 00 
 804e69f:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804e6a6:	00 00 00 
 804e6a9:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804e6b0:	00 00 00 
 804e6b3:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804e6ba:	00 00 00 
 804e6bd:	56                   	push   esi
 804e6be:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804e6c4:	6a 01                	push   0x1
 804e6c6:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804e6cc:	60                   	pusha  
 804e6cd:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804e6d2:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804e6d8:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804e6de:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804e6e4:	be 00 00 00 00       	mov    esi,0x0
 804e6e9:	bf 00 00 00 00       	mov    edi,0x0
 804e6ee:	bd 00 00 00 00       	mov    ebp,0x0
 804e6f3:	29 d8                	sub    eax,ebx
 804e6f5:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804e6fa:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804e700:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804e706:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804e70c:	61                   	popa   
 804e70d:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804e713:	5e                   	pop    esi

0804e714 <..@3087.__jup>:
 804e714:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804e71b:	00 00 00 
 804e71e:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804e725:	00 00 00 
 804e728:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804e72f:	00 00 00 
 804e732:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804e739:	00 00 00 
 804e73c:	56                   	push   esi
 804e73d:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804e743:	6a 01                	push   0x1
 804e745:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804e74b:	60                   	pusha  
 804e74c:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804e751:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804e757:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804e75d:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804e763:	be 00 00 00 00       	mov    esi,0x0
 804e768:	bf 00 00 00 00       	mov    edi,0x0
 804e76d:	bd 00 00 00 00       	mov    ebp,0x0
 804e772:	01 d8                	add    eax,ebx
 804e774:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804e779:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804e77f:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804e785:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804e78b:	61                   	popa   
 804e78c:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804e792:	5e                   	pop    esi
 804e793:	68 df e8 04 08       	push   0x804e8df
 804e798:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804e79f:	00 00 00 
 804e7a2:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804e7a9:	00 00 00 
 804e7ac:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804e7b3:	00 00 00 
 804e7b6:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804e7bd:	00 00 00 
 804e7c0:	6a 01                	push   0x1
 804e7c2:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804e7c8:	6a 00                	push   0x0
 804e7ca:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804e7d0:	60                   	pusha  
 804e7d1:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804e7d6:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804e7dc:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804e7e2:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804e7e8:	be 00 00 00 00       	mov    esi,0x0
 804e7ed:	bf 00 00 00 00       	mov    edi,0x0
 804e7f2:	bd 00 00 00 00       	mov    ebp,0x0
 804e7f7:	39 d8                	cmp    eax,ebx
 804e7f9:	7c 1d                	jl     804e818 <..@3124._jmp>
 804e7fb:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804e800:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804e806:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804e80c:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804e812:	61                   	popa   
 804e813:	83 c4 04             	add    esp,0x4
 804e816:	eb 1f                	jmp    804e837 <..@3124._end>

0804e818 <..@3124._jmp>:
 804e818:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804e81d:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804e823:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804e829:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804e82f:	61                   	popa   
 804e830:	83 c4 04             	add    esp,0x4
 804e833:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804e837 <..@3124._end>:
 804e837:	68 2f ea 04 08       	push   0x804ea2f
 804e83c:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804e843:	00 00 00 
 804e846:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804e84d:	00 00 00 
 804e850:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804e857:	00 00 00 
 804e85a:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804e861:	00 00 00 
 804e864:	56                   	push   esi
 804e865:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804e86b:	6a 03                	push   0x3
 804e86d:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804e873:	60                   	pusha  
 804e874:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804e879:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804e87f:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804e885:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804e88b:	be 00 00 00 00       	mov    esi,0x0
 804e890:	bf 00 00 00 00       	mov    edi,0x0
 804e895:	bd 00 00 00 00       	mov    ebp,0x0
 804e89a:	39 d8                	cmp    eax,ebx
 804e89c:	73 1d                	jae    804e8bb <..@3141._jmp>
 804e89e:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804e8a3:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804e8a9:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804e8af:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804e8b5:	61                   	popa   
 804e8b6:	83 c4 04             	add    esp,0x4
 804e8b9:	eb 1f                	jmp    804e8da <..@3141._end>

0804e8bb <..@3141._jmp>:
 804e8bb:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804e8c0:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804e8c6:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804e8cc:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804e8d2:	61                   	popa   
 804e8d3:	83 c4 04             	add    esp,0x4
 804e8d6:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804e8da <..@3141._end>:
 804e8da:	e9 a3 00 00 00       	jmp    804e982 <..@3086._end>

0804e8df <..@3086._less>:
 804e8df:	68 2f ea 04 08       	push   0x804ea2f
 804e8e4:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804e8eb:	00 00 00 
 804e8ee:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804e8f5:	00 00 00 
 804e8f8:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804e8ff:	00 00 00 
 804e902:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804e909:	00 00 00 
 804e90c:	56                   	push   esi
 804e90d:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804e913:	6a 03                	push   0x3
 804e915:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804e91b:	60                   	pusha  
 804e91c:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804e921:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804e927:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804e92d:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804e933:	be 00 00 00 00       	mov    esi,0x0
 804e938:	bf 00 00 00 00       	mov    edi,0x0
 804e93d:	bd 00 00 00 00       	mov    ebp,0x0
 804e942:	39 d8                	cmp    eax,ebx
 804e944:	76 1d                	jbe    804e963 <..@3158._jmp>
 804e946:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804e94b:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804e951:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804e957:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804e95d:	61                   	popa   
 804e95e:	83 c4 04             	add    esp,0x4
 804e961:	eb 1f                	jmp    804e982 <..@3086._end>

0804e963 <..@3158._jmp>:
 804e963:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804e968:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804e96e:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804e974:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804e97a:	61                   	popa   
 804e97b:	83 c4 04             	add    esp,0x4
 804e97e:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804e982 <..@3086._end>:
 804e982:	89 d7                	mov    edi,edx
 804e984:	83 c7 0c             	add    edi,0xc
 804e987:	89 cd                	mov    ebp,ecx
 804e989:	29 fd                	sub    ebp,edi
 804e98b:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804e992:	00 00 00 
 804e995:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804e99c:	00 00 00 
 804e99f:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804e9a6:	00 00 00 
 804e9a9:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804e9b0:	00 00 00 
 804e9b3:	52                   	push   edx
 804e9b4:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804e9ba:	57                   	push   edi
 804e9bb:	8f 05 06 29 05 08    	pop    DWORD PTR ds:0x8052906
 804e9c1:	55                   	push   ebp
 804e9c2:	8f 05 0a 29 05 08    	pop    DWORD PTR ds:0x805290a
 804e9c8:	60                   	pusha  
 804e9c9:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804e9ce:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804e9d4:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804e9da:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804e9e0:	be 00 00 00 00       	mov    esi,0x0
 804e9e5:	bf 00 00 00 00       	mov    edi,0x0
 804e9ea:	bd 00 00 00 00       	mov    ebp,0x0
 804e9ef:	39 d8                	cmp    eax,ebx
 804e9f1:	72 0e                	jb     804ea01 <..@3174.left>
 804e9f3:	01 c8                	add    eax,ecx
 804e9f5:	01 cb                	add    ebx,ecx

0804e9f7 <..@3174.right>:
 804e9f7:	48                   	dec    eax
 804e9f8:	4b                   	dec    ebx
 804e9f9:	8b 13                	mov    edx,DWORD PTR [ebx]
 804e9fb:	89 10                	mov    DWORD PTR [eax],edx
 804e9fd:	e2 f8                	loop   804e9f7 <..@3174.right>
 804e9ff:	eb 08                	jmp    804ea09 <..@3174.end>

0804ea01 <..@3174.left>:
 804ea01:	8b 13                	mov    edx,DWORD PTR [ebx]
 804ea03:	89 10                	mov    DWORD PTR [eax],edx
 804ea05:	40                   	inc    eax
 804ea06:	43                   	inc    ebx
 804ea07:	e2 f8                	loop   804ea01 <..@3174.left>

0804ea09 <..@3174.end>:
 804ea09:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804ea0e:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804ea14:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804ea1a:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804ea20:	61                   	popa   
 804ea21:	83 e9 0c             	sub    ecx,0xc
 804ea24:	83 eb 0c             	sub    ebx,0xc
 804ea27:	83 ea 0c             	sub    edx,0xc
 804ea2a:	e9 e5 fc ff ff       	jmp    804e714 <..@3087.__jup>

0804ea2f <..@3087.__jdown>:
 804ea2f:	83 c2 0c             	add    edx,0xc
 804ea32:	eb 00                	jmp    804ea34 <_________macro_ops_end6>

0804ea34 <_________macro_ops_end6>:
 804ea34:	83 c2 0c             	add    edx,0xc
 804ea37:	e9 15 f5 ff ff       	jmp    804df51 <_________macro_ops_for_begin6>

0804ea3c <_________macro_ops_for_end6>:
 804ea3c:	50                   	push   eax
 804ea3d:	53                   	push   ebx
 804ea3e:	51                   	push   ecx
 804ea3f:	6a 00                	push   0x0
 804ea41:	e8 46 96 ff ff       	call   804808c <macro_ops>
 804ea46:	59                   	pop    ecx
 804ea47:	5b                   	pop    ebx
 804ea48:	83 c4 08             	add    esp,0x8
 804ea4b:	89 c8                	mov    eax,ecx
 804ea4d:	e9 bc f4 ff ff       	jmp    804df0e <..@2843.__jup>

0804ea52 <macro_expr_hash_jmp>:
 804ea52:	60                   	pusha  
 804ea53:	83 c4 20             	add    esp,0x20
 804ea56:	5b                   	pop    ebx
 804ea57:	58                   	pop    eax
 804ea58:	83 ec 28             	sub    esp,0x28
 804ea5b:	89 c5                	mov    ebp,eax
 804ea5d:	89 df                	mov    edi,ebx
 804ea5f:	89 d9                	mov    ecx,ebx
 804ea61:	89 c3                	mov    ebx,eax
 804ea63:	b8 00 00 00 00       	mov    eax,0x0
 804ea68:	be 4b 00 00 00       	mov    esi,0x4b

0804ea6d <_________macro_expr_hash_1>:
 804ea6d:	f7 e6                	mul    esi
 804ea6f:	ba 00 00 00 00       	mov    edx,0x0
 804ea74:	8a 13                	mov    dl,BYTE PTR [ebx]
 804ea76:	80 ea 30             	sub    dl,0x30
 804ea79:	01 d0                	add    eax,edx
 804ea7b:	43                   	inc    ebx
 804ea7c:	e2 ef                	loop   804ea6d <_________macro_expr_hash_1>
 804ea7e:	f7 35 ae e3 0c 08    	div    DWORD PTR ds:0x80ce3ae
 804ea84:	8d 04 d5 22 c9 06 08 	lea    eax,[edx*8+0x806c922]
 804ea8b:	8b 5c 24 28          	mov    ebx,DWORD PTR [esp+0x28]
 804ea8f:	89 44 24 28          	mov    DWORD PTR [esp+0x28],eax
 804ea93:	89 5c 24 24          	mov    DWORD PTR [esp+0x24],ebx
 804ea97:	61                   	popa   
 804ea98:	83 c4 08             	add    esp,0x8
 804ea9b:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804ea9f <macro_var_jmp>:
 804ea9f:	60                   	pusha  
 804eaa0:	8b 74 24 20          	mov    esi,DWORD PTR [esp+0x20]
 804eaa4:	8b 7c 24 28          	mov    edi,DWORD PTR [esp+0x28]
 804eaa8:	89 fd                	mov    ebp,edi
 804eaaa:	29 f5                	sub    ebp,esi
 804eaac:	89 e9                	mov    ecx,ebp
 804eaae:	89 f3                	mov    ebx,esi
 804eab0:	68 b9 ea 04 08       	push   0x804eab9
 804eab5:	56                   	push   esi
 804eab6:	55                   	push   ebp
 804eab7:	eb 99                	jmp    804ea52 <macro_expr_hash_jmp>

0804eab9 <..@3200._1>:
 804eab9:	5b                   	pop    ebx
 804eaba:	8b 4c 24 24          	mov    ecx,DWORD PTR [esp+0x24]
 804eabe:	83 3b 00             	cmp    DWORD PTR [ebx],0x0
 804eac1:	74 2e                	je     804eaf1 <_________macro_var_stay_calm>
 804eac3:	e8 f6 1a 00 00       	call   80505be <__best_swrite+0x10>

0804eac8 <..@3203._1>:
 804eac8:	77 61                	ja     804eb2b <_________macro_expr_main_loop_begin+0xe>
 804eaca:	72 6e                	jb     804eb3a <_________macro_expr_g9+0x5>
 804eacc:	69                   	.byte 0x69
 804eacd:	6e                   	outs   dx,BYTE PTR ds:[esi]
 804eace:	67                   	addr16
 804eacf:	3a                   	.byte 0x3a

0804ead0 <..@3203._2>:
 804ead0:	60                   	pusha  
 804ead1:	b8 04 00 00 00       	mov    eax,0x4
 804ead6:	bb 01 00 00 00       	mov    ebx,0x1
 804eadb:	89 f1                	mov    ecx,esi
 804eadd:	89 ea                	mov    edx,ebp
 804eadf:	cd 80                	int    0x80
 804eae1:	61                   	popa   
 804eae2:	e8 ce 23 00 00       	call   8050eb5 <__best_sprint+0x14>

0804eae7 <..@3204._1>:
 804eae7:	20 72 65             	and    BYTE PTR [edx+0x65],dh
 804eaea:	64                   	fs
 804eaeb:	65                   	gs
 804eaec:	66                   	data16
 804eaed:	69                   	.byte 0x69
 804eaee:	6e                   	outs   dx,BYTE PTR ds:[esi]
 804eaef:	65                   	gs
 804eaf0:	64                   	fs

0804eaf1 <_________macro_var_stay_calm>:
 804eaf1:	89 0b                	mov    DWORD PTR [ebx],ecx
 804eaf3:	61                   	popa   
 804eaf4:	83 c4 0c             	add    esp,0xc
 804eaf7:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804eafb <macro_expr_jmp>:
 804eafb:	60                   	pusha  
 804eafc:	83 c4 20             	add    esp,0x20
 804eaff:	5d                   	pop    ebp
 804eb00:	5f                   	pop    edi
 804eb01:	83 ec 28             	sub    esp,0x28
 804eb04:	54                   	push   esp
 804eb05:	b8 00 00 00 00       	mov    eax,0x0
 804eb0a:	bb 00 00 00 00       	mov    ebx,0x0
 804eb0f:	b9 00 00 00 00       	mov    ecx,0x0
 804eb14:	be 00 00 00 00       	mov    esi,0x0
 804eb19:	b6 ff                	mov    dh,0xff
 804eb1b:	89 eb                	mov    ebx,ebp

0804eb1d <_________macro_expr_main_loop_begin>:
 804eb1d:	39 fb                	cmp    ebx,edi
 804eb1f:	0f 83 a2 02 00 00    	jae    804edc7 <_________macro_expr_main_loop_end>
 804eb25:	8a 0b                	mov    cl,BYTE PTR [ebx]
 804eb27:	b5 00                	mov    ch,0x0
 804eb29:	80 f9 30             	cmp    cl,0x30
 804eb2c:	72 07                	jb     804eb35 <_________macro_expr_g9>
 804eb2e:	80 f9 39             	cmp    cl,0x39
 804eb31:	77 02                	ja     804eb35 <_________macro_expr_g9>
 804eb33:	b5 01                	mov    ch,0x1

0804eb35 <_________macro_expr_g9>:
 804eb35:	80 f9 61             	cmp    cl,0x61
 804eb38:	72 07                	jb     804eb41 <_________macro_expr_gz>
 804eb3a:	80 f9 7a             	cmp    cl,0x7a
 804eb3d:	77 02                	ja     804eb41 <_________macro_expr_gz>
 804eb3f:	b5 02                	mov    ch,0x2

0804eb41 <_________macro_expr_gz>:
 804eb41:	80 f9 41             	cmp    cl,0x41
 804eb44:	72 07                	jb     804eb4d <_________macro_expr_gZ>
 804eb46:	80 f9 5a             	cmp    cl,0x5a
 804eb49:	77 02                	ja     804eb4d <_________macro_expr_gZ>
 804eb4b:	b5 02                	mov    ch,0x2

0804eb4d <_________macro_expr_gZ>:
 804eb4d:	80 f9 5f             	cmp    cl,0x5f
 804eb50:	75 02                	jne    804eb54 <_________macro_expr_nu>
 804eb52:	b5 02                	mov    ch,0x2

0804eb54 <_________macro_expr_nu>:
 804eb54:	80 f9 40             	cmp    cl,0x40
 804eb57:	75 02                	jne    804eb5b <_________macro_expr_na>
 804eb59:	b5 02                	mov    ch,0x2

0804eb5b <_________macro_expr_na>:
 804eb5b:	80 f9 2e             	cmp    cl,0x2e
 804eb5e:	75 02                	jne    804eb62 <_________macro_expr_nd>
 804eb60:	b5 02                	mov    ch,0x2

0804eb62 <_________macro_expr_nd>:
 804eb62:	80 f9 20             	cmp    cl,0x20
 804eb65:	75 02                	jne    804eb69 <_________macro_expr_ns>
 804eb67:	b5 03                	mov    ch,0x3

0804eb69 <_________macro_expr_ns>:
 804eb69:	80 f9 09             	cmp    cl,0x9
 804eb6c:	75 02                	jne    804eb70 <_________macro_expr_nt>
 804eb6e:	b5 03                	mov    ch,0x3

0804eb70 <_________macro_expr_nt>:
 804eb70:	80 f9 2c             	cmp    cl,0x2c
 804eb73:	75 02                	jne    804eb77 <_________macro_expr_nc>
 804eb75:	b5 04                	mov    ch,0x4

0804eb77 <_________macro_expr_nc>:
 804eb77:	80 f9 7c             	cmp    cl,0x7c
 804eb7a:	75 02                	jne    804eb7e <_________macro_expr_nv>
 804eb7c:	b5 05                	mov    ch,0x5

0804eb7e <_________macro_expr_nv>:
 804eb7e:	38 f5                	cmp    ch,dh
 804eb80:	0f 84 c9 00 00 00    	je     804ec4f <_________macro_expr_continuing>
 804eb86:	80 fe 00             	cmp    dh,0x0
 804eb89:	75 09                	jne    804eb94 <_________macro_expr_dh_n0>
 804eb8b:	58                   	pop    eax
 804eb8c:	6a 02                	push   0x2
 804eb8e:	56                   	push   esi
 804eb8f:	6a 00                	push   0x0
 804eb91:	50                   	push   eax
 804eb92:	eb 62                	jmp    804ebf6 <_________macro_expr_dh_end>

0804eb94 <_________macro_expr_dh_n0>:
 804eb94:	80 fe 01             	cmp    dh,0x1
 804eb97:	75 09                	jne    804eba2 <_________macro_expr_dh_n1>
 804eb99:	58                   	pop    eax
 804eb9a:	6a 01                	push   0x1
 804eb9c:	56                   	push   esi
 804eb9d:	6a 00                	push   0x0
 804eb9f:	50                   	push   eax
 804eba0:	eb 54                	jmp    804ebf6 <_________macro_expr_dh_end>

0804eba2 <_________macro_expr_dh_n1>:
 804eba2:	80 fe 02             	cmp    dh,0x2
 804eba5:	75 4f                	jne    804ebf6 <_________macro_expr_dh_end>
 804eba7:	29 f3                	sub    ebx,esi
 804eba9:	68 b5 eb 04 08       	push   0x804ebb5
 804ebae:	56                   	push   esi
 804ebaf:	53                   	push   ebx
 804ebb0:	e9 9d fe ff ff       	jmp    804ea52 <macro_expr_hash_jmp>

0804ebb5 <..@3206._1>:
 804ebb5:	58                   	pop    eax
 804ebb6:	83 38 00             	cmp    DWORD PTR [eax],0x0
 804ebb9:	75 2e                	jne    804ebe9 <_________macro_expr_stay_calm>
 804ebbb:	e8 fe 19 00 00       	call   80505be <__best_swrite+0x10>

0804ebc0 <..@3209._1>:
 804ebc0:	77 61                	ja     804ec23 <_________macro_expr_ch_n2+0xd>
 804ebc2:	72 6e                	jb     804ec32 <_________macro_expr_ch_n4+0x7>
 804ebc4:	69                   	.byte 0x69
 804ebc5:	6e                   	outs   dx,BYTE PTR ds:[esi]
 804ebc6:	67                   	addr16
 804ebc7:	3a                   	.byte 0x3a

0804ebc8 <..@3209._2>:
 804ebc8:	60                   	pusha  
 804ebc9:	89 da                	mov    edx,ebx
 804ebcb:	b8 04 00 00 00       	mov    eax,0x4
 804ebd0:	bb 02 00 00 00       	mov    ebx,0x2
 804ebd5:	89 f1                	mov    ecx,esi
 804ebd7:	cd 80                	int    0x80
 804ebd9:	61                   	popa   
 804ebda:	e8 d6 22 00 00       	call   8050eb5 <__best_sprint+0x14>

0804ebdf <..@3210._1>:
 804ebdf:	20 6e 6f             	and    BYTE PTR [esi+0x6f],ch
 804ebe2:	74 20                	je     804ec04 <_________macro_expr_ch_n0+0x4>
 804ebe4:	66 6f                	outs   dx,WORD PTR ds:[esi]
 804ebe6:	75 6e                	jne    804ec56 <_________macro_expr_continuing+0x7>
 804ebe8:	64                   	fs

0804ebe9 <_________macro_expr_stay_calm>:
 804ebe9:	01 f3                	add    ebx,esi
 804ebeb:	8b 00                	mov    eax,DWORD PTR [eax]
 804ebed:	89 c6                	mov    esi,eax
 804ebef:	58                   	pop    eax
 804ebf0:	6a 01                	push   0x1
 804ebf2:	56                   	push   esi
 804ebf3:	6a 00                	push   0x0
 804ebf5:	50                   	push   eax

0804ebf6 <_________macro_expr_dh_end>:
 804ebf6:	80 fd 00             	cmp    ch,0x0
 804ebf9:	75 05                	jne    804ec00 <_________macro_expr_ch_n0>
 804ebfb:	0f b6 f1             	movzx  esi,cl
 804ebfe:	eb 4a                	jmp    804ec4a <_________macro_expr_ch_end>

0804ec00 <_________macro_expr_ch_n0>:
 804ec00:	80 fd 01             	cmp    ch,0x1
 804ec03:	75 08                	jne    804ec0d <_________macro_expr_ch_n1>
 804ec05:	0f b6 f1             	movzx  esi,cl
 804ec08:	83 ee 30             	sub    esi,0x30
 804ec0b:	eb 3d                	jmp    804ec4a <_________macro_expr_ch_end>

0804ec0d <_________macro_expr_ch_n1>:
 804ec0d:	80 fd 02             	cmp    ch,0x2
 804ec10:	75 04                	jne    804ec16 <_________macro_expr_ch_n2>
 804ec12:	89 de                	mov    esi,ebx
 804ec14:	eb 34                	jmp    804ec4a <_________macro_expr_ch_end>

0804ec16 <_________macro_expr_ch_n2>:
 804ec16:	80 fd 04             	cmp    ch,0x4
 804ec19:	75 10                	jne    804ec2b <_________macro_expr_ch_n4>
 804ec1b:	58                   	pop    eax
 804ec1c:	6a 01                	push   0x1
 804ec1e:	6a 00                	push   0x0
 804ec20:	6a 00                	push   0x0
 804ec22:	6a 02                	push   0x2
 804ec24:	6a 2b                	push   0x2b
 804ec26:	6a 00                	push   0x0
 804ec28:	50                   	push   eax
 804ec29:	eb 1f                	jmp    804ec4a <_________macro_expr_ch_end>

0804ec2b <_________macro_expr_ch_n4>:
 804ec2b:	80 fd 05             	cmp    ch,0x5
 804ec2e:	75 1a                	jne    804ec4a <_________macro_expr_ch_end>
 804ec30:	58                   	pop    eax
 804ec31:	6a 02                	push   0x2
 804ec33:	6a 29                	push   0x29
 804ec35:	6a 00                	push   0x0
 804ec37:	6a 01                	push   0x1
 804ec39:	6a 00                	push   0x0
 804ec3b:	6a 00                	push   0x0
 804ec3d:	6a 02                	push   0x2
 804ec3f:	6a 2b                	push   0x2b
 804ec41:	6a 00                	push   0x0
 804ec43:	6a 02                	push   0x2
 804ec45:	6a 28                	push   0x28
 804ec47:	6a 00                	push   0x0
 804ec49:	50                   	push   eax

0804ec4a <_________macro_expr_ch_end>:
 804ec4a:	e9 70 01 00 00       	jmp    804edbf <_________macro_expr_contend>

0804ec4f <_________macro_expr_continuing>:
 804ec4f:	80 fd 00             	cmp    ch,0x0
 804ec52:	0f 85 47 01 00 00    	jne    804ed9f <_________macro_expr_same_n0>
 804ec58:	81 fe 00 01 00 00    	cmp    esi,0x100
 804ec5e:	73 67                	jae    804ecc7 <_________macro_expr_oper_ge256>
 804ec60:	b8 00 00 00 00       	mov    eax,0x0
 804ec65:	88 c8                	mov    al,cl
 804ec67:	52                   	push   edx
 804ec68:	ba 00 01 00 00       	mov    edx,0x100
 804ec6d:	f7 e2                	mul    edx
 804ec6f:	5a                   	pop    edx
 804ec70:	01 c6                	add    esi,eax
 804ec72:	52                   	push   edx
 804ec73:	53                   	push   ebx
 804ec74:	55                   	push   ebp
 804ec75:	ba 00 00 00 00       	mov    edx,0x0
 804ec7a:	bb 00 00 00 00       	mov    ebx,0x0

0804ec7f <_________macro_expr_oper_1_for_begin>:
 804ec7f:	3b 1d 0e e4 0c 08    	cmp    ebx,DWORD PTR ds:0x80ce40e
 804ec85:	73 16                	jae    804ec9d <_________macro_expr_oper_1_for_end>
 804ec87:	8d 2c 9d b2 e3 0c 08 	lea    ebp,[ebx*4+0x80ce3b2]
 804ec8e:	8b 6d 00             	mov    ebp,DWORD PTR [ebp+0x0]
 804ec91:	39 f5                	cmp    ebp,esi
 804ec93:	75 05                	jne    804ec9a <_________macro_expr_oper_1_nc>
 804ec95:	ba 01 00 00 00       	mov    edx,0x1

0804ec9a <_________macro_expr_oper_1_nc>:
 804ec9a:	43                   	inc    ebx
 804ec9b:	eb e2                	jmp    804ec7f <_________macro_expr_oper_1_for_begin>

0804ec9d <_________macro_expr_oper_1_for_end>:
 804ec9d:	83 fa 00             	cmp    edx,0x0
 804eca0:	75 1d                	jne    804ecbf <_________macro_expr_oper_1_f>
 804eca2:	29 c6                	sub    esi,eax
 804eca4:	5d                   	pop    ebp
 804eca5:	5b                   	pop    ebx
 804eca6:	5a                   	pop    edx
 804eca7:	58                   	pop    eax
 804eca8:	6a 02                	push   0x2
 804ecaa:	56                   	push   esi
 804ecab:	6a 00                	push   0x0
 804ecad:	50                   	push   eax
 804ecae:	52                   	push   edx
 804ecaf:	53                   	push   ebx
 804ecb0:	55                   	push   ebp
 804ecb1:	be 00 00 00 00       	mov    esi,0x0
 804ecb6:	b8 00 00 00 00       	mov    eax,0x0
 804ecbb:	88 c8                	mov    al,cl
 804ecbd:	89 c6                	mov    esi,eax

0804ecbf <_________macro_expr_oper_1_f>:
 804ecbf:	5d                   	pop    ebp
 804ecc0:	5b                   	pop    ebx
 804ecc1:	5a                   	pop    edx
 804ecc2:	e9 d6 00 00 00       	jmp    804ed9d <_________macro_expr_oper_end>

0804ecc7 <_________macro_expr_oper_ge256>:
 804ecc7:	81 fe 00 00 01 00    	cmp    esi,0x10000
 804eccd:	73 64                	jae    804ed33 <_________macro_expr_oper_ge256_256>
 804eccf:	b8 00 00 00 00       	mov    eax,0x0
 804ecd4:	88 c8                	mov    al,cl
 804ecd6:	52                   	push   edx
 804ecd7:	ba 00 00 01 00       	mov    edx,0x10000
 804ecdc:	f7 e2                	mul    edx
 804ecde:	5a                   	pop    edx
 804ecdf:	01 c6                	add    esi,eax
 804ece1:	52                   	push   edx
 804ece2:	53                   	push   ebx
 804ece3:	55                   	push   ebp
 804ece4:	ba 00 00 00 00       	mov    edx,0x0
 804ece9:	bb 00 00 00 00       	mov    ebx,0x0

0804ecee <_________macro_expr_oper_2_for_begin>:
 804ecee:	3b 1d 0e e4 0c 08    	cmp    ebx,DWORD PTR ds:0x80ce40e
 804ecf4:	73 16                	jae    804ed0c <_________macro_expr_oper_2_for_end>
 804ecf6:	8d 2c 9d b2 e3 0c 08 	lea    ebp,[ebx*4+0x80ce3b2]
 804ecfd:	8b 6d 00             	mov    ebp,DWORD PTR [ebp+0x0]
 804ed00:	39 f5                	cmp    ebp,esi
 804ed02:	75 05                	jne    804ed09 <_________macro_expr_oper_2_nc>
 804ed04:	ba 01 00 00 00       	mov    edx,0x1

0804ed09 <_________macro_expr_oper_2_nc>:
 804ed09:	43                   	inc    ebx
 804ed0a:	eb e2                	jmp    804ecee <_________macro_expr_oper_2_for_begin>

0804ed0c <_________macro_expr_oper_2_for_end>:
 804ed0c:	83 fa 00             	cmp    edx,0x0
 804ed0f:	75 1d                	jne    804ed2e <_________macro_expr_oper_2_f>
 804ed11:	29 c6                	sub    esi,eax
 804ed13:	5d                   	pop    ebp
 804ed14:	5b                   	pop    ebx
 804ed15:	5a                   	pop    edx
 804ed16:	58                   	pop    eax
 804ed17:	6a 02                	push   0x2
 804ed19:	56                   	push   esi
 804ed1a:	6a 00                	push   0x0
 804ed1c:	50                   	push   eax
 804ed1d:	52                   	push   edx
 804ed1e:	53                   	push   ebx
 804ed1f:	55                   	push   ebp
 804ed20:	be 00 00 00 00       	mov    esi,0x0
 804ed25:	b8 00 00 00 00       	mov    eax,0x0
 804ed2a:	88 c8                	mov    al,cl
 804ed2c:	89 c6                	mov    esi,eax

0804ed2e <_________macro_expr_oper_2_f>:
 804ed2e:	5d                   	pop    ebp
 804ed2f:	5b                   	pop    ebx
 804ed30:	5a                   	pop    edx
 804ed31:	eb 6a                	jmp    804ed9d <_________macro_expr_oper_end>

0804ed33 <_________macro_expr_oper_ge256_256>:
 804ed33:	81 fe 00 00 00 01    	cmp    esi,0x1000000
 804ed39:	73 62                	jae    804ed9d <_________macro_expr_oper_end>
 804ed3b:	b8 00 00 00 00       	mov    eax,0x0
 804ed40:	88 c8                	mov    al,cl
 804ed42:	52                   	push   edx
 804ed43:	ba 00 00 00 01       	mov    edx,0x1000000
 804ed48:	f7 e2                	mul    edx
 804ed4a:	5a                   	pop    edx
 804ed4b:	01 c6                	add    esi,eax
 804ed4d:	52                   	push   edx
 804ed4e:	53                   	push   ebx
 804ed4f:	55                   	push   ebp
 804ed50:	ba 00 00 00 00       	mov    edx,0x0
 804ed55:	bb 00 00 00 00       	mov    ebx,0x0

0804ed5a <_________macro_expr_oper_3_for_begin>:
 804ed5a:	3b 1d 0e e4 0c 08    	cmp    ebx,DWORD PTR ds:0x80ce40e
 804ed60:	73 16                	jae    804ed78 <_________macro_expr_oper_3_for_end>
 804ed62:	8d 2c 9d b2 e3 0c 08 	lea    ebp,[ebx*4+0x80ce3b2]
 804ed69:	8b 6d 00             	mov    ebp,DWORD PTR [ebp+0x0]
 804ed6c:	39 f5                	cmp    ebp,esi
 804ed6e:	75 05                	jne    804ed75 <_________macro_expr_oper_3_nc>
 804ed70:	ba 01 00 00 00       	mov    edx,0x1

0804ed75 <_________macro_expr_oper_3_nc>:
 804ed75:	43                   	inc    ebx
 804ed76:	eb e2                	jmp    804ed5a <_________macro_expr_oper_3_for_begin>

0804ed78 <_________macro_expr_oper_3_for_end>:
 804ed78:	83 fa 00             	cmp    edx,0x0
 804ed7b:	75 1d                	jne    804ed9a <_________macro_expr_oper_3_f>
 804ed7d:	29 c6                	sub    esi,eax
 804ed7f:	5d                   	pop    ebp
 804ed80:	5b                   	pop    ebx
 804ed81:	5a                   	pop    edx
 804ed82:	58                   	pop    eax
 804ed83:	6a 02                	push   0x2
 804ed85:	56                   	push   esi
 804ed86:	6a 00                	push   0x0
 804ed88:	50                   	push   eax
 804ed89:	52                   	push   edx
 804ed8a:	53                   	push   ebx
 804ed8b:	55                   	push   ebp
 804ed8c:	be 00 00 00 00       	mov    esi,0x0
 804ed91:	b8 00 00 00 00       	mov    eax,0x0
 804ed96:	88 c8                	mov    al,cl
 804ed98:	89 c6                	mov    esi,eax

0804ed9a <_________macro_expr_oper_3_f>:
 804ed9a:	5d                   	pop    ebp
 804ed9b:	5b                   	pop    ebx
 804ed9c:	5a                   	pop    edx

0804ed9d <_________macro_expr_oper_end>:
 804ed9d:	eb 20                	jmp    804edbf <_________macro_expr_contend>

0804ed9f <_________macro_expr_same_n0>:
 804ed9f:	80 fd 01             	cmp    ch,0x1
 804eda2:	75 1b                	jne    804edbf <_________macro_expr_contend>
 804eda4:	b8 00 00 00 00       	mov    eax,0x0
 804eda9:	88 c8                	mov    al,cl
 804edab:	83 e8 30             	sub    eax,0x30
 804edae:	50                   	push   eax
 804edaf:	52                   	push   edx
 804edb0:	89 f0                	mov    eax,esi
 804edb2:	ba 0a 00 00 00       	mov    edx,0xa
 804edb7:	f7 e2                	mul    edx
 804edb9:	89 c6                	mov    esi,eax
 804edbb:	5a                   	pop    edx
 804edbc:	58                   	pop    eax
 804edbd:	01 c6                	add    esi,eax

0804edbf <_________macro_expr_contend>:
 804edbf:	88 ee                	mov    dh,ch
 804edc1:	43                   	inc    ebx
 804edc2:	e9 56 fd ff ff       	jmp    804eb1d <_________macro_expr_main_loop_begin>

0804edc7 <_________macro_expr_main_loop_end>:
 804edc7:	5b                   	pop    ebx
 804edc8:	89 e0                	mov    eax,esp
 804edca:	89 c2                	mov    edx,eax
 804edcc:	89 c6                	mov    esi,eax
 804edce:	89 df                	mov    edi,ebx

0804edd0 <_________macro_expr_swap_begin>:
 804edd0:	39 d8                	cmp    eax,ebx
 804edd2:	73 12                	jae    804ede6 <_________macro_expr_swap_end>
 804edd4:	8b 08                	mov    ecx,DWORD PTR [eax]
 804edd6:	8b 6b fc             	mov    ebp,DWORD PTR [ebx-0x4]
 804edd9:	89 28                	mov    DWORD PTR [eax],ebp
 804eddb:	89 4b fc             	mov    DWORD PTR [ebx-0x4],ecx
 804edde:	83 c0 04             	add    eax,0x4
 804ede1:	83 eb 04             	sub    ebx,0x4
 804ede4:	eb ea                	jmp    804edd0 <_________macro_expr_swap_begin>

0804ede6 <_________macro_expr_swap_end>:
 804ede6:	89 f0                	mov    eax,esi
 804ede8:	89 fb                	mov    ebx,edi
 804edea:	68 f9 ed 04 08       	push   0x804edf9
 804edef:	68 2f 05 00 00       	push   0x52f
 804edf4:	e9 87 92 ff ff       	jmp    8048080 <macro_pr_jmp>

0804edf9 <..@3211._1>:
 804edf9:	50                   	push   eax
 804edfa:	53                   	push   ebx
 804edfb:	53                   	push   ebx
 804edfc:	6a 00                	push   0x0
 804edfe:	e8 92 f0 ff ff       	call   804de95 <macro_bops>
 804ee03:	83 c4 10             	add    esp,0x10
 804ee06:	89 dc                	mov    esp,ebx
 804ee08:	61                   	popa   
 804ee09:	83 c4 08             	add    esp,0x8
 804ee0c:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804ee10 <macro_set_jmp>:
 804ee10:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804ee17:	00 00 00 
 804ee1a:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804ee21:	00 00 00 
 804ee24:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804ee2b:	00 00 00 
 804ee2e:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804ee35:	00 00 00 
 804ee38:	60                   	pusha  
 804ee39:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804ee3e:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804ee44:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804ee4a:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804ee50:	be 00 00 00 00       	mov    esi,0x0
 804ee55:	bf 00 00 00 00       	mov    edi,0x0
 804ee5a:	bd 00 00 00 00       	mov    ebp,0x0
 804ee5f:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804ee66:	00 00 00 
 804ee69:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804ee70:	00 00 00 
 804ee73:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804ee7a:	00 00 00 
 804ee7d:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804ee84:	00 00 00 
 804ee87:	60                   	pusha  
 804ee88:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804ee8d:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804ee93:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804ee99:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804ee9f:	be 00 00 00 00       	mov    esi,0x0
 804eea4:	bf 00 00 00 00       	mov    edi,0x0
 804eea9:	bd 00 00 00 00       	mov    ebp,0x0
 804eeae:	89 e0                	mov    eax,esp
 804eeb0:	c7 05 02 29 05 08 00 	mov    DWORD PTR ds:0x8052902,0x0
 804eeb7:	00 00 00 
 804eeba:	c7 05 06 29 05 08 00 	mov    DWORD PTR ds:0x8052906,0x0
 804eec1:	00 00 00 
 804eec4:	c7 05 0a 29 05 08 00 	mov    DWORD PTR ds:0x805290a,0x0
 804eecb:	00 00 00 
 804eece:	c7 05 0e 29 05 08 00 	mov    DWORD PTR ds:0x805290e,0x0
 804eed5:	00 00 00 
 804eed8:	50                   	push   eax
 804eed9:	8f 05 02 29 05 08    	pop    DWORD PTR ds:0x8052902
 804eedf:	60                   	pusha  
 804eee0:	a1 02 29 05 08       	mov    eax,ds:0x8052902
 804eee5:	8b 1d 06 29 05 08    	mov    ebx,DWORD PTR ds:0x8052906
 804eeeb:	8b 0d 0a 29 05 08    	mov    ecx,DWORD PTR ds:0x805290a
 804eef1:	8b 15 0e 29 05 08    	mov    edx,DWORD PTR ds:0x805290e
 804eef7:	be 00 00 00 00       	mov    esi,0x0
 804eefc:	bf 00 00 00 00       	mov    edi,0x0
 804ef01:	bd 00 00 00 00       	mov    ebp,0x0
 804ef06:	29 e0                	sub    eax,esp
 804ef08:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804ef0d:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804ef13:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804ef19:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804ef1f:	61                   	popa   
 804ef20:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804ef26:	58                   	pop    eax
 804ef27:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804ef2c:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804ef32:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804ef38:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804ef3e:	61                   	popa   
 804ef3f:	ff 35 02 29 05 08    	push   DWORD PTR ds:0x8052902
 804ef45:	58                   	pop    eax
 804ef46:	01 e0                	add    eax,esp
 804ef48:	8b 08                	mov    ecx,DWORD PTR [eax]
 804ef4a:	83 c0 04             	add    eax,0x4
 804ef4d:	89 c3                	mov    ebx,eax
 804ef4f:	01 cb                	add    ebx,ecx
 804ef51:	50                   	push   eax
 804ef52:	53                   	push   ebx
 804ef53:	53                   	push   ebx
 804ef54:	6a 00                	push   0x0
 804ef56:	e8 3a ef ff ff       	call   804de95 <macro_bops>
 804ef5b:	83 c4 10             	add    esp,0x10
 804ef5e:	ff 70 04             	push   DWORD PTR [eax+0x4]
 804ef61:	8f 43 fc             	pop    DWORD PTR [ebx-0x4]
 804ef64:	a3 02 29 05 08       	mov    ds:0x8052902,eax
 804ef69:	89 1d 06 29 05 08    	mov    DWORD PTR ds:0x8052906,ebx
 804ef6f:	89 0d 0a 29 05 08    	mov    DWORD PTR ds:0x805290a,ecx
 804ef75:	89 15 0e 29 05 08    	mov    DWORD PTR ds:0x805290e,edx
 804ef7b:	61                   	popa   
 804ef7c:	03 24 24             	add    esp,DWORD PTR [esp]
 804ef7f:	83 c4 08             	add    esp,0x8
 804ef82:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0804ef86 <macro_regout>:
 804ef86:	e8 53 0d 00 00       	call   804fcde <__best_sput+0x6>

0804ef8b <..@3260._1>:
 804ef8b:	65 61                	gs popa 
 804ef8d:	78                   	.byte 0x78

0804ef8e <..@3260._2>:
 804ef8e:	e8 4d 0d 00 00       	call   804fce0 <__best_sput+0x8>

0804ef93 <..@3261._1>:
 804ef93:	20                   	.byte 0x20
 804ef94:	3d                   	.byte 0x3d
 804ef95:	3d                   	.byte 0x3d
 804ef96:	20                   	.byte 0x20

0804ef97 <..@3261._2>:
 804ef97:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804ef9c:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804efa1:	b0 1b                	mov    al,0x1b
 804efa3:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804efa7:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804efac:	83 ec 02             	sub    esp,0x2
 804efaf:	e8 58 0c 00 00       	call   804fc0c <__best_cput+0x2>
 804efb4:	e8 27 0d 00 00       	call   804fce0 <__best_sput+0x8>

0804efb9 <..@3266._1>:
 804efb9:	5b                   	pop    ebx
 804efba:	33 32                	xor    esi,DWORD PTR [edx]
 804efbc:	6d                   	ins    DWORD PTR es:[edi],dx

0804efbd <..@3266._2>:
 804efbd:	50                   	push   eax
 804efbe:	e8 4f 08 00 00       	call   804f812 <__best_dsput+0x2>
 804efc3:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804efc8:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804efcd:	b0 1b                	mov    al,0x1b
 804efcf:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804efd3:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804efd8:	83 ec 02             	sub    esp,0x2
 804efdb:	e8 2c 0c 00 00       	call   804fc0c <__best_cput+0x2>
 804efe0:	e8 f9 0c 00 00       	call   804fcde <__best_sput+0x6>

0804efe5 <..@3273._1>:
 804efe5:	5b                   	pop    ebx
 804efe6:	30                   	.byte 0x30
 804efe7:	6d                   	ins    DWORD PTR es:[edi],dx

0804efe8 <..@3273._2>:
 804efe8:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804efed:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804eff2:	b0 09                	mov    al,0x9
 804eff4:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804eff8:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804effd:	83 ec 02             	sub    esp,0x2
 804f000:	e8 07 0c 00 00       	call   804fc0c <__best_cput+0x2>
 804f005:	e8 d0 0c 00 00       	call   804fcda <__best_sput+0x2>

0804f00a <..@3278._1>:
 804f00a:	20                   	.byte 0x20

0804f00b <..@3278._2>:
 804f00b:	e8 ce 0c 00 00       	call   804fcde <__best_sput+0x6>

0804f010 <..@3280._1>:
 804f010:	65                   	gs
 804f011:	62                   	.byte 0x62
 804f012:	78                   	.byte 0x78

0804f013 <..@3280._2>:
 804f013:	e8 c8 0c 00 00       	call   804fce0 <__best_sput+0x8>

0804f018 <..@3281._1>:
 804f018:	20                   	.byte 0x20
 804f019:	3d                   	.byte 0x3d
 804f01a:	3d                   	.byte 0x3d
 804f01b:	20                   	.byte 0x20

0804f01c <..@3281._2>:
 804f01c:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f021:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f026:	b0 1b                	mov    al,0x1b
 804f028:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f02c:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f031:	83 ec 02             	sub    esp,0x2
 804f034:	e8 d3 0b 00 00       	call   804fc0c <__best_cput+0x2>
 804f039:	e8 a2 0c 00 00       	call   804fce0 <__best_sput+0x8>

0804f03e <..@3286._1>:
 804f03e:	5b                   	pop    ebx
 804f03f:	33 32                	xor    esi,DWORD PTR [edx]
 804f041:	6d                   	ins    DWORD PTR es:[edi],dx

0804f042 <..@3286._2>:
 804f042:	53                   	push   ebx
 804f043:	e8 ca 07 00 00       	call   804f812 <__best_dsput+0x2>
 804f048:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f04d:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f052:	b0 1b                	mov    al,0x1b
 804f054:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f058:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f05d:	83 ec 02             	sub    esp,0x2
 804f060:	e8 a7 0b 00 00       	call   804fc0c <__best_cput+0x2>
 804f065:	e8 74 0c 00 00       	call   804fcde <__best_sput+0x6>

0804f06a <..@3293._1>:
 804f06a:	5b                   	pop    ebx
 804f06b:	30                   	.byte 0x30
 804f06c:	6d                   	ins    DWORD PTR es:[edi],dx

0804f06d <..@3293._2>:
 804f06d:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f072:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f077:	b0 09                	mov    al,0x9
 804f079:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f07d:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f082:	83 ec 02             	sub    esp,0x2
 804f085:	e8 82 0b 00 00       	call   804fc0c <__best_cput+0x2>
 804f08a:	e8 4b 0c 00 00       	call   804fcda <__best_sput+0x2>

0804f08f <..@3298._1>:
 804f08f:	20                   	.byte 0x20

0804f090 <..@3298._2>:
 804f090:	e8 49 0c 00 00       	call   804fcde <__best_sput+0x6>

0804f095 <..@3300._1>:
 804f095:	65                   	gs
 804f096:	63                   	.byte 0x63
 804f097:	78                   	.byte 0x78

0804f098 <..@3300._2>:
 804f098:	e8 43 0c 00 00       	call   804fce0 <__best_sput+0x8>

0804f09d <..@3301._1>:
 804f09d:	20                   	.byte 0x20
 804f09e:	3d                   	.byte 0x3d
 804f09f:	3d                   	.byte 0x3d
 804f0a0:	20                   	.byte 0x20

0804f0a1 <..@3301._2>:
 804f0a1:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f0a6:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f0ab:	b0 1b                	mov    al,0x1b
 804f0ad:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f0b1:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f0b6:	83 ec 02             	sub    esp,0x2
 804f0b9:	e8 4e 0b 00 00       	call   804fc0c <__best_cput+0x2>
 804f0be:	e8 1d 0c 00 00       	call   804fce0 <__best_sput+0x8>

0804f0c3 <..@3306._1>:
 804f0c3:	5b                   	pop    ebx
 804f0c4:	33 32                	xor    esi,DWORD PTR [edx]
 804f0c6:	6d                   	ins    DWORD PTR es:[edi],dx

0804f0c7 <..@3306._2>:
 804f0c7:	51                   	push   ecx
 804f0c8:	e8 45 07 00 00       	call   804f812 <__best_dsput+0x2>
 804f0cd:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f0d2:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f0d7:	b0 1b                	mov    al,0x1b
 804f0d9:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f0dd:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f0e2:	83 ec 02             	sub    esp,0x2
 804f0e5:	e8 22 0b 00 00       	call   804fc0c <__best_cput+0x2>
 804f0ea:	e8 ef 0b 00 00       	call   804fcde <__best_sput+0x6>

0804f0ef <..@3313._1>:
 804f0ef:	5b                   	pop    ebx
 804f0f0:	30                   	.byte 0x30
 804f0f1:	6d                   	ins    DWORD PTR es:[edi],dx

0804f0f2 <..@3313._2>:
 804f0f2:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f0f7:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f0fc:	b0 09                	mov    al,0x9
 804f0fe:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f102:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f107:	83 ec 02             	sub    esp,0x2
 804f10a:	e8 fd 0a 00 00       	call   804fc0c <__best_cput+0x2>
 804f10f:	e8 c6 0b 00 00       	call   804fcda <__best_sput+0x2>

0804f114 <..@3318._1>:
 804f114:	20                   	.byte 0x20

0804f115 <..@3318._2>:
 804f115:	e8 c4 0b 00 00       	call   804fcde <__best_sput+0x6>

0804f11a <..@3320._1>:
 804f11a:	65                   	gs
 804f11b:	64                   	fs
 804f11c:	78                   	.byte 0x78

0804f11d <..@3320._2>:
 804f11d:	e8 be 0b 00 00       	call   804fce0 <__best_sput+0x8>

0804f122 <..@3321._1>:
 804f122:	20                   	.byte 0x20
 804f123:	3d                   	.byte 0x3d
 804f124:	3d                   	.byte 0x3d
 804f125:	20                   	.byte 0x20

0804f126 <..@3321._2>:
 804f126:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f12b:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f130:	b0 1b                	mov    al,0x1b
 804f132:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f136:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f13b:	83 ec 02             	sub    esp,0x2
 804f13e:	e8 c9 0a 00 00       	call   804fc0c <__best_cput+0x2>
 804f143:	e8 98 0b 00 00       	call   804fce0 <__best_sput+0x8>

0804f148 <..@3326._1>:
 804f148:	5b                   	pop    ebx
 804f149:	33 32                	xor    esi,DWORD PTR [edx]
 804f14b:	6d                   	ins    DWORD PTR es:[edi],dx

0804f14c <..@3326._2>:
 804f14c:	52                   	push   edx
 804f14d:	e8 c0 06 00 00       	call   804f812 <__best_dsput+0x2>
 804f152:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f157:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f15c:	b0 1b                	mov    al,0x1b
 804f15e:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f162:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f167:	83 ec 02             	sub    esp,0x2
 804f16a:	e8 9d 0a 00 00       	call   804fc0c <__best_cput+0x2>
 804f16f:	e8 6a 0b 00 00       	call   804fcde <__best_sput+0x6>

0804f174 <..@3333._1>:
 804f174:	5b                   	pop    ebx
 804f175:	30                   	.byte 0x30
 804f176:	6d                   	ins    DWORD PTR es:[edi],dx

0804f177 <..@3333._2>:
 804f177:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f17c:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f181:	b0 09                	mov    al,0x9
 804f183:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f187:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f18c:	83 ec 02             	sub    esp,0x2
 804f18f:	e8 78 0a 00 00       	call   804fc0c <__best_cput+0x2>
 804f194:	e8 41 0b 00 00       	call   804fcda <__best_sput+0x2>

0804f199 <..@3338._1>:
 804f199:	20                   	.byte 0x20

0804f19a <..@3338._2>:
 804f19a:	e8 3f 0b 00 00       	call   804fcde <__best_sput+0x6>

0804f19f <..@3340._1>:
 804f19f:	65 73 69             	gs jae 804f20b <..@3353._2+0xf>

0804f1a2 <..@3340._2>:
 804f1a2:	e8 39 0b 00 00       	call   804fce0 <__best_sput+0x8>

0804f1a7 <..@3341._1>:
 804f1a7:	20                   	.byte 0x20
 804f1a8:	3d                   	.byte 0x3d
 804f1a9:	3d                   	.byte 0x3d
 804f1aa:	20                   	.byte 0x20

0804f1ab <..@3341._2>:
 804f1ab:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f1b0:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f1b5:	b0 1b                	mov    al,0x1b
 804f1b7:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f1bb:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f1c0:	83 ec 02             	sub    esp,0x2
 804f1c3:	e8 44 0a 00 00       	call   804fc0c <__best_cput+0x2>
 804f1c8:	e8 13 0b 00 00       	call   804fce0 <__best_sput+0x8>

0804f1cd <..@3346._1>:
 804f1cd:	5b                   	pop    ebx
 804f1ce:	33 32                	xor    esi,DWORD PTR [edx]
 804f1d0:	6d                   	ins    DWORD PTR es:[edi],dx

0804f1d1 <..@3346._2>:
 804f1d1:	56                   	push   esi
 804f1d2:	e8 3b 06 00 00       	call   804f812 <__best_dsput+0x2>
 804f1d7:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f1dc:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f1e1:	b0 1b                	mov    al,0x1b
 804f1e3:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f1e7:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f1ec:	83 ec 02             	sub    esp,0x2
 804f1ef:	e8 18 0a 00 00       	call   804fc0c <__best_cput+0x2>
 804f1f4:	e8 e5 0a 00 00       	call   804fcde <__best_sput+0x6>

0804f1f9 <..@3353._1>:
 804f1f9:	5b                   	pop    ebx
 804f1fa:	30                   	.byte 0x30
 804f1fb:	6d                   	ins    DWORD PTR es:[edi],dx

0804f1fc <..@3353._2>:
 804f1fc:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f201:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f206:	b0 09                	mov    al,0x9
 804f208:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f20c:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f211:	83 ec 02             	sub    esp,0x2
 804f214:	e8 f3 09 00 00       	call   804fc0c <__best_cput+0x2>
 804f219:	e8 bc 0a 00 00       	call   804fcda <__best_sput+0x2>

0804f21e <..@3358._1>:
 804f21e:	20                   	.byte 0x20

0804f21f <..@3358._2>:
 804f21f:	e8 ba 0a 00 00       	call   804fcde <__best_sput+0x6>

0804f224 <..@3360._1>:
 804f224:	65                   	gs
 804f225:	64                   	fs
 804f226:	69                   	.byte 0x69

0804f227 <..@3360._2>:
 804f227:	e8 b4 0a 00 00       	call   804fce0 <__best_sput+0x8>

0804f22c <..@3361._1>:
 804f22c:	20                   	.byte 0x20
 804f22d:	3d                   	.byte 0x3d
 804f22e:	3d                   	.byte 0x3d
 804f22f:	20                   	.byte 0x20

0804f230 <..@3361._2>:
 804f230:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f235:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f23a:	b0 1b                	mov    al,0x1b
 804f23c:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f240:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f245:	83 ec 02             	sub    esp,0x2
 804f248:	e8 bf 09 00 00       	call   804fc0c <__best_cput+0x2>
 804f24d:	e8 8e 0a 00 00       	call   804fce0 <__best_sput+0x8>

0804f252 <..@3366._1>:
 804f252:	5b                   	pop    ebx
 804f253:	33 32                	xor    esi,DWORD PTR [edx]
 804f255:	6d                   	ins    DWORD PTR es:[edi],dx

0804f256 <..@3366._2>:
 804f256:	57                   	push   edi
 804f257:	e8 b6 05 00 00       	call   804f812 <__best_dsput+0x2>
 804f25c:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f261:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f266:	b0 1b                	mov    al,0x1b
 804f268:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f26c:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f271:	83 ec 02             	sub    esp,0x2
 804f274:	e8 93 09 00 00       	call   804fc0c <__best_cput+0x2>
 804f279:	e8 60 0a 00 00       	call   804fcde <__best_sput+0x6>

0804f27e <..@3373._1>:
 804f27e:	5b                   	pop    ebx
 804f27f:	30                   	.byte 0x30
 804f280:	6d                   	ins    DWORD PTR es:[edi],dx

0804f281 <..@3373._2>:
 804f281:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f286:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f28b:	b0 09                	mov    al,0x9
 804f28d:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f291:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f296:	83 ec 02             	sub    esp,0x2
 804f299:	e8 6e 09 00 00       	call   804fc0c <__best_cput+0x2>
 804f29e:	e8 37 0a 00 00       	call   804fcda <__best_sput+0x2>

0804f2a3 <..@3378._1>:
 804f2a3:	20                   	.byte 0x20

0804f2a4 <..@3378._2>:
 804f2a4:	e8 35 0a 00 00       	call   804fcde <__best_sput+0x6>

0804f2a9 <..@3380._1>:
 804f2a9:	65                   	gs
 804f2aa:	62                   	.byte 0x62
 804f2ab:	70                   	.byte 0x70

0804f2ac <..@3380._2>:
 804f2ac:	e8 2f 0a 00 00       	call   804fce0 <__best_sput+0x8>

0804f2b1 <..@3381._1>:
 804f2b1:	20                   	.byte 0x20
 804f2b2:	3d                   	.byte 0x3d
 804f2b3:	3d                   	.byte 0x3d
 804f2b4:	20                   	.byte 0x20

0804f2b5 <..@3381._2>:
 804f2b5:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f2ba:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f2bf:	b0 1b                	mov    al,0x1b
 804f2c1:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f2c5:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f2ca:	83 ec 02             	sub    esp,0x2
 804f2cd:	e8 3a 09 00 00       	call   804fc0c <__best_cput+0x2>
 804f2d2:	e8 09 0a 00 00       	call   804fce0 <__best_sput+0x8>

0804f2d7 <..@3386._1>:
 804f2d7:	5b                   	pop    ebx
 804f2d8:	33 32                	xor    esi,DWORD PTR [edx]
 804f2da:	6d                   	ins    DWORD PTR es:[edi],dx

0804f2db <..@3386._2>:
 804f2db:	55                   	push   ebp
 804f2dc:	e8 31 05 00 00       	call   804f812 <__best_dsput+0x2>
 804f2e1:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f2e6:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f2eb:	b0 1b                	mov    al,0x1b
 804f2ed:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f2f1:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f2f6:	83 ec 02             	sub    esp,0x2
 804f2f9:	e8 0e 09 00 00       	call   804fc0c <__best_cput+0x2>
 804f2fe:	e8 db 09 00 00       	call   804fcde <__best_sput+0x6>

0804f303 <..@3393._1>:
 804f303:	5b                   	pop    ebx
 804f304:	30                   	.byte 0x30
 804f305:	6d                   	ins    DWORD PTR es:[edi],dx

0804f306 <..@3393._2>:
 804f306:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f30b:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f310:	b0 09                	mov    al,0x9
 804f312:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f316:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f31b:	83 ec 02             	sub    esp,0x2
 804f31e:	e8 e9 08 00 00       	call   804fc0c <__best_cput+0x2>
 804f323:	e8 b2 09 00 00       	call   804fcda <__best_sput+0x2>

0804f328 <..@3398._1>:
 804f328:	20                   	.byte 0x20

0804f329 <..@3398._2>:
 804f329:	e8 b0 09 00 00       	call   804fcde <__best_sput+0x6>

0804f32e <..@3400._1>:
 804f32e:	65 73 70             	gs jae 804f3a1 <..@3413._1+0x1>

0804f331 <..@3400._2>:
 804f331:	e8 aa 09 00 00       	call   804fce0 <__best_sput+0x8>

0804f336 <..@3401._1>:
 804f336:	20                   	.byte 0x20
 804f337:	3d                   	.byte 0x3d
 804f338:	3d                   	.byte 0x3d
 804f339:	20                   	.byte 0x20

0804f33a <..@3401._2>:
 804f33a:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f33f:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f344:	b0 1b                	mov    al,0x1b
 804f346:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f34a:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f34f:	83 ec 02             	sub    esp,0x2
 804f352:	e8 b5 08 00 00       	call   804fc0c <__best_cput+0x2>
 804f357:	e8 84 09 00 00       	call   804fce0 <__best_sput+0x8>

0804f35c <..@3406._1>:
 804f35c:	5b                   	pop    ebx
 804f35d:	33 32                	xor    esi,DWORD PTR [edx]
 804f35f:	6d                   	ins    DWORD PTR es:[edi],dx

0804f360 <..@3406._2>:
 804f360:	29 24 24             	sub    DWORD PTR [esp],esp
 804f363:	f7 1c 24             	neg    DWORD PTR [esp]
 804f366:	87 04 24             	xchg   DWORD PTR [esp],eax
 804f369:	83 c0 0c             	add    eax,0xc
 804f36c:	50                   	push   eax
 804f36d:	e8 a0 04 00 00       	call   804f812 <__best_dsput+0x2>
 804f372:	83 e8 0c             	sub    eax,0xc
 804f375:	87 04 24             	xchg   DWORD PTR [esp],eax
 804f378:	f7 1c 24             	neg    DWORD PTR [esp]
 804f37b:	01 24 24             	add    DWORD PTR [esp],esp
 804f37e:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f383:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f388:	b0 1b                	mov    al,0x1b
 804f38a:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f38e:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f393:	83 ec 02             	sub    esp,0x2
 804f396:	e8 71 08 00 00       	call   804fc0c <__best_cput+0x2>
 804f39b:	e8 3e 09 00 00       	call   804fcde <__best_sput+0x6>

0804f3a0 <..@3413._1>:
 804f3a0:	5b                   	pop    ebx
 804f3a1:	30                   	.byte 0x30
 804f3a2:	6d                   	ins    DWORD PTR es:[edi],dx

0804f3a3 <..@3413._2>:
 804f3a3:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f3a8:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f3ad:	b0 09                	mov    al,0x9
 804f3af:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f3b3:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f3b8:	83 ec 02             	sub    esp,0x2
 804f3bb:	e8 4c 08 00 00       	call   804fc0c <__best_cput+0x2>
 804f3c0:	e8 23 09 00 00       	call   804fce8 <__best_sput+0x10>

0804f3c5 <..@3418._1>:
 804f3c5:	20 6c 69 6e          	and    BYTE PTR [ecx+ebp*2+0x6e],ch
 804f3c9:	65                   	gs
 804f3ca:	20                   	.byte 0x20
 804f3cb:	3d                   	.byte 0x3d
 804f3cc:	20                   	.byte 0x20

0804f3cd <..@3418._2>:
 804f3cd:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f3d2:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f3d7:	b0 1b                	mov    al,0x1b
 804f3d9:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f3dd:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f3e2:	83 ec 02             	sub    esp,0x2
 804f3e5:	e8 22 08 00 00       	call   804fc0c <__best_cput+0x2>
 804f3ea:	e8 f1 08 00 00       	call   804fce0 <__best_sput+0x8>

0804f3ef <..@3423._1>:
 804f3ef:	5b                   	pop    ebx
 804f3f0:	33 32                	xor    esi,DWORD PTR [edx]
 804f3f2:	6d                   	ins    DWORD PTR es:[edi],dx

0804f3f3 <..@3423._2>:
 804f3f3:	87 44 24 04          	xchg   DWORD PTR [esp+0x4],eax
 804f3f7:	50                   	push   eax
 804f3f8:	e8 15 04 00 00       	call   804f812 <__best_dsput+0x2>
 804f3fd:	87 44 24 04          	xchg   DWORD PTR [esp+0x4],eax
 804f401:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f406:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f40b:	b0 1b                	mov    al,0x1b
 804f40d:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f411:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f416:	83 ec 02             	sub    esp,0x2
 804f419:	e8 ee 07 00 00       	call   804fc0c <__best_cput+0x2>
 804f41e:	e8 bb 08 00 00       	call   804fcde <__best_sput+0x6>

0804f423 <..@3430._1>:
 804f423:	5b                   	pop    ebx
 804f424:	30                   	.byte 0x30
 804f425:	6d                   	ins    DWORD PTR es:[edi],dx

0804f426 <..@3430._2>:
 804f426:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f42b:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f430:	b0 0a                	mov    al,0xa
 804f432:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f436:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f43b:	83 ec 02             	sub    esp,0x2
 804f43e:	e8 c9 07 00 00       	call   804fc0c <__best_cput+0x2>
 804f443:	83 c4 08             	add    esp,0x8
 804f446:	c3                   	ret    

0804f447 <__best__uput_one>:
 804f447:	60                   	pusha  
 804f448:	ba 00 00 00 00       	mov    edx,0x0
 804f44d:	b9 00 00 00 00       	mov    ecx,0x0
 804f452:	be 00 00 00 00       	mov    esi,0x0
 804f457:	bd 00 00 00 00       	mov    ebp,0x0
 804f45c:	bb 0a 00 00 00       	mov    ebx,0xa
 804f461:	89 c7                	mov    edi,eax

0804f463 <__best__uput_one_1>:
 804f463:	41                   	inc    ecx
 804f464:	f7 f3                	div    ebx
 804f466:	ba 00 00 00 00       	mov    edx,0x0
 804f46b:	83 f8 00             	cmp    eax,0x0
 804f46e:	75 f3                	jne    804f463 <__best__uput_one_1>
 804f470:	89 ce                	mov    esi,ecx
 804f472:	ba 00 00 00 00       	mov    edx,0x0
 804f477:	b8 01 00 00 00       	mov    eax,0x1

0804f47c <__best__uput_one_2>:
 804f47c:	50                   	push   eax
 804f47d:	f7 e3                	mul    ebx
 804f47f:	e2 fb                	loop   804f47c <__best__uput_one_2>
 804f481:	89 f1                	mov    ecx,esi
 804f483:	89 f8                	mov    eax,edi

0804f485 <__best__uput_one_3>:
 804f485:	5b                   	pop    ebx
 804f486:	ba 00 00 00 00       	mov    edx,0x0
 804f48b:	f7 f3                	div    ebx
 804f48d:	83 c0 30             	add    eax,0x30
 804f490:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f495:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f49a:	88 c0                	mov    al,al
 804f49c:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f4a0:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f4a5:	83 ec 02             	sub    esp,0x2
 804f4a8:	e8 5f 07 00 00       	call   804fc0c <__best_cput+0x2>
 804f4ad:	89 d0                	mov    eax,edx
 804f4af:	e2 d4                	loop   804f485 <__best__uput_one_3>
 804f4b1:	61                   	popa   
 804f4b2:	c3                   	ret    

0804f4b3 <__best_quput_one>:
 804f4b3:	e8 8f ff ff ff       	call   804f447 <__best__uput_one>
 804f4b8:	c3                   	ret    

0804f4b9 <__best_qsput_one>:
 804f4b9:	83 f8 00             	cmp    eax,0x0
 804f4bc:	7d 1f                	jge    804f4dd <..@3440._1>
 804f4be:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f4c3:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f4c8:	b0 2d                	mov    al,0x2d
 804f4ca:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f4ce:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f4d3:	83 ec 02             	sub    esp,0x2
 804f4d6:	e8 31 07 00 00       	call   804fc0c <__best_cput+0x2>
 804f4db:	f7 d8                	neg    eax

0804f4dd <..@3440._1>:
 804f4dd:	e8 65 ff ff ff       	call   804f447 <__best__uput_one>
 804f4e2:	c3                   	ret    

0804f4e3 <__best_duput_one>:
 804f4e3:	e8 5f ff ff ff       	call   804f447 <__best__uput_one>
 804f4e8:	c3                   	ret    

0804f4e9 <__best_dsput_one>:
 804f4e9:	83 f8 00             	cmp    eax,0x0
 804f4ec:	7d 1f                	jge    804f50d <..@3445._1>
 804f4ee:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f4f3:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f4f8:	b0 2d                	mov    al,0x2d
 804f4fa:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f4fe:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f503:	83 ec 02             	sub    esp,0x2
 804f506:	e8 01 07 00 00       	call   804fc0c <__best_cput+0x2>
 804f50b:	f7 d8                	neg    eax

0804f50d <..@3445._1>:
 804f50d:	e8 35 ff ff ff       	call   804f447 <__best__uput_one>
 804f512:	c3                   	ret    

0804f513 <__best_wuput_one>:
 804f513:	e8 2f ff ff ff       	call   804f447 <__best__uput_one>
 804f518:	c3                   	ret    

0804f519 <__best_wsput_one>:
 804f519:	c1 e0 08             	shl    eax,0x8
 804f51c:	c1 e0 08             	shl    eax,0x8
 804f51f:	83 f8 00             	cmp    eax,0x0
 804f522:	7d 1f                	jge    804f543 <..@3450._1>
 804f524:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f529:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f52e:	b0 2d                	mov    al,0x2d
 804f530:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f534:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f539:	83 ec 02             	sub    esp,0x2
 804f53c:	e8 cb 06 00 00       	call   804fc0c <__best_cput+0x2>
 804f541:	f7 d8                	neg    eax

0804f543 <..@3450._1>:
 804f543:	c1 e8 08             	shr    eax,0x8
 804f546:	c1 e8 08             	shr    eax,0x8
 804f549:	e8 f9 fe ff ff       	call   804f447 <__best__uput_one>
 804f54e:	c3                   	ret    

0804f54f <__best_buput_one>:
 804f54f:	e8 f3 fe ff ff       	call   804f447 <__best__uput_one>
 804f554:	c3                   	ret    

0804f555 <__best_bsput_one>:
 804f555:	c1 e0 08             	shl    eax,0x8
 804f558:	c1 e0 08             	shl    eax,0x8
 804f55b:	c1 e0 08             	shl    eax,0x8
 804f55e:	83 f8 00             	cmp    eax,0x0
 804f561:	7d 1f                	jge    804f582 <..@3455._1>
 804f563:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f568:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f56d:	b0 2d                	mov    al,0x2d
 804f56f:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f573:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f578:	83 ec 02             	sub    esp,0x2
 804f57b:	e8 8c 06 00 00       	call   804fc0c <__best_cput+0x2>
 804f580:	f7 d8                	neg    eax

0804f582 <..@3455._1>:
 804f582:	c1 e8 08             	shr    eax,0x8
 804f585:	c1 e8 08             	shr    eax,0x8
 804f588:	c1 e8 08             	shr    eax,0x8
 804f58b:	e8 b7 fe ff ff       	call   804f447 <__best__uput_one>
 804f590:	c3                   	ret    

0804f591 <__best_cput_one>:
 804f591:	60                   	pusha  
 804f592:	66 50                	push   ax
 804f594:	b8 04 00 00 00       	mov    eax,0x4
 804f599:	bb 01 00 00 00       	mov    ebx,0x1
 804f59e:	89 e1                	mov    ecx,esp
 804f5a0:	ba 01 00 00 00       	mov    edx,0x1
 804f5a5:	cd 80                	int    0x80
 804f5a7:	83 c4 02             	add    esp,0x2
 804f5aa:	61                   	popa   
 804f5ab:	c3                   	ret    

0804f5ac <__best_sput_one>:
 804f5ac:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f5b1:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f5b6:	88 c0                	mov    al,al
 804f5b8:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f5bc:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f5c1:	83 ec 02             	sub    esp,0x2
 804f5c4:	e8 43 06 00 00       	call   804fc0c <__best_cput+0x2>
 804f5c9:	c3                   	ret    

0804f5ca <__best_quput>:
 804f5ca:	6a 00                	push   0x0
 804f5cc:	6a 00                	push   0x0
 804f5ce:	6a 00                	push   0x0
 804f5d0:	6a 00                	push   0x0
 804f5d2:	6a 00                	push   0x0
 804f5d4:	6a 00                	push   0x0
 804f5d6:	6a 00                	push   0x0
 804f5d8:	6a 00                	push   0x0
 804f5da:	6a 00                	push   0x0
 804f5dc:	6a 00                	push   0x0
 804f5de:	6a 00                	push   0x0
 804f5e0:	6a 00                	push   0x0
 804f5e2:	6a 00                	push   0x0
 804f5e4:	6a 00                	push   0x0
 804f5e6:	6a 00                	push   0x0
 804f5e8:	6a 00                	push   0x0
 804f5ea:	6a 00                	push   0x0
 804f5ec:	6a 00                	push   0x0
 804f5ee:	6a 00                	push   0x0
 804f5f0:	6a 00                	push   0x0
 804f5f2:	6a 00                	push   0x0
 804f5f4:	6a 00                	push   0x0
 804f5f6:	6a 00                	push   0x0
 804f5f8:	6a 00                	push   0x0
 804f5fa:	6a 00                	push   0x0
 804f5fc:	6a 00                	push   0x0
 804f5fe:	6a 00                	push   0x0
 804f600:	6a 00                	push   0x0
 804f602:	6a 00                	push   0x0
 804f604:	6a 00                	push   0x0
 804f606:	6a 00                	push   0x0
 804f608:	6a 00                	push   0x0
 804f60a:	6a 20                	push   0x20

0804f60c <..@3465._1>:
 804f60c:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 804f611:	75 08                	jne    804f61b <..@3465._2>
 804f613:	ff 0c 24             	dec    DWORD PTR [esp]
 804f616:	8f 04 24             	pop    DWORD PTR [esp]
 804f619:	eb f1                	jmp    804f60c <..@3465._1>

0804f61b <..@3465._2>:
 804f61b:	60                   	pusha  
 804f61c:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 804f620:	89 e2                	mov    edx,esp
 804f622:	83 c2 28             	add    edx,0x28
 804f625:	89 cb                	mov    ebx,ecx
 804f627:	90                   	nop
 804f628:	60                   	pusha  
 804f629:	89 d9                	mov    ecx,ebx

0804f62b <..@3464._2>:
 804f62b:	83 f9 01             	cmp    ecx,0x1
 804f62e:	7c 34                	jl     804f664 <..@3464._1>
 804f630:	b8 00 00 00 00       	mov    eax,0x0
 804f635:	8b 02                	mov    eax,DWORD PTR [edx]
 804f637:	e8 77 fe ff ff       	call   804f4b3 <__best_quput_one>
 804f63c:	83 c2 08             	add    edx,0x8
 804f63f:	49                   	dec    ecx
 804f640:	83 f9 01             	cmp    ecx,0x1
 804f643:	7c 1f                	jl     804f664 <..@3464._1>
 804f645:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f64a:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f64f:	b0 20                	mov    al,0x20
 804f651:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f655:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f65a:	83 ec 02             	sub    esp,0x2
 804f65d:	e8 aa 05 00 00       	call   804fc0c <__best_cput+0x2>
 804f662:	eb c7                	jmp    804f62b <..@3464._2>

0804f664 <..@3464._1>:
 804f664:	61                   	popa   
 804f665:	89 c8                	mov    eax,ecx
 804f667:	bb 08 00 00 00       	mov    ebx,0x8
 804f66c:	f7 e3                	mul    ebx
 804f66e:	89 e3                	mov    ebx,esp
 804f670:	89 de                	mov    esi,ebx
 804f672:	89 df                	mov    edi,ebx
 804f674:	01 c7                	add    edi,eax
 804f676:	b9 28 00 00 00       	mov    ecx,0x28
 804f67b:	01 cf                	add    edi,ecx
 804f67d:	01 ce                	add    esi,ecx
 804f67f:	4f                   	dec    edi
 804f680:	4e                   	dec    esi
 804f681:	fd                   	std    
 804f682:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 804f684:	fc                   	cld    
 804f685:	01 c4                	add    esp,eax
 804f687:	61                   	popa   
 804f688:	83 c4 04             	add    esp,0x4
 804f68b:	c3                   	ret    

0804f68c <__best_qsput>:
 804f68c:	6a 00                	push   0x0
 804f68e:	6a 00                	push   0x0
 804f690:	6a 00                	push   0x0
 804f692:	6a 00                	push   0x0
 804f694:	6a 00                	push   0x0
 804f696:	6a 00                	push   0x0
 804f698:	6a 00                	push   0x0
 804f69a:	6a 00                	push   0x0
 804f69c:	6a 00                	push   0x0
 804f69e:	6a 00                	push   0x0
 804f6a0:	6a 00                	push   0x0
 804f6a2:	6a 00                	push   0x0
 804f6a4:	6a 00                	push   0x0
 804f6a6:	6a 00                	push   0x0
 804f6a8:	6a 00                	push   0x0
 804f6aa:	6a 00                	push   0x0
 804f6ac:	6a 00                	push   0x0
 804f6ae:	6a 00                	push   0x0
 804f6b0:	6a 00                	push   0x0
 804f6b2:	6a 00                	push   0x0
 804f6b4:	6a 00                	push   0x0
 804f6b6:	6a 00                	push   0x0
 804f6b8:	6a 00                	push   0x0
 804f6ba:	6a 00                	push   0x0
 804f6bc:	6a 00                	push   0x0
 804f6be:	6a 00                	push   0x0
 804f6c0:	6a 00                	push   0x0
 804f6c2:	6a 00                	push   0x0
 804f6c4:	6a 00                	push   0x0
 804f6c6:	6a 00                	push   0x0
 804f6c8:	6a 00                	push   0x0
 804f6ca:	6a 00                	push   0x0
 804f6cc:	6a 20                	push   0x20

0804f6ce <..@3471._1>:
 804f6ce:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 804f6d3:	75 08                	jne    804f6dd <..@3471._2>
 804f6d5:	ff 0c 24             	dec    DWORD PTR [esp]
 804f6d8:	8f 04 24             	pop    DWORD PTR [esp]
 804f6db:	eb f1                	jmp    804f6ce <..@3471._1>

0804f6dd <..@3471._2>:
 804f6dd:	60                   	pusha  
 804f6de:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 804f6e2:	89 e2                	mov    edx,esp
 804f6e4:	83 c2 28             	add    edx,0x28
 804f6e7:	89 cb                	mov    ebx,ecx
 804f6e9:	90                   	nop
 804f6ea:	60                   	pusha  
 804f6eb:	89 d9                	mov    ecx,ebx

0804f6ed <..@3470._2>:
 804f6ed:	83 f9 01             	cmp    ecx,0x1
 804f6f0:	7c 34                	jl     804f726 <..@3470._1>
 804f6f2:	b8 00 00 00 00       	mov    eax,0x0
 804f6f7:	8b 02                	mov    eax,DWORD PTR [edx]
 804f6f9:	e8 bb fd ff ff       	call   804f4b9 <__best_qsput_one>
 804f6fe:	83 c2 08             	add    edx,0x8
 804f701:	49                   	dec    ecx
 804f702:	83 f9 01             	cmp    ecx,0x1
 804f705:	7c 1f                	jl     804f726 <..@3470._1>
 804f707:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f70c:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f711:	b0 20                	mov    al,0x20
 804f713:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f717:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f71c:	83 ec 02             	sub    esp,0x2
 804f71f:	e8 e8 04 00 00       	call   804fc0c <__best_cput+0x2>
 804f724:	eb c7                	jmp    804f6ed <..@3470._2>

0804f726 <..@3470._1>:
 804f726:	61                   	popa   
 804f727:	89 c8                	mov    eax,ecx
 804f729:	bb 08 00 00 00       	mov    ebx,0x8
 804f72e:	f7 e3                	mul    ebx
 804f730:	89 e3                	mov    ebx,esp
 804f732:	89 de                	mov    esi,ebx
 804f734:	89 df                	mov    edi,ebx
 804f736:	01 c7                	add    edi,eax
 804f738:	b9 28 00 00 00       	mov    ecx,0x28
 804f73d:	01 cf                	add    edi,ecx
 804f73f:	01 ce                	add    esi,ecx
 804f741:	4f                   	dec    edi
 804f742:	4e                   	dec    esi
 804f743:	fd                   	std    
 804f744:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 804f746:	fc                   	cld    
 804f747:	01 c4                	add    esp,eax
 804f749:	61                   	popa   
 804f74a:	83 c4 04             	add    esp,0x4
 804f74d:	c3                   	ret    

0804f74e <__best_duput>:
 804f74e:	6a 00                	push   0x0
 804f750:	6a 00                	push   0x0
 804f752:	6a 00                	push   0x0
 804f754:	6a 00                	push   0x0
 804f756:	6a 00                	push   0x0
 804f758:	6a 00                	push   0x0
 804f75a:	6a 00                	push   0x0
 804f75c:	6a 00                	push   0x0
 804f75e:	6a 00                	push   0x0
 804f760:	6a 00                	push   0x0
 804f762:	6a 00                	push   0x0
 804f764:	6a 00                	push   0x0
 804f766:	6a 00                	push   0x0
 804f768:	6a 00                	push   0x0
 804f76a:	6a 00                	push   0x0
 804f76c:	6a 00                	push   0x0
 804f76e:	6a 00                	push   0x0
 804f770:	6a 00                	push   0x0
 804f772:	6a 00                	push   0x0
 804f774:	6a 00                	push   0x0
 804f776:	6a 00                	push   0x0
 804f778:	6a 00                	push   0x0
 804f77a:	6a 00                	push   0x0
 804f77c:	6a 00                	push   0x0
 804f77e:	6a 00                	push   0x0
 804f780:	6a 00                	push   0x0
 804f782:	6a 00                	push   0x0
 804f784:	6a 00                	push   0x0
 804f786:	6a 00                	push   0x0
 804f788:	6a 00                	push   0x0
 804f78a:	6a 00                	push   0x0
 804f78c:	6a 00                	push   0x0
 804f78e:	6a 20                	push   0x20

0804f790 <..@3477._1>:
 804f790:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 804f795:	75 08                	jne    804f79f <..@3477._2>
 804f797:	ff 0c 24             	dec    DWORD PTR [esp]
 804f79a:	8f 04 24             	pop    DWORD PTR [esp]
 804f79d:	eb f1                	jmp    804f790 <..@3477._1>

0804f79f <..@3477._2>:
 804f79f:	60                   	pusha  
 804f7a0:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 804f7a4:	89 e2                	mov    edx,esp
 804f7a6:	83 c2 28             	add    edx,0x28
 804f7a9:	89 cb                	mov    ebx,ecx
 804f7ab:	90                   	nop
 804f7ac:	60                   	pusha  
 804f7ad:	89 d9                	mov    ecx,ebx

0804f7af <..@3476._2>:
 804f7af:	83 f9 01             	cmp    ecx,0x1
 804f7b2:	7c 34                	jl     804f7e8 <..@3476._1>
 804f7b4:	b8 00 00 00 00       	mov    eax,0x0
 804f7b9:	8b 02                	mov    eax,DWORD PTR [edx]
 804f7bb:	e8 23 fd ff ff       	call   804f4e3 <__best_duput_one>
 804f7c0:	83 c2 04             	add    edx,0x4
 804f7c3:	49                   	dec    ecx
 804f7c4:	83 f9 01             	cmp    ecx,0x1
 804f7c7:	7c 1f                	jl     804f7e8 <..@3476._1>
 804f7c9:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f7ce:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f7d3:	b0 20                	mov    al,0x20
 804f7d5:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f7d9:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f7de:	83 ec 02             	sub    esp,0x2
 804f7e1:	e8 26 04 00 00       	call   804fc0c <__best_cput+0x2>
 804f7e6:	eb c7                	jmp    804f7af <..@3476._2>

0804f7e8 <..@3476._1>:
 804f7e8:	61                   	popa   
 804f7e9:	89 c8                	mov    eax,ecx
 804f7eb:	bb 04 00 00 00       	mov    ebx,0x4
 804f7f0:	f7 e3                	mul    ebx
 804f7f2:	89 e3                	mov    ebx,esp
 804f7f4:	89 de                	mov    esi,ebx
 804f7f6:	89 df                	mov    edi,ebx
 804f7f8:	01 c7                	add    edi,eax
 804f7fa:	b9 28 00 00 00       	mov    ecx,0x28
 804f7ff:	01 cf                	add    edi,ecx
 804f801:	01 ce                	add    esi,ecx
 804f803:	4f                   	dec    edi
 804f804:	4e                   	dec    esi
 804f805:	fd                   	std    
 804f806:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 804f808:	fc                   	cld    
 804f809:	01 c4                	add    esp,eax
 804f80b:	61                   	popa   
 804f80c:	83 c4 04             	add    esp,0x4
 804f80f:	c3                   	ret    

0804f810 <__best_dsput>:
 804f810:	6a 00                	push   0x0
 804f812:	6a 00                	push   0x0
 804f814:	6a 00                	push   0x0
 804f816:	6a 00                	push   0x0
 804f818:	6a 00                	push   0x0
 804f81a:	6a 00                	push   0x0
 804f81c:	6a 00                	push   0x0
 804f81e:	6a 00                	push   0x0
 804f820:	6a 00                	push   0x0
 804f822:	6a 00                	push   0x0
 804f824:	6a 00                	push   0x0
 804f826:	6a 00                	push   0x0
 804f828:	6a 00                	push   0x0
 804f82a:	6a 00                	push   0x0
 804f82c:	6a 00                	push   0x0
 804f82e:	6a 00                	push   0x0
 804f830:	6a 00                	push   0x0
 804f832:	6a 00                	push   0x0
 804f834:	6a 00                	push   0x0
 804f836:	6a 00                	push   0x0
 804f838:	6a 00                	push   0x0
 804f83a:	6a 00                	push   0x0
 804f83c:	6a 00                	push   0x0
 804f83e:	6a 00                	push   0x0
 804f840:	6a 00                	push   0x0
 804f842:	6a 00                	push   0x0
 804f844:	6a 00                	push   0x0
 804f846:	6a 00                	push   0x0
 804f848:	6a 00                	push   0x0
 804f84a:	6a 00                	push   0x0
 804f84c:	6a 00                	push   0x0
 804f84e:	6a 00                	push   0x0
 804f850:	6a 20                	push   0x20

0804f852 <..@3483._1>:
 804f852:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 804f857:	75 08                	jne    804f861 <..@3483._2>
 804f859:	ff 0c 24             	dec    DWORD PTR [esp]
 804f85c:	8f 04 24             	pop    DWORD PTR [esp]
 804f85f:	eb f1                	jmp    804f852 <..@3483._1>

0804f861 <..@3483._2>:
 804f861:	60                   	pusha  
 804f862:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 804f866:	89 e2                	mov    edx,esp
 804f868:	83 c2 28             	add    edx,0x28
 804f86b:	89 cb                	mov    ebx,ecx
 804f86d:	90                   	nop
 804f86e:	60                   	pusha  
 804f86f:	89 d9                	mov    ecx,ebx

0804f871 <..@3482._2>:
 804f871:	83 f9 01             	cmp    ecx,0x1
 804f874:	7c 34                	jl     804f8aa <..@3482._1>
 804f876:	b8 00 00 00 00       	mov    eax,0x0
 804f87b:	8b 02                	mov    eax,DWORD PTR [edx]
 804f87d:	e8 67 fc ff ff       	call   804f4e9 <__best_dsput_one>
 804f882:	83 c2 04             	add    edx,0x4
 804f885:	49                   	dec    ecx
 804f886:	83 f9 01             	cmp    ecx,0x1
 804f889:	7c 1f                	jl     804f8aa <..@3482._1>
 804f88b:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f890:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f895:	b0 20                	mov    al,0x20
 804f897:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f89b:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f8a0:	83 ec 02             	sub    esp,0x2
 804f8a3:	e8 64 03 00 00       	call   804fc0c <__best_cput+0x2>
 804f8a8:	eb c7                	jmp    804f871 <..@3482._2>

0804f8aa <..@3482._1>:
 804f8aa:	61                   	popa   
 804f8ab:	89 c8                	mov    eax,ecx
 804f8ad:	bb 04 00 00 00       	mov    ebx,0x4
 804f8b2:	f7 e3                	mul    ebx
 804f8b4:	89 e3                	mov    ebx,esp
 804f8b6:	89 de                	mov    esi,ebx
 804f8b8:	89 df                	mov    edi,ebx
 804f8ba:	01 c7                	add    edi,eax
 804f8bc:	b9 28 00 00 00       	mov    ecx,0x28
 804f8c1:	01 cf                	add    edi,ecx
 804f8c3:	01 ce                	add    esi,ecx
 804f8c5:	4f                   	dec    edi
 804f8c6:	4e                   	dec    esi
 804f8c7:	fd                   	std    
 804f8c8:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 804f8ca:	fc                   	cld    
 804f8cb:	01 c4                	add    esp,eax
 804f8cd:	61                   	popa   
 804f8ce:	83 c4 04             	add    esp,0x4
 804f8d1:	c3                   	ret    

0804f8d2 <__best_wuput>:
 804f8d2:	6a 00                	push   0x0
 804f8d4:	6a 00                	push   0x0
 804f8d6:	6a 00                	push   0x0
 804f8d8:	6a 00                	push   0x0
 804f8da:	6a 00                	push   0x0
 804f8dc:	6a 00                	push   0x0
 804f8de:	6a 00                	push   0x0
 804f8e0:	6a 00                	push   0x0
 804f8e2:	6a 00                	push   0x0
 804f8e4:	6a 00                	push   0x0
 804f8e6:	6a 00                	push   0x0
 804f8e8:	6a 00                	push   0x0
 804f8ea:	6a 00                	push   0x0
 804f8ec:	6a 00                	push   0x0
 804f8ee:	6a 00                	push   0x0
 804f8f0:	6a 00                	push   0x0
 804f8f2:	6a 00                	push   0x0
 804f8f4:	6a 00                	push   0x0
 804f8f6:	6a 00                	push   0x0
 804f8f8:	6a 00                	push   0x0
 804f8fa:	6a 00                	push   0x0
 804f8fc:	6a 00                	push   0x0
 804f8fe:	6a 00                	push   0x0
 804f900:	6a 00                	push   0x0
 804f902:	6a 00                	push   0x0
 804f904:	6a 00                	push   0x0
 804f906:	6a 00                	push   0x0
 804f908:	6a 00                	push   0x0
 804f90a:	6a 00                	push   0x0
 804f90c:	6a 00                	push   0x0
 804f90e:	6a 00                	push   0x0
 804f910:	6a 00                	push   0x0
 804f912:	6a 20                	push   0x20

0804f914 <..@3489._1>:
 804f914:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 804f919:	75 08                	jne    804f923 <..@3489._2>
 804f91b:	ff 0c 24             	dec    DWORD PTR [esp]
 804f91e:	8f 04 24             	pop    DWORD PTR [esp]
 804f921:	eb f1                	jmp    804f914 <..@3489._1>

0804f923 <..@3489._2>:
 804f923:	60                   	pusha  
 804f924:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 804f928:	89 e2                	mov    edx,esp
 804f92a:	83 c2 28             	add    edx,0x28
 804f92d:	89 cb                	mov    ebx,ecx
 804f92f:	90                   	nop
 804f930:	60                   	pusha  
 804f931:	89 d9                	mov    ecx,ebx

0804f933 <..@3488._2>:
 804f933:	83 f9 01             	cmp    ecx,0x1
 804f936:	7c 40                	jl     804f978 <..@3488._1>
 804f938:	b8 00 00 00 00       	mov    eax,0x0
 804f93d:	8b 02                	mov    eax,DWORD PTR [edx]
 804f93f:	c1 e0 08             	shl    eax,0x8
 804f942:	c1 e0 08             	shl    eax,0x8
 804f945:	c1 e8 08             	shr    eax,0x8
 804f948:	c1 e8 08             	shr    eax,0x8
 804f94b:	e8 c3 fb ff ff       	call   804f513 <__best_wuput_one>
 804f950:	83 c2 02             	add    edx,0x2
 804f953:	49                   	dec    ecx
 804f954:	83 f9 01             	cmp    ecx,0x1
 804f957:	7c 1f                	jl     804f978 <..@3488._1>
 804f959:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804f95e:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804f963:	b0 20                	mov    al,0x20
 804f965:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804f969:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804f96e:	83 ec 02             	sub    esp,0x2
 804f971:	e8 96 02 00 00       	call   804fc0c <__best_cput+0x2>
 804f976:	eb bb                	jmp    804f933 <..@3488._2>

0804f978 <..@3488._1>:
 804f978:	61                   	popa   
 804f979:	89 c8                	mov    eax,ecx
 804f97b:	bb 02 00 00 00       	mov    ebx,0x2
 804f980:	f7 e3                	mul    ebx
 804f982:	89 e3                	mov    ebx,esp
 804f984:	89 de                	mov    esi,ebx
 804f986:	89 df                	mov    edi,ebx
 804f988:	01 c7                	add    edi,eax
 804f98a:	b9 28 00 00 00       	mov    ecx,0x28
 804f98f:	01 cf                	add    edi,ecx
 804f991:	01 ce                	add    esi,ecx
 804f993:	4f                   	dec    edi
 804f994:	4e                   	dec    esi
 804f995:	fd                   	std    
 804f996:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 804f998:	fc                   	cld    
 804f999:	01 c4                	add    esp,eax
 804f99b:	61                   	popa   
 804f99c:	83 c4 04             	add    esp,0x4
 804f99f:	c3                   	ret    

0804f9a0 <__best_wsput>:
 804f9a0:	6a 00                	push   0x0
 804f9a2:	6a 00                	push   0x0
 804f9a4:	6a 00                	push   0x0
 804f9a6:	6a 00                	push   0x0
 804f9a8:	6a 00                	push   0x0
 804f9aa:	6a 00                	push   0x0
 804f9ac:	6a 00                	push   0x0
 804f9ae:	6a 00                	push   0x0
 804f9b0:	6a 00                	push   0x0
 804f9b2:	6a 00                	push   0x0
 804f9b4:	6a 00                	push   0x0
 804f9b6:	6a 00                	push   0x0
 804f9b8:	6a 00                	push   0x0
 804f9ba:	6a 00                	push   0x0
 804f9bc:	6a 00                	push   0x0
 804f9be:	6a 00                	push   0x0
 804f9c0:	6a 00                	push   0x0
 804f9c2:	6a 00                	push   0x0
 804f9c4:	6a 00                	push   0x0
 804f9c6:	6a 00                	push   0x0
 804f9c8:	6a 00                	push   0x0
 804f9ca:	6a 00                	push   0x0
 804f9cc:	6a 00                	push   0x0
 804f9ce:	6a 00                	push   0x0
 804f9d0:	6a 00                	push   0x0
 804f9d2:	6a 00                	push   0x0
 804f9d4:	6a 00                	push   0x0
 804f9d6:	6a 00                	push   0x0
 804f9d8:	6a 00                	push   0x0
 804f9da:	6a 00                	push   0x0
 804f9dc:	6a 00                	push   0x0
 804f9de:	6a 00                	push   0x0
 804f9e0:	6a 20                	push   0x20

0804f9e2 <..@3495._1>:
 804f9e2:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 804f9e7:	75 08                	jne    804f9f1 <..@3495._2>
 804f9e9:	ff 0c 24             	dec    DWORD PTR [esp]
 804f9ec:	8f 04 24             	pop    DWORD PTR [esp]
 804f9ef:	eb f1                	jmp    804f9e2 <..@3495._1>

0804f9f1 <..@3495._2>:
 804f9f1:	60                   	pusha  
 804f9f2:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 804f9f6:	89 e2                	mov    edx,esp
 804f9f8:	83 c2 28             	add    edx,0x28
 804f9fb:	89 cb                	mov    ebx,ecx
 804f9fd:	90                   	nop
 804f9fe:	60                   	pusha  
 804f9ff:	89 d9                	mov    ecx,ebx

0804fa01 <..@3494._2>:
 804fa01:	83 f9 01             	cmp    ecx,0x1
 804fa04:	7c 40                	jl     804fa46 <..@3494._1>
 804fa06:	b8 00 00 00 00       	mov    eax,0x0
 804fa0b:	8b 02                	mov    eax,DWORD PTR [edx]
 804fa0d:	c1 e0 08             	shl    eax,0x8
 804fa10:	c1 e0 08             	shl    eax,0x8
 804fa13:	c1 e8 08             	shr    eax,0x8
 804fa16:	c1 e8 08             	shr    eax,0x8
 804fa19:	e8 fb fa ff ff       	call   804f519 <__best_wsput_one>
 804fa1e:	83 c2 02             	add    edx,0x2
 804fa21:	49                   	dec    ecx
 804fa22:	83 f9 01             	cmp    ecx,0x1
 804fa25:	7c 1f                	jl     804fa46 <..@3494._1>
 804fa27:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804fa2c:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804fa31:	b0 20                	mov    al,0x20
 804fa33:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804fa37:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804fa3c:	83 ec 02             	sub    esp,0x2
 804fa3f:	e8 c8 01 00 00       	call   804fc0c <__best_cput+0x2>
 804fa44:	eb bb                	jmp    804fa01 <..@3494._2>

0804fa46 <..@3494._1>:
 804fa46:	61                   	popa   
 804fa47:	89 c8                	mov    eax,ecx
 804fa49:	bb 02 00 00 00       	mov    ebx,0x2
 804fa4e:	f7 e3                	mul    ebx
 804fa50:	89 e3                	mov    ebx,esp
 804fa52:	89 de                	mov    esi,ebx
 804fa54:	89 df                	mov    edi,ebx
 804fa56:	01 c7                	add    edi,eax
 804fa58:	b9 28 00 00 00       	mov    ecx,0x28
 804fa5d:	01 cf                	add    edi,ecx
 804fa5f:	01 ce                	add    esi,ecx
 804fa61:	4f                   	dec    edi
 804fa62:	4e                   	dec    esi
 804fa63:	fd                   	std    
 804fa64:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 804fa66:	fc                   	cld    
 804fa67:	01 c4                	add    esp,eax
 804fa69:	61                   	popa   
 804fa6a:	83 c4 04             	add    esp,0x4
 804fa6d:	c3                   	ret    

0804fa6e <__best_buput>:
 804fa6e:	6a 00                	push   0x0
 804fa70:	6a 00                	push   0x0
 804fa72:	6a 00                	push   0x0
 804fa74:	6a 00                	push   0x0
 804fa76:	6a 00                	push   0x0
 804fa78:	6a 00                	push   0x0
 804fa7a:	6a 00                	push   0x0
 804fa7c:	6a 00                	push   0x0
 804fa7e:	6a 00                	push   0x0
 804fa80:	6a 00                	push   0x0
 804fa82:	6a 00                	push   0x0
 804fa84:	6a 00                	push   0x0
 804fa86:	6a 00                	push   0x0
 804fa88:	6a 00                	push   0x0
 804fa8a:	6a 00                	push   0x0
 804fa8c:	6a 00                	push   0x0
 804fa8e:	6a 00                	push   0x0
 804fa90:	6a 00                	push   0x0
 804fa92:	6a 00                	push   0x0
 804fa94:	6a 00                	push   0x0
 804fa96:	6a 00                	push   0x0
 804fa98:	6a 00                	push   0x0
 804fa9a:	6a 00                	push   0x0
 804fa9c:	6a 00                	push   0x0
 804fa9e:	6a 00                	push   0x0
 804faa0:	6a 00                	push   0x0
 804faa2:	6a 00                	push   0x0
 804faa4:	6a 00                	push   0x0
 804faa6:	6a 00                	push   0x0
 804faa8:	6a 00                	push   0x0
 804faaa:	6a 00                	push   0x0
 804faac:	6a 00                	push   0x0
 804faae:	6a 20                	push   0x20

0804fab0 <..@3501._1>:
 804fab0:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 804fab5:	75 08                	jne    804fabf <..@3501._2>
 804fab7:	ff 0c 24             	dec    DWORD PTR [esp]
 804faba:	8f 04 24             	pop    DWORD PTR [esp]
 804fabd:	eb f1                	jmp    804fab0 <..@3501._1>

0804fabf <..@3501._2>:
 804fabf:	60                   	pusha  
 804fac0:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 804fac4:	89 e2                	mov    edx,esp
 804fac6:	83 c2 28             	add    edx,0x28
 804fac9:	89 cb                	mov    ebx,ecx
 804facb:	90                   	nop
 804facc:	60                   	pusha  
 804facd:	89 d9                	mov    ecx,ebx

0804facf <..@3500._2>:
 804facf:	83 f9 01             	cmp    ecx,0x1
 804fad2:	7c 40                	jl     804fb14 <..@3500._1>
 804fad4:	b8 00 00 00 00       	mov    eax,0x0
 804fad9:	8b 02                	mov    eax,DWORD PTR [edx]
 804fadb:	c1 e0 08             	shl    eax,0x8
 804fade:	c1 e0 08             	shl    eax,0x8
 804fae1:	c1 e8 08             	shr    eax,0x8
 804fae4:	c1 e8 08             	shr    eax,0x8
 804fae7:	e8 63 fa ff ff       	call   804f54f <__best_buput_one>
 804faec:	83 c2 02             	add    edx,0x2
 804faef:	49                   	dec    ecx
 804faf0:	83 f9 01             	cmp    ecx,0x1
 804faf3:	7c 1f                	jl     804fb14 <..@3500._1>
 804faf5:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804fafa:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804faff:	b0 20                	mov    al,0x20
 804fb01:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804fb05:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804fb0a:	83 ec 02             	sub    esp,0x2
 804fb0d:	e8 fa 00 00 00       	call   804fc0c <__best_cput+0x2>
 804fb12:	eb bb                	jmp    804facf <..@3500._2>

0804fb14 <..@3500._1>:
 804fb14:	61                   	popa   
 804fb15:	89 c8                	mov    eax,ecx
 804fb17:	bb 02 00 00 00       	mov    ebx,0x2
 804fb1c:	f7 e3                	mul    ebx
 804fb1e:	89 e3                	mov    ebx,esp
 804fb20:	89 de                	mov    esi,ebx
 804fb22:	89 df                	mov    edi,ebx
 804fb24:	01 c7                	add    edi,eax
 804fb26:	b9 28 00 00 00       	mov    ecx,0x28
 804fb2b:	01 cf                	add    edi,ecx
 804fb2d:	01 ce                	add    esi,ecx
 804fb2f:	4f                   	dec    edi
 804fb30:	4e                   	dec    esi
 804fb31:	fd                   	std    
 804fb32:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 804fb34:	fc                   	cld    
 804fb35:	01 c4                	add    esp,eax
 804fb37:	61                   	popa   
 804fb38:	83 c4 04             	add    esp,0x4
 804fb3b:	c3                   	ret    

0804fb3c <__best_bsput>:
 804fb3c:	6a 00                	push   0x0
 804fb3e:	6a 00                	push   0x0
 804fb40:	6a 00                	push   0x0
 804fb42:	6a 00                	push   0x0
 804fb44:	6a 00                	push   0x0
 804fb46:	6a 00                	push   0x0
 804fb48:	6a 00                	push   0x0
 804fb4a:	6a 00                	push   0x0
 804fb4c:	6a 00                	push   0x0
 804fb4e:	6a 00                	push   0x0
 804fb50:	6a 00                	push   0x0
 804fb52:	6a 00                	push   0x0
 804fb54:	6a 00                	push   0x0
 804fb56:	6a 00                	push   0x0
 804fb58:	6a 00                	push   0x0
 804fb5a:	6a 00                	push   0x0
 804fb5c:	6a 00                	push   0x0
 804fb5e:	6a 00                	push   0x0
 804fb60:	6a 00                	push   0x0
 804fb62:	6a 00                	push   0x0
 804fb64:	6a 00                	push   0x0
 804fb66:	6a 00                	push   0x0
 804fb68:	6a 00                	push   0x0
 804fb6a:	6a 00                	push   0x0
 804fb6c:	6a 00                	push   0x0
 804fb6e:	6a 00                	push   0x0
 804fb70:	6a 00                	push   0x0
 804fb72:	6a 00                	push   0x0
 804fb74:	6a 00                	push   0x0
 804fb76:	6a 00                	push   0x0
 804fb78:	6a 00                	push   0x0
 804fb7a:	6a 00                	push   0x0
 804fb7c:	6a 20                	push   0x20

0804fb7e <..@3507._1>:
 804fb7e:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 804fb83:	75 08                	jne    804fb8d <..@3507._2>
 804fb85:	ff 0c 24             	dec    DWORD PTR [esp]
 804fb88:	8f 04 24             	pop    DWORD PTR [esp]
 804fb8b:	eb f1                	jmp    804fb7e <..@3507._1>

0804fb8d <..@3507._2>:
 804fb8d:	60                   	pusha  
 804fb8e:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 804fb92:	89 e2                	mov    edx,esp
 804fb94:	83 c2 28             	add    edx,0x28
 804fb97:	89 cb                	mov    ebx,ecx
 804fb99:	90                   	nop
 804fb9a:	60                   	pusha  
 804fb9b:	89 d9                	mov    ecx,ebx

0804fb9d <..@3506._2>:
 804fb9d:	83 f9 01             	cmp    ecx,0x1
 804fba0:	7c 40                	jl     804fbe2 <..@3506._1>
 804fba2:	b8 00 00 00 00       	mov    eax,0x0
 804fba7:	8b 02                	mov    eax,DWORD PTR [edx]
 804fba9:	c1 e0 08             	shl    eax,0x8
 804fbac:	c1 e0 08             	shl    eax,0x8
 804fbaf:	c1 e8 08             	shr    eax,0x8
 804fbb2:	c1 e8 08             	shr    eax,0x8
 804fbb5:	e8 9b f9 ff ff       	call   804f555 <__best_bsput_one>
 804fbba:	83 c2 02             	add    edx,0x2
 804fbbd:	49                   	dec    ecx
 804fbbe:	83 f9 01             	cmp    ecx,0x1
 804fbc1:	7c 1f                	jl     804fbe2 <..@3506._1>
 804fbc3:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804fbc8:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804fbcd:	b0 20                	mov    al,0x20
 804fbcf:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804fbd3:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804fbd8:	83 ec 02             	sub    esp,0x2
 804fbdb:	e8 2c 00 00 00       	call   804fc0c <__best_cput+0x2>
 804fbe0:	eb bb                	jmp    804fb9d <..@3506._2>

0804fbe2 <..@3506._1>:
 804fbe2:	61                   	popa   
 804fbe3:	89 c8                	mov    eax,ecx
 804fbe5:	bb 02 00 00 00       	mov    ebx,0x2
 804fbea:	f7 e3                	mul    ebx
 804fbec:	89 e3                	mov    ebx,esp
 804fbee:	89 de                	mov    esi,ebx
 804fbf0:	89 df                	mov    edi,ebx
 804fbf2:	01 c7                	add    edi,eax
 804fbf4:	b9 28 00 00 00       	mov    ecx,0x28
 804fbf9:	01 cf                	add    edi,ecx
 804fbfb:	01 ce                	add    esi,ecx
 804fbfd:	4f                   	dec    edi
 804fbfe:	4e                   	dec    esi
 804fbff:	fd                   	std    
 804fc00:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 804fc02:	fc                   	cld    
 804fc03:	01 c4                	add    esp,eax
 804fc05:	61                   	popa   
 804fc06:	83 c4 04             	add    esp,0x4
 804fc09:	c3                   	ret    

0804fc0a <__best_cput>:
 804fc0a:	6a 00                	push   0x0
 804fc0c:	6a 00                	push   0x0
 804fc0e:	6a 00                	push   0x0
 804fc10:	6a 00                	push   0x0
 804fc12:	6a 00                	push   0x0
 804fc14:	6a 00                	push   0x0
 804fc16:	6a 00                	push   0x0
 804fc18:	6a 00                	push   0x0
 804fc1a:	6a 00                	push   0x0
 804fc1c:	6a 00                	push   0x0
 804fc1e:	6a 00                	push   0x0
 804fc20:	6a 00                	push   0x0
 804fc22:	6a 00                	push   0x0
 804fc24:	6a 00                	push   0x0
 804fc26:	6a 00                	push   0x0
 804fc28:	6a 00                	push   0x0
 804fc2a:	6a 00                	push   0x0
 804fc2c:	6a 00                	push   0x0
 804fc2e:	6a 00                	push   0x0
 804fc30:	6a 00                	push   0x0
 804fc32:	6a 00                	push   0x0
 804fc34:	6a 00                	push   0x0
 804fc36:	6a 00                	push   0x0
 804fc38:	6a 00                	push   0x0
 804fc3a:	6a 00                	push   0x0
 804fc3c:	6a 00                	push   0x0
 804fc3e:	6a 00                	push   0x0
 804fc40:	6a 00                	push   0x0
 804fc42:	6a 00                	push   0x0
 804fc44:	6a 00                	push   0x0
 804fc46:	6a 00                	push   0x0
 804fc48:	6a 00                	push   0x0
 804fc4a:	6a 20                	push   0x20

0804fc4c <..@3513._1>:
 804fc4c:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 804fc51:	75 08                	jne    804fc5b <..@3513._2>
 804fc53:	ff 0c 24             	dec    DWORD PTR [esp]
 804fc56:	8f 04 24             	pop    DWORD PTR [esp]
 804fc59:	eb f1                	jmp    804fc4c <..@3513._1>

0804fc5b <..@3513._2>:
 804fc5b:	60                   	pusha  
 804fc5c:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 804fc60:	89 e2                	mov    edx,esp
 804fc62:	83 c2 28             	add    edx,0x28
 804fc65:	89 cb                	mov    ebx,ecx
 804fc67:	90                   	nop
 804fc68:	60                   	pusha  
 804fc69:	89 d9                	mov    ecx,ebx

0804fc6b <..@3512._2>:
 804fc6b:	83 f9 01             	cmp    ecx,0x1
 804fc6e:	7c 40                	jl     804fcb0 <..@3512._1>
 804fc70:	b8 00 00 00 00       	mov    eax,0x0
 804fc75:	8b 02                	mov    eax,DWORD PTR [edx]
 804fc77:	c1 e0 08             	shl    eax,0x8
 804fc7a:	c1 e0 08             	shl    eax,0x8
 804fc7d:	c1 e8 08             	shr    eax,0x8
 804fc80:	c1 e8 08             	shr    eax,0x8
 804fc83:	e8 09 f9 ff ff       	call   804f591 <__best_cput_one>
 804fc88:	83 c2 02             	add    edx,0x2
 804fc8b:	49                   	dec    ecx
 804fc8c:	83 f9 01             	cmp    ecx,0x1
 804fc8f:	7c 1f                	jl     804fcb0 <..@3512._1>
 804fc91:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804fc96:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804fc9b:	b0 20                	mov    al,0x20
 804fc9d:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804fca1:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804fca6:	83 ec 02             	sub    esp,0x2
 804fca9:	e8 5e ff ff ff       	call   804fc0c <__best_cput+0x2>
 804fcae:	eb bb                	jmp    804fc6b <..@3512._2>

0804fcb0 <..@3512._1>:
 804fcb0:	61                   	popa   
 804fcb1:	89 c8                	mov    eax,ecx
 804fcb3:	bb 02 00 00 00       	mov    ebx,0x2
 804fcb8:	f7 e3                	mul    ebx
 804fcba:	89 e3                	mov    ebx,esp
 804fcbc:	89 de                	mov    esi,ebx
 804fcbe:	89 df                	mov    edi,ebx
 804fcc0:	01 c7                	add    edi,eax
 804fcc2:	b9 28 00 00 00       	mov    ecx,0x28
 804fcc7:	01 cf                	add    edi,ecx
 804fcc9:	01 ce                	add    esi,ecx
 804fccb:	4f                   	dec    edi
 804fccc:	4e                   	dec    esi
 804fccd:	fd                   	std    
 804fcce:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 804fcd0:	fc                   	cld    
 804fcd1:	01 c4                	add    esp,eax
 804fcd3:	61                   	popa   
 804fcd4:	83 c4 04             	add    esp,0x4
 804fcd7:	c3                   	ret    

0804fcd8 <__best_sput>:
 804fcd8:	6a 00                	push   0x0
 804fcda:	6a 00                	push   0x0
 804fcdc:	6a 00                	push   0x0
 804fcde:	6a 00                	push   0x0
 804fce0:	6a 00                	push   0x0
 804fce2:	6a 00                	push   0x0
 804fce4:	6a 00                	push   0x0
 804fce6:	6a 00                	push   0x0
 804fce8:	6a 00                	push   0x0
 804fcea:	6a 00                	push   0x0
 804fcec:	6a 00                	push   0x0
 804fcee:	6a 00                	push   0x0
 804fcf0:	6a 00                	push   0x0
 804fcf2:	6a 00                	push   0x0
 804fcf4:	6a 00                	push   0x0
 804fcf6:	6a 00                	push   0x0
 804fcf8:	6a 00                	push   0x0
 804fcfa:	6a 00                	push   0x0
 804fcfc:	6a 00                	push   0x0
 804fcfe:	6a 00                	push   0x0
 804fd00:	6a 00                	push   0x0
 804fd02:	6a 00                	push   0x0
 804fd04:	6a 00                	push   0x0
 804fd06:	6a 00                	push   0x0
 804fd08:	6a 00                	push   0x0
 804fd0a:	6a 00                	push   0x0
 804fd0c:	6a 00                	push   0x0
 804fd0e:	6a 00                	push   0x0
 804fd10:	6a 00                	push   0x0
 804fd12:	6a 00                	push   0x0
 804fd14:	6a 00                	push   0x0
 804fd16:	6a 00                	push   0x0
 804fd18:	6a 20                	push   0x20

0804fd1a <..@3519._1>:
 804fd1a:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 804fd1f:	75 08                	jne    804fd29 <..@3519._2>
 804fd21:	ff 0c 24             	dec    DWORD PTR [esp]
 804fd24:	8f 04 24             	pop    DWORD PTR [esp]
 804fd27:	eb f1                	jmp    804fd1a <..@3519._1>

0804fd29 <..@3519._2>:
 804fd29:	60                   	pusha  
 804fd2a:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 804fd2e:	89 e2                	mov    edx,esp
 804fd30:	83 c2 28             	add    edx,0x28
 804fd33:	89 cb                	mov    ebx,ecx
 804fd35:	8b 54 24 24          	mov    edx,DWORD PTR [esp+0x24]
 804fd39:	01 4c 24 24          	add    DWORD PTR [esp+0x24],ecx
 804fd3d:	b9 00 00 00 00       	mov    ecx,0x0
 804fd42:	60                   	pusha  
 804fd43:	89 d9                	mov    ecx,ebx

0804fd45 <..@3518._2>:
 804fd45:	83 f9 01             	cmp    ecx,0x1
 804fd48:	7c 29                	jl     804fd73 <..@3518._1>
 804fd4a:	b8 00 00 00 00       	mov    eax,0x0
 804fd4f:	8b 02                	mov    eax,DWORD PTR [edx]
 804fd51:	c1 e0 08             	shl    eax,0x8
 804fd54:	c1 e0 08             	shl    eax,0x8
 804fd57:	c1 e0 08             	shl    eax,0x8
 804fd5a:	c1 e8 08             	shr    eax,0x8
 804fd5d:	c1 e8 08             	shr    eax,0x8
 804fd60:	c1 e8 08             	shr    eax,0x8
 804fd63:	e8 44 f8 ff ff       	call   804f5ac <__best_sput_one>
 804fd68:	83 c2 01             	add    edx,0x1
 804fd6b:	49                   	dec    ecx
 804fd6c:	83 f9 01             	cmp    ecx,0x1
 804fd6f:	7c 02                	jl     804fd73 <..@3518._1>
 804fd71:	eb d2                	jmp    804fd45 <..@3518._2>

0804fd73 <..@3518._1>:
 804fd73:	61                   	popa   
 804fd74:	89 c8                	mov    eax,ecx
 804fd76:	bb 01 00 00 00       	mov    ebx,0x1
 804fd7b:	f7 e3                	mul    ebx
 804fd7d:	89 e3                	mov    ebx,esp
 804fd7f:	89 de                	mov    esi,ebx
 804fd81:	89 df                	mov    edi,ebx
 804fd83:	01 c7                	add    edi,eax
 804fd85:	b9 28 00 00 00       	mov    ecx,0x28
 804fd8a:	01 cf                	add    edi,ecx
 804fd8c:	01 ce                	add    esi,ecx
 804fd8e:	4f                   	dec    edi
 804fd8f:	4e                   	dec    esi
 804fd90:	fd                   	std    
 804fd91:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 804fd93:	fc                   	cld    
 804fd94:	01 c4                	add    esp,eax
 804fd96:	61                   	popa   
 804fd97:	83 c4 04             	add    esp,0x4
 804fd9a:	c3                   	ret    

0804fd9b <__best_quwrite>:
 804fd9b:	6a 00                	push   0x0
 804fd9d:	6a 00                	push   0x0
 804fd9f:	6a 00                	push   0x0
 804fda1:	6a 00                	push   0x0
 804fda3:	6a 00                	push   0x0
 804fda5:	6a 00                	push   0x0
 804fda7:	6a 00                	push   0x0
 804fda9:	6a 00                	push   0x0
 804fdab:	6a 00                	push   0x0
 804fdad:	6a 00                	push   0x0
 804fdaf:	6a 00                	push   0x0
 804fdb1:	6a 00                	push   0x0
 804fdb3:	6a 00                	push   0x0
 804fdb5:	6a 00                	push   0x0
 804fdb7:	6a 00                	push   0x0
 804fdb9:	6a 00                	push   0x0
 804fdbb:	6a 00                	push   0x0
 804fdbd:	6a 00                	push   0x0
 804fdbf:	6a 00                	push   0x0
 804fdc1:	6a 00                	push   0x0
 804fdc3:	6a 00                	push   0x0
 804fdc5:	6a 00                	push   0x0
 804fdc7:	6a 00                	push   0x0
 804fdc9:	6a 00                	push   0x0
 804fdcb:	6a 00                	push   0x0
 804fdcd:	6a 00                	push   0x0
 804fdcf:	6a 00                	push   0x0
 804fdd1:	6a 00                	push   0x0
 804fdd3:	6a 00                	push   0x0
 804fdd5:	6a 00                	push   0x0
 804fdd7:	6a 00                	push   0x0
 804fdd9:	6a 00                	push   0x0
 804fddb:	6a 20                	push   0x20

0804fddd <..@3522._1>:
 804fddd:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 804fde2:	75 08                	jne    804fdec <..@3522._2>
 804fde4:	ff 0c 24             	dec    DWORD PTR [esp]
 804fde7:	8f 04 24             	pop    DWORD PTR [esp]
 804fdea:	eb f1                	jmp    804fddd <..@3522._1>

0804fdec <..@3522._2>:
 804fdec:	60                   	pusha  
 804fded:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 804fdf1:	89 e2                	mov    edx,esp
 804fdf3:	83 c2 28             	add    edx,0x28
 804fdf6:	89 cb                	mov    ebx,ecx
 804fdf8:	90                   	nop
 804fdf9:	60                   	pusha  
 804fdfa:	89 d9                	mov    ecx,ebx

0804fdfc <..@3521._2>:
 804fdfc:	83 f9 01             	cmp    ecx,0x1
 804fdff:	7c 34                	jl     804fe35 <..@3521._1>
 804fe01:	b8 00 00 00 00       	mov    eax,0x0
 804fe06:	8b 02                	mov    eax,DWORD PTR [edx]
 804fe08:	e8 a6 f6 ff ff       	call   804f4b3 <__best_quput_one>
 804fe0d:	83 c2 08             	add    edx,0x8
 804fe10:	49                   	dec    ecx
 804fe11:	83 f9 01             	cmp    ecx,0x1
 804fe14:	7c 1f                	jl     804fe35 <..@3521._1>
 804fe16:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804fe1b:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804fe20:	b0 20                	mov    al,0x20
 804fe22:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804fe26:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804fe2b:	83 ec 02             	sub    esp,0x2
 804fe2e:	e8 d9 fd ff ff       	call   804fc0c <__best_cput+0x2>
 804fe33:	eb c7                	jmp    804fdfc <..@3521._2>

0804fe35 <..@3521._1>:
 804fe35:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804fe3a:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804fe3f:	b0 20                	mov    al,0x20
 804fe41:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804fe45:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804fe4a:	83 ec 02             	sub    esp,0x2
 804fe4d:	e8 ba fd ff ff       	call   804fc0c <__best_cput+0x2>
 804fe52:	61                   	popa   
 804fe53:	89 c8                	mov    eax,ecx
 804fe55:	bb 08 00 00 00       	mov    ebx,0x8
 804fe5a:	f7 e3                	mul    ebx
 804fe5c:	89 e3                	mov    ebx,esp
 804fe5e:	89 de                	mov    esi,ebx
 804fe60:	89 df                	mov    edi,ebx
 804fe62:	01 c7                	add    edi,eax
 804fe64:	b9 28 00 00 00       	mov    ecx,0x28
 804fe69:	01 cf                	add    edi,ecx
 804fe6b:	01 ce                	add    esi,ecx
 804fe6d:	4f                   	dec    edi
 804fe6e:	4e                   	dec    esi
 804fe6f:	fd                   	std    
 804fe70:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 804fe72:	fc                   	cld    
 804fe73:	01 c4                	add    esp,eax
 804fe75:	61                   	popa   
 804fe76:	83 c4 04             	add    esp,0x4
 804fe79:	c3                   	ret    

0804fe7a <__best_qswrite>:
 804fe7a:	6a 00                	push   0x0
 804fe7c:	6a 00                	push   0x0
 804fe7e:	6a 00                	push   0x0
 804fe80:	6a 00                	push   0x0
 804fe82:	6a 00                	push   0x0
 804fe84:	6a 00                	push   0x0
 804fe86:	6a 00                	push   0x0
 804fe88:	6a 00                	push   0x0
 804fe8a:	6a 00                	push   0x0
 804fe8c:	6a 00                	push   0x0
 804fe8e:	6a 00                	push   0x0
 804fe90:	6a 00                	push   0x0
 804fe92:	6a 00                	push   0x0
 804fe94:	6a 00                	push   0x0
 804fe96:	6a 00                	push   0x0
 804fe98:	6a 00                	push   0x0
 804fe9a:	6a 00                	push   0x0
 804fe9c:	6a 00                	push   0x0
 804fe9e:	6a 00                	push   0x0
 804fea0:	6a 00                	push   0x0
 804fea2:	6a 00                	push   0x0
 804fea4:	6a 00                	push   0x0
 804fea6:	6a 00                	push   0x0
 804fea8:	6a 00                	push   0x0
 804feaa:	6a 00                	push   0x0
 804feac:	6a 00                	push   0x0
 804feae:	6a 00                	push   0x0
 804feb0:	6a 00                	push   0x0
 804feb2:	6a 00                	push   0x0
 804feb4:	6a 00                	push   0x0
 804feb6:	6a 00                	push   0x0
 804feb8:	6a 00                	push   0x0
 804feba:	6a 20                	push   0x20

0804febc <..@3532._1>:
 804febc:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 804fec1:	75 08                	jne    804fecb <..@3532._2>
 804fec3:	ff 0c 24             	dec    DWORD PTR [esp]
 804fec6:	8f 04 24             	pop    DWORD PTR [esp]
 804fec9:	eb f1                	jmp    804febc <..@3532._1>

0804fecb <..@3532._2>:
 804fecb:	60                   	pusha  
 804fecc:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 804fed0:	89 e2                	mov    edx,esp
 804fed2:	83 c2 28             	add    edx,0x28
 804fed5:	89 cb                	mov    ebx,ecx
 804fed7:	90                   	nop
 804fed8:	60                   	pusha  
 804fed9:	89 d9                	mov    ecx,ebx

0804fedb <..@3531._2>:
 804fedb:	83 f9 01             	cmp    ecx,0x1
 804fede:	7c 34                	jl     804ff14 <..@3531._1>
 804fee0:	b8 00 00 00 00       	mov    eax,0x0
 804fee5:	8b 02                	mov    eax,DWORD PTR [edx]
 804fee7:	e8 cd f5 ff ff       	call   804f4b9 <__best_qsput_one>
 804feec:	83 c2 08             	add    edx,0x8
 804feef:	49                   	dec    ecx
 804fef0:	83 f9 01             	cmp    ecx,0x1
 804fef3:	7c 1f                	jl     804ff14 <..@3531._1>
 804fef5:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804fefa:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804feff:	b0 20                	mov    al,0x20
 804ff01:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804ff05:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804ff0a:	83 ec 02             	sub    esp,0x2
 804ff0d:	e8 fa fc ff ff       	call   804fc0c <__best_cput+0x2>
 804ff12:	eb c7                	jmp    804fedb <..@3531._2>

0804ff14 <..@3531._1>:
 804ff14:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804ff19:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804ff1e:	b0 20                	mov    al,0x20
 804ff20:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804ff24:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804ff29:	83 ec 02             	sub    esp,0x2
 804ff2c:	e8 db fc ff ff       	call   804fc0c <__best_cput+0x2>
 804ff31:	61                   	popa   
 804ff32:	89 c8                	mov    eax,ecx
 804ff34:	bb 08 00 00 00       	mov    ebx,0x8
 804ff39:	f7 e3                	mul    ebx
 804ff3b:	89 e3                	mov    ebx,esp
 804ff3d:	89 de                	mov    esi,ebx
 804ff3f:	89 df                	mov    edi,ebx
 804ff41:	01 c7                	add    edi,eax
 804ff43:	b9 28 00 00 00       	mov    ecx,0x28
 804ff48:	01 cf                	add    edi,ecx
 804ff4a:	01 ce                	add    esi,ecx
 804ff4c:	4f                   	dec    edi
 804ff4d:	4e                   	dec    esi
 804ff4e:	fd                   	std    
 804ff4f:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 804ff51:	fc                   	cld    
 804ff52:	01 c4                	add    esp,eax
 804ff54:	61                   	popa   
 804ff55:	83 c4 04             	add    esp,0x4
 804ff58:	c3                   	ret    

0804ff59 <__best_duwrite>:
 804ff59:	6a 00                	push   0x0
 804ff5b:	6a 00                	push   0x0
 804ff5d:	6a 00                	push   0x0
 804ff5f:	6a 00                	push   0x0
 804ff61:	6a 00                	push   0x0
 804ff63:	6a 00                	push   0x0
 804ff65:	6a 00                	push   0x0
 804ff67:	6a 00                	push   0x0
 804ff69:	6a 00                	push   0x0
 804ff6b:	6a 00                	push   0x0
 804ff6d:	6a 00                	push   0x0
 804ff6f:	6a 00                	push   0x0
 804ff71:	6a 00                	push   0x0
 804ff73:	6a 00                	push   0x0
 804ff75:	6a 00                	push   0x0
 804ff77:	6a 00                	push   0x0
 804ff79:	6a 00                	push   0x0
 804ff7b:	6a 00                	push   0x0
 804ff7d:	6a 00                	push   0x0
 804ff7f:	6a 00                	push   0x0
 804ff81:	6a 00                	push   0x0
 804ff83:	6a 00                	push   0x0
 804ff85:	6a 00                	push   0x0
 804ff87:	6a 00                	push   0x0
 804ff89:	6a 00                	push   0x0
 804ff8b:	6a 00                	push   0x0
 804ff8d:	6a 00                	push   0x0
 804ff8f:	6a 00                	push   0x0
 804ff91:	6a 00                	push   0x0
 804ff93:	6a 00                	push   0x0
 804ff95:	6a 00                	push   0x0
 804ff97:	6a 00                	push   0x0
 804ff99:	6a 20                	push   0x20

0804ff9b <..@3542._1>:
 804ff9b:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 804ffa0:	75 08                	jne    804ffaa <..@3542._2>
 804ffa2:	ff 0c 24             	dec    DWORD PTR [esp]
 804ffa5:	8f 04 24             	pop    DWORD PTR [esp]
 804ffa8:	eb f1                	jmp    804ff9b <..@3542._1>

0804ffaa <..@3542._2>:
 804ffaa:	60                   	pusha  
 804ffab:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 804ffaf:	89 e2                	mov    edx,esp
 804ffb1:	83 c2 28             	add    edx,0x28
 804ffb4:	89 cb                	mov    ebx,ecx
 804ffb6:	90                   	nop
 804ffb7:	60                   	pusha  
 804ffb8:	89 d9                	mov    ecx,ebx

0804ffba <..@3541._2>:
 804ffba:	83 f9 01             	cmp    ecx,0x1
 804ffbd:	7c 34                	jl     804fff3 <..@3541._1>
 804ffbf:	b8 00 00 00 00       	mov    eax,0x0
 804ffc4:	8b 02                	mov    eax,DWORD PTR [edx]
 804ffc6:	e8 18 f5 ff ff       	call   804f4e3 <__best_duput_one>
 804ffcb:	83 c2 04             	add    edx,0x4
 804ffce:	49                   	dec    ecx
 804ffcf:	83 f9 01             	cmp    ecx,0x1
 804ffd2:	7c 1f                	jl     804fff3 <..@3541._1>
 804ffd4:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804ffd9:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804ffde:	b0 20                	mov    al,0x20
 804ffe0:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 804ffe4:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 804ffe9:	83 ec 02             	sub    esp,0x2
 804ffec:	e8 1b fc ff ff       	call   804fc0c <__best_cput+0x2>
 804fff1:	eb c7                	jmp    804ffba <..@3541._2>

0804fff3 <..@3541._1>:
 804fff3:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 804fff8:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 804fffd:	b0 20                	mov    al,0x20
 804ffff:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8050003:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 8050008:	83 ec 02             	sub    esp,0x2
 805000b:	e8 fc fb ff ff       	call   804fc0c <__best_cput+0x2>
 8050010:	61                   	popa   
 8050011:	89 c8                	mov    eax,ecx
 8050013:	bb 04 00 00 00       	mov    ebx,0x4
 8050018:	f7 e3                	mul    ebx
 805001a:	89 e3                	mov    ebx,esp
 805001c:	89 de                	mov    esi,ebx
 805001e:	89 df                	mov    edi,ebx
 8050020:	01 c7                	add    edi,eax
 8050022:	b9 28 00 00 00       	mov    ecx,0x28
 8050027:	01 cf                	add    edi,ecx
 8050029:	01 ce                	add    esi,ecx
 805002b:	4f                   	dec    edi
 805002c:	4e                   	dec    esi
 805002d:	fd                   	std    
 805002e:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8050030:	fc                   	cld    
 8050031:	01 c4                	add    esp,eax
 8050033:	61                   	popa   
 8050034:	83 c4 04             	add    esp,0x4
 8050037:	c3                   	ret    

08050038 <__best_dswrite>:
 8050038:	6a 00                	push   0x0
 805003a:	6a 00                	push   0x0
 805003c:	6a 00                	push   0x0
 805003e:	6a 00                	push   0x0
 8050040:	6a 00                	push   0x0
 8050042:	6a 00                	push   0x0
 8050044:	6a 00                	push   0x0
 8050046:	6a 00                	push   0x0
 8050048:	6a 00                	push   0x0
 805004a:	6a 00                	push   0x0
 805004c:	6a 00                	push   0x0
 805004e:	6a 00                	push   0x0
 8050050:	6a 00                	push   0x0
 8050052:	6a 00                	push   0x0
 8050054:	6a 00                	push   0x0
 8050056:	6a 00                	push   0x0
 8050058:	6a 00                	push   0x0
 805005a:	6a 00                	push   0x0
 805005c:	6a 00                	push   0x0
 805005e:	6a 00                	push   0x0
 8050060:	6a 00                	push   0x0
 8050062:	6a 00                	push   0x0
 8050064:	6a 00                	push   0x0
 8050066:	6a 00                	push   0x0
 8050068:	6a 00                	push   0x0
 805006a:	6a 00                	push   0x0
 805006c:	6a 00                	push   0x0
 805006e:	6a 00                	push   0x0
 8050070:	6a 00                	push   0x0
 8050072:	6a 00                	push   0x0
 8050074:	6a 00                	push   0x0
 8050076:	6a 00                	push   0x0
 8050078:	6a 20                	push   0x20

0805007a <..@3552._1>:
 805007a:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 805007f:	75 08                	jne    8050089 <..@3552._2>
 8050081:	ff 0c 24             	dec    DWORD PTR [esp]
 8050084:	8f 04 24             	pop    DWORD PTR [esp]
 8050087:	eb f1                	jmp    805007a <..@3552._1>

08050089 <..@3552._2>:
 8050089:	60                   	pusha  
 805008a:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 805008e:	89 e2                	mov    edx,esp
 8050090:	83 c2 28             	add    edx,0x28
 8050093:	89 cb                	mov    ebx,ecx
 8050095:	90                   	nop
 8050096:	60                   	pusha  
 8050097:	89 d9                	mov    ecx,ebx

08050099 <..@3551._2>:
 8050099:	83 f9 01             	cmp    ecx,0x1
 805009c:	7c 34                	jl     80500d2 <..@3551._1>
 805009e:	b8 00 00 00 00       	mov    eax,0x0
 80500a3:	8b 02                	mov    eax,DWORD PTR [edx]
 80500a5:	e8 3f f4 ff ff       	call   804f4e9 <__best_dsput_one>
 80500aa:	83 c2 04             	add    edx,0x4
 80500ad:	49                   	dec    ecx
 80500ae:	83 f9 01             	cmp    ecx,0x1
 80500b1:	7c 1f                	jl     80500d2 <..@3551._1>
 80500b3:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80500b8:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 80500bd:	b0 20                	mov    al,0x20
 80500bf:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80500c3:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 80500c8:	83 ec 02             	sub    esp,0x2
 80500cb:	e8 3c fb ff ff       	call   804fc0c <__best_cput+0x2>
 80500d0:	eb c7                	jmp    8050099 <..@3551._2>

080500d2 <..@3551._1>:
 80500d2:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80500d7:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 80500dc:	b0 20                	mov    al,0x20
 80500de:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80500e2:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 80500e7:	83 ec 02             	sub    esp,0x2
 80500ea:	e8 1d fb ff ff       	call   804fc0c <__best_cput+0x2>
 80500ef:	61                   	popa   
 80500f0:	89 c8                	mov    eax,ecx
 80500f2:	bb 04 00 00 00       	mov    ebx,0x4
 80500f7:	f7 e3                	mul    ebx
 80500f9:	89 e3                	mov    ebx,esp
 80500fb:	89 de                	mov    esi,ebx
 80500fd:	89 df                	mov    edi,ebx
 80500ff:	01 c7                	add    edi,eax
 8050101:	b9 28 00 00 00       	mov    ecx,0x28
 8050106:	01 cf                	add    edi,ecx
 8050108:	01 ce                	add    esi,ecx
 805010a:	4f                   	dec    edi
 805010b:	4e                   	dec    esi
 805010c:	fd                   	std    
 805010d:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 805010f:	fc                   	cld    
 8050110:	01 c4                	add    esp,eax
 8050112:	61                   	popa   
 8050113:	83 c4 04             	add    esp,0x4
 8050116:	c3                   	ret    

08050117 <__best_wuwrite>:
 8050117:	6a 00                	push   0x0
 8050119:	6a 00                	push   0x0
 805011b:	6a 00                	push   0x0
 805011d:	6a 00                	push   0x0
 805011f:	6a 00                	push   0x0
 8050121:	6a 00                	push   0x0
 8050123:	6a 00                	push   0x0
 8050125:	6a 00                	push   0x0
 8050127:	6a 00                	push   0x0
 8050129:	6a 00                	push   0x0
 805012b:	6a 00                	push   0x0
 805012d:	6a 00                	push   0x0
 805012f:	6a 00                	push   0x0
 8050131:	6a 00                	push   0x0
 8050133:	6a 00                	push   0x0
 8050135:	6a 00                	push   0x0
 8050137:	6a 00                	push   0x0
 8050139:	6a 00                	push   0x0
 805013b:	6a 00                	push   0x0
 805013d:	6a 00                	push   0x0
 805013f:	6a 00                	push   0x0
 8050141:	6a 00                	push   0x0
 8050143:	6a 00                	push   0x0
 8050145:	6a 00                	push   0x0
 8050147:	6a 00                	push   0x0
 8050149:	6a 00                	push   0x0
 805014b:	6a 00                	push   0x0
 805014d:	6a 00                	push   0x0
 805014f:	6a 00                	push   0x0
 8050151:	6a 00                	push   0x0
 8050153:	6a 00                	push   0x0
 8050155:	6a 00                	push   0x0
 8050157:	6a 20                	push   0x20

08050159 <..@3562._1>:
 8050159:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 805015e:	75 08                	jne    8050168 <..@3562._2>
 8050160:	ff 0c 24             	dec    DWORD PTR [esp]
 8050163:	8f 04 24             	pop    DWORD PTR [esp]
 8050166:	eb f1                	jmp    8050159 <..@3562._1>

08050168 <..@3562._2>:
 8050168:	60                   	pusha  
 8050169:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 805016d:	89 e2                	mov    edx,esp
 805016f:	83 c2 28             	add    edx,0x28
 8050172:	89 cb                	mov    ebx,ecx
 8050174:	90                   	nop
 8050175:	60                   	pusha  
 8050176:	89 d9                	mov    ecx,ebx

08050178 <..@3561._2>:
 8050178:	83 f9 01             	cmp    ecx,0x1
 805017b:	7c 40                	jl     80501bd <..@3561._1>
 805017d:	b8 00 00 00 00       	mov    eax,0x0
 8050182:	8b 02                	mov    eax,DWORD PTR [edx]
 8050184:	c1 e0 08             	shl    eax,0x8
 8050187:	c1 e0 08             	shl    eax,0x8
 805018a:	c1 e8 08             	shr    eax,0x8
 805018d:	c1 e8 08             	shr    eax,0x8
 8050190:	e8 7e f3 ff ff       	call   804f513 <__best_wuput_one>
 8050195:	83 c2 02             	add    edx,0x2
 8050198:	49                   	dec    ecx
 8050199:	83 f9 01             	cmp    ecx,0x1
 805019c:	7c 1f                	jl     80501bd <..@3561._1>
 805019e:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80501a3:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 80501a8:	b0 20                	mov    al,0x20
 80501aa:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80501ae:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 80501b3:	83 ec 02             	sub    esp,0x2
 80501b6:	e8 51 fa ff ff       	call   804fc0c <__best_cput+0x2>
 80501bb:	eb bb                	jmp    8050178 <..@3561._2>

080501bd <..@3561._1>:
 80501bd:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80501c2:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 80501c7:	b0 20                	mov    al,0x20
 80501c9:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80501cd:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 80501d2:	83 ec 02             	sub    esp,0x2
 80501d5:	e8 32 fa ff ff       	call   804fc0c <__best_cput+0x2>
 80501da:	61                   	popa   
 80501db:	89 c8                	mov    eax,ecx
 80501dd:	bb 02 00 00 00       	mov    ebx,0x2
 80501e2:	f7 e3                	mul    ebx
 80501e4:	89 e3                	mov    ebx,esp
 80501e6:	89 de                	mov    esi,ebx
 80501e8:	89 df                	mov    edi,ebx
 80501ea:	01 c7                	add    edi,eax
 80501ec:	b9 28 00 00 00       	mov    ecx,0x28
 80501f1:	01 cf                	add    edi,ecx
 80501f3:	01 ce                	add    esi,ecx
 80501f5:	4f                   	dec    edi
 80501f6:	4e                   	dec    esi
 80501f7:	fd                   	std    
 80501f8:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 80501fa:	fc                   	cld    
 80501fb:	01 c4                	add    esp,eax
 80501fd:	61                   	popa   
 80501fe:	83 c4 04             	add    esp,0x4
 8050201:	c3                   	ret    

08050202 <__best_wswrite>:
 8050202:	6a 00                	push   0x0
 8050204:	6a 00                	push   0x0
 8050206:	6a 00                	push   0x0
 8050208:	6a 00                	push   0x0
 805020a:	6a 00                	push   0x0
 805020c:	6a 00                	push   0x0
 805020e:	6a 00                	push   0x0
 8050210:	6a 00                	push   0x0
 8050212:	6a 00                	push   0x0
 8050214:	6a 00                	push   0x0
 8050216:	6a 00                	push   0x0
 8050218:	6a 00                	push   0x0
 805021a:	6a 00                	push   0x0
 805021c:	6a 00                	push   0x0
 805021e:	6a 00                	push   0x0
 8050220:	6a 00                	push   0x0
 8050222:	6a 00                	push   0x0
 8050224:	6a 00                	push   0x0
 8050226:	6a 00                	push   0x0
 8050228:	6a 00                	push   0x0
 805022a:	6a 00                	push   0x0
 805022c:	6a 00                	push   0x0
 805022e:	6a 00                	push   0x0
 8050230:	6a 00                	push   0x0
 8050232:	6a 00                	push   0x0
 8050234:	6a 00                	push   0x0
 8050236:	6a 00                	push   0x0
 8050238:	6a 00                	push   0x0
 805023a:	6a 00                	push   0x0
 805023c:	6a 00                	push   0x0
 805023e:	6a 00                	push   0x0
 8050240:	6a 00                	push   0x0
 8050242:	6a 20                	push   0x20

08050244 <..@3572._1>:
 8050244:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 8050249:	75 08                	jne    8050253 <..@3572._2>
 805024b:	ff 0c 24             	dec    DWORD PTR [esp]
 805024e:	8f 04 24             	pop    DWORD PTR [esp]
 8050251:	eb f1                	jmp    8050244 <..@3572._1>

08050253 <..@3572._2>:
 8050253:	60                   	pusha  
 8050254:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8050258:	89 e2                	mov    edx,esp
 805025a:	83 c2 28             	add    edx,0x28
 805025d:	89 cb                	mov    ebx,ecx
 805025f:	90                   	nop
 8050260:	60                   	pusha  
 8050261:	89 d9                	mov    ecx,ebx

08050263 <..@3571._2>:
 8050263:	83 f9 01             	cmp    ecx,0x1
 8050266:	7c 40                	jl     80502a8 <..@3571._1>
 8050268:	b8 00 00 00 00       	mov    eax,0x0
 805026d:	8b 02                	mov    eax,DWORD PTR [edx]
 805026f:	c1 e0 08             	shl    eax,0x8
 8050272:	c1 e0 08             	shl    eax,0x8
 8050275:	c1 e8 08             	shr    eax,0x8
 8050278:	c1 e8 08             	shr    eax,0x8
 805027b:	e8 99 f2 ff ff       	call   804f519 <__best_wsput_one>
 8050280:	83 c2 02             	add    edx,0x2
 8050283:	49                   	dec    ecx
 8050284:	83 f9 01             	cmp    ecx,0x1
 8050287:	7c 1f                	jl     80502a8 <..@3571._1>
 8050289:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 805028e:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 8050293:	b0 20                	mov    al,0x20
 8050295:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8050299:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 805029e:	83 ec 02             	sub    esp,0x2
 80502a1:	e8 66 f9 ff ff       	call   804fc0c <__best_cput+0x2>
 80502a6:	eb bb                	jmp    8050263 <..@3571._2>

080502a8 <..@3571._1>:
 80502a8:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80502ad:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 80502b2:	b0 20                	mov    al,0x20
 80502b4:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80502b8:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 80502bd:	83 ec 02             	sub    esp,0x2
 80502c0:	e8 47 f9 ff ff       	call   804fc0c <__best_cput+0x2>
 80502c5:	61                   	popa   
 80502c6:	89 c8                	mov    eax,ecx
 80502c8:	bb 02 00 00 00       	mov    ebx,0x2
 80502cd:	f7 e3                	mul    ebx
 80502cf:	89 e3                	mov    ebx,esp
 80502d1:	89 de                	mov    esi,ebx
 80502d3:	89 df                	mov    edi,ebx
 80502d5:	01 c7                	add    edi,eax
 80502d7:	b9 28 00 00 00       	mov    ecx,0x28
 80502dc:	01 cf                	add    edi,ecx
 80502de:	01 ce                	add    esi,ecx
 80502e0:	4f                   	dec    edi
 80502e1:	4e                   	dec    esi
 80502e2:	fd                   	std    
 80502e3:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 80502e5:	fc                   	cld    
 80502e6:	01 c4                	add    esp,eax
 80502e8:	61                   	popa   
 80502e9:	83 c4 04             	add    esp,0x4
 80502ec:	c3                   	ret    

080502ed <__best_buwrite>:
 80502ed:	6a 00                	push   0x0
 80502ef:	6a 00                	push   0x0
 80502f1:	6a 00                	push   0x0
 80502f3:	6a 00                	push   0x0
 80502f5:	6a 00                	push   0x0
 80502f7:	6a 00                	push   0x0
 80502f9:	6a 00                	push   0x0
 80502fb:	6a 00                	push   0x0
 80502fd:	6a 00                	push   0x0
 80502ff:	6a 00                	push   0x0
 8050301:	6a 00                	push   0x0
 8050303:	6a 00                	push   0x0
 8050305:	6a 00                	push   0x0
 8050307:	6a 00                	push   0x0
 8050309:	6a 00                	push   0x0
 805030b:	6a 00                	push   0x0
 805030d:	6a 00                	push   0x0
 805030f:	6a 00                	push   0x0
 8050311:	6a 00                	push   0x0
 8050313:	6a 00                	push   0x0
 8050315:	6a 00                	push   0x0
 8050317:	6a 00                	push   0x0
 8050319:	6a 00                	push   0x0
 805031b:	6a 00                	push   0x0
 805031d:	6a 00                	push   0x0
 805031f:	6a 00                	push   0x0
 8050321:	6a 00                	push   0x0
 8050323:	6a 00                	push   0x0
 8050325:	6a 00                	push   0x0
 8050327:	6a 00                	push   0x0
 8050329:	6a 00                	push   0x0
 805032b:	6a 00                	push   0x0
 805032d:	6a 20                	push   0x20

0805032f <..@3582._1>:
 805032f:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 8050334:	75 08                	jne    805033e <..@3582._2>
 8050336:	ff 0c 24             	dec    DWORD PTR [esp]
 8050339:	8f 04 24             	pop    DWORD PTR [esp]
 805033c:	eb f1                	jmp    805032f <..@3582._1>

0805033e <..@3582._2>:
 805033e:	60                   	pusha  
 805033f:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8050343:	89 e2                	mov    edx,esp
 8050345:	83 c2 28             	add    edx,0x28
 8050348:	89 cb                	mov    ebx,ecx
 805034a:	90                   	nop
 805034b:	60                   	pusha  
 805034c:	89 d9                	mov    ecx,ebx

0805034e <..@3581._2>:
 805034e:	83 f9 01             	cmp    ecx,0x1
 8050351:	7c 40                	jl     8050393 <..@3581._1>
 8050353:	b8 00 00 00 00       	mov    eax,0x0
 8050358:	8b 02                	mov    eax,DWORD PTR [edx]
 805035a:	c1 e0 08             	shl    eax,0x8
 805035d:	c1 e0 08             	shl    eax,0x8
 8050360:	c1 e8 08             	shr    eax,0x8
 8050363:	c1 e8 08             	shr    eax,0x8
 8050366:	e8 e4 f1 ff ff       	call   804f54f <__best_buput_one>
 805036b:	83 c2 02             	add    edx,0x2
 805036e:	49                   	dec    ecx
 805036f:	83 f9 01             	cmp    ecx,0x1
 8050372:	7c 1f                	jl     8050393 <..@3581._1>
 8050374:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8050379:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 805037e:	b0 20                	mov    al,0x20
 8050380:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8050384:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 8050389:	83 ec 02             	sub    esp,0x2
 805038c:	e8 7b f8 ff ff       	call   804fc0c <__best_cput+0x2>
 8050391:	eb bb                	jmp    805034e <..@3581._2>

08050393 <..@3581._1>:
 8050393:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8050398:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 805039d:	b0 20                	mov    al,0x20
 805039f:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80503a3:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 80503a8:	83 ec 02             	sub    esp,0x2
 80503ab:	e8 5c f8 ff ff       	call   804fc0c <__best_cput+0x2>
 80503b0:	61                   	popa   
 80503b1:	89 c8                	mov    eax,ecx
 80503b3:	bb 02 00 00 00       	mov    ebx,0x2
 80503b8:	f7 e3                	mul    ebx
 80503ba:	89 e3                	mov    ebx,esp
 80503bc:	89 de                	mov    esi,ebx
 80503be:	89 df                	mov    edi,ebx
 80503c0:	01 c7                	add    edi,eax
 80503c2:	b9 28 00 00 00       	mov    ecx,0x28
 80503c7:	01 cf                	add    edi,ecx
 80503c9:	01 ce                	add    esi,ecx
 80503cb:	4f                   	dec    edi
 80503cc:	4e                   	dec    esi
 80503cd:	fd                   	std    
 80503ce:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 80503d0:	fc                   	cld    
 80503d1:	01 c4                	add    esp,eax
 80503d3:	61                   	popa   
 80503d4:	83 c4 04             	add    esp,0x4
 80503d7:	c3                   	ret    

080503d8 <__best_bswrite>:
 80503d8:	6a 00                	push   0x0
 80503da:	6a 00                	push   0x0
 80503dc:	6a 00                	push   0x0
 80503de:	6a 00                	push   0x0
 80503e0:	6a 00                	push   0x0
 80503e2:	6a 00                	push   0x0
 80503e4:	6a 00                	push   0x0
 80503e6:	6a 00                	push   0x0
 80503e8:	6a 00                	push   0x0
 80503ea:	6a 00                	push   0x0
 80503ec:	6a 00                	push   0x0
 80503ee:	6a 00                	push   0x0
 80503f0:	6a 00                	push   0x0
 80503f2:	6a 00                	push   0x0
 80503f4:	6a 00                	push   0x0
 80503f6:	6a 00                	push   0x0
 80503f8:	6a 00                	push   0x0
 80503fa:	6a 00                	push   0x0
 80503fc:	6a 00                	push   0x0
 80503fe:	6a 00                	push   0x0
 8050400:	6a 00                	push   0x0
 8050402:	6a 00                	push   0x0
 8050404:	6a 00                	push   0x0
 8050406:	6a 00                	push   0x0
 8050408:	6a 00                	push   0x0
 805040a:	6a 00                	push   0x0
 805040c:	6a 00                	push   0x0
 805040e:	6a 00                	push   0x0
 8050410:	6a 00                	push   0x0
 8050412:	6a 00                	push   0x0
 8050414:	6a 00                	push   0x0
 8050416:	6a 00                	push   0x0
 8050418:	6a 20                	push   0x20

0805041a <..@3592._1>:
 805041a:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 805041f:	75 08                	jne    8050429 <..@3592._2>
 8050421:	ff 0c 24             	dec    DWORD PTR [esp]
 8050424:	8f 04 24             	pop    DWORD PTR [esp]
 8050427:	eb f1                	jmp    805041a <..@3592._1>

08050429 <..@3592._2>:
 8050429:	60                   	pusha  
 805042a:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 805042e:	89 e2                	mov    edx,esp
 8050430:	83 c2 28             	add    edx,0x28
 8050433:	89 cb                	mov    ebx,ecx
 8050435:	90                   	nop
 8050436:	60                   	pusha  
 8050437:	89 d9                	mov    ecx,ebx

08050439 <..@3591._2>:
 8050439:	83 f9 01             	cmp    ecx,0x1
 805043c:	7c 40                	jl     805047e <..@3591._1>
 805043e:	b8 00 00 00 00       	mov    eax,0x0
 8050443:	8b 02                	mov    eax,DWORD PTR [edx]
 8050445:	c1 e0 08             	shl    eax,0x8
 8050448:	c1 e0 08             	shl    eax,0x8
 805044b:	c1 e8 08             	shr    eax,0x8
 805044e:	c1 e8 08             	shr    eax,0x8
 8050451:	e8 ff f0 ff ff       	call   804f555 <__best_bsput_one>
 8050456:	83 c2 02             	add    edx,0x2
 8050459:	49                   	dec    ecx
 805045a:	83 f9 01             	cmp    ecx,0x1
 805045d:	7c 1f                	jl     805047e <..@3591._1>
 805045f:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8050464:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 8050469:	b0 20                	mov    al,0x20
 805046b:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 805046f:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 8050474:	83 ec 02             	sub    esp,0x2
 8050477:	e8 90 f7 ff ff       	call   804fc0c <__best_cput+0x2>
 805047c:	eb bb                	jmp    8050439 <..@3591._2>

0805047e <..@3591._1>:
 805047e:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8050483:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 8050488:	b0 20                	mov    al,0x20
 805048a:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 805048e:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 8050493:	83 ec 02             	sub    esp,0x2
 8050496:	e8 71 f7 ff ff       	call   804fc0c <__best_cput+0x2>
 805049b:	61                   	popa   
 805049c:	89 c8                	mov    eax,ecx
 805049e:	bb 02 00 00 00       	mov    ebx,0x2
 80504a3:	f7 e3                	mul    ebx
 80504a5:	89 e3                	mov    ebx,esp
 80504a7:	89 de                	mov    esi,ebx
 80504a9:	89 df                	mov    edi,ebx
 80504ab:	01 c7                	add    edi,eax
 80504ad:	b9 28 00 00 00       	mov    ecx,0x28
 80504b2:	01 cf                	add    edi,ecx
 80504b4:	01 ce                	add    esi,ecx
 80504b6:	4f                   	dec    edi
 80504b7:	4e                   	dec    esi
 80504b8:	fd                   	std    
 80504b9:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 80504bb:	fc                   	cld    
 80504bc:	01 c4                	add    esp,eax
 80504be:	61                   	popa   
 80504bf:	83 c4 04             	add    esp,0x4
 80504c2:	c3                   	ret    

080504c3 <__best_cwrite>:
 80504c3:	6a 00                	push   0x0
 80504c5:	6a 00                	push   0x0
 80504c7:	6a 00                	push   0x0
 80504c9:	6a 00                	push   0x0
 80504cb:	6a 00                	push   0x0
 80504cd:	6a 00                	push   0x0
 80504cf:	6a 00                	push   0x0
 80504d1:	6a 00                	push   0x0
 80504d3:	6a 00                	push   0x0
 80504d5:	6a 00                	push   0x0
 80504d7:	6a 00                	push   0x0
 80504d9:	6a 00                	push   0x0
 80504db:	6a 00                	push   0x0
 80504dd:	6a 00                	push   0x0
 80504df:	6a 00                	push   0x0
 80504e1:	6a 00                	push   0x0
 80504e3:	6a 00                	push   0x0
 80504e5:	6a 00                	push   0x0
 80504e7:	6a 00                	push   0x0
 80504e9:	6a 00                	push   0x0
 80504eb:	6a 00                	push   0x0
 80504ed:	6a 00                	push   0x0
 80504ef:	6a 00                	push   0x0
 80504f1:	6a 00                	push   0x0
 80504f3:	6a 00                	push   0x0
 80504f5:	6a 00                	push   0x0
 80504f7:	6a 00                	push   0x0
 80504f9:	6a 00                	push   0x0
 80504fb:	6a 00                	push   0x0
 80504fd:	6a 00                	push   0x0
 80504ff:	6a 00                	push   0x0
 8050501:	6a 00                	push   0x0
 8050503:	6a 20                	push   0x20

08050505 <..@3602._1>:
 8050505:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 805050a:	75 08                	jne    8050514 <..@3602._2>
 805050c:	ff 0c 24             	dec    DWORD PTR [esp]
 805050f:	8f 04 24             	pop    DWORD PTR [esp]
 8050512:	eb f1                	jmp    8050505 <..@3602._1>

08050514 <..@3602._2>:
 8050514:	60                   	pusha  
 8050515:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8050519:	89 e2                	mov    edx,esp
 805051b:	83 c2 28             	add    edx,0x28
 805051e:	89 cb                	mov    ebx,ecx
 8050520:	90                   	nop
 8050521:	60                   	pusha  
 8050522:	89 d9                	mov    ecx,ebx

08050524 <..@3601._2>:
 8050524:	83 f9 01             	cmp    ecx,0x1
 8050527:	7c 40                	jl     8050569 <..@3601._1>
 8050529:	b8 00 00 00 00       	mov    eax,0x0
 805052e:	8b 02                	mov    eax,DWORD PTR [edx]
 8050530:	c1 e0 08             	shl    eax,0x8
 8050533:	c1 e0 08             	shl    eax,0x8
 8050536:	c1 e8 08             	shr    eax,0x8
 8050539:	c1 e8 08             	shr    eax,0x8
 805053c:	e8 50 f0 ff ff       	call   804f591 <__best_cput_one>
 8050541:	83 c2 02             	add    edx,0x2
 8050544:	49                   	dec    ecx
 8050545:	83 f9 01             	cmp    ecx,0x1
 8050548:	7c 1f                	jl     8050569 <..@3601._1>
 805054a:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 805054f:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 8050554:	b0 20                	mov    al,0x20
 8050556:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 805055a:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 805055f:	83 ec 02             	sub    esp,0x2
 8050562:	e8 a5 f6 ff ff       	call   804fc0c <__best_cput+0x2>
 8050567:	eb bb                	jmp    8050524 <..@3601._2>

08050569 <..@3601._1>:
 8050569:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 805056e:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 8050573:	b0 20                	mov    al,0x20
 8050575:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8050579:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 805057e:	83 ec 02             	sub    esp,0x2
 8050581:	e8 86 f6 ff ff       	call   804fc0c <__best_cput+0x2>
 8050586:	61                   	popa   
 8050587:	89 c8                	mov    eax,ecx
 8050589:	bb 02 00 00 00       	mov    ebx,0x2
 805058e:	f7 e3                	mul    ebx
 8050590:	89 e3                	mov    ebx,esp
 8050592:	89 de                	mov    esi,ebx
 8050594:	89 df                	mov    edi,ebx
 8050596:	01 c7                	add    edi,eax
 8050598:	b9 28 00 00 00       	mov    ecx,0x28
 805059d:	01 cf                	add    edi,ecx
 805059f:	01 ce                	add    esi,ecx
 80505a1:	4f                   	dec    edi
 80505a2:	4e                   	dec    esi
 80505a3:	fd                   	std    
 80505a4:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 80505a6:	fc                   	cld    
 80505a7:	01 c4                	add    esp,eax
 80505a9:	61                   	popa   
 80505aa:	83 c4 04             	add    esp,0x4
 80505ad:	c3                   	ret    

080505ae <__best_swrite>:
 80505ae:	6a 00                	push   0x0
 80505b0:	6a 00                	push   0x0
 80505b2:	6a 00                	push   0x0
 80505b4:	6a 00                	push   0x0
 80505b6:	6a 00                	push   0x0
 80505b8:	6a 00                	push   0x0
 80505ba:	6a 00                	push   0x0
 80505bc:	6a 00                	push   0x0
 80505be:	6a 00                	push   0x0
 80505c0:	6a 00                	push   0x0
 80505c2:	6a 00                	push   0x0
 80505c4:	6a 00                	push   0x0
 80505c6:	6a 00                	push   0x0
 80505c8:	6a 00                	push   0x0
 80505ca:	6a 00                	push   0x0
 80505cc:	6a 00                	push   0x0
 80505ce:	6a 00                	push   0x0
 80505d0:	6a 00                	push   0x0
 80505d2:	6a 00                	push   0x0
 80505d4:	6a 00                	push   0x0
 80505d6:	6a 00                	push   0x0
 80505d8:	6a 00                	push   0x0
 80505da:	6a 00                	push   0x0
 80505dc:	6a 00                	push   0x0
 80505de:	6a 00                	push   0x0
 80505e0:	6a 00                	push   0x0
 80505e2:	6a 00                	push   0x0
 80505e4:	6a 00                	push   0x0
 80505e6:	6a 00                	push   0x0
 80505e8:	6a 00                	push   0x0
 80505ea:	6a 00                	push   0x0
 80505ec:	6a 00                	push   0x0
 80505ee:	6a 20                	push   0x20

080505f0 <..@3612._1>:
 80505f0:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 80505f5:	75 08                	jne    80505ff <..@3612._2>
 80505f7:	ff 0c 24             	dec    DWORD PTR [esp]
 80505fa:	8f 04 24             	pop    DWORD PTR [esp]
 80505fd:	eb f1                	jmp    80505f0 <..@3612._1>

080505ff <..@3612._2>:
 80505ff:	60                   	pusha  
 8050600:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8050604:	89 e2                	mov    edx,esp
 8050606:	83 c2 28             	add    edx,0x28
 8050609:	89 cb                	mov    ebx,ecx
 805060b:	8b 54 24 24          	mov    edx,DWORD PTR [esp+0x24]
 805060f:	01 4c 24 24          	add    DWORD PTR [esp+0x24],ecx
 8050613:	b9 00 00 00 00       	mov    ecx,0x0
 8050618:	60                   	pusha  
 8050619:	89 d9                	mov    ecx,ebx

0805061b <..@3611._2>:
 805061b:	83 f9 01             	cmp    ecx,0x1
 805061e:	7c 29                	jl     8050649 <..@3611._1>
 8050620:	b8 00 00 00 00       	mov    eax,0x0
 8050625:	8b 02                	mov    eax,DWORD PTR [edx]
 8050627:	c1 e0 08             	shl    eax,0x8
 805062a:	c1 e0 08             	shl    eax,0x8
 805062d:	c1 e0 08             	shl    eax,0x8
 8050630:	c1 e8 08             	shr    eax,0x8
 8050633:	c1 e8 08             	shr    eax,0x8
 8050636:	c1 e8 08             	shr    eax,0x8
 8050639:	e8 6e ef ff ff       	call   804f5ac <__best_sput_one>
 805063e:	83 c2 01             	add    edx,0x1
 8050641:	49                   	dec    ecx
 8050642:	83 f9 01             	cmp    ecx,0x1
 8050645:	7c 02                	jl     8050649 <..@3611._1>
 8050647:	eb d2                	jmp    805061b <..@3611._2>

08050649 <..@3611._1>:
 8050649:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 805064e:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 8050653:	b0 20                	mov    al,0x20
 8050655:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8050659:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 805065e:	83 ec 02             	sub    esp,0x2
 8050661:	e8 a6 f5 ff ff       	call   804fc0c <__best_cput+0x2>
 8050666:	61                   	popa   
 8050667:	89 c8                	mov    eax,ecx
 8050669:	bb 01 00 00 00       	mov    ebx,0x1
 805066e:	f7 e3                	mul    ebx
 8050670:	89 e3                	mov    ebx,esp
 8050672:	89 de                	mov    esi,ebx
 8050674:	89 df                	mov    edi,ebx
 8050676:	01 c7                	add    edi,eax
 8050678:	b9 28 00 00 00       	mov    ecx,0x28
 805067d:	01 cf                	add    edi,ecx
 805067f:	01 ce                	add    esi,ecx
 8050681:	4f                   	dec    edi
 8050682:	4e                   	dec    esi
 8050683:	fd                   	std    
 8050684:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8050686:	fc                   	cld    
 8050687:	01 c4                	add    esp,eax
 8050689:	61                   	popa   
 805068a:	83 c4 04             	add    esp,0x4
 805068d:	c3                   	ret    

0805068e <__best_quprint>:
 805068e:	6a 00                	push   0x0
 8050690:	6a 00                	push   0x0
 8050692:	6a 00                	push   0x0
 8050694:	6a 00                	push   0x0
 8050696:	6a 00                	push   0x0
 8050698:	6a 00                	push   0x0
 805069a:	6a 00                	push   0x0
 805069c:	6a 00                	push   0x0
 805069e:	6a 00                	push   0x0
 80506a0:	6a 00                	push   0x0
 80506a2:	6a 00                	push   0x0
 80506a4:	6a 00                	push   0x0
 80506a6:	6a 00                	push   0x0
 80506a8:	6a 00                	push   0x0
 80506aa:	6a 00                	push   0x0
 80506ac:	6a 00                	push   0x0
 80506ae:	6a 00                	push   0x0
 80506b0:	6a 00                	push   0x0
 80506b2:	6a 00                	push   0x0
 80506b4:	6a 00                	push   0x0
 80506b6:	6a 00                	push   0x0
 80506b8:	6a 00                	push   0x0
 80506ba:	6a 00                	push   0x0
 80506bc:	6a 00                	push   0x0
 80506be:	6a 00                	push   0x0
 80506c0:	6a 00                	push   0x0
 80506c2:	6a 00                	push   0x0
 80506c4:	6a 00                	push   0x0
 80506c6:	6a 00                	push   0x0
 80506c8:	6a 00                	push   0x0
 80506ca:	6a 00                	push   0x0
 80506cc:	6a 00                	push   0x0
 80506ce:	6a 20                	push   0x20

080506d0 <..@3619._1>:
 80506d0:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 80506d5:	75 08                	jne    80506df <..@3619._2>
 80506d7:	ff 0c 24             	dec    DWORD PTR [esp]
 80506da:	8f 04 24             	pop    DWORD PTR [esp]
 80506dd:	eb f1                	jmp    80506d0 <..@3619._1>

080506df <..@3619._2>:
 80506df:	60                   	pusha  
 80506e0:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 80506e4:	89 e2                	mov    edx,esp
 80506e6:	83 c2 28             	add    edx,0x28
 80506e9:	89 cb                	mov    ebx,ecx
 80506eb:	90                   	nop
 80506ec:	60                   	pusha  
 80506ed:	89 d9                	mov    ecx,ebx

080506ef <..@3618._2>:
 80506ef:	83 f9 01             	cmp    ecx,0x1
 80506f2:	7c 34                	jl     8050728 <..@3618._1>
 80506f4:	b8 00 00 00 00       	mov    eax,0x0
 80506f9:	8b 02                	mov    eax,DWORD PTR [edx]
 80506fb:	e8 b3 ed ff ff       	call   804f4b3 <__best_quput_one>
 8050700:	83 c2 08             	add    edx,0x8
 8050703:	49                   	dec    ecx
 8050704:	83 f9 01             	cmp    ecx,0x1
 8050707:	7c 1f                	jl     8050728 <..@3618._1>
 8050709:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 805070e:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 8050713:	b0 20                	mov    al,0x20
 8050715:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8050719:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 805071e:	83 ec 02             	sub    esp,0x2
 8050721:	e8 e6 f4 ff ff       	call   804fc0c <__best_cput+0x2>
 8050726:	eb c7                	jmp    80506ef <..@3618._2>

08050728 <..@3618._1>:
 8050728:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 805072d:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 8050732:	b0 0a                	mov    al,0xa
 8050734:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8050738:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 805073d:	83 ec 02             	sub    esp,0x2
 8050740:	e8 c7 f4 ff ff       	call   804fc0c <__best_cput+0x2>
 8050745:	61                   	popa   
 8050746:	89 c8                	mov    eax,ecx
 8050748:	bb 08 00 00 00       	mov    ebx,0x8
 805074d:	f7 e3                	mul    ebx
 805074f:	89 e3                	mov    ebx,esp
 8050751:	89 de                	mov    esi,ebx
 8050753:	89 df                	mov    edi,ebx
 8050755:	01 c7                	add    edi,eax
 8050757:	b9 28 00 00 00       	mov    ecx,0x28
 805075c:	01 cf                	add    edi,ecx
 805075e:	01 ce                	add    esi,ecx
 8050760:	4f                   	dec    edi
 8050761:	4e                   	dec    esi
 8050762:	fd                   	std    
 8050763:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8050765:	fc                   	cld    
 8050766:	01 c4                	add    esp,eax
 8050768:	61                   	popa   
 8050769:	83 c4 04             	add    esp,0x4
 805076c:	c3                   	ret    

0805076d <__best_qsprint>:
 805076d:	6a 00                	push   0x0
 805076f:	6a 00                	push   0x0
 8050771:	6a 00                	push   0x0
 8050773:	6a 00                	push   0x0
 8050775:	6a 00                	push   0x0
 8050777:	6a 00                	push   0x0
 8050779:	6a 00                	push   0x0
 805077b:	6a 00                	push   0x0
 805077d:	6a 00                	push   0x0
 805077f:	6a 00                	push   0x0
 8050781:	6a 00                	push   0x0
 8050783:	6a 00                	push   0x0
 8050785:	6a 00                	push   0x0
 8050787:	6a 00                	push   0x0
 8050789:	6a 00                	push   0x0
 805078b:	6a 00                	push   0x0
 805078d:	6a 00                	push   0x0
 805078f:	6a 00                	push   0x0
 8050791:	6a 00                	push   0x0
 8050793:	6a 00                	push   0x0
 8050795:	6a 00                	push   0x0
 8050797:	6a 00                	push   0x0
 8050799:	6a 00                	push   0x0
 805079b:	6a 00                	push   0x0
 805079d:	6a 00                	push   0x0
 805079f:	6a 00                	push   0x0
 80507a1:	6a 00                	push   0x0
 80507a3:	6a 00                	push   0x0
 80507a5:	6a 00                	push   0x0
 80507a7:	6a 00                	push   0x0
 80507a9:	6a 00                	push   0x0
 80507ab:	6a 00                	push   0x0
 80507ad:	6a 20                	push   0x20

080507af <..@3629._1>:
 80507af:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 80507b4:	75 08                	jne    80507be <..@3629._2>
 80507b6:	ff 0c 24             	dec    DWORD PTR [esp]
 80507b9:	8f 04 24             	pop    DWORD PTR [esp]
 80507bc:	eb f1                	jmp    80507af <..@3629._1>

080507be <..@3629._2>:
 80507be:	60                   	pusha  
 80507bf:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 80507c3:	89 e2                	mov    edx,esp
 80507c5:	83 c2 28             	add    edx,0x28
 80507c8:	89 cb                	mov    ebx,ecx
 80507ca:	90                   	nop
 80507cb:	60                   	pusha  
 80507cc:	89 d9                	mov    ecx,ebx

080507ce <..@3628._2>:
 80507ce:	83 f9 01             	cmp    ecx,0x1
 80507d1:	7c 34                	jl     8050807 <..@3628._1>
 80507d3:	b8 00 00 00 00       	mov    eax,0x0
 80507d8:	8b 02                	mov    eax,DWORD PTR [edx]
 80507da:	e8 da ec ff ff       	call   804f4b9 <__best_qsput_one>
 80507df:	83 c2 08             	add    edx,0x8
 80507e2:	49                   	dec    ecx
 80507e3:	83 f9 01             	cmp    ecx,0x1
 80507e6:	7c 1f                	jl     8050807 <..@3628._1>
 80507e8:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80507ed:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 80507f2:	b0 20                	mov    al,0x20
 80507f4:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80507f8:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 80507fd:	83 ec 02             	sub    esp,0x2
 8050800:	e8 07 f4 ff ff       	call   804fc0c <__best_cput+0x2>
 8050805:	eb c7                	jmp    80507ce <..@3628._2>

08050807 <..@3628._1>:
 8050807:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 805080c:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 8050811:	b0 0a                	mov    al,0xa
 8050813:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8050817:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 805081c:	83 ec 02             	sub    esp,0x2
 805081f:	e8 e8 f3 ff ff       	call   804fc0c <__best_cput+0x2>
 8050824:	61                   	popa   
 8050825:	89 c8                	mov    eax,ecx
 8050827:	bb 08 00 00 00       	mov    ebx,0x8
 805082c:	f7 e3                	mul    ebx
 805082e:	89 e3                	mov    ebx,esp
 8050830:	89 de                	mov    esi,ebx
 8050832:	89 df                	mov    edi,ebx
 8050834:	01 c7                	add    edi,eax
 8050836:	b9 28 00 00 00       	mov    ecx,0x28
 805083b:	01 cf                	add    edi,ecx
 805083d:	01 ce                	add    esi,ecx
 805083f:	4f                   	dec    edi
 8050840:	4e                   	dec    esi
 8050841:	fd                   	std    
 8050842:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8050844:	fc                   	cld    
 8050845:	01 c4                	add    esp,eax
 8050847:	61                   	popa   
 8050848:	83 c4 04             	add    esp,0x4
 805084b:	c3                   	ret    

0805084c <__best_duprint>:
 805084c:	6a 00                	push   0x0
 805084e:	6a 00                	push   0x0
 8050850:	6a 00                	push   0x0
 8050852:	6a 00                	push   0x0
 8050854:	6a 00                	push   0x0
 8050856:	6a 00                	push   0x0
 8050858:	6a 00                	push   0x0
 805085a:	6a 00                	push   0x0
 805085c:	6a 00                	push   0x0
 805085e:	6a 00                	push   0x0
 8050860:	6a 00                	push   0x0
 8050862:	6a 00                	push   0x0
 8050864:	6a 00                	push   0x0
 8050866:	6a 00                	push   0x0
 8050868:	6a 00                	push   0x0
 805086a:	6a 00                	push   0x0
 805086c:	6a 00                	push   0x0
 805086e:	6a 00                	push   0x0
 8050870:	6a 00                	push   0x0
 8050872:	6a 00                	push   0x0
 8050874:	6a 00                	push   0x0
 8050876:	6a 00                	push   0x0
 8050878:	6a 00                	push   0x0
 805087a:	6a 00                	push   0x0
 805087c:	6a 00                	push   0x0
 805087e:	6a 00                	push   0x0
 8050880:	6a 00                	push   0x0
 8050882:	6a 00                	push   0x0
 8050884:	6a 00                	push   0x0
 8050886:	6a 00                	push   0x0
 8050888:	6a 00                	push   0x0
 805088a:	6a 00                	push   0x0
 805088c:	6a 20                	push   0x20

0805088e <..@3639._1>:
 805088e:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 8050893:	75 08                	jne    805089d <..@3639._2>
 8050895:	ff 0c 24             	dec    DWORD PTR [esp]
 8050898:	8f 04 24             	pop    DWORD PTR [esp]
 805089b:	eb f1                	jmp    805088e <..@3639._1>

0805089d <..@3639._2>:
 805089d:	60                   	pusha  
 805089e:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 80508a2:	89 e2                	mov    edx,esp
 80508a4:	83 c2 28             	add    edx,0x28
 80508a7:	89 cb                	mov    ebx,ecx
 80508a9:	90                   	nop
 80508aa:	60                   	pusha  
 80508ab:	89 d9                	mov    ecx,ebx

080508ad <..@3638._2>:
 80508ad:	83 f9 01             	cmp    ecx,0x1
 80508b0:	7c 34                	jl     80508e6 <..@3638._1>
 80508b2:	b8 00 00 00 00       	mov    eax,0x0
 80508b7:	8b 02                	mov    eax,DWORD PTR [edx]
 80508b9:	e8 25 ec ff ff       	call   804f4e3 <__best_duput_one>
 80508be:	83 c2 04             	add    edx,0x4
 80508c1:	49                   	dec    ecx
 80508c2:	83 f9 01             	cmp    ecx,0x1
 80508c5:	7c 1f                	jl     80508e6 <..@3638._1>
 80508c7:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80508cc:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 80508d1:	b0 20                	mov    al,0x20
 80508d3:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80508d7:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 80508dc:	83 ec 02             	sub    esp,0x2
 80508df:	e8 28 f3 ff ff       	call   804fc0c <__best_cput+0x2>
 80508e4:	eb c7                	jmp    80508ad <..@3638._2>

080508e6 <..@3638._1>:
 80508e6:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80508eb:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 80508f0:	b0 0a                	mov    al,0xa
 80508f2:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80508f6:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 80508fb:	83 ec 02             	sub    esp,0x2
 80508fe:	e8 09 f3 ff ff       	call   804fc0c <__best_cput+0x2>
 8050903:	61                   	popa   
 8050904:	89 c8                	mov    eax,ecx
 8050906:	bb 04 00 00 00       	mov    ebx,0x4
 805090b:	f7 e3                	mul    ebx
 805090d:	89 e3                	mov    ebx,esp
 805090f:	89 de                	mov    esi,ebx
 8050911:	89 df                	mov    edi,ebx
 8050913:	01 c7                	add    edi,eax
 8050915:	b9 28 00 00 00       	mov    ecx,0x28
 805091a:	01 cf                	add    edi,ecx
 805091c:	01 ce                	add    esi,ecx
 805091e:	4f                   	dec    edi
 805091f:	4e                   	dec    esi
 8050920:	fd                   	std    
 8050921:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8050923:	fc                   	cld    
 8050924:	01 c4                	add    esp,eax
 8050926:	61                   	popa   
 8050927:	83 c4 04             	add    esp,0x4
 805092a:	c3                   	ret    

0805092b <__best_dsprint>:
 805092b:	6a 00                	push   0x0
 805092d:	6a 00                	push   0x0
 805092f:	6a 00                	push   0x0
 8050931:	6a 00                	push   0x0
 8050933:	6a 00                	push   0x0
 8050935:	6a 00                	push   0x0
 8050937:	6a 00                	push   0x0
 8050939:	6a 00                	push   0x0
 805093b:	6a 00                	push   0x0
 805093d:	6a 00                	push   0x0
 805093f:	6a 00                	push   0x0
 8050941:	6a 00                	push   0x0
 8050943:	6a 00                	push   0x0
 8050945:	6a 00                	push   0x0
 8050947:	6a 00                	push   0x0
 8050949:	6a 00                	push   0x0
 805094b:	6a 00                	push   0x0
 805094d:	6a 00                	push   0x0
 805094f:	6a 00                	push   0x0
 8050951:	6a 00                	push   0x0
 8050953:	6a 00                	push   0x0
 8050955:	6a 00                	push   0x0
 8050957:	6a 00                	push   0x0
 8050959:	6a 00                	push   0x0
 805095b:	6a 00                	push   0x0
 805095d:	6a 00                	push   0x0
 805095f:	6a 00                	push   0x0
 8050961:	6a 00                	push   0x0
 8050963:	6a 00                	push   0x0
 8050965:	6a 00                	push   0x0
 8050967:	6a 00                	push   0x0
 8050969:	6a 00                	push   0x0
 805096b:	6a 20                	push   0x20

0805096d <..@3649._1>:
 805096d:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 8050972:	75 08                	jne    805097c <..@3649._2>
 8050974:	ff 0c 24             	dec    DWORD PTR [esp]
 8050977:	8f 04 24             	pop    DWORD PTR [esp]
 805097a:	eb f1                	jmp    805096d <..@3649._1>

0805097c <..@3649._2>:
 805097c:	60                   	pusha  
 805097d:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8050981:	89 e2                	mov    edx,esp
 8050983:	83 c2 28             	add    edx,0x28
 8050986:	89 cb                	mov    ebx,ecx
 8050988:	90                   	nop
 8050989:	60                   	pusha  
 805098a:	89 d9                	mov    ecx,ebx

0805098c <..@3648._2>:
 805098c:	83 f9 01             	cmp    ecx,0x1
 805098f:	7c 34                	jl     80509c5 <..@3648._1>
 8050991:	b8 00 00 00 00       	mov    eax,0x0
 8050996:	8b 02                	mov    eax,DWORD PTR [edx]
 8050998:	e8 4c eb ff ff       	call   804f4e9 <__best_dsput_one>
 805099d:	83 c2 04             	add    edx,0x4
 80509a0:	49                   	dec    ecx
 80509a1:	83 f9 01             	cmp    ecx,0x1
 80509a4:	7c 1f                	jl     80509c5 <..@3648._1>
 80509a6:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80509ab:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 80509b0:	b0 20                	mov    al,0x20
 80509b2:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80509b6:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 80509bb:	83 ec 02             	sub    esp,0x2
 80509be:	e8 49 f2 ff ff       	call   804fc0c <__best_cput+0x2>
 80509c3:	eb c7                	jmp    805098c <..@3648._2>

080509c5 <..@3648._1>:
 80509c5:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 80509ca:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 80509cf:	b0 0a                	mov    al,0xa
 80509d1:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80509d5:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 80509da:	83 ec 02             	sub    esp,0x2
 80509dd:	e8 2a f2 ff ff       	call   804fc0c <__best_cput+0x2>
 80509e2:	61                   	popa   
 80509e3:	89 c8                	mov    eax,ecx
 80509e5:	bb 04 00 00 00       	mov    ebx,0x4
 80509ea:	f7 e3                	mul    ebx
 80509ec:	89 e3                	mov    ebx,esp
 80509ee:	89 de                	mov    esi,ebx
 80509f0:	89 df                	mov    edi,ebx
 80509f2:	01 c7                	add    edi,eax
 80509f4:	b9 28 00 00 00       	mov    ecx,0x28
 80509f9:	01 cf                	add    edi,ecx
 80509fb:	01 ce                	add    esi,ecx
 80509fd:	4f                   	dec    edi
 80509fe:	4e                   	dec    esi
 80509ff:	fd                   	std    
 8050a00:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8050a02:	fc                   	cld    
 8050a03:	01 c4                	add    esp,eax
 8050a05:	61                   	popa   
 8050a06:	83 c4 04             	add    esp,0x4
 8050a09:	c3                   	ret    

08050a0a <__best_wuprint>:
 8050a0a:	6a 00                	push   0x0
 8050a0c:	6a 00                	push   0x0
 8050a0e:	6a 00                	push   0x0
 8050a10:	6a 00                	push   0x0
 8050a12:	6a 00                	push   0x0
 8050a14:	6a 00                	push   0x0
 8050a16:	6a 00                	push   0x0
 8050a18:	6a 00                	push   0x0
 8050a1a:	6a 00                	push   0x0
 8050a1c:	6a 00                	push   0x0
 8050a1e:	6a 00                	push   0x0
 8050a20:	6a 00                	push   0x0
 8050a22:	6a 00                	push   0x0
 8050a24:	6a 00                	push   0x0
 8050a26:	6a 00                	push   0x0
 8050a28:	6a 00                	push   0x0
 8050a2a:	6a 00                	push   0x0
 8050a2c:	6a 00                	push   0x0
 8050a2e:	6a 00                	push   0x0
 8050a30:	6a 00                	push   0x0
 8050a32:	6a 00                	push   0x0
 8050a34:	6a 00                	push   0x0
 8050a36:	6a 00                	push   0x0
 8050a38:	6a 00                	push   0x0
 8050a3a:	6a 00                	push   0x0
 8050a3c:	6a 00                	push   0x0
 8050a3e:	6a 00                	push   0x0
 8050a40:	6a 00                	push   0x0
 8050a42:	6a 00                	push   0x0
 8050a44:	6a 00                	push   0x0
 8050a46:	6a 00                	push   0x0
 8050a48:	6a 00                	push   0x0
 8050a4a:	6a 20                	push   0x20

08050a4c <..@3659._1>:
 8050a4c:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 8050a51:	75 08                	jne    8050a5b <..@3659._2>
 8050a53:	ff 0c 24             	dec    DWORD PTR [esp]
 8050a56:	8f 04 24             	pop    DWORD PTR [esp]
 8050a59:	eb f1                	jmp    8050a4c <..@3659._1>

08050a5b <..@3659._2>:
 8050a5b:	60                   	pusha  
 8050a5c:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8050a60:	89 e2                	mov    edx,esp
 8050a62:	83 c2 28             	add    edx,0x28
 8050a65:	89 cb                	mov    ebx,ecx
 8050a67:	90                   	nop
 8050a68:	60                   	pusha  
 8050a69:	89 d9                	mov    ecx,ebx

08050a6b <..@3658._2>:
 8050a6b:	83 f9 01             	cmp    ecx,0x1
 8050a6e:	7c 40                	jl     8050ab0 <..@3658._1>
 8050a70:	b8 00 00 00 00       	mov    eax,0x0
 8050a75:	8b 02                	mov    eax,DWORD PTR [edx]
 8050a77:	c1 e0 08             	shl    eax,0x8
 8050a7a:	c1 e0 08             	shl    eax,0x8
 8050a7d:	c1 e8 08             	shr    eax,0x8
 8050a80:	c1 e8 08             	shr    eax,0x8
 8050a83:	e8 8b ea ff ff       	call   804f513 <__best_wuput_one>
 8050a88:	83 c2 02             	add    edx,0x2
 8050a8b:	49                   	dec    ecx
 8050a8c:	83 f9 01             	cmp    ecx,0x1
 8050a8f:	7c 1f                	jl     8050ab0 <..@3658._1>
 8050a91:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8050a96:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 8050a9b:	b0 20                	mov    al,0x20
 8050a9d:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8050aa1:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 8050aa6:	83 ec 02             	sub    esp,0x2
 8050aa9:	e8 5e f1 ff ff       	call   804fc0c <__best_cput+0x2>
 8050aae:	eb bb                	jmp    8050a6b <..@3658._2>

08050ab0 <..@3658._1>:
 8050ab0:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8050ab5:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 8050aba:	b0 0a                	mov    al,0xa
 8050abc:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8050ac0:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 8050ac5:	83 ec 02             	sub    esp,0x2
 8050ac8:	e8 3f f1 ff ff       	call   804fc0c <__best_cput+0x2>
 8050acd:	61                   	popa   
 8050ace:	89 c8                	mov    eax,ecx
 8050ad0:	bb 02 00 00 00       	mov    ebx,0x2
 8050ad5:	f7 e3                	mul    ebx
 8050ad7:	89 e3                	mov    ebx,esp
 8050ad9:	89 de                	mov    esi,ebx
 8050adb:	89 df                	mov    edi,ebx
 8050add:	01 c7                	add    edi,eax
 8050adf:	b9 28 00 00 00       	mov    ecx,0x28
 8050ae4:	01 cf                	add    edi,ecx
 8050ae6:	01 ce                	add    esi,ecx
 8050ae8:	4f                   	dec    edi
 8050ae9:	4e                   	dec    esi
 8050aea:	fd                   	std    
 8050aeb:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8050aed:	fc                   	cld    
 8050aee:	01 c4                	add    esp,eax
 8050af0:	61                   	popa   
 8050af1:	83 c4 04             	add    esp,0x4
 8050af4:	c3                   	ret    

08050af5 <__best_wsprint>:
 8050af5:	6a 00                	push   0x0
 8050af7:	6a 00                	push   0x0
 8050af9:	6a 00                	push   0x0
 8050afb:	6a 00                	push   0x0
 8050afd:	6a 00                	push   0x0
 8050aff:	6a 00                	push   0x0
 8050b01:	6a 00                	push   0x0
 8050b03:	6a 00                	push   0x0
 8050b05:	6a 00                	push   0x0
 8050b07:	6a 00                	push   0x0
 8050b09:	6a 00                	push   0x0
 8050b0b:	6a 00                	push   0x0
 8050b0d:	6a 00                	push   0x0
 8050b0f:	6a 00                	push   0x0
 8050b11:	6a 00                	push   0x0
 8050b13:	6a 00                	push   0x0
 8050b15:	6a 00                	push   0x0
 8050b17:	6a 00                	push   0x0
 8050b19:	6a 00                	push   0x0
 8050b1b:	6a 00                	push   0x0
 8050b1d:	6a 00                	push   0x0
 8050b1f:	6a 00                	push   0x0
 8050b21:	6a 00                	push   0x0
 8050b23:	6a 00                	push   0x0
 8050b25:	6a 00                	push   0x0
 8050b27:	6a 00                	push   0x0
 8050b29:	6a 00                	push   0x0
 8050b2b:	6a 00                	push   0x0
 8050b2d:	6a 00                	push   0x0
 8050b2f:	6a 00                	push   0x0
 8050b31:	6a 00                	push   0x0
 8050b33:	6a 00                	push   0x0
 8050b35:	6a 20                	push   0x20

08050b37 <..@3669._1>:
 8050b37:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 8050b3c:	75 08                	jne    8050b46 <..@3669._2>
 8050b3e:	ff 0c 24             	dec    DWORD PTR [esp]
 8050b41:	8f 04 24             	pop    DWORD PTR [esp]
 8050b44:	eb f1                	jmp    8050b37 <..@3669._1>

08050b46 <..@3669._2>:
 8050b46:	60                   	pusha  
 8050b47:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8050b4b:	89 e2                	mov    edx,esp
 8050b4d:	83 c2 28             	add    edx,0x28
 8050b50:	89 cb                	mov    ebx,ecx
 8050b52:	90                   	nop
 8050b53:	60                   	pusha  
 8050b54:	89 d9                	mov    ecx,ebx

08050b56 <..@3668._2>:
 8050b56:	83 f9 01             	cmp    ecx,0x1
 8050b59:	7c 40                	jl     8050b9b <..@3668._1>
 8050b5b:	b8 00 00 00 00       	mov    eax,0x0
 8050b60:	8b 02                	mov    eax,DWORD PTR [edx]
 8050b62:	c1 e0 08             	shl    eax,0x8
 8050b65:	c1 e0 08             	shl    eax,0x8
 8050b68:	c1 e8 08             	shr    eax,0x8
 8050b6b:	c1 e8 08             	shr    eax,0x8
 8050b6e:	e8 a6 e9 ff ff       	call   804f519 <__best_wsput_one>
 8050b73:	83 c2 02             	add    edx,0x2
 8050b76:	49                   	dec    ecx
 8050b77:	83 f9 01             	cmp    ecx,0x1
 8050b7a:	7c 1f                	jl     8050b9b <..@3668._1>
 8050b7c:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8050b81:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 8050b86:	b0 20                	mov    al,0x20
 8050b88:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8050b8c:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 8050b91:	83 ec 02             	sub    esp,0x2
 8050b94:	e8 73 f0 ff ff       	call   804fc0c <__best_cput+0x2>
 8050b99:	eb bb                	jmp    8050b56 <..@3668._2>

08050b9b <..@3668._1>:
 8050b9b:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8050ba0:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 8050ba5:	b0 0a                	mov    al,0xa
 8050ba7:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8050bab:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 8050bb0:	83 ec 02             	sub    esp,0x2
 8050bb3:	e8 54 f0 ff ff       	call   804fc0c <__best_cput+0x2>
 8050bb8:	61                   	popa   
 8050bb9:	89 c8                	mov    eax,ecx
 8050bbb:	bb 02 00 00 00       	mov    ebx,0x2
 8050bc0:	f7 e3                	mul    ebx
 8050bc2:	89 e3                	mov    ebx,esp
 8050bc4:	89 de                	mov    esi,ebx
 8050bc6:	89 df                	mov    edi,ebx
 8050bc8:	01 c7                	add    edi,eax
 8050bca:	b9 28 00 00 00       	mov    ecx,0x28
 8050bcf:	01 cf                	add    edi,ecx
 8050bd1:	01 ce                	add    esi,ecx
 8050bd3:	4f                   	dec    edi
 8050bd4:	4e                   	dec    esi
 8050bd5:	fd                   	std    
 8050bd6:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8050bd8:	fc                   	cld    
 8050bd9:	01 c4                	add    esp,eax
 8050bdb:	61                   	popa   
 8050bdc:	83 c4 04             	add    esp,0x4
 8050bdf:	c3                   	ret    

08050be0 <__best_buprint>:
 8050be0:	6a 00                	push   0x0
 8050be2:	6a 00                	push   0x0
 8050be4:	6a 00                	push   0x0
 8050be6:	6a 00                	push   0x0
 8050be8:	6a 00                	push   0x0
 8050bea:	6a 00                	push   0x0
 8050bec:	6a 00                	push   0x0
 8050bee:	6a 00                	push   0x0
 8050bf0:	6a 00                	push   0x0
 8050bf2:	6a 00                	push   0x0
 8050bf4:	6a 00                	push   0x0
 8050bf6:	6a 00                	push   0x0
 8050bf8:	6a 00                	push   0x0
 8050bfa:	6a 00                	push   0x0
 8050bfc:	6a 00                	push   0x0
 8050bfe:	6a 00                	push   0x0
 8050c00:	6a 00                	push   0x0
 8050c02:	6a 00                	push   0x0
 8050c04:	6a 00                	push   0x0
 8050c06:	6a 00                	push   0x0
 8050c08:	6a 00                	push   0x0
 8050c0a:	6a 00                	push   0x0
 8050c0c:	6a 00                	push   0x0
 8050c0e:	6a 00                	push   0x0
 8050c10:	6a 00                	push   0x0
 8050c12:	6a 00                	push   0x0
 8050c14:	6a 00                	push   0x0
 8050c16:	6a 00                	push   0x0
 8050c18:	6a 00                	push   0x0
 8050c1a:	6a 00                	push   0x0
 8050c1c:	6a 00                	push   0x0
 8050c1e:	6a 00                	push   0x0
 8050c20:	6a 20                	push   0x20

08050c22 <..@3679._1>:
 8050c22:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 8050c27:	75 08                	jne    8050c31 <..@3679._2>
 8050c29:	ff 0c 24             	dec    DWORD PTR [esp]
 8050c2c:	8f 04 24             	pop    DWORD PTR [esp]
 8050c2f:	eb f1                	jmp    8050c22 <..@3679._1>

08050c31 <..@3679._2>:
 8050c31:	60                   	pusha  
 8050c32:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8050c36:	89 e2                	mov    edx,esp
 8050c38:	83 c2 28             	add    edx,0x28
 8050c3b:	89 cb                	mov    ebx,ecx
 8050c3d:	90                   	nop
 8050c3e:	60                   	pusha  
 8050c3f:	89 d9                	mov    ecx,ebx

08050c41 <..@3678._2>:
 8050c41:	83 f9 01             	cmp    ecx,0x1
 8050c44:	7c 40                	jl     8050c86 <..@3678._1>
 8050c46:	b8 00 00 00 00       	mov    eax,0x0
 8050c4b:	8b 02                	mov    eax,DWORD PTR [edx]
 8050c4d:	c1 e0 08             	shl    eax,0x8
 8050c50:	c1 e0 08             	shl    eax,0x8
 8050c53:	c1 e8 08             	shr    eax,0x8
 8050c56:	c1 e8 08             	shr    eax,0x8
 8050c59:	e8 f1 e8 ff ff       	call   804f54f <__best_buput_one>
 8050c5e:	83 c2 02             	add    edx,0x2
 8050c61:	49                   	dec    ecx
 8050c62:	83 f9 01             	cmp    ecx,0x1
 8050c65:	7c 1f                	jl     8050c86 <..@3678._1>
 8050c67:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8050c6c:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 8050c71:	b0 20                	mov    al,0x20
 8050c73:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8050c77:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 8050c7c:	83 ec 02             	sub    esp,0x2
 8050c7f:	e8 88 ef ff ff       	call   804fc0c <__best_cput+0x2>
 8050c84:	eb bb                	jmp    8050c41 <..@3678._2>

08050c86 <..@3678._1>:
 8050c86:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8050c8b:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 8050c90:	b0 0a                	mov    al,0xa
 8050c92:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8050c96:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 8050c9b:	83 ec 02             	sub    esp,0x2
 8050c9e:	e8 69 ef ff ff       	call   804fc0c <__best_cput+0x2>
 8050ca3:	61                   	popa   
 8050ca4:	89 c8                	mov    eax,ecx
 8050ca6:	bb 02 00 00 00       	mov    ebx,0x2
 8050cab:	f7 e3                	mul    ebx
 8050cad:	89 e3                	mov    ebx,esp
 8050caf:	89 de                	mov    esi,ebx
 8050cb1:	89 df                	mov    edi,ebx
 8050cb3:	01 c7                	add    edi,eax
 8050cb5:	b9 28 00 00 00       	mov    ecx,0x28
 8050cba:	01 cf                	add    edi,ecx
 8050cbc:	01 ce                	add    esi,ecx
 8050cbe:	4f                   	dec    edi
 8050cbf:	4e                   	dec    esi
 8050cc0:	fd                   	std    
 8050cc1:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8050cc3:	fc                   	cld    
 8050cc4:	01 c4                	add    esp,eax
 8050cc6:	61                   	popa   
 8050cc7:	83 c4 04             	add    esp,0x4
 8050cca:	c3                   	ret    

08050ccb <__best_bsprint>:
 8050ccb:	6a 00                	push   0x0
 8050ccd:	6a 00                	push   0x0
 8050ccf:	6a 00                	push   0x0
 8050cd1:	6a 00                	push   0x0
 8050cd3:	6a 00                	push   0x0
 8050cd5:	6a 00                	push   0x0
 8050cd7:	6a 00                	push   0x0
 8050cd9:	6a 00                	push   0x0
 8050cdb:	6a 00                	push   0x0
 8050cdd:	6a 00                	push   0x0
 8050cdf:	6a 00                	push   0x0
 8050ce1:	6a 00                	push   0x0
 8050ce3:	6a 00                	push   0x0
 8050ce5:	6a 00                	push   0x0
 8050ce7:	6a 00                	push   0x0
 8050ce9:	6a 00                	push   0x0
 8050ceb:	6a 00                	push   0x0
 8050ced:	6a 00                	push   0x0
 8050cef:	6a 00                	push   0x0
 8050cf1:	6a 00                	push   0x0
 8050cf3:	6a 00                	push   0x0
 8050cf5:	6a 00                	push   0x0
 8050cf7:	6a 00                	push   0x0
 8050cf9:	6a 00                	push   0x0
 8050cfb:	6a 00                	push   0x0
 8050cfd:	6a 00                	push   0x0
 8050cff:	6a 00                	push   0x0
 8050d01:	6a 00                	push   0x0
 8050d03:	6a 00                	push   0x0
 8050d05:	6a 00                	push   0x0
 8050d07:	6a 00                	push   0x0
 8050d09:	6a 00                	push   0x0
 8050d0b:	6a 20                	push   0x20

08050d0d <..@3689._1>:
 8050d0d:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 8050d12:	75 08                	jne    8050d1c <..@3689._2>
 8050d14:	ff 0c 24             	dec    DWORD PTR [esp]
 8050d17:	8f 04 24             	pop    DWORD PTR [esp]
 8050d1a:	eb f1                	jmp    8050d0d <..@3689._1>

08050d1c <..@3689._2>:
 8050d1c:	60                   	pusha  
 8050d1d:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8050d21:	89 e2                	mov    edx,esp
 8050d23:	83 c2 28             	add    edx,0x28
 8050d26:	89 cb                	mov    ebx,ecx
 8050d28:	90                   	nop
 8050d29:	60                   	pusha  
 8050d2a:	89 d9                	mov    ecx,ebx

08050d2c <..@3688._2>:
 8050d2c:	83 f9 01             	cmp    ecx,0x1
 8050d2f:	7c 40                	jl     8050d71 <..@3688._1>
 8050d31:	b8 00 00 00 00       	mov    eax,0x0
 8050d36:	8b 02                	mov    eax,DWORD PTR [edx]
 8050d38:	c1 e0 08             	shl    eax,0x8
 8050d3b:	c1 e0 08             	shl    eax,0x8
 8050d3e:	c1 e8 08             	shr    eax,0x8
 8050d41:	c1 e8 08             	shr    eax,0x8
 8050d44:	e8 0c e8 ff ff       	call   804f555 <__best_bsput_one>
 8050d49:	83 c2 02             	add    edx,0x2
 8050d4c:	49                   	dec    ecx
 8050d4d:	83 f9 01             	cmp    ecx,0x1
 8050d50:	7c 1f                	jl     8050d71 <..@3688._1>
 8050d52:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8050d57:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 8050d5c:	b0 20                	mov    al,0x20
 8050d5e:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8050d62:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 8050d67:	83 ec 02             	sub    esp,0x2
 8050d6a:	e8 9d ee ff ff       	call   804fc0c <__best_cput+0x2>
 8050d6f:	eb bb                	jmp    8050d2c <..@3688._2>

08050d71 <..@3688._1>:
 8050d71:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8050d76:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 8050d7b:	b0 0a                	mov    al,0xa
 8050d7d:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8050d81:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 8050d86:	83 ec 02             	sub    esp,0x2
 8050d89:	e8 7e ee ff ff       	call   804fc0c <__best_cput+0x2>
 8050d8e:	61                   	popa   
 8050d8f:	89 c8                	mov    eax,ecx
 8050d91:	bb 02 00 00 00       	mov    ebx,0x2
 8050d96:	f7 e3                	mul    ebx
 8050d98:	89 e3                	mov    ebx,esp
 8050d9a:	89 de                	mov    esi,ebx
 8050d9c:	89 df                	mov    edi,ebx
 8050d9e:	01 c7                	add    edi,eax
 8050da0:	b9 28 00 00 00       	mov    ecx,0x28
 8050da5:	01 cf                	add    edi,ecx
 8050da7:	01 ce                	add    esi,ecx
 8050da9:	4f                   	dec    edi
 8050daa:	4e                   	dec    esi
 8050dab:	fd                   	std    
 8050dac:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8050dae:	fc                   	cld    
 8050daf:	01 c4                	add    esp,eax
 8050db1:	61                   	popa   
 8050db2:	83 c4 04             	add    esp,0x4
 8050db5:	c3                   	ret    

08050db6 <__best_cprint>:
 8050db6:	6a 00                	push   0x0
 8050db8:	6a 00                	push   0x0
 8050dba:	6a 00                	push   0x0
 8050dbc:	6a 00                	push   0x0
 8050dbe:	6a 00                	push   0x0
 8050dc0:	6a 00                	push   0x0
 8050dc2:	6a 00                	push   0x0
 8050dc4:	6a 00                	push   0x0
 8050dc6:	6a 00                	push   0x0
 8050dc8:	6a 00                	push   0x0
 8050dca:	6a 00                	push   0x0
 8050dcc:	6a 00                	push   0x0
 8050dce:	6a 00                	push   0x0
 8050dd0:	6a 00                	push   0x0
 8050dd2:	6a 00                	push   0x0
 8050dd4:	6a 00                	push   0x0
 8050dd6:	6a 00                	push   0x0
 8050dd8:	6a 00                	push   0x0
 8050dda:	6a 00                	push   0x0
 8050ddc:	6a 00                	push   0x0
 8050dde:	6a 00                	push   0x0
 8050de0:	6a 00                	push   0x0
 8050de2:	6a 00                	push   0x0
 8050de4:	6a 00                	push   0x0
 8050de6:	6a 00                	push   0x0
 8050de8:	6a 00                	push   0x0
 8050dea:	6a 00                	push   0x0
 8050dec:	6a 00                	push   0x0
 8050dee:	6a 00                	push   0x0
 8050df0:	6a 00                	push   0x0
 8050df2:	6a 00                	push   0x0
 8050df4:	6a 00                	push   0x0
 8050df6:	6a 20                	push   0x20

08050df8 <..@3699._1>:
 8050df8:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 8050dfd:	75 08                	jne    8050e07 <..@3699._2>
 8050dff:	ff 0c 24             	dec    DWORD PTR [esp]
 8050e02:	8f 04 24             	pop    DWORD PTR [esp]
 8050e05:	eb f1                	jmp    8050df8 <..@3699._1>

08050e07 <..@3699._2>:
 8050e07:	60                   	pusha  
 8050e08:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8050e0c:	89 e2                	mov    edx,esp
 8050e0e:	83 c2 28             	add    edx,0x28
 8050e11:	89 cb                	mov    ebx,ecx
 8050e13:	90                   	nop
 8050e14:	60                   	pusha  
 8050e15:	89 d9                	mov    ecx,ebx

08050e17 <..@3698._2>:
 8050e17:	83 f9 01             	cmp    ecx,0x1
 8050e1a:	7c 40                	jl     8050e5c <..@3698._1>
 8050e1c:	b8 00 00 00 00       	mov    eax,0x0
 8050e21:	8b 02                	mov    eax,DWORD PTR [edx]
 8050e23:	c1 e0 08             	shl    eax,0x8
 8050e26:	c1 e0 08             	shl    eax,0x8
 8050e29:	c1 e8 08             	shr    eax,0x8
 8050e2c:	c1 e8 08             	shr    eax,0x8
 8050e2f:	e8 5d e7 ff ff       	call   804f591 <__best_cput_one>
 8050e34:	83 c2 02             	add    edx,0x2
 8050e37:	49                   	dec    ecx
 8050e38:	83 f9 01             	cmp    ecx,0x1
 8050e3b:	7c 1f                	jl     8050e5c <..@3698._1>
 8050e3d:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8050e42:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 8050e47:	b0 20                	mov    al,0x20
 8050e49:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8050e4d:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 8050e52:	83 ec 02             	sub    esp,0x2
 8050e55:	e8 b2 ed ff ff       	call   804fc0c <__best_cput+0x2>
 8050e5a:	eb bb                	jmp    8050e17 <..@3698._2>

08050e5c <..@3698._1>:
 8050e5c:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8050e61:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 8050e66:	b0 0a                	mov    al,0xa
 8050e68:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8050e6c:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 8050e71:	83 ec 02             	sub    esp,0x2
 8050e74:	e8 93 ed ff ff       	call   804fc0c <__best_cput+0x2>
 8050e79:	61                   	popa   
 8050e7a:	89 c8                	mov    eax,ecx
 8050e7c:	bb 02 00 00 00       	mov    ebx,0x2
 8050e81:	f7 e3                	mul    ebx
 8050e83:	89 e3                	mov    ebx,esp
 8050e85:	89 de                	mov    esi,ebx
 8050e87:	89 df                	mov    edi,ebx
 8050e89:	01 c7                	add    edi,eax
 8050e8b:	b9 28 00 00 00       	mov    ecx,0x28
 8050e90:	01 cf                	add    edi,ecx
 8050e92:	01 ce                	add    esi,ecx
 8050e94:	4f                   	dec    edi
 8050e95:	4e                   	dec    esi
 8050e96:	fd                   	std    
 8050e97:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8050e99:	fc                   	cld    
 8050e9a:	01 c4                	add    esp,eax
 8050e9c:	61                   	popa   
 8050e9d:	83 c4 04             	add    esp,0x4
 8050ea0:	c3                   	ret    

08050ea1 <__best_sprint>:
 8050ea1:	6a 00                	push   0x0
 8050ea3:	6a 00                	push   0x0
 8050ea5:	6a 00                	push   0x0
 8050ea7:	6a 00                	push   0x0
 8050ea9:	6a 00                	push   0x0
 8050eab:	6a 00                	push   0x0
 8050ead:	6a 00                	push   0x0
 8050eaf:	6a 00                	push   0x0
 8050eb1:	6a 00                	push   0x0
 8050eb3:	6a 00                	push   0x0
 8050eb5:	6a 00                	push   0x0
 8050eb7:	6a 00                	push   0x0
 8050eb9:	6a 00                	push   0x0
 8050ebb:	6a 00                	push   0x0
 8050ebd:	6a 00                	push   0x0
 8050ebf:	6a 00                	push   0x0
 8050ec1:	6a 00                	push   0x0
 8050ec3:	6a 00                	push   0x0
 8050ec5:	6a 00                	push   0x0
 8050ec7:	6a 00                	push   0x0
 8050ec9:	6a 00                	push   0x0
 8050ecb:	6a 00                	push   0x0
 8050ecd:	6a 00                	push   0x0
 8050ecf:	6a 00                	push   0x0
 8050ed1:	6a 00                	push   0x0
 8050ed3:	6a 00                	push   0x0
 8050ed5:	6a 00                	push   0x0
 8050ed7:	6a 00                	push   0x0
 8050ed9:	6a 00                	push   0x0
 8050edb:	6a 00                	push   0x0
 8050edd:	6a 00                	push   0x0
 8050edf:	6a 00                	push   0x0
 8050ee1:	6a 20                	push   0x20

08050ee3 <..@3709._1>:
 8050ee3:	83 7c 24 04 00       	cmp    DWORD PTR [esp+0x4],0x0
 8050ee8:	75 08                	jne    8050ef2 <..@3709._2>
 8050eea:	ff 0c 24             	dec    DWORD PTR [esp]
 8050eed:	8f 04 24             	pop    DWORD PTR [esp]
 8050ef0:	eb f1                	jmp    8050ee3 <..@3709._1>

08050ef2 <..@3709._2>:
 8050ef2:	60                   	pusha  
 8050ef3:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
 8050ef7:	89 e2                	mov    edx,esp
 8050ef9:	83 c2 28             	add    edx,0x28
 8050efc:	89 cb                	mov    ebx,ecx
 8050efe:	8b 54 24 24          	mov    edx,DWORD PTR [esp+0x24]
 8050f02:	01 4c 24 24          	add    DWORD PTR [esp+0x24],ecx
 8050f06:	b9 00 00 00 00       	mov    ecx,0x0
 8050f0b:	60                   	pusha  
 8050f0c:	89 d9                	mov    ecx,ebx

08050f0e <..@3708._2>:
 8050f0e:	83 f9 01             	cmp    ecx,0x1
 8050f11:	7c 29                	jl     8050f3c <..@3708._1>
 8050f13:	b8 00 00 00 00       	mov    eax,0x0
 8050f18:	8b 02                	mov    eax,DWORD PTR [edx]
 8050f1a:	c1 e0 08             	shl    eax,0x8
 8050f1d:	c1 e0 08             	shl    eax,0x8
 8050f20:	c1 e0 08             	shl    eax,0x8
 8050f23:	c1 e8 08             	shr    eax,0x8
 8050f26:	c1 e8 08             	shr    eax,0x8
 8050f29:	c1 e8 08             	shr    eax,0x8
 8050f2c:	e8 7b e6 ff ff       	call   804f5ac <__best_sput_one>
 8050f31:	83 c2 01             	add    edx,0x1
 8050f34:	49                   	dec    ecx
 8050f35:	83 f9 01             	cmp    ecx,0x1
 8050f38:	7c 02                	jl     8050f3c <..@3708._1>
 8050f3a:	eb d2                	jmp    8050f0e <..@3708._2>

08050f3c <..@3708._1>:
 8050f3c:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8050f41:	a3 16 29 05 08       	mov    ds:0x8052916,eax
 8050f46:	b0 0a                	mov    al,0xa
 8050f48:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 8050f4c:	a1 16 29 05 08       	mov    eax,ds:0x8052916
 8050f51:	83 ec 02             	sub    esp,0x2
 8050f54:	e8 b3 ec ff ff       	call   804fc0c <__best_cput+0x2>
 8050f59:	61                   	popa   
 8050f5a:	89 c8                	mov    eax,ecx
 8050f5c:	bb 01 00 00 00       	mov    ebx,0x1
 8050f61:	f7 e3                	mul    ebx
 8050f63:	89 e3                	mov    ebx,esp
 8050f65:	89 de                	mov    esi,ebx
 8050f67:	89 df                	mov    edi,ebx
 8050f69:	01 c7                	add    edi,eax
 8050f6b:	b9 28 00 00 00       	mov    ecx,0x28
 8050f70:	01 cf                	add    edi,ecx
 8050f72:	01 ce                	add    esi,ecx
 8050f74:	4f                   	dec    edi
 8050f75:	4e                   	dec    esi
 8050f76:	fd                   	std    
 8050f77:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
 8050f79:	fc                   	cld    
 8050f7a:	01 c4                	add    esp,eax
 8050f7c:	61                   	popa   
 8050f7d:	83 c4 04             	add    esp,0x4
 8050f80:	c3                   	ret    
 8050f81:	66 90                	xchg   ax,ax
 8050f83:	66 90                	xchg   ax,ax
 8050f85:	66 90                	xchg   ax,ax
 8050f87:	66 90                	xchg   ax,ax
 8050f89:	66 90                	xchg   ax,ax
 8050f8b:	66 90                	xchg   ax,ax
 8050f8d:	66 90                	xchg   ax,ax
 8050f8f:	90                   	nop

08050f90 <_start>:
 8050f90:	89 25 42 84 0e 08    	mov    DWORD PTR ds:0x80e8442,esp
 8050f96:	eb 19                	jmp    8050fb1 <..@127._1>

08050f98 <..@128.__jup>:
 8050f98:	39 25 42 84 0e 08    	cmp    DWORD PTR ds:0x80e8442,esp
 8050f9e:	74 00                	je     8050fa0 <..@127._2>

08050fa0 <..@127._2>:
 8050fa0:	b8 01 00 00 00       	mov    eax,0x1
 8050fa5:	bb 00 00 00 00       	mov    ebx,0x0
 8050faa:	cd 80                	int    0x80
 8050fac:	e9 3a 09 00 00       	jmp    80518eb <..@128.__jdown>

08050fb1 <..@127._1>:
 8050fb1:	e9 39 02 00 00       	jmp    80511ef <..@134.__jdown>

08050fb6 <run>:
 8050fb6:	c7 05 2a e4 0c 08 00 	mov    DWORD PTR ds:0x80ce42a,0x0
 8050fbd:	00 00 00 
 8050fc0:	c7 05 2e e4 0c 08 00 	mov    DWORD PTR ds:0x80ce42e,0x0
 8050fc7:	00 00 00 
 8050fca:	c7 05 32 e4 0c 08 00 	mov    DWORD PTR ds:0x80ce432,0x0
 8050fd1:	00 00 00 
 8050fd4:	c7 05 36 e4 0c 08 00 	mov    DWORD PTR ds:0x80ce436,0x0
 8050fdb:	00 00 00 
 8050fde:	ff 74 24 10          	push   DWORD PTR [esp+0x10]
 8050fe2:	8f 05 2a e4 0c 08    	pop    DWORD PTR ds:0x80ce42a
 8050fe8:	ff 74 24 0c          	push   DWORD PTR [esp+0xc]
 8050fec:	8f 05 2e e4 0c 08    	pop    DWORD PTR ds:0x80ce42e
 8050ff2:	ff 74 24 08          	push   DWORD PTR [esp+0x8]
 8050ff6:	8f 05 32 e4 0c 08    	pop    DWORD PTR ds:0x80ce432
 8050ffc:	ff 74 24 04          	push   DWORD PTR [esp+0x4]
 8051000:	8f 05 36 e4 0c 08    	pop    DWORD PTR ds:0x80ce436
 8051006:	60                   	pusha  
 8051007:	a1 2a e4 0c 08       	mov    eax,ds:0x80ce42a
 805100c:	8b 1d 2e e4 0c 08    	mov    ebx,DWORD PTR ds:0x80ce42e
 8051012:	8b 0d 32 e4 0c 08    	mov    ecx,DWORD PTR ds:0x80ce432
 8051018:	8b 15 36 e4 0c 08    	mov    edx,DWORD PTR ds:0x80ce436
 805101e:	be 00 00 00 00       	mov    esi,0x0
 8051023:	bf 00 00 00 00       	mov    edi,0x0
 8051028:	bd 00 00 00 00       	mov    ebp,0x0
 805102d:	eb 41                	jmp    8051070 <..@132._2>

0805102f <..@134.__jup>:
 805102f:	a3 2a e4 0c 08       	mov    ds:0x80ce42a,eax
 8051034:	89 1d 2e e4 0c 08    	mov    DWORD PTR ds:0x80ce42e,ebx
 805103a:	89 0d 32 e4 0c 08    	mov    DWORD PTR ds:0x80ce432,ecx
 8051040:	89 15 36 e4 0c 08    	mov    DWORD PTR ds:0x80ce436,edx
 8051046:	61                   	popa   
 8051047:	ff 35 2a e4 0c 08    	push   DWORD PTR ds:0x80ce42a
 805104d:	8f 44 24 04          	pop    DWORD PTR [esp+0x4]
 8051051:	ff 35 2e e4 0c 08    	push   DWORD PTR ds:0x80ce42e
 8051057:	8f 44 24 08          	pop    DWORD PTR [esp+0x8]
 805105b:	ff 35 32 e4 0c 08    	push   DWORD PTR ds:0x80ce432
 8051061:	8f 44 24 0c          	pop    DWORD PTR [esp+0xc]
 8051065:	ff 35 36 e4 0c 08    	push   DWORD PTR ds:0x80ce436
 805106b:	8f 44 24 10          	pop    DWORD PTR [esp+0x10]
 805106f:	c3                   	ret    

08051070 <..@132._2>:
 8051070:	c7 05 2a e4 0c 08 00 	mov    DWORD PTR ds:0x80ce42a,0x0
 8051077:	00 00 00 
 805107a:	c7 05 2e e4 0c 08 00 	mov    DWORD PTR ds:0x80ce42e,0x0
 8051081:	00 00 00 
 8051084:	c7 05 32 e4 0c 08 00 	mov    DWORD PTR ds:0x80ce432,0x0
 805108b:	00 00 00 
 805108e:	c7 05 36 e4 0c 08 00 	mov    DWORD PTR ds:0x80ce436,0x0
 8051095:	00 00 00 
 8051098:	50                   	push   eax
 8051099:	8f 05 2a e4 0c 08    	pop    DWORD PTR ds:0x80ce42a
 805109f:	53                   	push   ebx
 80510a0:	8f 05 2e e4 0c 08    	pop    DWORD PTR ds:0x80ce42e
 80510a6:	60                   	pusha  
 80510a7:	a1 2a e4 0c 08       	mov    eax,ds:0x80ce42a
 80510ac:	8b 1d 2e e4 0c 08    	mov    ebx,DWORD PTR ds:0x80ce42e
 80510b2:	8b 0d 32 e4 0c 08    	mov    ecx,DWORD PTR ds:0x80ce432
 80510b8:	8b 15 36 e4 0c 08    	mov    edx,DWORD PTR ds:0x80ce436
 80510be:	be 00 00 00 00       	mov    esi,0x0
 80510c3:	bf 00 00 00 00       	mov    edi,0x0
 80510c8:	bd 00 00 00 00       	mov    ebp,0x0
 80510cd:	f7 e3                	mul    ebx
 80510cf:	a3 2a e4 0c 08       	mov    ds:0x80ce42a,eax
 80510d4:	89 1d 2e e4 0c 08    	mov    DWORD PTR ds:0x80ce42e,ebx
 80510da:	89 0d 32 e4 0c 08    	mov    DWORD PTR ds:0x80ce432,ecx
 80510e0:	89 15 36 e4 0c 08    	mov    DWORD PTR ds:0x80ce436,edx
 80510e6:	61                   	popa   
 80510e7:	ff 35 2a e4 0c 08    	push   DWORD PTR ds:0x80ce42a
 80510ed:	58                   	pop    eax
 80510ee:	c7 05 2a e4 0c 08 00 	mov    DWORD PTR ds:0x80ce42a,0x0
 80510f5:	00 00 00 
 80510f8:	c7 05 2e e4 0c 08 00 	mov    DWORD PTR ds:0x80ce42e,0x0
 80510ff:	00 00 00 
 8051102:	c7 05 32 e4 0c 08 00 	mov    DWORD PTR ds:0x80ce432,0x0
 8051109:	00 00 00 
 805110c:	c7 05 36 e4 0c 08 00 	mov    DWORD PTR ds:0x80ce436,0x0
 8051113:	00 00 00 
 8051116:	50                   	push   eax
 8051117:	8f 05 2a e4 0c 08    	pop    DWORD PTR ds:0x80ce42a
 805111d:	51                   	push   ecx
 805111e:	8f 05 2e e4 0c 08    	pop    DWORD PTR ds:0x80ce42e
 8051124:	60                   	pusha  
 8051125:	a1 2a e4 0c 08       	mov    eax,ds:0x80ce42a
 805112a:	8b 1d 2e e4 0c 08    	mov    ebx,DWORD PTR ds:0x80ce42e
 8051130:	8b 0d 32 e4 0c 08    	mov    ecx,DWORD PTR ds:0x80ce432
 8051136:	8b 15 36 e4 0c 08    	mov    edx,DWORD PTR ds:0x80ce436
 805113c:	be 00 00 00 00       	mov    esi,0x0
 8051141:	bf 00 00 00 00       	mov    edi,0x0
 8051146:	bd 00 00 00 00       	mov    ebp,0x0
 805114b:	f7 e3                	mul    ebx
 805114d:	a3 2a e4 0c 08       	mov    ds:0x80ce42a,eax
 8051152:	89 1d 2e e4 0c 08    	mov    DWORD PTR ds:0x80ce42e,ebx
 8051158:	89 0d 32 e4 0c 08    	mov    DWORD PTR ds:0x80ce432,ecx
 805115e:	89 15 36 e4 0c 08    	mov    DWORD PTR ds:0x80ce436,edx
 8051164:	61                   	popa   
 8051165:	ff 35 2a e4 0c 08    	push   DWORD PTR ds:0x80ce42a
 805116b:	58                   	pop    eax
 805116c:	c7 05 2a e4 0c 08 00 	mov    DWORD PTR ds:0x80ce42a,0x0
 8051173:	00 00 00 
 8051176:	c7 05 2e e4 0c 08 00 	mov    DWORD PTR ds:0x80ce42e,0x0
 805117d:	00 00 00 
 8051180:	c7 05 32 e4 0c 08 00 	mov    DWORD PTR ds:0x80ce432,0x0
 8051187:	00 00 00 
 805118a:	c7 05 36 e4 0c 08 00 	mov    DWORD PTR ds:0x80ce436,0x0
 8051191:	00 00 00 
 8051194:	50                   	push   eax
 8051195:	8f 05 2a e4 0c 08    	pop    DWORD PTR ds:0x80ce42a
 805119b:	52                   	push   edx
 805119c:	8f 05 2e e4 0c 08    	pop    DWORD PTR ds:0x80ce42e
 80511a2:	60                   	pusha  
 80511a3:	a1 2a e4 0c 08       	mov    eax,ds:0x80ce42a
 80511a8:	8b 1d 2e e4 0c 08    	mov    ebx,DWORD PTR ds:0x80ce42e
 80511ae:	8b 0d 32 e4 0c 08    	mov    ecx,DWORD PTR ds:0x80ce432
 80511b4:	8b 15 36 e4 0c 08    	mov    edx,DWORD PTR ds:0x80ce436
 80511ba:	be 00 00 00 00       	mov    esi,0x0
 80511bf:	bf 00 00 00 00       	mov    edi,0x0
 80511c4:	bd 00 00 00 00       	mov    ebp,0x0
 80511c9:	f7 e3                	mul    ebx
 80511cb:	a3 2a e4 0c 08       	mov    ds:0x80ce42a,eax
 80511d0:	89 1d 2e e4 0c 08    	mov    DWORD PTR ds:0x80ce42e,ebx
 80511d6:	89 0d 32 e4 0c 08    	mov    DWORD PTR ds:0x80ce432,ecx
 80511dc:	89 15 36 e4 0c 08    	mov    DWORD PTR ds:0x80ce436,edx
 80511e2:	61                   	popa   
 80511e3:	ff 35 2a e4 0c 08    	push   DWORD PTR ds:0x80ce42a
 80511e9:	58                   	pop    eax
 80511ea:	e9 40 fe ff ff       	jmp    805102f <..@134.__jup>

080511ef <..@134.__jdown>:
 80511ef:	c7 05 2a e4 0c 08 00 	mov    DWORD PTR ds:0x80ce42a,0x0
 80511f6:	00 00 00 
 80511f9:	c7 05 2e e4 0c 08 00 	mov    DWORD PTR ds:0x80ce42e,0x0
 8051200:	00 00 00 
 8051203:	c7 05 32 e4 0c 08 00 	mov    DWORD PTR ds:0x80ce432,0x0
 805120a:	00 00 00 
 805120d:	c7 05 36 e4 0c 08 00 	mov    DWORD PTR ds:0x80ce436,0x0
 8051214:	00 00 00 
 8051217:	68 3a 9f 14 08       	push   0x8149f3a
 805121c:	8f 05 2a e4 0c 08    	pop    DWORD PTR ds:0x80ce42a
 8051222:	6a 14                	push   0x14
 8051224:	8f 05 2e e4 0c 08    	pop    DWORD PTR ds:0x80ce42e
 805122a:	60                   	pusha  
 805122b:	a1 2a e4 0c 08       	mov    eax,ds:0x80ce42a
 8051230:	8b 1d 2e e4 0c 08    	mov    ebx,DWORD PTR ds:0x80ce42e
 8051236:	8b 0d 32 e4 0c 08    	mov    ecx,DWORD PTR ds:0x80ce432
 805123c:	8b 15 36 e4 0c 08    	mov    edx,DWORD PTR ds:0x80ce436
 8051242:	be 00 00 00 00       	mov    esi,0x0
 8051247:	bf 00 00 00 00       	mov    edi,0x0
 805124c:	bd 00 00 00 00       	mov    ebp,0x0
 8051251:	01 d8                	add    eax,ebx
 8051253:	a3 2a e4 0c 08       	mov    ds:0x80ce42a,eax
 8051258:	89 1d 2e e4 0c 08    	mov    DWORD PTR ds:0x80ce42e,ebx
 805125e:	89 0d 32 e4 0c 08    	mov    DWORD PTR ds:0x80ce432,ecx
 8051264:	89 15 36 e4 0c 08    	mov    DWORD PTR ds:0x80ce436,edx
 805126a:	61                   	popa   
 805126b:	ff 35 2a e4 0c 08    	push   DWORD PTR ds:0x80ce42a
 8051271:	8f 05 42 e4 0d 08    	pop    DWORD PTR ds:0x80de442
 8051277:	6a 02                	push   0x2
 8051279:	8f 05 42 74 0e 08    	pop    DWORD PTR ds:0x80e7442
 805127f:	6a 03                	push   0x3
 8051281:	8f 05 42 54 0e 08    	pop    DWORD PTR ds:0x80e5442
 8051287:	6a 04                	push   0x4
 8051289:	8f 05 42 04 0d 08    	pop    DWORD PTR ds:0x80d0442
 805128f:	6a 05                	push   0x5
 8051291:	8f 05 42 34 0e 08    	pop    DWORD PTR ds:0x80e3442
 8051297:	68 ac 12 05 08       	push   0x80512ac
 805129c:	68 42 14 0d 08       	push   0x80d1442
 80512a1:	68 ab 12 05 08       	push   0x80512ab
 80512a6:	e9 f4 d7 ff ff       	jmp    804ea9f <macro_var_jmp>

080512ab <..@242._1>:
 80512ab:	64                   	fs

080512ac <..@242._3>:
 80512ac:	68 c1 12 05 08       	push   0x80512c1
 80512b1:	68 42 74 0e 08       	push   0x80e7442
 80512b6:	68 c0 12 05 08       	push   0x80512c0
 80512bb:	e9 df d7 ff ff       	jmp    804ea9f <macro_var_jmp>

080512c0 <..@244._1>:
 80512c0:	7a                   	.byte 0x7a

080512c1 <..@244._3>:
 80512c1:	68 d6 12 05 08       	push   0x80512d6
 80512c6:	68 42 e4 0d 08       	push   0x80de442
 80512cb:	68 d5 12 05 08       	push   0x80512d5
 80512d0:	e9 ca d7 ff ff       	jmp    804ea9f <macro_var_jmp>

080512d5 <..@246._1>:
 80512d5:	71                   	.byte 0x71

080512d6 <..@246._3>:
 80512d6:	68 ed 12 05 08       	push   0x80512ed
 80512db:	68 b6 0f 05 08       	push   0x8050fb6
 80512e0:	68 ea 12 05 08       	push   0x80512ea
 80512e5:	e9 b5 d7 ff ff       	jmp    804ea9f <macro_var_jmp>

080512ea <..@248._1>:
 80512ea:	72 75                	jb     8051361 <..@256._expr+0x16>
 80512ec:	6e                   	outs   dx,BYTE PTR ds:[esi]

080512ed <..@248._3>:
 80512ed:	68 02 13 05 08       	push   0x8051302
 80512f2:	68 42 54 0e 08       	push   0x80e5442
 80512f7:	68 01 13 05 08       	push   0x8051301
 80512fc:	e9 9e d7 ff ff       	jmp    804ea9f <macro_var_jmp>

08051301 <..@250._1>:
 8051301:	78                   	.byte 0x78

08051302 <..@250._3>:
 8051302:	68 17 13 05 08       	push   0x8051317
 8051307:	68 42 04 0d 08       	push   0x80d0442
 805130c:	68 16 13 05 08       	push   0x8051316
 8051311:	e9 89 d7 ff ff       	jmp    804ea9f <macro_var_jmp>

08051316 <..@252._1>:
 8051316:	63                   	.byte 0x63

08051317 <..@252._3>:
 8051317:	68 2c 13 05 08       	push   0x805132c
 805131c:	68 42 34 0e 08       	push   0x80e3442
 8051321:	68 2b 13 05 08       	push   0x805132b
 8051326:	e9 74 d7 ff ff       	jmp    804ea9f <macro_var_jmp>

0805132b <..@254._1>:
 805132b:	76                   	.byte 0x76

0805132c <..@254._3>:
 805132c:	68 4b 13 05 08       	push   0x805134b
 8051331:	e8 c5 d7 ff ff       	call   804eafb <macro_expr_jmp>
 8051336:	20 28                	and    BYTE PTR [eax],ch
 8051338:	64 20 5b 30          	and    BYTE PTR fs:[ebx+0x30],bl
 805133c:	5d                   	pop    ebp
 805133d:	3d 28 7a 5b 30       	cmp    eax,0x305b7a28
 8051342:	5d                   	pop    ebp
 8051343:	29 2b                	sub    DWORD PTR [ebx],ebp
 8051345:	2d 2b 2d 31 29       	sub    eax,0x29312d2b
 805134a:	20                   	.byte 0x20

0805134b <..@256._expr>:
 805134b:	ff 35 42 14 0d 08    	push   DWORD PTR ds:0x80d1442
 8051351:	e8 d7 f5 ff ff       	call   805092d <__best_dsprint+0x2>
 8051356:	68 dc 13 05 08       	push   0x80513dc
 805135b:	e8 9b d7 ff ff       	call   804eafb <macro_expr_jmp>
 8051360:	20 28                	and    BYTE PTR [eax],ch
 8051362:	64 20 5b 30          	and    BYTE PTR fs:[ebx+0x30],bl
 8051366:	5d                   	pop    ebp
 8051367:	3d 28 28 7a 5b       	cmp    eax,0x5b7a2828
 805136c:	30 5d 2b             	xor    BYTE PTR [ebp+0x2b],bl
 805136f:	78 5b                	js     80513cc <..@256._expr+0x81>
 8051371:	30 5d 29             	xor    BYTE PTR [ebp+0x29],bl
 8051374:	2a 28                	sub    ch,BYTE PTR [eax]
 8051376:	20 63 5b             	and    BYTE PTR [ebx+0x5b],ah
 8051379:	30 5d 2b             	xor    BYTE PTR [ebp+0x2b],bl
 805137c:	76 5b                	jbe    80513d9 <..@256._expr+0x8e>
 805137e:	30 5d 29             	xor    BYTE PTR [ebp+0x29],bl
 8051381:	29 2b                	sub    DWORD PTR [ebx],ebp
 8051383:	28 2d 31 3c 31 26    	sub    BYTE PTR ds:0x26313c31,ch
 8051389:	26 31 3e             	xor    DWORD PTR es:[esi],edi
 805138c:	2d 31 29 2b 72       	sub    eax,0x722b2931
 8051391:	75 6e                	jne    8051401 <..@261._expr+0x1>
 8051393:	20 28                	and    BYTE PTR [eax],ch
 8051395:	71 5b                	jno    80513f2 <..@260._expr+0x16>
 8051397:	30 5d 5b             	xor    BYTE PTR [ebp+0x5b],bl
 805139a:	31 5d 2c             	xor    DWORD PTR [ebp+0x2c],ebx
 805139d:	71 5b                	jno    80513fa <..@260._expr+0x1e>
 805139f:	30 5d 5b             	xor    BYTE PTR [ebp+0x5b],bl
 80513a2:	71 20                	jno    80513c4 <..@256._expr+0x79>
 80513a4:	5b                   	pop    ebx
 80513a5:	30 5d 5b             	xor    BYTE PTR [ebp+0x5b],bl
 80513a8:	32 5d 5d             	xor    bl,BYTE PTR [ebp+0x5d]
 80513ab:	2c 71                	sub    al,0x71
 80513ad:	5b                   	pop    ebx
 80513ae:	30 5d 5b             	xor    BYTE PTR [ebp+0x5b],bl
 80513b1:	71 5b                	jno    805140e <..@261._expr+0xe>
 80513b3:	30 5d 5b             	xor    BYTE PTR [ebp+0x5b],bl
 80513b6:	71 5b                	jno    8051413 <..@261._expr+0x13>
 80513b8:	30 5d 5b             	xor    BYTE PTR [ebp+0x5b],bl
 80513bb:	33 5d 5d             	xor    ebx,DWORD PTR [ebp+0x5d]
 80513be:	5d                   	pop    ebp
 80513bf:	2c 71                	sub    al,0x71
 80513c1:	5b                   	pop    ebx
 80513c2:	30 5d 5b             	xor    BYTE PTR [ebp+0x5b],bl
 80513c5:	71 5b                	jno    8051422 <..@261._expr+0x22>
 80513c7:	30 5d 5b             	xor    BYTE PTR [ebp+0x5b],bl
 80513ca:	71 5b                	jno    8051427 <..@261._expr+0x27>
 80513cc:	30 5d 5b             	xor    BYTE PTR [ebp+0x5b],bl
 80513cf:	71 5b                	jno    805142c <..@261._expr+0x2c>
 80513d1:	30 5d 5b             	xor    BYTE PTR [ebp+0x5b],bl
 80513d4:	34 5d                	xor    al,0x5d
 80513d6:	5d                   	pop    ebp
 80513d7:	5d                   	pop    ebp
 80513d8:	5d                   	pop    ebp
 80513d9:	29 29                	sub    DWORD PTR [ecx],ebp
 80513db:	20                   	.byte 0x20

080513dc <..@260._expr>:
 80513dc:	68 00 14 05 08       	push   0x8051400
 80513e1:	e8 15 d7 ff ff       	call   804eafb <macro_expr_jmp>
 80513e6:	20 28                	and    BYTE PTR [eax],ch
 80513e8:	7c 20                	jl     805140a <..@261._expr+0xa>
 80513ea:	64 5b                	fs pop ebx
 80513ec:	30 5d 20             	xor    BYTE PTR [ebp+0x20],bl
 80513ef:	2b 3d 20 32 7c 20    	sub    edi,DWORD PTR ds:0x207c3220
 80513f5:	64 5b                	fs pop ebx
 80513f7:	30 5d 20             	xor    BYTE PTR [ebp+0x20],bl
 80513fa:	2f                   	das    
 80513fb:	3d 20 39 29 20       	cmp    eax,0x20293920

08051400 <..@261._expr>:
 8051400:	ff 35 42 14 0d 08    	push   DWORD PTR ds:0x80d1442
 8051406:	e8 22 f5 ff ff       	call   805092d <__best_dsprint+0x2>
 805140b:	68 3e 14 05 08       	push   0x805143e
 8051410:	e8 e6 d6 ff ff       	call   804eafb <macro_expr_jmp>
 8051415:	20 28                	and    BYTE PTR [eax],ch
 8051417:	28 2a                	sub    BYTE PTR [edx],ch
 8051419:	71 29                	jno    8051444 <..@265._expr+0x6>
 805141b:	5b                   	pop    ebx
 805141c:	2d 33 5d 2a 3d       	sub    eax,0x3d2a5d33
 8051421:	28 2a                	sub    BYTE PTR [edx],ch
 8051423:	71 29                	jno    805144e <..@265._expr+0x10>
 8051425:	5b                   	pop    ebx
 8051426:	2d 31 5d 3d 28       	sub    eax,0x283d5d31
 805142b:	2a 71 29             	sub    dh,BYTE PTR [ecx+0x29]
 805142e:	5b                   	pop    ebx
 805142f:	31 5d 3d             	xor    DWORD PTR [ebp+0x3d],ebx
 8051432:	28 2a                	sub    BYTE PTR [edx],ch
 8051434:	71 29                	jno    805145f <..@266._expr+0x1>
 8051436:	5b                   	pop    ebx
 8051437:	33 5d 2b             	xor    ebx,DWORD PTR [ebp+0x2b]
 805143a:	3d                   	.byte 0x3d
 805143b:	39 29                	cmp    DWORD PTR [ecx],ebp
 805143d:	20                   	.byte 0x20

0805143e <..@265._expr>:
 805143e:	68 5e 14 05 08       	push   0x805145e
 8051443:	e8 b3 d6 ff ff       	call   804eafb <macro_expr_jmp>
 8051448:	20 28                	and    BYTE PTR [eax],ch
 805144a:	28 2a                	sub    BYTE PTR [edx],ch
 805144c:	71 29                	jno    8051477 <..@266._expr+0x19>
 805144e:	5b                   	pop    ebx
 805144f:	2d 33 5d 25 3d       	sub    eax,0x3d255d33
 8051454:	28 2a                	sub    BYTE PTR [edx],ch
 8051456:	71 29                	jno    8051481 <..@267._expr+0x9>
 8051458:	5b                   	pop    ebx
 8051459:	2d 34 5d 29 20       	sub    eax,0x20295d34

0805145e <..@266._expr>:
 805145e:	68 78 14 05 08       	push   0x8051478
 8051463:	e8 93 d6 ff ff       	call   804eafb <macro_expr_jmp>
 8051468:	20 28                	and    BYTE PTR [eax],ch
 805146a:	28 2a                	sub    BYTE PTR [edx],ch
 805146c:	71 29                	jno    8051497 <..@268._expr+0x5>
 805146e:	5b                   	pop    ebx
 805146f:	2d 33 5d 2b 3d       	sub    eax,0x3d2b5d33
 8051474:	20 31                	and    BYTE PTR [ecx],dh
 8051476:	29 20                	sub    DWORD PTR [eax],esp

08051478 <..@267._expr>:
 8051478:	68 92 14 05 08       	push   0x8051492
 805147d:	e8 79 d6 ff ff       	call   804eafb <macro_expr_jmp>
 8051482:	20 28                	and    BYTE PTR [eax],ch
 8051484:	71 5b                	jno    80514e1 <..@271._expr+0x3>
 8051486:	30 5d 5b             	xor    BYTE PTR [ebp+0x5b],bl
 8051489:	33 5d 20             	xor    ebx,DWORD PTR [ebp+0x20]
 805148c:	2f                   	das    
 805148d:	3d 2d 32 29 20       	cmp    eax,0x2029322d

08051492 <..@268._expr>:
 8051492:	68 ac 14 05 08       	push   0x80514ac
 8051497:	e8 5f d6 ff ff       	call   804eafb <macro_expr_jmp>
 805149c:	20 28                	and    BYTE PTR [eax],ch
 805149e:	71 5b                	jno    80514fb <..@271._expr+0x1d>
 80514a0:	30 5d 5b             	xor    BYTE PTR [ebp+0x5b],bl
 80514a3:	2d 31 5d 2f 3d       	sub    eax,0x3d2f5d31
 80514a8:	20 36                	and    BYTE PTR [esi],dh
 80514aa:	29 20                	sub    DWORD PTR [eax],esp

080514ac <..@269._expr>:
 80514ac:	68 c6 14 05 08       	push   0x80514c6
 80514b1:	e8 45 d6 ff ff       	call   804eafb <macro_expr_jmp>
 80514b6:	20 28                	and    BYTE PTR [eax],ch
 80514b8:	28 2a                	sub    BYTE PTR [edx],ch
 80514ba:	71 29                	jno    80514e5 <..@271._expr+0x7>
 80514bc:	5b                   	pop    ebx
 80514bd:	31 5d 20             	xor    DWORD PTR [ebp+0x20],ebx
 80514c0:	2f                   	das    
 80514c1:	3d 2d 36 29 20       	cmp    eax,0x2029362d

080514c6 <..@270._expr>:
 80514c6:	68 de 14 05 08       	push   0x80514de
 80514cb:	e8 2b d6 ff ff       	call   804eafb <macro_expr_jmp>
 80514d0:	20 28                	and    BYTE PTR [eax],ch
 80514d2:	2a 2a                	sub    ch,BYTE PTR [edx]
 80514d4:	71 3d                	jno    8051513 <..@271._expr+0x35>
 80514d6:	2b 2d 2b 39 39 39    	sub    ebp,DWORD PTR ds:0x3939392b
 80514dc:	29 20                	sub    DWORD PTR [eax],esp

080514de <..@271._expr>:
 80514de:	6a 00                	push   0x0
 80514e0:	8f 05 42 44 0e 08    	pop    DWORD PTR ds:0x80e4442
 80514e6:	c7 05 2a e4 0c 08 00 	mov    DWORD PTR ds:0x80ce42a,0x0
 80514ed:	00 00 00 
 80514f0:	c7 05 2e e4 0c 08 00 	mov    DWORD PTR ds:0x80ce42e,0x0
 80514f7:	00 00 00 
 80514fa:	c7 05 32 e4 0c 08 00 	mov    DWORD PTR ds:0x80ce432,0x0
 8051501:	00 00 00 
 8051504:	c7 05 36 e4 0c 08 00 	mov    DWORD PTR ds:0x80ce436,0x0
 805150b:	00 00 00 
 805150e:	ff 35 42 44 0e 08    	push   DWORD PTR ds:0x80e4442
 8051514:	8f 05 2a e4 0c 08    	pop    DWORD PTR ds:0x80ce42a
 805151a:	6a 01                	push   0x1
 805151c:	8f 05 2e e4 0c 08    	pop    DWORD PTR ds:0x80ce42e
 8051522:	60                   	pusha  
 8051523:	a1 2a e4 0c 08       	mov    eax,ds:0x80ce42a
 8051528:	8b 1d 2e e4 0c 08    	mov    ebx,DWORD PTR ds:0x80ce42e
 805152e:	8b 0d 32 e4 0c 08    	mov    ecx,DWORD PTR ds:0x80ce432
 8051534:	8b 15 36 e4 0c 08    	mov    edx,DWORD PTR ds:0x80ce436
 805153a:	be 00 00 00 00       	mov    esi,0x0
 805153f:	bf 00 00 00 00       	mov    edi,0x0
 8051544:	bd 00 00 00 00       	mov    ebp,0x0
 8051549:	29 d8                	sub    eax,ebx
 805154b:	a3 2a e4 0c 08       	mov    ds:0x80ce42a,eax
 8051550:	89 1d 2e e4 0c 08    	mov    DWORD PTR ds:0x80ce42e,ebx
 8051556:	89 0d 32 e4 0c 08    	mov    DWORD PTR ds:0x80ce432,ecx
 805155c:	89 15 36 e4 0c 08    	mov    DWORD PTR ds:0x80ce436,edx
 8051562:	61                   	popa   
 8051563:	ff 35 2a e4 0c 08    	push   DWORD PTR ds:0x80ce42a
 8051569:	8f 05 42 44 0e 08    	pop    DWORD PTR ds:0x80e4442

0805156f <..@274.__jup>:
 805156f:	c7 05 2a e4 0c 08 00 	mov    DWORD PTR ds:0x80ce42a,0x0
 8051576:	00 00 00 
 8051579:	c7 05 2e e4 0c 08 00 	mov    DWORD PTR ds:0x80ce42e,0x0
 8051580:	00 00 00 
 8051583:	c7 05 32 e4 0c 08 00 	mov    DWORD PTR ds:0x80ce432,0x0
 805158a:	00 00 00 
 805158d:	c7 05 36 e4 0c 08 00 	mov    DWORD PTR ds:0x80ce436,0x0
 8051594:	00 00 00 
 8051597:	ff 35 42 44 0e 08    	push   DWORD PTR ds:0x80e4442
 805159d:	8f 05 2a e4 0c 08    	pop    DWORD PTR ds:0x80ce42a
 80515a3:	6a 01                	push   0x1
 80515a5:	8f 05 2e e4 0c 08    	pop    DWORD PTR ds:0x80ce42e
 80515ab:	60                   	pusha  
 80515ac:	a1 2a e4 0c 08       	mov    eax,ds:0x80ce42a
 80515b1:	8b 1d 2e e4 0c 08    	mov    ebx,DWORD PTR ds:0x80ce42e
 80515b7:	8b 0d 32 e4 0c 08    	mov    ecx,DWORD PTR ds:0x80ce432
 80515bd:	8b 15 36 e4 0c 08    	mov    edx,DWORD PTR ds:0x80ce436
 80515c3:	be 00 00 00 00       	mov    esi,0x0
 80515c8:	bf 00 00 00 00       	mov    edi,0x0
 80515cd:	bd 00 00 00 00       	mov    ebp,0x0
 80515d2:	01 d8                	add    eax,ebx
 80515d4:	a3 2a e4 0c 08       	mov    ds:0x80ce42a,eax
 80515d9:	89 1d 2e e4 0c 08    	mov    DWORD PTR ds:0x80ce42e,ebx
 80515df:	89 0d 32 e4 0c 08    	mov    DWORD PTR ds:0x80ce432,ecx
 80515e5:	89 15 36 e4 0c 08    	mov    DWORD PTR ds:0x80ce436,edx
 80515eb:	61                   	popa   
 80515ec:	ff 35 2a e4 0c 08    	push   DWORD PTR ds:0x80ce42a
 80515f2:	8f 05 42 44 0e 08    	pop    DWORD PTR ds:0x80e4442
 80515f8:	68 49 17 05 08       	push   0x8051749
 80515fd:	c7 05 2a e4 0c 08 00 	mov    DWORD PTR ds:0x80ce42a,0x0
 8051604:	00 00 00 
 8051607:	c7 05 2e e4 0c 08 00 	mov    DWORD PTR ds:0x80ce42e,0x0
 805160e:	00 00 00 
 8051611:	c7 05 32 e4 0c 08 00 	mov    DWORD PTR ds:0x80ce432,0x0
 8051618:	00 00 00 
 805161b:	c7 05 36 e4 0c 08 00 	mov    DWORD PTR ds:0x80ce436,0x0
 8051622:	00 00 00 
 8051625:	6a 01                	push   0x1
 8051627:	8f 05 2a e4 0c 08    	pop    DWORD PTR ds:0x80ce42a
 805162d:	6a 00                	push   0x0
 805162f:	8f 05 2e e4 0c 08    	pop    DWORD PTR ds:0x80ce42e
 8051635:	60                   	pusha  
 8051636:	a1 2a e4 0c 08       	mov    eax,ds:0x80ce42a
 805163b:	8b 1d 2e e4 0c 08    	mov    ebx,DWORD PTR ds:0x80ce42e
 8051641:	8b 0d 32 e4 0c 08    	mov    ecx,DWORD PTR ds:0x80ce432
 8051647:	8b 15 36 e4 0c 08    	mov    edx,DWORD PTR ds:0x80ce436
 805164d:	be 00 00 00 00       	mov    esi,0x0
 8051652:	bf 00 00 00 00       	mov    edi,0x0
 8051657:	bd 00 00 00 00       	mov    ebp,0x0
 805165c:	39 d8                	cmp    eax,ebx
 805165e:	7c 1d                	jl     805167d <..@311._jmp>
 8051660:	a3 2a e4 0c 08       	mov    ds:0x80ce42a,eax
 8051665:	89 1d 2e e4 0c 08    	mov    DWORD PTR ds:0x80ce42e,ebx
 805166b:	89 0d 32 e4 0c 08    	mov    DWORD PTR ds:0x80ce432,ecx
 8051671:	89 15 36 e4 0c 08    	mov    DWORD PTR ds:0x80ce436,edx
 8051677:	61                   	popa   
 8051678:	83 c4 04             	add    esp,0x4
 805167b:	eb 1f                	jmp    805169c <..@311._end>

0805167d <..@311._jmp>:
 805167d:	a3 2a e4 0c 08       	mov    ds:0x80ce42a,eax
 8051682:	89 1d 2e e4 0c 08    	mov    DWORD PTR ds:0x80ce42e,ebx
 8051688:	89 0d 32 e4 0c 08    	mov    DWORD PTR ds:0x80ce432,ecx
 805168e:	89 15 36 e4 0c 08    	mov    DWORD PTR ds:0x80ce436,edx
 8051694:	61                   	popa   
 8051695:	83 c4 04             	add    esp,0x4
 8051698:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

0805169c <..@311._end>:
 805169c:	68 90 18 05 08       	push   0x8051890
 80516a1:	c7 05 2a e4 0c 08 00 	mov    DWORD PTR ds:0x80ce42a,0x0
 80516a8:	00 00 00 
 80516ab:	c7 05 2e e4 0c 08 00 	mov    DWORD PTR ds:0x80ce42e,0x0
 80516b2:	00 00 00 
 80516b5:	c7 05 32 e4 0c 08 00 	mov    DWORD PTR ds:0x80ce432,0x0
 80516bc:	00 00 00 
 80516bf:	c7 05 36 e4 0c 08 00 	mov    DWORD PTR ds:0x80ce436,0x0
 80516c6:	00 00 00 
 80516c9:	ff 35 42 44 0e 08    	push   DWORD PTR ds:0x80e4442
 80516cf:	8f 05 2a e4 0c 08    	pop    DWORD PTR ds:0x80ce42a
 80516d5:	6a 0b                	push   0xb
 80516d7:	8f 05 2e e4 0c 08    	pop    DWORD PTR ds:0x80ce42e
 80516dd:	60                   	pusha  
 80516de:	a1 2a e4 0c 08       	mov    eax,ds:0x80ce42a
 80516e3:	8b 1d 2e e4 0c 08    	mov    ebx,DWORD PTR ds:0x80ce42e
 80516e9:	8b 0d 32 e4 0c 08    	mov    ecx,DWORD PTR ds:0x80ce432
 80516ef:	8b 15 36 e4 0c 08    	mov    edx,DWORD PTR ds:0x80ce436
 80516f5:	be 00 00 00 00       	mov    esi,0x0
 80516fa:	bf 00 00 00 00       	mov    edi,0x0
 80516ff:	bd 00 00 00 00       	mov    ebp,0x0
 8051704:	39 d8                	cmp    eax,ebx
 8051706:	7d 1d                	jge    8051725 <..@328._jmp>
 8051708:	a3 2a e4 0c 08       	mov    ds:0x80ce42a,eax
 805170d:	89 1d 2e e4 0c 08    	mov    DWORD PTR ds:0x80ce42e,ebx
 8051713:	89 0d 32 e4 0c 08    	mov    DWORD PTR ds:0x80ce432,ecx
 8051719:	89 15 36 e4 0c 08    	mov    DWORD PTR ds:0x80ce436,edx
 805171f:	61                   	popa   
 8051720:	83 c4 04             	add    esp,0x4
 8051723:	eb 1f                	jmp    8051744 <..@328._end>

08051725 <..@328._jmp>:
 8051725:	a3 2a e4 0c 08       	mov    ds:0x80ce42a,eax
 805172a:	89 1d 2e e4 0c 08    	mov    DWORD PTR ds:0x80ce42e,ebx
 8051730:	89 0d 32 e4 0c 08    	mov    DWORD PTR ds:0x80ce432,ecx
 8051736:	89 15 36 e4 0c 08    	mov    DWORD PTR ds:0x80ce436,edx
 805173c:	61                   	popa   
 805173d:	83 c4 04             	add    esp,0x4
 8051740:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

08051744 <..@328._end>:
 8051744:	e9 a8 00 00 00       	jmp    80517f1 <..@273._end>

08051749 <..@273._less>:
 8051749:	68 90 18 05 08       	push   0x8051890
 805174e:	c7 05 2a e4 0c 08 00 	mov    DWORD PTR ds:0x80ce42a,0x0
 8051755:	00 00 00 
 8051758:	c7 05 2e e4 0c 08 00 	mov    DWORD PTR ds:0x80ce42e,0x0
 805175f:	00 00 00 
 8051762:	c7 05 32 e4 0c 08 00 	mov    DWORD PTR ds:0x80ce432,0x0
 8051769:	00 00 00 
 805176c:	c7 05 36 e4 0c 08 00 	mov    DWORD PTR ds:0x80ce436,0x0
 8051773:	00 00 00 
 8051776:	ff 35 42 44 0e 08    	push   DWORD PTR ds:0x80e4442
 805177c:	8f 05 2a e4 0c 08    	pop    DWORD PTR ds:0x80ce42a
 8051782:	6a 0b                	push   0xb
 8051784:	8f 05 2e e4 0c 08    	pop    DWORD PTR ds:0x80ce42e
 805178a:	60                   	pusha  
 805178b:	a1 2a e4 0c 08       	mov    eax,ds:0x80ce42a
 8051790:	8b 1d 2e e4 0c 08    	mov    ebx,DWORD PTR ds:0x80ce42e
 8051796:	8b 0d 32 e4 0c 08    	mov    ecx,DWORD PTR ds:0x80ce432
 805179c:	8b 15 36 e4 0c 08    	mov    edx,DWORD PTR ds:0x80ce436
 80517a2:	be 00 00 00 00       	mov    esi,0x0
 80517a7:	bf 00 00 00 00       	mov    edi,0x0
 80517ac:	bd 00 00 00 00       	mov    ebp,0x0
 80517b1:	39 d8                	cmp    eax,ebx
 80517b3:	7e 1d                	jle    80517d2 <..@345._jmp>
 80517b5:	a3 2a e4 0c 08       	mov    ds:0x80ce42a,eax
 80517ba:	89 1d 2e e4 0c 08    	mov    DWORD PTR ds:0x80ce42e,ebx
 80517c0:	89 0d 32 e4 0c 08    	mov    DWORD PTR ds:0x80ce432,ecx
 80517c6:	89 15 36 e4 0c 08    	mov    DWORD PTR ds:0x80ce436,edx
 80517cc:	61                   	popa   
 80517cd:	83 c4 04             	add    esp,0x4
 80517d0:	eb 1f                	jmp    80517f1 <..@273._end>

080517d2 <..@345._jmp>:
 80517d2:	a3 2a e4 0c 08       	mov    ds:0x80ce42a,eax
 80517d7:	89 1d 2e e4 0c 08    	mov    DWORD PTR ds:0x80ce42e,ebx
 80517dd:	89 0d 32 e4 0c 08    	mov    DWORD PTR ds:0x80ce432,ecx
 80517e3:	89 15 36 e4 0c 08    	mov    DWORD PTR ds:0x80ce436,edx
 80517e9:	61                   	popa   
 80517ea:	83 c4 04             	add    esp,0x4
 80517ed:	ff 64 24 fc          	jmp    DWORD PTR [esp-0x4]

080517f1 <..@273._end>:
 80517f1:	c7 05 2a e4 0c 08 00 	mov    DWORD PTR ds:0x80ce42a,0x0
 80517f8:	00 00 00 
 80517fb:	c7 05 2e e4 0c 08 00 	mov    DWORD PTR ds:0x80ce42e,0x0
 8051802:	00 00 00 
 8051805:	c7 05 32 e4 0c 08 00 	mov    DWORD PTR ds:0x80ce432,0x0
 805180c:	00 00 00 
 805180f:	c7 05 36 e4 0c 08 00 	mov    DWORD PTR ds:0x80ce436,0x0
 8051816:	00 00 00 
 8051819:	68 3a 9f 14 08       	push   0x8149f3a
 805181e:	8f 05 2a e4 0c 08    	pop    DWORD PTR ds:0x80ce42a
 8051824:	ff 35 42 44 0e 08    	push   DWORD PTR ds:0x80e4442
 805182a:	8f 05 2e e4 0c 08    	pop    DWORD PTR ds:0x80ce42e
 8051830:	60                   	pusha  
 8051831:	a1 2a e4 0c 08       	mov    eax,ds:0x80ce42a
 8051836:	8b 1d 2e e4 0c 08    	mov    ebx,DWORD PTR ds:0x80ce42e
 805183c:	8b 0d 32 e4 0c 08    	mov    ecx,DWORD PTR ds:0x80ce432
 8051842:	8b 15 36 e4 0c 08    	mov    edx,DWORD PTR ds:0x80ce436
 8051848:	be 00 00 00 00       	mov    esi,0x0
 805184d:	bf 00 00 00 00       	mov    edi,0x0
 8051852:	bd 00 00 00 00       	mov    ebp,0x0
 8051857:	8d 1c 98             	lea    ebx,[eax+ebx*4]
 805185a:	8b 03                	mov    eax,DWORD PTR [ebx]
 805185c:	a3 2a e4 0c 08       	mov    ds:0x80ce42a,eax
 8051861:	89 1d 2e e4 0c 08    	mov    DWORD PTR ds:0x80ce42e,ebx
 8051867:	89 0d 32 e4 0c 08    	mov    DWORD PTR ds:0x80ce432,ecx
 805186d:	89 15 36 e4 0c 08    	mov    DWORD PTR ds:0x80ce436,edx
 8051873:	61                   	popa   
 8051874:	ff 35 2a e4 0c 08    	push   DWORD PTR ds:0x80ce42a
 805187a:	8f 05 42 24 0d 08    	pop    DWORD PTR ds:0x80d2442
 8051880:	ff 35 42 24 0d 08    	push   DWORD PTR ds:0x80d2442
 8051886:	e8 af e7 ff ff       	call   805003a <__best_dswrite+0x2>
 805188b:	e9 df fc ff ff       	jmp    805156f <..@274.__jup>

08051890 <..@274.__jdown>:
 8051890:	c6 44 24 ff 00       	mov    BYTE PTR [esp-0x1],0x0
 8051895:	a3 3e e4 0c 08       	mov    ds:0x80ce43e,eax
 805189a:	b0 0a                	mov    al,0xa
 805189c:	88 44 24 fe          	mov    BYTE PTR [esp-0x2],al
 80518a0:	a1 3e e4 0c 08       	mov    eax,ds:0x80ce43e
 80518a5:	83 ec 02             	sub    esp,0x2
 80518a8:	e8 5f e3 ff ff       	call   804fc0c <__best_cput+0x2>
 80518ad:	68 db 18 05 08       	push   0x80518db
 80518b2:	e8 44 d2 ff ff       	call   804eafb <macro_expr_jmp>
 80518b7:	20 28                	and    BYTE PTR [eax],ch
 80518b9:	7c 20                	jl     80518db <..@384._expr>
 80518bb:	2a 64 2b 3d          	sub    ah,BYTE PTR [ebx+ebp*1+0x3d]
 80518bf:	31 32                	xor    DWORD PTR [edx],esi
 80518c1:	7c 20                	jl     80518e3 <..@384._expr+0x8>
 80518c3:	2a 64 2f 3d          	sub    ah,BYTE PTR [edi+ebp*1+0x3d]
 80518c7:	34 7c                	xor    al,0x7c
 80518c9:	20 2a                	and    BYTE PTR [edx],ch
 80518cb:	64 2a 3d 32 2a 2a 64 	sub    bh,BYTE PTR fs:0x642a2a32
 80518d2:	7c 20                	jl     80518f4 <..@128.__jdown+0x9>
 80518d4:	2a 64 2a 3d          	sub    ah,BYTE PTR [edx+ebp*1+0x3d]
 80518d8:	32 29                	xor    ch,BYTE PTR [ecx]
 80518da:	20                   	.byte 0x20

080518db <..@384._expr>:
 80518db:	ff 35 42 14 0d 08    	push   DWORD PTR ds:0x80d1442
 80518e1:	e8 47 f0 ff ff       	call   805092d <__best_dsprint+0x2>
 80518e6:	e9 ad f6 ff ff       	jmp    8050f98 <..@128.__jup>
