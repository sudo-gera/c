<<<<<<< HEAD
# {10, 47, 48, 49, 50, 51,             55,         61, 67, 68, 72, 76, 80, 84, 88, 98, 102, 103, 106, 110, 114, 118,           121, 122}
# [43, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57,         68, 72, 76, 80, 84, 88, 98, 102,      106, 110, 114, 118, 119, 120, 121, 122]
# a=open('test.txt','rb')
# s=set()
# s=set(a.read())
# # for c in a.read():
# #     s.add(c)
# print(s)

# for w in range(10):
#     print(f'    | sed "s/{w}/100{w}/g" \\')

# from base64 import b64decode, b64encode


# def binstr(s):
#     if type(s)==str: s=s.encode()
#     return '_'.join([('0'*8+bin(w)[2:])[-8:] for w in s])


# l=[]
# # for w in range(256):
# for w in [43, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57,         68, 72, 76, 80, 84, 88, 98, 102,      106, 110, 114, 118, 119, 120, 121, 122]:
#     l+=b64encode(bytes([255,w,255]))
# l=sorted(list(set(l)))
# print(l)




# exit()
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

count=6

from copy import copy
from itertools import permutations

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

class graph:
    def __init__(s,l):
        s.l=l
    def __eq__(s,o):
        # return False
        q,a=s.l,o.l
        if sorted([len(w) for w in q])!=sorted([len(w) for w in a]):
            return False
        q=[
            [
                int(e in q[w])
            for e in range(5)]
        for w in range(5)]
        a=[
            [
                int(e in a[w])
            for e in range(5)]
        for w in range(5)]

        s=[w[:] for w in a]
        for w in permutations(range(5)):
            a=[
                [
                    s[w[e]][w[r]]
                for r in range(5)]
            for e in range(5)]
            if q==a:
                return True



    def __ne__(s,o):
        return not (s==o)
    def __hash__(self) -> int:
        return hash(tuple([tuple(w) for w in self.l]))



z=0
q=0
c=0
gs=[]
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
    if all([len(w)!=1 for w in g]) and (count==-1 or sum([len(w) for w in g])==count*2):
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
            gs.append(graph(h))


def cl(g):
    c=0
    for w in range(5):
        for e in range(5):
            if w!=e:
                if e not in g.l[w]:
                    if abs(w-e) in [1,4]:
                        c-=1
                    else:
                        c+=20
    return c

gs.sort(key=cl,reverse=0)

hs=[]
for w in gs:
    if w not in hs:
        hs.append(w)

gd={}
for w in hs:
    gd[w]=gs.count(w)

gd=[[q.l,w] for q,w in gd.items()]

for h,n in gd:
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
            a=coord[q]
            d=coord[e]
            for r in range(1000):
                s=(d-a)*0.001*r+a
                if e in w:
                    term[round(s.x)][round(s.y)]='\x1b[31m#\x1b[0m'
                else:
                    term[round(s.x)][round(s.y)]='\x1b[34m$\x1b[0m'
    print(f'{n}x')
    for w in term[::2]:
        for e in w[::]:
            print(e,end='')
        print()
print(len(gs))




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

=======
for q in 'qwertyuiopasdfghjklzxcvbnm'.upper():
    w=r'''                            {
                                "conditions": [
                                    {
                                        "type": "variable_unless",
                                        "name": "multitouch_extension_finger_count_total",
                                        "value": 0
                                    },
                                    {
                                        "input_sources": [
                                            {
                                                "language": "ru"
                                            }
                                        ],
                                        "type": "input_source_if"
                                    }
                                ],
                                "from": {
                                    "key_code": "'''+q.lower()+r'''",
                                    "modifiers": {
                                        "mandatory": [
                                            "right_shift"
                                        ],
                                        "optional": [
                                            "any"
                                        ]
                                    }
                                },
                                "to": [
                                    {
                                        "shell_command":"/opt/homebrew/opt/python@3.10/bin/python3 -c \"__import__('pynput.keyboard').keyboard.Controller().press('''+"'"+q+"'"+r''')\""
                                    }
                                ],
                                "type": "basic"
                            },'''
    print(w)
>>>>>>> 898f21198f47cf9f850bc53dc5a1391e009b7a88
