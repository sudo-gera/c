from h import *

chdir('../Downloads/Rushia')
a=listdir()
t=getctime(a[0])
s=[]
s+=['%02i'%(t%60)]
t//=60
s+=['%02i'%(t%60)]
t//=60
s+=['%02i:'%(t%24)]
t//=24
print(a[0],s)
