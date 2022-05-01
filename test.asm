%include "macro.inc"

section .data
aa d_ 5,4,3,2,1,0,-1,-2,-3,-4,-5

begin

def run
	_mul _ax,_bx
	_mul _ax,_cx
	_mul _ax,_dx
end

_add [q],aa,rsize*5


_mov [z],2
_mov [x],3
_mov [c],4
_mov [v],5




; set [d],=,run,(,1,z,[,0,],3,4,)
; _uprint [d]

expr d [0]=(z[0])+-+-1
print [d]
expr d [0]=((z[0]+x[0])*( c[0]+v[0]))+(-1<1&&1>-1)+run (q[0][1],q[0][q [0][2]],q[0][q[0][q[0][3]]],q[0][q[0][q[0][q[0][4]]]])
expr |\
	d[0] += 2|\
	d[0] /= 9

print [d]

expr (*q)[-3]*=(*q)[-1]=(*q)[1]=(*q)[3]+=9
expr (*q)[-3]%=(*q)[-4]
expr (*q)[-3]+= 1
expr q[0][3] /=-2
expr q[0][-1]/= 6
expr (*q)[1] /=-6

expr **q=+-+999

_sfor [w],11
	_aget [e],aa,[w]
	_swrite [e]
end
cput 10

expr |\
	*d+=12|\
	*d/=4|\
	*d*=2**d|\
	*d*=2

print [d]


; mov ecx,10
; jmp _2
; _1:
; set [d],=,[q],w[,1,],*=,-12
; print [d]
; loop _1

; set [d],=,256,*,256,*,256,*,256,+,1
; set [d],=,(,(,2,+,3,),*,(,4,+,5,),),+,(,-1,<,1,&&,1,>,-1,),+,run,(,[q],[,1,],[q],[,[q],[,2,],],[q],[,[q],[,[q],[,3,],],],[q],[,[q],[,[q],[,[q],[,4,],],],],)
; qsprint [d]


; set [d],=,[q],w[,1,],*=,-12
; dsprint [d]
; set [d],=,[q],w[,1,],%=,10
; print [d]
; set [d],=,aa,w[,6,]
; print [d]

; set q,[,0,],[,0,-,3,],*=,q,[,0,],[,0,-,1,],=,q,[,0,],[,1,],=,q,[,0,],[,3,],+=,9
; set [q],w[,-3,],%=,[q],w[,-4,]


; ; mov eax,256
; ; set al,=,3
; ; print eax

; for [w],11
; 	waget [e],aa,[w]
; 	wswrite [e]
; end
; cput 10
; buprint 1,2,34
; _2:
; dsput _2-_1

; qw:
; we:
; qwe:
; mov eax,840633404
; mov ebx,1441998478
; mov ecx,202105529
; mov edx,180003570
; mov esi,1520564170
; mov edi,2123457867
; mov ebp,1355131955

; var q
; var w
; var e
; var q
; var w
; var e
; var qw
; var we
; var qwe

; print q,[q]
; regout
; sput "$$$"
; regout

; expr q[0] = 999

; print q,[q]


; print vars_names

; for [w],[len_vars_names]
; 	daget [e],vars_names,[w]
; 	write [e]
; end

; stop
end


