%include "macro.inc"

section .data
aa dw 5,4,3,2,1,0,-1,-2,-3,-4,-5

begin

def run
	dmul eax,ebx
	dmul eax,ecx
	dmul eax,edx
end

dadd [q],aa,10

; mov ecx,10
; _1:
; set [d],=,[q],w[,1,],*=,-12
; print [d]
; loop _1

; set [d],=,(,(,2,+,3,),*,(,4,+,5,),),+,(,-1,<,1,and,1,>,-1,),+,run,(,[q],w[,1,],[q],w[,[q],w[,2,],],[q],w[,[q],w[,[q],w[,3,],],],[q],w[,[q],w[,[q],w[,[q],w[,4,],],],],)

; set [d],=,[q],w[,1,],*=,-12
; print [d]
; set [d],=,[q],w[,1,],%=,10
; print [d]
; set [d],=,aa,w[,6,]
; print [d]

; set [q],w[,-3,],*=,[q],w[,-1,],=,[q],w[,1,],=,[q],w[,3,],+=,9

; set [q],w[,-3,],%=,[q],w[,-4,]

; mov eax,256
; set [d],al,=,3
; print eax

; for [w],11
; 	waget [e],aa,[w]
; 	wswrite [e]
; end
; cput 10



end
