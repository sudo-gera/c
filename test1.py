from h import *

@dataclass(order=1)
class point:
  x:int
  y:int

def VecProdDot(A,B,C):
  # print(A,B,C)
  s=(B.x-A.x)*(C.y-B.y)-(B.y-A.y)*(C.x-B.x)
  # print(s)
  return s

aaaa=0

base=0

def cmp(a,s):
  global base
  global aaaa
  return - VecProdDot(aaaa[base],aaaa[a],aaaa[s])

def grahamscan(a,s):
  global base
  global aaaa
  for w in a:
    print(w,end=' ')
  print()
  n = len(a)
  p=[0]*n
  for w in range(n):
    p[w]=w
  for i in range(1,n):
    if a[p[i]].x<a[p[0]].x:
      p[i], p[0] = p[0], p[i]
  aaaa=a
  base = p[0]
  del p[0]
  print(p)
  p.sort(key = cmp_to_key(cmp))
  print(p)
  p.insert(0, base)
  for w in range(2,n):
    assert cmp(p[w-1],p[w])<=0
  s[0]=p[0]
  s[1]=p[1]
  ls=2
  assert len(p)==n
  i=2
  for w in a:
    print(w,end=' ')
  print()
  while (i<n):
    # print(s[ls-2],s[ls-1],p[i],i)
    while (VecProdDot(a[s[ls-2]],a[s[ls-1]],a[p[i]])<0):
      ls-=1;
    s[ls]=p[i];
    ls+=1;
    i+=1;
  print(s[:ls])
  return ls


def vd(q,e):
  return q.x*e.y-q.y*e.x;

def vect(_x,_y):
  x=_y.x-_x.x
  y=_y.y-_x.y
  return point(x,y)

def area(vertices):
  res=0;
  for w in range(2,len(vertices)):
    res+=vd(vect(vertices[0],vertices[w-1]),vect(vertices[w-1],vertices[w]));
  return abs(res)/2;

def run(a):
  n=len(a)
  a.sort()
  a=reduce(lambda a,s:a+[s] if s not in a else a, a, [])
  s=[0]*n
  ls=grahamscan(a,s)
  aa=s[:ls]
  a=[a[w] for w in aa]
  for w in range(3):
    a=reduce(lambda _a,_s:_a+[_s] if len(_a)<2 or vd(vect(_a[-1],_s),vect(_a[-1],_a[-2])) else _a[:-1]+[_s], a, [])
    a=a[1:]+a[:1]
  a=a[len(a)-3:]+a[:len(a)-3]
  r=[]


  n=len(a)
  perf_index = 0
  for w in range(len(a)):
    mp = 0;
    if (a[w].x < a[perf_index].x):
      mp = 1
    if (a[w].x == a[perf_index].x and a[w].y < a[perf_index].y):
      mp = 1
    if (mp):
      perf_index = w;
  a=a[perf_index:]+a[:perf_index]

  for w in range(n,0,-1):
    r.append(a[w%n])

  r=[len(a)]+r
  r.append(round(area(a),1))
  return r

if __name__ == '__main__':
  n=scan(int)
  a=[point(scan(int),scan(int)) for w in range(n)]
  a=run(a)
  print(a[0])
  for w in a[1:-1]:
    print(w.x,w.y)
  print(a[-1])
