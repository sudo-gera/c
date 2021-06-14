var x,y,b,m,n,e:int64;
begin
	read(n);
	for y :=0 to n-1 do begin
		for x :=0 to n-1 do begin
			m:=(x+y-n div 2);
			b:=(x-y-n div 2)-m*(n-3);
			m:=(m mod n+n) mod n;
			b:=(b mod n+n) mod n;
			b:=b+b mod 2*n;
			b:=b div 2;
			e:=m*n+b+1;
			write(e:7,' ');
		end;
		writeln();
	end;
end.