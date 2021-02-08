from sys import stdin
q=bytearray(stdin.buffer.readline()[:-1])
a=bytearray(stdin.buffer.readline()[:-1])
c=1
for w in range(len(q)):
	if q[w:w+len(a)]==a:
		print(w+1,end=' ')
		c=0
if c:
	print(0)
else:
	print()