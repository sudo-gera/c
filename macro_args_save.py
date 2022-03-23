d=set()
for r in ['','b','w','d']:
	for e in ['','b','w','d']:
		for w in ['','b','w','d']:
			for q in ['','b','w','d']:
				if q+w+e+r not in d:
					d.add(q+w+e+r)
					print('%macro macro_args_save_'+q+w+e+r+' '+str(len([z for z in [q,w,e,r] if z])))
					f={'d':4,'w':2,'b':1,'':0}
					print('add esp, '+str(16+f[q]+f[w]+f[e]+f[r]))
					for t,y in list(enumerate([q,w,e,r]))[::-1]:
						if y=='b':
							print('push byte  %'+str(t+1))
						if y=='w':
							print('push word  %'+str(t+1))
						if y=='d':
							print('push dword %'+str(t+1))
					print('sub esp, '+str(16))
					print('regload')
					print('%endmacro')
