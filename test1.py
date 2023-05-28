def create_list(a,n):
    import random
    return [random.randint(-a,a) for w in range(n)]
def write_list(l):
    if any([type(q)==list for q in l]):
        for q in l:
            if type(q)==list:
                print(*q,sep='\t')
            else:
                print(q)
    else:
        print(*l,sep='\t')
def task1(a,n):
    l=create_list(a,n)
    write_list(l)
    print('yes' if all([q <= w for q,w in zip(l,l[1:])]) else 'no')
n=int(input())
a=int(input())
if n<0 or a<0:
    print('wrong input')
else:
    task1()
