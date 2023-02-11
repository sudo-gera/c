# from h import *
# a=loads(open('/Users/gera/Downloads/test (1).json').read())
# a=[w[0:len('https://www.youtube.com/watch?v=zcVmHs_WzXU')] for w in a]
# a=list(set(a))
# print(len(a))
# # for w in a:
# #     run(['youtube-dl','-f','bestaudio',w])

from h import *
s,n=scan([str,int])
p=scan([str]*n)

for q in range(len(s)):
    for w in p:
        if s[q:].startswith(w):
            print(q,w)
    


