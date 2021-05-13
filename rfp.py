from urllib import request

r=request.Request('http://87.240.190.67/')
# r.set_proxy('127.0.0.1:8080','http')
# r.set_proxy('localhost:8080','http')
r.set_proxy('192.168.44.94:8765','http')
print(request.urlopen(r).read())
