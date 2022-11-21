# q='''
# 12	BITMAPCOREHEADER
# 12	OS21XBITMAPHEADER
# 64	OS22XBITMAPHEADER
# 16	OS22XBITMAPHEADER
# 40	BITMAPINFOHEADER
# 52	BITMAPV2INFOHEADER
# 56	BITMAPV3INFOHEADER
# 108	BITMAPV4HEADER
# 124	BITMAPV5HEADER
# '''
# q=[w.split() for w in q.splitlines()]
# q=[w for w in q if w]
# for w in q:
#     bl='{'
#     br='}'
#     print(f'''    {bl}{w[0]},"{w[1]}",nullptr{br},''')

def con(l,n):
    q=[4, 4, 4, 2, 2, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 4, 4, 4, 4]
    if l==12:
        q[1]=q[2]=2
    if sum(q[:n])<l:
        return q[n]
    return 0

def run(l,n):
    return ((l//13)*(l//13)+l//20+36//l+32//l>n)*2*(2-(n+10*(l==12)+1)//4%2+((n+10*(l==12)+11)%16<2))

for l in [12,64,16,40]:
    for n in range(32):
        if con(l,n)!=run(l,n):
            print(l,n,con(l,n),run(l,n))
