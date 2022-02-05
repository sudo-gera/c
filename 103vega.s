	.arch armv8-a
	.text
Ltext0:
	.cstring
	.align	3
lC0:
	.ascii "%zu\0"
	.align	3
lC1:
	.ascii " %c\0"
	.align	3
lC2:
	.ascii "%i\0"
	.align	3
lC3:
	.ascii "%i\12\0"
	.text
	.align	2
	.globl _main
_main:
LFB1:
	.file 1 "103vega.cpp"
	.loc 1 3 11
	sub	sp, sp, #112
LCFI0:
	stp	x29, x30, [sp, 16]
LCFI1:
	add	x29, sp, 16
	.loc 1 4 23
	mov	x0, 6784
	movk	x0, 0x6, lsl 16
	bl	__Znam
	str	x0, [sp, 64]
	.loc 1 5 23
	mov	x0, 6784
	movk	x0, 0x6, lsl 16
	bl	__Znam
	str	x0, [sp, 56]
	.loc 1 6 10
	str	xzr, [sp, 104]
	.loc 1 6 15
	str	xzr, [sp, 96]
	.loc 1 6 20
	str	xzr, [sp, 88]
	.loc 1 6 25
	str	xzr, [sp, 80]
	.loc 1 8 7
	add	x0, sp, 48
	str	x0, [sp]
	adrp	x0, lC0@GOTPAGE
	ldr	x0, [x0, lC0@GOTPAGEOFF];momd
	bl	_scanf
LBB2:
	.loc 1 9 14
	str	xzr, [sp, 72]
	.loc 1 9 2
	b	L2
L12:
LBB3:
	.loc 1 12 8
	add	x0, sp, 47
	str	x0, [sp]
	adrp	x0, lC1@GOTPAGE
	ldr	x0, [x0, lC1@GOTPAGEOFF];momd
	bl	_scanf
	.loc 1 13 10
	ldrsb	w0, [sp, 47]
	.loc 1 13 3
	cmp	w0, 45
	beq	L3
	cmp	w0, 45
	bgt	L4
	cmp	w0, 42
	beq	L5
	cmp	w0, 43
	bne	L4
	.loc 1 15 10
	add	x0, sp, 40
	str	x0, [sp]
	adrp	x0, lC2@GOTPAGE
	ldr	x0, [x0, lC2@GOTPAGEOFF];momd
	bl	_scanf
	.loc 1 16 7
	ldr	x0, [sp, 80]
	.loc 1 16 9
	lsl	x0, x0, 2
	ldr	x1, [sp, 56]
	add	x0, x1, x0
	.loc 1 16 10
	ldr	w1, [sp, 40]
	str	w1, [x0]
	.loc 1 17 7
	ldr	x0, [sp, 80]
	add	x0, x0, 1
	str	x0, [sp, 80]
	.loc 1 18 7
	ldr	x0, [sp, 80]
	mov	x1, 57609
	movk	x1, 0xc6d1, lsl 16
	movk	x1, 0x6b11, lsl 32
	movk	x1, 0x29f1, lsl 48
	smulh	x1, x0, x1
	asr	x2, x1, 14
	asr	x1, x0, 63
	sub	x2, x2, x1
	mov	x1, 34464
	movk	x1, 0x1, lsl 16
	mul	x1, x2, x1
	sub	x0, x0, x1
	str	x0, [sp, 80]
	.loc 1 19 5
	b	L4
L5:
	.loc 1 21 10
	add	x0, sp, 40
	str	x0, [sp]
	adrp	x0, lC2@GOTPAGE
	ldr	x0, [x0, lC2@GOTPAGEOFF];momd
	bl	_scanf
	.loc 1 22 5
	b	L6
