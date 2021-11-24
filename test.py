from pprint import pprint
a=open('test.txt').read()
a=a.split('====== Test')
a=[w for w in a if w]
s=[]
for w in a:
	w=w[w.index('=======\n--- Input: size')+len('=======\n--- Input: size'):]
	w=w[w.index('\n')+len('\n'):]
	w=w[:w.index('\n--- Output: size')]
	w=w.split()
	s.append(w)
a=s
s=[w[1] for w in a]
s=set(list(s))
s=[]
def root(q,n):
	b=0
	e=q
	while e-b>1:
		c=(b+e)//2
		d=c**n
		if (d>q):
			e=c
		elif (d<q):
			b=c
		elif (d==q):
			b=c
			e=c
	return b
def to_radix(_q,_e):
	q,e=_q,_e
	z=abs(q)
	s=''
	while z:
		s+=str("0123456789abcdefghijklmnopqrstuvwxyz".upper()[z%e])
		z//=e
	if q<0:
		s+='-'
	if not s:
		s='0'
	s=s[::-1]
	if int(s,e)!=q:
		print('error radix',[a.index(w)])
	return s
# a=[w for w in a if w[1]!='memstress']
for w in a:
	if w[1]=='pow':
		w.append(int(w[0])**int(w[2]))
	elif w[1]=='+':
		w.append(int(w[0])+int(w[2]))
	elif w[1]=='-':
		w.append(int(w[0])-int(w[2]))
	elif w[1]=='*':
		w.append(int(w[0])*int(w[2]))
	elif w[1]=='/':
		w.append(int(w[0])//int(w[2]))
	elif w[1]=='%':
		w.append(int(w[0])%int(w[2]))
	elif w[1]=='root':
		w.append(root(int(w[0]),int(w[2])))
	elif w[1]=='to_radix':
		w.append(to_radix(int(w[0]),int(w[2])))
	elif w[1]=='memstress':
		w.append(0)
	else:
		print(w[1])
	s.append(w)
a=s
a=[  w[:-1]+[str(w[-1])]    for w in a]
a=[f'/* { {"pow":"**","+":"+","-":"-","*":"*","/":"/","%":"%","root":"/ *","to_radix":"<< *","memstress":"^*"}[w[1]] } */test(str(BigInteger("{w[0]}",10){ {"pow":"**","+":"+","-":"-","*":"*","/":"/","%":"%","root":"/ *","to_radix":"<< *","memstress":"^*"}[w[1]] }BigInteger("{w[2]}",10)),"{w[3]}")' for w in a]
a=[f'#ifndef HIDE_{q}\n\tt=monotonic();\n\t{w}\n\tprint("test {q}",output_time(monotonic()-t));\n#endif\nic()\n' for q,w in enumerate(a)]
# a=[w if len(w)>1000 else f'print("skipping {q}");\n' for q,w in enumerate(a)]
a=[w if len(w) else f'' for q,w in enumerate(a)]
# a=a[:40]
a=''.join(a)
a='\tauto t=monotonic();\n'+a
open('stdout.cpp','w').write(a)















