.p2align 16

.data
;     .word 0
;     .word 0
;     .word 0
;     .word 0
;     .word 0
;     .word 0
;     .word 0
;     .word 0
;     .word 0
;     .word 0
;     .word 0
;     .word 0
;     .word 0
;     .word 0
;     .word 0
; _a: .word 0
;     .word 0
;     .word 0
;     .word 0
;     .word 0
;     .word 0
;     .word 0
;     .word 0
;     .word 0
;     .word 0
;     .word 0
;     .word 0
;     .word 0
;     .word 0
;     .word 0
A: .int 0
   .int 0
B: .int 0
   .int 0
C: .int 0
   .int 0
D: .int 0
   .int 0

.p2align 16

.text
.global A
; .global B
; .global C
; .global D
.global _c


_c:
    ldr x0,=_c
    ; mov x4,1
    ; mov x5,256
    ; mul x4,x4,x5
    ; mul x4,x4,x5
    ; mov x5,3
    ; add x4,x4,x5
    ; mov x5,256
    ; mul x4,x4,x5
    ; mul x4,x4,x5
    ; mov x0,x4
    ; ldr x0,[x4]


    ; adr x0,_a
    ; ldxr x0,4295163904
    ; ldr x4,=A
    ; mov x1,100030000
    ; mov x1,112
    ; ldr x0,=x1

    ; mul x0,x0,x1
    ; mul x2,x2,x3
    ; add x0,x0,x2
ret
