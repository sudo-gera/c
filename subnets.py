from ipaddress import ip_network

start = '0.0.0.0/0'
exclude = [
    '35.209.189.184/32', # zerotier
    '35.209.194.115/32', # zerotier
    '35.209.9.241/32', # zerotier
    '35.209.49.222/32', # zerotier
    '50.7.252.138/32', # zerotier
    '103.195.103.66/32', # zerotier
    '192.168.0.201/32', # zerotier
    '81.5.99.235/32', # zerotier
    '84.17.54.155/32', # zerotier
    '104.194.8.134/32', # zerotier
]

result = [ip_network(start)]
for x in exclude:
    n = ip_network(x)
    new = []
    for y in result:
        if y.overlaps(n):
            new.extend(y.address_exclude(n))
        else:
            new.append(y)
    result = new

print(','.join(str(x) for x in sorted(result)))