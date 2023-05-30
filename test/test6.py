import random
import pprint
def create_string(l):
    return ''.join([random.choice('snmrdfhg')+random.choice('aioue') for w in range(l)])[:l]
def create_dict(l):
    return {
        create_string(9):random.randint(1,9)
        for q in range(l)
    }
def swap(d):
    res={}
    for q,w in d.items():
        res[w]=[]
    for q,w in d.items():
        res[w].append(q)
    return res
def print_dict(d):
    pprint.pprint(d)
d=create_dict(9)
print_dict(d)
d=swap(d)
print_dict(d)
