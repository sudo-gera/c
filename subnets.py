from ipaddress import *


to_exclude4=[
# local:
    '0.0.0.0/8',
    '10.0.0.0/8',
    '172.16.0.0/12',
    '192.168.0.0/16',
    '224.0.0.0/3',
# zerotier:
    '35.209.189.184/32',
    '35.209.194.115/32',
    '35.209.9.241/32',
    '35.209.49.222/32',
    '50.7.252.138/32',
    '103.195.103.66/32',
    '192.168.0.201/32',
    '81.5.99.235/32',
    '84.17.54.155/32',
    '104.194.8.134/32',
# # vk:
    # '87.240.128.0/18',
    # '93.186.224.0/20',
    # '95.142.192.0/20',
    # '95.213.0.0/17',
    # '185.32.248.0/22',
]

def exclude(start,exclude)->list[IPv4Network|IPv6Network]:
    result = [ip_network(start)]
    for x in exclude:
        n = ip_network(x)
        new = []
        for y in result:
            if y.overlaps(n):
                if n.subnet_of(y):
                    new.extend(y.address_exclude(n))
            else:
                new.append(y)
        result = new
    return result

if __name__ == '__main__':
    to_exclude4=exclude('0.0.0.0/0',to_exclude4)

    print(', '.join(str(x) for x in sorted(to_exclude4)))