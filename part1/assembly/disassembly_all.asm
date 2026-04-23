
initv1:     file format elf64-x86-64


Disassembly of section .note.gnu.build-id:

0000000000000350 <.note.gnu.build-id>:
 350:	04 00                	add    $0x0,%al
 352:	00 00                	add    %al,(%rax)
 354:	14 00                	adc    $0x0,%al
 356:	00 00                	add    %al,(%rax)
 358:	03 00                	add    (%rax),%eax
 35a:	00 00                	add    %al,(%rax)
 35c:	47                   	rex.RXB
 35d:	4e 55                	rex.WRX push %rbp
 35f:	00 88 56 83 9e 6e    	add    %cl,0x6e9e8356(%rax)
 365:	6d                   	insl   (%dx),(%rdi)
 366:	06                   	(bad)
 367:	68 6b 91 85 11       	push   $0x1185916b
 36c:	d5 09 1c 7c          	{rex2 0x9} sbb $0x7c,%al
 370:	2e                   	cs
 371:	4b                   	rex.WXB
 372:	c7                   	.byte 0xc7
 373:	ac                   	lods   (%rsi),%al

Disassembly of section .interp:

0000000000000374 <.interp>:
 374:	2f                   	(bad)
 375:	6c                   	insb   (%dx),(%rdi)
 376:	69 62 36 34 2f 6c 64 	imul   $0x646c2f34,0x36(%rdx),%esp
 37d:	2d 6c 69 6e 75       	sub    $0x756e696c,%eax
 382:	78 2d                	js     3b1 <_init-0xc4f>
 384:	78 38                	js     3be <_init-0xc42>
 386:	36 2d 36 34 2e 73    	ss sub $0x732e3436,%eax
 38c:	6f                   	outsl  (%rsi),(%dx)
 38d:	2e 32 00             	cs xor (%rax),%al

Disassembly of section .gnu.hash:

0000000000000390 <.gnu.hash>:
 390:	01 00                	add    %eax,(%rax)
 392:	00 00                	add    %al,(%rax)
 394:	01 00                	add    %eax,(%rax)
 396:	00 00                	add    %al,(%rax)
 398:	01 00                	add    %eax,(%rax)
	...

Disassembly of section .dynsym:

00000000000003b0 <.dynsym>:
	...
 3c8:	06                   	(bad)
 3c9:	00 00                	add    %al,(%rax)
 3cb:	00 12                	add    %dl,(%rdx)
	...
 3dd:	00 00                	add    %al,(%rax)
 3df:	00 48 00             	add    %cl,0x0(%rax)
 3e2:	00 00                	add    %al,(%rax)
 3e4:	20 00                	and    %al,(%rax)
	...
 3f6:	00 00                	add    %al,(%rax)
 3f8:	01 00                	add    %eax,(%rax)
 3fa:	00 00                	add    %al,(%rax)
 3fc:	12 00                	adc    (%rax),%al
	...
 40e:	00 00                	add    %al,(%rax)
 410:	64 00 00             	add    %al,%fs:(%rax)
 413:	00 20                	add    %ah,(%rax)
	...
 425:	00 00                	add    %al,(%rax)
 427:	00 73 00             	add    %dh,0x0(%rbx)
 42a:	00 00                	add    %al,(%rax)
 42c:	20 00                	and    %al,(%rax)
	...
 43e:	00 00                	add    %al,(%rax)
 440:	18 00                	sbb    %al,(%rax)
 442:	00 00                	add    %al,(%rax)
 444:	22 00                	and    (%rax),%al
	...

Disassembly of section .dynstr:

