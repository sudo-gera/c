from pprint import pprint
import mitmproxy
import mitmproxy.http
import json
import pickle
import time
from traceback import *
import asyncio
import pickle
import base64
# from serialize import *

serializer = pickle

class mitm:
    def __init__(self):
        with open('./../loader/db.json','rb') as file:
            try:
                self.db = serializer.load(file)
            except Exception:
                self.db = {}
    async def request(self, flow:mitmproxy.http.HTTPFlow):
        f = f'{flow.request.host} {flow.request.port} {flow.request.path}'
        if f in self.db:
            flow.response = mitmproxy.http.Response.from_state(self.db[f])
        else:
            pass
            print(f, '-'*100)
    async def response(self, flow:mitmproxy.http.HTTPFlow):
        f = f'{flow.request.host} {flow.request.port} {flow.request.path}'
        self.db[f] = flow.response.get_state()
        with open('./../loader/db.json', 'wb') as file:
            serializer.dump(self.db, file)
    async def error(self, flow):
        print(time.asctime())
        print(time.time())
        print('error')
        pprint(flow)
        pprint(flow.get_state())
        time.sleep(0.1)
        print()
        print()
        

addons = [mitm()]