L7:
	.loc 1 23 8
	ldr	x0, [sp, 88]
	sub	x0, x0, #1
	str	x0, [sp, 88]
	.loc 1 24 8
	ldr	x0, [sp, 88]
	mov	x1, 57609
	movk	x1, 0xc6d1, lsl 16
	movk	x1, 0x6b11, lsl 32
	movk	x1, 0x29f1, lsl 48
	smulh	x1, x0, x1
	asr	x2, x1, 14
	asr	x1, x0, 63
	sub	x2, x2, x1
	mov	x1, 34464
	movk	x1, 0x1, lsl 16
	mul	x1, x2, x1
	sub	x0, x0, x1
	str	x0, [sp, 88]
	.loc 1 25 8
	ldr	x0, [sp, 96]
	sub	x0, x0, #1
	str	x0, [sp, 96]
	.loc 1 26 8
	ldr	x0, [sp, 96]
	mov	x1, 57609
	movk	x1, 0xc6d1, lsl 16
	movk	x1, 0x6b11, lsl 32
	movk	x1, 0x29f1, lsl 48
	smulh	x1, x0, x1
	asr	x2, x1, 14
	asr	x1, x0, 63
	sub	x2, x2, x1
	mov	x1, 34464
	movk	x1, 0x1, lsl 16
	mul	x1, x2, x1
	sub	x0, x0, x1
	str	x0, [sp, 96]
	.loc 1 27 14
	ldr	x0, [sp, 96]
	.loc 1 27 16
	lsl	x0, x0, 2
	ldr	x1, [sp, 64]
	add	x1, x1, x0
	.loc 1 27 8
	ldr	x0, [sp, 88]
	.loc 1 27 10
	lsl	x0, x0, 2
	ldr	x2, [sp, 56]
	add	x0, x2, x0
	.loc 1 27 16
	ldr	w1, [x1]
	.loc 1 27 11
	str	w1, [x0]
L6:
	.loc 1 22 13
	ldr	x1, [sp, 96]
	ldr	x0, [sp, 104]
	sub	x1, x1, x0
	.loc 1 22 19
	ldr	x2, [sp, 80]
	ldr	x0, [sp, 88]
	sub	x0, x2, x0
	.loc 1 22 16
	cmp	x1, x0
	bgt	L7
	.loc 1 29 5
	b	L8
L9:
	.loc 1 30 14
	ldr	x0, [sp, 88]
	.loc 1 30 16
	lsl	x0, x0, 2
	ldr	x1, [sp, 56]
	add	x1, x1, x0
	.loc 1 30 8
	ldr	x0, [sp, 96]
	.loc 1 30 10
	lsl	x0, x0, 2
	ldr	x2, [sp, 64]
	add	x0, x2, x0
	.loc 1 30 16
	ldr	w1, [x1]
	.loc 1 30 11
	str	w1, [x0]
	.loc 1 31 8
	ldr	x0, [sp, 88]
	add	x0, x0, 1
	str	x0, [sp, 88]
	.loc 1 32 8
	ldr	x0, [sp, 88]
	mov	x1, 57609
	movk	x1, 0xc6d1, lsl 16
	movk	x1, 0x6b11, lsl 32
	movk	x1, 0x29f1, lsl 48
	smulh	x1, x0, x1
	asr	x2, x1, 14
	asr	x1, x0, 63
	sub	x2, x2, x1
	mov	x1, 34464
	movk	x1, 0x1, lsl 16
	mul	x1, x2, x1
	sub	x0, x0, x1
	str	x0, [sp, 88]
	.loc 1 33 8
	ldr	x0, [sp, 96]
	add	x0, x0, 1
	str	x0, [sp, 96]
	.loc 1 34 8
	ldr	x0, [sp, 96]
	mov	x1, 57609
	movk	x1, 0xc6d1, lsl 16
	movk	x1, 0x6b11, lsl 32
	movk	x1, 0x29f1, lsl 48
	smulh	x1, x0, x1
	asr	x2, x1, 14
	asr	x1, x0, 63
	sub	x2, x2, x1
	mov	x1, 34464
	movk	x1, 0x1, lsl 16
	mul	x1, x2, x1
	sub	x0, x0, x1
	str	x0, [sp, 96]
