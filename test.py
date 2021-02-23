<<<<<<< HEAD
print(input())
print(input())
=======
<<<<<<< HEAD
from functools import reduce
w=[1,2,3,4,5,6]
w=[reduce(lambda a,s:a[:-1]+[a[-1]+[s]] if a and len(a[-1])<2 else a+[[s]],w,[])]
print(w)
=======
a=open('std','r+')
print(a.read())
.write('123')
a.seek(0)
print(a.read())
>>>>>>> c507d45e2e378d3ee187c1de4acd6306e33fd4c6
>>>>>>> dee5bcfe7daaabb65b9a3db5dfe2ae655669af6e
