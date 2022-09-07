from h import *
# @cache
def f(b:int,n:int):
    if b.bit_count()==3:
        return 1
    c=0
    for w in range(n):
        if b&(1<<w):
            c+=f(b^(1<<w),n)
    return c

