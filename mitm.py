from pprint import pprint
import mitmproxy
import mitmproxy.http
import json
import time

class mitm:
    def requestheaders(self, flow: mitmproxy.http.HTTPFlow):
        print('requestheaders')
        print(time.asctime())
        print(time.time())
        pprint(flow)
        pprint(flow.get_state())
        time.sleep(0.1)
<<<<<<< HEAD
        print()
        print()
=======
>>>>>>> 4af092fe4429bddb023f075574e6c9ff28b9e788
    def request(self, flow):
        print(time.asctime())
        print(time.time())
        print('request')
        pprint(flow)
        pprint(flow.get_state())
        time.sleep(0.1)
<<<<<<< HEAD
        print()
        print()
=======
>>>>>>> 4af092fe4429bddb023f075574e6c9ff28b9e788
    def responseheaders(self, flow):
        print(time.asctime())
        print(time.time())
        print('responseheaders')
        pprint(flow)
        pprint(flow.get_state())
        time.sleep(0.1)
<<<<<<< HEAD
        print()
        print()
=======
>>>>>>> 4af092fe4429bddb023f075574e6c9ff28b9e788
    def response(self, flow):
        print(time.asctime())
        print(time.time())
        print('response')
        pprint(flow)
        pprint(flow.get_state())
        time.sleep(0.1)
<<<<<<< HEAD
        print()
        print()
=======
>>>>>>> 4af092fe4429bddb023f075574e6c9ff28b9e788
    def error(self, flow):
        print(time.asctime())
        print(time.time())
        print('error')
        pprint(flow)
        pprint(flow.get_state())
        time.sleep(0.1)
<<<<<<< HEAD
        print()
        print()
=======
>>>>>>> 4af092fe4429bddb023f075574e6c9ff28b9e788

addons = [mitm()]


