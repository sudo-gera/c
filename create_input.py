from traceback import *
from random import *
from fractions import *
from sys import *
from builtins import *
run_num=int(argv[1]) if len(argv)>1 else 0
def rand(q=2**64,e=None):
	if e!=None:
		q,e=e,q
	else:
		e=0
	assert q
	return randint(e,q-1)
def getstr(l=200):
	return ''.join([choice('snmrdfhg')+choice('aioue') for w in range(rand(1,l))])[:l]
maxlen=200+int(run_num**0.5)
strs=[getstr(maxlen) for w in range(1)]

a=''.join([choice(choice(strs)) if rand(8) else choice(strs) for w in range(maxlen)])

# def prefix_fun(s):
# 	p=[0]*len(s)
# 	for i in range(1,len(s)):
# 		k = p[i - 1]
# 		while k > 0 and s[i] != s[k]:
# 			k = p[k - 1]
# 		if s[i] == s[k]:
# 			k+=1
# 		p[i]=k
# 	return p

# d=[]
# a=list(a)
# for q,w in enumerate(a):
# 	if w not in d:
# 		d.append(w)
# for q,w in enumerate(a):
# 	a[q]=chr(ord('a')+d.index(w))
# a=''.join(a)



# p=prefix_fun(a)
# print(len(p))
# print(*p)
# print('|')
print(a)
print(len(strs))
for w in strs:
	print(w)


















# def is_correst(a):
#     c=0
#     for w in a:
#         if w=='(':
#             c+=1
#         if w==')':
#             c-=1
#         if c<0:
#             return False
#     return c==0

# def create(n):
# 	if n<4:
# 		return '()'[:n]
# 	if rand(2):
# 		return '('+create(n-2)+')'
# 	else:
# 		t=randint(1,n//2-1)
# 		return create(t*2)+create(n-t*2)

# n=rand(1,4)*2
# q=rand(9)
# # q=1
# print(n,q)
# print(create(n))
# for w in range(q):
# 	print(rand(1,n+1),rand(1,n+1))

# print(rand(),rand(),rand())

# a=open('test.txt','w')
# for w in range(rand(100)):
# 	a.write(rand(1000,10000))
# a.close()

# a=list(getstr(29000))
# s=list(getstr(29000))

# for w in range(100):
# 	d=list(getstr(10000))
# 	f=rand(len(a)-len(d)-1)
# 	a[f:f+len(d)]=d
# 	f=rand(len(a)-len(d)-1)
# 	s[f:f+len(d)]=d
# a=''.join(a)
# s=''.join(s)


# print(a)
# print(s)

# while 1:
# 	s=''.join([choice('1234567890?*?*') for w in range(rand(1,10))])
# 	a=list(s)
# 	while '?' in a:
# 		a[a.index('?')]=choice('1234567890')
# 	while '*' in a:
# 		a[a.index('*')]=''.join([choice('1234567890') for w in range(rand(2))])
# 	for w in range(rand(40)-2):
# 		a[choice(list(range(len(a))))]=choice('1234567890')
# 	if not a:
# 		a='1'
# 	if len(''.join(a))<700:
# 		print(''.join(a))
# 		print(s)
# 		break

# llen=10**5

# n=rand(2,llen)
# m=rand(0,1+min(llen,(n-1)**2//4))
# print(n)
# # print(n,m)
# e=set()
# while len(e)<m:
# 	r=t=0
# 	while r==t:
# 		r=rand(n)+1
# 		t=rand(n)+1
# 	# r,t=sorted([r,t])
# 	e.add((r,t))
# for w in e:
# 	print(*w)

# while 1:
# 	try:
# 		n=rand(2,8)
# 		a=rand(n)
# 		s=[set() for w in range(n)]
# 		d=[a]
# 		f=set(range(n))
# 		for w in range(rand(16)):
# 			t1=s[d[-1]]
# 			t=list(f-t1-{d[-1]})
# 			if t:
# 				y=choice(t)
# 				s[d[-1]].add(y)
# 				d.append(y)
# 			else:
# 				break
# 		if d[-1]!=a:
# 			s[d[-1]].add(a)
# 			d.append(a)
# 		s=d
# 		# print(s)
# 		d=[w for w in zip(s[:],s[1:])]
# 		# print(d)
# 		e=[0]*n
# 		for q in d:
# 			e[q[0]]+=1
# 			e[q[1]]-=1
# 		assert e==[0]*n
# 		assert len(set(d))==len(d)
# 		print(n,a+1)
# 		for q in range(n):
# 			for w in range(n):
# 				# tmp=str((q,w))
# 				# esc='\x1b['
# 				# print(f'{esc}{30+10*w}C',tmp,f'{esc}{30+10*w+len(tmp)}D',sep='',end='')
# 				if (q,w) in d:
# 					print(0,end=' ')
# 				else:
# 					print(1,end=' ')
# 			print()
# 		break
# 	except:
# 		# print(format_exc(),file=stderr)
# 		pass

# n=rand(2,64)
# m=rand(0,min(64,n*(n-1)//2))
# k=rand(0,n)
# print(n,m,k)
# f=list(range(1,n+1))
# shuffle(f)
# print(*sorted(f[:k]))
# g=[[q+1,w+1,rand(64)] for q in range(n) for w in range(n) if q!=w]
# shuffle(g)
# for w in g[:m]:
# 	print(*w)
# f=list(range(1,n+1))
# shuffle(f)
# print(*f[:2])
