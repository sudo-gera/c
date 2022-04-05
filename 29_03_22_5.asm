%include "macro.inc"
section .data
aa times 9 dd 9
start
for [w],9
	daget [q],aa,[w]
	write [q]
end
cput 10
push dword aa
mov eax,[esp]
dmov [eax+ 0],0
dmov [eax+ 4],0
dmov [eax+ 8],0
dmov [eax+12],0
dmov [eax+16],0
dmov [eax+20],0
dmov [eax+24],0
dmov [eax+28],0
dmov [eax+32],0
add esp,4

for [w],9
	daget [q],aa,[w]
	write [q]
end
cput 10

stop
