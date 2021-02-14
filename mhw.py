a=input()
from re import *
f=findall(r'[a-zA-Z]+',a)
if f:
	l=len(max(f,key=len))
	s=''.join(list(map(chr,range(ord('a'),ord('z')+1))))
	d=''.join(list(map(chr,range(ord('A'),ord('Z')+1))))
	a=[s[s.index(w)+l-len(s)] if w in s else d[d.index(w)+l-len(d)] if w in d else w for w in a]
	a=''.join(a)
print(a)
