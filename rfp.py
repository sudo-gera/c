from urllib import request

r=request.Request('/')
r.set_proxy('192.168.44.94','http')
print(request.urlopen(r).read())
