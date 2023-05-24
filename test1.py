from h import *
a=[]
for q in range(-400,401):
    for w in range(-400,401):
        if q*q+w*w==325**2:
            a.append([q,w])
print(len(a))
for q in a:
    print(*q)