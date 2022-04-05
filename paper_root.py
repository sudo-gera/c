from h import *
def root(q):
	p=0
	while 10**p<q:
		p+=2
	s=1
	l=p
	for w in range(29):
		if type(q)==int:
			print(f'%80i'%q)
		else:
			print((f'%{81+l-p+1}.{l-p+1}f' % q).replace('.',''))
		print((f'%{80-p}.i' % s))
		print('%f' % ((s-1)/2*10**(p/2)))
		print()
		# if s*10**p>q and p==0:
		# 	break
		if s*10**p>q:
			p-=2
			s*=10
			s-=9
		else:
			q-=s*10**p
			s+=2
	return 10**(p/2)*(s-1)/2




# for w in range(2,2999):
# 	n=w if w<99 else rand(10**80)
# 	# n=rand(10**80)
# 	# if root(n)!=floor_root(n):
# 	if abs(root(n)-n**0.5)>0.001*(n+1)**0.5:
# 		print(n)
# 		print(root(n))
# 		print(floor_root(n))
# 		print(n**0.5)
# 		print(abs(root(n)-n**0.5))
# 		print(abs(root(n)-n**0.5)/(n+1)**0.5)
# 		break
# root(12345678987654321)
# print()
root(2000)
# root(1000**2+1)
# root(9999)
# root(1111)
# root(99999)
# root(11111)
# root(123**2)
