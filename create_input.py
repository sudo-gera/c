from random import *
def rand(q=2**64):
	assert q
	return randint(0,q-1)

def run():
	a=[choice('1234567890()-+*/') for w in range(rand(999))]
	a=''.join(a)
	if any([(w[0]+w[1]).isdigit() for w in zip(a,a[1:])]):
		return
	if a.isdigit():
		return
	a=a+max(a.count('(')-a.count(')'),0)*')'
	a=max(0,a.count(')')-a.count('('))*'('+a
	a=a.replace('//','/1/')
	a=a.replace('**','*1*')
	a=a.replace('()','(1)')
	for w in '1234567890':
		a=a.replace(w+'(',w+'*(')
	try:
		eval(a)
	except Exception:
		return
	return a
# a=[run() for w in range(rand(9999999))]
# a=[w for w in a if w]
# for w in a:
# 	print(w)
a=''
while not a:
	a=run()
print(a)
