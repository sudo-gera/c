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
def is_prime(q):
	if primes[-1]**2<q:
		if q<2:
			return False
		for w in primes:
			if q%w==0:
				return False
			if w*w>q:
				return True
		assert(primes[-1]**2>=q)
	else:
		return bisect_in(primes,q)
from prime_parser import *
