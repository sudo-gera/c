d=set()
for r in ['b','w','d']:
	for e in ['b','w','d']:
		for w in ['b','w','d']:
			for q in ['b','w','d']:
				if q+w+e+r not in d:
					d.add(q+w+e+r)
					print('%macro macro_args_read_'+q+w+e+r+' '+str(len([z for z in [q,w,e,r] if z])))
					print('sub esp,16')
					print('regsave')
					for t,y in enumerate([q,w,e,r]):
						if y=='b':
							# print('push dword 0')
							# print('mov byte [esp],%'+str(t+1))
							print('push word 0')
							print('pushbw byte %'+str(t+1))
						if y=='w':
							# print('push dword 0')
							# print('mov word [esp],%'+str(t+1))
							print('push word 0')
							print('push   word %'+str(t+1))
						if y=='d':
							# print('push dword 0')
							# print('mov dword[esp],%'+str(t+1))
							print('push  dword %'+str(t+1))
					print('regnull')
					for t,y in list(enumerate([q,w,e,r]))[::-1]:
						# if y=='b':
							# print('pop  %sl'%"abcd"[t])
						# if y=='w':
							# print('pop  %sx'%"abcd"[t])
						# if y=='d':
						print('pop e%sx'%"abcd"[t])

					print('%endmacro\n')
for r in ['','b','w','d']:
	for e in ['','b','w','d']:
		for w in ['','b','w','d']:
			for q in ['','b','w','d']:
				if q+w+e+r not in d:
					d.add(q+w+e+r)
					l=len([z for z in [q,w,e,r] if z])
					print('%macro macro_args_read_'+q+w+e+r+' '+str(l))
					print('macro_args_read_'+q+w+e+r+('d'*(4-l)+''.join([' %1,',' %2,',' %3,',' %4,',][:l])+''.join(([' 0,']*4)[:(4-l)])))
					print('%endmacro\n')
