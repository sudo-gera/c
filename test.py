from threading import Thread
# from multiprocessing import Process as Thread
from functools import *
from time import *

def setintervalrunner(t,f):
	while 1:
		f()
		sleep(t)


setintervalrunners=[]

def setintervalwrapper(t,f):
	a=Thread(target=partial(setintervalrunner,t,f))
	a.start()
	setintervalrunners.append(a)
	return f

def setinterval(t):
	return partial(setintervalwrapper,t)

a=0

@setinterval(1)
def q1():
	global a
	print(1,a)
	a+=1

@setinterval(2)
def q2():
	global a
	print(2,a)
	a+=1

sleep(1)
