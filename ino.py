n,m,q=list(map(int,input().split()))
a,b=list(map(int,input().split()))

def next(x,y):
	global nc,px,py,ppx,ppy
	nc+=(abs(px-x)+1)*(abs(py-y)+1)-1
	ppx=px
	ppy=py
	px=x
	py=y
	return nc

def rect(x,y):
	global nc,px,py,ppx,ppy
	if ppy==py:
		nc+=(abs(px-x)+1)*(abs(py-y))
	if ppx==px:
		nc+=(abs(px-x))*(abs(py-y)+1)
	return nc

def room(n,m,a,b):
	global nc,px,py,ppx,ppy
	w=min([a-1,b-1,n-a,m-b])
	nc+=w*(n+m+n+m)-w*w*4
	px+=w
	py+=w
	ppx=px+1
	ppy=py
	return nc


def main(n,m,a,b):
	c=input().split()
	x,y,c=list(map(int,c[:-1]))+c[-1:]
	c=c.lower()

	for w in range('enws'.index(c))
		x,y=n-y+1,x
		a,b=n-b+1,a
		n,m=m,n

	ppx,ppy,px,py=x,y,x,y
	nc=1
	if a>x and b==y:
		next(a-1,y)
		if y==1:
			return nc
		else:
			if x==1:
				return rect(1,1)
			else:
				next(a-1,1)
				next(1,1)
				if y==m:
					return rect(x-1,m)
				else:
					next(1,m)
					if a==n:
						return rect(n,b+1)
					else:
						next(n,m)
						return rect(a+1,1)
	else:
		next(n,y)
		if a==n and b==y-1:
			return nc
		else:
			if a==n and b<y-1:
				next(n,b+1)
				if x==0:
					return rect(1,y-1)
				else:
					next(1,b+1)
					if y==m:
						return rect(x-1,m)
					else:
						next(1,m)
						return rect(n,y+1)
			else:
				next(n,1)
				if b==1:
					if a>x-2:
						return rect(a+1,y-1)
					else:
						next(a+1,1)
						if y==m:
							return rect(x-1,m)
						else:
							next(a+1,m)
							return rect(n,y+1)
				else:
					next(1,1)
					if a==1 and b<=y:
						return rect(n-1,b-1)
					else:
						if x==1:
							if b>y:
								return rect(n-1,y-1)
							else:
								room(n-1,y-1,a,b-1)

								pass
								]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
						else:
							if a==1 and b==y+1:
								return rect(x-1,y)
							else:
								if a==1:
									next(1,b-1)
									return rect(n,y+1)
								else:
									if b<y:
										next(1,m)
										return rect(n,y+1)
									else:
										next(1,y)
										room(n,m-y,a,b-y)

										pass
										]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]



for w in range(q):
	print(main(n,m,a,b))


