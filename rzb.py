e=0
for w in range(2,11):
 e+=(1/w)**(1/(w-1))-(1/w)**(w/(w-1))
print(9-e)
exit()
f=[]
for n in range(2,11):
 f+=[1/n**(1/(n-1))]
f=[9-sum(f)]+f
'''
while 1:
 a=[rand() for w in range(10)]
'''
if 1:
 a=f
# s=sum(a)
# print(s)
# a=[w*9/s for w in a]
 v=0
 for w in range(len(a)):
  v+=a[w]**(w+1)
 if 1:
  print(v,a)
'''
def pol(x,n):
 return x-x**n
f=[]
for n in range(2,11):
 a=0
 b=1
 while a-b<-0.00000000000001:
  c=a+(b-a)/3
  d=b-(b-a)/3
  if pol(c,n)>pol(d,n):
   b=d
  if pol(c,n)<pol(d,n):
   a=c
  if pol(c,n)==pol(d,n):
   b=d
   a=c
'''