0000000000000458 <.dynstr>:
 458:	00 70 75             	add    %dh,0x75(%rax)
 45b:	74 73                	je     4d0 <_init-0xb30>
 45d:	00 5f 5f             	add    %bl,0x5f(%rdi)
 460:	6c                   	insb   (%dx),(%rdi)
 461:	69 62 63 5f 73 74 61 	imul   $0x6174735f,0x63(%rdx),%esp
 468:	72 74                	jb     4de <_init-0xb22>
 46a:	5f                   	pop    %rdi
 46b:	6d                   	insl   (%dx),(%rdi)
 46c:	61                   	(bad)
 46d:	69 6e 00 5f 5f 63 78 	imul   $0x78635f5f,0x0(%rsi),%ebp
 474:	61                   	(bad)
 475:	5f                   	pop    %rdi
 476:	66 69 6e 61 6c 69    	imul   $0x696c,0x61(%rsi),%bp
 47c:	7a 65                	jp     4e3 <_init-0xb1d>
 47e:	00 6c 69 62          	add    %ch,0x62(%rcx,%rbp,2)
 482:	63 2e                	movsxd (%rsi),%ebp
 484:	73 6f                	jae    4f5 <_init-0xb0b>
 486:	2e 36 00 47 4c       	cs ss add %al,0x4c(%rdi)
 48b:	49                   	rex.WB
 48c:	42                   	rex.X
 48d:	43 5f                	rex.XB pop %r15
 48f:	32 2e                	xor    (%rsi),%ch
 491:	32 2e                	xor    (%rsi),%ch
 493:	35 00 47 4c 49       	xor    $0x494c4700,%eax
 498:	42                   	rex.X
 499:	43 5f                	rex.XB pop %r15
 49b:	32 2e                	xor    (%rsi),%ch
 49d:	33 34 00             	xor    (%rax,%rax,1),%esi
 4a0:	5f                   	pop    %rdi
 4a1:	49 54                	rex.WB push %r12
 4a3:	4d 5f                	rex.WRB pop %r15
 4a5:	64 65 72 65          	fs gs jb 50e <_init-0xaf2>
 4a9:	67 69 73 74 65 72 54 	imul   $0x4d547265,0x74(%ebx),%esi
 4b0:	4d 
 4b1:	43 6c                	rex.XB insb (%dx),(%rdi)
 4b3:	6f                   	outsl  (%rsi),(%dx)
 4b4:	6e                   	outsb  (%rsi),(%dx)
 4b5:	65 54                	gs push %rsp
 4b7:	61                   	(bad)
 4b8:	62 6c 65 00 5f       	(bad)
 4bd:	5f                   	pop    %rdi
 4be:	67 6d                	insl   (%dx),(%edi)
 4c0:	6f                   	outsl  (%rsi),(%dx)
 4c1:	6e                   	outsb  (%rsi),(%dx)
 4c2:	5f                   	pop    %rdi
 4c3:	73 74                	jae    539 <_init-0xac7>
 4c5:	61                   	(bad)
 4c6:	72 74                	jb     53c <_init-0xac4>
 4c8:	5f                   	pop    %rdi
 4c9:	5f                   	pop    %rdi
 4ca:	00 5f 49             	add    %bl,0x49(%rdi)
 4cd:	54                   	push   %rsp
 4ce:	4d 5f                	rex.WRB pop %r15
 4d0:	72 65                	jb     537 <_init-0xac9>
 4d2:	67 69 73 74 65 72 54 	imul   $0x4d547265,0x74(%ebx),%esi
 4d9:	4d 
 4da:	43 6c                	rex.XB insb (%dx),(%rdi)
 4dc:	6f                   	outsl  (%rsi),(%dx)
 4dd:	6e                   	outsb  (%rsi),(%dx)
 4de:	65 54                	gs push %rsp
 4e0:	61                   	(bad)
 4e1:	62                   	.byte 0x62
 4e2:	6c                   	insb   (%dx),(%rdi)
 4e3:	65                   	gs
	...

Disassembly of section .gnu.version:

00000000000004e6 <.gnu.version>:
 4e6:	00 00                	add    %al,(%rax)
 4e8:	02 00                	add    (%rax),%al
 4ea:	00 00                	add    %al,(%rax)
 4ec:	03 00                	add    (%rax),%eax
 4ee:	00 00                	add    %al,(%rax)
 4f0:	00 00                	add    %al,(%rax)
 4f2:	03 00                	add    (%rax),%eax

Disassembly of section .gnu.version_r:

00000000000004f8 <.gnu.version_r>:
 4f8:	01 00                	add    %eax,(%rax)
 4fa:	02 00                	add    (%rax),%al
 4fc:	27                   	(bad)
 4fd:	00 00                	add    %al,(%rax)
 4ff:	00 10                	add    %dl,(%rax)
 501:	00 00                	add    %al,(%rax)
 503:	00 00                	add    %al,(%rax)
 505:	00 00                	add    %al,(%rax)
 507:	00 75 1a             	add    %dh,0x1a(%rbp)
 50a:	69 09 00 00 03 00    	imul   $0x30000,(%rcx),%ecx
 510:	31 00                	xor    %eax,(%rax)
 512:	00 00                	add    %al,(%rax)
 514:	10 00                	adc    %al,(%rax)
 516:	00 00                	add    %al,(%rax)
 518:	b4 91                	mov    $0x91,%ah
 51a:	96                   	xchg   %eax,%esi
 51b:	06                   	(bad)
 51c:	00 00                	add    %al,(%rax)
 51e:	02 00                	add    (%rax),%al
 520:	3d 00 00 00 00       	cmp    $0x0,%eax
 525:	00 00                	add    %al,(%rax)
	...

Disassembly of section .rela.dyn:

