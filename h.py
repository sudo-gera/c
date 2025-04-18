from pathlib import Path
HOME=str(Path.home())+'/'
try:
    from dataclasses import *
    import dataclasses
except:
    pass
try:
    from numpy import *
    import numpy
except:
    pass
from asyncio import *
import asyncio
from time import *
import time
from os import *
import os
from os.path import *
import os.path
from sys import *
import sys
from json import *
import json
from io import *
import io
from random import *
import random
from urllib.request import *
import urllib.request
from urllib.parse import *
import urllib.parse
from pprint import *
# import pprint
from math import *
import math
from cmath import *
import cmath
from decimal import *
import decimal
from traceback import *
import traceback
from fractions import *
import fractions
from subprocess import *
import subprocess
from pathlib import *
import pathlib
from functools import *
import functools
from difflib import *
import difflib
from base64 import *
import base64
from itertools import *
import itertools
from timeit import *
import timeit
from bisect import *
import bisect
from builtins import *
import builtins
from re import *
import re
from operator import *
import operator
from inspect import *
import inspect
from threading import *
import threading
from threading import *
import threading
from copy import *
try:
	cache
except:
	cache=lru_cache(maxsize=None)
try:
    from icecream import ic
    def outputFunction(*a):
        import time
        a=a[0]
        s=re.split(r'\:\d+ in ',a)
        file=s[0]
        a=a[len(file)+1:]
        s=re.split(r' in ',a)
        line=s[0]
        a=a[len(s[0])+4:]
        if '\n' in a:
            a=a.split('\n',1)
            a='- \n'.join(a)
        s=re.split(r'- ',a)
        func=s[0]
        a=a[len(func)+2:]
        args=a
        t=time.time()
        t='%.3f'%(t-int(t))
        at=time.asctime().split()
        at[3]+=t[1:]
        at=' '.join(at)
        print("\x1b[92mpid \x1b[94m"+str(os.getpid())+"\x1b[92m time \x1b[94m"+at+"\x1b[92m line \x1b[94m"+line+"\x1b[92m file \x1b[94m"+file+"\x1b[92m:\x1b[94m"+line+"\x1b[92m func \x1b[94m"+func+"\x1b[92m \x1b[0m"+args,file=sys.stderr)
    ic.configureOutput(includeContext=1)
    ic.configureOutput(outputFunction=outputFunction)
    ic.configureOutput(prefix='')
except Exception:
    ic=lambda *a:a[0] if len(a)==1 else [None,a][bool(a)]
from builtins import *
import builtins
home=str(Path.home())+'/'
def rand(q=2**64,e=None):
    if e!=None:
        q,e=e,q
    else:
        e=0
    assert q-e
    return randint(e,q-1)
exec(open(str(Path.home())+'/.pythonrc').read())
def urlread(*a,**s):
    return urlopen(*a,**s).read().decode()
from object import *
# class Object(dict):
#     def __getattr__(s,n):
#         return s[n]
#     def __setattr__(s,n,v):
#         s[n]=v
#     def __delattr__(s,n):
#         del s[n]
false=False
true=True
def bisect_in(a,s):
    return bisect_left(a,s)!=bisect_right(a,s)
# from primes import primes
primes=[2,3,5]
from is_prime import *
import is_prime
from scan import *
def is_prime_root(q):
    if primes[-1]>=q:
        return bisect_in(primes,q)
    for w in primes:
        if q%w==0:
            return False
        if w*w>q:
            return True
    start=primes[-1]
    start=start//6*6-1
    for w in count(start,6):
        if q%w==0:
            return False
        if q%(w+2)==0:
            return False
        if w*w>q:
            return True
@cache
def is_prime(q):
    if q<10**11:
        return is_prime_root(q)
    return is_prime_Miller(q)

# from prime_parser import *
@cache
def next_prime(q):
    if q<2:
        return 2
    q-=(q+1)%2
    q+=2
    while not is_prime(q):
        q+=2
    return q
@cache
def prev_prime(q):
    if q<3:
        return None
    if q==3:
        return 2
    q+=(q+1)%2
    q-=2
    while not is_prime(q):
        q-=2
    return q
def primes_until(w):
    while primes[-1]<w:
        primes.append(next_prime(primes[-1]))

primes_until(10**3)
from fib import *
import fib
# @cache
# def fibonacci(q):
# 	if q<0:
# 		return None
# 	if q==0:
# 		return 0
# 	if q==1:
# 		return 1
# 	return fibonacci(q-1)+fibonacci(q-2)
    # a,s=0,1
    # while q:
    # 	a,s=s,a+s
    # 	q-=1
    # return a

from root import *
import root

def factor(q):
    f=[]
    if q<0:
        q*=-1
        f=[-1]
    if q==0:
        return []
    primes_until(ceil_root(q))
    for w in primes:
        while q%w==0:
            f.append(w)
            q//=w
        if w*w>q:
            break
    if q!=1:
        f.append(q)
    return f

