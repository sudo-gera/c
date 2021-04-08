from sys import stdin
task=2
def readint():
	c=stdin.read(1)
	while c not in '1234567890':
		c=stdin.read(1)
	s=''
	while c in '1234567890':
		s+=c
		c=stdin.read(1)
	return int(s)		
if task==1:
	n=int(input())
	from bisect import *
	mg=[]
	me=[]
	for w in range(n):
		q=readint()
		insort(mg,[q,w])
		mg=mg[-8:]
		if q%2==0:
			insort(me,[q,w])
			me=me[-8:]
	a=[[
				w[0]*e[0]
			for e in me
			if abs(w[1]-e[1])>=4]
		for w in me+mg]
	a=sum(a,[])
	if len(a)==0:
		print('-inf')
	else:
		print(max(a))
if task==2:
	n=readint()
	d=readint()
	from bisect import *
	mg=[[-float('inf'),-float('inf')] for w in range(d)]
	me=[[-float('inf'),-float('inf')] for w in range(d)]
	for w in range(n):
		q=readint()
		mg[q%d]=max(mg[q%d],[q,w])
		if q%7==0:
			me[q%d]=max(me[q%d],[q,w])
	from pprint import pprint
	mg=[w for w in mg if w!=[-float('inf'),-float('inf')]]
	me=[w for w in me if w!=[-float('inf'),-float('inf')]]
	pprint([mg,me])
	a=[[
				w[0]*e[0]
			for e in me
			if w[1]!=e[1] and w[0]%d!=e[0]%d
		]
		for w in me+mg
	]
	a=sum(a,[])
	if len(a)==0:
		print('-inf')
	else:
		print(max(a))










