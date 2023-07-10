import random
def create_string(l):
    return ''.join([random.choice('snmrdfhg')+random.choice('aioue') for w in range(l)])[:l]
def create_list(a,b):
    return [create_string(a) for q in range(b)]
def create_rating(n):
    l=create_list(9,n)
    a={
        q:random.randint(-50,200)
        for q in l
    }
    return a
def change_rating(d):
    return {
        a:0 if s<0 else 100 if s>100 else s
        for a,s in d.items()
    }
a=create_rating(20)
for q,w in a.items():
    print(q,w)
print()
a=change_rating(a)
for q,w in a.items():
    print(q,w)



