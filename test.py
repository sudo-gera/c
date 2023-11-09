def char_encode(c):
    b = f'{ord(c):032b}'
    if set(b[:-7])=={'0'}:
        b = f'0{b}'
    elif set(b[:-11])=={'0'}:
        b = f'110{b[-11:-6]}10{b[-6:]}'
    elif set(b[:-16])=={'0'}:
        b = f'1110{b[-16:-12]}10{b[-12:-6]}10{b[-6:]}'
    elif set(b[:-21])=={'0'}:
        b = f'11110{b[-21:-18]}10{b[-18:-12]}10{b[-12:-6]}10{b[-6:]}'
    b = int(b, 2).to_bytes(4, 'big')
    while len(b)>1 and b[0]==0:
        b=b[1:]
    return b


# res = []
# for q in range(256):
#     s = f'{q:08b}'
#     d = (s+'0').index('0')
#     if d == 1:
#         d = None
#     elif d == 0:
#         d = 1
#     elif d > 4:
#         d = None
#     res.append(d)
# del q
# # for qq in range(-100,101):
# #     q=qq/10
# #     for ww in range(-100,101):
# #         w=ww/10
# #         for ee in range(-100,101):
# #             e=ee/10
# for a,d in enumerate(res):
#     a &= a << 1
#     a >>= 5
#     a = 8 + ~a
#     # a = a+1
#     import math
#     s = 13//(a+3)
#     if d is not None:
#         # print(f'{a = } {d = } {s = }')
#         assert d == s
# # else:
# #     print(q,w,e)

# for q in range(2**16):
#     b = b'\0\0\0\0'.join([w.to_bytes(4) for w in range(2**16)])
#     b.decode(errors='ignore')

for q in range(2**32):
    try:
        chr(q)
    except Exception:
        break
    b = char_encode(chr(q))

# l = 2**32
# for q in range(l):
#     if q%100000 == 0:
#         print(q/l)
#     b = q.to_bytes(4, 'little')
#     try:
#         s = b.decode()
#     except Exception:
#         continue
    # b = s[0].encode()
    d = len(b)
    a = b[0]
    s = 13//(10-(a&a*2)//32)
    assert s == d


# # for q in range(100):
# #     for w in range(100):
# #         for e in range(100):


#             # if all([True if t == None else
#             #             (q//(r+1)-w)//e
#             #         for r,t in enumerate(res)]):
#             #     print(q,w,e)


# def char_decode(c):
    

# for q in range(2**32):
#     try:
#         chr(q)
#     except Exception:
#         break
#     ceq = char_encode(chr(q))
#     try:
#         ce = chr(q).encode()
#     except Exception:
#         continue
#     assert ceq == ce

# print(char_encode('\ud800'))