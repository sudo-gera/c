from copyreg import pickle
from h import *
class a:
    def __init__(s,o=0):
        s.o=o
    # def __reduce__(s):
    #     return (a,(s.o,))

q=a()
w=a()
q.o=w
w.o=q
s=modules.pickle.dumps(q)
