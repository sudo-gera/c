# data={}
# def put(v):
#     from random import randint
#     k=''
#     while not k or k in data:
#         k=''.join(
#             [
#                 chr(
#                     randint(32,126)
#                 ) for w in range(
#                     randint(128,1024)
#                 )
#             ]
#         )
#     data[k]=v
#     return k

# def get(k):
#     return data[k]

max_len=8
assert max_len%2==0
class node:
    def __init__(s):
        s.data=[]
        s.next=None
    def insert(s,k):
        if s.next==None:
            if k not s.data:
                s.data.append(k)
                s.data.sort()
        else:
            w=0
            while not(w>=len(s.data) or s.data[w]>k):
                w+=1
            s.next[w].insert(w)
            if len(s.next[w].data)>max_len:
                assert len(s.next[w].data)==1+max_len
                q=s.next[w]
                a=node()
                a.data=q.data[:max_len//2]
                a.next=q.next[:max_len//2+1]
                d=q.data[max_len//2]
                q.data=q.data[max_len//2+1:]
                q.next=q.next[max_len//2+1:]
                s.next[w:w+1]=[a,q]
                s.data[w:w]=[d]
    