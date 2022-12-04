from h import *
# def f(x):
#     return floor(x)+floor(3*x)+floor(4*x)+floor(6*x)+floor(7*x/3)
# s={}
# # st=3*4*6*7*3
# st=10**3
# for w in range(st*150+1):
#     q=w/o/st
#     s[f(q)]=[]
# for w in range(st*150+1):
#     q=w/o/st
#     s[f(q)].append([q.numerator+q.denominator,q])
# for w in s:
#     s[w].sort()
# for w in s:
#     s[w]=s[w][0][1]
# for w in s:
#     print(w,s[w])    
# print(len(s))

p=[]
for x in range(0,256):
    p.append([])
    for y in range(0,256):
        p[-1].append(0)
        p[-1][-1]=[(x+y^x-y)%256]
        




bmp_write(p,'test.bmp')

#         if abs(x**3+y**3+(x+y)**3+48*x*y-8192)<10:
#             print(x,y)
#             s.add(x+y)
# print(s)
