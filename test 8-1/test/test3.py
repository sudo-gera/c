import random
def create_string(l):
    return ''.join([random.choice('snmrdfhg')+random.choice('aioue') for w in range(l)])[:l]
def create_list(a,b):
    return [create_string(a) for q in range(b)]
def get_vovels(l):
    if type(l)==str:
        return ''.join([w for w in l if w.lower() in 'aioueyуеыаоэяиюё'])
    else:
        return type(l)([get_vovels(q) for q in l])

a='qwerty asdfg poiu'.split()
print(*a)
print()
a=get_vovels(a)
print(*a)

