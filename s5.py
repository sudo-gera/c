n=input()
try:
	n=int(n)
	a=[int(w) for w in input().split()]
except:
	a=[int(w) for w in n.split()]
	n=len(a)
from functools import cache
# @cache
# def get(u):
# 	if u<3:
# 		return 0
# 	if a[u-1]<a[u-2]>a[u-3] or a[u-1]>a[u-2]<a[u-3]:
# 		r=1+get(u-2)
# 	else:
# 		r=max(get(u-1),get(u-2))
# 	return r

# print(get(len(a)))

def get(b):
	print(b)
	if b==n:
		return 0
	if b+1<n:
		if a[b]<a[b+1]:
			v=b
			while v+1<n and a[v]<=a[b+1]:
				v+=1
			v-=1
			if v+1<n:
				r=get(v+1)
				if r!=None:
					return r+1
				else:
					return None
			else:
				return None
		if a[b]>a[b+1]:
			v=b
			while v+1<n and a[v]>=a[b+1]:
				v+=1
			v-=1
			if v+1<n:
				r=get(v+1)
				if r!=None:
					return r+1
				else:
					return None
			else:
				return None
		if a[b]==a[b+1]:
			v=b
			while v+1<n and a[v]==a[b+1]:
				v+=1
			return get(v)
	else:
		return None


print(get(0))
