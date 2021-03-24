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
function len(q:
	array of real):integer;begin len:=length(q);end;
function len(q:
	array of array of real):integer;begin len:=length(q);end;
function len(q:
	array of array of array of real):integer;begin len:=length(q);end;
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
	real; value:
	real);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of real; value:
	array of real);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of real; value:
	array of array of real);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of array of real; value:
	array of array of array of real);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of array of array of real; value:
	array of array of array of array of real);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of array of array of array of real; value:
	array of array of array of array of array of real);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
procedure push_back(var a: array of
	array of array of array of array of array of array of real; value:
	array of array of array of array of array of array of real);begin SetLength(a, length(a) + 1);a[length(a) - 1]:= value;end;
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
	real): array of
	real;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of real): array of
	array of real;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of array of real): array of
	array of array of real;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of array of array of real): array of
	array of array of array of real;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of array of array of array of real): array of
	array of array of array of array of real;begin foreach var w in a do push_back(result,w);end;
function stoa(a:sequence of
	array of array of array of array of array of real): array of
	array of array of array of array of array of real;begin foreach var w in a do push_back(result,w);end;
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
function tarr(q:
	real):array of
	real;
	begin
		tarr:=arr(0.0);
	end;
function tarr(q:
	array of real):array of
	array of real;
	begin tarr:=stoa(q.select(x->tarr(x)));end;
function tarr(q:
	array of array of real):array of
	array of array of real;
	begin tarr:=stoa(q.select(x->tarr(x)));end;
function tarr(q:
	array of array of array of real):array of
	array of array of array of real;
	begin tarr:=stoa(q.select(x->tarr(x)));end;
function tarr(q:
	array of array of array of array of real):array of
	array of array of array of array of real;
	begin tarr:=stoa(q.select(x->tarr(x)));end;
function tarr(q:
	array of array of array of array of array of real):array of
	array of array of array of array of array of real;
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
function emparr(q:
	real):array of
	real;
	begin
		result:=arr(0.0);
		SetLength(result,0);
		emparr:=result;
	end;
function emparr(q:
	array of real):array of
	array of real;
	begin result:=tarr(q);SetLength(result,0);emparr:=result;end;
function emparr(q:
	array of array of real):array of
	array of array of real;
	begin result:=tarr(q);SetLength(result,0);emparr:=result;end;
function emparr(q:
	array of array of array of real):array of
	array of array of array of real;
	begin result:=tarr(q);SetLength(result,0);emparr:=result;end;
function emparr(q:
	array of array of array of array of real):array of
	array of array of array of array of real;
	begin result:=tarr(q);SetLength(result,0);emparr:=result;end;
function emparr(q:
	array of array of array of array of array of real):array of
	array of array of array of array of array of real;
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
var pi:=3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091456485669234603486104543266482133936072602491412737245870066063155881748815209209628292540917153643678925903600113305305488204665213841469519415116094330572703657595919530921861173819326117931051185480744623799627495673518857527248912279381830119491298336733624406566430860213949463952247371907021798609437027705392171762931767523846748184676694051320005681271452635608277857713427577896091736371787214684409012249534301465495853710507922796892589235420199561121290219608640344181598136297747713099605187072113499999983729780499510597317328160963185950244594553469083026425223082533446850352619311881710100031378387528865875332083814206171776691473035982534904287554687311595628638823537875937519577818577805321712268066130019278766111959092164201989;
function atan2(a:real;s:real):real;
begin
	if (a<0) and (s<0)then atan2:= arctan(a/s)-pi;
	if (a<0) and (s=0)then atan2:= -pi/2;
	if (a<0) and (s>0)then atan2:= arctan(a/s);
	if (a=0) and (s<0)then atan2:= 0;
	if (a=0) and (s=0)then atan2:= 0;
	if (a=0) and (s>0)then atan2:= 0;
	if (a>0) and (s<0)then atan2:= arctan(a/s)+pi;
	if (a>0) and (s=0)then atan2:= pi/2;
	if (a>0) and (s>0)then atan2:= arctan(a/s);
end;

function makesum(d1:array of real;d2:array of real):array of real;
begin
	var ff:real->real:= x-> (d1[0]*cos(x+d1[1])+d2[0]*cos(x+d2[1]));
	var j:=16;
	var k:=4;
	var aa:array of array of real;
	for var w:=0 to round(j*pi*4) do
	begin
		push_back(aa,arr(ff(w/j),w/j));
	end;
	var s2:=emparr(0.0);
	for var w :=0 to len(aa)-1 do
	begin
		push_back(s2, 0.0 );
		for var ww := w to min(w+k-1,len(aa)-1) do
		begin
			s2[len(s2)-1]+=aa[ww][0];
		end;
	end;
	var mv:=s2[0];
	var mi:=0;
	for var w :=0 to len(s2)-1 do
	begin
		if s2[w]>mv then
		begin
			mv:=s2[w];
			mi:=w;
		end;
	end;
	var s:=mi;
	aa:=aa[s:s+k];
	var fi:=aa[0][1];
	var st:=aa[len(aa)-1][1];
	var l:=64;
	for var t :=1 to l do
	begin
		var cl:=(st+st+fi)/3;
		var cr:=(st+fi+fi)/3;
		if ff(cl) < ff(cr) then
			st:=cl;
		if ff(cl) > ff(cr) then
			fi:=cr;
		if ff(cl) = ff(cr) then
		begin
			st:=cl;
			fi:=cr;
		end;
	end;
	var res:=(fi+st)/2;
	while res>pi*2 do res-=pi*2;
	while res<0 do res+=pi*2;
	makesum:= arr(ff(res),2*pi-res);
end;
begin
	var task:=2;
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
	if task=2 then
	begin


		var he:=0;
		var wi:=2;
		read(he);
		var d:array of array of real;
		for var w:=1 to he do
		begin
			push_back(d,emparr(0.0));
			for var e:= 1 to wi do
			begin
				var c:=0;
				read(c);
				push_back(d[w-1],c);
			end;
		end;



		var d1:=stoa(d.select(w->arr( 1.0*w[0]*w[0]+w[1]*w[1] , pi-atan2(w[1],w[0])*2 )         ));




		var f1:=d[0];
		foreach w:array of real in d1[1:] do
		begin
			println(f1,w);
			f1:=makesum(f1,w);
			println(f1);
		end;
		println(f1[1]);
		var f:=f1[1]/2;
		println(f);
		if (pi/4<f) and (f<3*pi/4) then
			println('y='+tan(pi/2-f)+'*x')
		else
			println('x='+tan(f)+'*y');

{}
	end;
end.