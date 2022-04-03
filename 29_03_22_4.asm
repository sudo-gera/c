%include "macro.inc"
section .data
start
mov ecx,esp
dget [q]
for [w],[q]
	wget [e]
	wpush [e]
end
cput 10
mov edx,esp

for esi,edx,ecx,2
	for edi,edx,esi,2
		wuif [esi],==,[edi]
			mov al,1
		end
	end
end

buprint al

dmul [q],2
add esp,[q]

stop