0000000000000528 <.rela.dyn>:
 528:	d0 3d 00 00 00 00    	sarb   $1,0x0(%rip)        # 52e <_init-0xad2>
 52e:	00 00                	add    %al,(%rax)
 530:	08 00                	or     %al,(%rax)
 532:	00 00                	add    %al,(%rax)
 534:	00 00                	add    %al,(%rax)
 536:	00 00                	add    %al,(%rax)
 538:	30 11                	xor    %dl,(%rcx)
 53a:	00 00                	add    %al,(%rax)
 53c:	00 00                	add    %al,(%rax)
 53e:	00 00                	add    %al,(%rax)
 540:	d8 3d 00 00 00 00    	fdivrs 0x0(%rip)        # 546 <_init-0xaba>
 546:	00 00                	add    %al,(%rax)
 548:	08 00                	or     %al,(%rax)
 54a:	00 00                	add    %al,(%rax)
 54c:	00 00                	add    %al,(%rax)
 54e:	00 00                	add    %al,(%rax)
 550:	e0 10                	loopne 562 <_init-0xa9e>
 552:	00 00                	add    %al,(%rax)
 554:	00 00                	add    %al,(%rax)
 556:	00 00                	add    %al,(%rax)
 558:	10 40 00             	adc    %al,0x0(%rax)
 55b:	00 00                	add    %al,(%rax)
 55d:	00 00                	add    %al,(%rax)
 55f:	00 08                	add    %cl,(%rax)
 561:	00 00                	add    %al,(%rax)
 563:	00 00                	add    %al,(%rax)
 565:	00 00                	add    %al,(%rax)
 567:	00 10                	add    %dl,(%rax)
 569:	40 00 00             	rex add %al,(%rax)
 56c:	00 00                	add    %al,(%rax)
 56e:	00 00                	add    %al,(%rax)
 570:	c0 3f 00             	sarb   $0x0,(%rdi)
 573:	00 00                	add    %al,(%rax)
 575:	00 00                	add    %al,(%rax)
 577:	00 06                	add    %al,(%rsi)
 579:	00 00                	add    %al,(%rax)
 57b:	00 01                	add    %al,(%rcx)
	...
 585:	00 00                	add    %al,(%rax)
 587:	00 c8                	add    %cl,%al
 589:	3f                   	(bad)
 58a:	00 00                	add    %al,(%rax)
 58c:	00 00                	add    %al,(%rax)
 58e:	00 00                	add    %al,(%rax)
 590:	06                   	(bad)
 591:	00 00                	add    %al,(%rax)
 593:	00 02                	add    %al,(%rdx)
	...
 59d:	00 00                	add    %al,(%rax)
 59f:	00 d0                	add    %dl,%al
 5a1:	3f                   	(bad)
 5a2:	00 00                	add    %al,(%rax)
 5a4:	00 00                	add    %al,(%rax)
 5a6:	00 00                	add    %al,(%rax)
 5a8:	06                   	(bad)
 5a9:	00 00                	add    %al,(%rax)
 5ab:	00 04 00             	add    %al,(%rax,%rax,1)
	...
 5b6:	00 00                	add    %al,(%rax)
 5b8:	d8 3f                	fdivrs (%rdi)
 5ba:	00 00                	add    %al,(%rax)
 5bc:	00 00                	add    %al,(%rax)
 5be:	00 00                	add    %al,(%rax)
 5c0:	06                   	(bad)
 5c1:	00 00                	add    %al,(%rax)
 5c3:	00 05 00 00 00 00    	add    %al,0x0(%rip)        # 5c9 <_init-0xa37>
 5c9:	00 00                	add    %al,(%rax)
 5cb:	00 00                	add    %al,(%rax)
 5cd:	00 00                	add    %al,(%rax)
 5cf:	00 e0                	add    %ah,%al
 5d1:	3f                   	(bad)
 5d2:	00 00                	add    %al,(%rax)
 5d4:	00 00                	add    %al,(%rax)
 5d6:	00 00                	add    %al,(%rax)
 5d8:	06                   	(bad)
 5d9:	00 00                	add    %al,(%rax)
 5db:	00 06                	add    %al,(%rsi)
	...

Disassembly of section .rela.plt:

00000000000005e8 <.rela.plt>:
 5e8:	00 40 00             	add    %al,0x0(%rax)
 5eb:	00 00                	add    %al,(%rax)
 5ed:	00 00                	add    %al,(%rax)
 5ef:	00 07                	add    %al,(%rdi)
 5f1:	00 00                	add    %al,(%rax)
 5f3:	00 03                	add    %al,(%rbx)
	...

Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 c1 2f 00 00 	mov    0x2fc1(%rip),%rax        # 3fd0 <__gmon_start__>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	call   *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	ret

Disassembly of section .plt:

0000000000001020 <puts@plt-0x10>:
    1020:	ff 35 ca 2f 00 00    	push   0x2fca(%rip)        # 3ff0 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	ff 25 cc 2f 00 00    	jmp    *0x2fcc(%rip)        # 3ff8 <_GLOBAL_OFFSET_TABLE_+0x10>
    102c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000001030 <puts@plt>:
    1030:	ff 25 ca 2f 00 00    	jmp    *0x2fca(%rip)        # 4000 <puts@GLIBC_2.2.5>
    1036:	68 00 00 00 00       	push   $0x0
    103b:	e9 e0 ff ff ff       	jmp    1020 <_init+0x20>

Disassembly of section .text:

0000000000001040 <_start>:
    1040:	f3 0f 1e fa          	endbr64
    1044:	31 ed                	xor    %ebp,%ebp
    1046:	49 89 d1             	mov    %rdx,%r9
    1049:	5e                   	pop    %rsi
    104a:	48 89 e2             	mov    %rsp,%rdx
    104d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    1051:	50                   	push   %rax
    1052:	54                   	push   %rsp
    1053:	45 31 c0             	xor    %r8d,%r8d
    1056:	31 c9                	xor    %ecx,%ecx
    1058:	48 8d 3d da 00 00 00 	lea    0xda(%rip),%rdi        # 1139 <main>
    105f:	ff 15 5b 2f 00 00    	call   *0x2f5b(%rip)        # 3fc0 <__libc_start_main@GLIBC_2.34>
    1065:	f4                   	hlt
    1066:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    106d:	00 00 00 

