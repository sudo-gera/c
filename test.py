from h import *
import sys
sys.setrecursionlimit(80)
# def f():
#     q = rand()%3
#     if q == 0:
#         return 'a'
#     if q == 1:
#         return 'b' + f()
#     if q == 2:
#         return 'c' + f() + f()

# def check(s):
#     for q in range(len(s)+1):
#         # print(q)
#         assert s[q:].count('a') >= s[q:].count('c')
#     assert s.count('a') -1 == s.count('c')

def s_():
    q = rand()%3
    if q == 0:
        return ')'
    if q == 1:
        return '(' + s_() + ')'
    if q == 2:
        return s_() + '(' + s_()

def check(s):
    c=0
    for q in '(' + s:
        if q=='(':
           c+=1
        else:
            c-=1
        assert c>=0
    assert c==0 

seed_ = 8859101521918320191
seed_ = rand()
print(seed_)
seed(seed_)

# if 1:
while 1:
    try:
        s = s_()
    except RecursionError:
        pass
    print(s)
    check(s)



