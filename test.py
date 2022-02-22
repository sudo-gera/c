<<<<<<< HEAD

=======
from h import *

<<<<<<< HEAD
def get_index_a(q,n):
	q=int(q)
	a=list(range(10**n))
	a.sort(key=str)
	return a.index(q)

def get_index_b(q,m):
	q=int(q)
	m=int(m)
	a=list(range(m+1))
	a.sort(key=str)
	return a.index(q)

def get_index(q,n):
	q=str(q)

	if len(q)==1:
		q=int(q)
		return int(str(q-1)*n)+1
	if q[0]>'1':
		w=int('1'+q[1:])
		return get_index(w,n)+int(str(int(q[0])-1)*n)

	if q[0]=='1' and q[1]!='0':
		w=int(q[1:])
		return get_index(q[1:],n-1)+int('1'*(n-1))+1

	return get_index(q[0]+'1'+q[2:],n)*2-get_index(q[0]+'2'+q[2:],n)


def get_index1(q,m):
	q=str(q)
	m=str(m)
	if q>m:
		return\
		get_index(q,         len(m)-1)-\
		get_index(m[:-1],    len(m)-1)+\
		get_index(m[:-1]+'0',len(m))+\
		int(m[-1:])
	else:
		return get_index(q,len(m))

# for w in range(9999):
# 	m=randint(1,999)
# 	q=randint(1,m)
# 	try:
# 		if get_index1(q,m) != get_index_b(q,m):
# 			print(q,m)
# 			break
# 	except:
# 		print(q,m)
# 		break

# print(get_index_b(*[scan(str),scan(str)][::-1]))

def get_index2(q,n):
	q=str(q)
	n=int(n)
	while len(q)<n:
		q+='/'
	q=[chr(ord(w)+1) for w in q]
	q=['a' if w==':' else w for w in q]
	q=''.join(q)
	q=int(q,11)
	d=11**(n-1)
	a=[d]
	while d:
		a.append(a[-1]+d)
		d//=11
	aa=a
	# if q in a:
	# 	return a.index(q)
	while q not in a:
		a.append(a[-1]+1)
	# return a.index(q)

	# return len(a)-1+q-a[-1]

	a=list(range(10**n))
	a.sort(key=str)
	a=[str(w) for w in a]
	a=[(w+'/'*n)[:n] for w in a]
	a=[''.join([chr(ord(w)+1) for w in q]) for q in a]
	a=[''.join(['a' if w==':' else w for w in q]) for q in a]
	a=[int(w,11) for w in a]
	if not a[:len(aa)]==aa:
		print(a[:len(aa)])
		print(aa)
		assert 0
	return a.index(q)


# n=5
# a=list(range(10**n))
# a.sort(key=str)
# a=[str(w) for w in a]
# a=[(w+'/'*n)[:n] for w in a]
# q=[''.join([chr(ord(w)+1) for w in q]) for q in a]
# q=[''.join(['a' if w==':' else w for w in q]) for q in q]
# q=[int(w,11) for w in q]
# print(q[:111])


for w in range(9999):
	n=randint(1,3)
	q=randint(1,10**n-1)
	try:
		if get_index2(q,n) != get_index(q,n):
			print(q,n)
			break
	except Exception:
		print(q,n)
		break
=======
print(input()+'_')

# if 1:
# 	q=[0]*8*4
# 	w=1
# 	w=scan(int)
# 	while w:
# 		if w==1:
# 			e,r=0,0
# 			e,r=scan(int),scan(int)
# 			q[e]=r
# 		else:
# 			e=scan(int)
# 			print(q[e])
# 		w=scan(int)
>>>>>>> ce402be16924a6f15247777b49396153b9b46ecc
>>>>>>> 74d49e8f8825a736a557241cf782f40ee7fd9ab7
