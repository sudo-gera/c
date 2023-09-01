cubes = [2,5,3,11,4,7,8,1]

n=len(cubes)
s=[0, cubes[0]]

while len(s)<=n:
    s.append(max(
        s[-1],
        s[-2] + cubes[len(s)-1]
    ))
print(s[-1])


