from fractions import Fraction as f
from pprint import pprint
from random import *
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
# s=[w[1] for w in a]
# s=set(list(s))
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
def to_dec(q,e):
	q*=10**e
	s=str(int(q))
	s='0'*(e-len(s)+1)+s
	s=s[:len(s)-e]+'.'+s[len(s)-e:]
	return s
a.append(['1000000000000000000000000000000000','/','-1000000'])
a.append(['453234523460009834520987234598234502345987029345436345634563','/','234523452034623049872345234520983475325345234232578'])
a.append(['-23534576554950000000000000009999990000999900000','/','8888888888884444444444433333333333332222222222222111112222777777777'])
a.append(['-1','/','1'])
a.append(['1000000000000000000000000000000000','%','-1000000'])
a.append(['453234523460009834520987234598234502345987029345436345634563','%','234523452034623049872345234520983475325345234232578'])
a.append(['-23534576554950000000000000009999990000999900000','%','8888888888884444444444433333333333332222222222222111112222777777777'])
a.append(['-1','/','1'])
# a=[w for w in a if w[1]!='%']
# a=[w for w in a if w[1]!='root']
# a=[w for w in a if w[1]!='pow']
# a=[w for w in a if w[1]!='to_radix']
# a=[w for w in a if w[1]!='memstress']
# a=[]
aa=382343234334334323331
# for w in range(400):
# 	# a.append([str(randint(-aa,aa))+'/'+str(randint(1,aa)),choice('+-/*'),str(randint(-aa,aa))+'/'+str(randint(1,aa))])
# 	a.append([str(randint(-aa,aa))+'/'+str(randint(1,aa)),'dec',str(randint(0,20))])
for w in a:
	if w[1]=='pow':
		w.append(f(w[0])**f(w[2]))
	elif w[1]=='+':
		w.append(f(w[0])+f(w[2]))
	elif w[1]=='-':
		w.append(f(w[0])-f(w[2]))
	elif w[1]=='*':
		w.append(f(w[0])*f(w[2]))
	elif w[1]=='/':
		w.append(int(w[0])//int(w[2]))
		# w.append(abs(int(w[0]))//abs(int(w[2]))*(-1 if int(w[0])*int(w[2])<0 else 1))
		# w.append(f(w[0])/f(f(w[2])))
	elif w[1]=='%':
		w.append(int(w[0])%int(w[2]))
		# w.append(abs(f(w[0]))%abs(f(w[2]))*(-1 if f(w[0])*f(w[2])<0 else 1))
	elif w[1]=='root':
		w.append(root(f(w[0]),f(w[2])))
	elif w[1]=='to_radix':
		w.append(to_radix(int(w[0]),int(w[2])))
	elif w[1]=='memstress':
		w.append(0)
	elif w[1]=='dec':
		w.append(to_dec(f(w[0]),int(w[2])))
	else:
		print(w[1])
	s.append(w)
a=s
a=[  w[:-1]+[str(w[-1])]    for w in a]
d={"pow":"**","+":"+","-":"-","*":"*","/":"/","%":"%","root":"/ *","to_radix":"<< *","memstress":"^*","dec":"%"}
n='BigInteger'
# n='Rational'
a=[f'/* { d[w[1]] } */test(str({n}("{w[0]}",10){ d[w[1]] }{n}("{w[2]}",10)),"{w[3]}")' for w in a]
a=[f'#ifndef HIDE_{q}\n\tt=monotonic();\n\t{w}\n\tprint("test {q}",output_time(monotonic()-t));\n#endif\n' for q,w in enumerate(a)]
a=[w if len(w) else f'//print("skipping {q}");\n' for q,w in enumerate(a)]
a=[w if len(w) else f'' for q,w in enumerate(a)]
# a=a[:40]
a=''.join(a)
a='\tauto t=monotonic();print("starting...");\n'+a+'print("stopping...");\n'
open('stdout.cpp','w').write(a)















