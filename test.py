




# from h import *

# def whois(ip:str):
#     a=subprocess.run(['whois',ip],stdout=PIPE)
#     a=a.stdout.read().splitlines()
    



# from subnets import *
# from random import *
# try:
#     d=loads(open(home+'/warp.json','r').read())
# except Exception:
#     d={}
# while 1:
#     print('%.2f'%(sum([2**(32-ip_network(w).prefixlen) for w in d])/2**32))
#     for w in range(256**2):
#         ip=ip_network(rand(256**4))
#         for w in d:
#             if ip.subnet_of(ip_network(w)):
#                break
#         else:
#             ip=str(ip)[:-3]
#             break
#     else:
#         a=exclude('0.0.0.0/0',d.keys())
#         ip=str(choice(list(zip(choice(a).hosts(),range(64))))[0])
#     a=popen('whois '+ip).read()
#     a=[w.split(':') for w in a.splitlines() if w.strip()]
#     a=dict(a)
    # _ip1,_ip2,v=scan([str,str,str])
    # ip1=f"{IPv4Address(_ip1):b}-"
    # ip2=f"{IPv4Address(_ip2):b}+"
    # l=[w==e for w,e in zip(ip1,ip2)].index(0)
    # d[_ip1+'/'+str(l)]=v
    # open(home+'/warp.json','w').write(dumps(d,indent=4))

