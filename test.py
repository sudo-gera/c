# class file_slice:
#     def __init__(self,f,n) -> None:
#         self.f=f
#         self.n=n
#     def read(self,l):
#         r=min(l,self.n)
#         self.n-=r
#         return self.f.read(r)


from h import *
# urlopen('https://example.com/',data=file_slice(modules.io.BytesIO(b'123'*8888),8192))


# proxies = {
#     'http': 'http://localhost:1234',
#     'https': 'http://localhost:1234',
# }
import urllib.request

proxy_support = urllib.request.ProxyHandler({'http' : 'http://localhost:1234', 
                                             'https': 'http://localhost:1234'})
opener = urllib.request.build_opener(proxy_support)
urllib.request.install_opener(opener)

print(urlopen("https://google.com").read())

