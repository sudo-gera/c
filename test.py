from h import *
def put_graph(g):
    _img=[]
    l=256
    for w in range(l*2):
        _img.append([])
        for e in range(l*2):
            _img[-1].append([255,255,255])
    l=len(_img)//2
    lc=l*100//128
    ls=tan(22.5/180*pi)*lc
    vs=[
        [l-lc,l-ls],
        [l-ls,l-lc],
        [l+lc,l-ls],
        [l+ls,l-lc],
        [l-lc,l+ls],
        [l-ls,l+lc],
        [l+lc,l+ls],
        [l+ls,l+lc],
    ]
    vs.sort(key=lambda x:atan2(x[0]-l,x[1]-l))
    for q,w in enumerate(g):
        for e in w:
            for w in range(l//2):
                x=int((vs[q][0]-vs[e][0])*w*2/l+vs[e][0])
                y=int((vs[q][1]-vs[e][1])*w*2/l+vs[e][1])
                for c in range(-l//32,l//32+1):
                    for v in range(-l//32,l//32+1):
                        if x+c in range(l*2) and y+v in range(l*2):
                            _img[x+c][y+v]=[
                                int(abs(((w*4/l)*512+  0)%512-256)*1.5),                                
                                int(abs(((w*4/l)*512+170)%512-256)*1.5),                                
                                int(abs(((w*4/l)*512+340)%512-256)*1.5),                                
                            ]
    for a,s in vs:
        for w in range(l*2):
            for e in range(l*2):
                if (w-a)**2+(e-s)**2<l:
                    _img[w][e]=[
                        int(abs(((atan2(e-s,w-a)+atan2(w-l,e-l))/pi*256+  0)%512-256)*1.5),
                        int(abs(((atan2(e-s,w-a)+atan2(w-l,e-l))/pi*256+170)%512-256)*1.5),
                        int(abs(((atan2(e-s,w-a)+atan2(w-l,e-l))/pi*256+340)%512-256)*1.5),
                    ]
    return _img



gs=[
    [
        [1],
        [2],
        [3],
        [4],
        [7],
        [6],
        [7],
        [0],
    ],

    [
        [1],
        [2],
        [3],
        [4],
        [7],
        [7],
        [7],
        [0],
    ],

    [
        [1],
        [2],
        [3],
        [4],
        [7],
        [4],
        [7],
        [0],
    ],
    [
        [1],
        [2],
        [3],
        [4],
        [7],
        [3],
        [7],
        [0],
    ],
    [
        [1],
        [2],
        [3],
        [4],
        [7],
        [2],
        [7],
        [0],
    ],


    [
        [1],
        [2],
        [3],
        [0],
        [5],
        [6],
        [7],
        [4,0],
    ],

    [
        [1],
        [2],
        [3],
        [4],
        [0],
        [6],
        [7],
        [5,0],
    ],

    [
        [2],
        [2],
        [3],
        [4],
        [5,1],
        [6],
        [7],
        [4],
    ],

    [
        [3],
        [2],
        [3],
        [4],
        [5,1],
        [6],
        [7],
        [4],
    ],

    [
        [4],
        [2],
        [3],
        [4],
        [5,1],
        [6],
        [7],
        [4],
    ],

    [
        [1],
        [2],
        [3],
        [4,1],
        [5],
        [6],
        [7],
        [3],
    ],

    [
        [3],
        [2],
        [3],
        [4,1],
        [5],
        [6],
        [7],
        [3],
    ],

    [
        [4],
        [2],
        [3],
        [4,1],
        [5],
        [6],
        [7],
        [3],
    ],

    [
        [5],
        [2],
        [3],
        [4,1],
        [5],
        [6],
        [7],
        [3],
    ],

]

for q,w in enumerate(gs):
    bmp_write(put_graph(w),f'test441-{q:04}.bmp')
    subprocess.run(['convert',f'test441-{q:04}.bmp',f'test441-{q:04}.png'])






