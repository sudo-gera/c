%include "st_io.inc"
%include "macro.inc"
start

def factor
	dmov ebx,2
	while ebx,<=,65536
		dmod edx,eax,ebx
		while edx,==,0
			ddiv eax,ebx
			print ebx
			dmod edx,eax,ebx
		end
		dinc ebx
	end
	if eax,>,1
		print eax
	end
end

dget eax
call0 factor,eax


stop
