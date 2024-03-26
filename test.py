import csv
from pprint import pprint
from dataclasses import dataclass
with open('/Users/gera/Downloads/whois-db-download-info-sample.csv') as file:
    data = file.read()
whois = csv.DictReader(data.splitlines(keepends=True), dialect=csv.Sniffer().sniff(data))
whois = [*whois]
good_keys = {key for key in whois[0].keys() if all([v[key]!='' for v in whois])}

# good_keys -= {'status'}

# pprint(dict([(key, max([len(v[key]) for v in whois])) for key in good_keys]))
# exit()


# a=set()
for v in whois:
    for k in good_keys:
        if 'postal' in k.lower():
            import re
            print(v[k])
            if not re.match(r'[0-9]+(-[0-9]+)?', v[k]):
                import time
                assert False
#     a.add(v['domainName'])
# assert len(a) == len(whois)

# for k in good_keys:
#     if any([v[k] == '' for v in whois]):
#         print(k)

# for k in good_keys:
#     if k.endswith('Date'):
#         a=[v[k] for v in whois]
#         print(k, min(a))
#         print(k, max(a))

# st = [int(v[k]) for v in whois for k in good_keys if k.endswith('postalCode')]
# print(st)
# f=set()
# for w in st:
#     assert len(w.split('|')) <= 5
#     for e in w.split('|'):
#         n=e.split(' ',1)[0]
#         assert e == f'{n} https://icann.org/epp#{n}'
#         f.add(n)
# pprint(f)

exit()


def check_pk(pks, keys):
    return all([
        not
        all([v1[key]==v2[key] for key in pks])
        or
        all([v1[key]==v2[key] for key in keys])
        for v1 in whois[:4]
        for v2 in whois[:4]
        ])

# def k1_implies_k2(k1, k2):
#     return all([
#         not (v1[k1]==v2[k1]) or (v1[k2]==v2[k2])
#         for v1 in whois[:4]
#         for v2 in whois[:4]
#         ])

# print(keys_are_equal('registrarName', 'whoisServer'))

unique_keys = {k for k in good_keys if all([
    v1[k] != v2[k]
    for q,v1 in enumerate(whois)
    for v2 in whois[:q]
])}

# def check_table(table, get_pk = lambda t:t[:1]):
#     for key in table:
#         for pk in get_pk(table):
#             assert k1_implies_k2(pk, key)

# domains = [
#     # 'domainName',  # primary
#     # 'contactEmail',
#     # 'administrativeContact_email',
#     # # foreigns...
# ]

# check_pk(domains[:], domains)


@dataclass
class City:
    city: str
    country: str
    state: str

@dataclass
class codes:
    postalCode: str
    city: City



cities = [
    'city', # primary
    'country',
    'state',
]

# check_pk(cities[:1], cities)

codes = [
    'postalCode', #primary

    'city', # -> cities
    'country',
    'state',
]

# check_pk(codes[:1], codes)

locations = [
    'street1', #primary

    'postalCode', # primary, -> codes
    'city',
    'country',
    'state',
]

# check_pk(locations[:2], locations)

organizations = [
    'email', # primary
    'telephone',
    'name',
]

# check_pk(organizations[:1], organizations)

registrants = [
    'registrant_email', # primary, -> locations
    'registrant_name',
    'registrant_telephone',

    'registrant_postalCode', # -> locations
    'registrant_street1',
    'registrant_city',
    'registrant_country',
    'registrant_state',
]

check_pk(registrants[:1], registrants)

administrativeContacts = [ # merge with registants
    'administrativeContact_email', # -> contact
    'administrativeContact_telephone',
    'administrativeContact_name',

    'administrativeContact_city', # -> location
    'administrativeContact_country',
    'administrativeContact_postalCode',
    'administrativeContact_street1',
    'administrativeContact_state',
]

check_pk(registrants[:1], registrants)

registrars = [
    'registrarName',
    'whoisServer',
]

check_pk(registrars[:1], registrars)

keys = [
    'domainName',
    'status',
    'createdDate',
    'expiresDate',
    'updatedDate',
    'Audit_auditUpdatedDate',
    'contactEmail',

    'registrarName', # ->
    'whoisServer',
]


# keys = set(keys)


# print([k for k in good_keys if k.startswith('registrant')])


# print(unique_keys)

# print(k1_implies_k2('registrant_name', 'registrant_email'))
# exit()

# good_keys -= unique_keys

# d={}
# for k1 in keys:
#     d[k1] = set()
#     for k2 in keys - {k1}:
#         if k1_implies_k2(k1, k2):
#             d[k1].add(k2)

# f = {}
# for _z in d:
#     for q in d:
#         if q not in f:
#             f[q] = set()
#         for w in d[q]:
#             f[q] |= d[w]

# for v in whois:
#     f='Updated'
#     date1 = v[f'{f.lower()}Date']
#     date2 = v[f'standardReg{f}Date']
#     assert date1[:10] == date2[:10]
#     assert date1[10:11] == 'T' and date2[10:11]==' '
#     assert date1[11:19]==date2[11:19]
#     assert date1[19:]=='Z' and date2[19:]==' UTC'
#     # print([date1, date2])

# for q in d:
#     for w in d[q]:
#         assert q != w
#         for e in d[w] - {q}:
#             assert e in d[q]

# d1={}
# while d1 != d:
#     d1=d
#     for q in keys:
#         for w in keys:
#             for e in keys:
#                 if w in d[q] and e in d[w]:
#                     if e in d[q]:
#                         d[q].remove(e)

# for q in d:
#     for w in d[q]:
#         print(f'{q} -> {w}')



# pprint(d)

# for row in whois:
#     pprint([*row.items()])
#     exit()

