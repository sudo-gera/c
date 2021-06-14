from urllib import request

r=request.Request('http://vk.com/')
# r.set_proxy('127.0.0.1:3128','http')
# r.set_proxy('localhost:8080','http')
r.set_proxy('192.168.44.94:3128','http')
print(request.urlopen(r).read())
