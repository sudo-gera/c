from h import *

def gen1(n):
	a=[None]*(n+n+n+n)
	gen2(n,a)
	a=a[:n]
	return a

def gen2(n,a):
	if (n==2):
		a[0]=2;
		a[1]=1;
		return;
	w=0;
	while (w<n):
		a[w]=w+1;
		w+=1;
	w=3;
	while (w<n+1):
		a[w-1]=a[int((w-1)/2)];
		a[int((w-1)/2)]=w;
		w+=1;

def gen(n,r=0):
	if n<3:
		a=list(range(1,n+1))
		if r==0:
			a=a[::-1]
		return a
	a=gen(n-1,1)
	a.append(a[(n-1)//2])
	a[(n-1)//2]=n
	return a

a=[w for w in range(995)]
a=[gen(w)==gen1(w) for w in a]
print(all(a))
# print(a)

def quickSort(a,l=0,r=-1,pr=1):
	r%=len(a)
	# if pr:
	# 	print(a[l:r+1])
	res=0
	x = a[(l + r) // 2];
	i = l;
	j = r;
	while(i <= j):
		while(a[i] < x):
			i+=1;
			res+=1
		res+=1
		while(a[j] > x):
			j-=1;
			res+=1
		res+=1
		if(i <= j):
			(a[i], a[j])=(a[i], a[j])[::-1];
			i+=1;
			j-=1;
	if (i < r):
		res+=quickSort(a,i, r,pr);
	if (l < j):
		res+=quickSort(a,l, j,pr);
	return res

# for size in range(1,11):
# 	a=list(range(size))
# 	a=permutations(a)
# 	a=[list(w) for w in a]
# 	a=[w for w in a if w[(len(w)-1)//2]==size-1]
# 	a=[[quickSort(w[:],pr=None),w] for w in a]
# 	a.sort()
# 	a=[w for w in a if w[0]==a[-1][0]]
# 	[quickSort(w[1][:]) for w in a]
# 	# pprint(a)
# 	print(a[-1][0]==quickSort(gen(size)))
# 	print(gen(size))
