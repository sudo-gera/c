q='''
|120 1000|120 1000|59 1000|60 97|85 1000|150 1000|68 97|162 13 1|120 1|120 1000|120 1000|59 1000|60 97|85 1000|150 1000|68 97|162 14 1|120 1|120 1000|120 1000|59 1000|60 97|85 1000|150 1000|68 97|162 15 1|120 1|120 1000|120 1000|59 1000|60 97|85 1000|150 1000|68 97|162 16 1|120 1|120 1000|120 1000|59 1000|60 97|85 1000|150 1000|68 97|162 17 1|120 1|120 1000|120 1000|59 1000|60 97|85 1000|150 1000|68 97|162 18 1|120 1|120 1000|120 1000|59 1000|60 97|85 1000|150 1000|68 97|162 19 1|120 1|120 1000|120 1000|59 1000|60 97|85 1000|150 1000|68 97|162 20 1|120 1|120 1000|120 1000|59 1000|60 97|85 1000|150 1000|68 97|162 21 1|120 1|120 1000|120 1000|59 1000|60 97|85 1000|150 1000|68 97|162 22 1|120 1|120 1000|120 1000|59 1000|60 97|85 1000|150 1000|68 97|162 23 1|120 1|120 1000|120 1000|59 1000|60 97|85 1000|150 1000|68 97|162 24 1|120 1|120 1000|120 1000|59 1000|60 97|85 1000|150 1000|68 97|162 25 1|120 1|120 1000|120 1000|59 1000|60 97|85 1000|150 1000|68 97
'''
for w in 'term ***'.split():
	if w in q:
		q=q.split(w)[0]
from icecream import ic
from h import *
q=q.strip()
q=q.split('|')[1:]
a=open('string.h').read().splitlines()
q=[w.split() for w in q]
q=[[int(w[0])]+[w[1:]] for w in q]
q=[[a[w[0]-1].strip()]+w for w in q]
q=[[int(w[0][1])]+w for w in q]
q=[[w[1].split(')')[0].split('(',1)[-1]]+w for w in q]
offset=int([w[:-1] if w.endswith(';') else w for w in ([w.split('=')[-1].strip() for w in a if 'int offset' in w and '//' not in w])][0])
offstep=int([w[:-1] if w.endswith(';') else w for w in ([w.split('=')[-1].strip() for w in a if 'int offstep' in w and '//' not in w])][0])
q=[[offset+z*offstep]+w for z,w in enumerate(q)]
q=[[{
	'line':w[-2],
	'ce':w[-6]
		}]+w for w in q]
for w in q:
	if w[-4]==1:
		try:
			w[0]['this']=w[-1][0]
		except:
			pass
		# w[0]['bnid']=w[-1][1]
		try:
			w[0][w[-5]]=w[-1][-1]
		except:
			pass
	if w[-4]==2:
		pass
		try:
			w[0][w[-5]]=w[-1][0]
		except:
			pass
	if w[-4]==3:
		try:
			w[0]['this']=w[-1][0]
		except:
			pass
		# w[0]['bnid']=w[-1][1]
	if w[-4]==4:
		pass
q=[w[0] for w in q]
for w in q:
	f=w['line']-1
	while a[f].startswith('\t\t'):
		f-=1
	w['func']=a[f].strip()
	if w['func'][-1]=='{':
		w['func']=w['func'][:-1]
a=[w['func'] for w in q]
a=[w[:w.index('(')].split()[-1] for w in a]
a=[w[w.index('&')+1:] if '&' in w else w for w in a]
q=[w|{'func_name':e} for w,e in zip(q,a)]
a=[w['func'] for w in q]
a=[w[w.index('(')+1:] for w in a]
a=[w[:-len('const')] if w.endswith('const') else w for w in a]
a=[w[:-len(')')] if w.endswith(')') else w for w in a]
a=[w.split(',') for w in a]
a=[[e[:e.index('=')] if '=' in e else e for e in w] for w in a]
a=[[ [e[len(e)-r:] for r in range(len(e)) if e[len(e)-r:].isidentifier()][-1]   for e in w if e] for w in a]
q=[w|{'func_args':e} for w,e in zip(q,a)]
a=[{}]
c=0
args=None
lf=''
for w in q:
	if w['func']!=lf:
		args={}
	lf=w['func']
	for e in w['func_args']:
		if e not in args:
			args[e]=None
		if e in w:
			args[e]=w[e]
	c=len([e for e in args if args[e]==None])
	w=dict(w)
	w.update(args)
	a.pop()
	a.append(w)
	if c==0:
		a.append({})
		args={}

q=a[:-1]


for w in q:
	a='ce line func bnid this orig'.split()
	for e in a+[e for e in w if e not in a]:
		if e=='func' and e in w and 'operator' in w[e]:
			w[e]=w[e].replace('operator','\x1b[93moperator\x1b[0m')
		if e in w:
			print('\x1b[94m',e,'\x1b[0m: ',w[e],sep='',end='\t')
		else:
			pass
			# print('    ','  ','    ',sep='',end='\t')			
	print()
