HOME=1
from icecream import ic
ic.configureOutput(includeContext=1)
from time import *
__o=open
from os import *
open=__o
from sys import *
from json import *
from random import *
from urllib.request import *
from pprint import *
from math import *
from decimal import *
from traceback import *
from fractions import *
from subprocess import *
from pathlib import *
from functools import *
from difflib import *
from base64 import *
from itertools import *
from timeit import *
from bisect import *
home=str(Path.home())+'/'
def rand(q=2**64):
	return randint(0,q-1)
exec(open(str(Path.home())+'/.pythonrc').read())
def urlread(*a,**s):
	return urlopen(*a,**s).read().decode()
class Object(dict):
	def __getattr__(s,n):
		return s[n]
	def __setattr__(s,n,v):
		s[n]=v
	def __delattr__(s,n):
		del s[n]
false=False
true=True
def bisect_in(a,s):
	return bisect_left(a,s)!=bisect_right(a,s)
from primes import primes
@cache
def is_prime(q):
	if primes[-1]>=q:
		return bisect_in(primes,q)
	# primes_until(ceil_root(q))
	if primes[-1]**2>=q:
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

@cache
def fibonacci(q):
	if q<0:
		return None
	a,s=0,1
	while q:
		a,s=s,a+s
		q-=1
	return a
from root import *

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
def to_radix(_q,_e):
	q,e=_q,_e
	z=abs(q)
	s=''
	while z:
		s+=str("0123456789abcdefghijklmnopqrstuvwxyz".upper()[z%e])
		z//=e
	if q<0:
		s+='-'
	if not s:
		s='0'
	s=s[::-1]
	assert int(s,e)==q
	return s
