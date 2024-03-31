import csv
from pprint import pprint
import json
import re
import random
from dataclasses import dataclass
import datetime
import time
with open('whois-db-download-info-sample.csv') as file:
    data = file.read()
whois = csv.DictReader(data.splitlines(keepends=True), dialect=csv.Sniffer().sniff(data))
whois = [*whois]
good_keys = {key for key in whois[0].keys() if all([v[key]!='' for v in whois])}

from dataclasses import dataclass
from functools import wraps

def make_table(get_pk):
    def process_class(cls):
        @wraps(cls, updated={})
        class test(cls):
            def __iter__(self):
                return iter((self.__class__.__name__, get_pk(self)))
            def __eq__(self, other):
                return tuple(self) == tuple(other)
            def __hash__(self) -> int:
                return hash(tuple(self))
            is_table = True
            # def __del__(self):
            #     print('del')
        return test
    return process_class

# def create_base(get_pk):
#     class base:
#         def __post_init__(self):
#             self.__hash__ = self.hash
#             self.__eq__ = self.eq
#             self.__iter__ = self.iter
#         def iter(self):
#             return iter((self.__class__.__name__, get_pk(self)))
#         def eq(self, other):
#             return tuple(self) == tuple(other)
#         def hash(self) -> int:
#             return hash(tuple(self))
#     return base


@make_table(lambda self: (self.name, self.state, self.country))
@dataclass
class city_table:
    id: int
    name: str
    state: str
    country: str

@make_table(lambda self: (self.city, self.street, self.postal_code))
@dataclass
class address_table:
    id: int
    city: city_table
    street: str
    postal_code: str

@make_table(lambda self: self.email)
@dataclass
class admin_table:
    email: str
    phone: str
    name: str
    address: address_table


@make_table(lambda self: self.email)
@dataclass
class registrant_table:
    email: str
    phone: str
    name: str
    address: address_table

@make_table(lambda self: self.name)
@dataclass
class registrar_table:
    name: str
    whois_server: str

@make_table(lambda self: self.name)
@dataclass
class domain_table:
    name: str
    updated_at: str
    expires_at: str
    created_at: str
    contact_email: str
    admin: admin_table
    registrant: registrant_table
    registrar: registrar_table

@make_table(lambda self: (self.name, self.updated_at))
@dataclass
class domain_table_history:
    name: str
    updated_at: str
    expires_at: str
    contact_email: str
    admin: admin_table
    registrant: registrant_table
    registrar: registrar_table


@make_table(lambda self: (self.name, self.domain))
@dataclass
class domain_status_table:
    name: str
    domain: domain_table


# data = {
#     'domain_table': [],
#     'domain_status_table': [],
#     'admin_table': [],
#     'city_table': [],
#     'registrant_table': [],
#     'address_table': [],
#     'domain_table_history': [],
#     'registrar_table': [],
# }

data = {}

# for v in whois:
#     data[]=None

# data[registrar_table(name='1',whois_server='2')]=None
# data[registrar_table(name='1',whois_server='0')]=None
# data[registrar_table(name='3',whois_server='4')]=None
# print(data)


    # data['domain_table'].append(dom
    #     'name': v['domainName'],
    #     'updated_at'
    # })


# print(good_keys)
for v in whois:
    v = dict(v)
    admin_city = city_table(
        id= len(data),
        name=v.pop('administrativeContact_city'),
        state=v.pop('administrativeContact_state'),
        country=v.pop('administrativeContact_country'),
    )
    if admin_city in data:
        admin_city=data[admin_city]
    else:
        data[admin_city]=admin_city
    admin_address = address_table(
        id=len(data),
        city=admin_city,
        street=v.pop('administrativeContact_street1'),
        postal_code=v.pop('administrativeContact_postalCode'),
    )
    if admin_address in data:
        admin_address=data[admin_address]
    else:
        data[admin_address]=admin_address
    admin = admin_table(
        email=v.pop('administrativeContact_email'),
        phone=v.pop('administrativeContact_telephone'),
        name=v.pop('administrativeContact_name'),
        address=admin_address,
    )
    if admin in data:
        admin=data[admin]
    else:
        data[admin]=admin
    registrant_city = city_table(
        id= len(data),
        name=v.pop('registrant_city'),
        state=v.pop('registrant_state'),
        country=v.pop('registrant_country'),
    )
    if registrant_city in data:
        registrant_city=data[registrant_city]
    else:
        data[registrant_city]=registrant_city
    registrant_address = address_table(
        id=len(data),
        city=registrant_city,
        street=v.pop('registrant_street1'),
        postal_code=v.pop('registrant_postalCode'),
    )
    if registrant_address in data:
        registrant_address=data[registrant_address]
    else:
        data[registrant_address]=registrant_address
    registrant = registrant_table(
        email=v.pop('registrant_email'),
        phone=v.pop('registrant_telephone'),
        name=v.pop('registrant_name'),
        address=registrant_address,
    )
    if registrant in data:
        registrant=data[registrant]
    else:
        data[registrant]=registrant
    registrar = registrar_table(
        name = v.pop('registrarName'),
        whois_server=v.pop('whoisServer'),
    )
    if registrar in data:
        registrar=data[registrar]
    else:
        data[registrar]=registrar
    domain = domain_table(
        name = v.pop('domainName'),
        created_at = v.pop('createdDate'),
        expires_at = v.pop('expiresDate'),
        updated_at = v.pop('updatedDate'),
        contact_email= v.pop('contactEmail'),
        admin=admin,
        registrar=registrar,
        registrant=registrant,
    )
    if domain in data:
        domain=data[domain]
    else:
        data[domain]=domain
    for status in v.pop('status').split('|'):
        status = domain_status_table(
            name = status.split(' ',1)[0],
            domain = domain,
        )
        if status in data:
            status=data[status]
        else:
            data[status]=status
    v.pop('standardRegCreatedDate')
    v.pop('standardRegUpdatedDate')
    v.pop('standardRegExpiresDate')
    v.pop('Audit_auditUpdatedDate')
    for k in [*v.keys()]:
        if k not in good_keys:
            v.pop(k)
    if v:
        print([*v.keys()])
        assert False

