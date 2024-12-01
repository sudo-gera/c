import random
def create_string(l):
    return ''.join([random.choice('snmrdfhg')+random.choice('aioue') for w in range(l)])[:l]
def create_list(a,b):
    return [create_string(a) for q in range(b)]
def count_letters(s):
    d={}
    for q in s:
        d[q]=0
    for q in s:
        d[q]+=1
    return d
def is_subset(a,s):
    return all([
        q in s and s[q]>=w for q,w in a.items()
    ])
def find_groups(d):
    d=[
        [frozenset(count_letters(q).items()),q]
        for q in d
    ]
    a={}
    for q,w in d:
        a[q]=[]
    for q,w in d:
        a[q].append(w)
    return list(a.values())

l='qw wq qw qwe qew weq qwee qeew'.split()
for q in find_groups(l):
    print(*q)