L8:
	.loc 1 29 13
	ldr	x1, [sp, 96]
	ldr	x0, [sp, 104]
	sub	x1, x1, x0
	.loc 1 29 19
	ldr	x2, [sp, 80]
	ldr	x0, [sp, 88]
	sub	x0, x2, x0
	.loc 1 29 16
	cmp	x1, x0
	blt	L9
	.loc 1 36 7
	ldr	x0, [sp, 88]
	sub	x0, x0, #1
	str	x0, [sp, 88]
	.loc 1 37 7
	ldr	x0, [sp, 88]
	mov	x1, 57609
	movk	x1, 0xc6d1, lsl 16
	movk	x1, 0x6b11, lsl 32
	movk	x1, 0x29f1, lsl 48
	smulh	x1, x0, x1
	asr	x2, x1, 14
	asr	x1, x0, 63
	sub	x2, x2, x1
	mov	x1, 34464
	movk	x1, 0x1, lsl 16
	mul	x1, x2, x1
	sub	x0, x0, x1
	str	x0, [sp, 88]
	.loc 1 38 7
	ldr	x0, [sp, 88]
	.loc 1 38 9
	lsl	x0, x0, 2
	ldr	x1, [sp, 56]
	add	x0, x1, x0
	.loc 1 38 10
	ldr	w1, [sp, 40]
	str	w1, [x0]
	.loc 1 39 5
	b	L4
L3:
	.loc 1 41 5
	ldr	x1, [sp, 96]
	ldr	x0, [sp, 104]
	cmp	x1, x0
	beq	L10
	.loc 1 42 22
	ldr	x0, [sp, 104]
	.loc 1 42 24
	lsl	x0, x0, 2
	ldr	x1, [sp, 64]
	add	x0, x1, x0
	.loc 1 42 12
	ldr	w0, [x0]
	str	w0, [sp]
	adrp	x0, lC3@GOTPAGE
	ldr	x0, [x0, lC3@GOTPAGEOFF];momd
	bl	_printf
	.loc 1 43 8
	ldr	x0, [sp, 104]
	add	x0, x0, 1
	str	x0, [sp, 104]
	.loc 1 44 8
	ldr	x0, [sp, 104]
	mov	x1, 57609
	movk	x1, 0xc6d1, lsl 16
	movk	x1, 0x6b11, lsl 32
	movk	x1, 0x29f1, lsl 48
	smulh	x1, x0, x1
	asr	x2, x1, 14
	asr	x1, x0, 63
	sub	x2, x2, x1
	mov	x1, 34464
	movk	x1, 0x1, lsl 16
	mul	x1, x2, x1
	sub	x0, x0, x1
	str	x0, [sp, 104]
	.loc 1 50 5
	b	L14
L10:
	.loc 1 46 22
	ldr	x0, [sp, 104]
	.loc 1 46 24
	lsl	x0, x0, 2
	ldr	x1, [sp, 64]
	add	x0, x1, x0
	.loc 1 46 12
	ldr	w0, [x0]
	str	w0, [sp]
	adrp	x0, lC3@GOTPAGE
	ldr	x0, [x0, lC3@GOTPAGEOFF];momd
	bl	_printf
	.loc 1 47 8
	ldr	x0, [sp, 104]
	add	x0, x0, 1
	str	x0, [sp, 104]
	.loc 1 48 8
	ldr	x0, [sp, 104]
	mov	x1, 57609
	movk	x1, 0xc6d1, lsl 16
	movk	x1, 0x6b11, lsl 32
	movk	x1, 0x29f1, lsl 48
	smulh	x1, x0, x1
	asr	x2, x1, 14
	asr	x1, x0, 63
	sub	x2, x2, x1
	mov	x1, 34464
	movk	x1, 0x1, lsl 16
	mul	x1, x2, x1
	sub	x0, x0, x1
	str	x0, [sp, 104]
