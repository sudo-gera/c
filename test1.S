	.arch armv8-a
	.text
	.const
__ZN6__pstl9execution2v1L3seqE:
	.space 1
__ZN6__pstl9execution2v1L3parE:
	.space 1
__ZN6__pstl9execution2v1L9par_unseqE:
	.space 1
__ZN6__pstl9execution2v1L5unseqE:
	.space 1
	.zerofill __DATA,__bss,__ZStL8__ioinit,1,0
	.const
	.align	2
__ZN9__gnu_cxxL21__default_lock_policyE:
	.word	2
	.align	3
__ZNSt8__detailL25__platform_wait_alignmentE:
	.xword	8
	.align	2
__ZNSt8__detailL25__atomic_spin_count_relaxE:
	.word	12
	.align	2
__ZNSt8__detailL19__atomic_spin_countE:
	.word	16
	.align	2
__ZNSt15regex_constantsL13error_collateE:
	.space 4
	.align	2
__ZNSt15regex_constantsL11error_ctypeE:
	.word	1
	.align	2
__ZNSt15regex_constantsL12error_escapeE:
	.word	2
	.align	2
__ZNSt15regex_constantsL13error_backrefE:
	.word	3
	.align	2
__ZNSt15regex_constantsL11error_brackE:
	.word	4
	.align	2
__ZNSt15regex_constantsL11error_parenE:
	.word	5
	.align	2
__ZNSt15regex_constantsL11error_braceE:
	.word	6
	.align	2
__ZNSt15regex_constantsL14error_badbraceE:
	.word	7
	.align	2
__ZNSt15regex_constantsL11error_rangeE:
	.word	8
	.align	2
__ZNSt15regex_constantsL11error_spaceE:
	.word	9
	.align	2
__ZNSt15regex_constantsL15error_badrepeatE:
	.word	10
	.align	2
__ZNSt15regex_constantsL16error_complexityE:
	.word	11
	.align	2
__ZNSt15regex_constantsL11error_stackE:
	.word	12
	.align	3
__ZNSt8__detailL19_S_invalid_state_idE:
	.xword	-1
	.text
	.align	2
	.globl _main
_main:
LFB11777:
	stp	x29, x30, [sp, -16]!
LCFI0:
	mov	x29, sp
	mov	w1, 3
	adrp	x0, __ZSt4cout@GOTPAGE
	ldr	x0, [x0, __ZSt4cout@GOTPAGEOFF]
	bl	__ZNSolsEi
	adrp	x1, __ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPAGE
	ldr	x1, [x1, __ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPAGEOFF]
	bl	__ZNSolsEPFRSoS_E
	mov	w0, 0
	ldp	x29, x30, [sp], 16
LCFI1:
	ret
LFE11777:
	.align	2
__Z41__static_initialization_and_destruction_0ii:
LFB13842:
	stp	x29, x30, [sp, -32]!
LCFI2:
	mov	x29, sp
	str	w0, [sp, 28]
	str	w1, [sp, 24]
	ldr	w0, [sp, 28]
	cmp	w0, 1
	bne	L5
	ldr	w1, [sp, 24]
	mov	w0, 65535
	cmp	w1, w0
	bne	L5
	adrp	x0, __ZStL8__ioinit@PAGE
	add	x0, x0, __ZStL8__ioinit@PAGEOFF;momd
	bl	__ZNSt8ios_base4InitC1Ev
	adrp	x0, ___dso_handle@PAGE
	add	x2, x0, ___dso_handle@PAGEOFF;momd
	adrp	x0, __ZStL8__ioinit@PAGE
	add	x1, x0, __ZStL8__ioinit@PAGEOFF;momd
	adrp	x0, __ZNSt8ios_base4InitD1Ev@GOTPAGE
	ldr	x0, [x0, __ZNSt8ios_base4InitD1Ev@GOTPAGEOFF]
	bl	___cxa_atexit
L5:
	nop
	ldp	x29, x30, [sp], 32
LCFI3:
	ret
LFE13842:
	.align	2
__GLOBAL__sub_I_test1.cpp:
LFB13866:
	stp	x29, x30, [sp, -16]!
LCFI4:
	mov	x29, sp
	mov	w1, 65535
	mov	w0, 1
	bl	__Z41__static_initialization_and_destruction_0ii
	ldp	x29, x30, [sp], 16
LCFI5:
	ret
LFE13866:
	.section __TEXT,__eh_frame,coalesced,no_toc+strip_static_syms+live_support
EH_frame1:
	.set L$set$0,LECIE1-LSCIE1
	.long L$set$0
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
LSFDE1:
	.set L$set$1,LEFDE1-LASFDE1
	.long L$set$1
LASFDE1:
	.long	LASFDE1-EH_frame1
	.quad	LFB11777-.
	.set L$set$2,LFE11777-LFB11777
	.quad L$set$2
	.uleb128 0
	.byte	0x4
	.set L$set$3,LCFI0-LFB11777
	.long L$set$3
	.byte	0xe
	.uleb128 0x10
	.byte	0x9d
	.uleb128 0x2
	.byte	0x9e
	.uleb128 0x1
	.byte	0x4
	.set L$set$4,LCFI1-LCFI0
	.long L$set$4
	.byte	0xde
	.byte	0xdd
	.byte	0xe
	.uleb128 0
	.align	3
LEFDE1:
LSFDE3:
	.set L$set$5,LEFDE3-LASFDE3
	.long L$set$5
LASFDE3:
	.long	LASFDE3-EH_frame1
	.quad	LFB13842-.
	.set L$set$6,LFE13842-LFB13842
	.quad L$set$6
	.uleb128 0
	.byte	0x4
	.set L$set$7,LCFI2-LFB13842
	.long L$set$7
	.byte	0xe
	.uleb128 0x20
	.byte	0x9d
	.uleb128 0x4
	.byte	0x9e
	.uleb128 0x3
	.byte	0x4
	.set L$set$8,LCFI3-LCFI2
	.long L$set$8
	.byte	0xde
	.byte	0xdd
	.byte	0xe
	.uleb128 0
	.align	3
LEFDE3:
LSFDE5:
	.set L$set$9,LEFDE5-LASFDE5
	.long L$set$9
LASFDE5:
	.long	LASFDE5-EH_frame1
	.quad	LFB13866-.
	.set L$set$10,LFE13866-LFB13866
	.quad L$set$10
	.uleb128 0
	.byte	0x4
	.set L$set$11,LCFI4-LFB13866
	.long L$set$11
	.byte	0xe
	.uleb128 0x10
	.byte	0x9d
	.uleb128 0x2
	.byte	0x9e
	.uleb128 0x1
	.byte	0x4
	.set L$set$12,LCFI5-LCFI4
	.long L$set$12
	.byte	0xde
	.byte	0xdd
	.byte	0xe
	.uleb128 0
	.align	3
LEFDE5:
	.private_extern ___dso_handle
	.ident	"GCC: (Homebrew GCC 12.2.0) 12.2.0"
	.mod_init_func
_Mod.init:
	.align	3
	.xword	__GLOBAL__sub_I_test1.cpp
	.subsections_via_symbols
