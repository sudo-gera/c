from random import *
def rand(q=2**64):
	assert q
	return randint(0,q-1)

# n=rand(99)
# print(n)
# for w in range(n):
# 	q=rand(40)
# 	print(q,end=' ')
# print()

a=list(range(4))
shuffle(a)
def t(q):
	return [len([
					e
			for e in range(w)
				if q[e]>q[w]])
		for w in range(len(q))
	]
print(len(a))
print(*t(a))
