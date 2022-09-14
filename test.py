# z=[0]*16
# def f(n):
#     # print(n)
#     # for w in range(4):
#     #     print(z[4*w:4*w+4])
#     if n==len(z):
#         return 1
#     a,s=divmod(n,4)
#     q={1,2,3,4}
#     for w in range(a):
#         q-={z[4*w+s]}
#     for w in range(s):
#         q-={z[4*a+w]}
#     c=0
#     for w in q:
#         z[n]=w
#         c+=f(n+1)
#         z[n]=0
#     return c
# print(f(0))

from copy import copy

class vector:
    def __init__(s,x=0,y=0):
        if type(x)==vector:
            s.x=x.x
            s.y=x.y
        else:
            s.x=x
            s.y=y
    def __imul__(s,o):
        s=vector(s)
        s.x*=o
        s.y*=o
        return s
    def __iadd__(s,o):
        s=vector(s)
        s.x+=o.x
        s.y+=o.y
        return s
    def __isub__(s,o):
        s=vector(s)
        s.x-=o.x
        s.y-=o.y
        return s
    def __mul__(s,o):
        s=vector(s)
        s.x*=o
        s.y*=o
        return s
    def __add__(s,o):
        s=vector(s)
        s.x+=o.x
        s.y+=o.y
        return s
    def __sub__(s,o):
        s=vector(s)
        s.x-=o.x
        s.y-=o.y
        return s


z=0
q=0
c=0
while 1:
    q=z
    z+=1
    g=[[] for w in range(5)]
    for w in range(5):
        for e in range(w):
            if q%2:
                g[w].append(e)
                g[e].append(w)
            q//=2
    if q:
        break
    h=copy(g)
    if all([len(w)!=1 for w in g]):
        s=set(g[0])
        g[0]=[]
        while 1:
            for w in list(s):
                s|=set(g[w])
                g[w]=[]
            if len(s)==5:
                break
            if all([g[w]==[] for w in s]):
                break
        if len(s)==5:
            print(h)
            coord=[
                vector(20,0),
                vector(0,25),
                vector(20,50),
                vector(50,40),
                vector(50,10),
            ]
            term=[[' ']*55 for w in range(55)]
            for q,w in enumerate(h):
                for e in [e for e in range(5) if e!=q]:
                # for e in w:
                    a=coord[q]
                    d=coord[e]
                    for r in range(1000):
                        s=(d-a)*0.001*r+a
                        if e in w:
                            term[round(s.x)][round(s.y)]='\x1b[34m#\x1b[0m'
                        else:
                            term[round(s.x)][round(s.y)]='\x1b[31m#\x1b[0m'
            for w in term[::2]:
                for e in w[::]:
                    print(e,end='')
                print()
            c+=1
print(c)




# from h import *

# def whois(ip:str):
#     a=subprocess.run(['whois',ip],stdout=PIPE)
#     a=a.stdout.read().splitlines()
    



# from subnets import *
# from random import *
# try:
#     d=loads(open(home+'/warp.json','r').read())
# except Exception:
#     d={}
# while 1:
#     print('%.2f'%(sum([2**(32-ip_network(w).prefixlen) for w in d])/2**32))
#     for w in range(256**2):
#         ip=ip_network(rand(256**4))
#         for w in d:
#             if ip.subnet_of(ip_network(w)):
#                break
#         else:
#             ip=str(ip)[:-3]
#             break
#     else:
#         a=exclude('0.0.0.0/0',d.keys())
#         ip=str(choice(list(zip(choice(a).hosts(),range(64))))[0])
#     a=popen('whois '+ip).read()
#     a=[w.split(':') for w in a.splitlines() if w.strip()]
#     a=dict(a)
    # _ip1,_ip2,v=scan([str,str,str])
    # ip1=f"{IPv4Address(_ip1):b}-"
    # ip2=f"{IPv4Address(_ip2):b}+"
    # l=[w==e for w,e in zip(ip1,ip2)].index(0)
    # d[_ip1+'/'+str(l)]=v
    # open(home+'/warp.json','w').write(dumps(d,indent=4))