L14:
	.loc 1 50 5
	nop
L4:
LBE3:
	.loc 1 9 2
	ldr	x0, [sp, 72]
	add	x0, x0, 1
	str	x0, [sp, 72]
L2:
	.loc 1 9 19
	ldr	x0, [sp, 48]
	ldr	x1, [sp, 72]
	cmp	x1, x0
	bcc	L12
LBE2:
	.loc 1 53 1
	mov	w0, 0
	ldp	x29, x30, [sp, 16]
	add	sp, sp, 112
LCFI2:
	ret
LFE1:
	.section __DWARF,__debug_frame,regular,debug
Lsection__debug_frame:
Lframe0:
	.set L$set$0,LECIE0-LSCIE0
	.long L$set$0
LSCIE0:
	.long	0xffffffff
	.byte	0x1
	.ascii "\0"
	.uleb128 0x1
	.sleb128 -8
	.byte	0x1e
	.byte	0xc
	.uleb128 0x1f
	.uleb128 0
	.align	3
LECIE0:
LSFDE0:
	.set L$set$1,LEFDE0-LASFDE0
	.long L$set$1
LASFDE0:
	.set L$set$2,Lframe0-Lsection__debug_frame
	.long L$set$2
	.quad	LFB1
	.set L$set$3,LFE1-LFB1
	.quad L$set$3
	.byte	0x4
	.set L$set$4,LCFI0-LFB1
	.long L$set$4
	.byte	0xe
	.uleb128 0x70
	.byte	0x4
	.set L$set$5,LCFI1-LCFI0
	.long L$set$5
	.byte	0x9d
	.uleb128 0xc
	.byte	0x9e
	.uleb128 0xb
	.byte	0x4
	.set L$set$6,LCFI2-LCFI1
	.long L$set$6
	.byte	0xdd
	.byte	0xde
	.byte	0xe
	.uleb128 0
	.align	3
LEFDE0:
	.section __TEXT,__eh_frame,coalesced,no_toc+strip_static_syms+live_support
EH_frame1:
	.set L$set$7,LECIE1-LSCIE1
	.long L$set$7
LSCIE1:
	.long	0
	.byte	0x1
	.ascii "zR\0"
	.uleb128 0x1
	.sleb128 -8
	.byte	0x1e
	.uleb128 0x1
	.byte	0x10
	.byte	0xc
	.uleb128 0x1f
	.uleb128 0
	.align	3
LECIE1:
LSFDE3:
	.set L$set$8,LEFDE3-LASFDE3
	.long L$set$8
LASFDE3:
	.long	LASFDE3-EH_frame1
	.quad	LFB1-.
	.set L$set$9,LFE1-LFB1
	.quad L$set$9
	.uleb128 0
	.byte	0x4
	.set L$set$10,LCFI0-LFB1
	.long L$set$10
	.byte	0xe
	.uleb128 0x70
	.byte	0x4
	.set L$set$11,LCFI1-LCFI0
	.long L$set$11
	.byte	0x9d
	.uleb128 0xc
	.byte	0x9e
	.uleb128 0xb
	.byte	0x4
	.set L$set$12,LCFI2-LCFI1
	.long L$set$12
	.byte	0xdd
	.byte	0xde
	.byte	0xe
	.uleb128 0
	.align	3
LEFDE3:
	.text
Letext0:
	.file 2 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/arm/_types.h"
	.file 3 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_int64_t.h"
	.file 4 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types/_size_t.h"
	.file 5 "/opt/homebrew/Cellar/gcc/11.2.0/lib/gcc/11/gcc/aarch64-apple-darwin20/11.1.0/include-fixed/stdio.h"
	.section __DWARF,__debug_info,regular,debug
