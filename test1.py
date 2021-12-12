a=open('stdin.txt').read().splitlines()
a=[w.rstrip() for w in a]
open('stdin.txt','w').write('\n'.join(a))