0000000000001070 <deregister_tm_clones>:
    1070:	48 8d 3d a1 2f 00 00 	lea    0x2fa1(%rip),%rdi        # 4018 <__TMC_END__>
    1077:	48 8d 05 9a 2f 00 00 	lea    0x2f9a(%rip),%rax        # 4018 <__TMC_END__>
    107e:	48 39 f8             	cmp    %rdi,%rax
    1081:	74 15                	je     1098 <deregister_tm_clones+0x28>
    1083:	48 8b 05 3e 2f 00 00 	mov    0x2f3e(%rip),%rax        # 3fc8 <_ITM_deregisterTMCloneTable>
    108a:	48 85 c0             	test   %rax,%rax
    108d:	74 09                	je     1098 <deregister_tm_clones+0x28>
    108f:	ff e0                	jmp    *%rax
    1091:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1098:	c3                   	ret
    1099:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000010a0 <register_tm_clones>:
    10a0:	48 8d 3d 71 2f 00 00 	lea    0x2f71(%rip),%rdi        # 4018 <__TMC_END__>
    10a7:	48 8d 35 6a 2f 00 00 	lea    0x2f6a(%rip),%rsi        # 4018 <__TMC_END__>
    10ae:	48 29 fe             	sub    %rdi,%rsi
    10b1:	48 89 f0             	mov    %rsi,%rax
    10b4:	48 c1 ee 3f          	shr    $0x3f,%rsi
    10b8:	48 c1 f8 03          	sar    $0x3,%rax
    10bc:	48 01 c6             	add    %rax,%rsi
    10bf:	48 d1 fe             	sar    $1,%rsi
    10c2:	74 14                	je     10d8 <register_tm_clones+0x38>
    10c4:	48 8b 05 0d 2f 00 00 	mov    0x2f0d(%rip),%rax        # 3fd8 <_ITM_registerTMCloneTable>
    10cb:	48 85 c0             	test   %rax,%rax
    10ce:	74 08                	je     10d8 <register_tm_clones+0x38>
    10d0:	ff e0                	jmp    *%rax
    10d2:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    10d8:	c3                   	ret
    10d9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000010e0 <__do_global_dtors_aux>:
    10e0:	f3 0f 1e fa          	endbr64
    10e4:	80 3d 2d 2f 00 00 00 	cmpb   $0x0,0x2f2d(%rip)        # 4018 <__TMC_END__>
    10eb:	75 33                	jne    1120 <__do_global_dtors_aux+0x40>
    10ed:	55                   	push   %rbp
    10ee:	48 83 3d ea 2e 00 00 	cmpq   $0x0,0x2eea(%rip)        # 3fe0 <__cxa_finalize@GLIBC_2.2.5>
    10f5:	00 
    10f6:	48 89 e5             	mov    %rsp,%rbp
    10f9:	74 0d                	je     1108 <__do_global_dtors_aux+0x28>
    10fb:	48 8b 3d 0e 2f 00 00 	mov    0x2f0e(%rip),%rdi        # 4010 <__dso_handle>
    1102:	ff 15 d8 2e 00 00    	call   *0x2ed8(%rip)        # 3fe0 <__cxa_finalize@GLIBC_2.2.5>
    1108:	e8 63 ff ff ff       	call   1070 <deregister_tm_clones>
    110d:	c6 05 04 2f 00 00 01 	movb   $0x1,0x2f04(%rip)        # 4018 <__TMC_END__>
    1114:	5d                   	pop    %rbp
    1115:	c3                   	ret
    1116:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    111d:	00 00 00 
    1120:	c3                   	ret
    1121:	0f 1f 40 00          	nopl   0x0(%rax)
    1125:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
    112c:	00 00 00 00 

0000000000001130 <frame_dummy>:
    1130:	f3 0f 1e fa          	endbr64
    1134:	e9 67 ff ff ff       	jmp    10a0 <register_tm_clones>

0000000000001139 <main>:
    1139:	55                   	push   %rbp
    113a:	48 89 e5             	mov    %rsp,%rbp
    113d:	48 8d 05 c0 0e 00 00 	lea    0xec0(%rip),%rax        # 2004 <_IO_stdin_used+0x4>
    1144:	48 89 c7             	mov    %rax,%rdi
    1147:	e8 e4 fe ff ff       	call   1030 <puts@plt>
    114c:	b8 00 00 00 00       	mov    $0x0,%eax
    1151:	5d                   	pop    %rbp
    1152:	c3                   	ret

Disassembly of section .fini:

0000000000001154 <_fini>:
    1154:	f3 0f 1e fa          	endbr64
    1158:	48 83 ec 08          	sub    $0x8,%rsp
    115c:	48 83 c4 08          	add    $0x8,%rsp
    1160:	c3                   	ret

Disassembly of section .rodata:

