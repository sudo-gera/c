from h import *
a=loads(open('/Users/gera/Downloads/test (1).json').read())
a=[w[0:len('https://www.youtube.com/watch?v=zcVmHs_WzXU')] for w in a]
a=list(set(a))
print(len(a))
# # for w in a:
# #     run(['youtube-dl','-f','bestaudio',w])

# from h import *
# s,p=scan([str,str])
# for q in range(len(s)):
#     if s[q:].startswith(p):
#         print(q)
    


