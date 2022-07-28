%include "macro.inc"

%if __BITS__ == 64
%define _get _qsget
%endif

begin

_get [n]
_get [m]
mov _ax,[n]
mov _bx,[n]
mul _bx
mov [g],_ax




mov _ax,[g]
mov _bx,rsize
mul _bx
mov [g],_ax




sub _sp,[g]
mov [j],_sp


for [w],[n]
	for [e],[m]
		scan_f " %c",[t]
		; _get [t]
		mov _ax,[w]
		mov _bx,[m]
		mul _bx
		mov [g],_ax




		mov _ax,[g]
		mov _bx,[e]
		add _ax,_bx
		mov [g],_ax




		mov _ax,[g]
		mov _bx,rsize
		mul _bx
		mov [g],_ax




		mov _ax,[j]
		mov _bx,[g]
		mov _cx,[t]
		mov [_ax+_bx],_cx
		; _aput [j],[g],[t]
	end
end

; for [w],[n]
; 	for [e],[m]
; 		mov _ax,[w]
		mov _bx,[m]
		mul _bx
		mov [g],_ax




; 		mov _ax,[g]
		mov _bx,[e]
		add _ax,_bx
		mov [g],_ax




; 		mov _ax,[g]
		mov _bx,rsize
		mul _bx
		mov [g],_ax




; 		mov _ax,[j]
; 		mov _bx,[g]
; 		mov _cx,[t]
; 		mov _cx,[_ax,_bx]
; 		mov [t],_cx
; 		; _aget [t],[j],[g]
; 		_uwrite [t]
; 	end
; 	cput 10
; end

mov _ax,[n]
mov _bx,[n]
mul _bx
mov [g],_ax




mov _ax,[g]
mov _bx,rsize
mul _bx
mov [g],_ax




sub _sp,[g]

push _sp
push _word [j]
push _word [m]
push _word [n]

call proc

add _sp,rsize*4


mov [j],_sp

for [w],[n]
	for [e],[n]
		mov _ax,[w]
		mov _bx,[n]
		mul _bx
		mov [g],_ax




		mov _ax,[g]
		mov _bx,[e]
		add _ax,_bx
		mov [g],_ax




		mov _ax,[g]
		mov _bx,rsize
		mul _bx
		mov [g],_ax




		mov _ax,[j]
		mov _bx,[g]
		mov _cx,[t]
		mov _cx,[_ax,_bx]
		mov [t],_cx
		; _aget [t],[j],[g]
		_uwrite [t]
	end
	cput 10
end

end

section .data
proc_n d_ 0
proc_m d_ 0
proc_a d_ 0
proc_s d_ 0
section .text

proc:
	db 'PQRSTUVW'
	mov _ax,[_sp+9*rsize]
	mov _bx,[_sp+10*rsize]
	mov _cx,[_sp+11*rsize]
	mov _dx,[_sp+12*rsize]
	mov [proc_n],_ax
	mov [proc_m],_bx
	mov [proc_a],_cx
	mov [proc_s],_dx
	for [w],[proc_n]
		for [e],[proc_n]
			mov _ax,[w]
			mov _bx,[proc_m]
			mul _bx
			mov _si,_ax




			mov _ax,_si
			mov _bx,rsize
			mul _bx
			mov _si,_ax




			mov _ax,_si
			mov _bx,[proc_a]
			add _ax,_bx
			mov _si,_ax




			mov _ax,[e]
			mov _bx,[proc_m]
			mul _bx
			mov _di,_ax




			mov _ax,_di
			mov _bx,rsize
			mul _bx
			mov _di,_ax




			mov _ax,_di
			mov _bx,[proc_a]
			add _ax,_bx
			mov _di,_ax




			mov _cx,[proc_m]
			repe cmps %+ _
			jnz _1
				dec _cx
			_1:
			mov _ax,[proc_m]
			mov _bx,_cx
			sub _ax,_bx
			mov _cx,_ax




			dec _cx
			mov [b],_cx
			mov _ax,[w]
			mov _bx,[proc_n]
			mul _bx
			mov [g],_ax




			mov _ax,[g]
			mov _bx,[e]
			add _ax,_bx
			mov [g],_ax




			mov _ax,[g]
			mov _bx,rsize
			mul _bx
			mov [g],_ax




			mov _ax,[proc_s]
			mov _bx,[g]
			mov _cx,[b]
			mov [_ax+_bx],_cx
		end
		cput 10
	end
	db '_^]X[ZYX'
	ret