0000000000002000 <_IO_stdin_used>:
    2000:	01 00                	add    %eax,(%rax)
    2002:	02 00                	add    (%rax),%al
    2004:	49 6e                	rex.WB outsb (%rsi),(%dx)
    2006:	69 74 69 61 6c 69 73 	imul   $0x6573696c,0x61(%rcx,%rbp,2),%esi
    200d:	65 
    200e:	64 20 66 69          	and    %ah,%fs:0x69(%rsi)
    2012:	72 73                	jb     2087 <__GNU_EH_FRAME_HDR+0x67>
    2014:	74 20                	je     2036 <__GNU_EH_FRAME_HDR+0x16>
    2016:	70 72                	jo     208a <__GNU_EH_FRAME_HDR+0x6a>
    2018:	6f                   	outsl  (%rsi),(%dx)
    2019:	67 72 61             	addr32 jb 207d <__GNU_EH_FRAME_HDR+0x5d>
    201c:	6d                   	insl   (%dx),(%rdi)
    201d:	21 00                	and    %eax,(%rax)

Disassembly of section .eh_frame_hdr:

0000000000002020 <__GNU_EH_FRAME_HDR>:
    2020:	01 1b                	add    %ebx,(%rbx)
    2022:	03 3b                	add    (%rbx),%edi
    2024:	24 00                	and    $0x0,%al
    2026:	00 00                	add    %al,(%rax)
    2028:	03 00                	add    (%rax),%eax
    202a:	00 00                	add    %al,(%rax)
    202c:	00 f0                	add    %dh,%al
    202e:	ff                   	(bad)
    202f:	ff 58 00             	lcall  *0x0(%rax)
    2032:	00 00                	add    %al,(%rax)
    2034:	20 f0                	and    %dh,%al
    2036:	ff                   	(bad)
    2037:	ff 40 00             	incl   0x0(%rax)
    203a:	00 00                	add    %al,(%rax)
    203c:	19 f1                	sbb    %esi,%ecx
    203e:	ff                   	(bad)
    203f:	ff                   	.byte 0xff
    2040:	80 00 00             	addb   $0x0,(%rax)
	...

Disassembly of section .eh_frame:

0000000000002048 <__FRAME_END__-0x78>:
    2048:	14 00                	adc    $0x0,%al
    204a:	00 00                	add    %al,(%rax)
    204c:	00 00                	add    %al,(%rax)
    204e:	00 00                	add    %al,(%rax)
    2050:	01 7a 52             	add    %edi,0x52(%rdx)
    2053:	00 01                	add    %al,(%rcx)
    2055:	78 10                	js     2067 <__GNU_EH_FRAME_HDR+0x47>
    2057:	01 1b                	add    %ebx,(%rbx)
    2059:	0c 07                	or     $0x7,%al
    205b:	08 90 01 00 00 14    	or     %dl,0x14000001(%rax)
    2061:	00 00                	add    %al,(%rax)
    2063:	00 1c 00             	add    %bl,(%rax,%rax,1)
    2066:	00 00                	add    %al,(%rax)
    2068:	d8 ef                	fsubr  %st(7),%st
    206a:	ff                   	(bad)
    206b:	ff 26                	jmp    *(%rsi)
    206d:	00 00                	add    %al,(%rax)
    206f:	00 00                	add    %al,(%rax)
    2071:	44 07                	rex.R (bad)
    2073:	10 00                	adc    %al,(%rax)
    2075:	00 00                	add    %al,(%rax)
    2077:	00 24 00             	add    %ah,(%rax,%rax,1)
    207a:	00 00                	add    %al,(%rax)
    207c:	34 00                	xor    $0x0,%al
    207e:	00 00                	add    %al,(%rax)
    2080:	a0 ef ff ff 20 00 00 	movabs 0x20ffffef,%al
    2087:	00 00 
    2089:	0e                   	(bad)
    208a:	10 46 0e             	adc    %al,0xe(%rsi)
    208d:	18 4a 0f             	sbb    %cl,0xf(%rdx)
    2090:	0b 77 08             	or     0x8(%rdi),%esi
    2093:	80 00 3f             	addb   $0x3f,(%rax)
    2096:	1a 3b                	sbb    (%rbx),%bh
    2098:	2a 33                	sub    (%rbx),%dh
    209a:	24 22                	and    $0x22,%al
    209c:	00 00                	add    %al,(%rax)
    209e:	00 00                	add    %al,(%rax)
    20a0:	1c 00                	sbb    $0x0,%al
    20a2:	00 00                	add    %al,(%rax)
    20a4:	5c                   	pop    %rsp
    20a5:	00 00                	add    %al,(%rax)
    20a7:	00 91 f0 ff ff 1a    	add    %dl,0x1afffff0(%rcx)
    20ad:	00 00                	add    %al,(%rax)
    20af:	00 00                	add    %al,(%rax)
    20b1:	41 0e                	rex.B (bad)
    20b3:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
    20b9:	55                   	push   %rbp
    20ba:	0c 07                	or     $0x7,%al
    20bc:	08 00                	or     %al,(%rax)
	...

