from ipaddress import ip_network

start = '0.0.0.0/0'
exclude = ['1.2.3.4','5.6.7.8','9.10.11.12']

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