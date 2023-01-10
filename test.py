# # from h import *
# # def test():
# #     a=[0,0,1,2]
# #     s=[]
# #     d=[]
# #     shuffle(a)
# #     for w in a:
# #         f=[]
# #         if len(s)<2:
# #             f.append(s)
# #         if len(d)<3:
# #             f.append(d)
# #         choice(f).append(w)
# #     return d.count(0)==1

# # z=0
# # x=0
# # try:
# #     while 1:
# #         for w in range(1_000_000):
# #             if test():
# #                 z+=1
# #             else:
# #                 x+=1
# #         print(z/(z+x))
# # except KeyboardInterrupt:
# #     print(z/(z+x))


# z=0
# x=0
# from itertools import permutations
# for a in permutations([0,0,1,2]):
#     for q in range(16):
#         s=[]
#         d=[]
#         for w in a:
#             f=[]
#             if len(s)<2:
#                 f.append(s)
#             if len(d)<3:
#                 f.append(d)
#             f[q%2-1].append(w)
#             q//=2
#         if d.count(0)==1:
#             z+=1
#         else:
#             x+=1
# from fractions import Fraction
# o=Fraction(1)
# print(o*z/(z+x))
        

c=0
for n in range(1,840+1):
    a=[
        (n)//3,
        (n)//4,
        (n)//7,
    ]
    s=[
        (n+1)//3,
        (n+1)//4,
        (n+1)//7,
    ]
    if (a!=s) ^ (set(a)!=set(s)):
        print(a,s)
    # c+=set(a)!=set(s)
print(c)

