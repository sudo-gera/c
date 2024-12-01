import random
def create_list(n):
    if n<0:
        print('error')
        exit()
    return [
        random.randint(0,9)
        for q in range(n)
    ]
def create_set(l):
    l.sort()
    s=[]
    for q,w in zip(l,l[1:]+[-1]):
        s.append(str(q)+' '*(q!=w))
    return {
        str(q)
        for q in ''.join(s).split()
    }
def print_collection(c):
    print(*c)
l=create_list(9)
print_collection(l)
s=create_set(l)
print_collection(s)
