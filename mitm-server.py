from pprint import pprint
import mitmproxy
import mitmproxy.http
import json
import time

class mitm:
    async def request(self, flow):
        print(time.asctime())
        print(time.time())
        print('request')
        pprint(flow)
        pprint(flow.get_state())
        time.sleep(0.1)
        print()
        print()
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


