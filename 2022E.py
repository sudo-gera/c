from queue import Queue
scan_cache=Queue()

def scan(t=int):
	if type(t) in (list, tuple):
		t=type(t)([scan(w) for w in t])
		return t
	global scan_cache
	while scan_cache.empty():
		for w in input().split():
			scan_cache.put(w)
	return t(scan_cache.get_nowait())

def simple(a,s,d):
    f=set()
    for q in range(a+1):
        for w in range(s+1):
            for e in range(d+1):
                f.add(q+w+w+e+e+e)
    if 0 in f:
        f.remove(0)
    return len(f)

def one(a,s,d):
    if a>6 and d>6:
        a-=3
        d+=a//3
        a%=3
        a+=3
    if s>6 and d>6:
        s-=3
        d+=s//3*2
        s%=3
        s+=3
    print(a,s,d)
    assert a<30 and s<30
    return linear(a,s,d,simple)
    
def linear(a,s,d,one=one):
    print(a,s,d)
    if d<20:
        return one(a,s,d)
    return (one(a,s,20)-one(a,s,19))*(d-19)+one(a,s,19)

def cases(a,s,d):
    if a==0 and s==0:
        return d
    if a==0 and s==1:
        return 2*d+1
    if a==0 and s==2:
        return 3*d+2
    if a==0 and d==0:
        return s
    if a==0 and d==1:
        return 2*s+1
    if s==0 and d==0:
        return a
    if a==0 and s==3 and d>=2:
        return 10+(d-2)*3
    




# a,s,d=scan([int]*3)
# print(linear(a,s,d))

from h import *
c=0
while 1:
    a,s,d=rand(50),rand(50),rand(50)
    # if not simple(a,s,d)==simple(a-3,s,d+1):
    #     print(a,s,d)
    #     print(a-3,s,d+1)
    #     print(simple(a,s,d))
    #     print(simple(a-3,s,d+1))
    #     exit()
    # if not simple(a,s,d)==simple(a,s-3,d+2):
    #     print(a,s,d)
    #     print(a,s-3,d+2)
    #     print(simple(a,s,d))
    #     print(simple(a,s-3,d+2))
    #     exit()
    if simple(a,s,d)!=linear(a,s,d):
        print(a,s,d)
        print(simple(a,s,d))
        print(linear(a,s,d))
        exit()
    # if len(one(a,s,d-1))+len(one(a,s,d+1))!=len(one(a,s,d))*2:
    #     print(a,s,d-1)
    #     print(one(a,s,d-1))
    #     print(a,s,d)
    #     print(one(a,s,d))
    #     print(a,s,d+1)
    #     print(one(a,s,d+1))
    #     exit()
    # if linear(a,s,d)!=one(a,s,d):
    #     print(a,s,d)
    #     print(linear(a,s,d))
    #     print(one(a,s,d))
    #     exit()
    c+=1
    if c%10==0:
        print(time())

# for d in range(20):
#     for a in range(5):
#         for s in range(5):
#             print(len(one(a,s,d)),end='\t')
#     print()
