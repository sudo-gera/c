	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 12, 0	sdk_version 12, 3
	.section	__DATA,__const
	.p2align	3                               ; -- Begin function main
lCPI0_0:
	.quad	Ltmp0
lCPI0_1:
	.quad	Ltmp1
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	stp	x29, x30, [sp, #-16]!           ; 16-byte Folded Spill
	mov	x29, sp
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	bl	_main
Lloh0:
	adrp	x8, lCPI0_0@PAGE
Lloh1:
	ldr	x8, [x8, lCPI0_0@PAGEOFF]
	br	x8
Ltmp0:                                  ; Block address taken
LBB0_1:                                 ; =>This Inner Loop Header: Depth=1
Lloh2:
	adrp	x8, lCPI0_1@PAGE
Lloh3:
	ldr	x8, [x8, lCPI0_1@PAGEOFF]
	br	x8
Ltmp1:                                  ; Block address taken
LBB0_2:                                 ; %tailrecurse
                                        ; =>This Inner Loop Header: Depth=1
Lloh4:
	adrp	x8, lCPI0_0@PAGE
Lloh5:
	ldr	x8, [x8, lCPI0_0@PAGEOFF]
	br	x8
	.loh AdrpLdr	Lloh0, Lloh1
	.loh AdrpLdr	Lloh2, Lloh3
	.loh AdrpLdr	Lloh4, Lloh5
	.cfi_endproc
                                        ; -- End function
.subsections_via_symbols
