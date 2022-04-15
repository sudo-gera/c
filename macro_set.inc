%assign macro_set_len 3

%macro set 1-*
	push %%_1
	%rep %0
		%rotate -1
		%ifidni %1,+
			push dword 0
			push dword '+'
			push dword 2
		%elifidni %1,-
			push dword 0
			push dword '-'
			push dword 2
		%elifidni %1,*
			push dword 0
			push dword '*'
			push dword 2
		%elifidni %1,/
			push dword 0
			push dword '/'
			push dword 2
		%elifidni %1,%
			push dword 0
			push dword '%'
			push dword 2
		%elifidni %1,(
			push dword 0
			push dword '('
			push dword 2
		%elifidni %1,)
			push dword 0
			push dword ')'
			push dword 2
		%elifidni %1,<
			push dword 0
			push dword '<'
			push dword 2
		%elifidni %1,>
			push dword 0
			push dword '>'
			push dword 2
		%elifidni %1,<=
			push dword 0
			push dword '<='
			push dword 2
		%elifidni %1,>=
			push dword 0
			push dword '<='
			push dword 2
		%elifidni %1,==
			push dword 0
			push dword '=='
			push dword 2
		%elifidni %1,!=
			push dword 0
			push dword '!='
			push dword 2
		%elifidni %1,and
			push dword 0
			push dword 'and'
			push dword 2
		%elifidni %1,or
			push dword 0
			push dword 'or'
			push dword 2
		%elifidni %1,&&
			push dword 0
			push dword '&&'
			push dword 2
		%elifidni %1,||
			push dword 0
			push dword '||'
			push dword 2
		%elifidni %1,[
			push dword 0
			push dword '['
			push dword 2
		%elifidni %1,]
			push dword 0
			push dword ']'
			push dword 2
		%elifidni %1,b[
			push dword 0
			push dword 'b['
			push dword 2
		%elifidni %1,w[
			push dword 0
			push dword 'w['
			push dword 2
		%elifidni %1,d[
			push dword 0
			push dword 'd['
			push dword 2
		%elifidni %1,=
			push dword 0
			push dword '='
			push dword 2
		%elifidni %1,+=
			push dword 0
			push dword '+='
			push dword 2
		%elifidni %1,-=
			push dword 0
			push dword '-='
			push dword 2
		%elifidni %1,*=
			push dword 0
			push dword '*='
			push dword 2
		%elifidni %1,/=
			push dword 0
			push dword '/='
			push dword 2
		%elifidni %1,%=
			push dword 0
			push dword '%='
			push dword 2
		%else
			%defstr %$arg %1
			%strlen %$lll %$arg
			%substr %$arg1 %$arg 1,1
			%substr %$arg2 %$arg %$lll,1
			%if %$arg1 == '[' && %$arg2 == ']'
				push dword 4
				push dword %1
				push dword 0
				pushad
				lea eax,%1
				mov [esp+32],eax
				popad
			%else
				push dword 0
				push dword %1
				push dword 1
			%endif
		%endif
	%endrep
	push dword (%0)*macro_set_len*4
	jmp macro_set_jmp
	%%_1:
%endmacro

%macro macro_set_memmove 1
dufor esi,%1
	mov edi,edx
	add edi,macro_set_len*4
	mov ebp,ecx
	sub ebp,edi
	dmemmove edx,edi,ebp
	sub ecx,macro_set_len*4
	sub ebx,macro_set_len*4
	sub edx,macro_set_len*4
end
%endmacro


%macro macro_set_pr 0
push %%_1
push dword __LINE__
jmp macro_pr_jmp
%%_1:
%endmacro



%macro macro_set_hash 3
push %%_1
push dword %2
push dword %3
jmp macro_expr_hash_jmp
%%_1:
pop dword %1
%endmacro


%define macro_var
%macro var 1
%defstr %%varstr %1
push %%_3
push dword %1
push %%_1
jmp macro_var_jmp
%%_1:
db %%varstr
%%_3:
%endmacro




%macro expr 1+
%defstr %%varstr %1
push %%_3
push %%_1
jmp macro_expr_jmp
%%_1:
db ' ('
db %%varstr
db ') '
%%_3:
%endmacro
