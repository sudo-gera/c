from icecream import ic
ic.configureOutput(includeContext=1)
from time import *
__o=open
from os import *
open=__o
from sys import *
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
exec(open(str(Path.home())+'/.pythonrc').read())
class Object(dict):
	def __getattr__(s,n):
		return s[n]
	def __setattr__(s,n,v):
		s[n]=v
	def __delattr__(s,n):
		del s[n]
