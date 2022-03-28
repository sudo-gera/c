from h import *

# chdir('../Downloads/Rushia')
a=listdir()
a=[w for w in a if w[0]!='.']
a=[[stat(w).st_birthtime,w] for w in a]
a.sort()
a=[w[1] for w in a]
for q,w in enumerate(a):
	rename(w,('%03i'%q)+w)
