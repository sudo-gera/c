function len(q:
	string):integer;begin len:=q.length;end;
function len(q:
	array of string):integer;begin len:=length(q);end;
function len(q:
	array of array of string):integer;begin len:=length(q);end;
function len(q:
	array of array of array of string):integer;begin len:=length(q);end;
function len(q:
	array of integer):integer;begin len:=length(q);end;
function len(q:
	array of array of integer):integer;begin len:=length(q);end;
function len(q:
	array of array of array of integer):integer;begin len:=length(q);end;
procedure push_back(var a: array of
	integer; value:
	integer);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of integer; value:
	array of integer);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of integer; value:
	array of array of integer);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of array of integer; value:
	array of array of array of integer);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of array of array of integer; value:
	array of array of array of array of integer);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of array of array of array of integer; value:
	array of array of array of array of array of integer);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of array of array of array of array of integer; value:
	array of array of array of array of array of array of integer);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	string; value:
	string);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of string; value:
	array of string);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of string; value:
	array of array of string);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of array of string; value:
	array of array of array of string);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of array of array of string; value:
	array of array of array of array of string);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of array of array of array of string; value:
	array of array of array of array of array of string);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
function stoa(a:sequence of
	integer): array of
	integer;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of integer): array of
	array of integer;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of array of integer): array of
	array of array of integer;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of array of array of integer): array of
	array of array of array of integer;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of array of array of array of integer): array of
	array of array of array of array of integer;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of array of array of array of array of integer): array of
	array of array of array of array of array of integer;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	string): array of
	string;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of string): array of
	array of string;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of array of string): array of
	array of array of string;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of array of array of string): array of
	array of array of array of string;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of array of array of array of string): array of
	array of array of array of array of string;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of array of array of array of array of string): array of
	array of array of array of array of array of string;begin foreach var w in a do push_back(result,w);end;
function stoa(a:set of
	integer): array of
	integer;begin foreach var w in a do push_back(result,w);end;
function stoa(a:set of
	array of integer): array of
	array of integer;begin foreach var w in a do push_back(result,w);end;
function stoa(a:set of
	array of array of integer): array of
	array of array of integer;begin foreach var w in a do push_back(result,w);end;
function stoa(a:set of
	array of array of array of integer): array of
	array of array of array of integer;begin foreach var w in a do push_back(result,w);end;
function stoa(a:set of
	string): array of
	string;begin foreach var w in a do push_back(result,w);end;
function stoa(a:set of
	array of string): array of
	array of string;begin foreach var w in a do push_back(result,w);end;
function stoa(a:set of
	array of array of string): array of
	array of array of string;begin foreach var w in a do push_back(result,w);end;
function stoa(a:set of
	array of array of array of string): array of
	array of array of array of string;begin foreach var w in a do push_back(result,w);end;
function tarr(q:
	integer):array of
	integer;
	begin
		tarr:=arr(0);
	end;
function tarr(q:
	array of integer):array of
	array of integer;
	begin tarr:=stoa(q.select(x->tarr(x)));end;
function tarr(q:
	array of array of integer):array of
	array of array of integer;
	begin tarr:=stoa(q.select(x->tarr(x)));end;
function tarr(q:
	array of array of array of integer):array of
	array of array of array of integer;
	begin tarr:=stoa(q.select(x->tarr(x)));end;
function tarr(q:
	array of array of array of array of integer):array of
	array of array of array of array of integer;
	begin tarr:=stoa(q.select(x->tarr(x)));end;
function tarr(q:
	array of array of array of array of array of integer):array of
	array of array of array of array of array of integer;
	begin tarr:=stoa(q.select(x->tarr(x)));end;
function emparr(q:
	integer):array of
	integer;
	begin
		result:=arr(0);
		SetLength(result,0);
		emparr:=result;
	end;
function emparr(q:
	array of integer):array of
	array of integer;
	begin result:=tarr(q);SetLength(result,0);emparr:=result;end;
function emparr(q:
	array of array of integer):array of
	array of array of integer;
	begin result:=tarr(q);SetLength(result,0);emparr:=result;end;
function emparr(q:
	array of array of array of integer):array of
	array of array of array of integer;
	begin result:=tarr(q);SetLength(result,0);emparr:=result;end;
function emparr(q:
	array of array of array of array of integer):array of
	array of array of array of array of integer;
	begin result:=tarr(q);SetLength(result,0);emparr:=result;end;
function emparr(q:
	array of array of array of array of array of integer):array of
	array of array of array of array of array of integer;
	begin result:=tarr(q);SetLength(result,0);emparr:=result;end;


function int(q:string):integer;
begin
	var e:=0;
	if not(integer.tryparse(q,e)) then println('error in int');
	int:=e;
end;
var cache: array of string;
function tocache(q:string):integer;
begin
	push_back(cache,q);
	tocache:=len(cache)-1;
end;
begin
	var task:=3;
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
		// var d:dictionary<string,integer>;
		var dk:set of string;
		foreach w:array of integer in a1 do
		begin
			dk+=[cache[w[1]]];
		end;
		var d:=stoa(dk).todictionary(x->x,x->0);
		foreach w:array of integer in a1 do
			d[cache[w[1]]]+=w[0];
		var s:array of string;
		foreach w:string in dk do
		begin
			push_back(s,d[w].tostring()+w);
		end;
		println(string.join('+',s));
	end;
	if task=3 then
	begin
		var he:=0;
		var wi:=0;
		read(wi,he);
		var d:array of array of integer;
		for var w:=1 to he do
		begin
			push_back(d,emparr(0));
			for var e:= 1 to wi do
			begin
				var c:=0;
				read(c);
				push_back(d[w-1],c);
			end;
		end;
		d:=d[::-1];
		var ca :=emparr(emparr(emparr(0)));
		for var w:=1 to he do
		begin
			push_back(ca,emparr(emparr(0)));
			for var e:= 1 to wi do
			begin
				var x:=w-1;
				var y:=e-1;
				if (x=0) and (0=y) then
				begin
					push_back(ca[w-1],arr(d[x][y],-1,-1));
				end else
				if x=0 then
				begin
					push_back(ca[w-1],arr(d[x][y]+ca[x][y-1][0],x,y-1));
				end else
				if y=0 then
				begin
					push_back(ca[w-1],arr(d[x][y]+ca[x-1][y][0],x-1,y));
				end else
				begin
					if ca[x-1][y][0]<ca[x][y-1][0] then
					begin
						push_back(ca[w-1], arr(d[x][y]+ca[x-1][y][0],x-1,y));
					end
					else
					begin
						push_back(ca[w-1], arr(d[x][y]+ca[x][y-1][0],x,y-1));
					end;
				end;
			end;
		end;
		var p:=arr(len(d)-1,len(d[0])-1);
		var ext:=emparr(emparr(0));
		while (p[0]<>-1) or (p[1]<>-1) do
		begin
			push_back(ext,p);
			p:=arr(ca[p[0]][p[1]][1],ca[p[0]][p[1]][2]);
		end;
		ext:=ext[::-1];
		foreach w:array of integer in ext do
			println(w[1]+1,w[0]+1)
	end;

end.