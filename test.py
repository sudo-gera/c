from urllib.request import *
import json

headers = {'Content-Type': 'application/json'}
def call(path, data = None, **a):
    url = 'http://localhost:8000'
    req = Request(url + path, data=json.dumps(data).encode(), **a)
    for k,v in headers.items():
        req.add_header(k,v)
    res=urlopen(req).read().decode()
    return json.loads(res) if res else None

# res = call('/api/create_user', dict(username='testuser3', password='testpassword3'))
# print(res)
token = call('/api/token/access', dict(username="testuser1", password="testpassword1"))['access']
headers['Authorization'] = 'Bearer '+token
# res = call('/api/del_user',dict(title='new_flow'))
# print(res)
res = call('/api/create_flow',dict(title='new_flow'))
print(res)
# res = call('/api/get_flows')
# print(res)
# res = call('/api/create_block', dict(flow_id=6, content='hello world'))
# print(res)
# res = call('/api/set_block', dict(flow_id=6, content='goodbye world', block_id=2))
# print(res)
# res = call('/api/del_block', dict(flow_id=6, content='goodbye world', block_id=2))
# print(res)
# res = call('/api/get_blocks', dict(flow_id=6))
# print(res)


# res = call('/api/create_flow_link', dict(id=1, mode=2))
# print(res)
# res = call('/api/redeem_link', dict(token='ro-c15e546c16ddad0e093b8a740829c5e1662b8af56e38856166cf4b709ac6f837e3d38bbd7306492f641a1b88cd6b095e740ac57c665f90e603a65d8cd5a485104f59d82d60e52df2cbb11e0fef9e2f7958cb4ed5e95bcae3a7b77d188ebfbdf4d0f7368d4932c2d51edf0055f4ce6a606b8ec12fba45794f91e898e0168d287c7ee0fb05eb7bccda64a52d5c0da148a378058a41ed3197ff5e0ca10cba8f7b5cf573935fb67ff6a11dd57823886a05dc9740c4e33f7b3bd9f0b403a936945563d81d03cd9123a02c2f2e73eb30194d81d782427f82842958758d0fe0ae898e8aad75437c11ba272ce92ab2fa4bc90a757ba36263e86cbe7dcda3'))
# print(res)
# res = call('/api/redeem_link', dict(token='rw-fcb1020642ff79680bddfe9a8c6b807ab7de998b68cbbc3cfa4de723cf164b2f2a60ae12238f33037df61e405d79eac7bb212e75530a0fe2acbecd4cfdcf6dfb6ac70c0a46304c4ccfeb6cdc16bc1ec478e174d72cf8577a8f445558de0921ee156d321a10486932168d6d255095bddd77b17bf903a30cf5b988c5896ea578eac2653096963ef2509a1a29cef3c47949907655ee0d0503f4e44dfe46767c8c903734fc3c93e91c8355d5a8b8f22c4627b4e741f35a03922755462f2119de5dcb514496ce80af324357d301a53c9ee033a7398109421cfba686602a1d0effdab100670a8f095cf8ab9ae9354ff2298fe9dde8cd33051cce679bae'))
# print(res)
# res = call('/api/get_flow_users', dict(flow_id=1))
# print(res)
# res = call('/api/del_flow', dict(flow_id=1))
# print(res)
# res = call('/api/kick_flow_user', dict(flow_id=1, user_id=3))
# print(res)
# res = call('/api/del_flow_link', dict(id=1, link_id=4))
# print(res)
# links = call('/api/get_flow_links', dict(id=1))
# print(links)
# flows = call('/api/get_flows/')
# print(flows)
# res = call('/api/redeem_link/', dict(token='some token'))
# print(res)
# objects = call('/api/get_flow_links/', dict(id=1))
# print(objects)
# print(call('/api/set_flow_title/', dict(id=1, title='new_title')))


# req = urllib.request.Request('http://localhost:8000/api/token/access/')


