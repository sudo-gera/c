<<<<<<< HEAD
d=set()
for r in ['b','w','d']:
	for e in ['b','w','d']:
		for w in ['b','w','d']:
			for q in ['b','w','d']:
				if q+w+e+r not in d:
					d.add(q+w+e+r)
					print('%macro macro_args_read_'+q+w+e+r+' '+str(len([w for w in [q,w,e,r] if w])))
					print('regsave')
					for t,y in enumerate([q,w,e,r]):
						if y=='b':
							print('push byte  %'+str(t))
						if y=='w':
							print('push word  %'+str(t))
						if y=='d':
							print('push dword %'+str(t))
					print('regnull')
					for t,y in list(enumerate([q,w,e,r]))[::-1]:
						if y=='b':
							print('pop  %sl'%"abcd"[t])
						if y=='w':
							print('pop  %sx'%"abcd"[t])
						if y=='d':
							print('pop e%sx'%"abcd"[t])

					print('%endmacro')
=======
from h import *
q=0
def aa(a:int=0):
	ic(q,a,2,{'1':2,3:'4'})
aa(3)
ic(4)
ic()
>>>>>>> 7e277cf050509082352e5bb30554e2cdb1d01d9d
