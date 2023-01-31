from h import *
a=loads(open('/Users/gera/Downloads/test (1).json').read())
a=[w[0:len('https://www.youtube.com/watch?v=zcVmHs_WzXU')] for w in a]
a=list(set(a))
for w in a:
    run(['youtube-dl','-f','bestaudio',w])
