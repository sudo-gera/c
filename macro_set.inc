%assign macro_set_len 3

%macro set 1-*
	_push %%_1
	%rep %0
		%rotate -1
		%ifidni %1,+
			_push 0
			_push '+'
			_push 2
		%elifidni %1,-
			_push 0
			_push '-'
			_push 2
		%elifidni %1,*
			_push 0
			_push '*'
			_push 2
		%elifidni %1,/
			_push 0
			_push '/'
			_push 2
		%elifidni %1,%
			_push 0
			_push '%'
			_push 2
		%elifidni %1,(
			_push 0
			_push '('
			_push 2
		%elifidni %1,)
			_push 0
			_push ')'
			_push 2
		%elifidni %1,<
			_push 0
			_push '<'
			_push 2
		%elifidni %1,>
			_push 0
			_push '>'
			_push 2
		%elifidni %1,<=
			_push 0
			_push '<='
			_push 2
		%elifidni %1,>=
			_push 0
			_push '<='
			_push 2
		%elifidni %1,==
			_push 0
			_push '=='
			_push 2
		%elifidni %1,!=
			_push 0
			_push '!='
			_push 2
		%elifidni %1,and
			_push 0
			_push 'and'
			_push 2
		%elifidni %1,or
			_push 0
			_push 'or'
			_push 2
		%elifidni %1,&&
			_push 0
			_push '&&'
			_push 2
		%elifidni %1,||
			_push 0
			_push '||'
			_push 2
		%elifidni %1,[
			_push 0
			_push '['
			_push 2
		%elifidni %1,]
			_push 0
			_push ']'
			_push 2
		%elifidni %1,b[
			_push 0
			_push 'b['
			_push 2
		%elifidni %1,w[
			_push 0
			_push 'w['
			_push 2
		%elifidni %1,d[
			_push 0
			_push 'd['
			_push 2
		%elifidni %1,q[
			_push 0
			_push 'q['
			_push 2
		%elifidni %1,=
			_push 0
			_push '='
			_push 2
		%elifidni %1,+=
			_push 0
			_push '+='
			_push 2
		%elifidni %1,-=
			_push 0
			_push '-='
			_push 2
		%elifidni %1,*=
			_push 0
			_push '*='
			_push 2
		%elifidni %1,/=
			_push 0
			_push '/='
			_push 2
		%elifidni %1,%=
			_push 0
			_push '%='
			_push 2
		%else
			%defstr %%_arg %1
			%strlen %%lll %%_arg
			%substr %%arg1 %%_arg 1,1
			%substr %%arg2 %%_arg %%lll,1
			%if %%arg1 == '[' && %%arg2 == ']'
				_push rsize
				_push %1
				_push 0
				pushad
				lea _ax,%1
				mov [_sp+8*rsize],_ax
				popad
			%else
				_push 0
				_push %1
				_push 1
			%endif
		%endif
	%endrep
	_push (%0)*macro_set_len*rsize
	jmp macro_set_jmp
	%%_1:
%endmacro

%macro macro_set_memmove 1
_ufor _si,%1
	mov _di,_dx
	add _di,macro_set_len*rsize
	mov _bp,_cx
	sub _bp,_di
	_memmove _dx,_di,_bp
	sub _cx,macro_set_len*rsize
	sub _bx,macro_set_len*rsize
	sub _dx,macro_set_len*rsize
end
%endmacro


%macro macro_set_pr 0
_push %%_1
_push __LINE__
jmp macro_pr_jmp
%%_1:
%endmacro



%macro macro_set_hash 3
push %%_1
_push %2
_push %3
jmp macro_expr_hash_jmp
%%_1:
pop _word %1
%endmacro


%define macro_var
%macro var 1
%defstr %%varstr %1
push %%_3
_push %1
push %%_1
jmp macro_var_jmp
%%_1:
db %%varstr
%%_3:
%endmacro




%macro expr 1+
%defstr %%varstr %1
push %%_expr
call macro_expr_jmp
db ' ('
db %%varstr
db ') '
%%_expr:
%endmacro