00000000000020c0 <__FRAME_END__>:
    20c0:	00 00                	add    %al,(%rax)
	...

Disassembly of section .note.gnu.property:

00000000000020c8 <.note.gnu.property>:
    20c8:	04 00                	add    $0x0,%al
    20ca:	00 00                	add    %al,(%rax)
    20cc:	30 00                	xor    %al,(%rax)
    20ce:	00 00                	add    %al,(%rax)
    20d0:	05 00 00 00 47       	add    $0x47000000,%eax
    20d5:	4e 55                	rex.WRX push %rbp
    20d7:	00 02                	add    %al,(%rdx)
    20d9:	80 00 c0             	addb   $0xc0,(%rax)
    20dc:	04 00                	add    $0x0,%al
    20de:	00 00                	add    %al,(%rax)
    20e0:	01 00                	add    %eax,(%rax)
    20e2:	00 00                	add    %al,(%rax)
    20e4:	00 00                	add    %al,(%rax)
    20e6:	00 00                	add    %al,(%rax)
    20e8:	01 00                	add    %eax,(%rax)
    20ea:	01 c0                	add    %eax,%eax
    20ec:	04 00                	add    $0x0,%al
    20ee:	00 00                	add    %al,(%rax)
    20f0:	01 00                	add    %eax,(%rax)
    20f2:	00 00                	add    %al,(%rax)
    20f4:	00 00                	add    %al,(%rax)
    20f6:	00 00                	add    %al,(%rax)
    20f8:	02 00                	add    (%rax),%al
    20fa:	01 c0                	add    %eax,%eax
    20fc:	04 00                	add    $0x0,%al
    20fe:	00 00                	add    %al,(%rax)
    2100:	01 00                	add    %eax,(%rax)
    2102:	00 00                	add    %al,(%rax)
    2104:	00 00                	add    %al,(%rax)
	...

Disassembly of section .note.ABI-tag:

0000000000002108 <__abi_tag>:
    2108:	04 00                	add    $0x0,%al
    210a:	00 00                	add    %al,(%rax)
    210c:	10 00                	adc    %al,(%rax)
    210e:	00 00                	add    %al,(%rax)
    2110:	01 00                	add    %eax,(%rax)
    2112:	00 00                	add    %al,(%rax)
    2114:	47                   	rex.RXB
    2115:	4e 55                	rex.WRX push %rbp
    2117:	00 00                	add    %al,(%rax)
    2119:	00 00                	add    %al,(%rax)
    211b:	00 04 00             	add    %al,(%rax,%rax,1)
    211e:	00 00                	add    %al,(%rax)
    2120:	04 00                	add    $0x0,%al
    2122:	00 00                	add    %al,(%rax)
    2124:	00 00                	add    %al,(%rax)
	...

Disassembly of section .init_array:

0000000000003dd0 <__frame_dummy_init_array_entry>:
    3dd0:	30 11                	xor    %dl,(%rcx)
    3dd2:	00 00                	add    %al,(%rax)
    3dd4:	00 00                	add    %al,(%rax)
	...

Disassembly of section .fini_array:

0000000000003dd8 <__do_global_dtors_aux_fini_array_entry>:
    3dd8:	e0 10                	loopne 3dea <_DYNAMIC+0xa>
    3dda:	00 00                	add    %al,(%rax)
    3ddc:	00 00                	add    %al,(%rax)
	...

Disassembly of section .dynamic:

