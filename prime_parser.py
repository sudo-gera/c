from h import *
def hide():
	def parse(a):
		s=[]
		d=a
		while a:
			try:
				s.append(d.decode())
				a=a[len(d)+1:]
				d=a
			except:
				d=d[:-1]
		a=''.join(s)
		a=a.split('</table>')[:-1]
		a=[w.split('<table',1)[1:] for w in a]
		a=[(w+[''])[0] for w in a]
		a.sort(key=lambda w:w.count('<td>'))
		a=a[-1]
		a=a[a.index('>')+1:]
		a=a.replace('>','<')
		a=a.split('<')
		a=[int(e) for e in a if e.isnumeric()]
		return a

	def find_primes_right(q):
		a=urlopen('http://compoasso.free.fr/primelistweb/page/prime/liste_online_en.php',
			data=f'primePageInput=600&numberInput={q}'.encode()).read()
		return parse(a)

	def find_primes_left(q):
		a=urlopen('http://compoasso.free.fr/primelistweb/page/prime/liste_online_en.php',
			data=f'primePageInput=600&numberInput={q}&previousButton=previous+page&firstPrimeHidden={q}'.encode()).read()
		return parse(a)

	try:
		primes_db=loads(open(home+'.primes_db').read())
	except:
		open(home+'.primes_db','w').write(dumps([None]))
		primes_db=loads(open(home+'.primes_db').read())

	def load(q,f=None):
		if f==None:
			f=lambda f:find_primes_left(q)+find_primes_right(q)
		nonlocal primes_db
		a=f(q)
		a=sorted(list(set(a)))
		d=[]
		for w in primes_db:
			if w != None and w>=a[0]:
				break
			d.append(w)
		if not (len(d)<len(primes_db) and primes_db[len(d)]==a[0]) and (len(d)==0 or d[-1]!=None):
			d.append(None)
		d+=a

		e=[]
		for w in primes_db[::-1]:
			if w != None and w<=a[-1]:
				break
			e.append(w)
		if not (len(e)<len(primes_db) and primes_db[len(primes_db)-len(e)-1]==a[-1]) and (len(e)==0 or e[-1]!=None):
			e.append(None)
		d+=e[::-1]
		primes_db=d
		open(home+'.primes_db','w').write(dumps(primes_db))

	def get_primes(q):
		q=int(q)
		if q<2:
			return [None,2]
		if q>1000000016531:
			return [1000000016531,None]
		if len(primes_db)<3:
			load(q)
		b=0
		while primes_db[b]==None:
			b+=1
		e=len(primes_db)-1
		while primes_db[e]==None:
			e-=1
		if q<primes_db[b]:
			load(q)
		if q>primes_db[e]:
			load(q)
		while e-b>3:
			c=(e+b)//2
			d=primes_db[c]
			while d==None:
				c+=1
				d=primes_db[c]
			if d<q:
				b=c
			if d>q:
				e=c
			if d==q:
				b=d=c
		while primes_db[b]==None or primes_db[b]<q:
			b+=1
		if b>0 and primes_db[b-1]==None:
			load(q)
			return get_primes(q)
		else:
			b=primes_db[b]
		while primes_db[e]==None or primes_db[e]>q:
			e-=1
		if e<len(primes_db)-1 and primes_db[e+1]==None:
			load(q)
			return get_primes(q)
		else:
			e=primes_db[e]
		return [e,b]

	def prev_prime(q):
		return get_primes(q-1)[0]

	def next_prime(q):
		return get_primes(q+1)[1]

	return next_prime,prev_prime
next_prime,prev_prime=hide()
del(hide)
