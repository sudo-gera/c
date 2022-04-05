from h import *

a=input()
mc=-1
ms=''
for w in range(len(a)):
	for e in range(w):
		for c in range(1,len(a)):
			if a[w:w+c]==a[e:e+c]:
				if c>mc:
					mc=c
					ms=a[w:w+c]
print(ms)
# print(mc)
