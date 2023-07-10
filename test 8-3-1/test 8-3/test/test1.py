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
def filter_dict(d,s):
    s=count_letters(s)
    return [
        q for q in d if is_subset(count_letters(q),s)
    ]
s='qwweee'
l='qwe qwee qwwweee qwweee qwer'.split()
print(s)
print(*l)
print()
print(*filter_dict(l,s))



