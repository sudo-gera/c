a=input()
s=0
s+=int(a)
a=a[1:]+a[:1]
s+=int(a)
a=a[1:]+a[:1]
s+=int(a)
print(s)
