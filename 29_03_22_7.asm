%include "macro.inc"

start
mov eax,esp

cget [c]
while [c],!=,10
	dmov [n],0
	if [c],<=,'9'
		if [c],>=,'0'
			dmov [n],1
		end
	end
	dmov [l],0
	if [c],<=,'z'
		if [c],>=,'a'
			dmov [l],1
		end
	elif [c],<=,'Z'
		if [c],>=,'A'
			dmov [l],1
		end
	elif [c],==,'_'
		dmov [l],1
	end
	if [c],==,'+'
		dpush 0
		dpush [c]
		cget [c]
	elif [c],==,'-'
		dpush 0
		dpush [c]
		cget [c]
	elif [c],==,'*'
		dpush 0
		dpush [c]
		cget [c]
	elif [c],==,'/'
		dpush 0
		dpush [c]
		cget [c]
	elif [c],==,'%'
		dpush 0
		dpush [c]
		cget [c]
	elif [n],!=,0
		dmov [q],0
		while [n],!=,0
			dsub [c],48
			dmul [q],10
			dadd [q],[c]
			cget [c]
			dmov [n],0
			if [c],<=,'9'
				if [c],>=,'0'
					dmov [n],1
				end
			end
		end
		dpush 1
		dpush [q]
	elif [l],!=,0
		dmov [q],0
		while [l],!=,0
			dsub [c],48
			dmul [q],123
			dadd [q],[c]
			cget [c]
			dmov [l],0
			if [c],<=,9
				if [c],>=,'0'
					dmov [l],'1'
				end
			elif [c],<=,'z'
				if [c],>=,'a'
					dmov [l],1
				end
			elif [c],<=,'Z'
				if [c],>=,'A'
					dmov [l],1
				end
			elif [c],==,'_'
				dmov [l],1
			end
		end
		dmov [g],1
		mov ebx,esp
		for ecx,ebx,eax,8
			if [ecx+4],==,2
				if [ecx],==,[q]
					dmov [g],0
				end
			end
		end
		if [g],==,1
			dinc [v]
		end
		dpush 2
		dpush [q]
	elif [c],==,' '
		pass
		cget [c]
	else
		swrite "unknown character"
		cwrite [c]
		print [c]
		cget [c]
	end
end

mov ebx,esp

dmov [d],eax
dmov [s],ebx

; for ecx,[s],[d],4
; 	write [ecx]
; end
; cput 10

dmov eax,[s]
dmov ebx,[d]

while eax,<,ebx
	dmov [t],[eax]
	dmov [eax],[ebx-4]
	dmov [ebx-4],[t]
	add eax,4
	sub ebx,4
end

; for ecx,[s],[d],4
; 	write [ecx]
; end
; cput 10

for [w],[v]
	cget [c]
	dmov [l],1
	dmov [q],0
	while [l],!=,0
		dsub [c],48
		dmul [q],123
		dadd [q],[c]
		cget [c]
		dmov [l],0
		if [c],<=,'9'
			if [c],>=,'0'
				dmov [l],1
			end
		elif [c],<=,'z'
			if [c],>=,'a'
				dmov [l],1
			end
		elif [c],<=,'Z'
			if [c],>=,'A'
				dmov [l],1
			end
		elif [c],==,'_'
			dmov [l],1
		end
	end
	dmov [a],[q]
	dmov [n],1
	cget [c]
	dmov [q],0
	while [n],!=,0
		dsub [c],48
		dmul [q],10
		dadd [q],[c]
		cget [c]
		dmov [n],0
		if [c],<=,'9'
			if [c],>=,'0'
				dmov [n],1
			end
		end
	end
	for ecx,[s],[d],8
		if [ecx],==,2
			if [ecx+4],==,[a]
				dmov [ecx],1
				dmov [ecx+4],[q]
			end
		end
	end
end

; for ecx,[s],[d],4
; 	write [ecx]
; end
; cput 10

for ecx,[s],[d],8
	if [ecx],==,1
		dpush [ecx+4]
	else
		dpop [z]
		dpop [x]
		if [ecx+4],==,'+'
			dadd [b],[z],[x]
			dpush [b]
		elif [ecx+4],==,'-'
			dsub [b],[x],[z]
			dpush [b]

		elif [ecx+4],==,'*'
			dmul [b],[z],[x]
			dpush [b]

		elif [ecx+4],==,'/'
			ddiv [b],[x],[z]
			dpush [b]

		elif [ecx+4],==,'%'
			dmod [b],[x],[z]
			dpush [b]
		end
	end
end

dpop [b]

print [b]

dsub [b],[d],[s]

add esp,[b]

stop