def divizors(q):
    f=[]
    if q<0:
        q=-q
    w=1
    while w*w<q:
        if q%w==0:
            f.append(w)
        w+=1
    l=len(f)
    if w*w==q:
        f.append(w)
    for e in f[:l][::-1]:
        f.append(q//e)
    return f

def from_radix_list(value : list[int], base: int) -> int:
    r=0
    for w in value:
        r*=base
        r+=w
    return r

def to_radix_list(value: int, base: int) -> list[int]:
    z=abs(value)
    x=z
    if bin(base).count('1')==1:
        s=list(bin(z)[2:][::-1])
        s=[int(w) for w in s]
        l=len(bin(base))-3
        while len(s)%l:
            s.append(0)
        r=[]
        s=s[::-1]
        for w in range(0,len(s),l):
            a=0
            for t in range(l):
                a*=2
                a+=s[w+t]
            r.append(a)
        if not r:
            r=[0]
        s=r
    else:
        s=[]
        while z:
            s.append(z%base)
            z//=base
        if not s:
            s=[0]
        s=s[::-1]
    assert x==from_radix_list(s,base)
    if value<0:
        s = [-w for w in s]
    return s

def to_radix(q,e):
    s=to_radix_list(q,e)
    s=''.join(["0123456789abcdefghijklmnopqrstuvwxyz".upper()[w] for w in s])
    return s

def from_radix(q,e):
    if e<37:
        return int(q,e)
    q=[int(w,36) for w in q]
    s=from_radix_list(q,e)
    return s

def primes_count(start=0):
    start-=1
    while 1:
        start=next_prime(start)
        yield start

@cache
def fast_next_prime(q):
    if q<2:
        return 2
    q+=1
    while q%30!=7:
        q+=1
    while 1:
        if pow(2,q-1,q)==1 and fibonacci(q+1,q)==0:
            return q
        q+=6
        if pow(2,q-1,q)==1 and fibonacci(q+1,q)==0:
            return q
        q+=4
        if pow(2,q-1,q)==1 and fibonacci(q+1,q)==0:
            return q
        q+=6
        if pow(2,q-1,q)==1 and fibonacci(q+1,q)==0:
            return q
        q+=14

@cache
def fast_prev_prime(q):
    if q<1024:
        return prev_prime(q)
    q-=1
    while q%30!=7:
        q-=1
    while 1:
        if pow(2,q-1,q)==1 and fibonacci(q+1,q)==0:
            return q
        q-=14
        if pow(2,q-1,q)==1 and fibonacci(q+1,q)==0:
            return q
        q-=6
        if pow(2,q-1,q)==1 and fibonacci(q+1,q)==0:
            return q
        q-=4
        if pow(2,q-1,q)==1 and fibonacci(q+1,q)==0:
            return q
        q-=6

from builtins import *
import builtins

class Prime:
    def __init__(s,p,n):
        s.n=n
        s.p=p
    def __lt__(s,o):
        return s.p(o)
    def __le__(s,o):
        return s.p(o+1)
    def __gt__(s,o):
        return s.n(o)
    def __ge__(s,o):
        return s.n(o-1)
    def __eq__(s,o):
        return is_prime(o)
    def __ne__(s,o):
        return not s==o

prime=Prime(prev_prime,next_prime)
fast_prime=Prime(fast_prev_prime,fast_next_prime)
def euler(q):
    f=set(factor(q))
    for w in f:
        q*=w-1
        q//=w
    return q
def perf():
    global _perf_prev_
    args=('%.9f'%(perf_counter()-_perf_prev_)).replace('0','\x1b[34m0\x1b[0m')
    try:
        g=stack()
        g=g[1][0]
        g=getframeinfo(g)
        line=str(g.lineno)
        file=g.filename
        func=g.function
    except Exception:
        print(format_exc())
        line=''
        file=''
        func=''
    print("\x1b[92mpid \x1b[94m"+getpid()+"\x1b[92m line \x1b[94m"+line+"\x1b[92m file \x1b[94m"+file+"\x1b[92m func \x1b[94m"+func+"\x1b[92m \x1b[0m"+args)
    _perf_prev_=perf_counter()
_perf_prev_=perf_counter()
def append(a,s):
    a.append(s)
def pop(a):
    return a.pop()
@cache
def c(n,k):
    if k in [0,n]:
        return 1
    if 0<k<n:
        try:
            return c(n-1,k-1)+c(n-1,k)
        except:
            pass
        r=1
        for w in range(k):
            r*=n-w
        for w in range(k):
            r//=w+1
        return r
    return 0

def binstr(s):
    if type(s)==str: s=s.encode()
    return '_'.join([('0'*8+bin(w)[2:])[-8:] for w in s])

o=Fraction(1,1)

def bmp_write(a,filename):
    height=len(a);
    width=len(a[0]) if a else 0;
    data=[
        int.from_bytes(b'\x00\x00BM','little'),
        height * width * 4 + 54,
        0, 54, 40,
        width, height,
        0x200001, 0,
        height * width * 4,
        0, 0, 0, 0
    ]
    for q in a:
        for w in q:
            w=[max(min(e,255),0) for e in w]
            data.append(int.from_bytes(bytearray(w),'little'))
    data=b''.join([w.to_bytes(4,'little') for w in data])
    open(filename,'wb').write(data[2:])

def hex_array(a):
    return ''.join(['\\x'+('00'+hex(w)[2:])[-2:] for w in a])




