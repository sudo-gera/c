def treeprint(root,l=None):
    #━┃┏┓┗┛┣┫┳┻╋► 
    if root==None:
        return
    if l==None:
        l=[]
    l.append(0)
    save=0
    if len(l)>1 and l[-2]==1:
        save=l[-2]
        l[-2]=0
    l[-1]=1
    treeprint(root.next[0],l)
    if save:
        l[-2]=save
    for q in range(len(root.data)):
        for d in range(len(l)-1):
            if l[d]==3:
                if d==len(l)-2:
                    if q==len(root.data)-1:
                        print("┗",end='')
                    else:
                        print("┣",end='')
                else:
                    print("┃",end='')
            elif l[d]==2:
                if d==len(l)-2:
                    print("┣",end='')
                else:
                    print("┃",end='')
            elif l[d]==1:
                if d==len(l)-2:
                    if q==0:
                        print("┏",end='')
                    else:
                        print("┣",end='')
                else:
                    print("┃",end='')
            else:
                print(" ",end='')

        if root.next[q]==None and q==0 and root.next[q+1]==None and q==len(root.data)-1:
            print("━",end='')
        elif root.next[q]==None and q==0:
            print("┳",end='')
        elif root.next[q+1]==None and q==len(root.data)-1:
            print("┻",end='')
        else:
            print("╋",end='')
        print("► ",end='')
        print(root.mem,root.data[q])

        save=0
        if len(l)>1 and q==len(root.data)-1 and l[-2]==3:
            save=l[-2]
            l[-2]=0
        l[-1]=2+(q==len(root.data)-1)
        treeprint(root.next[q+1],l)
        if save:
            l[-2]=save
    l.pop()
            

def treeprint_(root,prev_node=0):
    if root in [0,None]:
        return
    treeprint_(root.next[0],prev_node+1)
    for w in range(len(root.data)):
        print(prev_node*'>',root.data[w])
        treeprint_(root.next[w+1],prev_node+1)
