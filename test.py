from h import *
q=scan()
a=q
w=32
q//=w
w-=1
while q!=(32-w):
    q//=w
    w-=1
# print(q)
s=[]
for w in range(q):
    d=32-q+w+1
    s.append(255-a%d)
    a//=d
print(s[::-1])