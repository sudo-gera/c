import random
import pprint
def create_string(l):
    if l<0:
        print('error')
        exit()
    return ''.join([random.choice('snmrdfhg')+random.choice('aioue') for w in range(l)])[:l]
def create_dict(l):
    if l<0:
        print('error')
        exit()
    return {
        create_string(9):random.randint(1,9)
        for q in range(l)
    }
def create_list(a,b):
    return [create_string(a) for q in range(b)]
def get_max(c):
    rl=[]
    for q in c:
        if rl:
            if q>rl[0]:
                rl[0]=q
        else:
            rl.append(q)
    if rl:
        return rl[0]
    else:
        print('error')
def print_dict(d):
    pprint.pprint(d)
def print_list(l):
    pprint.pprint(l)

d=create_dict(9)
print_dict(d)
print(get_max(d))

l=create_list(9,9)
print_list(l)
print(get_max(l))

