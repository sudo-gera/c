HOME=1
from string import *
from re import *
from difflib import *
from textwrap import *
from unicodedata import *
from stringprep import *
from readline import *
from rlcompleter import *
from struct import *
from codecs import *
from datetime import *
from zoneinfo import *
from calendar import *
from collections import *
from collections.abc import *
from heapq import *
from bisect import *
from array import *
from weakref import *
from types import *
from copy import *
from pprint import *
from reprlib import *
from enum import *
from graphlib import *
from numbers import *
from math import *
from cmath import *
from decimal import *
from fractions import *
from random import *
from statistics import *
from itertools import *
from functools import *
from operator import *
from pathlib import *
from os.path import *
from fileinput import *
from stat import *
from filecmp import *
from tempfile import *
from glob import *
from fnmatch import *
from linecache import *
from shutil import *
from pickle import *
from copyreg import *
from shelve import *
from marshal import *
from dbm import *
from sqlite3 import *
from zlib import *
from gzip import *
from bz2 import *
from lzma import *
from zipfile import *
from tarfile import *
from csv import *
from configparser import *
from netrc import *
from plistlib import *
from hashlib import *
from hmac import *
from secrets import *
from os import *
from io import *
from time import *
from argparse import *
from getopt import *
from logging import *
from logging.config import *
from logging.handlers import *
from getpass import *
from curses import *
from curses.textpad import *
from curses.ascii import *
from curses.panel import *
from platform import *
from errno import *
from ctypes import *
from threading import *
from multiprocessing import *
from multiprocessing.shared_memory import *
from concurrent.futures import *
from subprocess import *
from sched import *
from queue import *
from contextvars import *
from _thread import *
from asyncio import *
from socket import *
from ssl import *
from select import *
from selectors import *
from signal import *
from mmap import *
from email import *
from json import *
from mailcap import *
from mailbox import *
from mimetypes import *
from base64 import *
from binascii import *
from quopri import *
from html import *
from html.parser import *
from html.entities import *
from xml.dom import *
from xml.dom.minidom import *
from xml.dom.pulldom import *
from xml.sax import *
from xml.sax.handler import *
from xml.sax.saxutils import *
from xml.sax.xmlreader import *
from xml.parsers.expat import *
from webbrowser import *
from wsgiref import *
from urllib import *
from urllib.request import *
from urllib.response import *
from urllib.parse import *
from urllib.error import *
from urllib.robotparser import *
from http import *
from http.client import *
from ftplib import *
from poplib import *
from imaplib import *
from smtplib import *
from uuid import *
from socketserver import *
from http.server import *
from http.cookies import *
from http.cookiejar import *
from xmlrpc import *
from xmlrpc.client import *
from xmlrpc.server import *
from ipaddress import *
from wave import *
from colorsys import *
from gettext import *
from locale import *
from turtle import *
from cmd import *
from shlex import *
from tkinter import *
from tkinter.colorchooser import *
from tkinter.font import *
from tkinter.messagebox import *
from tkinter.scrolledtext import *
from tkinter.dnd import *
from tkinter.ttk import *
from tkinter.tix import *
from typing import *
from pydoc import *
from doctest import *
from unittest import *
from unittest.mock import *
from unittest.mock import *
from bdb import *
from faulthandler import *
from pdb import *
from timeit import *
from tracemalloc import *
from distutils import *
from ensurepip import *
from venv import *
from zipapp import *
from sys import *
from sysconfig import *
from builtins import *
from __main__ import *
from warnings import *
from dataclasses import *
from contextlib import *
from abc import *
from atexit import *
from traceback import *
from gc import *
from inspect import *
from site import *
from code import *
from codeop import *
from zipimport import *
from pkgutil import *
from modulefinder import *
from runpy import *
from importlib import *
from ast import *
from symtable import *
from token import *
from keyword import *
from tokenize import *
from tabnanny import *
from pyclbr import *
from py_compile import *
from compileall import *
from dis import *
from pickletools import *
from posix import *
from pwd import *
from grp import *
from termios import *
from tty import *
from pty import *
from fcntl import *
from resource import *
from syslog import *
from aifc import *
from asynchat import *
from asyncore import *
from audioop import *
from cgi import *
from cgitb import *
from chunk import *
from crypt import *
from imghdr import *
from nntplib import *
from nis import *
from optparse import *
from pipes import *
from smtpd import *
from sndhdr import *
from sunau import *
from telnetlib import *
from uu import *
from dataclasses import *
from time import *
from copy import *
from os import *
from os.path import *
from sys import *
from json import *
from random import *
from urllib.request import *
from urllib.parse import *
from pprint import *
from math import *
from cmath import *
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
from builtins import *
from re import *
def outputFunction(*a):
	a=a[0]
	s=split(r'\:\d+ in ',a)
	file=s[0]
	a=a[len(file)+1:]
	s=split(r' in ',a)
	line=s[0]
	a=a[len(s[0])+4:]
	if '\n' in a:
		a=a.split('\n',1)
		a='- \n'.join(a)
	s=split(r'- ',a)
	func=s[0]
	a=a[len(func)+2:]
	args=a
	print("\x1b[92mline \x1b[94m"+line+"\x1b[92m file \x1b[94m"+file+"\x1b[92m func \x1b[94m"+func+"\x1b[92m \x1b[0m"+args)
from icecream import ic
ic.configureOutput(includeContext=1)
ic.configureOutput(outputFunction=outputFunction)
ic.configureOutput(prefix='')
from builtins import *
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
# from primes import primes
primes=[2,3,5]
from is_prime import *
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

prime=Prime(prev_prime,next_prime)
fast_prime=Prime(fast_prev_prime,fast_next_prime)
