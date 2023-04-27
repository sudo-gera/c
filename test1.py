<<<<<<< HEAD
try:
    from urllib.request import Request, urlopen  # Python 3
except ImportError:
    from urllib2 import Request, urlopen  # Python 2

req = Request('https://user225847803-etle274b.wormhole.vk-apps.com/')
req.add_header('Upgrade', 'WebSocket')
req.add_header('Connection', 'Upgrade')
content = urlopen(req).read()

print(content)

=======
from __future__ import annotations
from test import test
class _test1:
    pass

def _f1(a:_test1,b:test._test):
    ...
>>>>>>> 409b23bb6e0aba34433d9b534b13fbc7cca76958
