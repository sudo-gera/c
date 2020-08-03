from fractions import Fraction as f
from sys import argv
q=int(argv[1])
a=[]
for w in range(1,q+1):
 for e in range(w):
  a.append(f(e,w))
a=sorted(list(set(a)))
print(*a)