0000000000003de0 <_DYNAMIC>:
    3de0:	01 00                	add    %eax,(%rax)
    3de2:	00 00                	add    %al,(%rax)
    3de4:	00 00                	add    %al,(%rax)
    3de6:	00 00                	add    %al,(%rax)
    3de8:	27                   	(bad)
    3de9:	00 00                	add    %al,(%rax)
    3deb:	00 00                	add    %al,(%rax)
    3ded:	00 00                	add    %al,(%rax)
    3def:	00 0c 00             	add    %cl,(%rax,%rax,1)
    3df2:	00 00                	add    %al,(%rax)
    3df4:	00 00                	add    %al,(%rax)
    3df6:	00 00                	add    %al,(%rax)
    3df8:	00 10                	add    %dl,(%rax)
    3dfa:	00 00                	add    %al,(%rax)
    3dfc:	00 00                	add    %al,(%rax)
    3dfe:	00 00                	add    %al,(%rax)
    3e00:	0d 00 00 00 00       	or     $0x0,%eax
    3e05:	00 00                	add    %al,(%rax)
    3e07:	00 54 11 00          	add    %dl,0x0(%rcx,%rdx,1)
    3e0b:	00 00                	add    %al,(%rax)
    3e0d:	00 00                	add    %al,(%rax)
    3e0f:	00 19                	add    %bl,(%rcx)
    3e11:	00 00                	add    %al,(%rax)
    3e13:	00 00                	add    %al,(%rax)
    3e15:	00 00                	add    %al,(%rax)
    3e17:	00 d0                	add    %dl,%al
    3e19:	3d 00 00 00 00       	cmp    $0x0,%eax
    3e1e:	00 00                	add    %al,(%rax)
    3e20:	1b 00                	sbb    (%rax),%eax
    3e22:	00 00                	add    %al,(%rax)
    3e24:	00 00                	add    %al,(%rax)
    3e26:	00 00                	add    %al,(%rax)
    3e28:	08 00                	or     %al,(%rax)
    3e2a:	00 00                	add    %al,(%rax)
    3e2c:	00 00                	add    %al,(%rax)
    3e2e:	00 00                	add    %al,(%rax)
    3e30:	1a 00                	sbb    (%rax),%al
    3e32:	00 00                	add    %al,(%rax)
    3e34:	00 00                	add    %al,(%rax)
    3e36:	00 00                	add    %al,(%rax)
    3e38:	d8 3d 00 00 00 00    	fdivrs 0x0(%rip)        # 3e3e <_DYNAMIC+0x5e>
    3e3e:	00 00                	add    %al,(%rax)
    3e40:	1c 00                	sbb    $0x0,%al
    3e42:	00 00                	add    %al,(%rax)
    3e44:	00 00                	add    %al,(%rax)
    3e46:	00 00                	add    %al,(%rax)
    3e48:	08 00                	or     %al,(%rax)
    3e4a:	00 00                	add    %al,(%rax)
    3e4c:	00 00                	add    %al,(%rax)
    3e4e:	00 00                	add    %al,(%rax)
    3e50:	f5                   	cmc
    3e51:	fe                   	(bad)
    3e52:	ff 6f 00             	ljmp   *0x0(%rdi)
    3e55:	00 00                	add    %al,(%rax)
    3e57:	00 90 03 00 00 00    	add    %dl,0x3(%rax)
    3e5d:	00 00                	add    %al,(%rax)
    3e5f:	00 05 00 00 00 00    	add    %al,0x0(%rip)        # 3e65 <_DYNAMIC+0x85>
    3e65:	00 00                	add    %al,(%rax)
    3e67:	00 58 04             	add    %bl,0x4(%rax)
    3e6a:	00 00                	add    %al,(%rax)
    3e6c:	00 00                	add    %al,(%rax)
    3e6e:	00 00                	add    %al,(%rax)
    3e70:	06                   	(bad)
    3e71:	00 00                	add    %al,(%rax)
    3e73:	00 00                	add    %al,(%rax)
    3e75:	00 00                	add    %al,(%rax)
    3e77:	00 b0 03 00 00 00    	add    %dh,0x3(%rax)
    3e7d:	00 00                	add    %al,(%rax)
    3e7f:	00 0a                	add    %cl,(%rdx)
    3e81:	00 00                	add    %al,(%rax)
    3e83:	00 00                	add    %al,(%rax)
    3e85:	00 00                	add    %al,(%rax)
    3e87:	00 8d 00 00 00 00    	add    %cl,0x0(%rbp)
    3e8d:	00 00                	add    %al,(%rax)
    3e8f:	00 0b                	add    %cl,(%rbx)
    3e91:	00 00                	add    %al,(%rax)
    3e93:	00 00                	add    %al,(%rax)
    3e95:	00 00                	add    %al,(%rax)
    3e97:	00 18                	add    %bl,(%rax)
    3e99:	00 00                	add    %al,(%rax)
    3e9b:	00 00                	add    %al,(%rax)
    3e9d:	00 00                	add    %al,(%rax)
    3e9f:	00 15 00 00 00 00    	add    %dl,0x0(%rip)        # 3ea5 <_DYNAMIC+0xc5>
	...
    3ead:	00 00                	add    %al,(%rax)
    3eaf:	00 03                	add    %al,(%rbx)
    3eb1:	00 00                	add    %al,(%rax)
    3eb3:	00 00                	add    %al,(%rax)
    3eb5:	00 00                	add    %al,(%rax)
    3eb7:	00 e8                	add    %ch,%al
    3eb9:	3f                   	(bad)
    3eba:	00 00                	add    %al,(%rax)
    3ebc:	00 00                	add    %al,(%rax)
    3ebe:	00 00                	add    %al,(%rax)
    3ec0:	02 00                	add    (%rax),%al
    3ec2:	00 00                	add    %al,(%rax)
    3ec4:	00 00                	add    %al,(%rax)
    3ec6:	00 00                	add    %al,(%rax)
    3ec8:	18 00                	sbb    %al,(%rax)
    3eca:	00 00                	add    %al,(%rax)
    3ecc:	00 00                	add    %al,(%rax)
    3ece:	00 00                	add    %al,(%rax)
    3ed0:	14 00                	adc    $0x0,%al
    3ed2:	00 00                	add    %al,(%rax)
    3ed4:	00 00                	add    %al,(%rax)
    3ed6:	00 00                	add    %al,(%rax)
    3ed8:	07                   	(bad)
    3ed9:	00 00                	add    %al,(%rax)
    3edb:	00 00                	add    %al,(%rax)
    3edd:	00 00                	add    %al,(%rax)
    3edf:	00 17                	add    %dl,(%rdi)
    3ee1:	00 00                	add    %al,(%rax)
    3ee3:	00 00                	add    %al,(%rax)
    3ee5:	00 00                	add    %al,(%rax)
    3ee7:	00 e8                	add    %ch,%al
    3ee9:	05 00 00 00 00       	add    $0x0,%eax
    3eee:	00 00                	add    %al,(%rax)
    3ef0:	07                   	(bad)
    3ef1:	00 00                	add    %al,(%rax)
    3ef3:	00 00                	add    %al,(%rax)
    3ef5:	00 00                	add    %al,(%rax)
    3ef7:	00 28                	add    %ch,(%rax)
    3ef9:	05 00 00 00 00       	add    $0x0,%eax
    3efe:	00 00                	add    %al,(%rax)
    3f00:	08 00                	or     %al,(%rax)
    3f02:	00 00                	add    %al,(%rax)
    3f04:	00 00                	add    %al,(%rax)
    3f06:	00 00                	add    %al,(%rax)
    3f08:	c0 00 00             	rolb   $0x0,(%rax)
    3f0b:	00 00                	add    %al,(%rax)
    3f0d:	00 00                	add    %al,(%rax)
    3f0f:	00 09                	add    %cl,(%rcx)
    3f11:	00 00                	add    %al,(%rax)
    3f13:	00 00                	add    %al,(%rax)
    3f15:	00 00                	add    %al,(%rax)
    3f17:	00 18                	add    %bl,(%rax)
    3f19:	00 00                	add    %al,(%rax)
    3f1b:	00 00                	add    %al,(%rax)
    3f1d:	00 00                	add    %al,(%rax)
    3f1f:	00 fb                	add    %bh,%bl
    3f21:	ff                   	(bad)
    3f22:	ff 6f 00             	ljmp   *0x0(%rdi)
    3f25:	00 00                	add    %al,(%rax)
    3f27:	00 00                	add    %al,(%rax)
    3f29:	00 00                	add    %al,(%rax)
    3f2b:	08 00                	or     %al,(%rax)
    3f2d:	00 00                	add    %al,(%rax)
    3f2f:	00 fe                	add    %bh,%dh
    3f31:	ff                   	(bad)
    3f32:	ff 6f 00             	ljmp   *0x0(%rdi)
    3f35:	00 00                	add    %al,(%rax)
    3f37:	00 f8                	add    %bh,%al
    3f39:	04 00                	add    $0x0,%al
    3f3b:	00 00                	add    %al,(%rax)
    3f3d:	00 00                	add    %al,(%rax)
    3f3f:	00 ff                	add    %bh,%bh
    3f41:	ff                   	(bad)
    3f42:	ff 6f 00             	ljmp   *0x0(%rdi)
    3f45:	00 00                	add    %al,(%rax)
    3f47:	00 01                	add    %al,(%rcx)
    3f49:	00 00                	add    %al,(%rax)
    3f4b:	00 00                	add    %al,(%rax)
    3f4d:	00 00                	add    %al,(%rax)
    3f4f:	00 f0                	add    %dh,%al
    3f51:	ff                   	(bad)
    3f52:	ff 6f 00             	ljmp   *0x0(%rdi)
    3f55:	00 00                	add    %al,(%rax)
    3f57:	00 e6                	add    %ah,%dh
    3f59:	04 00                	add    $0x0,%al
    3f5b:	00 00                	add    %al,(%rax)
    3f5d:	00 00                	add    %al,(%rax)
    3f5f:	00 f9                	add    %bh,%cl
    3f61:	ff                   	(bad)
    3f62:	ff 6f 00             	ljmp   *0x0(%rdi)
    3f65:	00 00                	add    %al,(%rax)
    3f67:	00 03                	add    %al,(%rbx)
	...

