import requests
import argparse
import base64
import pathlib
import json
import dataclasses
import time
try:
    from tqdm import tqdm
except Exception:
    tqdm = lambda x:x

@dataclasses.dataclass
class ovpn_server:
    code: str
    name: str
    country: str
    city: str

parser = argparse.ArgumentParser()
parser.add_argument('--cookie', required=True)
parser.add_argument('--xsrf-token', required=True)
parser.add_argument('--file', help='This file expected to be non-existent or output of previous run. in latter case its contents would be merged with freshly loaded data.', required=True)
parser.add_argument('--allow-invalidating-exisiting-creds', required=True, action='store_true')
args = parser.parse_args()

if not args.allow_invalidating_exisiting_creds:
    print('Flag --allow-invalidating-exisiting-creds is required. Cannot operate.')
    exit(1)

headers = { 'X-XSRF-TOKEN': args.xsrf_token, 'Cookie': args.cookie}

file = pathlib.Path(args.file)

if file.exists():
    with file.open() as f:
        data = json.load(f)
else:
    data = {}

codes = []

response = requests.get('https://my.kaspersky.com/api/ksec-vpn/locations/ovpn', headers=headers)
items = response.json()
for item_d in items:
    item = ovpn_server(**item_d)
    if item.code not in data:
        data[item.code] = {
            'last_updated': 0,
            'basic_info': item_d,
            'remotes': None,
        }
    data[item.code]['basic_info'] = item_d,
    codes.append(item.code)

data = {code: data[code] for code in codes}

codes.sort(key=lambda code: data[code]['last_updated'])

with file.open('w') as f:
    json.dump(data, f, indent=4)

for code in tqdm(codes):
    time.sleep(4)
    requests.delete('https://my.kaspersky.com/api/ksec-vpn/creds', headers=headers)
    response = requests.post('https://my.kaspersky.com/api/ksec-vpn/creds/ovpn/'+code, headers=headers)
    content = response.json()["oVpnFileData"]
    remotes = [line for line in base64.b64decode(content).decode().splitlines() if line.startswith('remote ')]
    data[code]['remotes'] = remotes
    data[code]['last_updated'] = time.time()
    with file.open('w') as f:
        json.dump(data, f, indent=4)