Lsection__debug_info:
Ldebug_info0:
	.long	0x295
	.short	0x2
	.set L$set$13,Ldebug_abbrev0-Lsection__debug_abbrev
	.long L$set$13
	.byte	0x8
	.uleb128 0x1
	.ascii "GNU C++23 11.1.0 -fPIC -mmacosx-version-min=11.1.0 -mlittle-endian -mabi=lp64 -g -std=c++23\0"
	.byte	0x4
	.ascii "103vega.cpp\0"
	.ascii "/Users/gera/c\0"
	.byte	0x1
	.quad	Ltext0
	.quad	Letext0
	.set L$set$14,Ldebug_line0-Lsection__debug_line
	.long L$set$14
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.ascii "char\0"
	.uleb128 0x3
	.long	0x98
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.ascii "signed char\0"
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.ascii "unsigned char\0"
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.ascii "short int\0"
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.ascii "short unsigned int\0"
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.ascii "int\0"
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.ascii "unsigned int\0"
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.ascii "long long int\0"
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.ascii "long long unsigned int\0"
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.ascii "long int\0"
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.ascii "long unsigned int\0"
	.uleb128 0x4
	.ascii "__darwin_size_t\0"
	.byte	0x2
	.byte	0x46
	.byte	0x21
	.long	0x136
	.uleb128 0x4
	.ascii "int64_t\0"
	.byte	0x3
	.byte	0x1e
	.byte	0x21
	.long	0xff
	.uleb128 0x4
	.ascii "size_t\0"
	.byte	0x4
	.byte	0x1f
	.byte	0x20
	.long	0x14b
	.uleb128 0x5
	.byte	0x8
	.long	0xa0
	.uleb128 0x6
	.byte	0x1
	.ascii "printf\0"
	.byte	0x5
	.byte	0xb8
	.byte	0x6
	.long	0xe8
	.byte	0x1
	.long	0x1a4
	.uleb128 0x7
	.long	0x182
	.uleb128 0x8
	.byte	0
	.uleb128 0x6
	.byte	0x1
	.ascii "scanf\0"
	.byte	0x5
	.byte	0xbf
	.byte	0x6
	.long	0xe8
	.byte	0x1
	.long	0x1bf
	.uleb128 0x7
	.long	0x182
	.uleb128 0x8
	.byte	0
	.uleb128 0x9
	.byte	0x1
	.ascii "main\0"
	.byte	0x1
	.byte	0x3
	.byte	0x5
	.long	0xe8
	.quad	LFB1
	.quad	LFE1
	.set L$set$15,LLST0-Lsection__debug_loc
	.long L$set$15
	.long	0x292
	.uleb128 0xa
	.ascii "a\0"
	.byte	0x1
	.byte	0x4
	.byte	0x7
	.long	0x292
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0xa
	.ascii "s\0"
	.byte	0x1
	.byte	0x5
	.byte	0x7
	.long	0x292
	.byte	0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0xa
	.ascii "ab\0"
	.byte	0x1
	.byte	0x6
	.byte	0xa
	.long	0x163
	.byte	0x2
	.byte	0x91
	.sleb128 -8
	.uleb128 0xa
	.ascii "ae\0"
	.byte	0x1
	.byte	0x6
	.byte	0xf
	.long	0x163
	.byte	0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0xa
	.ascii "sb\0"
	.byte	0x1
	.byte	0x6
	.byte	0x14
	.long	0x163
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xa
	.ascii "se\0"
	.byte	0x1
	.byte	0x6
	.byte	0x19
	.long	0x163
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0xa
	.ascii "n\0"
	.byte	0x1
	.byte	0x7
	.byte	0x9
	.long	0x173
	.byte	0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0xb
	.quad	LBB2
	.quad	LBE2
	.uleb128 0xa
	.ascii "w\0"
	.byte	0x1
	.byte	0x9
	.byte	0xe
	.long	0x173
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0xb
	.quad	LBB3
	.quad	LBE3
	.uleb128 0xa
	.ascii "c\0"
	.byte	0x1
	.byte	0xa
	.byte	0x8
	.long	0x98
	.byte	0x3
	.byte	0x91
	.sleb128 -65
	.uleb128 0xa
	.ascii "n\0"
	.byte	0x1
	.byte	0xb
	.byte	0x7
	.long	0xe8
	.byte	0x3
	.byte	0x91
	.sleb128 -72
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x5
	.byte	0x8
	.long	0xe8
	.byte	0
	.section __DWARF,__debug_abbrev,regular,debug
