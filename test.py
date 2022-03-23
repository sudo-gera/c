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
							print('push byte  %'+str(t+1))
						if y=='w':
							print('push word  %'+str(t+1))
						if y=='d':
							print('push dword %'+str(t+1))
					print('regnull')
					for t,y in list(enumerate([q,w,e,r]))[::-1]:
						if y=='b':
							print('pop  %sl'%"abcd"[t])
						if y=='w':
							print('pop  %sx'%"abcd"[t])
						if y=='d':
							print('pop e%sx'%"abcd"[t])

					print('%endmacro')
