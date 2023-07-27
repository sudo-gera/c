task=7
if task==8:
    a=[0]*106
    a[2]=1
    for q in range(2,105):
        a[q+1]+=a[q]
        a[50]=0
        if q*q<106:
            a[q*q]+=a[q]
            a[50]=0
    print(a[105])
    print(a[8])
    print(a[9])
    print(a[10])
if task == 7:
    g=[21,24,18,30]
    for a in range(32):
        if all([x<a or y<a or y>4*x+81 or x%3==0
            for x in range(1,9)
            for y in range(1,9)
        ]):
            if a in g:
                print(a)
            else:
                print('error:',a)
if task == 6:
    z=5**2023 - 5**1010 + 25**650 - 625
    a=[]
    while z:
        a.append(z%5)
        z//=5
    print(a.count(4))

    # from h import *
    # a=to_radix(5**2023 - 5**1010 + 25**650 - 625,5)
    # assert int(a,5)==5**2023-5**1010+25**650-625
    # print(a.count('4'))
if task == 3:
    f=0
    for a in [0,1]:
        for b in [0,1]:
            for c in [0,1]:
                for d in [0,1]:
                    if ((a==b)==c) and (a or d) and (not a or c):
                        print(a,b,c,d)
                        f+=1
    print(f)
if task == 10:
    def encode(n):
        s=bin(n)[2:]
        s=('0'*8+s)[-8:]
        a=s.count('0')
        b=s.count('1')
        a,b=max(a,b),min(a,b)
        d,f=s[:a],s[a:]
        for q in range(b):
            d=d[1:]+d[:1]
        for q in range(a):
            f=f[-1:]+f[:-1]
        s=d+f
        s=''.join(['0' if q =='1' else '1' for q in s])
        n=int(s,2)
        return n
    print(encode(243))
    # for q in range(0,255):
    #     if encode(q)==243:
    #         print(q)
if task == 5:
    f=0
    def make(a:list):
        global f
        if len(a)==6:
            if all([
                (a[q]&a[q+1]&1)==0
                for q in range(5)
            ]):
                if [1 in a, 3 in a, 5 in a].count(True)<=2:
                    f+=1
        else:
            for q in range(6):
                a.append(q)
                make(a)
                a.pop()
    make([])
    print(f)



