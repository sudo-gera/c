from h import *
from server_example import *

def save(q,f):
	z=urlopen('https://img.youtube.com/vi/'+q+'/maxresdefault.jpg').read()
	for w in '#%&{}\\<>*?/$!\'":@+`|=':
		f=f.replace(w,'_')
	for w in range(128):
		if chr(w).isspace():
			f=f.replace(chr(w),'_')
	f+='.jpg'
	open(f,'wb').write(z)

s=Server(port=2000)
print(s.port)
while 1:
	a=s.get()
	s.put(b'0')
	try:
		a=a[0]
		print(a)
		a=a.split('|||||')
		a[0]=modules.urllib.parse.parse_qs(modules.urllib.parse.urlparse(a[0]).query)
		a[0]=a[0]['v']
		a[0]=a[0][0]
		a[1]=modules.urllib.parse.unquote_plus(a[1])
		a[1]=a[1][:-len(' - YouTube')]
		save(*a)
	except Exception:
		pass


def url(q):
	urllib=modules.urllib
	url = q
	user_agent = 'Mozilla/5.0 (Windows NT 6.1; Win64; x64)'
	headers = {'User-Agent': user_agent}

	req = urllib.request.Request(url, b'', headers)
	with urllib.request.urlopen(req) as response:
		the_page = response.read()
	return the_page



# save('https://img.youtube.com/vi/vZ48adlBdlI/maxresdefault.jpg','1.jpg')





# from h import *

# @dataclass(order=1)
# class point:
#   x:int
#   y:int

# def rotate(A,B,C):
#   return (B.x-A.x)*(C.y-B.y)-(B.y-A.y)*(C.x-B.x)

# def grahamscan(A):
#   n = len(A)
#   P = list(range(n))
#   for i in range(1,n):
#     if A[P[i]].x<A[P[0]].x:
#       P[i], P[0] = P[0], P[i]
#   for i in range(2,n):
#     j = i
#     while j>1 and (rotate(A[P[0]],A[P[j-1]],A[P[j]])<0): 
#       P[j], P[j-1] = P[j-1], P[j]
#       j -= 1
#   S = [P[0],P[1]]
#   for i in range(2,n):
#     while rotate(A[S[-2]],A[S[-1]],A[P[i]])<0:
#       S.pop()
#     S.append(P[i])
#   return S


# def vd(q,e):
#   return q.x*e.y-q.y*e.x;

# def vect(_x,_y):
#   x=_y.x-_x.x
#   y=_y.y-_x.y
#   return point(x,y)

# def area(vertices):
#   res=0;
#   for w in range(2,len(vertices)):
#     res+=vd(vect(vertices[0],vertices[w-1]),vect(vertices[w-1],vertices[w]));
#   return abs(res)/2;

# def run(a):
#   n=len(a)
#   a.sort()
#   a=reduce(lambda a,s:a+[s] if s not in a else a, a, [])
#   aa=grahamscan(a)
#   a=[a[w] for w in aa]
#   for w in range(len(a)):
#     a=reduce(lambda _a,_s:_a+[_s] if len(_a)<2 or vd(vect(_a[-1],_s),vect(_a[-1],_a[-2])) else _a[:-1]+[_s], a, [])
#     a=a[1:]+a[:1]
#   r=[]
#   for w in a:
#     r.append(w)
#   # r.sort()
#   r=[len(a)]+r
#   r.append(round(area(a),1))
#   return r

# if __name__ == '__main__':
#   n=scan(int)
#   a=[point(scan(int),scan(int)) for w in range(n)]
#   a=run(a)
#   print(a[0])
#   for w in a[1:-1]:
#     print(w.x,w.y)
#   print(a[-1])
