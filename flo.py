import sys
import json
data = open(sys.argv[1],'rb').read()
head = data[:10]
data = data[10:]
def decode_numbes(data:bytes):
    res = []
    buffer = ''
    for q in data:
        q=bin(q+2**256)[-8:][::-1]
        buffer += q[:-1]
        if q[-1]=='0':
            res.append(int(buffer[::-1],2))
            buffer = ''
    return res
def decode_negative_numbers(data:list[int]):
    return [-(q+1)//2 if q%2 else q//2 for q in data]
data = decode_numbes(data)
data = decode_negative_numbers(data)
blocks = []
state = [0, 0, 0, 0]
for q,w in enumerate(data):
    ps = data[q:q+4]+[0,0,0,0]
    if q == 0 or ps[0]>999 and ps[1]>state[1] and ps[2]==8 and ps[3]==state[3]+6:
        state = ps
        blocks.append([])
    blocks[-1].append(w)
block_db={}
for q in blocks:
    block_db[q[0]]=dict(
        arg_count = len(q)
    )
    for w in q:
        print(f'{w:6}',end='')
    print()
open('flo.json','w').write(json.dumps(block_db,indent=4))



