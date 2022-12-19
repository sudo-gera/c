from treap import *


a = treap(range(10**4))

for w in range(10**4):
    s=a[:10**3:treap.no_copy]
    a+=treap.no_copy(s)


