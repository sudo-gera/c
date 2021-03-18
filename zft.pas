  function len(q:string):integer;
begin
	len:=q.length;
end;
function int(q:string):integer;
begin
	var e:=0;
	if not(integer.tryparse(q,e)) then println('error in int');
	int:=e;
end;
procedure push_back(var a: array of integer; value: integer);
begin
	 SetLength(a, length(a) + 1);
	 a[length(a) - 1]:= value;
end;
procedure push_back(var a: array of array of integer; value: array of integer);
begin
	 SetLength(a, length(a) + 1);
	 a[length(a) - 1]:= value;
end;
procedure push_back(var a: array of array of array of integer; value: array of array of integer);
begin
	 SetLength(a, length(a) + 1);
	 a[length(a) - 1]:= value;
end;
procedure push_back(var a: array of string; value: string);
begin
	 SetLength(a, length(a) + 1);
	 a[length(a) - 1]:= value;
end;
procedure push_back(var a: array of array of string; value: array of string);
begin
	 SetLength(a, length(a) + 1);
	 a[length(a) - 1]:= value;
end;
procedure push_back(var a: array of array of array of string; value: array of array of string);
begin
	 SetLength(a, length(a) + 1);
	 a[length(a) - 1]:= value;
end;
var cache: array of string;
function tocache(q:string):integer;
begin
	push_back(cache,q);
	tocache:=len(q)-1;
end;
function stoa(a:sequence of integer): array of integer;
begin
	foreach var w in a do
		push_back(result,w);
end;
function stoa(a:sequence of array of integer): array of array of integer;
begin
	foreach var w in a do
		push_back(result,w);
end;
function stoa(a:sequence of array of array of integer): array of array of array of integer;
begin
	foreach var w in a do
		push_back(result,w);
end;
function stoa(a:sequence of string): array of string;
begin
	foreach var w in a do
		push_back(result,w);
end;
function stoa(a:sequence of array of string): array of array of string;
begin
	foreach var w in a do
		push_back(result,w);
end;
function stoa(a:sequence of array of array of string): array of array of array of string;
begin
	foreach var w in a do
		push_back(result,w);
end;
begin
	var task:=1;
	if task=1 then
	begin
		var q0:='';
		read(q0);
		var q1:=q0[2:len(q0)].split(')(');
		var q2:=stoa(q1.select(w->w.split('+')));
		var q3:=stoa(q2.select(w->stoa(w.select(e->arr(e.split('x^')[0],e.split('x^')[1].split('y^')[0],e.split('y^')[1])))));
		var q:=stoa(q3.select(w->stoa(w.select(e->stoa(e.select(r->int(r)))))));
		var a:array of array of integer;
		foreach w: array of integer in q[0] do
			foreach e: array of integer in q[1] do
				push_back(a,arr(w[0]*e[0],w[1]+e[1],w[2]+e[2]));
		var a1:=stoa(a.select(w->arr(w[0],tocache('x^'+w[1]+'y^'+w[2]))));
		var d:dictionary<string,integer>;
		var dk:set of string;
		foreach w:array of integer in a1 do
		begin
			d[cache[w[1]]]:=0;
			dk+=[cache[w[1]]];
		end;
		foreach w:array of integer in a do
			d[cache[w[1]]]+=w[0];
		var s:array of string;
		foreach w:string in dk do
			push_back(s,d[w]+w);
		println(string.join('+',a));
	end;{
	if task=3:
		from sys import stdin
		from json import loads
		s:=''
		l:=0
		ic:=0
		while 1:
			ic+:=1
			if ic=1000:
				print('inf loop')
				exit()
			try:
				d:=loads(s)[::-1]
				break
			except:
				s+:=stdin.read(1)
				if len(s)=l:
					print('err')
					exit()
				l:=len(s)
		from functools import lru_cache
		@lru_cache
		def s(x,y):
			if x=0=y:
				return [d[x][y],None]
			if x=0:
				return [d[x][y]+s(x,y-1)[0],[x,y-1]]
			if y=0:
				return [d[x][y]+s(x-1,y)[0],[x-1,y]]
			a:=min([s(x-1,y)+[[x-1,y]],s(x,y-1)+[[x,y-1]]])
			return [d[x][y]+a[0],a[2]]
		p:=[len(d)-1,len(d[0])-1]
		ext:=[]
		while p!:=None:
			ext.append(p)
			p:=s(*p)[1]
		ext:=ext[::-1]
		for w in ext:
			print(*w)
}
end.