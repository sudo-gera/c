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