Disassembly of section .got:

0000000000003fc0 <.got>:
	...

Disassembly of section .got.plt:

0000000000003fe8 <_GLOBAL_OFFSET_TABLE_>:
    3fe8:	e0 3d                	loopne 4027 <_end+0x7>
	...
    3ffe:	00 00                	add    %al,(%rax)
    4000:	36 10 00             	ss adc %al,(%rax)
    4003:	00 00                	add    %al,(%rax)
    4005:	00 00                	add    %al,(%rax)
	...

Disassembly of section .data:

0000000000004008 <__data_start>:
	...

0000000000004010 <__dso_handle>:
    4010:	10 40 00             	adc    %al,0x0(%rax)
    4013:	00 00                	add    %al,(%rax)
    4015:	00 00                	add    %al,(%rax)
	...

Disassembly of section .comment:

0000000000000000 <.comment>:
   0:	47                   	rex.RXB
   1:	43                   	rex.XB
   2:	43 3a 20             	rex.XB cmp (%r8),%spl
   5:	28 47 4e             	sub    %al,0x4e(%rdi)
   8:	55                   	push   %rbp
   9:	29 20                	sub    %esp,(%rax)
   b:	31 35 2e 32 2e 31    	xor    %esi,0x312e322e(%rip)        # 312e323f <_end+0x312df21f>
  11:	20 32                	and    %dh,(%rdx)
  13:	30 32                	xor    %dh,(%rdx)
  15:	36 30 32             	ss xor %dh,(%rdx)
  18:	30 39                	xor    %bh,(%rcx)
	...
