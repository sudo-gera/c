from os import listdir
from os import chdir
from os import system
from os import popen
from os import remove
from os.path import isdir
from os.path import islink
from os.path import isfile
from os.path import realpath
from os.path import exists
from PIL import Image as img
from subprocess import run
from traceback import format_exc
from difflib import ndiff
from functools import reduce
from fractions import Fraction as f
imgopen=img.open
def find():
	return popen('find').read().split('\n')

'''
for q in find():
	if isfile(q) and islink(q):
		a=open(q,'rb').read()
		remove(q)
		open(q,'wb').write(a)

for w in listdir():
	if isdir(w):
		for e in range(1,129):
			import re
			if str(e) in re.findall(r'\d+',open('index.theme').read()):
				if not exists(w+'/'+str(e)):
					run(['mkdir',w+'/'+str(e)])
			else:
				if exists(w+'/'+str(e)):
					run(['rm','-r',w+'/'+str(e)])


'''
sizeofdir=dict()
path=popen('pwd').read()[:-1]
for w in find():
	chdir(path)
	if isdir(w):
		chdir(w)
		a=[[e] for e in listdir() if isfile(e)]
		for e in a:
			try:
				e[0]=imgopen(e[0]).size
			except:
				e.pop()	
				print(format_exc())
		a=sum(a,[])
		if a:
			a.sort()
			s=reduce(lambda a,s:a if a and a[-1]==s else a+[s],a,[])
			a=[[a.count(w),w] for w in s]
			a=max(a)
			a=a[1]
			sizeofdir[w]=a
		else:
			if [e for e in w.split('/') if e][-1].isdecimal():
				sizeofdir[w]=int([e for e in w.split('/') if e][-1])
				sizeofdir[w]=(sizeofdir[w],sizeofdir[w])

'''
dirs=[w for w in find() if isdir(w)]
dirs=[[(a+'/').split('/')[1],a] for a in dirs]
d=dict()
for w in dirs:
	if w[0] not in d:
		d[w[0]]=[w[1]]
	else:
		d[w[0]].append(w[1])
dirs=d
logd=0
lc=0
lds=dict()
for w in find():
	if isdir(w):
		lds[w]=listdir(w)


sldk=sorted(list(dirs.keys()))
converts=[]
def run(d,st):
	global logd,lc,sldk
	for w in dirs[d]:
		for e in dirs[d]:
			if e in sizeofdir:
				le=lds[e]
				lw=lds[w]
				for a in lw:
					if (w+'/'+a) not in lds:
						if a not in le:
							try:
#									print(w+'/'+a,'to',e+'/'+a,'begin                                                  ')
								if st or sizeofdir[w]>=sizeofdir[e]:
									converts.append([w,a,e])
#									m=imgopen(w+'/'+a)
#									m.resize(sizeofdir[e])
#									m.save(e+'/'+a)
								lds[e].append(a)
#									print(w+'/'+a,'to',e+'/'+a,'end                                                    ')
								if 0:
									lc+=1
									sldk=sorted(list(dirs.keys()))
									tolog=f(st)/2+sldk.index(d)/f(len(sldk))/2+dirs[d].index(w)/f(len(sldk))/len(dirs[d])/2+dirs[d].index(e)/f(len(sldk))/len(dirs[d])**2/2+lw.index(a)/f(len(sldk))/len(dirs[d])**3/2+f(lc,100000000000000000000000)
									if tolog>logd:
										logd=tolog
										print(float(logd),logd,end='\r',sep='\t')

				#				return 1
							except:
								print(format_exc())
					if 1:
						lc+=1
						sldk=sorted(list(dirs.keys()))
						tolog=f(st)/2+sldk.index(d)/f(len(sldk))/2+dirs[d].index(w)/f(len(sldk))/len(dirs[d])/2+dirs[d].index(e)/f(len(sldk))/len(dirs[d])**2/2+lw.index(a)/f(len(sldk))/len(dirs[d])**3/2+f(lc,100000000000000000000000)
						if tolog>logd:
							logd=tolog
							print(float(logd),logd,end='\r',sep='\t')
	return 0
for d in sldk:
	while run(d,0):
		pass
for d in sldk:
	while run(d,1):
		pass
'''
from json import *
#open('converts','w').write(dumps(converts))
converts=loads(open('converts').read())
g=0
for w in converts:
	print(g/len(converts),end='\r')
	g+=1
	w,a,e=w
	if not exists(e+'/'+a):
		try:
			m=imgopen(w+'/'+a)
			m.resize(sizeofdir[e])
			m.save(e+'/'+a)
		except:
			print(format_exc())



print('success')