for item in [*data]:
    if isinstance(item, domain_table):
        history_v1 = domain_table_history(
            name=item.name,
            updated_at=item.updated_at,
            expires_at=item.expires_at,
            contact_email=item.contact_email,
            admin=item.admin,
            registrant=item.registrant,
            registrar=item.registrar,
        )
        if history_v1 in data:
            history_v1=data[history_v1]
        else:
            data[history_v1]=history_v1
        assert re.fullmatch(r'^\d\d\d\d-\d\d-\d\dT\d\d:\d\d:\d\dZ$', item.created_at)
        assert re.fullmatch(r'^\d\d\d\d-\d\d-\d\dT\d\d:\d\d:\d\dZ$', item.updated_at)
        assert re.fullmatch(r'^\d\d\d\d-\d\d-\d\dT\d\d:\d\d:\d\dZ$', item.expires_at)
        updated_at = time.mktime(datetime.datetime.fromisoformat(item.updated_at).timetuple())
        expires_at = time.mktime(datetime.datetime.fromisoformat(item.expires_at).timetuple())
        assert isinstance(updated_at, float)
        assert isinstance(expires_at, float)
        expires_at_ = random.random() * (expires_at - updated_at) + updated_at
        expires_at_ = datetime.datetime.fromtimestamp(expires_at_, datetime.UTC)
        expires_at_ = expires_at_.isoformat()[:19] + 'Z'
        updated_at = item.updated_at
        expires_at = item.expires_at
        assert re.fullmatch(r'^\d\d\d\d-\d\d-\d\dT\d\d:\d\d:\d\dZ$', expires_at_)
        history_v1 = domain_table_history(
            name=item.name,
            updated_at=item.created_at,
            expires_at=expires_at_,
            contact_email=item.contact_email,
            admin=item.admin,
            registrant=item.registrant,
            registrar=item.registrar,
        )
        if history_v1 in data:
            history_v1=data[history_v1]
        else:
            data[history_v1]=history_v1

tables = {}
for item in data:
    tables[item.__class__.__name__] = []
for item in data:
    r = {}
    for key in item.__dataclass_fields__:
        value = getattr(item, key)
        if hasattr(value, 'is_table'):
            if hasattr(value, 'id'):
                value = (value.__class__.__name__, value.id)
            else:
                value = tuple(value)
        r[key] = value
    tables[item.__class__.__name__].append(r)

# for v1 in tables['domain_table']:
#     for v2 in tables['domain_table']:
#         assert v1['registrant'] != v2['registrant'] or v1==v2

# pprint(tables)

# tables['city_table'] = [*dict([
#     (frozenset([
#         value
#     for key,value in item.items()
#     if key != 'id']), item)
# for item in tables['city_table']]).values()]



for name, table in tables.items():
    print(name, len(table))









# tables = json.dumps(tables, indent=4)
with open('whois-db-download-info-sample.json', 'w') as file:
    # pprint(tables, stream=file)
    file.write(json.dumps(tables, indent=4))

ids = {}

with open('whois-db-download-info-sample.pgsql', 'w') as file:
    for name, table in tables.items():
        for item in table:
            fields = [w for w in eval(name).__dataclass_fields__]
            if 'id' in fields:
                if name not in ids:
                    ids[name] = {}
                ids[name][item['id']] = len(ids[name]) + 1
                # pprint(ids)
            fields = [w for w in fields if w != 'id']
            print(f'insert into whois.{name} ({json.dumps(fields)[1:-1]}) values ({repr([[[w if isinstance(w, int) else w+'""""' for w in [( ids[w[0]][w[1]]  if isinstance(w[1], int) else w[1]) if isinstance(w, tuple) else w]][0] for w in [item[field]]][0] for field in fields])[1:-1].replace('""""','').replace(r"\'","''")});', file=file)


        #     print(name, field)
        #         print(f'insert into {name} values ')
        # print()
        # print(name, [*eval(name).__dataclass_fields__])
        #     # exit()


# good_keys -= {'status'}

# pprint(dict([(key, max([len(v[key]) for v in whois])) for key in good_keys]))
# exit()


# a=set()
# for v in whois:
#     for k in good_keys:
#         if 'status' in k.lower():
#             import re
#             print(v[k], k)
#             if not re.fullmatch(r'', v[k]):
#                 import time
#                 assert False
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

