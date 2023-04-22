import time
import math
task=5
if task==1:
    def fact_rec(n):
        if n:
            return fact_rec(n-1)*n
        else:
            return 1
    def fact(n):
        r=1
        for i in range(1,n+1):
            r*=i
        return r
    t1=time.perf_counter_ns()
    r=fact_rec(500)
    t2=time.perf_counter_ns()
    print(r,t2-t1)
    t1=time.perf_counter_ns()
    r=fact(500)
    t2=time.perf_counter_ns()
    print(r,t2-t1)
if task==2:
    h=float(input('Высота='))
    r=float(input('Радиус='))
    def cylinder():
        print('дай номер команды')
        print('1 площадь боковой пов')
        print('2 площадь всей пов')
        n=int(input())-1
        def circle():
            return math.pi*r**2
        if n:
            return 2*math.pi*r*h+2*circle()
        else:
            return 2*math.pi*r*h
    print(cylinder())
if task ==3:
    f=lambda r:math.pi*r*r
    for i in range(1,10):
        print(f(i))
if task==4:
    s=input()
    if s.isdecimal():
        print('{:50d}'.format(int(s)).replace(' ','.'))
    elif s.count('.')==1 and s[:s.index('.')].isdigit() and s[s.index('.')+1:].isdigit():
        print('{:30f}'.format(float(s)).replace(' ','_'))
    else:
        print(s)
if task==5:
    n=int(input())
    k=int(input())
    def rec_sum(n,k):
        if n==1:
            return k
        return rec_sum(n-1,k)+n*k
    def sum(n,k):
        r=0
        for m in range(1,n+1):
            r+=m*k
        return r
    t1=time.perf_counter_ns()
    r=rec_sum(n,k)
    t2=time.perf_counter_ns()
    print(r,t2-t1)
    t1=time.perf_counter_ns()
    r=sum(n,k)
    t2=time.perf_counter_ns()
    print(r,t2-t1)