Lsection__debug_abbrev:
Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0x8
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1b
	.uleb128 0x8
	.uleb128 0x2134
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0
	.byte	0
	.byte	0
	.section __DWARF,__debug_loc,regular,debug
Lsection__debug_loc:
Ldebug_loc0:
LLST0:
	.set L$set$16,LFB1-Ltext0
	.quad L$set$16
	.set L$set$17,LCFI0-Ltext0
	.quad L$set$17
	.short	0x2
	.byte	0x8f
	.sleb128 0
	.set L$set$18,LCFI0-Ltext0
	.quad L$set$18
	.set L$set$19,LCFI2-Ltext0
	.quad L$set$19
	.short	0x3
	.byte	0x8f
	.sleb128 112
	.set L$set$20,LCFI2-Ltext0
	.quad L$set$20
	.set L$set$21,LFE1-Ltext0
	.quad L$set$21
	.short	0x2
	.byte	0x8f
	.sleb128 0
	.quad	0
	.quad	0
	.section __DWARF,__debug_pubnames,regular,debug
Lsection__debug_pubnames:
	.long	0x2c
	.short	0x2
	.set L$set$22,Ldebug_info0-Lsection__debug_info
	.long L$set$22
	.long	0x299
	.long	0x188
	.ascii "printf\0"
	.long	0x1a4
	.ascii "scanf\0"
	.long	0x1bf
	.ascii "main\0"
	.long	0
	.section __DWARF,__debug_pubtypes,regular,debug
Lsection__debug_pubtypes:
	.long	0xf2
	.short	0x2
	.set L$set$23,Ldebug_info0-Lsection__debug_info
	.long L$set$23
	.long	0x299
	.long	0x98
	.ascii "char\0"
	.long	0xa5
	.ascii "signed char\0"
	.long	0xb4
	.ascii "unsigned char\0"
	.long	0xc5
	.ascii "short int\0"
	.long	0xd2
	.ascii "short unsigned int\0"
	.long	0xe8
	.ascii "int\0"
	.long	0xef
	.ascii "unsigned int\0"
	.long	0xff
	.ascii "long long int\0"
	.long	0x110
	.ascii "long long unsigned int\0"
	.long	0x12a
	.ascii "long int\0"
	.long	0x136
	.ascii "long unsigned int\0"
	.long	0x14b
	.ascii "__darwin_size_t\0"
	.long	0x163
	.ascii "int64_t\0"
	.long	0x173
	.ascii "size_t\0"
	.long	0
	.section __DWARF,__debug_aranges,regular,debug
Lsection__debug_aranges:
	.long	0x2c
	.short	0x2
	.set L$set$24,Ldebug_info0-Lsection__debug_info
	.long L$set$24
	.byte	0x8
	.byte	0
	.short	0
	.short	0
	.quad	Ltext0
	.set L$set$25,Letext0-Ltext0
	.quad L$set$25
	.quad	0
	.quad	0
	.section __DWARF,__debug_line,regular,debug
Lsection__debug_line:
Ldebug_line0:
	.section __DWARF,__debug_str,regular,debug
Lsection__debug_str:
	.ident	"GCC: (Homebrew GCC 11.2.0) 11.1.0"
	.subsections_via_symbols
