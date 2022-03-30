d=set()
for r in ['','b','w','d']:
	for e in ['','b','w','d']:
		for w in ['','b','w','d']:
			for q in ['','b','w','d']:
				if q+w+e+r not in d:
					d.add(q+w+e+r)
					print('%macro macro_args_save_'+q+w+e+r+' '+str(len([z for z in [q,w,e,r] if z])))
					f={'d':4,'w':2,'b':1,'':0}
					g={'d':4,'w':4,'b':4,'':0}
					print('add esp, '+str(32+g[q]+g[w]+g[e]+g[r]))
					for t,y in list(enumerate([q,w,e,r]))[::-1]:
						if y=='b':
							print('push dword 0')
							print('mov byte [esp], %sl'%'abcd'[t])
							# print('push byte  %sl'%'abcd'[t])
						if y=='w':
							print('push dword 0')
							print('mov word [esp], %sx'%'abcd'[t])
							# print('push word  %sx'%'abcd'[t])
						if y=='d':
							print('push dword 0')
							print('mov dword[esp],e%sx'%'abcd'[t])
							# print('push dword e%sx'%'abcd'[t])
					print('sub esp, '+str(32))
					# print('regload')
					# print('regload')
					print('popad')
					for t,y in list(enumerate([q,w,e,r])):
						if y=='b':
							# print('mov %'+str(t+1)+', byte[esp]')
							# print('add esp,4')
							print('popbw      %'+str(t+1))
							print('add esp,2')
						if y=='w':
							# print('mov %'+str(t+1)+', word[esp]')
							# print('add esp,4')
							print('pop   word %'+str(t+1))
							print('add esp,2')
						if y=='d':
							# print('mov %'+str(t+1)+', dword[esp]')
							# print('add esp,4')
							print('pop  dword %'+str(t+1))
					print('add esp,'+str(16-g[q]-g[w]-g[e]-g[r]))
					print('%endmacro\n')
