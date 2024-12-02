from pprint import pprint
import mitmproxy
import mitmproxy.http
import json
import time
from traceback import *

class mitm:
    def request(self, flow):
        print(time.asctime())
        print(time.time())
        print('request')
        pprint(flow)
        pprint(flow.get_state())
        time.sleep(0.1)
        print()
        print()
        print_stack()
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


