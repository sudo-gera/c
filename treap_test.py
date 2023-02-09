from __future__ import annotations
from h import *
import functools
import json
import traceback
import typing
import random
import time
import dataclasses
import random
import copy

def treeprint(root: treap.Node,prev_node: list[int|None]|None=None):
    if root is None:
        return
    left = root._left
    right = root._right

    node:list[typing.Any]=[prev_node,0,None]
    if prev_node:
        prev_node[2]=node; #type: ignore

    save=0
    if prev_node and prev_node[1]==2:
        save=prev_node[1]
        prev_node[1]=0
    
    node[1]=2
    treeprint(left,node)
    if save:
        prev_node[1]=save; #type: ignore
    
    d=node
    while d[0]:
        d=d[0]
    
    while d!=node:
        if d[1]==1:
            if d==prev_node:
                print("┗",end='')
            else:
                print("┃",end='')
            
        elif d[1]==2:
            if d==prev_node:
                print("┏",end='')
            else:
                print("┃",end='')
            
        else:
            print(" ",end='')
        
        d=d[2]
    

    if root.rev:
        print("\x1b[34m",end='')
    
    if left==None and right==None:
        print("━",end='')
    elif left==None:
        print("┳",end='');
    elif right==None:
        print("┻",end='');
    else:
        print("╋",end='');
    
    if root.rev:
        print("\x1b[0m",end='')
    
    print("► ",end='')

    print(root.x)

    save=0
    if prev_node and prev_node[1]==1:
        save=prev_node[1];
        prev_node[1]=0;
    
    node[1]=1
    treeprint(right,node)
    if save:
        prev_node[1]=save # type: ignore



def check(q : Node) -> None:
    if q is None:
        return
    check(q._left)
    check(q._right)
    if q._left is not None and q._right is not None:
        assert q.size == q._left.size + 1 + q._right.size
        assert q._right.parent == q
        assert q._left.parent == q
    elif q._right is not None:
        assert q.size == 1 + q._right.size
        assert q._right.parent == q
    elif q._left is not None:
        assert q.size == 1 + q._left.size
        assert q._left.parent == q
    else:
        assert q.size == 1
    if q.parent is not None:
        assert q == q.parent._left or q == q.parent._right



if __name__ == '__main__':
    # random.seed(0)
    from typeguard.importhook import install_import_hook
    install_import_hook('treap')
    from treap import treap
    treap.check[0]=check
    # big_prime=65537
    # sml_prime=257
    # big_prime=4099
    # sml_prime=257
    # big_prime=1031
    # sml_prime=67
    big_prime=17
    sml_prime=5
    # big_prime=5
    # sml_prime=3
    t=treap(range(big_prime))
    assert list(t)==list(range(big_prime))
    ic()
    check(t.root)
    ic()
    for w in range(len(t)):
        t[w]*=sml_prime
        t[w]%=big_prime
    t.sort()
    ic()
    assert list(t)==list(range(big_prime))
    for w in range(big_prime):
        t+=treap.no_copy(t[:sml_prime:treap.no_copy])
    assert list(t)==list(range(big_prime))
    t.reverse()
    ic()
    assert list(t)==list(range(big_prime))[::-1]
    t.reverse()
    assert list(t)==list(range(big_prime))
    for w in range(len(t)):
        z=t[sml_prime-1::treap.no_copy(step=-1)]
        x=t[::treap.no_copy(step=-1)]
        z+=treap.no_copy(x)
        t[::treap.no_copy(step=-1)]=z
    assert list(t)==list(range(big_prime))
    ic()
    assert list(t[::2]) == list(range(0,big_prime,2))
    for w in range(sml_prime):
        z=random.randint(sml_prime,big_prime-sml_prime-1)
        x=z+random.randint(-sml_prime,sml_prime)
        assert list(t[z:x:2])  == list(range(z,x,2))
        assert list(t[z:x:-2]) == list(range(z,x,-2))
        assert list(t[z:x:1])  == list(range(z,x,1))
        assert list(t[z:x:-1]) == list(range(z,x,-1))
    ic()
    t[0]=t
    y=copy.deepcopy(t)
    assert y[0] is y
    y[0]=0
    assert t[0] is t
    t[0] = 0
    assert list(t)==list(range(big_prime))
    ic()
    for w in range(len(t)):
        t[w]=treap([t[w]])
    ic()
    y=copy.deepcopy(t)
    for w in t:
        w[0]*=-1
    for q,w in zip(y,t):
        assert q[0]+w[0]==0

    t=treap(range(64))
    assert list(t*16) == list(range(64))*16

    for q,w in enumerate(t):
        assert q==w

    y=deepcopy(t)
    y+=treap.no_copy(t)
    assert len(t)==0

