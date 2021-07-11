













uses system.io;
begin
	foreach var a in directory.getfiles('/Users/gera') do
		print(a);
end.
