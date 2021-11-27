q='''
|713 -463290803559815096943/460502054458890625000|714 1|605 0|605 0|677 0|678 -29650611427828166204352/29472131485369|670 0 -29650611427828166204352/29472131485369|708 0|709 0|677 -64750272873355693|678 65142393306938481150961344|670 -64750272873355693 65142393306938481150961344|656 -29650611427828166204352/29472131485369 -29472131485369/29650611427828166204352|605 1|708 1|709 1|605 402365964|605 25|649 402365964|650 25|641 402365964 25|605 2147483647|605 1000000009|605 1000000007|656 1000000007 1000000009|656 1000000016000000063 2147483647|677 2147483681359738487291469761|678 402365939|670 2147483681359738487291469761 402365939|733 2147483681359738487291469761/402365939 10|684 402365939|609 1|609 -402365939|677 -402365939|678 1|670 -402365939 1|677 -402365939|678 2147483681359738487291469761|670 -402365939 2147483681359738487291469761|733 -402365939/2147483681359738487291469761 25terminate called after throwing an instance of 'std::runtime_error'
'''
for w in 'term ***'.split():
	if w in q:
		q=q.split(w)[0]
from icecream import ic
q=q.strip()
q=q.split('|')[1:]
a=open('biginteger.h').read().splitlines()
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
a=[[e[e.index('&')+1:] if '&' in e else e for e in w if e] for w in a]
a=[[e[:e.index('=')] if '=' in e else e for e in w] for w in a]
q=[w|{'func_args':e} for w,e in zip(q,a)]
a=[]
c=0
args={}
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
	if c==0:
		w=dict(w)
		w.update(args)
		a.append(w)
		args={}
q=a


for w in q:
	a='ce line func bnid this orig q w e g'.split()
	for e in a+[e for e in w if e not in a]:
		if e=='func' and e in w and 'operator' in w[e]:
			w[e]=w[e].replace('operator','\x1b[93moperator\x1b[0m')
		if e in w:
			print('\x1b[94m',e,'\x1b[0m: ',w[e],sep='',end='\t')
		else:
			pass
			# print('    ','  ','    ',sep='',end='\t')			
	print()
